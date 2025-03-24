#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

enum DEFECTCASE_MBR_TYPE
{
	DEFECTCASE_MBR_DISP = 0, //构件初始缺陷
	DEFECTCASE_MBR_HARM = 1,  //不利方向构件初始缺陷
};
//典型缺陷角度
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
//构件初始缺陷工况
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

	//DEFECTCASE_TYPE m_iType; //初始缺陷类型
	CString m_sCaseName;  //缺陷工况名称
	CString m_sMemo; //缺陷工况说明
	DEFECTCASE_MBR_TYPE m_iType; //缺陷类型
	float m_fAngle; //缺陷方向

	BOOL m_bUpdate; //缺陷参数是否进行了修改，TRUE需重新生成缺陷文件

	float m_fAngleBeam;
	float m_fAngleColumn;
	float m_fAngleBrace;
	BOOL m_bPlateUsedNotAdd; //与楼板相连构件不考虑缺陷

	BOOL AddMemberData();
	BOOL SetMemberAngle(int iLC); //iLC工况号
	BOOL SetMemberDefect(int iLC); //iLC工况号
	BOOL SetMemberAngle(int iLC, CString sCase); //iLC工况号,sCase不利方向依据工况名称

	static CString GetDefectStr(float fDefect); //初始缺陷表达方式 300->1/300
	static CString GetAngleStr(float fAngle); //角度取整
	static float GetDefectValue(CString str); //缺陷代表值转浮点数 1/300->float
	static float GetAngleValue(CString str); //角度转浮点数

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	int iMap; //旧工况号
	bool bMap; //新工况标识符，true表示新工况
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
	CArray<CDefectCaseMbr*, CDefectCaseMbr*> aDefectPtr; //初始缺陷工况集合
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

	CString GetShowText(const float fDefect, const float fAngle, const BOOL bDefect = TRUE, const BOOL bAngle = TRUE);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout, int& index, int id, int iStructType);
private:
	int numLoad;
	float** loadData; //各缺陷工况缺陷值 工况、缺陷值（工况号、缺陷代表值、缺陷方向）
	static int nData; //每个缺陷工况数据个数 为3
};

