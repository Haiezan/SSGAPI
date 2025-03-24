#pragma once

#include "SysPara.h"
#include "ASCFile.h"
#include "HeadDefine.h"
#include "PublicFunc_Cpp.h"
#include "SectionBaseHead.h"
#include "StructFunc.h"

const int SYSTEM_COLOR_NUMBER=42;	//�� 2017��8��29�� ����2023.5.17 ����2023.9.20 ����20231213 ��ҵ�� 2024��2��21��
const int SYSTEM_SIZE_NUMBER=36;	//2016.7.12
const int SYSTEM_STRUCTURAL_MEMBER_COLOR_NUMBER = 132;	// ������ʾ��ͬ�Ľṹ��������ɫ ��ҵ�� 2024��2��21��


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

//�Զ����û��ӽ�
struct _SSG_DLLIMPEXP USER_VIEW
{
	float vEyex, vEyey, vEyez, vLookatx, vLookaty, vLookatz, vUpx, vUpy, vUpz;
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
			COLORREF Sys_RigidColor; //����¥����ɫ ����20231213

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

			COLORREF Sys_BlastFrontWallColor; //��ը������ǰǽ��ע��ɫ
			COLORREF Sys_BlastSideWallColor; //��ը�����в�ǽ��ע��ɫ
			COLORREF Sys_BlastRoofWallColor; //��ը�����в�ǽ��ע��ɫ
			COLORREF Sys_BlastBackWallColor; //��ը�����к�ǽ��ע��ɫ

			COLORREF Sys_PartitionWallColor; //��ǽ��ɫ
			COLORREF Sys_ReinforcedColor; // ������ǽ��ӹ���ɫ

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
			float Sys_LinkDrift;			//һ�����Ӳ��������λ�ƽ�[1-���룬0-������]
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

	enum {PRJ_NUMBER=72};	//�Ǳ��� 2015.5.7

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

	//2021��������
	/*56*/int Prj_CodeType;//�淶���ͣ���Ӧ��ϵ��0-���ҹ淶��1-�㶫���ܹ�̣�2-���꣬3-�㶫�߹�,4-���ܼ���,5-�Ϻ���׼��
	/*57*/int Prj_PerformType;//�������۱�׼���ͣ���Ӧ��ϵ��0-Ĭ��ֵ��1-�����淶��2-RBS��3-�㶫��
	/*58*/int Prj_SlabConcLayer;				//ȱʡ�İ幹������������
	/*59*/float Prj_StructTemper;				   //�����¶�
	/*60*/float Prj_ScaleMassMinLength;
	/*61*/float Prj_ScaleMassMinTriArea;
	/*62*/float Prj_ScaleMassMinQuadArea;
	/*63*/float Prj_ScaleFactor;
	/*64*/int Prj_bScaleByFactor;   // δ��ʼ�� -1�� FALSE 1;  TRUE 0
	/*65*/float Prj_fTotalMassRatio;
	/*66*/BOOL Prj_bAutoScaleMass;
	/*67*/BOOL Prj_bScaleMass;
	/*68*/float Prj_DriftLmt; //���λ�ƽ���ֵ ����20230310
	/*69*/int Prj_JGCodeType;//�����ӹ̱�׼

	//2024��������
	/*70*/int Prj_MeshOptIter;//�����Ż���������

	//2025��������
	/*71*/int Prj_DZPerformanceGradeGJ;//���������¹ؼ������Ŀ�������ˮ׼
	/*72*/int Prj_DZPerformanceGradeNM;//������������ͨ���򹹼��Ŀ�������ˮ׼
	/*73*/int Prj_DZPerformanceGradeHN;//���������º��ܹ����Ŀ�������ˮ׼

	/*74*/int Prj_ZZPerformanceGradeGJ;//��������¹ؼ������Ŀ�������ˮ׼
	/*75*/int Prj_ZZPerformanceGradeNM;//�����������ͨ���򹹼��Ŀ�������ˮ׼
	/*76*/int Prj_ZZPerformanceGradeHN;//��������º��ܹ����Ŀ�������ˮ׼

	/*77*/int Prj_XZPerformanceGradeGJ;//���������¹ؼ������Ŀ�������ˮ׼
	/*78*/int Prj_XZPerformanceGradeNM;//������������ͨ���򹹼��Ŀ�������ˮ׼
	/*79*/int Prj_XZPerformanceGradeHN;//���������º��ܹ����Ŀ�������ˮ׼
	
