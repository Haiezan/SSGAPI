
#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include <vector>
#include "..\Common\Loadmap.h"

enum DESIGN_TYPE
{
	DSN_USER = 0,//�û��Զ���
	DSN_STEEL = 1,//�ֽṹ
	DSN_CRT = 2,		//������
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

//�������ع���
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
	
	STCASE_TYPE m_iCaseType;//��������
	CString m_sCaseName;  //���ع�������
	CString m_sMemo;
	float m_fMassCoef;//�������ش���ֵ���ֵϵ��
	bool m_bLoadComb;// �Ƿ��ɺ��ع����������
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
	CArray<CStaticLoadCase*,CStaticLoadCase*> aStaticLoadPtr; //���ع�������
public:
	vector<CombData> m_vStaticComb;
};

//�������
class _SSG_DLLIMPEXP CLoadCaseComb
{
public:
	CLoadCaseComb(void);
	CLoadCaseComb(CLoadCaseComb &lccb)
	{
		*this=lccb;
	}
	~CLoadCaseComb() {}

	CString m_sCombName;  //���ع����������
	CString m_sMemo;
	DESIGN_TYPE m_iDesignType;//�������
	COMB_TYPE m_iCombType;//��Ϸ�ʽ

	vector<CombData> m_vCombData;

	CLoadCaseComb& operator=(const CLoadCaseComb& lccb);
	BOOL operator==(const CLoadCaseComb& lccb);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
	//�õ��������0����1�޷����2X��������3Y��������
	int GetCombType();
	//�õ��������ϵ�� 
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
	CArray<CLoadCaseComb*,CLoadCaseComb*> aLoadCombPtr; //���ع�������
};

//�������ع���
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
	
	DYCASE_TYPE m_iCaseType;//��������
	CString m_sCaseName;  //���ع�������
	CString m_sMemo;
	LOADASSIGN aDyload;//��Ӧ���ع����Ķ�����
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
	CArray<CDynamicLoadCase*,CDynamicLoadCase*> aDynaLoadPtr; //���ع�������
};
