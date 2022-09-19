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

//延长线交点类型
enum EXT_TYPE
{
	EXT_NONE,          //两个线段的延长线无交点
	EXT_INNER,         //延长线方向上在目标线段上有内部交点
	EXT_EXT,           //延长线方向上在目标线段外有交点
	EXT_RESERVE_INNER, //延长线反方向上在目标线段上有内部交点
	EXT_RESERVE_EXT,   //延长线反方向上在目标线段外有交点
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

//框架结构类
class _SSG_DLLIMPEXP CFrame : public CRemoveInvalidPrimitive
{
public:
	CFrame(void);
	CFrame(const CFrame &frame) {*this=frame;}
	~CFrame(void){Clear();} 

public:
	float m_fVer;  //版本号,合法值1.1,2.0，此版本号为读入的数据文件版本号，写出文件后将被改变
	float m_fExeVer; //2021版630临时判断版本

	//几何数据
	CArray<CVertex,CVertex&> m_aVex;   //点数组,所有框架图元顶点共用该数组，包括线条、多边形面、轴网、辅助线
	CArray<CLine,CLine&>  m_aLine;     //结构线数组

	//结构数据
	CArray<CBeamStruc,CBeamStruc&>  m_aBeam;    //梁和柱和斜撑的数组
	CArray<CLine,CLine&> m_aGuides;				//辅助线数组
	CArray<CPlateStruc,CPlateStruc&> m_aPlate;	//板和墙数组，存储楼板、墙面结构

	//Sigma 1.0
	std::vector<CSolidStruc> m_vSolid;				//实体

	CSectionCollection m_cSection;					//截面信息
	CDamperSectionCollection m_cDamperSection;		//一般连接截面信息	//乔保娟 2015.5.19
	CDamperGroupSecCollection  m_cDamperGroupSec;	//减震构件组  邱海 2016年10月27日
	CPlateSectionCollection m_cPlateSection;		//面构件截面信息
	CMaterialCollection m_cMaterial;				//材料信息
	//临时使用：tendon使用及添加vector
	vector<int> m_cMaterialTendon;
	CEdgeStrucCollection m_cEdgeCollection;			//边缘构件信息,为了显示边缘构件的墙构成关系用
	CBoundaryCollection m_cBoundary;				//边界条件信息
	CNonISOModel m_cNonISOModel;					//非隔震模型参数

	//分组信息
	CStageCollection m_cStage;   //分步模型信息，将模型按照建设过程分成若干部分，逐次提交计算
	CGroupCollection m_cGroup;
	CGroupCollection m_cDamperGroup;

	//网格控制参数
	float m_fElmSize;			//网格特征尺寸
	float m_fAlphaPlate,m_fBetaPlate;		//楼板网格生成参数
	float m_fAlphaWall,m_fBetaWall;		//墙体网格生成参数
	int m_nWallBeamLayer;
	float m_fWallBeamLayerSize;
	float m_fWallBeamLayerMinSize;
	BOOL m_bAntiBeamPillarAsOne;
	BOOL m_bAlongBraceAsOne;

	//分析控制参数
	BOOL m_bScaleIrrMass;
	BOOL m_bScaleSelectedMass;
	BOOL m_bScaleIrrByFactor;

	float m_fScaleFactor;	//暂时没存
	float m_fMinTriAngle;	//没用
	float m_fMinQuadAngle;	//没用
	float m_fMinLength;
	float m_fMinTriArea;
	float m_fMinQuadArea;

	//项目通用参数
	CString m_sCurCase;  //当前工况(组合)名称

	//刚性隔板信息
	int m_nRigidBody;	//隔板数
	int *m_pRigidBody;	//中心点编号


	//计算控制
	BOOL m_bStatic;				//是否静力求解
	BOOL m_bExplicitStatic;		//是否显式静力计算
	BOOL m_bDynamic;			//是否动力计算
	BOOL m_bExplicitDynamic;	//是否显式动力计算
	BOOL m_bMaxFreq;			//是否求最大频率
	BOOL m_bModeAnalysis;		//是否模态分析
	BOOL m_bModeAnalysisDamage;		//是否实时模态分析