	//2026��������
	/*80*/float Prj_SoilkhRatio;//����ˮƽ����ϵ���ı���ϵ��

	//�������������
	CArray<PROFILE_PARA,PROFILE_PARA&> m_aPrj_Profile;
	USER_VIEW m_UserView;

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
		/*56*/Prj_CodeType						=para.Prj_CodeType;
		/*57*/Prj_PerformType					=para.Prj_PerformType;
		/*58*/Prj_SlabConcLayer					=para.Prj_SlabConcLayer;
		/*59*/Prj_StructTemper					=para.Prj_StructTemper;
		/*60*/Prj_ScaleMassMinLength            =para.Prj_ScaleMassMinLength;
		/*61*/Prj_ScaleMassMinTriArea           =para.Prj_ScaleMassMinTriArea;
		/*62*/Prj_ScaleMassMinQuadArea          =para.Prj_ScaleMassMinQuadArea;
		/*63*/Prj_ScaleFactor                   =para.Prj_ScaleFactor;
		/*64*/Prj_bScaleByFactor                =para.Prj_bScaleByFactor;
		/*65*/Prj_fTotalMassRatio				=para.Prj_fTotalMassRatio;
		/*66*/Prj_bAutoScaleMass				=para.Prj_bAutoScaleMass;
		/*67*/Prj_bScaleMass                    =para.Prj_bScaleMass;
		/*68*/Prj_DriftLmt						=para.Prj_DriftLmt;
		/*69*/Prj_JGCodeType					=para.Prj_JGCodeType;

		/*70*/Prj_MeshOptIter					=para.Prj_MeshOptIter;

		/*71*/Prj_DZPerformanceGradeGJ			=para.Prj_DZPerformanceGradeGJ;
		/*72*/Prj_DZPerformanceGradeNM			=para.Prj_DZPerformanceGradeNM;
		/*73*/Prj_DZPerformanceGradeHN			=para.Prj_DZPerformanceGradeHN;

		/*74*/Prj_ZZPerformanceGradeGJ			=para.Prj_ZZPerformanceGradeGJ;
		/*75*/Prj_ZZPerformanceGradeGJ			=para.Prj_ZZPerformanceGradeGJ;
		/*76*/Prj_ZZPerformanceGradeGJ			=para.Prj_ZZPerformanceGradeGJ;

		/*77*/Prj_XZPerformanceGradeGJ			=para.Prj_XZPerformanceGradeGJ;
		/*78*/Prj_XZPerformanceGradeGJ			=para.Prj_XZPerformanceGradeGJ;
		/*79*/Prj_XZPerformanceGradeGJ			=para.Prj_XZPerformanceGradeGJ;
		/*80*/Prj_SoilkhRatio                   =para.Prj_SoilkhRatio;
		m_aPrj_Profile.RemoveAll();
		m_aPrj_Profile.Copy(para.m_aPrj_Profile);

