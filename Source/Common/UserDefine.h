#pragma once

#include "SysPara.h"
#include "ASCFile.h"
#include "HeadDefine.h"

const int SYSTEM_COLOR_NUMBER=35;	//邱海 2017年8月29日
const int SYSTEM_SIZE_NUMBER=35;	//2016.7.12


extern "C" _SSG_DLLIMPEXP float GetPrivateProfileFloat(LPCTSTR lpAppName,LPCTSTR lpKeyName,float fDefault,LPCTSTR lpIniFile);
extern "C" _SSG_DLLIMPEXP void  WritePrivateProfileFloat(LPCTSTR lpAppName,LPCTSTR lpKeyName,float fData,LPCTSTR lpIniFile);


//定义的剖面或断面参数
struct _SSG_DLLIMPEXP PROFILE_PARA
{
	CString sName;
	int prof_type;  //剖面类型,0-剖面，1-断面
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
			COLORREF Sys_Backgroundcolor; //窗口背景色
			COLORREF Sys_VexColor;  //顶点颜色，结构缺省颜色
			COLORREF Sys_GuideLineColor;  //线条颜色(辅助线)
			COLORREF Sys_StructLineColor;  //线条颜色(结构线)
			COLORREF Sys_BoundaryLineColor;  //边界线颜色

			COLORREF Sys_BeamColor;  //梁线条颜色
			COLORREF Sys_PillarColor;  //柱线条颜色
			COLORREF Sys_BracingColor;  //斜撑线条颜色
			COLORREF Sys_EdgeColor;  //边缘构件颜色
			COLORREF Sys_HideBeamColor;  //虚梁颜色
			COLORREF Sys_LongiRebarColor;  //连梁纵筋颜色
			COLORREF Sys_2ndBeamColor;  //次梁颜色
			COLORREF Sys_PlateColor;  //楼板颜色
			COLORREF Sys_WallColor;  //墙颜色
			COLORREF Sys_BeamWallColor;  //墙梁颜色
			COLORREF Sys_LinkColor;  //阻尼器线条颜色	//乔保娟 2015.5.19

			COLORREF Sys_LineLoadColor;  //荷载线颜色
			COLORREF Sys_AxisColor;  //坐标轴颜色,分量最大值为
			COLORREF Sys_HighlightPointColor;  //拾取点高亮显示颜色
			COLORREF Sys_HighlightColor;  //拾取物体高亮显示颜色
			COLORREF Sys_CurrentColor;  //当前选中的物体显示颜色
			COLORREF Sys_ElasticColor;  //橡皮筋显示颜色

			COLORREF Sys_OriginalColor;		//原始虚图形显示颜色
			COLORREF Sys_SectionConcColor;	//截面示意图中混凝土颜色
			COLORREF Sys_SectionSteelColor; //截面示意图中钢材颜色
			COLORREF Sys_LabelColor;		//截面示意图中标注颜色
			COLORREF Sys_GreyColor;			//禁止控件的颜色

			COLORREF Sys_ProfileColor; //外轮廓长方体的颜色
			COLORREF Sys_CommentsColor; //标注文字的颜色

			COLORREF Sys_AnticulatePointColor;//铰接点颜色
			COLORREF Sys_EdgeWallColor;//边缘构件分支颜色
			COLORREF Sys_DriftPillarColor;//层间位移角柱子颜色

			COLORREF Sys_MaxValueColor; //显示数值中最大值颜色
			COLORREF Sys_MinValueColor; //显示数值中最小值颜色
			COLORREF Sys_WarningColor; //显示数值不满足要求的颜色

			
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
			//采用像素为单元的图元为固定大小，不支持缩放，下同
			//采用米为单元的图元支持缩放
			float Sys_RefLineWidth;         //辅助线、结构线宽度(像素)
			float Sys_BeamLineWidth;        //梁线条宽度(像素)
			float Sys_HighLightLineWidth;   //高亮线条宽度(像素)
			float Sys_MeshLineWidth;        //网格线条宽度(像素)
			float Sys_NormalPointSize;      //普通点绘制尺寸(厘米)
			float Sys_HighLightPointSize;   //高亮点绘制尺寸(像素)，固定大小，不缩放
			float Sys_AxisLineWidth;        //坐标轴线条宽度(像素)

