#pragma once
#include "HeadDefine.h"
#include "data.h"
#include "PostData.h"
#include "CF5ElmFieldData.h"
#include "CF15StruFieldData.h"
#include "CCheckingData.h"
#include "SumDllPara.h" 
#include "SSGData.h"
//#include "..\ssgapi\TractDll\Fibre.h"
#include "SectionBaseHead.h"
#include "TractDll\HeadDefine.h"
#include "TractDll\Interpolation.h"
#include "TractDll\PmmData.h"
#include "TractDll\Section.h"
#include "TractDll\SectionMesh.h"
//#include "..\ssgapi\TractDll\TMat.h"
#include "TractDll\Tract.h"

#include "CombineStruc.h"
#include "PostStruct.h"

class _POST_DLLIMPEXP CPost /*: public CRemoveInvalidPrimitive,public CProfile*/
{
public:
	CPost(void);
	~CPost(void);

	//����
	FIELD_TYPE m_MappingField;   //ӳ����������
	PERFORM_FIELD m_PerformanceiField;
	DEFORM_TYPE m_DeformType;   //����ͼ���ͣ�����״̬�Զ���ʾ��Ӧ����ͼ
	BOOL m_bNodeCenterSmooth;   //��Ԫ���ĵ��Ƿ��������ƽ����ʾ

	CVertex *m_pDeformNode;  //���κ����������飬���ڶ���


	CNodeFieldSet m_cDeformSet; //λ�Ƴ������ڱ��ε���
	CNodeFieldSet m_cNodeFieldSet; //�������,Ҳ������λ�Ƴ���������ɫ��ʾ
	CElmFieldOneComponent m_cElmFieldSet;   //��Ԫ����,������ɫ��ʾ	

	CCheckingData m_cChkData;//��������
	BOOL m_bNoIso;// �Ǹ���ģ�ͽ���鿴
	vector<CCombineStruc*> m_cCombineStruc; //�ϳɹ�������  ����20211116

	CPost & operator=(const CPost & mesh)
	{
		if(this==&mesh) return *this;
		ASSERT(FALSE);  //���ڸ��ٴ˺�������ʱ���ṩ���ƹ���
		return *this;
	}

	void Clear();

	//����fTimeʱ�̵ı������꣬fDeformRatioΪλ�ƷŴ���
	//�������������ַ,��ʱ�䳬�����ʱ�䲽�����޸�fTime�ص����,bDeform-������Σ�bColor-ӳ����ɫ
	CVertex *GetDeformNode(float &fTime,float fDeformRatio);  

	//����iLoopIndexʱ�̵�ģ̬�������꣬�������������ַ
	CVertex *GetDeformNode_Modal(int iLoopIndex,float fDeformRatio);
	CVertex *GetDeformNode_CModal(int iLoopIndex,int iComponent, float fDeformRatio);



	//������λ�ƽǲ�д�ļ�
	//�������ݣ�
	//iFilter: �������˷�����		0--�����η�Χ����									1--�����Ź���	2--��ָ�������
	//pFilterData:�����õ����ݣ�	const float[4] ���η�Χ(xmin,ymin,xmax,ymax)		const int* ����		NULL
	//���ز��λ�ƽ��ı��ļ�
	//iCalcType=1��ͳ�����ֵ��=2��ͳ��ƽ��ֵ��=3��ȫ��ͳ��
	BOOL CalcStoryShift(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads,int iCalcType=3, BOOL bScaleMassFlag=FALSE);
	BOOL CalcStoryShear(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads);
	BOOL CalcStoryEnergy(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads);

