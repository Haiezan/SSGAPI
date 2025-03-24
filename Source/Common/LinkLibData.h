#pragma once
#include "afxwin.h"
#include "DataDamper.h"
#include <vector>

const int nLinkLibData = 20;
const int nMaxLen = 100;

struct _SSG_DLLIMPEXP LinkLibData
{
	LINK_SUBTYPE link_type;
	int sub_type;
	char chName[nMaxLen];
	union
	{
		struct INFO_LRB IsolatorInfo;
		struct INFO_ESB ESBInfo;
		struct INFO_FPS FPSInfo;
		struct INFO_BRB BRBInfo;
		struct INFO_VFD VFDInfo;
		struct INFO_MYD MYDInfo;
		float fData[nLinkLibData];
	};
	LinkLibData()
		: link_type(LINK_UNKNOWN)
		, sub_type(-1)
	{
		memset(chName, 0, sizeof(char) * nMaxLen);
		memset(fData, 0, sizeof(float) * nLinkLibData);
	}
	LinkLibData(const LinkLibData& link)
	{
		*this = link;
	};
};

class _SSG_DLLIMPEXP CLinkLib
{
public:
	CLinkLib();
	~CLinkLib();

	void ClearLinkLib();
	bool GetLinkLIB(LINK_SUBTYPE link_type, int subType = 0);
	int GetCount() { return m_cLib.GetCount(); }
	LinkLibData* operator[](int i) { return m_cLib[i];}
	static bool GenLinkLIB(const CString& sFile, bool bSysLib, bool bAppend = false);
	static bool ExportLinkLIBTxt(LINK_SUBTYPE link_type, bool bSysLib);
	void SetLibType(bool bSysLib = false) { m_bSysLib = bSysLib; };
	bool GetLIBSortParamISO(std::vector<float>& vS2, std::vector<float>& vShear) const;
	bool GetLIBSortParamESB(std::vector<float>& vCoef, std::vector<float>& vShear) const;
	bool GetLIBSortParamFPS(std::vector<float>& vType, std::vector<float>& vRad, std::vector<float>& vCSlow, std::vector<float>& vCFast) const;
	bool GetLIBSortParamBRB(std::vector<float>& vYieldF) const;
	bool GetLIBSortParamVFD(std::vector<float>& vDampExp, std::vector<float>& vUpF) const;

	//BOOL GetLIBNumAndName(int iType,int &iNum,CString *sNames);
	//BOOL GetLIBDataByName(int iType,CString sNames,float fS2,float fShearMod,float *fData);
	//BOOL GetLIBData(BOOL& bLNB, BOOL& bLRB);
private:
	bool m_bSysLib;
	CArray<LinkLibData*, LinkLibData*> m_cLib;
};