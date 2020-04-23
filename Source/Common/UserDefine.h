#pragma once

#include "SysPara.h"
#include "ASCFile.h"
#include "HeadDefine.h"

const int SYSTEM_COLOR_NUMBER=35;	//�� 2017��8��29��
const int SYSTEM_SIZE_NUMBER=35;	//2016.7.12


extern "C" _SSG_DLLIMPEXP float GetPrivateProfileFloat(LPCTSTR lpAppName,LPCTSTR lpKeyName,float fDefault,LPCTSTR lpIniFile);
extern "C" _SSG_DLLIMPEXP void  WritePrivateProfileFloat(LPCTSTR lpAppName,LPCTSTR lpKeyName,float fData,LPCTSTR lpIniFile);


//����������������
struct _SSG_DLLIMPEXP PROFILE_PARA
{
	CString sName;
	int prof_type;  //��������,0-���棬1-����
	float vEyex,vEyey,vEyez,vLookatx,vLookaty,vLookatz,vUpx,vUpy,vUpz;
	float fNear;
};

class _SSG_DLLIMPEXP  CSystemColor
{
public:
	CSystemColor(void);
	~CSystemColor(void);

	union
	{
		struct
		{
			COLORREF Sys_Backgroundcolor; //���ڱ���ɫ
			COLORREF Sys_VexColor;  //������ɫ���ṹȱʡ��ɫ
			COLORREF Sys_GuideLineColor;  //������ɫ(������)
			COLORREF Sys_StructLineColor;  //������ɫ(�ṹ��)
			COLORREF Sys_BoundaryLineColor;  //�߽�����ɫ

			COLORREF Sys_BeamColor;  //��������ɫ
			COLORREF Sys_PillarColor;  //��������ɫ
			COLORREF Sys_BracingColor;  //б��������ɫ
			COLORREF Sys_EdgeColor;  //��Ե������ɫ
			COLORREF Sys_HideBeamColor;  //������ɫ
			COLORREF Sys_LongiRebarColor;  //�����ݽ���ɫ
			COLORREF Sys_2ndBeamColor;  //������ɫ
			COLORREF Sys_PlateColor;  //¥����ɫ
			COLORREF Sys_WallColor;  //ǽ��ɫ
			COLORREF Sys_BeamWallColor;  //ǽ����ɫ
			COLORREF Sys_LinkColor;  //������������ɫ	//�Ǳ��� 2015.5.19

			COLORREF Sys_LineLoadColor;  //��������ɫ
			COLORREF Sys_AxisColor;  //��������ɫ,�������ֵΪ
			COLORREF Sys_HighlightPointColor;  //ʰȡ�������ʾ��ɫ
			COLORREF Sys_HighlightColor;  //ʰȡ���������ʾ��ɫ
			COLORREF Sys_CurrentColor;  //��ǰѡ�е�������ʾ��ɫ
			COLORREF Sys_ElasticColor;  //��Ƥ����ʾ��ɫ

			COLORREF Sys_OriginalColor;		//ԭʼ��ͼ����ʾ��ɫ
			COLORREF Sys_SectionConcColor;	//����ʾ��ͼ�л�������ɫ
			COLORREF Sys_SectionSteelColor; //����ʾ��ͼ�иֲ���ɫ
			COLORREF Sys_LabelColor;		//����ʾ��ͼ�б�ע��ɫ
			COLORREF Sys_GreyColor;			//��ֹ�ؼ�����ɫ

			COLORREF Sys_ProfileColor; //���������������ɫ
			COLORREF Sys_CommentsColor; //��ע���ֵ���ɫ

			COLORREF Sys_AnticulatePointColor;//�½ӵ���ɫ
			COLORREF Sys_EdgeWallColor;//��Ե������֧��ɫ
			COLORREF Sys_DriftPillarColor;//���λ�ƽ�������ɫ

