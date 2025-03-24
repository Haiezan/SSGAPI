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

//iReportType == 0  SAUSG ����
//iReportType == 1  Design ����
//iReportType == 2  ����ϵ�� ����
//iReportType == 3  ��������� ����
//iReportType == 4  DOG ����
//iReportType == 5  ���𱨸�
//iReportType == 6  ���𱨸�
//iReportType == 7  �ֽṹ����

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
	//���𱨸�����begin��
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
	//���𱨸�end
	//���𱨸�����begin��
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
	//���𱨸�end
	REPORT_BUCKLINGRESULT,
	REPORT_IMPERFECTIONS,
	REPORT_DISPLACEMENT,
	REPORT_STRESS,
	REPORT_STORYACC,
	//�ӹ̱���
	REPORT_REINFORED_MODELINFO,
	REPORT_REINFORED_PERFORMANCE,
	REPORT_METERIAL_USED,


};


struct WAVEDATA
{
	CString fame;  //�ļ���
	CString sCaseName;  //������
	CString sWaveName;  //��Ȼ�� �˹���
	CString sComboName;  //�����
	int iEarthQuakeProbility; //qiaobaojuan 2016.12.19
	int iWaveLibIndex; //�Ǳ��� 2015.6.11
	int iWaveLib;	//0----SSG���𲨿⣬ 1-----�û��Զ��岨
	float fAmp; //�����е�����ķ�ֵ���ٶ� 20230309�������
	vector<float> vTime;
	vector<float> vAcc;

	//������ż���Ӧ�׻��׼��� //20231229 Ϳ��� ���

	int iWaveCaseX = -1;//����X�����Ӧ�ķ����������
	int iWaveCaseY = -1;//����Y�����Ӧ�ķ����������
	int iWaveElasticCaseX = -1;//����X�����Ӧ�ĵ��Թ��������������
	int iWaveElasticCaseY = -1;//����Y�����Ӧ�ĵ��Թ��������������
	int iWaveType = 0;//0Ϊ��Ȼ����1Ϊ�˹���
	int iCrtCons = 1;//0Ϊ���ԣ�1Ϊ������
	float ResSpecBaseShearX = 0.0f;//X��Ӧ�׻��׼���
	float RatioX = 0.0f;
	float ResSpecBaseShearY = 0.0f;//Y��Ӧ�׻��׼���
	float RatioY = 0.0f;
	float ResSpecBaseShearXNonISO = 0.0f;//�Ǹ���ģ��X��Ӧ�׻��׼���
	float RatioXNonISO = 0.0f;
	float ResSpecBaseShearYNonISO = 0.0f;//�Ǹ���ģ��Y��Ӧ�׻��׼���
	float RatioYNonISO = 0.0f;

	float fDt;
	float fTimeInterval;//20241212 Ϳ���

	float fStartComputeTime;
	float fEndComputeTime;

	void PutData(CDataSequence2* pData2)
	{
		for (int i = 0; i < pData2->nPoints; i++) {
			vTime.push_back(pData2->pData[i].t);
			vAcc.push_back(pData2->pData[i].v);
		}
	}

	//��ֵ���ٶ�
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
		fame.Replace(L"��", L"");
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

	void OutputEarthquake(CLoadCollection lc,int iProbility=-1);//-1ȫ���
	void OutputAnalysisCase(CLoadCollection lc,int iProbility=-1);//-1ȫ���

	bool OutputModalResult(bool bWriteTitlOut=false);

	void PrepareShearResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
	void OutputShearChart();
	void OutputShearTable(CString sLoad=L"");
	void OutputEEPShearTable(CString sLoad = L"");
	void OutputDamperTable(CString sLoad = L"");
	void OutputRespecShearTable(CLoadCollection lc, int iProbility=-1);//-1ȫ���

	void PrepareDispResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
	void OutputDispChart();
	void OutputDispTable(CString sLoad=L"");

	void PrepareStoryAccResult(CLoadCollection lc, int iProbility=-1);
	void OutputStoryAccChart();//¥�����ļ��ٶ�ͼ 20230117 Ϳ���
	void OutputStoryAccTable();//¥������ͳ�Ʊ� 20230117 Ϳ���

