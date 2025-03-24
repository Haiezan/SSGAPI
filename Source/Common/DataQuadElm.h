#pragma once

#include <afxtempl.h>
#include <vector>
#include <map>

#include "HeadDefine.h"

using namespace std;

//四结点四边形面单元，用于网格
class _SSG_DLLIMPEXP CQuadElm : public CPrimitiveProp
{
public:
	CQuadElm(void)
		: PlateStrucIDM(-1)
		, pVexIDM()
		, iBlock(0)
	{}

	enum {VEXNUM=4}; //边界点数，不重合
	int pVexIDM[VEXNUM];  //端点ID数组
	int PlateStrucIDM; //关联的构件ID，用于获得配筋信息
	//STRUCT_TYPE iStrucType;

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //接口中单元分类ID

	//	int pVexIrr[4];

	const CPlateStruc &GetPlate(const CArray<CPlateStruc,CPlateStruc&>  &aPlate) const
	{
		if(PlateStrucIDM<0 || PlateStrucIDM>=aPlate.GetCount()) return *(CPlateStruc *)NULL;
		return aPlate[PlateStrucIDM];
	}

	const CPlateStruc *GetPlateP(const CPlateStruc *pPlate,int nPlate) const
	{
		if(!pPlate) return NULL;
		if(PlateStrucIDM<0 || PlateStrucIDM>=nPlate) return NULL;
		return pPlate+PlateStrucIDM;
	}

	//按照构件设置属性
	void CopyProp(const CPlateStruc &plate) 
	{
		*(CPrimitiveProp *)this=plate;
		//iStrucType=plate.iStrucType;
	}

	float Area(const CVertex *pNode) const;  //计算四边形面积>0,pNode为结点坐标数组
	float Area(const Vector4* pNode) const;
	float GetTcr() const; //计算单元临界步长

	//得到坐标范围
	void GetRange(const CVertex* pVexArray, Vector4 &rMin,Vector4 &rMax);

	void Clear(void) {PlateStrucIDM=-1;iBlock=0; /*memset(pVexIrr,0,sizeof(pVexIrr))*/;}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
	static CQuadElm *Renew(CQuadElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CQuadElm *newp=new CQuadElm[newCount];
		if(!newp) return NULL;

		int k=min(oldCount,newCount);
		for(int i=0;i<k;i++)
		{
			newp[i]=oldp[i];
		}
		delete[] oldp;
		oldp=newp;
		return newp;
	}

	//w为法线，顶点编号符合右手定则，u、v与整体坐标系没有关系
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//计算中心点坐标，pVex为全局结点数组，因此这里要用传进来的坐标数组参数进行计算
	Vector4 GetCenter(const CVertex *pVex) const;

	virtual BOOL Read(CASCFile &fin); //派生类的虚函数关键字virtual可写可不写，但总是虚函数
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype, float area);

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};