			COLORREF Sys_MaxValueColor; //��ʾ��ֵ�����ֵ��ɫ
			COLORREF Sys_MinValueColor; //��ʾ��ֵ����Сֵ��ɫ
			COLORREF Sys_WarningColor; //��ʾ��ֵ������Ҫ�����ɫ

			
		};
		COLORREF Sys_ColorArray[SYSTEM_COLOR_NUMBER];
	};
};

class _SSG_DLLIMPEXP  CSystemSize
{
public:
	CSystemSize(void);
	~CSystemSize(void);
	union
	{
		struct
		{
			//��������Ϊ��Ԫ��ͼԪΪ�̶���С����֧�����ţ���ͬ
			//������Ϊ��Ԫ��ͼԪ֧������
			float Sys_RefLineWidth;         //�����ߡ��ṹ�߿��(����)
			float Sys_BeamLineWidth;        //���������(����)
			float Sys_HighLightLineWidth;   //�����������(����)
			float Sys_MeshLineWidth;        //�����������(����)
			float Sys_NormalPointSize;      //��ͨ����Ƴߴ�(����)
			float Sys_HighLightPointSize;   //��������Ƴߴ�(����)���̶���С��������
			float Sys_AxisLineWidth;        //�������������(����)

			float Sys_PointError;			//������ޣ���λ����
			float Sys_AngleError;			//�Ƕ����ޣ���λ����
			float Sys_AngleIncrease;        //��ͼ�Ƕ���������λ����
			float Sys_DistPrecision;        //�ƶ������ʱ�ľ���ֱ��ʣ���λ����
			float Sys_InitGraphRange;		//��ʼ��ͼ��Χ(��)
			float Sys_ProfileThickness;		//�������(��)
			float Sys_PlateShinkRatio;		//��������εı��������ڿ�����ʾģʽ�±�Ƕ������
			float Sys_AmbientRatio;         //������ǿ��,��Χ[0,1]
			float Sys_DirectRatio;          //�����������ǿ�ȣ���Χ[0,1]
			float Sys_RecentFiles;          //��������Ŀ��ʷ�嵥��Ŀ
			float Sys_PickDelayTime;		//��׽�������ӳ�ʱ��,��λ����
			float Sys_LegendType;			//��ͼ������ͣ�0-������1-��ɢ
			float Sys_LegendBlocks;			//��ɫ�ּ�����ȱʡ12
			float Sys_BraceDrift;			//б�Ų��������λ�ƽ�[1-���룬0-������]
			float Sys_TriInsertRatio;		//����������ʱ��������С����[0.05,0.2]��ֵԽС����Խ����
			float Sys_TriInsertLoop;		//����������ʱ���������ѭ������[1,10]��ֵԽ������Խ����
			float Sys_SpliteConcavePoly;	//�Զ���ְ������
			float Sys_PolyInnerAngle;		//�Զ���ְ����������ڽ�(��)
			float Sys_BlendMinAlfa;			//��Ⱦʱ��С͸����[0,255]
			float Sys_MinVexSize;			//����ģ�͵����ֵ(����)
			float Sys_MinPointSize;			//�����������ֵ(����)
			float Sys_MinLineSize;			//�����߶ε���ֵ(����/��)
			float Sys_MinExtendSize;		//������ʾ����ֵ(����/��)
			float Sys_AnticulateCircleRadius;//��ʾ�½ӵ�Բ���뾶(����)
			float Sys_AnticulateOffset;		 //��ʾ�½ӵ�Բ������ƫ����(��)
			float Sys_HingeCircleRadius;	//��ʾ���Խµ�Բ���뾶(����)
			float Sys_HingeOffset;			//��ʾ���Խµ�Բ������ƫ����(��)
			float Sys_OutputAve;			//��Ԫ��������ƽ����ֵ��%��
		//	float Sys_AdvancedFunc;			//�߼�����

			//�Ķ����ݺ�ע���޸�SYSTEM_SIZE_NUMBER
		};
		float Sys_SizeArray[SYSTEM_SIZE_NUMBER];
	};
};

class _SSG_DLLIMPEXP  CAxeParameter
{
public:
	CAxeParameter(void);
	~CAxeParameter(void);

