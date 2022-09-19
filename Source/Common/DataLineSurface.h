#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
//#include "PublicFunc.h"
//#include "PublicFunc_MFC.h"
//#include "PublicFunc_Cpp.h"
//
//#include "ASCFile.h"
//#include "UserDefine.h"
//#include "BeamSection.h"
//#include "Material.h"
//#include "EdgeStruct.h"
//#include "PlateSection.h"
//#include "Loadmap.h"

#include "DataPrimitive.h"
#include "Loadmap.h"
#include "DataVertex.h"

#include <afxtempl.h>
#include <vector>
#include <map>

class CVertex;

using namespace std;


//线段类
class _SSG_DLLIMPEXP CLine : public CPrimitiveProp
{
public:
	CLine(void);
	CLine(int i1,int i2,int istory);
	~CLine()
	{
		if(pNodes)
		{
			delete []pNodes;
			pNodes=NULL;
		}
	};

	int VexIDM1,VexIDM2;  //端点IDM
	float fDeadLoad,fLiveLoad; //线载荷,本类中不读取，在应用时读写赋值，KN/m
	int idmBoundary;  //边界条件ID，不参与类读写，单独处理2
	LOADASSIGN aload;  //对应荷载工况的荷载 
	int *pNodes;//临时数据  //节点集合,生成全部网格以及读入网格后形成
	int nNodes;

	//判断编码相同
	BOOL operator==(const CLine &line) const
	{
		if(line.VexIDM1==VexIDM1 && line.VexIDM2==VexIDM2) return TRUE;
		if(line.VexIDM1==VexIDM2 && line.VexIDM2==VexIDM1) return TRUE;
		return FALSE;
	}

	//复制构造函数
	CLine(const CLine &line) 
	{
		pNodes=NULL;
		*this=line;
	}

	//判断编码相同: pNodes
	CLine & operator=(const CLine &line) 
	{
		if(this==&line) return *this;

		if(pNodes)
		{
			delete []pNodes;
			pNodes=NULL;
			nNodes=0;
		}
		*(CPrimitiveProp *)this=(CPrimitiveProp &)line;

		VexIDM1=line.VexIDM1;
		VexIDM2=line.VexIDM2;
		fDeadLoad=line.fDeadLoad;
		fLiveLoad=line.fLiveLoad;
		idmBoundary=line.idmBoundary;
		aload=line.aload;
		//nNodes=line.nNodes;
		//if(line.pNodes)
		//{
		//	pNodes=new int[nNodes];
		//	for (int i=0;i<nNodes;i++)
		//		pNodes[i]=line.pNodes[i];
		//}

		return *this;
	}

	BOOL IsCrossStory(void) const;
	//void SetCrossStory(BOOL bCrossStory=TRUE);  //实际上是设置线的端点，线数据被有跨层属性，应避免使用点属性带入

	BOOL IsOnFloor(void);//在楼面

	BOOL IsCrossTower(void) const;
	//void SetCrossTower(BOOL bCrossTower=TRUE);  //实际上是设置线的端点，线数据被有跨塔属性，应避免使用点属性带入

	inline float Length(const CVertex *vex) const //vex为顶点坐标数组
	{
		return (vex[VexIDM1]-vex[VexIDM2]).Length();
	}
	inline float Angle(const CVertex *vex) const //vex为顶点坐标数组
	{
		float length= (vex[VexIDM1]-vex[VexIDM2]).Length();
		float high=abs(vex[VexIDM1].z-vex[VexIDM2].z);
		return acos(high/length);
	}
	inline BOOL InRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //正选，线段是否完全在矩形范围内，包括边界重合
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)>0) return FALSE;
		if((vex1.y-vMin.y)*(vex1.y-vMax.y)>0) return FALSE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)>0) return FALSE;
		if((vex2.y-vMin.y)*(vex2.y-vMax.y)>0) return FALSE;
		return TRUE;
	}

	inline BOOL CrossRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //反选，线段是否与矩形重叠，包括边界重合
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)<0 && (vex1.y-vMin.y)*(vex1.y-vMax.y)<0) return TRUE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)<0 && (vex2.y-vMin.y)*(vex2.y-vMax.y)<0) return TRUE;
		return FALSE;
	}

	void Clear(void);
	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);
	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取
};

//构件的构造面，用于显示绘制
class _SSG_DLLIMPEXP CSurface
{
public:
	CSurface(void) {nVertex=0;pVertex=NULL;color=0;}
	~CSurface() {delete[] pVertex;}

	CSurface(CSurface &surf)
	{
		pVertex=NULL;
		*this=surf;
	}

	//赋值运算符重载
	CSurface & operator=(const CSurface& surf)
	{
		if(this==&surf) return *this;

		delete[] pVertex;
		nVertex=surf.nVertex;
		pVertex=new Vector4[nVertex];
		for(int i=0;i<nVertex;i++)
		{
			pVertex[i]=surf.pVertex[i];
		}
		return *this;
	}

	int nVertex; //顶点数
	Vector4 *pVertex; //顶点坐标数组，相对于构件的局部坐标
	DWORD color; //实际绘制颜色
};

class _SSG_DLLIMPEXP CBeamFace
{
public:
	CBeamFace(void);
	~CBeamFace();

	Vector4 a1,b1,c1,d1; //第一个面的顶点
	Vector4 a2,b2,c2,d2; //第二个面的顶点
	float fColor1,fColor2,fColor3; //a1-a2光照系数，a1-b1光照系数，a1-d1光照系数
};