	void PrepareStoryMaxAccResult(CLoadCollection lc,int iProbility=-1);
	void OutputStoryMaxAccTable(); //¥����ٶ�ͳ�Ʊ� 20230117 Ϳ���
	void OutputStoryMaxAccChart();//¥����ٶ����߱� 20230117 Ϳ���

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

	int GetKeyStory();//��ȡģ�͵ײ���ǿ�� 20241129 Ϳ���
	BOOL IsVipTypeDefined();//�ж��Ƿ����Զ�����Ҫ�Եȼ� 20241129 Ϳ���
	BOOL IsVipTypeMemberExist(int iViptype);//�жϸ���Ҫ�Եȼ��Ĺ����Ƿ���� 20241129 Ϳ���
	COLORREF GetTargetLevelColor(int iTarget);//��ȡ����Ŀ�����ɫ 20241129 Ϳ���

//���𱨸�ר�ú���begin
	void OutputIsolatorProperty();//�������֧����ѧ����
	void OutputContentsSISO();
	void OutputSSGISOTable(int iChk, int ic);//���֧�������� ic=0-���硢1-ƽ��
	void OutputISOESFTable();//��������Իָ���������
	void OutputISOMomentTable();//�������㿹�㸲������
	void OutputISOBasicRequirement();//����������Ҫ��
	void OutputISODesignRequirement();//����������Ҫ�󣺸��������֧����������
	void OutputISOModalResult();//�������Ǹ���ģ�����ڶԱ�
	void PrepareISOShearResult(CLoadCollection& loads, bool bBothDir = false);
	void PrepareISOShearReportResult(CLoadCollection& loads, bool bBothDir = false);
	void PrepareISODispResult(CLoadCollection& loads);
	void OutputISODispTable();
	void OutputISODispChart();
	void OutputISOShearChart(bool bBothDir = false);//���ˮƽ�����ϵ�������̣�¥��������㸲����
	void OutputISOShearReportChart(bool bBothDir = false);//20240311 Ϳ���
	void OutputISOBetaContents(bool bBetaReport = true, bool bBothDir = false);//���ˮƽ�����ϵ��������
	void OutputISOBetaReportContents(bool bBothDir = false);//20240311 Ϳ���
	void OutputConclusionISO();
	// ���𱨸�ר�ú���end