	float Sys_CoorCubicRatio;  //����ԭ��С������ı���
	float Sys_ArrowAngle;   //�������ͷ��нǣ���λ����
	int Sys_CoorFontSize;//���������С����λ����
	CString Sys_CoorFontName;//������������
	float Sys_FontDeviation;   //���徫�ȣ�>=0
	int Sys_AxisPosition;  //�����λ��
	BOOL Sys_bVectorFont; //�Ƿ�ʸ������
};

//������Ŀģ�Ͳ�����ʼ����ȱʡ���ݣ�һ�㲻��Ϊģ�͵ľ������ԣ�֮�����һ��ӳ�����
//��������Ҫӳ���ģ�����Կ���ֱ�ӱ�����CFrame��
class _SSG_DLLIMPEXP  CProjectPara
{
public:
	CProjectPara(void);
	~CProjectPara(void);
	CProjectPara(const CProjectPara &para)
	{
		GetAddr();
		*this=para;
	}

	enum {PRJ_NUMBER=56};	//�Ǳ��� 2015.5.7

	//����Ϊ��׼��ʽ����SSG�ļ��ж���
	/*0 */CString Prj_Name;						//��Ŀ����
	/*1 */float Prj_BeamProtectLayerThick;		//���ֽ������(m)
	/*2 */float Prj_PillarProtectLayerThick;	//����б�Ÿֽ������(m)
	/*3 */float Prj_PlateProtectLayerThick;		//�屣������(m)
	/*4 */float Prj_WallProtectLayerThick;		//ǽ��������(m)
	/*5 */int Prj_Nsty;							//¥����������0��
	/*6 */int Prj_BaseStoryNum;					//�����Ҳ���,�ػ���0�����ڵ�����
	/*7 */int Prj_OldBaseStoryNum;				//ɾ���ĵ����Ҳ���
	/*8 */float Prj_ConcDensity;				//�������ض�kN/m3
	/*9 */float Prj_SteelDensity;				//�ֲ��ض�kN/m3
	/*10*/float Prj_GravityAcce;				//�������ٶ�m/s2
	/*11*/CString Prj_EdgeRebar;				//����ǽ��Ե�����ֽ��
	/*12*/CString Prj_LinkRebar;				//�����ݽ�ֽ��
	/*13*/CString Prj_BeamStirrup;				//�������
	/*14*/CString Prj_ColumnStirrup;			//�������
	/*15*/float Prj_BeamLinkSpace;				//��������
	/*16*/float Prj_ColumnLinkSpace;			//��������
	/*17*/float Prj_WallHoriRebarSpace;			//ǽˮƽ�ֲ�����(m)
	/*18*/float Prj_WallVertRebarSpace;			//ǽ����ֲ�����(m)
	/*19*/int Prj_WallSeisGrade;				//����ǽ�Ŀ���ȼ� 
	/*20*/int Prj_FrameSeisGrade;				//��ܵĿ���ȼ�
	/*21*/int Prj_ConsEdgeSty;					//Լ����Ե�������� 
//	/*21*/float Prj_SeisIntensity;				//����Ҷ�		//�������ظ����Ǳ���ע�͵�	2015.5.7
	/*22*/BOOL Prj_SlabSelfWeight;				//�Զ�����¥������,TRUE--¥�������Ѿ����������������
	/*23*/BOOL Prj_BraceBool;					//б�Ų��벼������
	/*24*/STRUCT_SYSTEM Prj_StructSystem;		//�ṹ��ϵ

