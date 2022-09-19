#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "..\Common\SysPara.h"
#include "PublicFunc.h"
#include "ASCFile.h"
#include "Data.h"
#include "LoadCase.h"
#include "DamperGroupData.h"
#include "VisibleStruct.h"
#include "CombineFrame.h"
#include "PlateSection.h"
#include "GeneralLoad.h"
#include "Load.h"
#include "WindLoad.h"
#include "NonISOModel.h"
#include "RSfunction.h"
#include "RSLoadCase.h"
#include "StaticLoadCase.h"

#include "DataSolidStruc.h"

#define ID_TEST_FUNC1					60001
#define ID_TEST_FUNC2					60002
#define ID_TEST_FUNC3					60003
#define ID_PLUGIN_FUNC1					60004
#define ID_PLUGIN_FUNC2					60005
#define ID_PLUGIN_FUNC3					60006
#define ID_PLUGIN_FUNC4					60007
#define ID_PLUGIN_FUNC5					60008

//�ӳ��߽�������
enum EXT_TYPE
{
	EXT_NONE,          //�����߶ε��ӳ����޽���
	EXT_INNER,         //�ӳ��߷�������Ŀ���߶������ڲ�����
	EXT_EXT,           //�ӳ��߷�������Ŀ���߶����н���
	EXT_RESERVE_INNER, //�ӳ��߷���������Ŀ���߶������ڲ�����
	EXT_RESERVE_EXT,   //�ӳ��߷���������Ŀ���߶����н���
};

struct ID_STAGE
{
public:
	int id;
	int iStage;
	static bool Compare(const ID_STAGE &a,const ID_STAGE &b)
	{
		return (a.iStage<b.iStage); 
	};
};

//��ܽṹ��
class _SSG_DLLIMPEXP CFrame : public CRemoveInvalidPrimitive
{
public:
	CFrame(void);
	CFrame(const CFrame &frame) {*this=frame;}
	~CFrame(void){Clear();} 

public:
	float m_fVer;  //�汾��,�Ϸ�ֵ1.1,2.0���˰汾��Ϊ����������ļ��汾�ţ�д���ļ��󽫱��ı�
	float m_fExeVer; //2021��630��ʱ�жϰ汾

	//��������
	CArray<CVertex,CVertex&> m_aVex;   //������,���п��ͼԪ���㹲�ø����飬����������������桢������������
	CArray<CLine,CLine&>  m_aLine;     //�ṹ������

	//�ṹ����
	CArray<CBeamStruc,CBeamStruc&>  m_aBeam;    //��������б�ŵ�����
	CArray<CLine,CLine&> m_aGuides;				//����������
	CArray<CPlateStruc,CPlateStruc&> m_aPlate;	//���ǽ���飬�洢¥�塢ǽ��ṹ

	//Sigma 1.0
	std::vector<CSolidStruc> m_vSolid;				//ʵ��

	CSectionCollection m_cSection;					//������Ϣ
	CDamperSectionCollection m_cDamperSection;		//һ�����ӽ�����Ϣ	//�Ǳ��� 2015.5.19
	CDamperGroupSecCollection  m_cDamperGroupSec;	//���𹹼���  �� 2016��10��27��
	CPlateSectionCollection m_cPlateSection;		//�湹��������Ϣ
	CMaterialCollection m_cMaterial;				//������Ϣ
	//��ʱʹ�ã�tendonʹ�ü����vector
	vector<int> m_cMaterialTendon;
	CEdgeStrucCollection m_cEdgeCollection;			//��Ե������Ϣ,Ϊ����ʾ��Ե������ǽ���ɹ�ϵ��
	CBoundaryCollection m_cBoundary;				//�߽�������Ϣ
	CNonISOModel m_cNonISOModel;					//�Ǹ���ģ�Ͳ���

	//������Ϣ
	CStageCollection m_cStage;   //�ֲ�ģ����Ϣ����ģ�Ͱ��ս�����̷ֳ����ɲ��֣�����ύ����
	CGroupCollection m_cGroup;
	CGroupCollection m_cDamperGroup;

	//������Ʋ���
	float m_fElmSize;			//���������ߴ�
	float m_fAlphaPlate,m_fBetaPlate;		//¥���������ɲ���
	float m_fAlphaWall,m_fBetaWall;		//ǽ���������ɲ���
	int m_nWallBeamLayer;
	float m_fWallBeamLayerSize;
	float m_fWallBeamLayerMinSize;
	BOOL m_bAntiBeamPillarAsOne;
	BOOL m_bAlongBraceAsOne;

