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
	REPORTTYPE_PI = 5,
	REPORTTYPE_PD = 6,
	REPORTTYPE_STEEL = 7,
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
	REPORT_EARTHQUAKEINFO,
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
	REPORT_ISOCHECK,
	REPORT_DIVISION,
	REPORT_DIVISION_LCS,
	REPORT_DIVISION_EQINFO,
	REPORT_DIVISION_SHEAR,
	REPORT_DIVISION_BETA,
	REPORT_DIVISION_DRIFT,
	REPORT_DIRECT,
	REPORT_DIRECT_LCS,
	REPORT_DIRECT_EQINFO,
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
	REPORT_ELASTIC_EQINFO,
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
	REPORT_STORYACC,
	//加固报告
	REPORT_REINFORED_MODELINFO,
	REPORT_REINFORED_PERFORMANCE,
	REPORT_METERIAL_USED,


};


struct WAVEDATA
{
	CString fame;  //文件名
	CString sCaseName;  //工况名
	CString sWaveName;  //天然波 人工波
	CString sComboName;  //组合名
	int iEarthQuakeProbility; //qiaobaojuan 2016.12.19
	int iWaveLibIndex; //乔保娟 2015.6.11
	int iWaveLib;	//0----SSG地震波库， 1-----用户自定义波
	float fAmp; //工况中调幅后的峰值加速度 20230309贾苏添加
	vector<float> vTime;
	vector<float> vAcc;

	//工况序号及反应谱基底剪力 //20231229 涂天驰 添加

	int iWaveCaseX = -1;//工况X主向对应的分析工况序号
	int iWaveCaseY = -1;//工况Y主向对应的分析工况序号
	int iWaveElasticCaseX = -1;//工况X主向对应的弹性工况分析工况序号
	int iWaveElasticCaseY = -1;//工况Y主向对应的弹性工况分析工况序号
	int iWaveType = 0;//0为天然波，1为人工波
	int iCrtCons = 1;//0为弹性，1为弹塑性
	float ResSpecBaseShearX = 0.0f;//X反应谱基底剪力
	float RatioX = 0.0f;
	float ResSpecBaseShearY = 0.0f;//Y反应谱基底剪力
	float RatioY = 0.0f;
	float ResSpecBaseShearXNonISO = 0.0f;//非隔震模型X反应谱基底剪力
	float RatioXNonISO = 0.0f;
	float ResSpecBaseShearYNonISO = 0.0f;//非隔震模型Y反应谱基底剪力
	float RatioYNonISO = 0.0f;

	float fDt;
	float fTimeInterval;//20241212 涂天驰

	float fStartComputeTime;
	float fEndComputeTime;

	void PutData(CDataSequence2* pData2)
	{
		for (int i = 0; i < pData2->nPoints; i++) {
			vTime.push_back(pData2->pData[i].t);
			vAcc.push_back(pData2->pData[i].v);
		}
	}

	//峰值加速度
	float fMaxAcc;

	void GetMax()
	{
		float fMin = 1.0e6;
		float fMax = -1.0e6;
		for (int i = 0; i < vAcc.size(); i++) {
			if (vAcc[i] < fMin) fMin = vAcc[i];
			if (vAcc[i] > fMax) fMax = vAcc[i];
		}
		fMax = max(fabs(fMin), fabs(fMax));

		fMaxAcc = fMax;
	}

	//Trim
	void TrimComma() {
		fame.Replace(L" ", L"_");
		fame.Replace(L",", L"");
		fame.Replace(L"，", L"");
		//		fame.Replace(L"	",L"_");
	}
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
	void OutputEEPShearTable(CString sLoad = L"");
	void OutputDamperTable(CString sLoad = L"");
	void OutputRespecShearTable(CLoadCollection lc, int iProbility=-1);//-1全输出

	void PrepareDispResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1全输出
	void OutputDispChart();
	void OutputDispTable(CString sLoad=L"");

	void PrepareStoryAccResult(CLoadCollection lc, int iProbility=-1);
	void OutputStoryAccChart();//楼面质心加速度图 20230117 涂天驰
	void OutputStoryAccTable();//楼面质心统计表 20230117 涂天驰

	void PrepareStoryMaxAccResult(CLoadCollection lc,int iProbility=-1);
	void OutputStoryMaxAccTable(); //楼层加速度统计表 20230117 涂天驰
	void OutputStoryMaxAccChart();//楼层加速度曲线表 20230117 涂天驰