	//���𱨸�ר�ú���begin
	void PrepareShearResultDES(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
	void OutputContentsSDMP();
	void OutputSDMPTable();//���������������
	void OutputSDMPChart(CLoadCollection lc, int iProbility=-1);//����������ͻ����� 20240118 Ϳ���
	void OutputDMPBasicRequirement();//����������Ҫ��
	void OutputDMPDampingRatio(CLoadCollection lc,int iProbility=-1);//�����Ч����� 20240116 Ϳ���
	void OutputDMPDampingRatioCode(CLoadCollection lc, int iProbility=-1);//����淶�������Ч����� 20240116 Ϳ���
	void OutputSectProperty();
	void OutputSectNums();//���������������ͳ�Ʊ� 20240116 Ϳ���
	void OutputConclusionDMP();
	//void OutputISOModalResult();//�������Ǹ���ģ�����ڶԱ�
	// ���𱨸�ר�ú���end
	bool OutputCombination(CLoadCollection &lc);

	void OutputContentsSSteel();//�ֽṹ����
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
	

	// �ӹ̱���begin
	void OutputContentsReinForced();
	void OutputReinForcedInformation();
	bool OutputReinForcedModalResult(bool bWriteTitlOut = false); // ����
	void PrepareShearResultReinForced(CLoadCollection lc, bool bBothDir, int iProbility = -1);//-1ȫ��� ����
	void PrepareDispResultReinForced(CLoadCollection lc, bool bBothDir, int iProbility = -1);//-1ȫ��� λ��
	void OutputEnergyChartReinForced(CLoadCollection lc, int iProbility = -1); // ����ͼ
	void OutputDamagePerformanceReinForced(); // ����ָ��
	void OutputPerformanceStatisticsReinForced(bool bSpandrelOnly = false); // ����ͳ��
	void InterlayerDisplaycementAngleIndicater(); // ���λ�ƽ�ָ��
	void TheAmountOfMeterialUsed(); // �ӹ̺��������ͳ��
	CString GetFilePath_Temp(const CString& sExt, const CString& sLoadCase = L"", const CString& sGroupName = L"");
	CString GetPrjName_Temp(void);
	CString GetPrjPath_Temp(void);
	CString GetCaseStaticPath_Temp(const CString& sLoadCase); //�õ�����������Ŀ¼������"d:\exam_path\StaticResult\"
	CString GetEarthQuakePath_Temp(const CString& sLoadCase, bool m_bEnvCase = false); //�õ����⹤����Ŀ¼������"d:\exam_path\EarthQuakeResult\case_n\"
	CString GetEarthQuakeRoot_Temp(bool m_bEnvCase=false); //�õ����𹤿���Ŀ¼������"d:\exam_path\EarthQuakeResult\"
	CSSGData theData2;
	BOOL bNotReinForcedSSGModel;


	// ��ģ�ͷ�������Ƚ�
	void OutputContentsMultiModel();
	bool OutputMultiModelModalResult(bool bWriteTitlOut = false); // ����
	void PrepareShearResultMultiModel(const CSSGData* pMultiplyData, CLoadCollection lc, bool bBothDir, CString sSchemeName, int iProbility = -1);//-1ȫ��� ����
	void EnergyCalcu(const CSSGData* pMultiplyData, const CLoadCase* pLoad, float* pEnergy, BOOL m_bAddStaticEnergy=TRUE);
	void EnergyCalcuMultiModel(const CSSGData* pMultiplyData, CLoadCollection* pLC);
	void OutputEnergyCalcuTableMultiModel();
	void OutputPerformanceStatisticsMultiModel(CSSGData* pMultiplyData, int iScheme, bool bSpandrelOnly = false);
	void OutputPerformanceStatisticsMultiModelChart();
	void PrepareDispResultMultiModel(const CSSGData* pMultiplyData,CLoadCollection lc, bool bBothDir, CString sSchemeName, int iProbility = -1);//-1ȫ���
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
//	// ����
	bool DrawCurve_Wave(CString sPathName,float* fValue,int nCount[3]);
//	// X����Ϊ�̶�step�̶�
//	bool DrawCurve_X(CString sPathName,float fXStep,float* fValue,int nCount[3]);		// ���ݷ������Σ�ÿ�γ���
//	bool DrawCurve_Elas(CString sPathName,float* fcd1,float* fcd2,int nCount[2],BOOL bType);
//	// Ϊ����X��̶ȣ�Ҳ��˵fXValue��fValue��һһ��Ӧ��
//	bool DrawCurve(CString sPathName,FLOAT2* fValue,int *nCntValue,int nCount);		// ���ݷ������Σ�ÿ�γ���
//	// ����¥����ص�
//	bool DrawStorey(CString sPathName,int nStorey,int nStart,float* fValue,int nCount,CString* s,CString sXName,int itype=0);

	BOOL SavePicture(CString& sPathName,CDrawSetting& dSetting,float* fX,float* fY,int* nCount,CString* sSeriesName,int* nStart,int nCurve);
	BOOL SavePicture(CString& sPathName,CDrawSetting& dSetting,CACurveData* pData,int nCurve);
//	float Coord2ClientX(float x,float OrgX,float fXScale);
//	float Coord2ClientY(float y,float OrgY,float fYScale);
	void GetStringNodes(CString sLine);//,vector<int>& vNodeIDs);
	
//	

	vector<WAVEDATA> GetWaveType(CLoadCollection lc, int iProbility);//������Ȼ�����˹������ͼ�ͳ�� 20231229 Ϳ���
	vector<WAVEDATA>m_vWaveSeries;
	void GetWaveNums(vector<WAVEDATA> vWaveSeries);
	int m_nArtiWaves;
	int m_nNatureWaves;
	void ReadPeriod(CString fname, vector<float>& vPeriod);//��ȡģ������ 20241210 Ϳ���
//
//	// �����ǻ�ͼ����
//	void DrawAxis(CDC &dc,CRect& rc,float fMinX,float fMaxX,float fMinY,float fMaxY,float fRatioX,float fRatioY);
//	void Draw(CDC& MemDC,CRect& rc,int nCurve,int nCount,float* fX,float* fY,float fMinX,float fMinY,float fRatX,float fRatY);
//	float ScaleAxis(float init_min_value,float init_max_value,int init_point_num, 
//		float &axis_min_value,float &axis_max_value, int &axis_point_num,int &iex);		// Ҫʵ��
//
//	CPoint GetClientCoor(CRect rc,float x,float y,float fMinX,float fMinY,float fRatioX,float fRatioY);  //��������ת��Ϊ��ͼ����;
//
//	COLORREF m_CColor[6];
//
//
//
//private:
//	//CReportEDlg* m_pSetDlg;
//

//	// ����8������������Vx\б��Vx\����ǽVx\¥�����Vx\����Vy\б��Vy\����ǽVy\¥�����Vy
//	map<int,vFlt8>  m_mapShear;		// ������һ����������������һ������
//	//λ��6��������x���λ�ƣ�y���λ�ƣ�x���λ�ƽǣ�y���λ�ƽǣ�x¥��λ�ƣ�y¥��λ��
//	// ����ʱ�̼���
	CWord m_word;
	CString m_edtNode;
	CString m_edtTime;

	vector<CString> m_vecCase;
	vector<multimap<CString, CString>> m_vecProgress;

	float m_fTotalWeight;
	vector<vector<float>> m_vBaseShear;	//���������׼������ݣ�  { ������Vx  ¥�����Vx ������Vy  ¥�����Vy }
	vector<vector<float>> m_vDispX;		//������λ�����ݣ�  { ��󶥵�λ�ơ������λ�ƽǡ�λ�ƽǶ�Ӧ��� }
	vector<vector<float>> m_vDispY;		//������λ�����ݣ�  { ��󶥵�λ�ơ������λ�ƽǡ�λ�ƽǶ�Ӧ��� }

	vector<vector<float>> m_vAccX;		//������λ�����ݣ�  { ���¥����ٶȡ���Ӧ��� }
	vector<vector<float>> m_vAccY;		//������λ�����ݣ�  { ���¥����ٶȡ���Ӧ��� }


	//vector<bool> m_vCaseX;	//��ʱ�ģ�Ҫɾ����

	vector<bool> m_vCaseSelected;	//case selected for output  ��������
	vector<bool> m_vCaseSelectedStatic;	//case selected for output ����������
	vector<bool> m_vCaseSelectedElastic;	//case selected for output ��Ч����
	vector<bool> m_vCaseSelectedDirect;	//case selected for output ֱ�ӷ������
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


//���㹤��
	sd::IGenerateText *m_pGenerateDocx;

	sd::CExhibition *m_pExhibition;


	//sd::IGenerateText *m_pGenerate;

//SAUSAGE-Check ������
	int m_iValueCombi;
	float m_fMinValue;
	float m_fMaxValue;
	float m_f2dfMinValue;
	float m_f2dfMaxValue;

	bool m_batchReport;	//����������
private:

	int m_iReportType;
	PPAGE_FORMAT m_pPageFormat;			//ҳ���ʽ
	PPARAGRAPH_FORMAT m_pParaghFormat;  //�����ʽ
	PTEXT_FORMAT m_pTextFormat;			//�ı���ʽ
	PGRAPHIC_FORMAT m_pPicFormat;		//��ͨͼƬ��ʽ
	PGRAPHIC_EMBED_FORMAT m_pPicEmbedFormat; //Ƕ����ͼƬ��ʽ
	PTABLE_FORMAT m_pTableFormat;		//����ʽ
	PCELL_FORMAT m_pCellFormat;			//��Ԫ���ʽ
	PCHART_FORMAT m_pChartFormat;		//ͼ���ʽ(��״ͼ��)

	vector<int> m_vElas;
	vector<int> m_vPlas;
	vector<pair<int,int>> m_vecElasPlas;

	vector<wstring> m_vArrayShear;		//�������
	vector<wstring> m_vArrayRespecShear;		//��Ӧ�׼������ 20240102 Ϳ���
	vector<wstring> m_vArrayElasticShear;		//�����Ի��׼����Աȱ��
	vector<wstring> m_vArrayDisp[2];	//λ�Ʊ��, 0-���壬 1-�Զ���
	vector<wstring> m_vArrayModal;		//ģ̬���
	vector<wstring> m_vArrayCase;
	vector<wstring> m_vArrayDamper; //�ṹ��������ȱ�� 20240104 Ϳ���
	vector<wstring> m_vArraySpecEarthQuake; //������淶��Ӧ����Ҫ���ڵ��ֵ 20240109 Ϳ���
	vector<wstring> m_vArraySpecAverage; //����ƽ������淶��Ӧ����Ҫ���ڵ��ֵ 20240109 Ϳ���
	vector<wstring> m_vArrayAcc;// ¥����ٶȱ�� 20240117 Ϳ���
	vector<wstring> m_vArrayMassCenter;// ¥�����ļ��ٶȱ�� 20240117 Ϳ���

	vector<wstring> m_vArrayEnergy; //Ӧ���ܱ�� 20240116 Ϳ���
	vector<wstring> m_vArrayDamperEnergy; //���������ܱ�� 20240116 Ϳ���
	vector<wstring> m_vArraySecNumbers; //������������� 20240116 Ϳ���

	vector<wstring> m_vArrayPerformance; //�������ܻ��ܱ� 20240204 Ϳ���
	vector<wstring> m_vArrayPerformGrade; //����ˮƽ��� 20240205 Ϳ���

	vector<float>m_vDispDamperRatioX;//20240116 Ϳ���
	vector<float>m_vVeloDamperRatioX;//20240116 Ϳ���
	vector<float>m_vTotalAddDamperRatioX;//20240116 Ϳ���
	vector<float>m_vDispDamperRatioY;//20240116 Ϳ���
	vector<float>m_vVeloDamperRatioY;//20240116 Ϳ���
	vector<float>m_vTotalAddDamperRatioY;//20240116 Ϳ���

	vector<string> m_vXDispName[2];		//¥��λ��
	vector<string> m_vYDispName[2];

	vector<vector<string>> m_vXDispNameTower;//20240108 Ϳ���
	vector<vector<string>> m_vYDispNameTower;//20240108 Ϳ���

	vector<vector<float>> m_vXDispStorySeries[2];	
	vector<vector<float>> m_vYDispStorySeries[2];

	vector<vector<vector<float>>> m_vXDispStorySeriesTower;			//20240108 Ϳ���
	vector<vector<vector<float>>> m_vYDispStorySeriesTower;			//20240108 Ϳ���

	vector<vector<float>> m_vXDispSeries[2];
	vector<vector<float>> m_vYDispSeries[2];

	vector<vector<vector<float>>>  m_vXDispSeriesTower;			//20240108 Ϳ���
	vector<vector<vector<float>>>  m_vYDispSeriesTower;			//20240108 Ϳ���



	//¥����ٶ� 20240117 Ϳ���

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

	//¥�����ļ��ٶ� 20240117 Ϳ���
	vector<string> m_vXAcceName;
	vector<string> m_vYAcceName;

	vector<vector<float>> m_vXAcceStorySeries;
	vector<vector<float>> m_vYAcceStorySeries;

	vector<vector<float>> m_vXAcceSeries;
	vector<vector<float>> m_vYAcceSeries;


	vector<string> m_vXDriftName[2];	//���λ�ƽ�
	vector<string> m_vYDriftName[2];

	vector<vector<string>> m_vXDriftNameTower;//20240108 Ϳ���
	vector<vector<string>> m_vYDriftNameTower;//20240108 Ϳ���

	vector<vector<float>> m_vXDriftStorySeries[2];
	vector<vector<float>> m_vYDriftStorySeries[2];

	vector<vector<vector<float>>> m_vXDriftStorySeriesTower;			//20240108 Ϳ���
	vector<vector<vector<float>>> m_vYDriftStorySeriesTower;			//20240108 Ϳ���

	vector<vector<float>> m_vXDriftSeries[2];
	vector<vector<float>> m_vYDriftSeries[2];

	vector<vector<vector<float>>>  m_vXDriftSeriesTower;			//20240108 Ϳ���
	vector<vector<vector<float>>>  m_vYDriftSeriesTower;			//20240108 Ϳ���

	BOOL bDriftMeetLimit;
	BOOL bAccMeetLimit;
	BOOL bAcceMeetLimit;

	vector<string> m_vXDispTopName;
	vector<string> m_vYDispTopNames;

	vector<vector<float>> m_vXDispTopTimeSeries;
	vector<vector<float>> m_vYDispTopTimeSeries;

	vector<vector<float>> m_vXDispTopSeriesNodeDisp;
	vector<vector<float>> m_vYDispTopSeriesNodeDisp;


	//����,¥��,���� 
	vector<string> m_vXShearName;							//X�� ��ǩ
	vector<string> m_vYShearName;							//Y�� ��ǩ
	vector<string> m_vXShearNameNoIso;					//20240130 Ϳ���
	vector<string> m_vYShearNameNoIso;					//20240130 Ϳ���
	vector<vector<float>> m_vXShearTimeSeries;
	vector<vector<float>> m_vYShearTimeSeries;
	vector<vector<float>> m_vXShearBaseshearSeries;			//X ���׼���ʱ��
	vector<vector<float>> m_vYShearBaseshearSeries;			//Y ���׼���ʱ��

	vector<string> m_vXShearStoryName;						//X�� ��ǩ
	vector<string> m_vYShearStoryName;						//Y�� ��ǩ
	vector<vector<string>> m_vXShearStoryNameTower;			//20240105 Ϳ���
	vector<vector<string>> m_vYShearStoryNameTower;			//20240105 Ϳ���
	vector<string> m_vXShearStoryNameNoIso;					//20240130 Ϳ���
	vector<string> m_vYShearStoryNameNoIso;					//20240130 Ϳ���

	//¥�����
	vector<vector<float>> m_vXStoryShearIDSeries;			//X��Ϊ�� ¥����
	vector<vector<float>> m_vYStoryShearIDSeries;			//Y��Ϊ�� ¥����
	vector<vector<float>> m_vXStoryShearIDSeriesNoIso;			//20240130 Ϳ���
	vector<vector<float>> m_vYStoryShearIDSeriesNoIso;			//20240130 Ϳ���
	vector<vector<vector<float>>>m_vXStoryShearIDSeriesTower;			//20240105 Ϳ���
	vector<vector<vector<float>>> m_vYStoryShearIDSeriesTower;			//20240105 Ϳ���


	vector<vector<float>> m_vXStoryShearForceSeries;		//X������
	vector<vector<float>> m_vYStoryShearForceSeries;		//Y������
	vector<vector<float>> m_vXStoryShearForceSeriesNoIso;		//20240130 Ϳ���
	vector<vector<float>> m_vYStoryShearForceSeriesNoIso;		//20240130 Ϳ���
	vector<vector<vector<float>>> m_vXStoryShearForceSeriesTower;		//20240105 Ϳ���
	vector<vector<vector<float>>> m_vYStoryShearForceSeriesTower;		//20240105 Ϳ���

	vector<vector<float>> m_vShearXStoryMomentSeries;		//X���㸲����
	vector<vector<float>> m_vShearYStoryMomentSeries;		//Y���㸲����
	vector<vector<float>> m_vShearXStoryMomentSeriesNoIso;		//X���㸲����
	vector<vector<float>> m_vShearYStoryMomentSeriesNoIso;		//Y���㸲����
	vector<vector<vector<float>>> m_vShearXStoryMomentSeriesTower;		//20240105 Ϳ���
	vector<vector<vector<float>>> m_vShearYStoryMomentSeriesTower;		//20240105 Ϳ���

	float m_fShearRatioAveX;//X����ر�ƽ��ֵ
	float m_fShearRatioAveY;//Y����ر�ƽ��ֵ

	vector<int> m_vNodeIDs;
	vector<int> m_vTopPoint;

	//��Ӧ�׻��׼��� 20240102 Ϳ���
	float m_fRespecBaseShearX ;//��Ӧ��X����׼���
	float m_fRespecBaseShearY ;//��Ӧ��Y����׼���
	float m_fRespecBaseShearXNonISO;//�Ǹ���ģ�ͷ�Ӧ��X����׼���
	float m_fRespecBaseShearYNonISO;//�Ǹ���ģ�ͷ�Ӧ��Y����׼���


	float m_fDispXMax;//�����������X����λ�ƽ�
	float m_fDispYMax;//�����������Y����λ�ƽ�
	int m_fDispXMaxStory;//�����������X����λ�ƽǶ�Ӧ���
	int m_fDispYMaxStory;//�����������Y����λ�ƽǶ�Ӧ���

	float m_fAccXMax;//�����������X��¥����ٶ�
	float m_fAccYMax;//�����������Y��¥����ٶ�
	int m_fAccXMaxStory;//�����������X��¥����ٶȶ�Ӧ���
	int m_fAccYMaxStory;//�����������Y��¥����ٶȶ�Ӧ���

	float m_fAbsAccXMax;//�����������X��¥�����ļ��ٶ�
	float m_fAbsAccYMax;//�����������Y��¥�����ļ��ٶ�
	int m_fAbsAccXMaxStory;//�����������X��¥�����ļ��ٶȶ�Ӧ���
	int m_fAbsAccYMaxStory;//�����������Y��¥�����ļ��ٶȶ�Ӧ���

	//��Ч�����
	vector<float>m_vStrainLast;//�����������
	vector<float>m_vVeloDamperLast;//�ٶ��������������
	vector<float>m_vDispDamperLast;//λ���������������
	vector<vector<float>>m_vEnergyRatio;//����ռ��

	int m_nSDMPNums;
	vector<CString>m_vSDMPName;//���������ּ�����
	vector<float>m_vMaxDesignLoad;//�����������ƺ���
	vector<float>m_vMaxDesignDisp;//������������λ��
	vector<float>m_vMaxDesignVelo;//�������������ٶ�
	vector<float>m_vDesignLoadCodeLimit;//������������ƺ���
	vector<float>m_vDesignDispCodeLimit;//�������������λ��
	vector<float>m_vDesignVeloCodeLimit;//��������������ٶ�
	vector<BOOL>m_bMeetSDMPCheck;//��������������ٶ�
	vector<BOOL>m_vISOCheck;//����֧������ʹ��״̬����
	float m_fUltimateDis;//����֧�����ˮƽλ��
	float m_fUltimateDisLimit;//����֧�����ˮƽλ����ֵ
	float m_fCmpStress;//����֧�����ѹӦ��
	float m_fCmpStressLimit;//����֧�������Ӧ��
	float m_fTenStress;//����֧�������Ӧ��
	float m_fTenStressLimit;//����֧�������Ӧ����ֵ
	float m_fTenStressPercent;//����֧�������ٷֱ�
	BOOL m_bESFCheck;//����֧���ָ���������
	BOOL m_bMomentCheck;//����֧���㸲����������
	BOOL m_bISISOChecked;
	BOOL m_bISESFChecked;
	BOOL m_bISMomentChecked;


	float m_fStrainLastEnv;//����������Ȱ���ֵ
	float m_fVeloDamperLastEnv;//�ٶ�������������Ȱ���ֵ
	float m_fDispDamperLastEnv;//λ��������������Ȱ���ֵ
	float m_fStrainLastAve;//�����������ƽ��ֵ
	float m_fVeloDamperLastAve;//�ٶ��������������ƽ��ֵ
	float m_fDispDamperLastAve;//λ���������������ƽ��ֵ
	float m_fTotalDamperAve;//�ܵ�Ч�����ƽ��ֵ
	float m_fAddLastEnvX;//��������Ȱ���ֵ
	float m_fAddLastEnvY;//��������Ȱ���ֵ
	float m_fAddLastAveX;//���������ƽ��ֵ
	float m_fAddLastAveY;//���������ƽ��ֵ
	float m_fCodeAddLastEnvX;//�淶�㷨��������Ȱ���ֵ
	float m_fCodeAddLastEnvY;//�淶�㷨��������Ȱ���ֵ
	float m_fCodeAddLastAveX;//�淶�㷨���������ƽ��ֵ
	float m_fCodeAddLastAveY;//�淶�㷨���������ƽ��ֵ
	//vector<float>m_vKsi0;//��ʼ�����
	//vector<float>m_vKsi0c;//��������ʼ�����
	//vector<float>m_vKsi0s;//�ֳ�ʼ�����
	//vector<float>m_vKsiDamper;�ܵ�Ч�����
	float m_fBetaX;//X��ˮƽ����ϵ��
	float m_fBetaY;//Y��ˮƽ����ϵ��

	////Ĭ�Ϸ��๹������ͳ��//0-�����, 1-�����, 2-б��,3-¥��, 4-�ײ���ǿ������ǽ,5-һ�㲿λ������ǽ 6-����
	vector<vector<float>> m_vTotalPerformanceNumSeries;
	vector<int>  m_vMemberTypeNum;
	vector<float> m_vTotalMaxPerformanceNums;
	vector<float> m_vTotalMaxPerformancePer;
	vector<int> m_vTotalMaxPerformanceGrade;
	vector<float> m_vTotalMinPerformanceNums;
	vector<int> m_vTotalMinPerformanceGrade;

	////�ؼ���������ͳ��//0-�����, 1-�����, 2-б��,3-¥��, 4-����ǽ,5-����
	//vector<vector<float>> m_vKeyPerformanceNumSeries;
	//vector<int>  m_vKeyMemberTypeNum;
	//vector<float> m_vKeyMaxPerformanceNums;
	//vector<float> m_vKeyMaxPerformancePer;
	//vector<int> m_vKeyMaxPerformanceGrade;
	//vector<float> m_vKeyMinPerformanceNums;
	//vector<int> m_vKeyMinPerformanceGrade;

	////��ͨ���򹹼�����ͳ��//0-�����, 1-�����, 2-б��,3-¥��, 4-����ǽ,5-����
	//vector<vector<float>> m_vNormalPerformanceNumSeries;
	//vector<int>  m_vNormalMemberTypeNum;
	//vector<float> m_vNormalMaxPerformanceNums;
	//vector<float> m_vNormalMaxPerformancePer;
	//vector<int> m_vNormalMaxPerformanceGrade;
	//vector<float> m_vNormalMinPerformanceNums;
	//vector<int> m_vNormalMinPerformanceGrade;

	////���ܹ�������ͳ��//0-�����, 1-�����, 2-б��,3-¥��, 4-����ǽ,5-����
	//vector<vector<float>> m_vConsumptionPerformanceNumSeries;
	//vector<int>  m_vConsumptionMemberTypeNum;
	//vector<float> m_vConsumptionMaxPerformanceNums;
	//vector<float> m_vConsumptionMaxPerformancePer;
	//vector<int> m_vConsumptionMaxPerformanceGrade;
	//vector<float> m_vConsumptionMinPerformanceNums;
	//vector<int> m_vConsumptionMinPerformanceGrade;

	vector<BOOL> m_vShearCheck; //0-�ؼ�����ǽ��1-�ؼ��������2-�ؼ�б�š�3-��ͨ����ǽ��4-��ͨ�������5-��ͨб�š�6-���ܼ���ǽ��7-���ܿ������8-����б��
	vector<int> m_vEleindex;

	// ��ģ�ͷ�������Ƚ�
	vector<vector<vector<float>>> m_vTotalSchemeData;
	vector<string> m_vSchemePerformanceNames;
	vector<string> m_vSchemeNames; // �����������
	vector<string> m_vXDispNameSchemeName[2]; // ���λ�ƽǣ������������
	vector<string> m_vYDispNameSchemeName[2]; // ���λ�ƽǣ������������
	vector<string> m_vXDispWaveName[2]; // ¥��λ�ƣ���������
	vector<string> m_vYDispWaveName[2]; // ¥��λ�ƣ���������
	vector<string> m_vXShearNameSchemeName; // ������������������
	vector<string> m_vYShearNameSchemeName; // ������������������
	vector<string> m_vXShearWaveName; // ����������������
	vector<string> m_vYShearWaveName; // ����������������
	vector<vector<float>> m_vSchemeSeries;
	float m_fDispXMaxScheme;//���з�����Ƚϣ���СX����λ�ƽ�
	float m_fDispYMaxScheme;//���з�����Ƚϣ���СY����λ�ƽ�
	CString m_sDispXMaxScheme;//���з�����Ƚϣ���СX����λ�ƽǶ�Ӧ�ķ���
	CString m_sDispYMaxScheme;//���з�����Ƚϣ���СY����λ�ƽǶ�Ӧ�ķ���
	float m_fBaseShearXMax;
	float m_fBaseShearYMax;
	float m_fBaseShearXMaxScheme;
	float m_fBaseShearYMaxScheme;
	CString m_sBaseShearXMaxScheme;//���з�����Ƚϣ���СX����λ�ƽǶ�Ӧ�ķ���
	CString m_sBaseShearYMaxScheme;//���з�����Ƚϣ���СY����λ�ƽǶ�Ӧ�ķ���
	vector<vector<string>> m_vPerformanceLoadCase; // �������ܷ�����Ĺ���
	vector<string> m_vSchemePerformanceLoadCaseName; // ��������
	vector<vector<string>> m_vEnergyLoadCase; // �ۼ�������������
	vector<vector<vector<float>>> m_vTotalStaticEnergy;
	vector<string> m_vSchemeEnergyLoadCaseName; // ��������
	float m_fDamperXMax;
	float m_fDamperYMax;
	float m_fDamperXMaxScheme;
	float m_fDamperYMaxScheme;
	CString m_sDamperXMaxScheme;
	CString m_sDamperYMaxScheme;

};