			float Sys_PointError;			//点距容限，单位：米
			float Sys_AngleError;			//角度容限，单位：度
			float Sys_AngleIncrease;        //绘图角度增量，单位：度
			float Sys_DistPrecision;        //移动点或线时的距离分辨率，单位：米
			float Sys_InitGraphRange;		//初始绘图范围(米)
			float Sys_ProfileThickness;		//断面层厚度(米)
			float Sys_PlateShinkRatio;		//收缩多边形的比例，用于框线显示模式下标记多边形面
			float Sys_AmbientRatio;         //环境光强度,范围[0,1]
			float Sys_DirectRatio;          //方向光漫反射强度，范围[0,1]
			float Sys_RecentFiles;          //保留的项目历史清单数目
			float Sys_PickDelayTime;		//捕捉动作的延迟时间,单位：秒
			float Sys_LegendType;			//云图填充类型，0-连续，1-离散
			float Sys_LegendBlocks;			//颜色分级数，缺省12
			float Sys_BraceDrift;			//斜撑参与计算层间位移角[1-参与，0-不参与]
			float Sys_TriInsertRatio;		//生成三角网时插入点的最小比例[0.05,0.2]，值越小网格越均匀
			float Sys_TriInsertLoop;		//生成三角网时插入点的最大循环次数[1,10]，值越大网格越均匀
			float Sys_SpliteConcavePoly;	//自动拆分凹多边形
			float Sys_PolyInnerAngle;		//自动拆分凹多边形最大内角(度)
			float Sys_BlendMinAlfa;			//渲染时最小透明度[0,255]
			float Sys_MinVexSize;			//隐藏模型点的阈值(像素)
			float Sys_MinPointSize;			//隐藏网点的阈值(像素)
			float Sys_MinLineSize;			//隐藏线段的阈值(像素/米)
			float Sys_MinExtendSize;		//拉伸显示的阈值(像素/米)
			float Sys_AnticulateCircleRadius;//表示铰接的圆环半径(像素)
			float Sys_AnticulateOffset;		 //表示铰接的圆环向内偏移量(米)
			float Sys_HingeCircleRadius;	//表示塑性铰的圆环半径(像素)
			float Sys_HingeOffset;			//表示塑性铰的圆环向内偏移量(米)
			float Sys_OutputAve;			//单元结点结果输出平均阈值（%）
		//	float Sys_AdvancedFunc;			//高级功能

			//改动数据后注意修改SYSTEM_SIZE_NUMBER
		};
		float Sys_SizeArray[SYSTEM_SIZE_NUMBER];
	};
};

class _SSG_DLLIMPEXP  CAxeParameter
{
public:
	CAxeParameter(void);
	~CAxeParameter(void);

	float Sys_CoorCubicRatio;  //坐标原点小立方体的比例
	float Sys_ArrowAngle;   //坐标轴箭头半夹角，单位弧度
	int Sys_CoorFontSize;//坐标字体大小，单位：磅
	CString Sys_CoorFontName;//坐标字体名称
	float Sys_FontDeviation;   //字体精度，>=0
	int Sys_AxisPosition;  //坐标架位置
	BOOL Sys_bVectorFont; //是否矢量字体
};

