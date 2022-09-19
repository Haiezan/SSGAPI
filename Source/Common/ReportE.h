#pragma once
#include "Post.h"
#include "B2c.h"
#include "ADrawCurve.h"
#include "IGenerateText.h"
#include "ReportEFunc.h"
#include "MyTreeCtrl.h"
#include "StructFunc.h"
#include "HeadDefine.h"

enum REPORT_TYPE
{
	REPORTTYPE_SAUSAGE = 0,
	REPORTTYPE_CHECK = 1,
	REPORTTYPE_DOG = 4,
	REPORTTYPE_STEEL = 5,
	REPORTTYPE_PI = 6,
	REPORTTYPE_PD = 7,
	REPORTTYPE_RESI = 8,
};

//iReportType == 0  SAUSG 报告
//iReportType == 1  Design 报告
//iReportType == 2  减震系数 报告
//iReportType == 3  附加阻尼比 报告
//iReportType == 4  DOG 报告
//iReportType == 5  隔震报告
//iReportType == 6  减震报告
//iReportType == 7  钢结构报告

enum SSGREPORT
{
	REPORT_ALL=0,
	REPORT_MODELINFO,
	REPORT_MODEL_PIC,
	REPORT_MODEL_MATERIAL,
	REPORT_MODEL_SECTION,
	REPORT_MODALRESULT,
	REPORT_CASEINFO,
	REPORT_SHEAR,
	REPORT_SHEAR_TIME,
	REPORT_SHEAR_ENVELOP,
	REPORT_MOMENT_ENVELOP,
	REPORT_DRIFT,
	REPORT_DRIFT_ENVELOP,
	REPORT_DRIFT_TIME,
	REPORT_DRIFT_EEP,
	REPORT_HYS,
	REPORT_ENERGY,
	REPORT_TERMCURVE,
	REPORT_DAMAGE,
	REPORT_DAMAGE_BEAM,
	REPORT_DAMAGE_COLUMN,
	REPORT_DAMAGE_WALL,
	REPORT_DAMAGE_SLAB,
	REPORT_DAMAGE_CROSS,
	REPORT_DAMAGE_PROCESS,
	REPORT_PLASTICSTRAIN,
	REPORT_PERFORM,
	REPORT_PERFORM_BEAM,
	REPORT_PERFORM_COLUMN,
	REPORT_PERFORM_WALL,
	REPORT_PERFORM_SLAB,
	REPORT_PERFORM_CROSS,
	REPORT_PERFORM_COUNT,
	REPORT_SHEARSECCHECK,
	REPORT_PULLCHECK,
	//隔震报告增加begin：
	REPORT_ISOBEGIN,
	REPORT_ISOLAYERBAS,
	REPORT_ISOLAYERDES,
	REPORT_DMPDEVICES,
	REPORT_DIVISION,
	REPORT_DIVISION_LCS,
	REPORT_DIVISION_SHEAR,
	REPORT_DIVISION_BETA,
	REPORT_DIVISION_DRIFT,
	REPORT_DIRECT,
	REPORT_DIRECT_LCS,
	REPORT_DIRECT_SHEAR,
	REPORT_DIRECT_DRIFT,
	REPORT_DIRECT_ENERGY,
	REPORT_DIRECT_DISPLACEMENT,
	REPORT_DIRECT_STRESS,
	REPORT_BIG,
	REPORT_HINGE,
	//隔震报告end
	//减震报告增加begin：
	REPORT_DMPBEGIN,
	REPORT_DMPBAS,
	REPORT_MID_DMPRATIO,
	REPORT_DMPRATIO,
	REPORT_ELASTIC,
	REPORT_ELASTIC_LCS,
	REPORT_ELASTIC_SHEAR,
	REPORT_ELASTIC_DMPRATIO,
	REPORT_ELASTIC_DRIFT,
	REPORT_ELASTIC_ENERGY,
	REPORT_DMPCHECK,
	//减震报告end
	REPORT_BUCKLINGRESULT,
	REPORT_IMPERFECTIONS,
	REPORT_DISPLACEMENT,
	REPORT_STRESS,
};