	//隐式静力加载参数
	BOOL m_bUseRebar;	//是否计入钢筋作用
	UINT m_iMaxSteps; // 最大迭代次数，5000
	float m_fStaticTol;// 收敛精度 ，0.00001

	//显式静力加载参数
	float m_fStaticTimeStep;   //采用显式计算模拟重力加载的时间，采用显式分析进行竖向荷载加载，有效

	//隐式动力加载参数，目前不提供

	//进行最大频率分析，有效
	UINT m_iMaxFreqSteps; //=10000;最大频率的迭代步数
	float m_fMaxFreqTol; //=0.0000001;最大频率的收敛精度（相对精度）

	//模态分析控制参数
	float    		m_fMinFreq;     //特征值下限;0
	float    		m_fMaxFreq;     //特征值上限;5000
	UINT			m_nModes;		//振型数
	UINT			m_iModalAnalysisMethod;		//振型数
	float			m_fWallBeamReductCoef;		//连梁刚度折减系数
	BOOL			m_bX;		//地震作用方向
	BOOL			m_bY;		//地震作用方向
	BOOL			m_bZ;		//地震作用方向
	int				m_nLancSteps;		////lanczos过程的迭代步数;500
	BOOL	  		m_bEvalVec;     //是否计算特征向量;false
	BOOL			m_bFilterLocal;		//地震作用方向
	BOOL      m_bCalcuNonIso;//隐式分析同时计算非隔震模型 V2021
	BOOL        m_bCalSubStru; //  隐式分析同时计算层间隔震结构下部结构  用于复模态分析组装非比例阻尼矩阵  林思齐 20210602
	//整体缺陷
	float m_fOverallImperfect;	//缺陷最大值
	float m_fImperfectAngle;//缺陷角度
	int m_iOverallImperfectMode;

	//显式动力分析
	CLoadCollection m_cLoad; //荷载工况组合集合
	CLoadCollection m_cLoadDesign; //荷载工况组合集合,用于设计
	CLoadCollection m_cLoadStatic; //非线性静力分析
	CLoadCollection m_cLoadElastic; //等效弹性分析
	//CLoadCollection m_cLoadGenTH; //通用时程分析
	//CLoadCollection m_cLoadPush; //显式静力推覆
	CWaveCollection m_cWave; //荷已选地震波集合
	CFunctionCollection m_cFunc;//时程函数
	//CLoadSet m_cLoadSet;//荷载集合

	int   nModalDamage;       //进行实时模态分析的次数 //乔保娟2015.12.25
	CString sModalCaseName[Sys_Max_ModalDamage];	//实时模态分析工况名称	
	float fModalTime[Sys_Max_ModalDamage];	//实时模态分析时间 
	//关联表，单独读取，不包含在本类Read中
	CArray<COutput,COutput&> aOutput; //输出的分量表
	float fDisStep,fForceStep,fGroupStep;


	CGeneralCollection m_cGenLoad; //荷载工况集合:1恒1活1风1地震

	//2020年11月6日 静力荷载工况及工况组合
	CStaticLoadCaseCollection m_cStaticLoad;
	CDynamicLoadCaseCollection m_cDynaLoad;
	CLoadCaseCombCollection m_cLoadComb;

	CWindCollection m_cWindLoad; //风荷载工况集合
	CRSFunctionCollection m_cRSFunction;
	CRSLoadCaseCollection m_cRSLoadCase;

	//屈曲分析
	UINT m_nBucklingModes;		//振型数
	BOOL m_bBucklingOverallDefect;
	BOOL m_bBucklingMemberDefect;

	// 复模态分析控制参数  林思齐 20210526
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
	//其它控制参数

	//按位控制参数
	//bit0-是否向墙内延伸梁单元0x01
	//bit1-墙梁至少剖分两层0x02
	//bit2-生成单元时底座结点自动固支0x04
	//bit3-是否考虑自重0x08,如果考虑自重，将自重加到fext中,否则只计入mass
	//bit4-附加外荷载转为质量0x10,如果为1，将外荷载加到mass中,否则只计入fext
	//bit6~bit8,求解器类型：7--SSG求解器,0--PARDISO求解器,1--MUMPS求解器
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