	//�������Ʋ���
	BOOL m_bScaleIrrMass;
	BOOL m_bScaleSelectedMass;
	BOOL m_bScaleIrrByFactor;

	float m_fScaleFactor;	//��ʱû��
	float m_fMinTriAngle;	//û��
	float m_fMinQuadAngle;	//û��
	float m_fMinLength;
	float m_fMinTriArea;
	float m_fMinQuadArea;

	//��Ŀͨ�ò���
	CString m_sCurCase;  //��ǰ����(���)����

	//���Ը�����Ϣ
	int m_nRigidBody;	//������
	int *m_pRigidBody;	//���ĵ���


	//�������
	BOOL m_bStatic;				//�Ƿ������
	BOOL m_bExplicitStatic;		//�Ƿ���ʽ��������
	BOOL m_bDynamic;			//�Ƿ�������
	BOOL m_bExplicitDynamic;	//�Ƿ���ʽ��������
	BOOL m_bMaxFreq;			//�Ƿ������Ƶ��
	BOOL m_bModeAnalysis;		//�Ƿ�ģ̬����
	BOOL m_bModeAnalysisDamage;		//�Ƿ�ʵʱģ̬����

	//��ʽ�������ز���
	BOOL m_bUseRebar;	//�Ƿ����ֽ�����
	UINT m_iMaxSteps; // ������������5000
	float m_fStaticTol;// �������� ��0.00001

	//��ʽ�������ز���
	float m_fStaticTimeStep;   //������ʽ����ģ���������ص�ʱ�䣬������ʽ��������������ؼ��أ���Ч

	//��ʽ�������ز�����Ŀǰ���ṩ

	//�������Ƶ�ʷ�������Ч
	UINT m_iMaxFreqSteps; //=10000;���Ƶ�ʵĵ�������
	float m_fMaxFreqTol; //=0.0000001;���Ƶ�ʵ��������ȣ���Ծ��ȣ�

	//ģ̬�������Ʋ���
	float    		m_fMinFreq;     //����ֵ����;0
	float    		m_fMaxFreq;     //����ֵ����;5000
	UINT			m_nModes;		//������
	UINT			m_iModalAnalysisMethod;		//������
	float			m_fWallBeamReductCoef;		//�����ն��ۼ�ϵ��
	BOOL			m_bX;		//�������÷���
	BOOL			m_bY;		//�������÷���
	BOOL			m_bZ;		//�������÷���
	int				m_nLancSteps;		////lanczos���̵ĵ�������;500
	BOOL	  		m_bEvalVec;     //�Ƿ������������;false
	BOOL			m_bFilterLocal;		//�������÷���
	BOOL      m_bCalcuNonIso;//��ʽ����ͬʱ����Ǹ���ģ�� V2021
	BOOL        m_bCalSubStru; //  ��ʽ����ͬʱ���������ṹ�²��ṹ  ���ڸ�ģ̬������װ�Ǳ����������  ��˼�� 20210602
	//����ȱ��
	float m_fOverallImperfect;	//ȱ�����ֵ
	float m_fImperfectAngle;//ȱ�ݽǶ�
	int m_iOverallImperfectMode;

	//��ʽ��������
	CLoadCollection m_cLoad; //���ع�����ϼ���
	CLoadCollection m_cLoadDesign; //���ع�����ϼ���,�������
	CLoadCollection m_cLoadStatic; //�����Ծ�������
	CLoadCollection m_cLoadElastic; //��Ч���Է���
	//CLoadCollection m_cLoadGenTH; //ͨ��ʱ�̷���
	//CLoadCollection m_cLoadPush; //��ʽ�����Ƹ�
	CWaveCollection m_cWave; //����ѡ���𲨼���
	CFunctionCollection m_cFunc;//ʱ�̺���
	//CLoadSet m_cLoadSet;//���ؼ���

	int   nModalDamage;       //����ʵʱģ̬�����Ĵ��� //�Ǳ���2015.12.25
	CString sModalCaseName[Sys_Max_ModalDamage];	//ʵʱģ̬������������	
	float fModalTime[Sys_Max_ModalDamage];	//ʵʱģ̬����ʱ�� 
	//������������ȡ���������ڱ���Read��
	CArray<COutput,COutput&> aOutput; //����ķ�����
	float fDisStep,fForceStep,fGroupStep;


	CGeneralCollection m_cGenLoad; //���ع�������:1��1��1��1����

	//2020��11��6�� �������ع������������
	CStaticLoadCaseCollection m_cStaticLoad;
	CDynamicLoadCaseCollection m_cDynaLoad;
	CLoadCaseCombCollection m_cLoadComb;