	//2.0��������
	/*25*/int Prj_FieldClass;					//������� ����Ӧ��ϵ��0-I0,1-I1,2-II,3-III,4-IV��
	/*26*/int Prj_FieldGroup;					//���ط��飨��Ӧ��ϵ��0-��һ�飬1-�ڶ��飬2-�����飩
	/*27*/float Prj_EarthQuakeGrade;			//�����Ҷȣ�����Ϊ6, 7, 7.5, 8, 8.5, 9֮һ��
	/*28*/int Prj_EarthQuakeProbility;			//������� (0-С��,1-����,2-����) 
	/*29*/int Prj_ExtendMethod;					//�淶�����Ʒ��� (0-����ǰ�ι�ʽ��1-�㶨ֵ)
	/*30*/int Prj_PerformanceDesignGrade;		//���ܻ���Ƶ���ˮ׼ (��0λΪ1��ʾС�𣬵�1λΪ1��ʾ���𣬵�2λΪ1��ʾ����)
	
	//���²���δ��SSG�ļ��ж���
	/*31*/float Prj_BeamRebarDiameter;			//��ȱʡ�ֽ�ֱ��(m)
	/*32*/float Prj_PillarRebarDiameter;		//��ȱʡ�ֽ�ֱ��(m)
	/*33*/float Prj_PlateRebarDiameter;			//���ǽȱʡ�ֽ�ֱ��(m)
	/*34*/float Prj_BeamRebarRatio;				//����ȱʡ�����(%)�����͵׽�
	/*35*/float Prj_PillarRebarRatio;			//����ȱʡ�����(%)��ˮƽ�������
	/*36*/float Prj_PlateRebarRatio;			//��ȱʡ�ֽ������(%)
	/*37*/float Prj_WallRebarRatio;				//ǽȱʡ�ֽ������(%)
	/*38*/float Prj_PlateDefaultThickness;		//���ȱʡ���(m)
	/*39*/float Prj_WallDefaultThickness;		//ǽ��ȱʡ���(m)
	/*40*/int	Prj_WallConcLayer;				//ȱʡ��ǽ��������������
	/*41*/BOOL  Prj_CoorOffset;					//������Ƿ��Ѿ�������ƫ�ƽ������������û������޸�
	/*42*/float Prj_MaxQuadAngle;				//�����ı�������ʱ�õ��Ĳ���������ı����ڽǣ���λ����
	/*43*/float Prj_MaxTriAngle ;				//�����ı�������ʱ�õ��Ĳ���������������ڽǣ���λ����
	/*44*/int   Prj_nSmooth;					//����⻬����
	/*45*/float Prj_MinLineSize;				//��С��Ԫ�ߴ�ϵ����������Ԫ��Ч���ǵ�Ԫ�ɲ��ܴ˿���
	/*46*/BOOL	Prj_BeamOverlayStiffDeduction;	//�����ֹǻ���������ۼ��ص��ն�
	/*47*/BOOL	Prj_BeamOverlayAreaDeduction;	//�����ֹǻ���������ۼ��ص����
	/*48*/BOOL	Prj_PlateOverlayStiffDeduction;	//��ǽ�ֹǻ���������ۼ��ص��ն�
	/*49*/BOOL	Prj_PlateOverlayAreaDeduction;	//��ǽ�ֹǻ���������ۼ��ص����
	
	//2018��������
	/*50*/int	Prj_FortificationCategory;	//�����������
	/*51*/int	Prj_SlabSeisGrade;	//��Ŀ���ȼ� 
	/*52*/int	Prj_SeisDetailsGrade;//�������ʩ�Ŀ���ȼ� ������� ���һ�� ���ı� ����һ�� ��������
	/*53*/int	Prj_IsolatStory;//�����λ��
	/*54*/float	Prj_ImportanceCoef;//�ṹ��Ҫ��ϵ��
	/*55*/float	Prj_BearingCoef;//�������������ϵ��

	//�������������
	CArray<PROFILE_PARA,PROFILE_PARA&> m_aPrj_Profile;

	//��ʱ����
	enum PRJ_TYPE
	{
		prINT=0,
		prFLOAT=1,
		prSTR=2,
	};

	struct PRJ_PARA
	{
		union
		{
			void *pvar;
			int *pivar;
			float *pfvar;
			CString *psvar;
		};
		PRJ_TYPE type;
		char key[32];
		BOOL bShow;		//�Ƿ��ṩ�����޸�
		CString sName;	//��������
		float fcoef;	//ת��ϵ���������óˣ�����ó�
	}m_pAddr[PRJ_NUMBER]; //���ڱ����������ַ������¥��������������m_aPrj_Profile