	//层间位移角位置信息
	int m_nDriftPos;  //位置个数
	CVertex m_DriftPos[Sys_MaxDriftNum];  //位置坐标，只使用x,y,z

	//存储在单独文件中：FILE_VISIBLEINFO
	CVisibleStruct m_cVisible;  //模型可见分类

	//存储在单独文件中：FILE_COMBINEFRAME
	CCombineFrameCollection m_cCombine;  //竖向组合构件，用于计算组合构件内力，生成网格时生成数据，模型解锁时清除数据

	//临时数据
	//读文件的时候赋值，用于局部编码和数组下标转换
	int m_nBeam,m_nPillar,m_nBrace,m_nEdge;
	int m_nLink;	//乔保娟 2015.5.19
	int m_nPlate,m_nWallCol,m_nWallBeam;
	
	int m_nTowers; //分塔数=最大塔号+1，要求塔号连续

	int m_nSolid;	//sigma 1.0实体
	bool AddSolidByFaceVertex(const int *vex, int nvex, const int *face, int nface, int iStory, const CStory *pStory);
	bool AddSolid(CSolidStruc &newsolid, int *nNewSolid = NULL, int *pNewSolidID = NULL);
public:
	////////////////基础函数////////////////

	CFrame & operator=(const CFrame &frame);

	void Clear();  
	//删除所有依赖于SSG的中间文件
	void RemoveAllIntFile(void);
	//删除所有计算结果文件,sPrjName项目文件
	void RemoveAllResultFile(void);	//qiao
	BOOL IsVersion10() {return m_fVer<2.0f-0.01f;}	//1.0及1.1版本
	BOOL IsVersion20() {return (m_fVer>2.0f-0.01f&&m_fVer<2.0+0.01f);}	//2.0 //3.1版本
	BOOL IsVersionBigEqual20() {return (m_fVer>2.0f-0.01f);}
	BOOL IsVersion32() {return (m_fVer>3.2f-0.01f&&m_fVer<3.2+0.01f);}	//3.2   //2016版本
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
	////////////////建模函数////////////////

	//增加线段,计算与交叉点和分割线
	//输入：newline--新线段, pStory--楼层数据
	//输出：nNewSegment--新线被分成的线段数,指针,pNewSegmentID为NULL时不输出该数据
	//      pNewSegmentID--新线段的ID数组,由外部程序维护,必须足够大,pNewSegmentID为NULL时不输出该数据
	void AddStructLines  (CLine &newline,const CStory *pStory,int *nNewSegment,int *pNewSegmentID,BOOL bBreakByStory=TRUE); //增加结构线
	BOOL AddStructLinesInStory(const CVertex &v1,const CVertex &v2,const int iStory,int *nNewSegment=NULL,int *pNewSegmentID=NULL);  //根据两个点坐标增加结构线,2个点可能不在同一楼层，比如柱的端点
	void AddGuides(CLine &newline,const CStory *pStory,BOOL bBreakByStory=TRUE); //增加辅助线
	void AddGuidesInStory(const CVertex &v1,const CVertex &v2,const int iStory); ///根据两个点坐标增加辅助线,v1,v2必须处于同一楼层,需要判断端点是否存在,若v1,v2不能存在则增加
	void AddGuidesInStory(CLine &line); //增加辅助线,line的端点必须处于同一楼层,不用判断端点是否存在

	//直接在数组中增加梁柱，不做布尔运算，需要计算局部坐标，返回数组下标
	int AppendBeam(CBeamStruc &newbeam);

	//直接在数组中增加板或墙，不做布尔运算，需要计算局部坐标，返回数组下标
	int AppendPlate(CPlateStruc &newplate);