		return *this;
	}

	BOOL operator==(const CProjectPara& para) const
	{
		/*0 */if (Prj_Name != para.Prj_Name) return FALSE;
		/*1 */if (Prj_BeamProtectLayerThick != para.Prj_BeamProtectLayerThick) return FALSE;
		/*2 */if (Prj_PillarProtectLayerThick != para.Prj_PillarProtectLayerThick) return FALSE;
		/*3 */if (Prj_PlateProtectLayerThick != para.Prj_PlateProtectLayerThick) return FALSE;
		/*4 */if (Prj_WallProtectLayerThick != para.Prj_WallProtectLayerThick) return FALSE;
		/*5 */if (Prj_Nsty != para.Prj_Nsty) return FALSE;
		/*6 */if (Prj_BaseStoryNum != para.Prj_BaseStoryNum) return FALSE;
		/*7 */if (Prj_OldBaseStoryNum != para.Prj_OldBaseStoryNum) return FALSE;
		/*8 */if (Prj_ConcDensity != para.Prj_ConcDensity) return FALSE;
		/*9 */if(Prj_SteelDensity != para.Prj_SteelDensity) return FALSE;
		/*10*/if (Prj_GravityAcce != para.Prj_GravityAcce) return FALSE;
		/*11*/if (Prj_EdgeRebar != para.Prj_EdgeRebar) return FALSE;
		/*12*/if (Prj_LinkRebar != para.Prj_LinkRebar) return FALSE;
		/*13*/if (Prj_BeamStirrup != para.Prj_BeamStirrup) return FALSE;
		/*14*/if (Prj_ColumnStirrup != para.Prj_ColumnStirrup) return FALSE;
		/*15*/if (Prj_BeamLinkSpace != para.Prj_BeamLinkSpace) return FALSE;
		/*16*/if (Prj_ColumnLinkSpace != para.Prj_ColumnLinkSpace) return FALSE;
		/*17*/if (Prj_WallHoriRebarSpace != para.Prj_WallHoriRebarSpace) return FALSE;
		/*18*/if (Prj_WallVertRebarSpace != para.Prj_WallVertRebarSpace) return FALSE;
		/*19*/if (Prj_WallSeisGrade != para.Prj_WallSeisGrade) return FALSE;
		/*20*/if (Prj_FrameSeisGrade != para.Prj_FrameSeisGrade) return FALSE;
		/*21*/if (Prj_ConsEdgeSty != para.Prj_ConsEdgeSty) return FALSE;
		/*22*/if (Prj_SlabSelfWeight != para.Prj_SlabSelfWeight) return FALSE;
		/*23*/if (Prj_BraceBool != para.Prj_BraceBool) return FALSE;
		/*24*/if (Prj_StructSystem != para.Prj_StructSystem) return FALSE;

		//2.0��������
		/*25*/if (Prj_FieldClass != para.Prj_FieldClass) return FALSE;
		/*26*/if (Prj_FieldGroup != para.Prj_FieldGroup) return FALSE;
		/*27*/if (Prj_EarthQuakeGrade != para.Prj_EarthQuakeGrade) return FALSE;
		/*28*/if (Prj_EarthQuakeProbility != para.Prj_EarthQuakeProbility) return FALSE;
		/*29*/if (Prj_ExtendMethod != para.Prj_ExtendMethod) return FALSE;
		/*30*/if (Prj_PerformanceDesignGrade != para.Prj_PerformanceDesignGrade) return FALSE;

		/*31*/if (Prj_BeamRebarDiameter != para.Prj_BeamRebarDiameter) return FALSE;
		/*32*/if (Prj_PillarRebarDiameter != para.Prj_PillarRebarDiameter) return FALSE;
		/*33*/if (Prj_PlateRebarDiameter != para.Prj_PlateRebarDiameter) return FALSE;
		/*34*/if (Prj_BeamRebarRatio != para.Prj_BeamRebarRatio) return FALSE;
		/*35*/if (Prj_PillarRebarRatio != para.Prj_PillarRebarRatio) return FALSE;
		/*36*/if (Prj_PlateRebarRatio != para.Prj_PlateRebarRatio) return FALSE;
		/*37*/if (Prj_WallRebarRatio != para.Prj_WallRebarRatio) return FALSE;
		/*38*/if (Prj_PlateDefaultThickness != para.Prj_PlateDefaultThickness) return FALSE;
		/*39*/if (Prj_WallDefaultThickness != para.Prj_WallDefaultThickness) return FALSE;
		/*40*/if (Prj_WallConcLayer != para.Prj_WallConcLayer) return FALSE;
		/*41*/if (Prj_CoorOffset != para.Prj_CoorOffset) return FALSE;
		/*42*/if (Prj_MaxQuadAngle != para.Prj_MaxQuadAngle) return FALSE;
		/*43*/if (Prj_MaxTriAngle != para.Prj_MaxTriAngle) return FALSE;
		/*44*/if (Prj_nSmooth != para.Prj_nSmooth) return FALSE;
		/*45*/if (Prj_MinLineSize != para.Prj_MinLineSize) return FALSE;
		/*46*/if (Prj_BeamOverlayStiffDeduction != para.Prj_BeamOverlayStiffDeduction) return FALSE;
		/*47*/if (Prj_BeamOverlayAreaDeduction != para.Prj_BeamOverlayAreaDeduction) return FALSE;
		/*48*/if (Prj_PlateOverlayStiffDeduction != para.Prj_PlateOverlayStiffDeduction) return FALSE;
		/*49*/if (Prj_PlateOverlayAreaDeduction != para.Prj_PlateOverlayAreaDeduction) return FALSE;
		/*50*/if (Prj_FortificationCategory != para.Prj_FortificationCategory) return FALSE;
		/*51*/if (Prj_SlabSeisGrade != para.Prj_SlabSeisGrade) return FALSE;
		/*52*/if (Prj_SeisDetailsGrade != para.Prj_SeisDetailsGrade) return FALSE;
		/*53*/if (Prj_IsolatStory != para.Prj_IsolatStory) return FALSE;
		/*54*/if (Prj_ImportanceCoef != para.Prj_ImportanceCoef) return FALSE;
		/*55*/if (Prj_BearingCoef != para.Prj_BearingCoef) return FALSE;
		/*56*/if (Prj_CodeType != para.Prj_CodeType) return FALSE;
		/*57*/if (Prj_PerformType != para.Prj_PerformType) return FALSE;
		/*58*/if (Prj_SlabConcLayer != para.Prj_SlabConcLayer) return FALSE;
		/*59*/if (Prj_StructTemper != para.Prj_StructTemper) return FALSE;
		/*60*/if (Prj_ScaleMassMinLength != para.Prj_ScaleMassMinLength) return FALSE;
		/*61*/if (Prj_ScaleMassMinTriArea != para.Prj_ScaleMassMinTriArea) return FALSE;
		/*62*/if (Prj_ScaleMassMinQuadArea != para.Prj_ScaleMassMinQuadArea) return FALSE;
		/*63*/if (Prj_ScaleFactor != para.Prj_ScaleFactor) return FALSE;
		/*64*/if (Prj_bScaleByFactor != para.Prj_bScaleByFactor) return FALSE;
		/*65*/if (Prj_fTotalMassRatio != para.Prj_fTotalMassRatio) return FALSE;
		/*66*/if (Prj_bAutoScaleMass != para.Prj_bAutoScaleMass) return FALSE;
		/*67*/if (Prj_bScaleMass != para.Prj_bScaleMass) return FALSE;
		/*68*/if (Prj_DriftLmt != para.Prj_DriftLmt) return FALSE;
		/*69*/if (Prj_JGCodeType != para.Prj_JGCodeType) return FALSE;

		/*70*/if (Prj_MeshOptIter != para.Prj_MeshOptIter) return FALSE;

		/*71*/if (Prj_DZPerformanceGradeGJ != para.Prj_DZPerformanceGradeGJ) return FALSE;
		/*72*/if (Prj_DZPerformanceGradeNM != para.Prj_DZPerformanceGradeNM) return FALSE;
		/*73*/if (Prj_DZPerformanceGradeHN != para.Prj_DZPerformanceGradeHN) return FALSE;

		/*74*/if (Prj_ZZPerformanceGradeGJ != para.Prj_ZZPerformanceGradeGJ) return FALSE;
		/*75*/if (Prj_ZZPerformanceGradeNM != para.Prj_ZZPerformanceGradeNM) return FALSE;
		/*76*/if (Prj_ZZPerformanceGradeHN != para.Prj_ZZPerformanceGradeHN) return FALSE;

		/*77*/if (Prj_XZPerformanceGradeGJ != para.Prj_XZPerformanceGradeGJ) return FALSE;
		/*78*/if (Prj_XZPerformanceGradeNM != para.Prj_XZPerformanceGradeNM) return FALSE;
		/*79*/if (Prj_XZPerformanceGradeHN != para.Prj_XZPerformanceGradeHN) return FALSE;

		/*80*/if (Prj_SoilkhRatio != para.Prj_SoilkhRatio)return FALSE;
		return TRUE;
	}

	void Init(void);

	//��SSG�ļ��ж���
	BOOL Read(const CString &sPrjName);
	BOOL Write(CFile &fout);
	BOOL Write2020(CFile &fout);

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
		int Sys_PerformType;//4Ϊ�����Թ��(Ӧ��),3Ϊ�㶫ʡ���\�����Թ��(λ�ƽ�),2ΪRBS��0ΪĬ�ϣ�1Ϊ����//2019.11.27����
		BOOL Sys_PerformTypeSteelOn; //�Ƿ��Ǹֹ������۱�׼
		int Sys_PerformTypeSteel; //�ֹ������۱�׼

		BOOL Sys_PerformTypeDamperOn; //�Ƿ������������۱�ע

		int Sys_PerformGradeNum; //���۵ȼ�����

		CString Sys_PerformGradeNameRBS[5];//2019.11.27����
		COLORREF Sys_PerformGradeColorRBS[5];//2019.11.27����
	
		float Sys_RebarSteelStrainRBS[3];//2019.12.30����
		float Sys_DcRBS[3];//2019.12.30����

		//�㶫ʡ����������ۡ������Թ�̣�λ�ƽǣ��������ò��� 2021.1.13����
		float Sys_GDNLBeam[8][6] =
		{
			//���
			0.004f,0.016f,0.024f,0.031f,0.039f,0.044f, //0 m��0.2 ��v��0.012
			0.004f,0.018f,0.029f,0.039f,0.049f,0.054f, //1 m��0.8 ��v��0.012
			0.004f,0.010f,0.011f,0.013f,0.014f,0.017f, //2 m��0.2 ��v��0.001
			0.004f,0.012f,0.016f,0.020f,0.024f,0.029f, //3 m��0.8 ��v��0.001
			//�����
			0.004f,0.009f,0.014f,0.019f,0.024f,0.026f, //4 m��0.5 ��sv��0.008
			0.004f,0.007f,0.009f,0.012f,0.014f,0.016f, //5 m��2.5 ��sv��0.008
			0.004f,0.007f,0.009f,0.012f,0.014f,0.016f, //6 m��0.5 ��sv��0.0005
			0.004f,0.005f,0.007f,0.008f,0.009f,0.012f, //7 m��2.5 ��sv��0.0005
		};

		float Sys_GDNLPillar[8][6] =
		{
			//���
			0.004f,0.018f,0.027f,0.037f,0.046f,0.056f, //0 n��0.1 ��v��0.021
			0.004f,0.013f,0.018f,0.022f,0.027f,0.030f, //1 n=0.6 ��v��0.021
			0.004f,0.015f,0.022f,0.029f,0.036f,0.042f, //2 n��0.1 ��v��0.001
			0.004f,0.009f,0.011f,0.012f,0.013f,0.014f, //3 n=0.6 ��v��0.001
			//�����
			0.003f,0.013f,0.020f,0.026f,0.033f,0.040f, //4 n��0.1 m��0.6
			0.003f,0.009f,0.011f,0.014f,0.016f,0.018f, //5 n=0.6 m��0.6
			0.003f,0.011f,0.016f,0.021f,0.026f,0.028f, //6 n��0.1 m��1.0
			0.003f,0.008f,0.009f,0.011f,0.012f,0.014f, //7 n=0.6 m��1.0
		};

		float Sys_GDNLWall[8][6] =
		{
			//���
			0.003f,0.011f,0.016f,0.022f,0.025f,0.028f, //0 n��0.1 ��v��0.025
			0.003f,0.010f,0.013f,0.017f,0.020f,0.022f, //1 n=0.4 ��v��0.025
			0.003f,0.008f,0.010f,0.011f,0.013f,0.015f, //2 n��0.1 ��v��0.004
			0.003f,0.007f,0.008f,0.009f,0.010f,0.011f, //3 n=0.4 ��v��0.004
			//�����
			0.003f,0.010f,0.013f,0.017f,0.020f,0.021f, //4 n��0.1 m��0.5
			0.003f,0.008f,0.011f,0.013f,0.015f,0.016f, //5 n=0.3 m��0.5
			0.003f,0.008f,0.010f,0.011f,0.013f,0.015f, //6 n��0.1 m=2.0
			0.003f,0.007f,0.008f,0.010f,0.011f,0.013f, //7 n=0.3 m=2.0
		};

		//������������������CECS 392�� 2014��
		CString Sys_PerformGradeNameCollapse[Sys_MaxPerformGrade] =
		{
			_CHSL(L"����", L"None") ,_CHSL(L"��΢��", L"Light") ,_CHSL(L"�����", L"Slight"),
			_CHSL(L"�ж���", L"Moderate") ,_CHSL(L"�Ƚ�������", L"Heavy") ,_CHSL(L"������", L"Severe")
		};
		float Sys_PerformCollapseConcrete[6] = { 0.f,1.f,1.f,1.5f,2.f,3.f };
		float Sys_PerformCollapseRebar[6] = { 0.f,1.f,2.5f,5.f,12.5f,20.f };

		//Ӧ����׼
		CString Sys_PerformGradeNameStress[6] =
		{
			_CHSL(L"����", L"None") ,_CHSL(L"��΢��", L"Light") ,_CHSL(L"�����", L"Slight"),
			_CHSL(L"�ж���", L"Moderate") ,_CHSL(L"�ض���", L"Heavy") ,_CHSL(L"������", L"Severe")
		};
		float Sys_PerformStressConcrete[6] = { -1.f,-0.2f,0.f,0.2f,0.5f,0.75f };
		float Sys_PerformStressRebar[6] = { 0.f,1.f,3.f,5.f,7.f,12.f };

		//�����Թ���������
		CString Sys_PerformGradeNameNonlinear[Sys_MaxPerformGrade] =
		{
			_CHSL(L"����", L"None") ,_CHSL(L"��΢��", L"Light") ,_CHSL(L"�����", L"Slight"),
			_CHSL(L"�ж���", L"Moderate") ,_CHSL(L"�ض���", L"Heavy") ,_CHSL(L"������", L"Severe")
		};
		float Sys_PerformNonlinearConcrete[6] = { 0.f,0.8f,1.f,1.35f,2.175f,3.f };
		float Sys_PerformNonlinearRebar[6] = { 0.f,1.f,2.f,4.f,7.f,13.f };

		//�������۱�׼�������
		CString Sys_PerformGradeNameRES[Sys_MaxPerformGrade] =
		{ 
			_CHSL(L"0��", L"Level 0") ,_CHSL(L"1��", L"Level 1") ,_CHSL(L"2��", L"Level 2"),
			_CHSL(L"3��", L"Level 3") ,_CHSL(L"4��", L"Level 4") ,_CHSL(L"5��", L"Level 5")
		};
		COLORREF Sys_PerformGradeColorRES[Sys_MaxPerformGrade] = { RGB(0,0,255) ,RGB(0,255,255) ,RGB(0,255,0) ,RGB(255,255,0) ,RGB(255,97,0) ,RGB(255,0,0) };
		float Sys_PerformRESConcrete[Sys_MaxPerformGrade] = { 0.f,1.f,1.f,1.5f,3.f,4.5f };
		float Sys_PerformRESRebar[Sys_MaxPerformGrade] = { 0.f,1.f,2.f,3.5f,12.f,20.f };

		//���ܻ���Ʊ�׼�������
		CString Sys_PerformGradeNamePBSD[Sys_MaxPerformGrade] =
		{
			_CHSL(L"����", L"None") ,_CHSL(L"��΢��", L"Light") ,_CHSL(L"�����", L"Slight"),
			_CHSL(L"�ж���", L"Moderate") ,_CHSL(L"�ض���", L"Heavy") ,_CHSL(L"������", L"Severe")
		};
		float Sys_PerformPBSDConcrete[6] = { 0.f,0.5f,1.f,1.5f,3.f,4.5f };
		float Sys_PerformPBSDRebar[6] = { 0.f,1.f,3.f,6.f,12.f,20.f };

		//2023�汾Ĭ�����۱�׼
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

		//�ֹ����������۱�׼
		int Sys_SteelPerformGradeNum = 6;
		float Sys_SteelGradeDefault[17][Sys_MaxPerformGrade] =
		{
			//S1
			0.0f,1.0f,4.5f,8.0f,12.0f,15.0f ,
			0.0f,1.0f,3.0f,5.0f,7.0f,9.0f,
			0.0f,1.0f,2.5f,4.0f,5.5f,7.0f,
			0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,
			//S2
			0.0f,1.0f,2.5f,4.0f,6.0f,8.0f,
			0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,
			0.0f,1.0f,1.75f,2.5f,3.25f,4.0f,
			0.0f,1.0f,1.5f,2.0f,2.5f,3.0f,
			//S3
			0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,
			0.0f,1.0f,1.5f,2.0f,2.5f,3.0f,
			0.0f,1.0f,1.4f,1.75f,2.2f,2.5f,
			0.0f,1.0f,1.25f,1.5f,1.75f,2.0f,
			//S4
			0.0f,1.0f,1.5f,2.0f,3.0f,4.0f,
			0.0f,1.0f,1.4f,1.75f,2.2f,2.5f,
			0.0f,1.0f,1.25f,1.5f,1.75f,2.0f,
			0.0f,1.0f,1.2f,1.4f,1.6f,1.8f,
			//P/Py>0.6
			0.0f,1.0f,1.0f,1.0f,1.0f,1.0f
		};

		//�ֹ����������۱�׼��λ�ƽǣ�
		float Sys_SteelDirftLmtGradeDefault[5][4] = //���Ⱥ͸ߺ����ֵ
		{
			 9.f,72.f,11.f,110.f,
			 9.f,51.f,11.f,79.f,
			 9.f,45.f,11.f,68.f,
			19.f,51.f,33.f,79.f,
			19.f,45.f,33.f,68.f,
		};
		float Sys_SteelDirftGradeDefault[11][Sys_MaxPerformGrade] =
		{
			//����H���棩
			0.0f,1.0f,2.00f,6.0f,10.0f,12.0f, //b/tf��9��h/tw��72
			0.0f,1.0f,1.25f,2.63f,4.0f,5.f, //b/tf��11��h/tw��110

			//����H���棩
			//n<0.2
			0.0f,1.0f,2.0f,6.0f,10.0f,12.0f, //b/tf��9��h/tw��51
			0.0f,1.0f,1.25f,2.63f,4.0f,5.f, //b/tf��11��h/tw��79
			//0.2��n��0.6
			0.0f,1.0f,1.25f,8.125f,15.0f,18.0f, //b/tf��9��h/tw��51
			0.0f,1.0f,1.25f,1.38f,1.5f,1.8f, //b/tf��11��h/tw��79

			//�������ܽ��棩
			//n<0.2
			0.0f,1.0f,2.0f,6.0f,10.0f,12.0f, //b/tf��19��h/tw��51
			0.0f,1.0f,1.25f,2.63f,4.0f,5.f, //b/tf��33��h/tw��79
			//0.2��n��0.6
			0.0f,1.0f,1.25f,8.125f,15.0f,18.0f, //b/tf��19��h/tw��45
			0.0f,1.0f,1.25f,1.38f,1.5f,1.8f, //b/tf��33��h/tw��68

			//�������
			0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
		};
		float Sys_SteelDirftNGradeDefault[11][Sys_MaxPerformGrade] =
		{
			//����H���棩
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��9��h/tw��72
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��11��h/tw��110

			//����H���棩
			//n<0.2
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��9��h/tw��51
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��11��h/tw��79
			//0.2��n��0.6
			0.0f,0.0f,0.0f,11.7f,23.3f,28.3f, //b/tf��9��h/tw��51
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��11��h/tw��79

			//�������ܽ��棩
			//n<0.2
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��19��h/tw��51
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��33��h/tw��79
			//0.2��n��0.6
			0.0f,0.0f,0.0f,11.7f,23.3f,28.3f, //b/tf��19��h/tw��45
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f, //b/tf��33��h/tw��68

			//�������
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		};

		int Sys_DamperPerformGradeNum = 6; //һ���������۱�׼
		
		float Sys_DamperGradeDefault[6];//2020.7.10����
		float Sys_DamperGrade_n[6];//2020.6.4��������ʱ�ò�����Ϊ���������������������ֿ�������
		float Sys_DamperGrade_t[6];//2020.6.15��������ʱ�ò�����Ϊ���������������������ֿ�������
	};

	CString GetSteelDriftString(int i, int j)
	{
		CString str;
		float X = Sys_SteelDirftGradeDefault[i][j];
		float Y = Sys_SteelDirftNGradeDefault[i][j];

		if (abs(Y) > 0.f) str.Format(L"%g-%gn", X, Y);
		else str.Format(L"%g", X);

		return str;
	};
	BOOL GetSteelDriftLmt(float* fA, float* fB, CString str)
	{
		CStringArray sArr;
		SplitCString(str, &sArr);

		if (sArr.GetCount() > 0) *fA = _ttof(sArr[0]);
		if (sArr.GetCount() > 1) *fB = _ttof(sArr[1]);

		return TRUE;
	}
	int GetSteelDriftPerform(STRUCT_TYPE iStrucType, SECTION_SHAPE iSecType, float fDrift, float fKHB, float fGHB, float fComp = 0.f);

	//�������۱�׼˵��
	CString GetPerformNote();

	void Read(CASCFile& fin, int iPerformType);
	void Write(CASCFile& fout, int iPerformType);
	CString GetStrSwitch(CString str);
	CString* GetPerformGradeName();
	COLORREF* GetPerformGradeColor();
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

#define Sys_ComponentNum 392 //��������
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
extern "C" _SSG_DLLIMPEXP COLORREF g_Sys_Structural_member_Color[SYSTEM_STRUCTURAL_MEMBER_COLOR_NUMBER];