	CWindCollection m_cWindLoad; //����ع�������
	CRSFunctionCollection m_cRSFunction;
	CRSLoadCaseCollection m_cRSLoadCase;

	//��������
	UINT m_nBucklingModes;		//������
	BOOL m_bBucklingOverallDefect;
	BOOL m_bBucklingMemberDefect;

	// ��ģ̬�������Ʋ���  ��˼�� 20210526
	BOOL m_bParaInput;
	BOOL m_bParaIter;
	BOOL m_bParaTHA;
	BOOL m_bDireComb;
	int  m_iCModeNum;
	int m_iCalcMethod;
	int m_iDampType;
	float m_fPeriodGround;
	float m_fAlphaMax;
	float m_fStruDampRatio;
	vector<CString> m_vSpectCase;
	int m_iAngleNum;
	vector<float> m_vAngle;
	int m_iCaseNum;
	//�������Ʋ���

	//��λ���Ʋ���
	//bit0-�Ƿ���ǽ����������Ԫ0x01
	//bit1-ǽ�������ʷ�����0x02
	//bit2-���ɵ�Ԫʱ��������Զ���֧0x04
	//bit3-�Ƿ�������0x08,����������أ������ؼӵ�fext��,����ֻ����mass
	//bit4-���������תΪ����0x10,���Ϊ1��������ؼӵ�mass��,����ֻ����fext
	//bit6~bit8,��������ͣ�7--SSG�����,0--PARDISO�����,1--MUMPS�����
	DWORD m_dwControl; 

	BOOL IsExtentBeam()				const {return m_dwControl&0x01?TRUE:FALSE;}
	BOOL IsBeamWallDoubleLayer()	const {return m_dwControl&0x02?TRUE:FALSE;}
	BOOL IsBottomBnd()				const {return m_dwControl&0x04?TRUE:FALSE;}
	BOOL IsSelfWeight()				const {return m_dwControl&0x08?TRUE:FALSE;}
	BOOL IsExLoad2Mass()			const {return m_dwControl&0x10?TRUE:FALSE;}
	BOOL IsOffsetFlag()				const {return m_dwControl&0x20?TRUE:FALSE;}

	void SetExtentBeamFlag(BOOL bFlag)			{if(bFlag) m_dwControl |=0x01;else m_dwControl &=~0x01;}
	void SetBeamWallDoubleLayerFlag(BOOL bFlag)	{if(bFlag) m_dwControl |=0x02;else m_dwControl &=~0x02;}
	void SetBottomBndFlag(BOOL bFlag)			{if(bFlag) m_dwControl |=0x04;else m_dwControl &=~0x04;}
	void SetSelfWeightFlag(BOOL bFlag)			{if(bFlag) m_dwControl |=0x08;else m_dwControl &=~0x08;}
	void SetExLoad2MassFlag(BOOL bFlag)			{if(bFlag) m_dwControl |=0x10;else m_dwControl &=~0x10;}
	void SetOffsetFlag(BOOL bFlag)				{if(bFlag) m_dwControl |=0x20;else m_dwControl &=~0x20;}


	void SetDeviceType(DEVICE_TYPE device)
	{
		m_dwControl &= ~DEVICE_MASK;
		if(device==DEVICE_CUDA) m_dwControl |= DEVICE_CUDA ;
		if(device==DEVICE_OMP) m_dwControl |= DEVICE_OMP ;
	}

	DEVICE_TYPE GetDeviceType() const
	{
		if(m_dwControl &DEVICE_CUDA) return DEVICE_CUDA;
		if(m_dwControl &DEVICE_OMP) return DEVICE_OMP;
		return DEVICE_CUDA;
	}

	//���λ�ƽ�λ����Ϣ
	int m_nDriftPos;  //λ�ø���
	CVertex m_DriftPos[Sys_MaxDriftNum];  //λ�����ֻ꣬ʹ��x,y,z

	//�洢�ڵ����ļ��У�FILE_VISIBLEINFO
	CVisibleStruct m_cVisible;  //ģ�Ϳɼ�����

	//�洢�ڵ����ļ��У�FILE_COMBINEFRAME
	CCombineFrameCollection m_cCombine;  //������Ϲ��������ڼ�����Ϲ�����������������ʱ�������ݣ�ģ�ͽ���ʱ�������

	//��ʱ����
	//���ļ���ʱ��ֵ�����ھֲ�����������±�ת��
	int m_nBeam,m_nPillar,m_nBrace,m_nEdge;
	int m_nLink;	//�Ǳ��� 2015.5.19
	int m_nPlate,m_nWallCol,m_nWallBeam;
	
