#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

//�ṹ��ʼȱ������
enum DEFECTCASE_FRM_TYPE
{
	DEFECTCASE_FRM_NORMAL = 0, //����ˮƽλ��
	DEFECTCASE_FRM_GRAVITY = 1, //�������ر���
	DEFECTCASE_FRM_BUCKLING = 2, //��������ģ̬
};
struct DefectTypeName
{
	const wchar_t* sName;
	int iType;
};
const struct DefectTypeName DefectCaseTypeNameArray[] =
{
#ifdef _SIMPLIFIED_CHINESE
	L"����ˮƽλ��",		DEFECTCASE_FRM_NORMAL,
	L"�������ر���",		DEFECTCASE_FRM_GRAVITY,
	L"��������ģ̬",		DEFECTCASE_FRM_BUCKLING
#else
	L"H_DISP",		DEFECTCASE_FRM_NORMAL,
	L"GRAVITY",		DEFECTCASE_FRM_GRAVITY,
	L"BUCKLING",	DEFECTCASE_FRM_BUCKLING
#endif
};
//����ȱ�ݽǶ�
struct FrmDefectAngleName
{
	CString sNote;
	int iAngle;
	CString GetName() const
	{
		CString str;
		str.Format(L"%d", iAngle);
		return str + sNote;
	};
};
const struct FrmDefectAngleName FrmDefectAngleArray[] =
{
	L"[+X]",		0,
	L"[+X+Y]",		45,
	L"[+Y]",		90,
	L"[-X+Y]",		135,
	L"[-X]",		180,
	L"[-X-Y]",		225,
	L"[-Y]",		270,
	L"[+X-Y]",		315
};

//������ʼȱ�ݹ���
class _SSG_DLLIMPEXP CDefectCaseFrm
{
public:
	CDefectCaseFrm(void);
	CDefectCaseFrm(CDefectCaseFrm& lc)
	{
		*this = lc;
	}
	~CDefectCaseFrm() {};

	CDefectCaseFrm& operator=(const CDefectCaseFrm& lc);
	BOOL operator==(const CDefectCaseFrm& lc);

	//DEFECTCASE_TYPE m_iType; //��ʼȱ������
	CString m_sCaseName;  //ȱ�ݹ�������
	CString m_sMemo; //ȱ�ݹ���˵��
	DEFECTCASE_FRM_TYPE m_iType; //ȱ������
	int m_iBucklingCase; //��������������
	int m_iMode; //ģ̬����
	float m_fDefect; //ȱ�����ֵ
	float m_fAngle; //ȱ�ݷ���

	BOOL m_bUpdate; //ȱ�ݲ����Ƿ�������޸ģ�TRUE����������ȱ���ļ�

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	int iMap; //�ɹ�����
	bool bMap; //�¹�����ʶ����true��ʾ�¹���
};

class _SSG_DLLIMPEXP DefectCaseFrmCollection
{
public:
	DefectCaseFrmCollection() { ; };
	DefectCaseFrmCollection(const DefectCaseFrmCollection& lc)
	{
		*this = lc;
	};
	~DefectCaseFrmCollection() { RemoveAll(); }

	int Append(CDefectCaseFrm* load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const { return aDefectPtr.GetCount(); }

	CDefectCaseFrm* GetAt(int i) { return aDefectPtr.GetAt(i); }

	CDefectCaseFrm* operator[](int i) { return aDefectPtr[i]; }

	void SetAt(int i, CDefectCaseFrm* load) { aDefectPtr[i] = load; }

	DefectCaseFrmCollection& operator=(const DefectCaseFrmCollection& load);

	void Write(CFile& fout)
	{
		for (int i = 0; i < aDefectPtr.GetCount(); i++)
			aDefectPtr[i]->Write(fout);
	}

private:
	CArray<CDefectCaseFrm*, CDefectCaseFrm*> aDefectPtr; //��ʼȱ�ݹ�������
};