	void OutputEnergyChartDEP(CLoadCollection lc, int iProbility=-1);
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
	void OutputConclusion();

	void OutputPerformGradePara();
	void OutputDamagePerformance();

	void OutputReductionFactor();
	void OutputReductionTable(STRUCT_TYPE iType, CStruFieldOneStepOneBlock* pStruFieldSet);
	
	void OutputStiffCoefTxt(int iType, CStruFieldOneStepOneBlock* pStruFieldSet);
	BOOL OutputIsolatorBeta(float &fMaxRatioAll);
	BOOL OutputDamperRatio();
	void OutputDefenseCoef();

	int GetKeyStory();//获取模型底部加强层 20241129 涂天驰
	BOOL IsVipTypeDefined();//判断是否有自定义重要性等级 20241129 涂天驰
	BOOL IsVipTypeMemberExist(int iViptype);//判断该重要性等级的构件是否存在 20241129 涂天驰
	COLORREF GetTargetLevelColor(int iTarget);//获取性能目标的颜色 20241129 涂天驰

//隔震报告专用函数begin
	void OutputIsolatorProperty();//输出隔震支座力学参数
	void OutputContentsSISO();
	void OutputSSGISOTable(int iChk, int ic);//输出支座验算表格 ic=0-包络、1-平均
	void OutputISOESFTable();//输出隔震弹性恢复力验算表格
	void OutputISOMomentTable();//输出隔震层抗倾覆验算表格
	void OutputISOBasicRequirement();//输出隔震基本要求
	void OutputISODesignRequirement();//输出隔震设计要求：隔震层验算支座静力验算
	void OutputISOModalResult();//输出隔震非隔震模型周期对比
	void PrepareISOShearResult(CLoadCollection& loads, bool bBothDir = false);
	void PrepareISOShearReportResult(CLoadCollection& loads, bool bBothDir = false);
	void PrepareISODispResult(CLoadCollection& loads);
	void OutputISODispTable();
	void OutputISODispChart();
	void OutputISOShearChart(bool bBothDir = false);//输出水平向减震系数求解过程：楼层剪力及倾覆力矩
	void OutputISOShearReportChart(bool bBothDir = false);//20240311 涂天驰
	void OutputISOBetaContents(bool bBetaReport = true, bool bBothDir = false);//输出水平向减震系数求解过程
	void OutputISOBetaReportContents(bool bBothDir = false);//20240311 涂天驰
	void OutputConclusionISO();
	// 隔震报告专用函数end