	void GetAddr(void); //�����й��캯������,���ڳ�ʼ��m_pAddr

public:
	//��ֵ���������
	CProjectPara & operator=(const CProjectPara& para)
	{
		if(this==&para) return *this;

		/*0 */Prj_Name					=para.Prj_Name;					
		/*1 */Prj_BeamProtectLayerThick	=para.Prj_BeamProtectLayerThick;	
		/*2 */Prj_PillarProtectLayerThick=para.Prj_PillarProtectLayerThick;	
		/*3 */Prj_PlateProtectLayerThick=para.Prj_PlateProtectLayerThick;	
		/*4 */Prj_WallProtectLayerThick	=para.Prj_WallProtectLayerThick;	
		/*5 */Prj_Nsty					=para.Prj_Nsty;
		/*6 */Prj_BaseStoryNum			=para.Prj_BaseStoryNum;				
		/*7 */Prj_OldBaseStoryNum		=para.Prj_OldBaseStoryNum;				
		/*8 */Prj_ConcDensity			=para.Prj_ConcDensity;				
		/*9 */Prj_SteelDensity			=para.Prj_SteelDensity;				
		/*10*/Prj_GravityAcce			=para.Prj_GravityAcce;		
		/*11*/Prj_EdgeRebar				=para.Prj_EdgeRebar;		
		/*12*/Prj_LinkRebar				=para.Prj_LinkRebar;
		/*13*/Prj_BeamStirrup			=para.Prj_BeamStirrup;				
		/*14*/Prj_ColumnStirrup			= para.Prj_ColumnStirrup;			
		/*15*/Prj_BeamLinkSpace			=para.Prj_BeamLinkSpace;	
		/*16*/Prj_ColumnLinkSpace		=para.Prj_ColumnLinkSpace;
		/*17*/Prj_WallHoriRebarSpace	=para.Prj_WallHoriRebarSpace;
		/*18*/Prj_WallVertRebarSpace	=para.Prj_WallVertRebarSpace;
		/*19*/Prj_WallSeisGrade			=para.Prj_WallSeisGrade;				
		/*20*/Prj_FrameSeisGrade		=para.Prj_FrameSeisGrade;				
		/*21*/Prj_ConsEdgeSty			=para.Prj_ConsEdgeSty;				
//		/*21*/Prj_SeisIntensity			=para.Prj_SeisIntensity;			//�Ǳ���	2015.5.7
		/*22*/Prj_SlabSelfWeight		=para.Prj_SlabSelfWeight;				
		/*23*/Prj_BraceBool				=para.Prj_BraceBool;					
		/*24*/Prj_StructSystem			=para.Prj_StructSystem;		

		//2.0��������
		/*25*/Prj_FieldClass			= 	para.Prj_FieldClass;					
		/*26*/Prj_FieldGroup			=  	para.Prj_FieldGroup;				
		/*27*/Prj_EarthQuakeGrade		=  	para.Prj_EarthQuakeGrade;			
		/*28*/Prj_EarthQuakeProbility	=  	para.Prj_EarthQuakeProbility;	
		/*29*/Prj_ExtendMethod			=  	para.Prj_ExtendMethod;		
		/*30*/Prj_PerformanceDesignGrade=  	para.Prj_PerformanceDesignGrade;		

		
		/*31*/Prj_BeamRebarDiameter		=para.Prj_BeamRebarDiameter;		
		/*32*/Prj_PillarRebarDiameter	=para.Prj_PillarRebarDiameter;		
		/*33*/Prj_PlateRebarDiameter	=para.Prj_PlateRebarDiameter;		
		/*34*/Prj_BeamRebarRatio		=para.Prj_BeamRebarRatio;			
		/*35*/Prj_PillarRebarRatio		=para.Prj_PillarRebarRatio;			
		/*36*/Prj_PlateRebarRatio		=para.Prj_PlateRebarRatio;			
		/*37*/Prj_WallRebarRatio		=para.Prj_WallRebarRatio;			
		/*38*/Prj_PlateDefaultThickness	=para.Prj_PlateDefaultThickness;	
		/*39*/Prj_WallDefaultThickness	=para.Prj_WallDefaultThickness;		
		/*40*/Prj_WallConcLayer			=para.Prj_WallConcLayer;				
		/*41*/Prj_CoorOffset			=para.Prj_CoorOffset; 
		/*42*/Prj_MaxQuadAngle			=para.Prj_MaxQuadAngle;
		/*43*/Prj_MaxTriAngle			=para.Prj_MaxTriAngle;
		/*44*/Prj_nSmooth				=para.Prj_nSmooth;
		/*45*/Prj_MinLineSize			=para.Prj_MinLineSize; 
		/*46*/Prj_BeamOverlayStiffDeduction		=para.Prj_BeamOverlayStiffDeduction	; 
		/*47*/Prj_BeamOverlayAreaDeduction		=para.Prj_BeamOverlayAreaDeduction	; 
		/*48*/Prj_PlateOverlayStiffDeduction	=para.Prj_PlateOverlayStiffDeduction	; 
		/*49*/Prj_PlateOverlayAreaDeduction		=para.Prj_PlateOverlayAreaDeduction	; 
		/*50*/Prj_FortificationCategory			=para.Prj_FortificationCategory				;
		/*51*/Prj_SlabSeisGrade					=para.Prj_SlabSeisGrade				;
		/*52*/Prj_SeisDetailsGrade				=para.Prj_SeisDetailsGrade				;
		/*53*/Prj_IsolatStory					=para.Prj_IsolatStory;			
		/*54*/Prj_ImportanceCoef				=para.Prj_ImportanceCoef;			
		/*55*/Prj_BearingCoef					=para.Prj_BearingCoef;			


		m_aPrj_Profile.RemoveAll();
		m_aPrj_Profile.Copy(para.m_aPrj_Profile);

		return *this;
	}

