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

	//后处理
	FIELD_TYPE m_MappingField;   //映射物理场类型
	PERFORM_FIELD m_PerformanceiField;
	DEFORM_TYPE m_DeformType;   //变形图类型，动画状态自动显示相应变形图
	BOOL m_bNodeCenterSmooth;   //单元中心点是否参与物理场平滑显示

	CVertex *m_pDeformNode;  //变形后结点坐标数组，用于动画


	CNodeFieldSet m_cDeformSet; //位移场，用于变形叠加
	CNodeFieldSet m_cNodeFieldSet; //结点物理场,也可以是位移场，用于颜色显示
	CElmFieldOneComponent m_cElmFieldSet;   //单元物理场,用于颜色显示	
	CElmFieldOneComponent m_cElmFieldSet2;   //单元物理场,用于颜色显示	多分量显示用,目前仅用于裂缝显示

	CCheckingData m_cChkData;//验算数据
	BOOL m_bNoIso;// 非隔震模型结果查看
	vector<CCombineStruc*> m_cCombineStruc; //合成构件数据  贾苏20211116

	CPost & operator=(const CPost & mesh)
	{
		if(this==&mesh) return *this;
		ASSERT(FALSE);  //用于跟踪此函数，暂时不提供复制功能
		return *this;
	}

	void Clear();

	//计算fTime时刻的变形坐标，fDeformRatio为位移放大倍数
	//返回坐标数组地址,若时间超过最大时间步，则修改fTime回到起点,bDeform-坐标变形，bColor-映射颜色
	CVertex *GetDeformNode(float &fTime,float fDeformRatio);  

	//计算iLoopIndex时刻的模态振型坐标，返回坐标数组地址
	CVertex *GetDeformNode_Modal(int iLoopIndex,float fDeformRatio);
	CVertex *GetDeformNode_CModal(int iLoopIndex,int iComponent, float fDeformRatio);



	//计算层间位移角并写文件
	//输入数据：
	//iFilter: 构件过滤方法，		0--按矩形范围过滤									1--按塔号过滤	2--按指定点过滤
	//pFilterData:过滤用的数据，	const float[4] 矩形范围(xmin,ymin,xmax,ymax)		const int* 塔号		NULL
	//返回层间位移角文本文件
	//iCalcType=1：统计最大值，=2：统计平均值，=3：全部统计
	BOOL CalcStoryShift(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads,int iCalcType=3, BOOL bScaleMassFlag=FALSE, float m_fAngle=0, int iCentroidTower=-1);// m_fAngle0自定义角度 iTower塔号 
	BOOL CalcStoryShear(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads);
	BOOL CalcStoryEnergy(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads);

	BOOL CalcPerform(CArray<int, int>& aRunCase, CLoadCollection& cLoads, BOOL bCombStrucs = TRUE);
	BOOL GetDamperPerform(int nOutMaxSteps,float** ppData,CElmFieldOneComponent* pElmFieldSet,int iDamperDispDir = 0, int nInMaxSteps = 0, int nDamper = 0);
	BOOL CalcElmPerformOld(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcElmPerform(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStruPerform(CArray<int, int> &aRunCase, CLoadCollection &cLoads); //贾苏2021.11.11
	BOOL CalcStruPerformNew(CArray<int, int> &aRunCase, CLoadCollection &cLoads); //贾苏2021.11.11
	BOOL CombineStruc(); //贾苏2021.11.11
	BOOL CombineStrucHighSpeed(); //贾苏2022.01.27
	int CompareVector(vector<int> x,vector<int> y); //贾苏2021.11.11
	bool IsCombine(CPlateStruc &pPlateID1, CPlateStruc &pPlateID2);
	BOOL GetRBSDcAssess(float *f1Coordinate, float *f2Coordinate, float *f3Coordinate, int iCountLower,\
		int v0,vector<float> IntersectLocation, float (&f2Local)[2], float (&f3Local)[2], float (&f2LocalCompare)[2], float (&f3LocalCompare)[2], \
		vector<vector<float> > &DcDamageAssess);//王丹，2019.11.14
	BOOL GetRBSPlatePerform(float *pPlateStrucPerform, int nIntersectLine, int plateid, int iStep, vector<vector<int> > &SteelStrainDtAssessPlate,\
		vector<vector<float> > &DcDamageAssess);//王丹，2019.11.14
	BOOL GetNonlinearPlatePerform(float *pPlateStrucPerform, int nIntersectLine, int plateid, int iStep, \
		vector<vector<float> > &DcDamageAssess);//王丹，23.01.2021
	BOOL GetIntersectLocation(float fCoordinateMax, float fCoordinateMin, vector<float> &IntersectLocation);//王丹，2019.11.12
	BOOL GetElmAssess(int nMaxSteps,float** ppData,CElmFieldOneComponent* pElmFieldSet,PERFORM_FIELD iPerformField,\
		vector<vector<int> > &SteelStrainDtAssessBeam, vector<vector<int> > &SteelStrainDtAssessPlate, vector<vector<int> > &DcDamage, int iDamperDispDir = 0, BOOL bFD = TRUE, int iQuo = 0, int nForceMaxSteps = 0, int nDamper = 0);//, vector<vector<float> > &DtAssessPlate, vector<vector<float> > &DtAssess);//王丹，2019.10.29 
	BOOL GetElmAssessNonlinearStrain(int nMaxSteps,float** ppData,PERFORM_FIELD iPerformField,\
		 vector<vector<int> > &DcDamage, CElmFieldOneComponent* pElmFieldSet = NULL);//非线性规程（应变）王丹，23.01.2021
	BOOL GetRBSDamageWidth(int v0, int LineNumber, float InterNorm,vector<vector<float> > &DcDamageAssess);//王丹，2019.11.5
	BOOL CalcStruPerformOld(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStruPerformRBS(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//王丹，2019.11.22
	BOOL CalcStruPerformCollapse(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//王丹 
	BOOL CalcStruPerformGDNL(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//王丹 06.01.2021广东省规程性能评价+非线性规程性能评价
	BOOL CalcStruPerformSteelDrift(CArray<int, int>& aRunCase, CLoadCollection& cLoads); //计算钢构件位移角性能
	BOOL CalcStruPerformNonlinearStrain(CArray<int,int> &aRunCase,CLoadCollection &cLoads);//王丹 23.01.2021广东省规程性能评价+非线性规程性能评价
	//计算单工况韧性指标
	BOOL CalcCaseResi(int iCase,float *pBeamStrucPerform,float *pPlateStrucPerform,float *pk,float *prH,float *prD,float *pT,bool bCaseFile,CString sLoadCase);
	BOOL CalcResi84(int n,float *pValue,float &fLnMean,float &fLnStd,float &fValue84);	//韧性评价，计算84%保证率指标
	BOOL CalcResi(CArray<int,int> &aRunCase,CLoadCollection &cLoads,bool bExtend);		//韧性评价
	BOOL CalcResiInfo();	//韧性评价模型信息，导入潘老师韧性评价系统
	BOOL CalcStiffReduction(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcStiffReduction2(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcOneCaseEnvelope(CArray<int,int> &aRunCase,CLoadCollection &cLoads, int nType = FLAG_BIN_DEFAULT);
	BOOL CalcOneCaseCQC(CArray<int,int> &aRunCase,CLoadCollection &cLoads,CString file=L"All");
	BOOL Cal_CQC(float *InPut, int nLen,float *DampRatio, float *ModeT,int ModeNum, float *OutPut);
	BOOL Cal_CCQC(float* pNodalDispQ, float* pNodalDispDQ, int iDofNum, float* pDampRatio, float* pPeriod, int iCModeNum, float* pNodalDispComb);
	BOOL CalcRebarAs(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcRebarML(CArray<int, int>& aRunCase, CLoadCollection& cLoads, CTime& startTime);
	BOOL CalcEnvelopeRebarAs(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//BOOL CalcRebarAsByElm(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL CalcMultiCaseEnvelope(CLoadCollection &cLoads, bool bPI=false, int nType = FLAG_BIN_DEFAULT);//自动多工况包络 邱海 2023年7月4日
	BOOL CF15File2CF5(CArray<int,int> &aRunCase, CLoadCollection &cLoads, const wchar_t *cInName, const wchar_t *cOutName, char *cWriteTitle, CString cWriteName, const wchar_t *cOutName1 = NULL, const wchar_t *cOutName2 = NULL,  bool bSHKB=false);//
	BOOL CalcStoryShiftRespSpectrum(CArray<int,int> &aRunCase,int iFilter,const void *pFilterData,CLoadCollection &cLoads,int iCalcType=3, BOOL bScaleMassFlag=FALSE);
	BOOL CalcStoryShiftFunc(float *pData, float *pAveData, CString sBDSname, int *story_pillar_node, int npillar, BOOL bScaleMassFlag =  FALSE);
	BOOL GetCModePeriod(int &nMode, float *&pPeriod, float *&pDampRatio);
	BOOL CalcStoryShearRespSpectrum(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	BOOL WriteBinStoryFieldSpectrum(const CString &fname, int nItems, float *pData);
	BOOL CalcMemberForceSpectrum(CArray<int,int> &aRunCase, CLoadCollection &cLoads);
	
	//根据单工况包络文件生成多工况单元结果的包络文件
	void GenerateBinElmField_Envelope_MultiLoadCase(const std::vector<int>& vCase, int nEnvType, const CString& sDirName, const CString& sFileName, const CString& sGroup, const CLoadCollection& cLoads, bool bDirectAve = true);
	//根据单工况包络文件生成多工况构件结果的包络文件
	void GenerateBinStruField_Envelope_MultiLoadCase(const std::vector<int>& vCase, int nEnvType, const CString& sDirName, const CString& sFileName, const CString& sGroup, const CLoadCollection& cLoads);
	//生成单工况构件结果的包络文件 按每个分量
	void GenerateBinStruField_Envelope_MultiLoadCase_OneCmp(const std::vector<int>& vCase, int nEnvType, const CString& sDirName, const CString& sFileName, const CString& sGroup, const CLoadCollection& cLoads);
	void GenerateBinField_Envelope_MultiLoadCase(const CLoadCollection& cLoads, int iEnv, bool bPI = false, int nType = -1);

	int AddForce(const CString &fname,CF5Header  &hdr,CF5ElemBlock *pblock,STRUCT_TYPE iType,float* pData,int nComp,
		vector<BEAM_CONN_LAYER> &vBottomBeamElm,vector<SHELL_CONN_LAYER> &vBottomShell,vector<SHELL_CONN_LAYER> &vBottomQuad);

	void TheNumberOfComponents(const CFrame& frame, int& nBeam, int*& pBeam, int& nPlate, int*& pPlate, int iFilter, const void* pFilterData);

	BOOL AddStoryForce(const CString& fname, CF15Header& hdrRead, CF15StruBlock* pblock, float* pData, int nComp, int nBeam, int* pBeam, int nPlate, int* pPlate, float m_fAngle0);

	//生成单工况单元结果的包络文件
	void GenerateBinElmField_Envelope(int iLoadCase, const CString& sTypeName, const CString& sGroup, const CLoadCollection &cLoads);

	//二分法包络找最大值最小值
	void MaxMin(float **ppData, int nCol, int iCol, int nElm, int iElm, int nElmBefore, int iBegin, int nMaxSteps, float &fMax, float &fMin);

	//生成单工况构件结果的包络文件
	void GenerateBinStruField_Envelope(int iLoadCase,const CString& sTypeName, const CString& sGroup, const CLoadCollection &cLoads);

	//生成单工况构件结果的包络文件 按每个分量
	void GenerateBinStruField_Envelope_Force(int iLoadCase,const CString &sTypeName,const CString &sGroup, const CLoadCollection &cLoads);

	BOOL GetSteelSecRes(int nMaxSteps,CElmFieldOneComponent* pElmFieldSet,float* pRes=NULL);
	//钢结构截面验算
	BOOL GetSteelCrossSecStrengthCalc(CString sLoadcase,int &nBeam,float *pRes[2],bool bMesh=false,bool bShowError=false);

	//根据构件两端内力考虑分布力得到n个中间截面内力
	void GetSectForce(CBeamStruc *beam,const SectForce &sf1,const SectForce &sf2,SectForce &sfMid);
	void GetSectForce(CPlateStruc *plate,const SectForce &sf1,const SectForce &sf2,SectForce &sfMid);
	//根据构件及单元得到构件截面内力
	void GetSecForceByElm(int iStruId, int *pElm,SectForce *psf);

	//规范公式应力比计算
	BOOL CalcSecStressRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//规范公式应力比计算,增加工况判断 周璋鑫 2022年12月29日
	BOOL ReCalcSecStressRatio(CArray<int, int>& aRunCase, CLoadCollection& cLoads);

	BOOL WriteStressRatioTxtByStory(CString sResultPath, CPostContainer* pPost, vector< CLoadCase*> pLoadCase);
	BOOL WriteStressRatioTxt(CString sResultPath, CPostContainer* pPost, vector< CLoadCase*> pLoadCase);
	BOOL WriteStressRatioTxtTitle(CString sResultPath);
	BOOL WriteStressRatioTxtForce(SEnvStep* pEnvStep, CString sResultPath);
	BOOL WriteStressRatioTxtCase(vector< CLoadCase*> pLoadCase, CString sResultPath);
	BOOL OpenStressRatioTxt(int ID);
	//BOOL CalcPerformByForce(LOADCASETYPE iType);
	//剪压比计算
	BOOL CalcShearCompressRatio(CArray<int,int> &aRunCase, CLoadCollection &cLoads);
	//剪压比计算,增加构件类型判断,增加输出间隔设置 周璋鑫 2022年12月14日
	BOOL CalcShearCompressRatio(bool& b1DCalc, bool& b2DCalc, CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	//剪跨比计算
	BOOL CalcShearSpanRatio(CArray<int, int>& aRunCase, CLoadCollection& cLoads);
	//剪跨比计算,增加输出间隔设置 周璋鑫 2023年3月6日
	BOOL CalcShearSpanRatio(CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	//名义拉应力计算
	BOOL CalcNominalTensileStress(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//名义拉应力计算,增加构件类型判断,增加输出间隔设置 周璋鑫 2022年12月14日
	BOOL CalcNominalTensileStress(bool& b1DCalc, bool& b2DCalc, CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	//轴压力系数计算
	BOOL CalcAxialTensionCoef(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//轴压力系数计算,增加构件类型判断,增加输出间隔设置 周璋鑫 2022年12月14日
	BOOL CalcAxialTensionCoef(bool& b1DCalc, bool& b2DCalc, CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	//轴压比计算
	//BOOL CalcAxialCompressionRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//抗剪承载力计算
	BOOL CalcShearStress(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//抗剪承载力计算,增加构件类型判断,增加输出间隔设置 周璋鑫 2022年12月14日
	BOOL CalcShearStress(bool& b1DCalc, bool& b2DCalc, CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	//抗弯承载力计算
	BOOL CalcMomentStress(bool& b1DCalc, bool& b2DCalc, CArray<int, int>& aRunCase, CLoadCollection& cLoads, const float fCalcTime);
	BOOL CalcFlexuralBearingCapacity(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//弯剪比计算
	//BOOL CalcMomentShearRatio(CArray<int,int> &aRunCase,CLoadCollection &cLoads);
	//广东省规程构件位移角
	BOOL CalcDispAngleGD(CArray<int, int> &aRunCase, CLoadCollection &cLoads, bool bSHKB=false);//广东省位移角计算试做

	BOOL CalcDispAngleXue(CArray<int, int> &aRunCase, CLoadCollection &cLoads);//薛总位移角计算试做

	//siya 抗爆后处理
	BOOL CPost::CalcDuctilityRatioBlast(CArray<int, int>& aRunCase, CLoadCollection& cLoads);
	void CPost::GetGroupRange(const vector<int> vStruct, Vector4& rMin, Vector4& rMax);

	//乔保娟临时代码
	BOOL CalcRebarAsv();
	BOOL Edge2Col();

	//贾工dll提取函数
//输出信息
	//void PrintMsg(string str, string m_sDir);
	
	//BOOL TractBySSGMesh(int Num, BEAM_FIBRE_GEO *pConcFibreBuf, int nConcFibre, BEAM_FIBRE_GEO *pRebarFibreBuf, int nRebarFibre, BEAM_FIBRE_GEO *pSteelFibreBuf, int nSteelFibre, float fConcFc, float fRebarFy, float fSteelFy, int *MatType,int Method, CTract *pTract, PmmData *ppmmData);//, string sPath);
	//void TractWriteFile(CTract *m_cTract, string m_sDir);

	bool CalcPerformance(float P, float Mx, float My, float *M, vector<PmmData*> &m_Data);

	//计算构件的极限内力
	bool CalcMaxMoment(float P, float Mx, float My, int MatType, float *M, vector<PmmData*> &m_Data);

	float dot(float *p0, float *p1);//王丹 2021.03.08

	bool IsPointInPoly(float *p0, float **Poly);//王丹2021.03.08

//从App 传过来
	BOOL m_bSecondCalIsoBeta;
	BOOL m_bSecondCalElastic;

	void SetSecondCalIsoBeta(BOOL);
	void SetSecondCalElastic(BOOL);

	bool CalcPushover(float &M1,float &Coef,int NodeId,int IDir);

	//计算长度系数 2023.2.27贾苏
	BOOL CalcMemlengthcoef(int iMemberID, int iDir, CString sCaseName, int iMode = 0);
	float GetMemberForce(int iMemberID, CString fname);

	BOOL MemberPerformStatistics(CElmFieldOneComponent* pElmFieldSet, float fTime, std::vector<std::vector<int>> vPerform[7], const CSSGData* pMultiplyData = NULL,BOOL bIsMultiModel = FALSE); // pMultiplyData 多模型方案使用

	//韧性评价后处理接口函数 贾苏20240125
	BOOL WriteResEDPfile(CLoadCase* pLoad, CString fname);
	BOOL WriteResEDPfileStruc(CLoadCase* pLoad, CASCFile* fout);
	BOOL WriteResEDPfileStory(CLoadCase* pLoad, CASCFile* fout);
	BOOL WriteResBinResult(CString sLoadCase);
};

extern _POST_DLLIMPEXP CPost thePost;
