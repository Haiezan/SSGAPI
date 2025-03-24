
#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include <vector>
#include "..\Common\Loadmap.h"

enum DESIGN_TYPE
{
	DSN_USER = 0,//用户自定义
	DSN_STEEL = 1,//钢结构
	DSN_CRT = 2,		//混凝土
};

class _SSG_DLLIMPEXP CombData
{
public:
	char nCaseType;//0 StaticLoadcase 1 m_cLoad 2 m_cLoadStatic
	int nCaseId;//StaticLoadcase ID 
	float fFactor;

	CombData()
		: nCaseType(0)
		, nCaseId(-1)
		, fFactor(1.f)
	{
	}

	CombData(int Id, float factor)
		: nCaseType(0)
		, nCaseId(Id)
		, fFactor(factor)
	{
	}

	CombData(const CombData& data)
	{
		*this = data;
	}

	CombData& operator = (const CombData& data)
	{
		if (this == &data)
			return *this;

		nCaseType = data.nCaseType;
		nCaseId = data.nCaseId;
		fFactor = data.fFactor;

		return *this;
	}

	bool operator == (const CombData& data)const
	{
		if (this == &data)
			return true;

		if (nCaseType != data.nCaseType)
			return false;

		if (nCaseId != data.nCaseId)
			return false;

		if (abs(fFactor - data.fFactor) > 1e-6f)
			return false;

		return true;
	}

	CombData(int Type, int CaseId, float Factor)
		: nCaseType(Type)
		, nCaseId(CaseId)
		, fFactor(Factor)
	{
	}

	CString sCaseName() const;
	int GetCaseId(CString str);
};

//静力荷载工况
class _SSG_DLLIMPEXP CStaticLoadCase
{
public:
	CStaticLoadCase(void);
	CStaticLoadCase(STCASE_TYPE nType);
	CStaticLoadCase(CStaticLoadCase &lc)
	{
		*this=lc;
	}
	~CStaticLoadCase() {}
	
	STCASE_TYPE m_iCaseType;//荷载类型
	CString m_sCaseName;  //荷载工况名称
	CString m_sMemo;
	float m_fMassCoef;//重力荷载代表值组合值系数
	bool m_bLoadComb;// 是否由荷载工况组合生成
	CStaticLoadCase& operator=(const CStaticLoadCase& lc);
	BOOL operator==(const CStaticLoadCase& lc);
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CStaticLoadCaseCollection
{
public:
	CStaticLoadCaseCollection(){;};
	CStaticLoadCaseCollection(const CStaticLoadCaseCollection &stload) 
	{
		*this=stload;
	};
	~CStaticLoadCaseCollection(){RemoveAll();}

	int Append(CStaticLoadCase *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aStaticLoadPtr.GetCount();}

	CStaticLoadCase *GetAt(int i) {return aStaticLoadPtr.GetAt(i);}

	CStaticLoadCase *operator[](int i) const {return aStaticLoadPtr[i];}

	void SetAt(int i,CStaticLoadCase *load) {aStaticLoadPtr[i]=load;}

	CStaticLoadCaseCollection& operator=(const CStaticLoadCaseCollection &load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aStaticLoadPtr.GetCount();i++)
			aStaticLoadPtr[i]->Write(fout);
	}
private:
	CArray<CStaticLoadCase*,CStaticLoadCase*> aStaticLoadPtr; //荷载工况集合
public:
	vector<CombData> m_vStaticComb;
};

//工况组合
class _SSG_DLLIMPEXP CLoadCaseComb
{
public:
	CLoadCaseComb(void);
	CLoadCaseComb(CLoadCaseComb &lccb)
	{
		*this=lccb;
	}
	~CLoadCaseComb() {}

	CString m_sCombName;  //荷载工况组合名称
	CString m_sMemo;
	DESIGN_TYPE m_iDesignType;//设计类型
	COMB_TYPE m_iCombType;//组合方式

	vector<CombData> m_vCombData;

	CLoadCaseComb& operator=(const CLoadCaseComb& lccb);
	BOOL operator==(const CLoadCaseComb& lccb);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
	//得到组合类型0静力1无风地震2X风地震组合3Y风地震组合
	int GetCombType();
	//得到地震分项系数 
	float GetSeismicCoef();
};

class _SSG_DLLIMPEXP CLoadCaseCombCollection
{
public:
	CLoadCaseCombCollection(){;};
	CLoadCaseCombCollection(const CLoadCaseCombCollection &loadcomb) 
	{
		*this = loadcomb;
	};
	~CLoadCaseCombCollection(){RemoveAll();}

	int Append(CLoadCaseComb *loadcomb);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aLoadCombPtr.GetCount();}

	CLoadCaseComb *GetAt(int i) {return aLoadCombPtr.GetAt(i);}

	CLoadCaseComb *operator[](int i) {return aLoadCombPtr[i];}

	void SetAt(int i,CLoadCaseComb *loadcomb) {aLoadCombPtr[i]=loadcomb;}

	CLoadCaseCombCollection& operator=(const CLoadCaseCombCollection &loadcomb);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aLoadCombPtr.GetCount();i++)
			aLoadCombPtr[i]->Write(fout);
	}
private:
	CArray<CLoadCaseComb*,CLoadCaseComb*> aLoadCombPtr; //荷载工况集合
};

//动力荷载工况
class _SSG_DLLIMPEXP CDynamicLoadCase
{
public:
	CDynamicLoadCase(void);
	CDynamicLoadCase(DYCASE_TYPE nType);
	CDynamicLoadCase(CDynamicLoadCase &lc)
	{
		*this=lc;
	}
	~CDynamicLoadCase() {aDyload.clear();}
	
	DYCASE_TYPE m_iCaseType;//荷载类型
	CString m_sCaseName;  //荷载工况名称
	CString m_sMemo;
	LOADASSIGN aDyload;//对应荷载工况的动荷载
	CDynamicLoadCase& operator=(const CDynamicLoadCase& lc);
	BOOL operator==(const CDynamicLoadCase& lc);
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CDynamicLoadCaseCollection
{
public:
	CDynamicLoadCaseCollection(){;};
	CDynamicLoadCaseCollection(const CDynamicLoadCaseCollection &dyload) 
	{
		*this=dyload;
	};
	~CDynamicLoadCaseCollection(){RemoveAll();}

	int Append(CDynamicLoadCase *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aDynaLoadPtr.GetCount();}

	CDynamicLoadCase *GetAt(int i) {return aDynaLoadPtr.GetAt(i);}

	CDynamicLoadCase *operator[](int i) {return aDynaLoadPtr[i];}

	void SetAt(int i,CDynamicLoadCase *load) {aDynaLoadPtr[i]=load;}

	CDynamicLoadCaseCollection& operator=(const CDynamicLoadCaseCollection &load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aDynaLoadPtr.GetCount();i++)
			aDynaLoadPtr[i]->Write(fout);
	}
private:
	CArray<CDynamicLoadCase*,CDynamicLoadCase*> aDynaLoadPtr; //荷载工况集合
};
