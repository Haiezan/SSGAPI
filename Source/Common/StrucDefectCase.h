#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

enum DEFECTCASE_TYPE
{
	DEFECTCASE_NORMAL = 0, //������ʼȱ��
	DEFECTCASE_DISA = 1, //������ʼȱ��
	DEFECTCASE_RAND = 2,  //�ṹ��ʼȱ��
};

//��ʼȱ�ݹ���
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

	//DEFECTCASE_TYPE m_iType; //��ʼȱ������
	CString m_sCaseName;  //ȱ�ݹ�������
	CString m_sMemo; //ȱ�ݹ���˵��
	DEFECTCASE_TYPE m_iType; //ȱ������
	float m_fAngle; //ȱ�ݷ���

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
	CArray<CStrucDefectCase*, CStrucDefectCase*> aDefectPtr; //��ʼȱ�ݹ�������
};

//��ʼȱ������
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
	float** loadData; //��ȱ�ݹ���ȱ��ֵ ������ȱ��ֵ�������š�ȱ�ݴ���ֵ��ȱ�ݷ���
	static int nData; //ÿ��ȱ�ݹ������ݸ��� Ϊ3
};

