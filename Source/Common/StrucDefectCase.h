#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

enum DEFECTCASE_TYPE
{
	DEFECTCASE_NORMAL = 0, //构件初始缺陷
	DEFECTCASE_DISA = 1, //构件初始缺陷
	DEFECTCASE_RAND = 2,  //结构初始缺陷
};

//初始缺陷工况
class _SSG_DLLIMPEXP CStrucDefectCase
{
public:
	CStrucDefectCase(void);
	CStrucDefectCase(CStrucDefectCase& lc)
	{
		*this = lc;
	}
	~CStrucDefectCase() {};

	CStrucDefectCase& operator=(const CStrucDefectCase& lc);
	BOOL operator==(const CStrucDefectCase& lc);

	//DEFECTCASE_TYPE m_iType; //初始缺陷类型
	CString m_sCaseName;  //缺陷工况名称
	CString m_sMemo; //缺陷工况说明
	DEFECTCASE_TYPE m_iType; //缺陷类型
	float m_fAngle; //缺陷方向

	float m_fAngleBeam;
	float m_fAngleColumn;
	float m_fAngleBrace;

	void Read(CASCFile& fin);
	void Write(CFile& fout);
};

class _SSG_DLLIMPEXP CStrucDefectCaseCollection
{
public:
	CStrucDefectCaseCollection() { ; };
	CStrucDefectCaseCollection(const CStrucDefectCaseCollection& lc)
	{
		*this = lc;
	};
	~CStrucDefectCaseCollection() { RemoveAll(); }

	int Append(CStrucDefectCase* load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const { return aDefectPtr.GetCount(); }

	CStrucDefectCase* GetAt(int i) { return aDefectPtr.GetAt(i); }

	CStrucDefectCase* operator[](int i) { return aDefectPtr[i]; }

	void SetAt(int i, CStrucDefectCase* load) { aDefectPtr[i] = load; }

	CStrucDefectCaseCollection& operator=(const CStrucDefectCaseCollection& load);

	void Write(CFile& fout)
	{
		for (int i = 0; i < aDefectPtr.GetCount(); i++)
			aDefectPtr[i]->Write(fout);
	}

private:
	CArray<CStrucDefectCase*, CStrucDefectCase*> aDefectPtr; //初始缺陷工况集合
};

//初始缺陷数据
class _SSG_DLLIMPEXP DEFECTASSIGN
{
public:
	DEFECTASSIGN()
	{
		loadData = NULL;
		numLoad = 0;
	}
	~DEFECTASSIGN()
	{
		clear();
	}
	void clear();
	DEFECTASSIGN& operator=(const DEFECTASSIGN& lm);
	bool operator!=(const DEFECTASSIGN& lm) const;

	int inline GetLoadCount() const { return numLoad; };

	BOOL DeleteLoad(int iLC);
	BOOL AppendLoad(int iLC, const float* pData);
	BOOL ReorderLoad(int iLC, int iNew);
	BOOL RemoveLoad(int iLC);

	BOOL SetLoad(int iLC, const float* pData);
	float* GetLoad(int iLC);
	BOOL AddLoad(float* pData);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout, int& index, int id, int iStructType);
private:
	int numLoad;
	float** loadData; //各缺陷工况缺陷值 工况、缺陷值（工况号、缺陷代表值、缺陷方向）
	static int nData; //每个缺陷工况数据个数 为3
};

