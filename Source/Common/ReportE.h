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
	//���𱨸�end
	//���𱨸�����begin��
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
	//���𱨸�end
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

	void OutputEarthquake(CLoadCollection lc,int iProbility=-1);//-1ȫ���
	void OutputAnalysisCase(CLoadCollection lc,int iProbility=-1);//-1ȫ���
	bool OutputModalResult(bool bWriteTitlOut=false);

	void PrepareShearResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
	void OutputShearChart();
	void OutputShearTable(CString sLoad=L"");

	void PrepareDispResult(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
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
//���𱨸�ר�ú���begin
	void OutputContentsSISO();
	void OutputSSGISOTable(int iChk);//���֧��������
	void OutputISOBasicRequirement();//����������Ҫ��
	void OutputISODesignRequirement();//����������Ҫ�󣺸��������֧����������
	void OutputISOModalResult();//�������Ǹ���ģ�����ڶԱ�
	void PrepareISOShearResult(CLoadCollection  &loads,bool bBothDir=false);
	void OutputISOShearChart(bool bBothDir=false);//���ˮƽ�����ϵ�������̣�¥��������㸲����
	void OutputISOBetaContents(bool bBetaReport=true,bool bBothDir=false);//���ˮƽ�����ϵ��������
	// ���𱨸�ר�ú���end

	//���𱨸�ר�ú���begin
	void PrepareShearResultDES(CLoadCollection lc,bool bBothDir,int iProbility=-1);//-1ȫ���
	void OutputContentsSDMP();
	void OutputSDMPTable();//���������������
	void OutputDMPBasicRequirement();//����������Ҫ��
	void OutputDMPDampingRatio(CLoadCollection lc,int iProbility=-1);//�����Ч�նȼ���Ч�����
	void OutputSectProperty();
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

	//vector<bool> m_vCaseX;	//��ʱ�ģ�Ҫɾ����

	vector<bool> m_vCaseSelected;	//case selected for output  ��������
	vector<bool> m_vCaseSelectedStatic;	//case selected for output ����������
	vector<bool> m_vCaseSelectedElastic;	//case selected for output ��Ч����
	vector<bool> m_vCaseSelectedDirect;	//case selected for output ֱ�ӷ������
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
	vector<wstring> m_vArrayDisp[2];	//λ�Ʊ��, 0-���壬 1-�Զ���
	vector<wstring> m_vArrayModal;		//ģ̬���
	vector<wstring> m_vArrayCase;

	vector<string> m_vXDispName[2];
	vector<string> m_vYDispName[2];

	vector<vector<float>> m_vXDispStorySeries[2];	
	vector<vector<float>> m_vYDispStorySeries[2];

	vector<vector<float>> m_vXDriftSeries[2];		//���λ�ƽ�
	vector<vector<float>> m_vYDriftSeries[2];

	vector<vector<float>> m_vXDispSeries[2];		//¥��λ��
	vector<vector<float>> m_vYDispSeries[2];


	vector<string> m_vXDispTopName;
	vector<string> m_vYDispTopNames;

	vector<vector<float>> m_vXDispTopTimeSeries;
	vector<vector<float>> m_vYDispTopTimeSeries;

	vector<vector<float>> m_vXDispTopSeriesNodeDisp;
	vector<vector<float>> m_vYDispTopSeriesNodeDisp;


	//����,¥��,���� 
	vector<string> m_vXShearName;							//X�� ��ǩ
	vector<string> m_vYShearName;							//Y�� ��ǩ
	vector<vector<float>> m_vXShearTimeSeries;
	vector<vector<float>> m_vYShearTimeSeries;
	vector<vector<float>> m_vXShearBaseshearSeries;			//X ���׼���ʱ��
	vector<vector<float>> m_vYShearBaseshearSeries;			//Y ���׼���ʱ��

	vector<string> m_vXShearStoryName;						//X�� ��ǩ
	vector<string> m_vYShearStoryName;						//Y�� ��ǩ

	//¥�����
	vector<vector<float>> m_vXStoryShearIDSeries;			//X��Ϊ�� ¥����
	vector<vector<float>> m_vYStoryShearIDSeries;			//Y��Ϊ�� ¥����

	vector<vector<float>> m_vXStoryShearForceSeries;		//X������
	vector<vector<float>> m_vYStoryShearForceSeries;		//Y������

	vector<vector<float>> m_vShearXStoryMomentSeries;		//X���㸲����
	vector<vector<float>> m_vShearYStoryMomentSeries;		//Y���㸲����


	vector<int> m_vNodeIDs;
	vector<int> m_vTopPoint;
};