class _POST_DLLIMPEXP CReportE
{
public:
	CReportE();
	~CReportE();

public:
	bool Init();
	CString OutputReportWord(int iReportType);

	void GetDispTopPoint();

	void OutputSausageChkContents();
	void OutputBetaContents();
	void OutputDamperRatioContents();
	void OutputContentsSausage();

	void OutputSteelStressRatio();

	void OutputContentsSDog();

	bool OutputModelInfomation();
	bool OutputModelInfomationCheck();

	void OutputEarthquake(CLoadCollection lc,int iProbility=-1);//-1全输出
	void OutputAnalysisCase(CLoadCollection lc,int iProbility=-1);//-1全输出
	bool OutputModalResult(bool bWriteTitlOut=false);

	void PrepareShearResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1全输出
	void OutputShearChart();
	void OutputShearTable(CString sLoad=L"");

	void PrepareDispResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1全输出
	void OutputDispChart();
	void OutputDispTable(CString sLoad=L"");

	void OutputEnergyChart(CLoadCollection lc,int iProbility=-1);
	void OutputPerformanceStatistics(bool bSpandrelOnly=false);
	void OutputShearHysteris();
	void OutputRealtimeResult();
	
	void OutputDamageChart();
	void OutputPerformChart();
	void OutputHingeChart();
	void OutputPlasticStrainChart();
	void OutputShearCheck();
	void OutputDamageProgress();

	void OutputDamagePerformance();

	void OutputReductionFactor();
	void OutputReductionTable(STRUCT_TYPE iType,CStruFieldOneComponent* pStruFieldSet);
	
	void OutputStiffCoefTxt(int iType,CStruFieldOneComponent* pStruFieldSet);
	BOOL OutputIsolatorBeta(float &fMaxRatioAll);
	BOOL OutputDamperRatio();
	void OutputDefenseCoef();
//隔震报告专用函数begin
	void OutputContentsSISO();
	void OutputSSGISOTable(int iChk);//输出支座验算表格
	void OutputISOBasicRequirement();//输出隔震基本要求
	void OutputISODesignRequirement();//输出隔震设计要求：隔震层验算支座静力验算
	void OutputISOModalResult();//输出隔震非隔震模型周期对比
	void PrepareISOShearResult(CLoadCollection  &loads,bool bBothDir=false);
	void OutputISOShearChart(bool bBothDir=false);//输出水平向减震系数求解过程：楼层剪力及倾覆力矩
	void OutputISOBetaContents(bool bBetaReport=true,bool bBothDir=false);//输出水平向减震系数求解过程
	// 隔震报告专用函数end

