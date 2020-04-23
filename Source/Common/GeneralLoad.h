
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



//工况组合
class _SSG_DLLIMPEXP CGeneralLoad
{
public:
	CGeneralLoad(void);
	CGeneralLoad(CASE_TYPE nType,bool bNewCode=true);
	CGeneralLoad(CGeneralLoad &lc)
	{
		*this=lc;
	}
	~CGeneralLoad() {}
	
	CASE_TYPE m_iCaseType;//荷载类型
	CString m_sCaseName;  //荷载工况名称
	CString m_sMemo;
	float m_fMassCoef;//重力荷载代表值组合值系数
	//分项系数：	恒：2018可靠性标准：不利主控、有利、0；2008可靠性标准不利主控、有利、不利非主控
	//						活：分项系数、组合系数、0
	//						风：分项系数、抗震组合系数、无震组合系数
	//					地震：主控、非主控、0
	float m_fPartCoef[3];
	float m_fLcComb[Sys_MaxLoadcaseComb];//荷载组合
	float m_fBucklingComb; //屈曲分析荷载组合
	CGeneralLoad& operator=(const CGeneralLoad& lc);
	BOOL operator==(const CGeneralLoad& lc);
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CGeneralCollection
{
public:
	CGeneralCollection(){
	m_iCode=1;
	m_fGravPart=1.2f;
	}
	CGeneralCollection(const CGeneralCollection &load) 
	{
		*this=load;
	};
	~CGeneralCollection(){RemoveAll();}

	int Append(CGeneralLoad *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aGenLoadPtr.GetCount();}

	CGeneralLoad *GetAt(int i) {return aGenLoadPtr.GetAt(i);}

	CGeneralLoad *operator[](int i) {return aGenLoadPtr[i];}

	void SetAt(int i,CGeneralLoad *load) {aGenLoadPtr[i]=load;}

	CGeneralCollection& operator=(const CGeneralCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aGenLoadPtr.GetCount();i++)
			aGenLoadPtr[i]->Write(fout);
	}
	
	int m_iCode;//1:Code2018 0:Code2008
	float m_fGravPart;//重力荷载分项系数
private:
	CArray<CGeneralLoad*,CGeneralLoad*> aGenLoadPtr; //荷载工况组合集合
};