//用于项目模型参数初始化的缺省数据，一般不作为模型的具体属性，之间存在一个映射过程
//其它不需要映射的模型属性可以直接保存在CFrame中
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

	enum {PRJ_NUMBER=56};	//乔保娟 2015.5.7

	//以下为标准格式，在SSG文件中定义
	/*0 */CString Prj_Name;						//项目名称
	/*1 */float Prj_BeamProtectLayerThick;		//梁钢筋保护层厚度(m)
	/*2 */float Prj_PillarProtectLayerThick;	//柱、斜撑钢筋保护层厚度(m)
	/*3 */float Prj_PlateProtectLayerThick;		//板保护层厚度(m)
	/*4 */float Prj_WallProtectLayerThick;		//墙保护层厚度(m)
	/*5 */int Prj_Nsty;							//楼层数，包括0层
	/*6 */int Prj_BaseStoryNum;					//地下室层数,地基层0不属于地下室
	/*7 */int Prj_OldBaseStoryNum;				//删除的地下室层数
	/*8 */float Prj_ConcDensity;				//混凝土重度kN/m3
	/*9 */float Prj_SteelDensity;				//钢材重度kN/m3
	/*10*/float Prj_GravityAcce;				//重力加速度m/s2
	/*11*/CString Prj_EdgeRebar;				//剪力墙边缘构件钢筋级别
	/*12*/CString Prj_LinkRebar;				//连梁纵筋钢筋级别
	/*13*/CString Prj_BeamStirrup;				//梁箍筋级别
	/*14*/CString Prj_ColumnStirrup;			//柱箍筋级别
	/*15*/float Prj_BeamLinkSpace;				//梁箍筋间距
	/*16*/float Prj_ColumnLinkSpace;			//柱箍筋间距
	/*17*/float Prj_WallHoriRebarSpace;			//墙水平分布筋间距(m)
	/*18*/float Prj_WallVertRebarSpace;			//墙竖向分布筋间距(m)
	/*19*/int Prj_WallSeisGrade;				//剪力墙的抗震等级 
	/*20*/int Prj_FrameSeisGrade;				//框架的抗震等级
	/*21*/int Prj_ConsEdgeSty;					//约束边缘构件层数 
