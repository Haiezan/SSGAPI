#pragma once

#include "HeadDefine.h"
#include <afxtempl.h>
#include "SSGAppInterface.h"

//输出用于计算层间位移的柱子层高程上结点信息，包括柱子、边缘构件，不包括斜撑
//文件格式：
//层数  柱子数
//层号  柱子1结点号(从1开始)  柱子2结点号(从1开始)  ...
extern "C" _SSG_FEADLL void WriteColumnInfo(const CString & fname, int Sty_Col_Num, const int* Sty_Col_id, const int* Sty_Col_Type, BOOL bUser = FALSE, float fAngle = 0); // bUser 和float 用于自定义
extern "C" _SSG_FEADLL void SetDriftElm();

class CSSGFeaInterface/* : public CCmdTarget*/
{
public:
	virtual void InitialApp(ISSGApp* theExeApp) = 0;
	virtual void SetMultiGPU(bool bMultiGPU) = 0;
	virtual int Run(BOOL bShutdown = FALSE) = 0;
	virtual void SetISORun(CArray<int, int>& runCase) = 0;//减隔震处理非隔震非减震模型计算
	virtual ~CSSGFeaInterface() = 0;
public:
	BOOL m_bShutdown;  //析构时关机
	BOOL m_bSilence;
	BOOL m_bExpShape;
	BOOL m_bSecondCalIsoBeta;
	BOOL m_bSecondCalElastic;
	RUN_CASE iRunCase;

	CLoadCollection m_cLoad;
	CArray<int, int> m_aRunCase;//2016.1.28
};

extern "C" _SSG_FEADLL CSSGFeaInterface* GetFeaInterface();