#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

//结构初始缺陷类型
enum DEFECTCASE_FRM_TYPE
{
	DEFECTCASE_FRM_NORMAL = 0, //假想水平位移
	DEFECTCASE_FRM_GRAVITY = 1, //重力荷载变形
	DEFECTCASE_FRM_BUCKLING = 2, //屈曲分析模态
};
struct DefectTypeName
{
	const wchar_t* sName;
	int iType;
};
const struct DefectTypeName DefectCaseTypeNameArray[] =
{
#ifdef _SIMPLIFIED_CHINESE
	L"假想水平位移",		DEFECTCASE_FRM_NORMAL,
	L"重力荷载变形",		DEFECTCASE_FRM_GRAVITY,
	L"屈曲分析模态",		DEFECTCASE_FRM_BUCKLING
#else
	L"H_DISP",		DEFECTCASE_FRM_NORMAL,
	L"GRAVITY",		DEFECTCASE_FRM_GRAVITY,
	L"BUCKLING",	DEFECTCASE_FRM_BUCKLING
#endif
};
//典型缺陷角度
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

//构件初始缺陷工况
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

	//DEFECTCASE_TYPE m_iType; //初始缺陷类型
	CString m_sCaseName;  //缺陷工况名称
	CString m_sMemo; //缺陷工况说明
	DEFECTCASE_FRM_TYPE m_iType; //缺陷类型
	int m_iBucklingCase; //屈曲分析工况号
	int m_iMode; //模态阶数
	float m_fDefect; //缺陷最大值
	float m_fAngle; //缺陷方向

	BOOL m_bUpdate; //缺陷参数是否进行了修改，TRUE需重新生成缺陷文件

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	int iMap; //旧工况号
	bool bMap; //新工况标识符，true表示新工况
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
	CArray<CDefectCaseFrm*, CDefectCaseFrm*> aDefectPtr; //初始缺陷工况集合
};