	//输入：newplate--新板结构
	//输出：nNewPlate--新板被分成的板数，不被分割时为1,指针,nNewPlate为NULL时不输出该数据
	//      pNewPlateID--新板的ID数组,由外部程序维护,必须足够大,pNewPlateID为NULL时不输出该数据
	BOOL AddPlate(CPlateStruc &newplate,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//将plateid1与其它构件做布尔运算
	void PlateCross( int plateid1,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//给定本楼层的两个点,按分组规定创建墙,成功返回TRUE
	BOOL AddWall(const CVertex &vex1,const CVertex &vex2,int iStory,const CStory *pStory);
	//根据nvex个点的x,y坐标创建墙,成功返回TRUE
	BOOL AddWall(const int *vex,int nvex,int iStory,const CStory *pStory);

	//把点添加到结构上，计算点是否在某结构线或面上，如果是，需要修改结构
	//如果iLineType=1，添加到辅助线里面，如果iLineType=2，添加到结构线里面，并且修改相关的结构
	//输入：pointID--点ID
	void CrossVertex(int pointID,int iLineType);
	void CrossVertex(const CVertex &vex,int iLineType);

	BOOL DeleteVex(int id); //根据点ID判断是否该点是否是孤立点,是则置为无效,成功删除返回TRUE
	void DeleteGuides(int id); //删除辅助线，以及相关的孤立点
	BOOL DeleteLine(int id); //删除无用的结构线，以及相关的孤立点,成功删除返回TRUE
	void DeleteBeam(int id); //删除梁或柱结构，以及相关的孤立结构线和点

	void DeletePlate(int id); //删除板或墙，以及相关的孤立结构线和点
	void ReplaceVertex(int discard_vex,int reserve_vex);  //将discard_vex结点用reserve_vex替换，同时删除discard_vex,只是针对线结构进行简单代替，不检查拓扑结构变化
	void MergeVertex(int discard_vex,int reserve_vex); //将旧点与新点合并，保留新点，完成点编号替换，处理拓扑关系的变化，处理退化的线和面、以及相关构件
	void SpliteBeam(int nSel,const int *pSelNames, int nSegments);  //对所选线构件拆分，用到选择集

	BOOL MergeCoinVertex(float fError = g_cSysSizePara.Sys_PointError); //有合并返回TRUE

	void RearrangeID();  //清理无效图元	
	void RearrangeBeam(); //需要重新整理线构件顺序：梁(包括虚梁、纵筋)---柱---撑---边缘构件
	void RearrangePlate(); //需要重新整理面构件顺序：板--墙梁--墙柱

	////////////////获取属性函数////////////////

	/////////////////////////////////////////////////////
	//基本假设： 2012/11/13
	//假设点不能重叠，结构线可以重叠，线构件基于结构线可以重叠
	//一个空间位置只能有一个点
	//两个点可以定义多条结构线
	//两个点只能定义一根辅助线
	//每根结构线上只能有一根线构件
	/////////////////////////////////////////////////////

	//点的相似性定义：X,Y,DZ分别相等
	int GetSimilarVertex(int pointid,int iStory); //按给定点pointid的XY及ΔZ(=楼层标高-点的Z坐标)坐标在指定楼层寻找靠近点的ID，没找到返回-1
	int GetSimilarVertex(float x,float y,float dz,int iStory); //按给定的XY及ΔZ(=楼层标高-点的Z坐标)坐标在指定楼层寻找靠近点的ID，没找到返回-1
	int GetSimilarGuideLine(int lineid,int iStory);  //按给的线ID找到对应楼层的相似的辅助线ID，没找到返回-1
	
	int GetSimilarLines(int lineid,int iStory,int *pLineIDs,int maxsize); //按给的线ID找到对应楼层的相似的结构线IDs，返回线段个数
	int GetFirstSimilarLine(int lineid,int iStory);  //按给的线ID找到对应楼层的相似的结构线ID，端点满足相似性，没找到返回-1

	int GetSimilarBeams(int beamid,int iStory,int *pBeamIDs,int maxsize); //按给的梁或柱ID找到对应楼层的相似的梁或柱ID，结构线满足相似性，要求结构类型相同，返回构件个数
	int GetFirstSimilarBeam(int beamid,int iStory);  //按给的梁或柱ID找到对应楼层的相似的梁或柱ID，结构线满足相似性，要求结构类型相同，没找到返回-1

	int GetSimilarPlate(int plateid,int iStory);  //按给的板或墙ID找到对应楼层的相似的板或墙ID，结构线满足相似性，没找到返回-1

	int GetVertexID(float x,float y,float z);  //按给定的坐标搜索靠近点的ID，没找到返回-1
	int GetVertexID(const CVertex &v);   //按给定的坐标搜索靠近点的ID，没找到返回-1
	int GetVertexID(const Vector4 &v);   //按给定的坐标搜索靠近点的ID，没找到返回-1
	int GetLineIDs(int idP1, int idP2,int *pLineIDs,int maxsize); //根据点ID找到结构线IDs,返回线段个数，线段ID放在pLineIDs中
	int GetFirstLineID(int id1, int id2); //根据点ID找到遇到的第一条线ID--heby,未找到则返回-1，仅仅判断点号相等

	int GetGuidesID(int id1, int id2);  //根据点ID找到辅助线ID,未找到则返回-1
	int GetBeamID(int lineid);      //按给的线ID 找到使用这条结构线的梁或柱的ID，没找到返回-1
	int GetPlateIDs(int lineid,int *pPlateIDs,int maxsize) const;  //按给的线ID，找到使用这条结构线的板或墙的ID，返回个数，板ID保存在pIDs中
	int GetPlateID(const CPlateStruc &plate);   //按给面的几何数据，返回板或墙的ID，没找到返回-1

	float GetInclineCos(const CLine &line);  //得到结构线的倾角余弦(首点指向末点的矢量与Z轴的夹角)，范围：-1 -- 1	
	float GetInclineCos(const CBeamStruc &beam);  //得到结构的倾角余弦(首点指向末点的矢量与Z轴的夹角)，范围：-1 -- 1
	float GetInclineAngle(const CLine &line);  //得到结构线的倾角(首点指向末点的矢量与Z轴的夹角)，单位：弧度，范围：0--PI
	float GetInclineAngle(const CBeamStruc &beam);  //得到结构的倾角(首点指向末点的矢量与Z轴的夹角)，单位：弧度，范围：0--PI

	float BeamLength(int id);  //计算线构件长度
	float BeamLength(CBeamStruc &beam);  //计算线构件长度
	float PlateArea(int id);   //计算面构件面积
	float PlateArea(CPlateStruc &plate);   //计算面构件面积
	float GetMinMax(Vector4 &MinCoor,Vector4 &MaxCoor); //返回外包直径
	//搜索面构件坐标范围，返回最小楼层号
	int GetPlateMinMax(int plateid,CVertex &MinCoor,CVertex &MaxCoor);
	int GetPlateMinMax(CPlateStruc &plate,CVertex &MinCoor,CVertex &MaxCoor);

	//得到所有施工阶段的图元数据
	//vBeam,vPlate--输出每个施工阶段的构件编号
	void GetStepStruct(vector<int> vBeam[],vector<int> vPlate[],int nStory); 

	//得到材料库到使用库的索引，及使用库到材料库的索引，传出创建指针和用到的材料名称集合，调用程序需要清除，返回值为使用库的材料数
	int GetUsedConc(int *&pIndexOfLib2Used,int *&pIndexOfUsed2Lib,CStringArray &aConcList);  //混凝土
	int GetUsedSteel(int *&pIndexOfLib2Used,int *&pIndexOfUsed2Lib,CStringArray &aSteelList); //金属,，包括型钢和钢筋材料

	//统计各种构件的数量
	STRUCT_COUNT GetStructCount(void) const;	

	//建立点到墙的索引,并记录结构线是否被梁和墙用到
	void GetWallConnection(CPointWallIndex *pPointConnect,LINE_USED *pLineUsed) const;

	//找到竖向面构件的上端线最外侧的两个端点，去掉中间点
	//返回：TRUE--与天花板相接(仅指高程)，FALSE--不与天花板相接(仅指高程)
	//有上端线，与天花板相接，id1,id2有效，返回TRUE
	//有上端线，不与天花板相接，id1,id2有效，返回FALSE
	//没有上端线，一个点与天花板相接，id1有效,id2=-1，返回TRUE
	//没有上端线，不与天花板相接，id1,id2=-1，返回FALSE
	BOOL GetTopPoint(const CPlateStruc &plate,int &id1,int &id2) const;

	//找到竖向面构件的下端线最外侧的两个端点，去掉中间点
	//返回：TRUE--与地板相接(仅指高程)，FALSE--不与地板相接(仅指高程)
	//有下端线，与地板相接，id1,id2有效，返回TRUE
	//有下端线，不与地板相接，id1,id2有效，返回FALSE
	//没有下端线，一个点与地板相接，id1有效,id2=-1，返回TRUE
	//没有下端线，不与地板相接，id1,id2=-1，返回FALSE
	BOOL GetBottomPoint(const CPlateStruc &plate,int &id1,int &id2) const;
	
	//按边界顺序返回四个角点ID，左下、右下、右上、左上
	BOOL GetCornerPoint(const CPlateStruc &plate,int &left_bottom,int &right_bottom,int &right_top,int &left_top) const;

	//找到墙的三条或四条边线IDs,如果是上三角形，则vDown.size()=0,如果是下三角形，则vUp.size()=0
	//vLeft,vRight,vUp,vDown,每条边线段编号(分别为左、右、上、下)，每个墙最多四条边
	//线段编号按照一致的右手螺旋，vLeft--vDown--vRight--vUp--vLeft的线段ID一定首尾相接，某个数组为0时需要跳过
	//支持中间半截墙
	//返回边数
	int GetWallEdge(int wallid,vector<int> &vLeft,vector<int> &vRight,vector<int> &vUp,vector<int> &vDown);
	int GetWallEdge(CPlateStruc &wall,vector<int> &vLeft,vector<int> &vRight,vector<int> &vUp,vector<int> &vDown);

	//找到本楼层该点下所有竖向结构线(被斜撑用到的除外)，不管是否是墙的边界
	void GetLinesByVex(int vexid,list<int> &vLines);
	void GetLinesByVex(int vexid,int &nlines,int *pline);

	//创建点到柱子的连接关系，包括边缘构件和柱子
	PT2LINESTRUCT *CreatePt2Pillar(void);	

	//求直线与面构件的交集（在多边形内部的线段）
	//输入直线的两个点v1,v2
	//返回的线段端点放在p1,p2
	BOOL GetIntersectionLine(CVertex v1,CVertex v2,CPlateStruc &plate,CVertex &p1,CVertex &p2);

	////////////////设置属性函数////////////////

	void Set2ndBeam(int nSel,const int *pSelNames,BOOL b2ndBeam); //对所选构件设置成次梁

	////////////////数据检查函数////////////////

	BOOL IsValidPlateLine(int lineid);	//判断结构线是否可以形成板
	int CheckStage(int nStory);  //检查修改阶段设置的有效性，返回阶段数

	//是否墙梁，最大最小z坐标差不等于楼层高度，并且顶部和底部为直线的墙
	BOOL IsBeamWall(const CPlateStruc &plate) const; 
	BOOL IsBeamWall(int idm);
	//跟踪墙梁，返回值：0--不是墙梁，1--墙梁，2--未知
	int TraceBeamWall(const CPlateStruc &plate,vector<int> &vBraceLine,float &minz,float &maxz) const; 
	// 1-顶部与楼层相连；0-底部与楼层相连；-1-不与楼层相连
	int BeamWallPos(const CPlateStruc &plate) const; //qiaobaojuan 2016.3.21


	////////////////输入输出函数////////////////

	BOOL Read(CString fname,CProjectPara cPrjPara,BOOL bOnlyModel=FALSE);
	BOOL Write(void);
	BOOL Write2020(void);
protected:
	

public:
	BOOL MergeSSG(CString fname, float dx, float dy, float dz, float angle);

	//按照约定规则改变线段方向，水平线向右为正，竖向线向上为正，返回：TRUE-修改，FALSE-未修改
	BOOL CheckLine( int iLine,float fTanAng );	
	BOOL CheckLine( CLine &line,float fTanAng );

	//iLineType=1,增加到m_aGuides，iLineType=2增加到m_aLine，newline可以跨楼层
	void AddLinesMulStory(int iLineType,const CLine &newline,const CStory *pStory,int *nNewSegment=NULL,int *pNewSegmentID=NULL,BOOL bBreakByStory=TRUE); 

	//被AddLinesMulStory调用，不考虑按楼层断开，//iLineType=1,增加到m_aGuides，iLineType=2增加到m_aLine
	void AddLinesInStory(int iLineType,const CLine &newline,int *nNewSegment=NULL,int *pNewSegmentID=NULL); 

	//断开结构线，并修改受影响的构件，idOldLine--原线段IDM，newpoint--截断点IDM
	void BreakLine(int idOldLine,int newpoint);

	//断开辅助线，不影响构件，idOldLine--原线段IDM，newpoint--截断点IDM
	void BreakGuides(int idOldLine,int newpoint);

	//切割多边形，plateid--原多边形ID，lineid--线段的ID
	LINE_CROSS_POLY BreakPlate(int lineid,int plateid);

	//计算三维空间中两线段交点，同时旧线被交点断开，并修改相关结构，但不增加新线的子线段
	//输入：iLineType=1辅助线，iLineType=2结构线；idP1,idP2为新线端点ID，lineid为线段ID
	//输出：交点数nCross(最多为2，可以是idP1,idP2),交点ID数组pCross[2]
	//返回值：1为两线段相交于1点，0不相交，2两条线部分重合，-1两条线有一个端点重合且不共线，-2两条线完全重合
	int LineCross3D(int iLineType,int idP1,int idP2,int lineid, int &nCross,int *pCross,int maxcross);

	//功能：计算三维空间中线段与面相交，并分割面
	//输入：lineid为线段ID，idPlate为面结构ID
	//返回值： LINE_CROSS_POLY
	LINE_CROSS_POLY LineCrossPolygon3D(int lineid, int idPlate,int *nNewPlate=NULL,int *pNewPlateID=NULL);

	//给定首末点以及目标线段，返回延长线交点与末点的距离（负值表示交点在延长线的相反方向），交点坐标放在ext_point中
	float GetExtendCrossPoint(const CVertex &start_point,const CVertex &end_point,const CLine &line,Vector4 &ext_point,EXT_TYPE &iType);


	//根据构件信息计算点和线的阶段、塔号、楼层
	void UpdateGeoInfo(void);

	//根据楼层信息重新生成点的跨层属性
	void UpdateVertexCrossInfo(void);


	BOOL FindVex(int vexid,int plateid);   //给定点是否在面构件边界上
	
	//用阶段数据更新构件的阶段号，设置阶段和读入数据时使用
	void UpdateStage(int nStory);

	//根据地震动信息更新工况对应地震动信息
	BOOL UpdateLoadCaseWaveData(CArray<int,int> &aRunCase,CLoadCollection &cLoads,bool bCheckWave=false);

	//根据Static名称得到对应的Id号
	int GetStaticCaseIdByName(CString sName);
	//根据Static类型得到类型名称
	CString GetStaticCaseTypeName(STCASE_TYPE nType);
	//根据Static类型名称得到类型
	STCASE_TYPE GetStaticCaseType(CString sName);
	//计算动力荷载工况总时长
	float GetDynamicCaseAllTime(int iDynaCase);
	//根据Dynamic名称得到对应的Id号
	int GetDynamicCaseIdByName(CString sName);
	//根据Function名称得到对应的Id号
	int GetFunctionIdByName(CString sName);
	//删除重编静力荷载工况
	void ReorderStaticLoadCase(int *pMap);
	//删除重编动力荷载工况
	void ReorderDynaLoadCase(int *pMap);
	//检查网格与几何模型是否对应
	void CheckMesh() const;
	//点共线
	bool IsVertexColline(const CVertex &va, const CVertex &vb, const CVertex &v);
};