	//减震报告专用函数begin
	void PrepareShearResultDES(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1全输出
	void OutputContentsSDMP();
	void OutputSDMPTable();//输出消能器验算表格
	void OutputSDMPChart(CLoadCollection lc, int iProbility=-1);//输出消能器滞回曲线 20240118 涂天驰
	void OutputDMPBasicRequirement();//输出减震基本要求
	void OutputDMPDampingRatio(CLoadCollection lc,int iProbility=-1);//输出等效阻尼比 20240116 涂天驰
	void OutputDMPDampingRatioCode(CLoadCollection lc, int iProbility=-1);//输出规范法计算等效阻尼比 20240116 涂天驰
	void OutputSectProperty();
	void OutputSectNums();//输出组阻尼器布置统计表 20240116 涂天驰
	void OutputConclusionDMP();
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
	

	// 加固报告begin
	void OutputContentsReinForced();
	void OutputReinForcedInformation();
	bool OutputReinForcedModalResult(bool bWriteTitlOut = false); // 周期
	void PrepareShearResultReinForced(CLoadCollection lc, bool bBothDir, int iProbility = -1);//-1全输出 剪力
	void PrepareDispResultReinForced(CLoadCollection lc, bool bBothDir, int iProbility = -1);//-1全输出 位移
	void OutputEnergyChartReinForced(CLoadCollection lc, int iProbility = -1); // 能量图
	void OutputDamagePerformanceReinForced(); // 性能指标
	void OutputPerformanceStatisticsReinForced(bool bSpandrelOnly = false); // 性能统计
	void InterlayerDisplaycementAngleIndicater(); // 层间位移角指标
	void TheAmountOfMeterialUsed(); // 加固后材料用量统计
	CString GetFilePath_Temp(const CString& sExt, const CString& sLoadCase = L"", const CString& sGroupName = L"");
	CString GetPrjName_Temp(void);
	CString GetPrjPath_Temp(void);
	CString GetCaseStaticPath_Temp(const CString& sLoadCase); //得到静力工况根目录，例："d:\exam_path\StaticResult\"
	CString GetEarthQuakePath_Temp(const CString& sLoadCase, bool m_bEnvCase = false); //得到任意工况子目录，例："d:\exam_path\EarthQuakeResult\case_n\"
	CString GetEarthQuakeRoot_Temp(bool m_bEnvCase=false); //得到地震工况根目录，例："d:\exam_path\EarthQuakeResult\"
	CSSGData theData2;
	BOOL bNotReinForcedSSGModel;


	// 多模型方案报告比较
	void OutputContentsMultiModel();
	bool OutputMultiModelModalResult(bool bWriteTitlOut = false); // 周期
	void PrepareShearResultMultiModel(const CSSGData* pMultiplyData, CLoadCollection lc, bool bBothDir, CString sSchemeName, int iProbility = -1);//-1全输出 剪力
	void EnergyCalcu(const CSSGData* pMultiplyData, const CLoadCase* pLoad, float* pEnergy, BOOL m_bAddStaticEnergy=TRUE);
	void EnergyCalcuMultiModel(const CSSGData* pMultiplyData, CLoadCollection* pLC);
	void OutputEnergyCalcuTableMultiModel();
	void OutputPerformanceStatisticsMultiModel(CSSGData* pMultiplyData, int iScheme, bool bSpandrelOnly = false);
	void OutputPerformanceStatisticsMultiModelChart();
	void PrepareDispResultMultiModel(const CSSGData* pMultiplyData,CLoadCollection lc, bool bBothDir, CString sSchemeName, int iProbility = -1);//-1全输出
	void PrepareDispLimitResultMultiModel();
	void OutputMultiModelConclusion();
	void OutputShearTableMultiModel(CString sLoad = L"");
	void OutputDispChartMultiModelAccordingToCase();
	void OutputShearChartMultiModelAccordingToCase();
	void GetMultiplyDispTopPoint(const CSSGData* pMultiplyData);

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

	vector<WAVEDATA> GetWaveType(CLoadCollection lc, int iProbility);//工况天然波、人工波类型及统计 20231229 涂天驰
	vector<WAVEDATA>m_vWaveSeries;
	void GetWaveNums(vector<WAVEDATA> vWaveSeries);
	int m_nArtiWaves;
	int m_nNatureWaves;
	void ReadPeriod(CString fname, vector<float>& vPeriod);//读取模型周期 20241210 涂天驰
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

	vector<vector<float>> m_vAccX;		//各工况位移数据：  { 最大楼层加速度、对应层号 }
	vector<vector<float>> m_vAccY;		//各工况位移数据：  { 最大楼层加速度、对应层号 }


	//vector<bool> m_vCaseX;	//临时的，要删除的

	vector<bool> m_vCaseSelected;	//case selected for output  大震弹塑性
	vector<bool> m_vCaseSelectedStatic;	//case selected for output 静力非线性
	vector<bool> m_vCaseSelectedElastic;	//case selected for output 等效弹性
	vector<bool> m_vCaseSelectedDirect;	//case selected for output 直接分析设计
	vector<bool> m_vHysCurveStorySelected;
	vector<bool> m_vSlabStorySelected;
	vector<bool> m_vCaseDamageSelected;
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
	BOOL bUserView;
	BOOL bShowWaveName;
	

	int m_iResultIndex;
	int indexTitle2;
	int m_iCaseSelected;
	int m_iIndexSelected;


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
	vector<wstring> m_vArrayRespecShear;		//反应谱剪力表格 20240102 涂天驰
	vector<wstring> m_vArrayElasticShear;		//弹塑性基底剪力对比表格
	vector<wstring> m_vArrayDisp[2];	//位移表格, 0-总体， 1-自定义
	vector<wstring> m_vArrayModal;		//模态表格
	vector<wstring> m_vArrayCase;
	vector<wstring> m_vArrayDamper; //结构附加阻尼比表格 20240104 涂天驰
	vector<wstring> m_vArraySpecEarthQuake; //地震波与规范反应谱主要周期点差值 20240109 涂天驰
	vector<wstring> m_vArraySpecAverage; //地震平均波与规范反应谱主要周期点差值 20240109 涂天驰
	vector<wstring> m_vArrayAcc;// 楼层加速度表格 20240117 涂天驰
	vector<wstring> m_vArrayMassCenter;// 楼面质心加速度表格 20240117 涂天驰

	vector<wstring> m_vArrayEnergy; //应变能表格 20240116 涂天驰
	vector<wstring> m_vArrayDamperEnergy; //阻尼器耗能表格 20240116 涂天驰
	vector<wstring> m_vArraySecNumbers; //阻尼器数量表格 20240116 涂天驰

	vector<wstring> m_vArrayPerformance; //构件性能汇总表 20240204 涂天驰
	vector<wstring> m_vArrayPerformGrade; //性能水平表格 20240205 涂天驰

	vector<float>m_vDispDamperRatioX;//20240116 涂天驰
	vector<float>m_vVeloDamperRatioX;//20240116 涂天驰
	vector<float>m_vTotalAddDamperRatioX;//20240116 涂天驰
	vector<float>m_vDispDamperRatioY;//20240116 涂天驰
	vector<float>m_vVeloDamperRatioY;//20240116 涂天驰
	vector<float>m_vTotalAddDamperRatioY;//20240116 涂天驰

	vector<string> m_vXDispName[2];		//楼层位移
	vector<string> m_vYDispName[2];

	vector<vector<string>> m_vXDispNameTower;//20240108 涂天驰
	vector<vector<string>> m_vYDispNameTower;//20240108 涂天驰

	vector<vector<float>> m_vXDispStorySeries[2];	
	vector<vector<float>> m_vYDispStorySeries[2];

	vector<vector<vector<float>>> m_vXDispStorySeriesTower;			//20240108 涂天驰
	vector<vector<vector<float>>> m_vYDispStorySeriesTower;			//20240108 涂天驰

	vector<vector<float>> m_vXDispSeries[2];
	vector<vector<float>> m_vYDispSeries[2];

	vector<vector<vector<float>>>  m_vXDispSeriesTower;			//20240108 涂天驰
	vector<vector<vector<float>>>  m_vYDispSeriesTower;			//20240108 涂天驰



	//楼层加速度 20240117 涂天驰

	vector<string> m_vXAccName;
	vector<string> m_vYAccName;

	vector<vector<string>> m_vXAccNameTower;
	vector<vector<string>> m_vYAccNameTower;

	vector<vector<float>> m_vXAccStorySeries;
	vector<vector<float>> m_vYAccStorySeries;

	vector<vector<vector<float>>> m_vXAccStorySeriesTower;
	vector<vector<vector<float>>> m_vYAccStorySeriesTower;

	vector<vector<float>> m_vXAccSeries;
	vector<vector<float>> m_vYAccSeries;

	vector<vector<vector<float>>>  m_vXAccSeriesTower;
	vector<vector<vector<float>>>  m_vYAccSeriesTower;

	//楼面质心加速度 20240117 涂天驰
	vector<string> m_vXAcceName;
	vector<string> m_vYAcceName;

	vector<vector<float>> m_vXAcceStorySeries;
	vector<vector<float>> m_vYAcceStorySeries;

	vector<vector<float>> m_vXAcceSeries;
	vector<vector<float>> m_vYAcceSeries;


	vector<string> m_vXDriftName[2];	//层间位移角
	vector<string> m_vYDriftName[2];

	vector<vector<string>> m_vXDriftNameTower;//20240108 涂天驰
	vector<vector<string>> m_vYDriftNameTower;//20240108 涂天驰

	vector<vector<float>> m_vXDriftStorySeries[2];
	vector<vector<float>> m_vYDriftStorySeries[2];

	vector<vector<vector<float>>> m_vXDriftStorySeriesTower;			//20240108 涂天驰
	vector<vector<vector<float>>> m_vYDriftStorySeriesTower;			//20240108 涂天驰

	vector<vector<float>> m_vXDriftSeries[2];
	vector<vector<float>> m_vYDriftSeries[2];

	vector<vector<vector<float>>>  m_vXDriftSeriesTower;			//20240108 涂天驰
	vector<vector<vector<float>>>  m_vYDriftSeriesTower;			//20240108 涂天驰

	BOOL bDriftMeetLimit;
	BOOL bAccMeetLimit;
	BOOL bAcceMeetLimit;

	vector<string> m_vXDispTopName;
	vector<string> m_vYDispTopNames;

	vector<vector<float>> m_vXDispTopTimeSeries;
	vector<vector<float>> m_vYDispTopTimeSeries;

	vector<vector<float>> m_vXDispTopSeriesNodeDisp;
	vector<vector<float>> m_vYDispTopSeriesNodeDisp;


	//工况,楼层,分量 
	vector<string> m_vXShearName;							//X向 标签
	vector<string> m_vYShearName;							//Y向 标签
	vector<string> m_vXShearNameNoIso;					//20240130 涂天驰
	vector<string> m_vYShearNameNoIso;					//20240130 涂天驰
	vector<vector<float>> m_vXShearTimeSeries;
	vector<vector<float>> m_vYShearTimeSeries;
	vector<vector<float>> m_vXShearBaseshearSeries;			//X 基底剪力时程
	vector<vector<float>> m_vYShearBaseshearSeries;			//Y 基底剪力时程

	vector<string> m_vXShearStoryName;						//X向 标签
	vector<string> m_vYShearStoryName;						//Y向 标签
	vector<vector<string>> m_vXShearStoryNameTower;			//20240105 涂天驰
	vector<vector<string>> m_vYShearStoryNameTower;			//20240105 涂天驰
	vector<string> m_vXShearStoryNameNoIso;					//20240130 涂天驰
	vector<string> m_vYShearStoryNameNoIso;					//20240130 涂天驰

	//楼层剪力
	vector<vector<float>> m_vXStoryShearIDSeries;			//X向为主 楼层编号
	vector<vector<float>> m_vYStoryShearIDSeries;			//Y向为主 楼层编号
	vector<vector<float>> m_vXStoryShearIDSeriesNoIso;			//20240130 涂天驰
	vector<vector<float>> m_vYStoryShearIDSeriesNoIso;			//20240130 涂天驰
	vector<vector<vector<float>>>m_vXStoryShearIDSeriesTower;			//20240105 涂天驰
	vector<vector<vector<float>>> m_vYStoryShearIDSeriesTower;			//20240105 涂天驰


	vector<vector<float>> m_vXStoryShearForceSeries;		//X向层剪力
	vector<vector<float>> m_vYStoryShearForceSeries;		//Y向层剪力
	vector<vector<float>> m_vXStoryShearForceSeriesNoIso;		//20240130 涂天驰
	vector<vector<float>> m_vYStoryShearForceSeriesNoIso;		//20240130 涂天驰
	vector<vector<vector<float>>> m_vXStoryShearForceSeriesTower;		//20240105 涂天驰
	vector<vector<vector<float>>> m_vYStoryShearForceSeriesTower;		//20240105 涂天驰

	vector<vector<float>> m_vShearXStoryMomentSeries;		//X向倾覆力矩
	vector<vector<float>> m_vShearYStoryMomentSeries;		//Y向倾覆力矩
	vector<vector<float>> m_vShearXStoryMomentSeriesNoIso;		//X向倾覆力矩
	vector<vector<float>> m_vShearYStoryMomentSeriesNoIso;		//Y向倾覆力矩
	vector<vector<vector<float>>> m_vShearXStoryMomentSeriesTower;		//20240105 涂天驰
	vector<vector<vector<float>>> m_vShearYStoryMomentSeriesTower;		//20240105 涂天驰

	float m_fShearRatioAveX;//X向剪重比平均值
	float m_fShearRatioAveY;//Y向剪重比平均值

	vector<int> m_vNodeIDs;
	vector<int> m_vTopPoint;

	//反应谱基底剪力 20240102 涂天驰
	float m_fRespecBaseShearX ;//反应谱X向基底剪力
	float m_fRespecBaseShearY ;//反应谱Y向基底剪力
	float m_fRespecBaseShearXNonISO;//非隔震模型反应谱X向基底剪力
	float m_fRespecBaseShearYNonISO;//非隔震模型反应谱Y向基底剪力


	float m_fDispXMax;//各地震波下最大X向层间位移角
	float m_fDispYMax;//各地震波下最大Y向层间位移角
	int m_fDispXMaxStory;//各地震波下最大X向层间位移角对应层号
	int m_fDispYMaxStory;//各地震波下最大Y向层间位移角对应层号

	float m_fAccXMax;//各地震波下最大X向楼层加速度
	float m_fAccYMax;//各地震波下最大Y向楼层加速度
	int m_fAccXMaxStory;//各地震波下最大X向楼层加速度对应层号
	int m_fAccYMaxStory;//各地震波下最大Y向楼层加速度对应层号

	float m_fAbsAccXMax;//各地震波下最大X向楼面质心加速度
	float m_fAbsAccYMax;//各地震波下最大Y向楼面质心加速度
	int m_fAbsAccXMaxStory;//各地震波下最大X向楼面质心加速度对应层号
	int m_fAbsAccYMaxStory;//各地震波下最大Y向楼面质心加速度对应层号

	//等效阻尼比
	vector<float>m_vStrainLast;//弹塑性阻尼比
	vector<float>m_vVeloDamperLast;//速度型阻尼器阻尼比
	vector<float>m_vDispDamperLast;//位移型阻尼器阻尼比
	vector<vector<float>>m_vEnergyRatio;//耗能占比

	int m_nSDMPNums;
	vector<CString>m_vSDMPName;//阻尼器名字及类型
	vector<float>m_vMaxDesignLoad;//阻尼器最大设计荷载
	vector<float>m_vMaxDesignDisp;//阻尼器最大设计位移
	vector<float>m_vMaxDesignVelo;//阻尼器最大设计速度
	vector<float>m_vDesignLoadCodeLimit;//阻尼器极限设计荷载
	vector<float>m_vDesignDispCodeLimit;//阻尼器极限设计位移
	vector<float>m_vDesignVeloCodeLimit;//阻尼器极限设计速度
	vector<BOOL>m_bMeetSDMPCheck;//阻尼器极限设计速度
	vector<BOOL>m_vISOCheck;//隔震支座正常使用状态验算
	float m_fUltimateDis;//隔震支座最大水平位移
	float m_fUltimateDisLimit;//隔震支座最大水平位移限值
	float m_fCmpStress;//隔震支座最大压应力
	float m_fCmpStressLimit;//隔震支座最大拉应力
	float m_fTenStress;//隔震支座最大拉应力
	float m_fTenStressLimit;//隔震支座最大拉应力限值
	float m_fTenStressPercent;//隔震支座受拉百分比
	BOOL m_bESFCheck;//隔震支座恢复力验算结果
	BOOL m_bMomentCheck;//隔震支座倾覆力矩验算结果
	BOOL m_bISISOChecked;
	BOOL m_bISESFChecked;
	BOOL m_bISMomentChecked;


	float m_fStrainLastEnv;//弹塑性阻尼比包络值
	float m_fVeloDamperLastEnv;//速度型阻尼器阻尼比包络值
	float m_fDispDamperLastEnv;//位移型阻尼器阻尼比包络值
	float m_fStrainLastAve;//弹塑性阻尼比平均值
	float m_fVeloDamperLastAve;//速度型阻尼器阻尼比平均值
	float m_fDispDamperLastAve;//位移型阻尼器阻尼比平均值
	float m_fTotalDamperAve;//总等效阻尼比平均值
	float m_fAddLastEnvX;//附加阻尼比包络值
	float m_fAddLastEnvY;//附加阻尼比包络值
	float m_fAddLastAveX;//附加阻尼比平均值
	float m_fAddLastAveY;//附加阻尼比平均值
	float m_fCodeAddLastEnvX;//规范算法附加阻尼比包络值
	float m_fCodeAddLastEnvY;//规范算法附加阻尼比包络值
	float m_fCodeAddLastAveX;//规范算法附加阻尼比平均值
	float m_fCodeAddLastAveY;//规范算法附加阻尼比平均值
	//vector<float>m_vKsi0;//初始阻尼比
	//vector<float>m_vKsi0c;//混凝土初始阻尼比
	//vector<float>m_vKsi0s;//钢初始阻尼比
	//vector<float>m_vKsiDamper;总等效阻尼比
	float m_fBetaX;//X向水平减震系数
	float m_fBetaY;//Y向水平减震系数

	////默认分类构件性能统计//0-框架梁, 1-框架柱, 2-斜撑,3-楼板, 4-底部加强区剪力墙,5-一般部位区剪力墙 6-连梁
	vector<vector<float>> m_vTotalPerformanceNumSeries;
	vector<int>  m_vMemberTypeNum;
	vector<float> m_vTotalMaxPerformanceNums;
	vector<float> m_vTotalMaxPerformancePer;
	vector<int> m_vTotalMaxPerformanceGrade;
	vector<float> m_vTotalMinPerformanceNums;
	vector<int> m_vTotalMinPerformanceGrade;

	////关键构件性能统计//0-框架梁, 1-框架柱, 2-斜撑,3-楼板, 4-剪力墙,5-连梁
	//vector<vector<float>> m_vKeyPerformanceNumSeries;
	//vector<int>  m_vKeyMemberTypeNum;
	//vector<float> m_vKeyMaxPerformanceNums;
	//vector<float> m_vKeyMaxPerformancePer;
	//vector<int> m_vKeyMaxPerformanceGrade;
	//vector<float> m_vKeyMinPerformanceNums;
	//vector<int> m_vKeyMinPerformanceGrade;

	////普通竖向构件性能统计//0-框架梁, 1-框架柱, 2-斜撑,3-楼板, 4-剪力墙,5-连梁
	//vector<vector<float>> m_vNormalPerformanceNumSeries;
	//vector<int>  m_vNormalMemberTypeNum;
	//vector<float> m_vNormalMaxPerformanceNums;
	//vector<float> m_vNormalMaxPerformancePer;
	//vector<int> m_vNormalMaxPerformanceGrade;
	//vector<float> m_vNormalMinPerformanceNums;
	//vector<int> m_vNormalMinPerformanceGrade;

	////耗能构件性能统计//0-框架梁, 1-框架柱, 2-斜撑,3-楼板, 4-剪力墙,5-连梁
	//vector<vector<float>> m_vConsumptionPerformanceNumSeries;
	//vector<int>  m_vConsumptionMemberTypeNum;
	//vector<float> m_vConsumptionMaxPerformanceNums;
	//vector<float> m_vConsumptionMaxPerformancePer;
	//vector<int> m_vConsumptionMaxPerformanceGrade;
	//vector<float> m_vConsumptionMinPerformanceNums;
	//vector<int> m_vConsumptionMinPerformanceGrade;

	vector<BOOL> m_vShearCheck; //0-关键剪力墙、1-关键框架柱、2-关键斜撑、3-普通剪力墙、4-普通框架柱、5-普通斜撑、6-耗能剪力墙、7-耗能框架柱、8-耗能斜撑
	vector<int> m_vEleindex;

	// 多模型方案报告比较
	vector<vector<vector<float>>> m_vTotalSchemeData;
	vector<string> m_vSchemePerformanceNames;
	vector<string> m_vSchemeNames; // 方案组的名称
	vector<string> m_vXDispNameSchemeName[2]; // 层间位移角：方案组的名称
	vector<string> m_vYDispNameSchemeName[2]; // 层间位移角：方案组的名称
	vector<string> m_vXDispWaveName[2]; // 楼层位移：工况名称
	vector<string> m_vYDispWaveName[2]; // 楼层位移：工况名称
	vector<string> m_vXShearNameSchemeName; // 层间剪力：方案组名称
	vector<string> m_vYShearNameSchemeName; // 层间剪力：方案组名称
	vector<string> m_vXShearWaveName; // 层间剪力：工况名称
	vector<string> m_vYShearWaveName; // 层间剪力：工况名称
	vector<vector<float>> m_vSchemeSeries;
	float m_fDispXMaxScheme;//所有方案相比较，最小X向层间位移角
	float m_fDispYMaxScheme;//所有方案相比较，最小Y向层间位移角
	CString m_sDispXMaxScheme;//所有方案相比较，最小X向层间位移角对应的方案
	CString m_sDispYMaxScheme;//所有方案相比较，最小Y向层间位移角对应的方案
	float m_fBaseShearXMax;
	float m_fBaseShearYMax;
	float m_fBaseShearXMaxScheme;
	float m_fBaseShearYMaxScheme;
	CString m_sBaseShearXMaxScheme;//所有方案相比较，最小X向层间位移角对应的方案
	CString m_sBaseShearYMaxScheme;//所有方案相比较，最小Y向层间位移角对应的方案
	vector<vector<string>> m_vPerformanceLoadCase; // 构件性能方案组的工况
	vector<string> m_vSchemePerformanceLoadCaseName; // 工况名称
	vector<vector<string>> m_vEnergyLoadCase; // 累计能量工况名称
	vector<vector<vector<float>>> m_vTotalStaticEnergy;
	vector<string> m_vSchemeEnergyLoadCaseName; // 工况名称
	float m_fDamperXMax;
	float m_fDamperYMax;
	float m_fDamperXMaxScheme;
	float m_fDamperYMaxScheme;
	CString m_sDamperXMaxScheme;
	CString m_sDamperYMaxScheme;

};