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


//�߶���
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

	int VexIDM1,VexIDM2;  //�˵�IDM
	float fDeadLoad,fLiveLoad; //���غ�,�����в���ȡ����Ӧ��ʱ��д��ֵ��KN/m
	int idmBoundary;  //�߽�����ID�����������д����������2
	LOADASSIGN aload;  //��Ӧ���ع����ĺ��� 
	int *pNodes;//��ʱ����  //�ڵ㼯��,����ȫ�������Լ�����������γ�
	int nNodes;

	//�жϱ�����ͬ
	BOOL operator==(const CLine &line) const
	{
		if(line.VexIDM1==VexIDM1 && line.VexIDM2==VexIDM2) return TRUE;
		if(line.VexIDM1==VexIDM2 && line.VexIDM2==VexIDM1) return TRUE;
		return FALSE;
	}

	//���ƹ��캯��
	CLine(const CLine &line) 
	{
		pNodes=NULL;
		*this=line;
	}

	//�жϱ�����ͬ: pNodes
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
	//void SetCrossStory(BOOL bCrossStory=TRUE);  //ʵ�����������ߵĶ˵㣬�����ݱ��п�����ԣ�Ӧ����ʹ�õ����Դ���

	BOOL IsOnFloor(void);//��¥��

	BOOL IsCrossTower(void) const;
	//void SetCrossTower(BOOL bCrossTower=TRUE);  //ʵ�����������ߵĶ˵㣬�����ݱ��п������ԣ�Ӧ����ʹ�õ����Դ���

	inline float Length(const CVertex *vex) const //vexΪ������������
	{
		return (vex[VexIDM1]-vex[VexIDM2]).Length();
	}
	inline float Angle(const CVertex *vex) const //vexΪ������������
	{
		float length= (vex[VexIDM1]-vex[VexIDM2]).Length();
		float high=abs(vex[VexIDM1].z-vex[VexIDM2].z);
		return acos(high/length);
	}
	inline BOOL InRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ���ȫ�ھ��η�Χ�ڣ������߽��غ�
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)>0) return FALSE;
		if((vex1.y-vMin.y)*(vex1.y-vMax.y)>0) return FALSE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)>0) return FALSE;
		if((vex2.y-vMin.y)*(vex2.y-vMax.y)>0) return FALSE;
		return TRUE;
	}

	inline BOOL CrossRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ�������ص��������߽��غ�
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
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ
};

//�����Ĺ����棬������ʾ����
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

	//��ֵ���������
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

	int nVertex; //������
	Vector4 *pVertex; //�����������飬����ڹ����ľֲ�����
	DWORD color; //ʵ�ʻ�����ɫ
};

class _SSG_DLLIMPEXP CBeamFace
{
public:
	CBeamFace(void);
	~CBeamFace();

	Vector4 a1,b1,c1,d1; //��һ����Ķ���
	Vector4 a2,b2,c2,d2; //�ڶ�����Ķ���
	float fColor1,fColor2,fColor3; //a1-a2����ϵ����a1-b1����ϵ����a1-d1����ϵ��
};
