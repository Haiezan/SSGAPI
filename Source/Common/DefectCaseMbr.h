#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

enum DEFECTCASE_MBR_TYPE
{
	DEFECTCASE_MBR_DISP = 0, //������ʼȱ��
	DEFECTCASE_MBR_HARM = 1,  //�������򹹼���ʼȱ��
};
//����ȱ�ݽǶ�
struct MbrDefectAngleName
{
	CString sNote;
	int iAngle;
	CString GetName() const
	{
		CString str;
		str.Format(L"%d", iAngle);
		return str + sNote;
	};
	CString GetAngleStr() const
	{
		CString str;
		str.Format(L"%d", iAngle);
		return str;
	}
};
const struct MbrDefectAngleName MbrDefectAngleArray[] =
{
	L"[+2]",		0,
	L"[+2+3]",		45,
	L"[+3]",		90,
	L"[-2+3]",		135,
	L"[-2]",		180,
	L"[-2-3]",		225,
	L"[-3]",		270,
	L"[+2-3]",		315
};
const CString MbrDefectValueArray[] =
{
	L"0",L"1/1000",L"1/400",L"1/350",L"1/300",L"1/250"
};
//������ʼȱ�ݹ���
class _SSG_DLLIMPEXP CDefectCaseMbr
{
public:
	CDefectCaseMbr(void);
	CDefectCaseMbr(CDefectCaseMbr& lc)
	{
		*this = lc;
	}
	~CDefectCaseMbr() {};

	CDefectCaseMbr& operator=(const CDefectCaseMbr& lc);
	BOOL operator==(const CDefectCaseMbr& lc);

	//DEFECTCASE_TYPE m_iType; //��ʼȱ������
	CString m_sCaseName;  //ȱ�ݹ�������
	CString m_sMemo; //ȱ�ݹ���˵��
	DEFECTCASE_MBR_TYPE m_iType; //ȱ������
	float m_fAngle; //ȱ�ݷ���

	BOOL m_bUpdate; //ȱ�ݲ����Ƿ�������޸ģ�TRUE����������ȱ���ļ�

	float m_fAngleBeam;
	float m_fAngleColumn;
	float m_fAngleBrace;
	BOOL m_bPlateUsedNotAdd; //��¥����������������ȱ��

	BOOL AddMemberData();
	BOOL SetMemberAngle(int iLC); //iLC������
	BOOL SetMemberDefect(int iLC); //iLC������
	BOOL SetMemberAngle(int iLC, CString sCase); //iLC������,sCase�����������ݹ�������

	static CString GetDefectStr(float fDefect); //��ʼȱ�ݱ�﷽ʽ 300->1/300
	static CString GetAngleStr(float fAngle); //�Ƕ�ȡ��
	static float GetDefectValue(CString str); //ȱ�ݴ���ֵת������ 1/300->float
	static float GetAngleValue(CString str); //�Ƕ�ת������

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	int iMap; //�ɹ�����
	bool bMap; //�¹�����ʶ����true��ʾ�¹���
};

class _SSG_DLLIMPEXP DefectCaseMbrCollection
{
public:
	DefectCaseMbrCollection() { ; };
	DefectCaseMbrCollection(const DefectCaseMbrCollection& lc)
	{
		*this = lc;
	};
	~DefectCaseMbrCollection() { RemoveAll(); }

	int Append(CDefectCaseMbr* load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const { return aDefectPtr.GetCount(); }

	CDefectCaseMbr* GetAt(int i) { return aDefectPtr.GetAt(i); }

	CDefectCaseMbr* operator[](int i) { return aDefectPtr[i]; }

	void SetAt(int i, CDefectCaseMbr* load) { aDefectPtr[i] = load; }

	DefectCaseMbrCollection& operator=(const DefectCaseMbrCollection& load);

	void Write(CFile& fout)
	{
		for (int i = 0; i < aDefectPtr.GetCount(); i++)
			aDefectPtr[i]->Write(fout);
	}

private:
	CArray<CDefectCaseMbr*, CDefectCaseMbr*> aDefectPtr; //��ʼȱ�ݹ�������
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

	CString GetShowText(const float fDefect, const float fAngle, const BOOL bDefect = TRUE, const BOOL bAngle = TRUE);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout, int& index, int id, int iStructType);
private:
	int numLoad;
	float** loadData; //��ȱ�ݹ���ȱ��ֵ ������ȱ��ֵ�������š�ȱ�ݴ���ֵ��ȱ�ݷ���
	static int nData; //ÿ��ȱ�ݹ������ݸ��� Ϊ3
};