	int m_nTowers; //������=�������+1��Ҫ����������

	int m_nSolid;	//sigma 1.0ʵ��
	bool AddSolidByFaceVertex(const int *vex, int nvex, const int *face, int nface, int iStory, const CStory *pStory);
	bool AddSolid(CSolidStruc &newsolid, int *nNewSolid = NULL, int *pNewSolidID = NULL);
public:
	////////////////��������////////////////

	CFrame & operator=(const CFrame &frame);

	void Clear();  
	//ɾ������������SSG���м��ļ�
	void RemoveAllIntFile(void);
	//ɾ�����м������ļ�,sPrjName��Ŀ�ļ�
	void RemoveAllResultFile(void);	//qiao
	BOOL IsVersion10() {return m_fVer<2.0f-0.01f;}	//1.0��1.1�汾
	BOOL IsVersion20() {return (m_fVer>2.0f-0.01f&&m_fVer<2.0+0.01f);}	//2.0 //3.1�汾
	BOOL IsVersionBigEqual20() {return (m_fVer>2.0f-0.01f);}
	BOOL IsVersion32() {return (m_fVer>3.2f-0.01f&&m_fVer<3.2+0.01f);}	//3.2   //2016�汾
	BOOL IsVersionBigEqual32() {return (m_fVer>3.2f-0.01f);}
	BOOL IsVersionBigEqual2017() {return (m_fVer>2017.0f-0.01f);}
	BOOL IsVersionSmallThan2018() {return (m_fVer<2018.0f-0.01f);}
	BOOL IsVersionBigEqual2018() {return (m_fVer>2018.0f-0.01f);}
	BOOL IsVersionBigEqual2019() {return (m_fVer>2019.0f-0.01f);}
	BOOL IsVersion2019() {return (m_fVer>2019.0f-0.01f&&m_fVer<2019.0f+0.01f);}
	BOOL IsVersionBigEqual2020() {return (m_fVer>2020.0f-0.01f);} 
	BOOL IsVersionBigEqual20202() {return (m_fVer>2020.2f-0.01f);} 
	BOOL IsVersionBigEqual20203() {return (m_fVer>2020.3f-0.01f);} 
	BOOL IsVersionBigEqual20204() {return (m_fVer>2020.4f-0.01f);} 
	BOOL IsVersionBigEqual20205(){return (m_fVer > 2020.5f - 0.01f);}
	BOOL IsVersionBigEqual20206(){return (m_fVer > 2020.6f - 0.01f);}
	BOOL IsVersionBigEqual20207(){return (m_fVer > 2020.7f - 0.01f);}
	BOOL IsVersionBigEqual2021(){return (m_fVer > 2021.0f - 0.01f);}
	BOOL IsVersionBigEqual2022630(){return m_fExeVer > 2022.0f - 0.01f;}
	BOOL IsVersionBigEqual2022(){return m_fVer > 2022.0f - 0.01f;}
	////////////////��ģ����////////////////

	//�����߶�,�����뽻���ͷָ���
	//���룺newline--���߶�, pStory--¥������
	//�����nNewSegment--���߱��ֳɵ��߶���,ָ��,pNewSegmentIDΪNULLʱ�����������
	//      pNewSegmentID--���߶ε�ID����,���ⲿ����ά��,�����㹻��,pNewSegmentIDΪNULLʱ�����������
	void AddStructLines  (CLine &newline,const CStory *pStory,int *nNewSegment,int *pNewSegmentID,BOOL bBreakByStory=TRUE); //���ӽṹ��
	BOOL AddStructLinesInStory(const CVertex &v1,const CVertex &v2,const int iStory,int *nNewSegment=NULL,int *pNewSegmentID=NULL);  //�����������������ӽṹ��,2������ܲ���ͬһ¥�㣬�������Ķ˵�
	void AddGuides(CLine &newline,const CStory *pStory,BOOL bBreakByStory=TRUE); //���Ӹ�����
	void AddGuidesInStory(const CVertex &v1,const CVertex &v2,const int iStory); ///�����������������Ӹ�����,v1,v2���봦��ͬһ¥��,��Ҫ�ж϶˵��Ƿ����,��v1,v2���ܴ���������
	void AddGuidesInStory(CLine &line); //���Ӹ�����,line�Ķ˵���봦��ͬһ¥��,�����ж϶˵��Ƿ����

	//ֱ�������������������������������㣬��Ҫ����ֲ����꣬���������±�
	int AppendBeam(CBeamStruc &newbeam);

