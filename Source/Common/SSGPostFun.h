#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "HeadDefine.h"
#include "SSGData.h"
#include "ReportE.h"

namespace ssgPost
{
	_POST_FUN void ShowShearforcecurve(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowMomentcurve(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowEnergyCurve(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowEnergyStructCurve(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void OnOpendatafile();
	_POST_FUN void OnTermCurve();
	_POST_FUN void OnSupportfile();
	_POST_FUN void OnSupportfileNoIso();
	_POST_FUN void OnTerm();
	_POST_FUN void OnTermNoIso();
	_POST_FUN void OnMaxfreqfile();
	_POST_FUN void OnMaxfreqfileNoIso();
	_POST_FUN void OnBucklingLoad();
	_POST_FUN void ShowPMMCurve(CString sPath, int m_iPt2, vector<int> &m_vStructID1D, vector<int> &m_vStructID2D);
	_POST_FUN bool ShowReportDlg(CReportE &report);
	_POST_FUN void GenerateReport(CReportE &report);
	_POST_FUN void ShowStressRatioGraph();
	_POST_FUN bool OnDefineperformance();
	_POST_FUN bool OnOpenSAUSGAPI();
	_POST_FUN void ShowShearforcecurveCmp(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowMomentcurveCmp(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowEnergyCurveCmp(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowPMMDlg();
	_POST_FUN void ShowMultiModelShearforcecurveCmp(LOADCASETYPE iType = EARTHQUAKE);
	_POST_FUN void ShowMultiModelMomentcurveCmp(LOADCASETYPE iType = EARTHQUAKE);
}