	//减震报告专用函数begin
	void PrepareShearResultDES(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1全输出
	void OutputContentsSDMP();
	void OutputSDMPTable();//输出消能器验算表格
	void OutputDMPBasicRequirement();//输出减震基本要求
	void OutputDMPDampingRatio(CLoadCollection lc,int iProbility=-1);//输出等效刚度及等效阻尼比
	void OutputSectProperty();
	//void OutputISOModalResult();//输出隔震非隔震模型周期对比
	// 减震报告专用函数end
	bool OutputCombination(CLoadCollection &lc);

	void OutputContentsSSteel();//钢结构报告
	bool OutputBucklingResult();
	bool OutputInitialImperfections();
	bool OutputDisplacement(CLoadCollection &lc);
	bool OutputStress(CLoadCollection &lc);
	bool OutputStructStress(CLoadCollection &lc);
	void OutputDamagePerformance(CLoadCollection &lc,const vector<bool> cCaseSel);
	bool GetLoadCaseByType(CLoadCollection &lc,vector<bool> &cCaseSel,int iType);
	void OutputAnalysisCaseByType(CLoadCollection lc,int iType);
	void PrepareShearResultByType(CLoadCollection lc,int iType);
	bool GetWindDirect(CLoadCase *lc);//true Main

	vector<struct TreeData> m_vSSGOutput;
	BOOL bOutput(int iOutput);
	void WriteWave();
//
//	// 绘制
	bool DrawCurve_Wave(CString sPathName,float* fValue,int nCount[3]);
//	// X方向为固定step刻度
//	bool DrawCurve_X(CString sPathName,float fXStep,float* fValue,int nCount[3]);		// 数据分三个段，每段长度
//	bool DrawCurve_Elas(CString sPathName,float* fcd1,float* fcd2,int nCount[2],BOOL bType);
//	// 为任意X轴刻度，也就说fXValue和fValue是一一对应的
//	bool DrawCurve(CString sPathName,FLOAT2* fValue,int *nCntValue,int nCount);		// 数据分三个段，每段长度
//	// 绘制楼层相关的
//	bool DrawStorey(CString sPathName,int nStorey,int nStart,float* fValue,int nCount,CString* s,CString sXName,int itype=0);

	BOOL SavePicture(CString& sPathName,CDrawSetting& dSetting,float* fX,float* fY,int* nCount,CString* sSeriesName,int* nStart,int nCurve);
	BOOL SavePicture(CString& sPathName,CDrawSetting& dSetting,CACurveData* pData,int nCurve);
//	float Coord2ClientX(float x,float OrgX,float fXScale);
//	float Coord2ClientY(float y,float OrgY,float fYScale);
	void GetStringNodes(CString sLine);//,vector<int>& vNodeIDs);

//
//	// 下面是绘图部分
//	void DrawAxis(CDC &dc,CRect& rc,float fMinX,float fMaxX,float fMinY,float fMaxY,float fRatioX,float fRatioY);
//	void Draw(CDC& MemDC,CRect& rc,int nCurve,int nCount,float* fX,float* fY,float fMinX,float fMinY,float fRatX,float fRatY);
//	float ScaleAxis(float init_min_value,float init_max_value,int init_point_num, 
//		float &axis_min_value,float &axis_max_value, int &axis_point_num,int &iex);		// 要实现
//
//	CPoint GetClientCoor(CRect rc,float x,float y,float fMinX,float fMinY,float fRatioX,float fRatioY);  //物理坐标转换为绘图坐标;
//
//	COLORREF m_CColor[6];
//
//
//
//private:
//	//CReportEDlg* m_pSetDlg;
//

//	// 剪力8个分量：柱子Vx\斜撑Vx\剪力墙Vx\楼层剪力Vx\柱子Vy\斜撑Vy\剪力墙Vy\楼层剪力Vy
//	map<int,vFlt8>  m_mapShear;		// 排序是一个分量结束后再下一个分量
//	//位移6个分量：x层间位移，y层间位移，x层间位移角，y层间位移角，x楼层位移，y楼层位移
//	// 基底时程剪力
	CWord m_word;
	CString m_edtNode;
	CString m_edtTime;

	vector<CString> m_vecCase;
	vector<multimap<CString, CString>> m_vecProgress;

	float m_fTotalWeight;
	vector<vector<float>> m_vBaseShear;	//各工况基底剪力数据：  { 柱剪力Vx  楼层剪力Vx 柱剪力Vy  楼层剪力Vy }
	vector<vector<float>> m_vDispX;		//各工况位移数据：  { 最大顶点位移、最大层间位移角、位移角对应层号 }
	vector<vector<float>> m_vDispY;		//各工况位移数据：  { 最大顶点位移、最大层间位移角、位移角对应层号 }

	//vector<bool> m_vCaseX;	//临时的，要删除的

	vector<bool> m_vCaseSelected;	//case selected for output  大震弹塑性
	vector<bool> m_vCaseSelectedStatic;	//case selected for output 静力非线性
	vector<bool> m_vCaseSelectedElastic;	//case selected for output 等效弹性
	vector<bool> m_vCaseSelectedDirect;	//case selected for output 直接分析设计
	vector<bool> m_vHysCurveStorySelected;
	vector<bool> m_vSlabStorySelected;
	vector<bool> m_vShearChkStorySelected;
	BOOL bModelInfo;
	BOOL bModal;
	BOOL bCaseInfo;
	BOOL bShear;
	BOOL bDrift;
	BOOL bHysteretic;
	BOOL bEnergy;
	BOOL bTermCurve;
	BOOL bDamage;
	BOOL bDamageProcess;
	BOOL bPerformance;
	BOOL bPlasticStrain;
	BOOL bShearCheck;

	BOOL bWallBeamCoef;
	BOOL bSecondDefense;	
	BOOL bDesignStiffCoef;
	BOOL bDamper;
	BOOL bIsolator;	
	
	BOOL bStress;
	BOOL bDisplacement;
	

	int m_iResultIndex;
	int indexTitle2;


//计算工具
	sd::IGenerateText *m_pGenerateDocx;

	sd::CExhibition *m_pExhibition;


	//sd::IGenerateText *m_pGenerate;

//SAUSAGE-Check 控制项
	int m_iValueCombi;
	float m_fMinValue;
	float m_fMaxValue;
	float m_f2dfMinValue;
	float m_f2dfMaxValue;

	bool m_batchReport;	//批处理运行
private:

	int m_iReportType;
	PPAGE_FORMAT m_pPageFormat;			//页面格式
	PPARAGRAPH_FORMAT m_pParaghFormat;  //段落格式
	PTEXT_FORMAT m_pTextFormat;			//文本格式
	PGRAPHIC_FORMAT m_pPicFormat;		//普通图片格式
	PGRAPHIC_EMBED_FORMAT m_pPicEmbedFormat; //嵌入型图片格式
	PTABLE_FORMAT m_pTableFormat;		//表格格式
	PCELL_FORMAT m_pCellFormat;			//单元格格式
	PCHART_FORMAT m_pChartFormat;		//图表格式(柱状图等)

	vector<int> m_vElas;
	vector<int> m_vPlas;
	vector<pair<int,int>> m_vecElasPlas;

	vector<wstring> m_vArrayShear;		//剪力表格
	vector<wstring> m_vArrayDisp[2];	//位移表格, 0-总体， 1-自定义
	vector<wstring> m_vArrayModal;		//模态表格
	vector<wstring> m_vArrayCase;

	vector<string> m_vXDispName[2];
	vector<string> m_vYDispName[2];

	vector<vector<float>> m_vXDispStorySeries[2];	
	vector<vector<float>> m_vYDispStorySeries[2];

	vector<vector<float>> m_vXDriftSeries[2];		//层间位移角
	vector<vector<float>> m_vYDriftSeries[2];

	vector<vector<float>> m_vXDispSeries[2];		//楼层位移
	vector<vector<float>> m_vYDispSeries[2];


	vector<string> m_vXDispTopName;
	vector<string> m_vYDispTopNames;

	vector<vector<float>> m_vXDispTopTimeSeries;
	vector<vector<float>> m_vYDispTopTimeSeries;

	vector<vector<float>> m_vXDispTopSeriesNodeDisp;
	vector<vector<float>> m_vYDispTopSeriesNodeDisp;


	//工况,楼层,分量 
	vector<string> m_vXShearName;							//X向 标签
	vector<string> m_vYShearName;							//Y向 标签
	vector<vector<float>> m_vXShearTimeSeries;
	vector<vector<float>> m_vYShearTimeSeries;
	vector<vector<float>> m_vXShearBaseshearSeries;			//X 基底剪力时程
	vector<vector<float>> m_vYShearBaseshearSeries;			//Y 基底剪力时程

	vector<string> m_vXShearStoryName;						//X向 标签
	vector<string> m_vYShearStoryName;						//Y向 标签

	//楼层剪力
	vector<vector<float>> m_vXStoryShearIDSeries;			//X向为主 楼层编号
	vector<vector<float>> m_vYStoryShearIDSeries;			//Y向为主 楼层编号

	vector<vector<float>> m_vXStoryShearForceSeries;		//X向层剪力
	vector<vector<float>> m_vYStoryShearForceSeries;		//Y向层剪力

	vector<vector<float>> m_vShearXStoryMomentSeries;		//X向倾覆力矩
	vector<vector<float>> m_vShearYStoryMomentSeries;		//Y向倾覆力矩


	vector<int> m_vNodeIDs;
	vector<int> m_vTopPoint;
};