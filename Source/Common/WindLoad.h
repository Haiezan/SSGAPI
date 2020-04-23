
#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include "UserDefine.h"

#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>
#include <map>

using namespace std;



//风荷载
class _SSG_DLLIMPEXP CWindLoad
{
public:
	CWindLoad(void);
	CWindLoad(CWindLoad &lc)
	{
		*this=lc;
	}
	~CWindLoad() {}

	
	CString sCaseName;  //风荷载工况名称
	BOOL m_bUserDefine;   //是否用户自定义,0-程序计算,1-用户自定义
		

	//风荷载
	int m_iRough;  //粗糙度类别，0-A，1-B，2-C，3-D； 
    float m_fWindPressure; //基本风压；
	float m_fXPeriod; //X向基本周期；
	float m_fYPeriod; //Y向基本周期；
	float m_fDamp;    //风荷载计算用阻尼比；
	float m_fAmp;     //风荷载效应放大系数；
	int m_iGroup;     //风荷载体型分段数；
	int m_iHighStory[3]; //三段最高楼层号；
	float m_fShapeCoefGroup[3][2]; //三段X向体型系数、Y向体型系数； 
	int m_iAlongWind; //是否考虑顺风向风振，0-不考虑，1-考虑；
	int m_iAcrossWind;//是否考虑横风向风振，0-不考虑，1-考虑；
	int m_iTorWind;   //是否考虑扭转向风振，0-不考虑，1-考虑；
	int m_iAngleType; //切角类型，0-削角，1-凹角；
	float m_fbBratio; //b/B
	float m_fFirstTorPeriod; //第一扭转周期
	float m_fLevel; //室外地面标高


	float fWindAngle;	//风荷载作用方向与X轴夹角
	float fCoefAlong;	//顺风向荷载系数
	float fCoefAcross;	//横风向荷载系数
	float fCoefTortion;	//扭转风荷载系数
	float m_AlongWind[Sys_Max_Stories][Sys_Max_Towers]; //顺风向荷载
	float m_AcrossWind[Sys_Max_Stories][Sys_Max_Towers]; //横风向风荷载
	float m_TorsionalWind[Sys_Max_Stories][Sys_Max_Towers]; //扭转风荷载
	float m_fLcComb[Sys_MaxLoadcaseComb];//荷载组合
	float m_fBucklingComb; //屈曲分析荷载组合

	CWindLoad& operator=(const CWindLoad& lc);
	BOOL operator==(const CWindLoad& lc);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CWindCollection
{
public:
	CWindCollection(){;}
	CWindCollection(const CWindCollection &load) 
	{
		*this=load;
	};
	~CWindCollection(){RemoveAll();}

	int Append(CWindLoad *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aWindLoadPtr.GetCount();}

	CWindLoad *GetAt(int i) {return aWindLoadPtr.GetAt(i);}

	CWindLoad *operator[](int i) {return aWindLoadPtr[i];}

	void SetAt(int i,CWindLoad *load) {aWindLoadPtr[i]=load;}

	CWindCollection& operator=(const CWindCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aWindLoadPtr.GetCount();i++)
			aWindLoadPtr[i]->Write(fout);
	}

private:
	CArray<CWindLoad*,CWindLoad*> aWindLoadPtr; //荷载工况组合集合
};