	void Init(void);

	//��SSG�ļ��ж���
	BOOL Read(const CString &sPrjName);
	BOOL Write(CFile &fout);
};

class _SSG_DLLIMPEXP  CProgramControl
{
public:
	CProgramControl(void);
	~CProgramControl(void);

	union
	{
		struct
		{
			float Sys_MaxUndoStep;						//���undo����
			float Sys_AngStep;								//���̷�����ƶ�ͼ�εĽǶȲ�������
			float Sys_AutoSaving;							//��ʱ�Զ����湤��(1-�ǣ�0-��)
			float Sys_AutoSavingTimeStep;			//��ʱ�Զ����湤��ʱ����
			float Sys_SaveBackup;							//���̱���ʱͬʱ���渱��
			float Sys_MaxBackupNumber;			// ���̱�����󸱱�����
		};
		float Sys_ProgCtrlArray[6];
	};
};

class _SSG_DLLIMPEXP  CInitialviewParameter
{
public:
	CInitialviewParameter(void);
	~CInitialviewParameter(void);

	union
	{
		struct
		{

			float Sys_Angle;
			float Sys_zNear;
			float Sys_zFar;
			float Sys_WindowRatio;
			float Sys_AxisPosition;
		};
		float Sys_InitialviewParameterArray[4];
	};
};

class _SSG_DLLIMPEXP  CPerformanceGradePara
{
public:
	CPerformanceGradePara(void);
	~CPerformanceGradePara(void);

	struct
	{
		int Sys_PerformType;//2ΪRBS��0ΪĬ�ϣ�1Ϊ����//2019.11.27����
		CString Sys_PerformGradeNameRBS[5];//2019.11.27����
		COLORREF Sys_PerformGradeColorRBS[5];//2019.11.27����
		int Sys_bPerformDefault;//2020.4.1�������ж��û��Ƿ�Ϊ��һ��ʹ�ó��򣬲���Ϊ1
	