	//ֱ�������������Ӱ��ǽ�������������㣬��Ҫ����ֲ����꣬���������±�
	int AppendPlate(CPlateStruc &newplate);

	//���룺newplate--�°�ṹ
	//�����nNewPlate--�°屻�ֳɵİ����������ָ�ʱΪ1,ָ��,nNewPlateΪNULLʱ�����������
	//      pNewPlateID--�°��ID����,���ⲿ����ά��,�����㹻��,pNewPlateIDΪNULLʱ�����������
	BOOL AddPlate(CPlateStruc &newplate,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//��plateid1��������������������
	void PlateCross( int plateid1,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//������¥���������,������涨����ǽ,�ɹ�����TRUE
	BOOL AddWall(const CVertex &vex1,const CVertex &vex2,int iStory,const CStory *pStory);
	//����nvex�����x,y���괴��ǽ,�ɹ�����TRUE
	BOOL AddWall(const int *vex,int nvex,int iStory,const CStory *pStory);

	//�ѵ���ӵ��ṹ�ϣ�������Ƿ���ĳ�ṹ�߻����ϣ�����ǣ���Ҫ�޸Ľṹ
	//���iLineType=1����ӵ����������棬���iLineType=2����ӵ��ṹ�����棬�����޸���صĽṹ
	//���룺pointID--��ID
	void CrossVertex(int pointID,int iLineType);
	void CrossVertex(const CVertex &vex,int iLineType);

	BOOL DeleteVex(int id); //���ݵ�ID�ж��Ƿ�õ��Ƿ��ǹ�����,������Ϊ��Ч,�ɹ�ɾ������TRUE
	void DeleteGuides(int id); //ɾ�������ߣ��Լ���صĹ�����
	BOOL DeleteLine(int id); //ɾ�����õĽṹ�ߣ��Լ���صĹ�����,�ɹ�ɾ������TRUE
	void DeleteBeam(int id); //ɾ���������ṹ���Լ���صĹ����ṹ�ߺ͵�

	void DeletePlate(int id); //ɾ�����ǽ���Լ���صĹ����ṹ�ߺ͵�
	void ReplaceVertex(int discard_vex,int reserve_vex);  //��discard_vex�����reserve_vex�滻��ͬʱɾ��discard_vex,ֻ������߽ṹ���м򵥴��棬��������˽ṹ�仯
	void MergeVertex(int discard_vex,int reserve_vex); //���ɵ����µ�ϲ��������µ㣬��ɵ����滻���������˹�ϵ�ı仯�������˻����ߺ��桢�Լ���ع���
	void SpliteBeam(int nSel,const int *pSelNames, int nSegments);  //����ѡ�߹�����֣��õ�ѡ��

	BOOL MergeCoinVertex(float fError = g_cSysSizePara.Sys_PointError); //�кϲ�����TRUE

	void RearrangeID();  //������ЧͼԪ	
	void RearrangeBeam(); //��Ҫ���������߹���˳����(�����������ݽ�)---��---��---��Ե����
	void RearrangePlate(); //��Ҫ���������湹��˳�򣺰�--ǽ��--ǽ��

	////////////////��ȡ���Ժ���////////////////

	/////////////////////////////////////////////////////
	//�������裺 2012/11/13
	//����㲻���ص����ṹ�߿����ص����߹������ڽṹ�߿����ص�
	//һ���ռ�λ��ֻ����һ����
	//��������Զ�������ṹ��
	//������ֻ�ܶ���һ��������
	//ÿ���ṹ����ֻ����һ���߹���
	/////////////////////////////////////////////////////

	//��������Զ��壺X,Y,DZ�ֱ����
	int GetSimilarVertex(int pointid,int iStory); //��������pointid��XY����Z(=¥����-���Z����)������ָ��¥��Ѱ�ҿ������ID��û�ҵ�����-1
	int GetSimilarVertex(float x,float y,float dz,int iStory); //��������XY����Z(=¥����-���Z����)������ָ��¥��Ѱ�ҿ������ID��û�ҵ�����-1
	int GetSimilarGuideLine(int lineid,int iStory);  //��������ID�ҵ���Ӧ¥������Ƶĸ�����ID��û�ҵ�����-1
	
	int GetSimilarLines(int lineid,int iStory,int *pLineIDs,int maxsize); //��������ID�ҵ���Ӧ¥������ƵĽṹ��IDs�������߶θ���
	int GetFirstSimilarLine(int lineid,int iStory);  //��������ID�ҵ���Ӧ¥������ƵĽṹ��ID���˵����������ԣ�û�ҵ�����-1

	int GetSimilarBeams(int beamid,int iStory,int *pBeamIDs,int maxsize); //������������ID�ҵ���Ӧ¥������Ƶ�������ID���ṹ�����������ԣ�Ҫ��ṹ������ͬ�����ع�������
	int GetFirstSimilarBeam(int beamid,int iStory);  //������������ID�ҵ���Ӧ¥������Ƶ�������ID���ṹ�����������ԣ�Ҫ��ṹ������ͬ��û�ҵ�����-1

	int GetSimilarPlate(int plateid,int iStory);  //�����İ��ǽID�ҵ���Ӧ¥������Ƶİ��ǽID���ṹ�����������ԣ�û�ҵ�����-1

	int GetVertexID(float x,float y,float z);  //�����������������������ID��û�ҵ�����-1
	int GetVertexID(const CVertex &v);   //�����������������������ID��û�ҵ�����-1
	int GetVertexID(const Vector4 &v);   //�����������������������ID��û�ҵ�����-1
	int GetLineIDs(int idP1, int idP2,int *pLineIDs,int maxsize); //���ݵ�ID�ҵ��ṹ��IDs,�����߶θ������߶�ID����pLineIDs��
	int GetFirstLineID(int id1, int id2); //���ݵ�ID�ҵ������ĵ�һ����ID--heby,δ�ҵ��򷵻�-1�������жϵ�����

	int GetGuidesID(int id1, int id2);  //���ݵ�ID�ҵ�������ID,δ�ҵ��򷵻�-1
	int GetBeamID(int lineid);      //��������ID �ҵ�ʹ�������ṹ�ߵ���������ID��û�ҵ�����-1
	int GetPlateIDs(int lineid,int *pPlateIDs,int maxsize) const;  //��������ID���ҵ�ʹ�������ṹ�ߵİ��ǽ��ID�����ظ�������ID������pIDs��
	int GetPlateID(const CPlateStruc &plate);   //������ļ������ݣ����ذ��ǽ��ID��û�ҵ�����-1

	float GetInclineCos(const CLine &line);  //�õ��ṹ�ߵ��������(�׵�ָ��ĩ���ʸ����Z��ļн�)����Χ��-1 -- 1	
	float GetInclineCos(const CBeamStruc &beam);  //�õ��ṹ���������(�׵�ָ��ĩ���ʸ����Z��ļн�)����Χ��-1 -- 1
	float GetInclineAngle(const CLine &line);  //�õ��ṹ�ߵ����(�׵�ָ��ĩ���ʸ����Z��ļн�)����λ�����ȣ���Χ��0--PI
	float GetInclineAngle(const CBeamStruc &beam);  //�õ��ṹ�����(�׵�ָ��ĩ���ʸ����Z��ļн�)����λ�����ȣ���Χ��0--PI

	float BeamLength(int id);  //�����߹�������
	float BeamLength(CBeamStruc &beam);  //�����߹�������
	float PlateArea(int id);   //�����湹�����
	float PlateArea(CPlateStruc &plate);   //�����湹�����
	float GetMinMax(Vector4 &MinCoor,Vector4 &MaxCoor); //�������ֱ��
	//�����湹�����귶Χ��������С¥���
	int GetPlateMinMax(int plateid,CVertex &MinCoor,CVertex &MaxCoor);
	int GetPlateMinMax(CPlateStruc &plate,CVertex &MinCoor,CVertex &MaxCoor);

	//�õ�����ʩ���׶ε�ͼԪ����
	//vBeam,vPlate--���ÿ��ʩ���׶εĹ������
	void GetStepStruct(vector<int> vBeam[],vector<int> vPlate[],int nStory); 

	//�õ����Ͽ⵽ʹ�ÿ����������ʹ�ÿ⵽���Ͽ����������������ָ����õ��Ĳ������Ƽ��ϣ����ó�����Ҫ���������ֵΪʹ�ÿ�Ĳ�����
	int GetUsedConc(int *&pIndexOfLib2Used,int *&pIndexOfUsed2Lib,CStringArray &aConcList);  //������
	int GetUsedSteel(int *&pIndexOfLib2Used,int *&pIndexOfUsed2Lib,CStringArray &aSteelList); //����,�������͸ֺ͸ֽ����

	//ͳ�Ƹ��ֹ���������
	STRUCT_COUNT GetStructCount(void) const;	

	//�����㵽ǽ������,����¼�ṹ���Ƿ�����ǽ�õ�
	void GetWallConnection(CPointWallIndex *pPointConnect,LINE_USED *pLineUsed) const;

	//�ҵ������湹�����϶��������������˵㣬ȥ���м��
	//���أ�TRUE--���컨�����(��ָ�߳�)��FALSE--�����컨�����(��ָ�߳�)
	//���϶��ߣ����컨����ӣ�id1,id2��Ч������TRUE
	//���϶��ߣ������컨����ӣ�id1,id2��Ч������FALSE
	//û���϶��ߣ�һ�������컨����ӣ�id1��Ч,id2=-1������TRUE
	//û���϶��ߣ������컨����ӣ�id1,id2=-1������FALSE
	BOOL GetTopPoint(const CPlateStruc &plate,int &id1,int &id2) const;

	//�ҵ������湹�����¶��������������˵㣬ȥ���м��
	//���أ�TRUE--��ذ����(��ָ�߳�)��FALSE--����ذ����(��ָ�߳�)
	//���¶��ߣ���ذ���ӣ�id1,id2��Ч������TRUE
	//���¶��ߣ�����ذ���ӣ�id1,id2��Ч������FALSE
	//û���¶��ߣ�һ������ذ���ӣ�id1��Ч,id2=-1������TRUE
	//û���¶��ߣ�����ذ���ӣ�id1,id2=-1������FALSE
	BOOL GetBottomPoint(const CPlateStruc &plate,int &id1,int &id2) const;
	
	//���߽�˳�򷵻��ĸ��ǵ�ID�����¡����¡����ϡ�����
	BOOL GetCornerPoint(const CPlateStruc &plate,int &left_bottom,int &right_bottom,int &right_top,int &left_top) const;

	//�ҵ�ǽ����������������IDs,������������Σ���vDown.size()=0,������������Σ���vUp.size()=0
	//vLeft,vRight,vUp,vDown,ÿ�����߶α��(�ֱ�Ϊ���ҡ��ϡ���)��ÿ��ǽ���������
	//�߶α�Ű���һ�µ�����������vLeft--vDown--vRight--vUp--vLeft���߶�IDһ����β��ӣ�ĳ������Ϊ0ʱ��Ҫ����
	//֧���м���ǽ
	//���ر���
	int GetWallEdge(int wallid,vector<int> &vLeft,vector<int> &vRight,vector<int> &vUp,vector<int> &vDown);
	int GetWallEdge(CPlateStruc &wall,vector<int> &vLeft,vector<int> &vRight,vector<int> &vUp,vector<int> &vDown);

	//�ҵ���¥��õ�����������ṹ��(��б���õ��ĳ���)�������Ƿ���ǽ�ı߽�
	void GetLinesByVex(int vexid,list<int> &vLines);
	void GetLinesByVex(int vexid,int &nlines,int *pline);

	//�����㵽���ӵ����ӹ�ϵ��������Ե����������
	PT2LINESTRUCT *CreatePt2Pillar(void);	

	//��ֱ�����湹���Ľ������ڶ�����ڲ����߶Σ�
	//����ֱ�ߵ�������v1,v2
	//���ص��߶ζ˵����p1,p2
	BOOL GetIntersectionLine(CVertex v1,CVertex v2,CPlateStruc &plate,CVertex &p1,CVertex &p2);

	////////////////�������Ժ���////////////////

	void Set2ndBeam(int nSel,const int *pSelNames,BOOL b2ndBeam); //����ѡ�������óɴ���

	////////////////���ݼ�麯��////////////////

	BOOL IsValidPlateLine(int lineid);	//�жϽṹ���Ƿ�����γɰ�
	int CheckStage(int nStory);  //����޸Ľ׶����õ���Ч�ԣ����ؽ׶���

	//�Ƿ�ǽ���������Сz��������¥��߶ȣ����Ҷ����͵ײ�Ϊֱ�ߵ�ǽ
	BOOL IsBeamWall(const CPlateStruc &plate) const; 
	BOOL IsBeamWall(int idm);
	//����ǽ��������ֵ��0--����ǽ����1--ǽ����2--δ֪
	int TraceBeamWall(const CPlateStruc &plate,vector<int> &vBraceLine,float &minz,float &maxz) const; 
	// 1-������¥��������0-�ײ���¥��������-1-����¥������
	int BeamWallPos(const CPlateStruc &plate) const; //qiaobaojuan 2016.3.21


	////////////////�����������////////////////

	BOOL Read(CString fname,CProjectPara cPrjPara,BOOL bOnlyModel=FALSE);
	BOOL Write(void);
	BOOL Write2020(void);
protected:
	

public:
	BOOL MergeSSG(CString fname, float dx, float dy, float dz, float angle);

	//����Լ������ı��߶η���ˮƽ������Ϊ��������������Ϊ�������أ�TRUE-�޸ģ�FALSE-δ�޸�
	BOOL CheckLine( int iLine,float fTanAng );	
	BOOL CheckLine( CLine &line,float fTanAng );

	//iLineType=1,���ӵ�m_aGuides��iLineType=2���ӵ�m_aLine��newline���Կ�¥��
	void AddLinesMulStory(int iLineType,const CLine &newline,const CStory *pStory,int *nNewSegment=NULL,int *pNewSegmentID=NULL,BOOL bBreakByStory=TRUE); 

	//��AddLinesMulStory���ã������ǰ�¥��Ͽ���//iLineType=1,���ӵ�m_aGuides��iLineType=2���ӵ�m_aLine
	void AddLinesInStory(int iLineType,const CLine &newline,int *nNewSegment=NULL,int *pNewSegmentID=NULL); 

	//�Ͽ��ṹ�ߣ����޸���Ӱ��Ĺ�����idOldLine--ԭ�߶�IDM��newpoint--�ضϵ�IDM
	void BreakLine(int idOldLine,int newpoint);

	//�Ͽ������ߣ���Ӱ�칹����idOldLine--ԭ�߶�IDM��newpoint--�ضϵ�IDM
	void BreakGuides(int idOldLine,int newpoint);

	//�и����Σ�plateid--ԭ�����ID��lineid--�߶ε�ID
	LINE_CROSS_POLY BreakPlate(int lineid,int plateid);

	//������ά�ռ������߶ν��㣬ͬʱ���߱�����Ͽ������޸���ؽṹ�������������ߵ����߶�
	//���룺iLineType=1�����ߣ�iLineType=2�ṹ�ߣ�idP1,idP2Ϊ���߶˵�ID��lineidΪ�߶�ID
	//�����������nCross(���Ϊ2��������idP1,idP2),����ID����pCross[2]
	//����ֵ��1Ϊ���߶��ཻ��1�㣬0���ཻ��2�����߲����غϣ�-1��������һ���˵��غ��Ҳ����ߣ�-2��������ȫ�غ�
	int LineCross3D(int iLineType,int idP1,int idP2,int lineid, int &nCross,int *pCross,int maxcross);

	//���ܣ�������ά�ռ����߶������ཻ�����ָ���
	//���룺lineidΪ�߶�ID��idPlateΪ��ṹID
	//����ֵ�� LINE_CROSS_POLY
	LINE_CROSS_POLY LineCrossPolygon3D(int lineid, int idPlate,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//������ĩ���Լ�Ŀ���߶Σ������ӳ��߽�����ĩ��ľ��루��ֵ��ʾ�������ӳ��ߵ��෴���򣩣������������ext_point��
	float GetExtendCrossPoint(const CVertex &start_point,const CVertex &end_point,const CLine &line,Vector4 &ext_point,EXT_TYPE &iType);


	//���ݹ�����Ϣ�������ߵĽ׶Ρ����š�¥��
	void UpdateGeoInfo(void);

	//����¥����Ϣ�������ɵ�Ŀ������
	void UpdateVertexCrossInfo(void);


	BOOL FindVex(int vexid,int plateid);   //�������Ƿ����湹���߽���
	
	//�ý׶����ݸ��¹����Ľ׶κţ����ý׶κͶ�������ʱʹ��
	void UpdateStage(int nStory);

	//���ݵ�����Ϣ���¹�����Ӧ������Ϣ
	BOOL UpdateLoadCaseWaveData(CArray<int,int> &aRunCase,CLoadCollection &cLoads,bool bCheckWave=false);

	//����Static���Ƶõ���Ӧ��Id��
	int GetStaticCaseIdByName(CString sName);
	//����Static���͵õ���������
	CString GetStaticCaseTypeName(STCASE_TYPE nType);
	//����Static�������Ƶõ�����
	STCASE_TYPE GetStaticCaseType(CString sName);
	//���㶯�����ع�����ʱ��
	float GetDynamicCaseAllTime(int iDynaCase);
	//����Dynamic���Ƶõ���Ӧ��Id��
	int GetDynamicCaseIdByName(CString sName);
	//����Function���Ƶõ���Ӧ��Id��
	int GetFunctionIdByName(CString sName);
	//ɾ���رྲ�����ع���
	void ReorderStaticLoadCase(int *pMap);
	//ɾ���رද�����ع���
	void ReorderDynaLoadCase(int *pMap);
	//��������뼸��ģ���Ƿ��Ӧ
	void CheckMesh() const;
	//�㹲��
	bool IsVertexColline(const CVertex &va, const CVertex &vb, const CVertex &v);
};