//	/*21*/float Prj_SeisIntensity;				//设防烈度		//与下文重复，乔保娟注释掉	2015.5.7
	/*22*/BOOL Prj_SlabSelfWeight;				//自动读入楼板自重,TRUE--楼板自重已经被包含在外荷载中
	/*23*/BOOL Prj_BraceBool;					//斜撑参与布尔运算
	/*24*/STRUCT_SYSTEM Prj_StructSystem;		//结构体系

	//2.0新增参数
	/*25*/int Prj_FieldClass;					//场地类别 （对应关系：0-I0,1-I1,2-II,3-III,4-IV）
	/*26*/int Prj_FieldGroup;					//场地分组（对应关系：0-第一组，1-第二组，2-第三组）
	/*27*/float Prj_EarthQuakeGrade;			//地震烈度（必须为6, 7, 7.5, 8, 8.5, 9之一）
	/*28*/int Prj_EarthQuakeProbility;			//地震概率 (0-小震,1-中震,2-大震) 
	/*29*/int Prj_ExtendMethod;					//规范谱外推方法 (0-沿用前段公式，1-恒定值)
	/*30*/int Prj_PerformanceDesignGrade;		//性能化设计地震水准 (第0位为1表示小震，第1位为1表示中震，第2位为1表示大震)
	
	//以下参数未在SSG文件中定义
	/*31*/float Prj_BeamRebarDiameter;			//梁缺省钢筋直径(m)
	/*32*/float Prj_PillarRebarDiameter;		//柱缺省钢筋直径(m)
	/*33*/float Prj_PlateRebarDiameter;			//板和墙缺省钢筋直径(m)
	/*34*/float Prj_BeamRebarRatio;				//梁的缺省配筋率(%)，面筋和底筋
	/*35*/float Prj_PillarRebarRatio;			//柱的缺省配筋率(%)，水平筋和竖筋
	/*36*/float Prj_PlateRebarRatio;			//板缺省钢筋配筋率(%)
	/*37*/float Prj_WallRebarRatio;				//墙缺省钢筋配筋率(%)
	/*38*/float Prj_PlateDefaultThickness;		//板的缺省厚度(m)
	/*39*/float Prj_WallDefaultThickness;		//墙的缺省厚度(m)
	/*40*/int	Prj_WallConcLayer;				//缺省的墙构件混凝土层数
	/*41*/BOOL  Prj_CoorOffset;					//坐标点是否已经被构件偏移进行了修正，用户不能修改
	/*42*/float Prj_MaxQuadAngle;				//生成四边形网格时用到的参数，最大四边形内角，单位：度
	/*43*/float Prj_MaxTriAngle ;				//生成四边形网格时用到的参数，最大三角形内角，单位：度
	/*44*/int   Prj_nSmooth;					//网格光滑次数
	/*45*/float Prj_MinLineSize;				//最小单元尺寸系数，对梁单元有效，壳单元可不受此控制
	/*46*/BOOL	Prj_BeamOverlayStiffDeduction;	//梁柱钢骨混凝土截面扣减重叠刚度
	/*47*/BOOL	Prj_BeamOverlayAreaDeduction;	//梁柱钢骨混凝土截面扣减重叠面积
	/*48*/BOOL	Prj_PlateOverlayStiffDeduction;	//板墙钢骨混凝土截面扣减重叠刚度
	/*49*/BOOL	Prj_PlateOverlayAreaDeduction;	//板墙钢骨混凝土截面扣减重叠面积
	
	//2018新增参数
	/*50*/int	Prj_FortificationCategory;	//抗震设防分类
	/*51*/int	Prj_SlabSeisGrade;	//板的抗震等级 
	/*52*/int	Prj_SeisDetailsGrade;//抗震构造措施的抗震等级 提高两级 提高一级 不改变 降低一级 降低两级
	/*53*/int	Prj_IsolatStory;//隔震层位置
	/*54*/float	Prj_ImportanceCoef;//结构重要性系数
	/*55*/float	Prj_BearingCoef;//承载力抗震调整系数

	//定义的剖面或断面
	CArray<PROFILE_PARA,PROFILE_PARA&> m_aPrj_Profile;

	//临时数据
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
		BOOL bShow;		//是否提供交互修改
		CString sName;	//变量名称
		float fcoef;	//转换系数，读入用乘，输出用除
	}m_pAddr[PRJ_NUMBER]; //用于保存各参数地址，包括楼层数，但不包括m_aPrj_Profile

	void GetAddr(void); //被所有构造函数调用,用于初始化m_pAddr

public:
	//赋值运算符重载
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
//		/*21*/Prj_SeisIntensity			=para.Prj_SeisIntensity;			//乔保娟	2015.5.7
		/*22*/Prj_SlabSelfWeight		=para.Prj_SlabSelfWeight;				
		/*23*/Prj_BraceBool				=para.Prj_BraceBool;					
		/*24*/Prj_StructSystem			=para.Prj_StructSystem;		

		//2.0新增参数
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

	//从SSG文件中读入
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
			float Sys_MaxUndoStep;						//最大undo级数
			float Sys_AngStep;								//键盘方向键移动图形的角度步长，度
			float Sys_AutoSaving;							//定时自动保存工程(1-是，0-否)
			float Sys_AutoSavingTimeStep;			//定时自动保存工程时间间隔
			float Sys_SaveBackup;							//工程保存时同时保存副本
			float Sys_MaxBackupNumber;			// 工程保存最大副本数量
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
		int Sys_PerformType;//2为RBS，0为默认，1为倒塌//2019.11.27王丹
		CString Sys_PerformGradeNameRBS[5];//2019.11.27王丹
		COLORREF Sys_PerformGradeColorRBS[5];//2019.11.27王丹
		int Sys_bPerformDefault;//2020.4.1王丹，判断用户是否为第一次使用程序，不是为1
	
		float Sys_RebarSteelStrainRBS[3];//2019.12.30王丹
		float Sys_DcRBS[3];//2019.12.30王丹

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

#define Sys_ComponentNum 188 //分量名称
struct _SSG_DLLIMPEXP COMPONENT_COMMENT_TABLE
{
	CString sName;				//分量名称
	CString sComment;			//分量说明
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