		float Sys_RebarSteelStrainRBS[3];//2019.12.30����
		float Sys_DcRBS[3];//2019.12.30����

		int Sys_PerformGradeNum;
		CString Sys_PerformGradeName[Sys_MaxPerformGrade];
		float Sys_StrainGrade[Sys_MaxPerformGrade];
		float Sys_DamageGrade[Sys_MaxPerformGrade];
		float Sys_DtGrade[Sys_MaxPerformGrade];
		float Sys_WallStrainGrade[Sys_MaxPerformGrade];
		float Sys_WallDamageGrade[Sys_MaxPerformGrade];
		float Sys_WallDtGrade[Sys_MaxPerformGrade];
		COLORREF Sys_PerformGradeColor[Sys_MaxPerformGrade];	

		int Sys_PerformGradeNumDefault;
		CString Sys_PerformGradeNameDefault[Sys_MaxPerformGrade];
		float Sys_StrainGradeDefault[Sys_MaxPerformGrade];
		float Sys_DamageGradeDefault[Sys_MaxPerformGrade];
		float Sys_DtGradeDefault[Sys_MaxPerformGrade];
		float Sys_WallStrainGradeDefault[Sys_MaxPerformGrade];
		float Sys_WallDamageGradeDefault[Sys_MaxPerformGrade];
		float Sys_WallDtGradeDefault[Sys_MaxPerformGrade];
		COLORREF Sys_PerformGradeColorDefault[Sys_MaxPerformGrade];	
	};
};

class _SSG_DLLIMPEXP  CHingeGradePara
{
public:
	CHingeGradePara(void);
	~CHingeGradePara(void);

	struct
	{
		int Sys_HingeGradeNum;
		CString Sys_HingeGradeName[Sys_MaxHingeGrade];
		float Sys_RebarKGrade[Sys_MaxHingeGrade];
		float Sys_SteelKGrade[Sys_MaxHingeGrade];
		COLORREF Sys_HingeGradeColor[Sys_MaxHingeGrade];	

		int Sys_HingeGradeNumDefault;
		CString Sys_HingeGradeNameDefault[Sys_MaxHingeGrade];
		float Sys_RebarKGradeDefault[Sys_MaxHingeGrade];
		float Sys_SteelKGradeDefault[Sys_MaxHingeGrade];
		COLORREF Sys_HingeGradeColorDefault[Sys_MaxHingeGrade];	
	};
};

#define Sys_ComponentNum 188 //��������
struct _SSG_DLLIMPEXP COMPONENT_COMMENT_TABLE
{
	CString sName;				//��������
	CString sComment;			//����˵��
};

extern "C" _SSG_DLLIMPEXP CSystemSize g_cSysSizePara;
extern "C" _SSG_DLLIMPEXP CSystemColor g_cSysColorPara;
extern "C" _SSG_DLLIMPEXP CAxeParameter g_cSysAxePara;
extern "C" _SSG_DLLIMPEXP CProgramControl g_cSysProgCtrl;
extern "C" _SSG_DLLIMPEXP CInitialviewParameter g_cSysInitViewPata;
extern "C" _SSG_DLLIMPEXP CPerformanceGradePara g_cSysPerformGradePara;
extern "C" _SSG_DLLIMPEXP CHingeGradePara g_cSysHingeGradePara;
extern "C" _SSG_DLLIMPEXP float g_Sys_Size_Default[SYSTEM_SIZE_NUMBER];
extern "C" _SSG_DLLIMPEXP COLORREF g_Sys_Color_Default[SYSTEM_COLOR_NUMBER];
extern "C" _SSG_DLLIMPEXP float g_Sys_ProgCtrl_Default[6];
extern "C" _SSG_DLLIMPEXP float g_Sys_InitialviewParameter_Default[4];
extern "C" _SSG_DLLIMPEXP COMPONENT_COMMENT_TABLE aComponentCommentTable[Sys_ComponentNum];
