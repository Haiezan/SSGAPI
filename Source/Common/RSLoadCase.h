
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



//反应谱函数
class _SSG_DLLIMPEXP CRSLoadCase
{
public:
	CRSLoadCase(void);
	CRSLoadCase(CRSLoadCase &Rs)
	{
		*this=Rs;
	}
	~CRSLoadCase() {}	

	//反应谱函数
	CString m_sRSLCName;         //反应谱工况名称
	int m_iRSFuntion;     //反应谱函数编号
	int m_iDir;       //方向
	float m_fAngle;   //角度
	BOOL m_bAutoSearch; //自动搜索最不利角度
	int m_iCombType;    //组合方式
	int m_iDampType;    //阻尼类型
	float m_fUniDampRatio;   //统一阻尼比
	float m_fSteelDampRatio; //钢材阻尼比
	float m_fConDampRatio;   //混凝土阻尼比
	float m_fTReduCoef;      //周期折减系数


	CRSLoadCase& operator=(const CRSLoadCase& Rs);
	BOOL operator==(const CRSLoadCase& Rs);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CRSLoadCaseCollection
{
public:
	CRSLoadCaseCollection(){;}
	CRSLoadCaseCollection(const CRSLoadCaseCollection &RS) 
	{
		*this=RS;
	};
	~CRSLoadCaseCollection(){RemoveAll();}

	int Append(CRSLoadCase *RS);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aRSPtr.GetCount();}

	CRSLoadCase *GetAt(int i) {return aRSPtr.GetAt(i);}

	CRSLoadCase *operator[](int i) {return aRSPtr[i];}

	void SetAt(int i,CRSLoadCase *RS) {aRSPtr[i]=RS;}

	CRSLoadCaseCollection& operator=(const CRSLoadCaseCollection&RS);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aRSPtr.GetCount();i++)
			aRSPtr[i]->Write(fout);
	}

private:
	CArray<CRSLoadCase*,CRSLoadCase*> aRSPtr; //反应谱函数集合
};