	BOOL CalcPerform(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL GetDamperPerform(int nOutMaxSteps,float** ppData,CElmFieldOneComponent* pElmFieldSet,int iDamperDispDir = 0, int nInMaxSteps = 0, int nDamper = 0);
	BOOL CalcElmPerformOld(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcElmPerform(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStruPerform(CArray<int, int> &aRunCase, CLoadCollection &cLoads); //����2021.11.11
	BOOL CalcStruPerformNew(CArray<int, int> &aRunCase, CLoadCollection &cLoads); //����2021.11.11
	BOOL CombineStruc(); //����2021.11.11
	BOOL CombineStrucHighSpeed(); //����2022.01.27
	int CompareVector(vector<int> x,vector<int> y); //����2021.11.11
	bool IsCombine(CPlateStruc &pPlateID1, CPlateStruc &pPlateID2);
	BOOL GetRBSDcAssess(float *f1Coordinate, float *f2Coordinate, float *f3Coordinate, int iCountLower,\
		int v0,vector<float> IntersectLocation, float (&f2Local)[2], float (&f3Local)[2], float (&f2LocalCompare)[2], float (&f3LocalCompare)[2], \
		vector<vector<float> > &DcDamageAssess);//������2019.11.14
	BOOL GetRBSPlatePerform(float *pPlateStrucPerform, int nIntersectLine, int plateid, int iStep, vector<vector<int> > &SteelStrainDtAssessPlate,\
		vector<vector<float> > &DcDamageAssess);//������2019.11.14
	BOOL GetNonlinearPlatePerform(float *pPlateStrucPerform, int nIntersectLine, int plateid, int iStep, \
		vector<vector<float> > &DcDamageAssess);//������23.01.2021
	BOOL GetIntersectLocation(float fCoordinateMax, float fCoordinateMin, vector<float> &IntersectLocation);//������2019.11.12
	BOOL GetElmAssess(int nMaxSteps,float** ppData,CElmFieldOneComponent* pElmFieldSet,PERFORM_FIELD iPerformField,\
		vector<vector<int> > &SteelStrainDtAssessBeam, vector<vector<int> > &SteelStrainDtAssessPlate, vector<vector<int> > &DcDamage, int iDamperDispDir = 0, BOOL bFD = TRUE, int iQuo = 0, int nForceMaxSteps = 0, int nDamper = 0);//, vector<vector<float> > &DtAssessPlate, vector<vector<float> > &DtAssess);//������2019.10.29 
	BOOL GetElmAssessNonlinearStrain(int nMaxSteps,float** ppData,PERFORM_FIELD iPerformField,\
		 vector<vector<int> > &DcDamage, CElmFieldOneComponent* pElmFieldSet = NULL);//�����Թ�̣�Ӧ�䣩������23.01.2021
	BOOL GetRBSDamageWidth(int v0, int LineNumber, float InterNorm,vector<vector<float> > &DcDamageAssess);//������2019.11.5
	BOOL CalcStruPerformOld(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStruPerformRBS(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//������2019.11.22
	BOOL CalcStruPerformCollapse(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//���� 
	BOOL CalcStruPerformGDNL(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//���� 06.01.2021�㶫ʡ�����������+�����Թ����������
	BOOL CalcStruPerformNonlinearStrain(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//���� 23.01.2021�㶫ʡ�����������+�����Թ����������
	//���㵥��������ָ��
	BOOL CalcCaseResi(int iCase,float *pBeamStrucPerform,float *pPlateStrucPerform,float *pk,float *prH,float *prD,float *pT,bool bCaseFile,CString sLoadCase);
	BOOL CalcResi84(int n,float *pValue,float &fLnMean,float &fLnStd,float &fValue84);	//�������ۣ�����84%��֤��ָ��
	BOOL CalcResi(CArray<int,int> &aRunCase,CLoadCollection &cLoads,bool bExtend);		//��������
	BOOL CalcResiInfo();	//��������ģ����Ϣ����������ʦ��������ϵͳ
	BOOL CalcStiffReduction(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStiffReduction2(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcOneCaseEnvelope(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL CalcOneCaseEnvelopeRatioCalc(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL CalcOneCaseEnvelopeXueCalc(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL CalcOneCaseCQC(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL Cal_CQC(float *InPut, int nLen,float *DampRatio, float *ModeT,int ModeNum, float *OutPut);
	BOOL Cal_CCQC(float* pNodalDispQ, float* pNodalDispDQ, int iDofNum, float* pDampRatio, float* pPeriod, int iCModeNum, float* pNodalDispComb);
	BOOL CalcRebarAs(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcEnvelopeRebarAs(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcRebarAsByElm(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcMultiCaseEnvelope(CArray<int,int> &aRunCase,CLoadCollection &cLoads,bool bPI=false);//��������Զ��๤������ �� 2017��11��30��
	BOOL CalcMultiCaseEnvelopeRatioCalc(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//��������Զ��๤������ �� 2017��11��30��
	BOOL CalcMultiCaseEnvelopeRebarAs(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file);//�๤��������
	BOOL CalcMultiCaseEnvelopeXueCalc(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//��������Զ��๤������ �� 2017��11��30��
	BOOL CF15File2CF5(CArray<int,int> &aRunCase, CLoadCollection &cLoads, const wchar_t *cInName, const wchar_t *cOutName, char *cWriteTitle, CString cWriteName, const wchar_t *cOutName1 = NULL, const wchar_t *cOutName2 = NULL);//
	BOOL CalcStoryShiftRespSpectrum(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads,int iCalcType=3, BOOL bScaleMassFlag=FALSE);
	BOOL CalcStoryShiftFunc(float *pData, float *pAveData, CString sBDSname, int *story_pillar_node, int npillar, BOOL bScaleMassFlag =  FALSE);
	BOOL GetCModePeriod(int &nMode, float *&pPeriod, float *&pDampRatio);
	BOOL CalcStoryShearRespSpectrum(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL WriteBinStoryFieldSpectrum(const CString &fname, int nItems, float *pData);
	BOOL CalcMemberForceSpectrum(CArray<int,int> &aRunCase, CLoadCollection &cLoads);

	int AddForce(const CString &fname,CF5Header  &hdr,CF5ElemBlock *pblock,STRUCT_TYPE iType,float* pData,int nComp,
		vector<BEAM_CONN_LAYER> &vBottomBeamElm,vector<SHELL_CONN_LAYER> &vBottomShell,vector<SHELL_CONN_LAYER> &vBottomQuad);

	//���ɵ�������Ԫ����İ����ļ�
	void GenerateBinElmField_Envelope(int iLoadCase,CString sTypeName,CString sGroup,CLoadCollection &cLoads);

	//���ַ����������ֵ��Сֵ
	void MaxMin(float **ppData, int nCol, int iCol, int nElm, int iElm, int nElmBefore, int iBegin, int nMaxSteps, float &fMax, float &fMin);


	//���ݵ����������ļ����ɶ๤����Ԫ����İ����ļ�
	void GenerateBinElmField_Envelope_MultiLoadCase(int nEnveCase,CString *sEnveCaseName,
		bool *bJoinCase,char *chEnveArr,CString sTypeName,CString sGroup,CLoadCollection &cLoads,bool bDirectAve=true);

	//�����������ش���ֵ������ѹ��
	void GenerateBinElmField_Gravity(int iLoadCase,CString sTypeName,CString sGroup);

	//���ɵ�������������İ����ļ�
	void GenerateBinStruField_Envelope(int iLoadCase,CString sTypeName,CString sGroup,CLoadCollection &cLoads);

	//���ɵ�������������İ����ļ� ��ÿ������
	void GenerateBinStruField_Envelope_OneCmp(int iLoadCase,CString sTypeName,CString sGroup,CLoadCollection &cLoads);

	//���ݵ����������ļ����ɶ๤����������İ����ļ�
	void GenerateBinStruField_Envelope_MultiLoadCase(int nEnveCase,CString *sEnveCaseName,
		bool *bJoinCase,char *chEnveArr,CString sTypeName,CString sGroup,CLoadCollection &cLoads);

	//���ݵ����������ļ����ɶ๤����������İ����ļ� ��ÿ����������
	void GenerateBinStruField_Envelope_MultiLoadCase_OneCmp(int nEnveCase,CString *sEnveCaseName,
		bool *bJoinCase,char *chEnveArr,CString sTypeName,CString sGroup,CLoadCollection &cLoads);

	BOOL GetSteelSecRes(int nMaxSteps,CElmFieldOneComponent* pElmFieldSet,float* pRes=NULL);
	//�ֽṹ��������
	BOOL GetSteelCrossSecStrengthCalc(CString sLoadcase,int &nBeam,float *pRes[2],bool bMesh=false,bool bShowError=false);

	//���ݹ��������������Ƿֲ����õ�n���м��������
	void GetSectForce(CBeamStruc *beam,const SectForce &sf1,const SectForce &sf2,SectForce &sfMid);
	void GetSectForce(CPlateStruc *plate,const SectForce &sf1,const SectForce &sf2,SectForce &sfMid);
	//���ݹ�������Ԫ�õ�������������
	void GetSecForceByElm(int iStruId, int *pElm,SectForce *psf);

	//�淶��ʽӦ���ȼ���
	BOOL CalcSecStressRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);

	BOOL WriteStressRatioTxtByStory(CString sResultPath, CPostContainer* pPost, vector< CLoadCase*> pLoadCase);
	BOOL WriteStressRatioTxt(CString sResultPath, CPostContainer* pPost, vector< CLoadCase*> pLoadCase);
	BOOL WriteStressRatioTxtTitle(CString sResultPath);
	BOOL WriteStressRatioTxtForce(SEnvStep* pEnvStep, CString sResultPath);
	BOOL WriteStressRatioTxtCase(vector< CLoadCase*> pLoadCase, CString sResultPath);
	BOOL OpenStressRatioTxt(int ID);
	BOOL CalcPerformByForce(LOADCASETYPE iType);
	//��ѹ�ȼ���
	BOOL CalcShearCompressRatio(CArray<int,int> &aRunCase, CLoadCollection &cLoads);
	//����ȼ���
	BOOL CalcShearSpanRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//������Ӧ������
	BOOL CalcNominalTensileStress(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//��ѹ��ϵ������
	BOOL CalcAxialTensionCoef(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//��ѹ�ȼ���
	//BOOL CalcAxialCompressionRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	
	//��������������
	BOOL CalcShearStress(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//�������������
	BOOL CalcFlexuralBearingCapacity(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//����ȼ���
	BOOL CalcMomentShearRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//�㶫ʡ��̹���λ�ƽ�
	BOOL CalcDispAngleGD(CArray<int, int> &aRunCase, CLoadCollection &cLoads);//�㶫ʡλ�ƽǼ�������

	BOOL CalcDispAngleXue(CArray<int, int> &aRunCase, CLoadCollection &cLoads);//Ѧ��λ�ƽǼ�������

	//�Ǳ�����ʱ����
	BOOL CalcDispAngleQiao(CArray<int, int> &aRunCase, CLoadCollection &cLoads);
	BOOL CalcOneCaseEnvelopeQiao(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL CalcRebarAsv(CArray<int,int> &aRunCase,CLoadCollection &cLoads);

	//�ֹ�dll��ȡ����
//�����Ϣ
	//void PrintMsg(string str, string m_sDir);
	
	BOOL TractBySSGMesh(int Num, BEAM_FIBRE_GEO *pConcFibreBuf, int nConcFibre, BEAM_FIBRE_GEO *pRebarFibreBuf, int nRebarFibre, BEAM_FIBRE_GEO *pSteelFibreBuf, int nSteelFibre, float fConcFc, float fRebarFy, float fSteelFy, int *MatType,int Method, CTract *pTract, PmmData *ppmmData);//, string sPath);
	//void TractWriteFile(CTract *m_cTract, string m_sDir);

	bool CalcPerformance(float P, float Mx, float My, float *M, vector<PmmData*> &m_Data);

	//���㹹���ļ�������
	bool CalcMaxMoment(float P, float Mx, float My, int MatType, float *M, vector<PmmData*> &m_Data);

	float dot(float *p0, float *p1);//���� 2021.03.08

	bool IsPointInPoly(float *p0, float **Poly);//����2021.03.08

//��App ������
	BOOL m_bSecondCalIsoBeta;
	BOOL m_bSecondCalElastic;

	void SetSecondCalIsoBeta(BOOL);
	void SetSecondCalElastic(BOOL);

	bool CalcPushover(float &M1,float &Coef,int NodeId,int IDir);
};

extern _POST_DLLIMPEXP CPost thePost;
