#pragma once

//#include "SysPara.h"
#include "HeadDefine.h"
#include "..\Common\Vector4.h"
#include "..\Common\Matrix4x4.h"
#include "..\Common\UserDefine.h"
#include "..\Common\EdgeStruct.h"
#include "..\Common\VisibleStruct.h"
#include "..\Common\EdgeStruct.h"
//#include "DebugInfoDlg.h"
//#include "Timediff.h"
#include "..\Common\Mesh.h"
#include "Shader.h"
#include "..\Platform\Profile.h"
#include<unordered_map>

#include "../../Lib/gl/include/GL/glew.h"
//#include "../../Lib/gl/include/GL/glxew.h"
#include "../../Lib/gl/include/GL/wglew.h"

const int DISPLAY_PATA1_NUM=12;  //显示开关参数个数
const int DISPLAY_PATA2_NUM=13;  //显示开关参数个数
const int DISPLAY_PATA3_NUM=8;  //显示开关参数个数	//20156.1.12

const int BUFSIZE=512;  //拾取缓冲区大小
const Vector4 Sys_LightPosition(-0.436f,0.218f,0.873f);  //灯光的方向余弦
//const float Sys_AmbientRatio=0.1f;   //环境光强度,范围[0,1]
//const float Sys_DirectRatio=1.0f;    //方向光漫反射强度，范围[0,1]



enum RENDER_TYPE
{
	RENDER_VERTEX,      //按顶点颜色渲染
	RENDER_PRIMITIVE,   //按图元颜色渲染
	RENDER_SMOOTH,      //按单元平均到结点渲染
};

enum COLOR_TYPE
{
	COLOR_BODY,    //按实体颜色绘制
	COLOR_VERTEX,  //按顶点颜色绘制
};

struct hash_vec
{
	size_t operator()(const Vector4& vc)const
	{
		return hash<float>()(vc.x) ^ hash<float>()(vc.y) ^ hash<float>()(vc.z);
	}
};

class _SSG_OPENGLDLL COpenGL//:CProfile
{
public:
	COpenGL(void);
	~COpenGL(void);

public:


	//属性
	BOOL m_bShowFrame; //TRUE--绘制框架，FALSE--绘制网格


	float m_fDiameter;  //图形最大尺寸,用于控制显示的坐标轴等尺寸
	Vector4 m_MinCoor;
	Vector4 m_MaxCoor;  //坐标范围
	struct MUL_PROJRCT *m_MP; //项目信息
	int m_nProjects; //项目数
	float m_fPointSize;  //普通点的大小，单位：像素

	/*m_bShowAuxVex(以下记为a)和m_bShowVex(以下记为b)的关系：
	绘制所有点=a         是否绘所有点=a && b
	绘辅助线  =A         是否绘相应点=A && b
	绘结构线  =B         是否绘相应点=B && b
	绘构件    =C         是否绘相应点=C && ~B && b

	所以，b是能否看到任何点的开关，a是能否看到辅助点的开关，不可能只单独看到辅助点

	(a,b)四种组合中，当a=TRUE,同时b=FALSE的状态无效
	设置参数时应强执行以下语句:a=TRUE，一定要b=TRUE，否则会出现指令不起作用：
	当b=FALSE,a的任何状态都无关紧要，最好设置为a=FALSE
	*/

	union 
	{
		struct
		{
			BOOL m_bShowVex;		  //是否显示点
			BOOL m_bShowBeam;         //是否显示梁
			BOOL m_bShowPillar;       //是否显示柱
			BOOL m_bShowPlate;        //是否显示板
			BOOL m_bShowWallColumn;         //是否显示墙柱
			BOOL m_bShowWallBeam;         //是否显示墙梁
			BOOL m_bShowBracing;      //是否显示斜撑
			BOOL m_bShowEdge;         //是否显示边缘构件
			BOOL m_bShowHideBeam;     //是否显示虚梁
			BOOL m_bShowLongiRebar;   //是否显示连梁纵筋
			BOOL m_bShowLink;     //是否显示阻尼器	//乔保娟 2015.5.21
			BOOL m_bShowRigid; //是否显示刚性隔板 贾苏 20231214
		};
		BOOL m_pbDisplayPara1[DISPLAY_PATA1_NUM];
	};

	union 
	{
		struct
		{
			BOOL m_bShowAuxVex;       //是否显示辅助点，m_bShowVex=TRUE才有效
			BOOL m_bShowGuides;       //是否显示辅助线
			BOOL m_bShowStructLines;  //是否显示结构线
			BOOL m_bShowBoundaryLine;  //是否显示边界线
			BOOL m_bShowAnticulate;   //是否显示铰接标识
			BOOL m_bShowComments;     //是否显示标注信息
			BOOL m_bShowLC;           //是否显示约束区长度
			BOOL m_bShowAxis;         //是否显示坐标轴
			BOOL m_bShowScale;        //是否显示窗口刻度
			BOOL m_bShowOuterFrame;   //是否显示外框线
			BOOL m_bShowLocalAxis;			//是否显示局部坐标系 2017年12月18日
			BOOL m_bShowRestraints;			//是否显示位移约束 2017年12月18日
			BOOL m_bShowVexCross;		//是否显示点跨层标识
		};
		BOOL m_pbDisplayPara2[DISPLAY_PATA2_NUM];
	};

	union
	{
		struct
		{
			//其它效果开关
			BOOL m_bShowFace;       //实体模式
			BOOL m_bSmoothVex;      //结点光滑
			BOOL m_bDrawByBody;     //结构拉伸
			BOOL m_bBeamBlend;      //水平线构件半透明模式
			BOOL m_bPillarBlend;    //纵向线构件半透明模式
			BOOL m_bPlateBlend;     //板半透明模式
			BOOL m_bWallBlend;      //墙半透明模式
			BOOL m_bRenderBlend;		//半透明云图
			BOOL m_bRenderLight;		//云图模拟光照效果 //2016.1.12
		};
		BOOL m_pbDisplayPara3[DISPLAY_PATA3_NUM];
	};

	BOOL m_bShowHinge;			//是否显示塑性铰	//2015.5.9
	BOOL m_bUseShader;
	BOOL m_bShowUndeform;     //是否显示原始参考图
	BOOL m_bOrtho;            //正交投影模式	
	BOOL m_bNodeCenterSmooth; //单元中心点是否参与物理场平滑显示
	BOOL m_bCoorOffset;       //坐标点是否已经考虑构件偏移
	BOOL m_bShowCrack;

	enum DRAWTYPE m_DrawType; //视图类型
	enum RENDER_TYPE m_iRenderType; //颜色渲染方式，只在绘制单元时有效，用于处理物理场的映射方式

	float m_fFontRatio;  //字体放大比例
	BOOL m_bVectorFont;  //是否矢量字体
	BOOL m_bBusy;  //防止绘图函数重入

	//Shader
	CShader m_cSmoothShader;

	BOOL m_bBackDraw;	//后台截图	2016.1.13

	//实现

	COpenGL & operator=(const COpenGL & gl)
	{
		if(this==&gl) return *this;

		ASSERT(FALSE);

		return *this;
	}

	//OPENGL绘图准备

	BOOL Init(HWND hWnd); //初始化绘图参数
	void InitVariables(void);  //初始化与项目有关系的数据,打开新项目之前要调用,清除历史数据
	BOOL ReleaseGraphicsDevice(void);  //关闭OpenGL绘图设备
	void CalProjectMatrix(int ScreenWidth,int ScreenHeight); //设置投影方式
	void Active(void); //激活当前窗口，将设备句柄与绘图句柄绑定
	void ReSize(int width, int height);

	//全屏显示
	BOOL FullScreen(BOOL bFullScreen=TRUE);

	//图形交互变换
	void InitSize(const Vector4 &vmin,const Vector4 &vmax,float maxDiameter,float ratio); //设置最大尺寸,并恢复到原始放大倍数
	void SetStory(int storymin,int storymax){m_iStoryMin=storymin;m_iStoryMax=storymax;} //设置楼层显示范围
	void SetStage(int stepmin,int stepmax) {m_iStageMin=stepmin;m_iStageMax=stepmax;} //设置施工阶段显示范围
	void UpdateCoorRange(Vector4 &vmin,Vector4 &vmax){m_vMin=vmin;m_vMax=vmax;}  //设置坐标显示范围
	BOOL SetProfile(const Vector4 *pProfile=NULL,int nProfile=4);  //设置剖面轮廓点,按边界顺序排列，缺省4个轮廓点，数据与之前不同则返回TRUE
	void ShowSelectZone(const Vector4 &vMin,const Vector4 &vMax,BOOL bShow); //设置选取图元的区域
	void ClearSelectZone() { m_bShowSelectZone = FALSE; };
	void ShowDriftPos(BOOL bShow);  //显示层间位移角位置信息

	//以下所有参数都是相对原来的数据
	void Zoom(float fRatio,int ScreenWidth,int ScreenHeight); //放大倍数
	void RotateX(float ang); //绕屏幕X轴旋转
	void RotateY(float ang); //绕屏幕Y轴旋转
	void Translate(int cx,int cy,int WinHeight); //移动图形, cx,cy为移动的屏幕距离,WinHeight为窗口高度
	void LookAtRH(Vector4 &eye, Vector4 &lookat, Vector4 &up);  //设置模型矩阵
	void SetViewRange(float fNear,float fFar);  //设置视野范围,<=0时使用缺省值

	//显示实体
	void ShowByBody(void);
	//显示剖面，fNear为剖面与眼睛距离,bCrossSection： TRUE-断面图还是FALSE--剖面图
	void ShowByProfile(float fNear,BOOL bCrossSection);

	//数据交换
	//结点或者顶点坐标
	void SetVex(int n,const CVertex *p);         //传入顶点坐标地址
	void SetNode(int n,const CVertex *p);         //传入网格结点坐标地址
	const CVertex *GetNode(void){return m_pNode;}         //得到结点坐标地址
	void SetDeformNode(int n,const CVertex *p){m_nNode=n; m_pDeformNode=p;}
	void SetNodeCenterSmooth(BOOL bNodeCenterSmooth) {m_bNodeCenterSmooth=bNodeCenterSmooth;}

	//单元数据
	void SetQuadElm(int n,const CQuadElm *p) {m_nQuadElm=n;m_pQuadElm=p;} //传入四边形单元数据
	void SetTriangleElm(int n,const CTriangleElm *p) {m_nTriangleElm=n;m_pTriangleElm=p;} //传入三角形单元数据
	void SetBeamElm(int n,const CBeamElm *p){m_nBeamElm=n;m_pBeamElm=p;}                 //传入梁单元数据
	void SetGroundElm(int nline,const RECT *pline) {m_nGroundLine=nline; m_pGroundLine=pline;}//传入地面网格数据
	void SetGroundOffset(Vector4 offset) {m_vOffset=offset;} //设置坐标偏移，一般每个时钟相应都要调用更新，模拟地面地震
	void SetBoundaryMesh(int n,const CBoundary *p){m_BoundaryMesh=n;m_pBoundaryMesh=p;}//传入节点约束数据


	//框架数据
	void SetGuides(int n,const CLine *p) {m_nGuides=n; m_pGuides=p;}             //传入辅助线坐标
	void SetLine(int n,const CLine *p) {m_nLineStruc=n; m_pLineStruc=p;}         //传入结构线数据
	void SetBeam(int n,const CBeamStruc *p){m_nBeamStruc=n; m_pBeamStruc=p;}     //传入梁和柱结构数据
	void SetSurf(int n,const CPlateStruc *p) {m_nPlateStruc=n; m_pPlateStruc=p;} //传入面结构数据
	void SetSection(const CSectionCollection *pSec) {m_pSec=(CSectionCollection *)pSec;} //传入截面数据，通于梁的显示
	void SetDamperSection(const CDamperSectionCollection *pSec) {m_pDamperSec =(CDamperSectionCollection *)pSec;} //传入截面数据，通于梁的显示
	void SetEdgeStruc(const CEdgeStrucCollection *p){m_pEdgeCollection=p;}     //传入边缘构件数据
	void SetVisible(const CVisibleStruct *pVisible) {m_pVisible=pVisible;} //传入构件可见信息类指针
	void SetVisibleMesh(const CVisibleMesh *pVisibleMesh) {m_pVisibleElm = pVisibleMesh;} //传入构件可见信息类指针
	void SetVisibleResult(const CVisibleStruct* pVisibleResult) { m_pVisibleResult = pVisibleResult; } //传入构件结果可见信息类指针 20241225 涂天驰
	void SetBoundaryFrame(int n,const CBoundary *p){m_nBoundaryFrame=n;m_pBoundaryFrame=p;}//传入节点约束数据

	void SetSubElm(const SUB_ELM_INFO2 *pSubBeamInfo,const SUB_ELM_INFO3 *pSubTriInfo,
		const SUB_ELM_INFO4 *pSubQuadInfo,const CNode2ElmIndex *pNode2Elm) 
	{
		m_pNode2Elm=pNode2Elm;
		m_pSubQuadInfo=pSubQuadInfo;
		m_pSubTriInfo=pSubTriInfo;
		m_pSubBeamInfo=pSubBeamInfo;
	};
	void SetElmPrim(const Vector4* pTri, const Vector4* pQuad) { m_pTriPrim = pTri; m_pQuadPrim = pQuad;};

	//设置橡皮筋显示状态, 传入橡皮筋坐标或矩形顶点坐标
	//0-不显示
	//1-屏幕坐标线段（vex1,vex2均为屏幕坐标）
	//2-屏幕坐标矩形（vex1,vex2均为屏幕坐标）
	//3-混合坐标线段(vex1为世界坐标,因为图形可能已经被移动，屏幕坐标已经无效，vex2为屏幕坐标)
	//4-世界坐标线段，vex1,vex2均为世界坐标
	int SetDragLine(int iType, float* vex1 = NULL, float* vex2 = NULL, BOOL bDrawVex1 = FALSE, BOOL bDrawVex2 = TRUE)
	{
		int oldtype = m_DragLineType;
		m_DragLineType = iType;
		if(vex1 == NULL)
			memset(m_ElasticVex1, 0,  3*sizeof(float));
		else
			memcpy(m_ElasticVex1, vex1, 3*sizeof(float));

		if(vex2 == NULL)
			memset(m_ElasticVex2, 0,  3*sizeof(float));
		else
			memcpy(m_ElasticVex2, vex2, 3*sizeof(float));

		m_bDrawElasticVex1 = bDrawVex1;
		m_bDrawElasticVex2 = bDrawVex2;

		return oldtype;
	}

	//世界坐标多边形, 类型：0--绘制封闭边界线；1--绘制不封闭边界线；2--绘制填充多边形
	void SetDragPoly(int iType,const int *pvex1,int nvex) {m_iDragPolyType=iType,m_pDragPolyVex=pvex1;m_nDragPolyVex=nvex;} 

	//设置虚点，传入地址，调用一次即可
	void SetVirtualPoint(const VIRTUAL_POINT_TYPE *piVirtualPoint,const Vector4 *pvVirtualPoint) 
		{m_piVirtualPoint=piVirtualPoint;m_pvVirtualPoint=pvVirtualPoint;} 

	//设置提示信息,显示在捕捉点
	void SetHintMsg(CString &Hint){m_sHint=Hint;}  

	//设置工具图标显示位置
	void SetZoomIconRect(const CRect &rect){m_rectZoomIcon=rect;} //设置缩放工具图标位置
	void SetRotateIconRect(const CRect &rect){m_rectRotateIcon=rect;} //设置旋转工具图标位置
	void SetMiniMapIconRect(const CRect &rect){m_rectMiniMapIcon=rect;} //设置小地图工具图标位置

	//绘图和拾取过程，只有拾取绘图的时候才提供参数
	void Draw(unsigned int PrimitiveType=STRUCT_UNKNOWN, unsigned int SecondaryType=0);
	int Pick(const CPoint &point,unsigned int PrimitiveType,int **pPBuf, unsigned int SecondaryType);  //捕捉某一个点处的图元，point为鼠标位置,PrimitiveType图元类型
	const int *GetPickedObj(void) {return m_pPickedIDG;}
	int GetPickedNum(void) {return m_nPickedObj;}
	int PickGroup(const CRect &rect,unsigned int PrimitiveType,int *&pNames, unsigned int SecondaryType=0); //反选一组图元
	void SetCaptureID(int iCaptureID,bool bDraw = true) {m_iCaptureID = iCaptureID; if(bDraw) Draw();}
	int GetCaptureID(){return m_iCaptureID;}
	CPoint World2Client(const CVertex &p); //由物理坐标获得屏幕坐标(实际为窗口坐标)
	void World2Client(float *v, int *pt, const int nP); //由物理坐标获得屏幕坐标(实际为窗口坐标)
	Vector4 Client2World(int x, int y); //屏幕坐标（实际为窗口坐标）转为物理坐标
	void Client2World(float *pt, float *pCoor, const int nPt = 1); //屏幕坐标（实际为窗口坐标）转为物理坐标
	void Client2WorldCenter(int x, int y, float *pCoor); //屏幕坐标（实际为窗口坐标）转为物理坐标,视野的中心
	float GetPhysicalLength(int iClientLength); //得到物理长度，单位：米
	float GetScreenLength(float fPhyLength); //得到屏幕长度，单位：像素



	//将线段p1-p2在平面vPlaneNormal(单位矢量)内移动到过屏幕坐标point的新位置q1-q2
	//返回移动的方向代码：0-失败，1-X，2-Y，3-Z，4-线段的法向
	int MoveLineInPlane(const Vector4 &oldpoint,const CPoint &point,const Vector4 &vPlaneNormal,
		const CVertex &p1,const CVertex &p2, Vector4 &q1,Vector4 &q2);  
	//将点vOld沿线段vOld-pConnPoint[i]移动到新点vNew，自动判断最贴近的线段
	//返回移动的方向代码：0-失败，5-线段方向
	int MovePointAlongLine(const CPoint &point,int nConnPoint,	const Vector4 *pConnPoint, const Vector4 &vOld, Vector4 &vNew);

	//动画过程
	//void SetTimeLoop(int iTimeLoop){m_iTimeLoop=iTimeLoop;}

	//实际绘图的坐标范围
	Vector4 m_vDrawRangeMin,m_vDrawRangeMax;


	//返回视点矢量,主要用于调试
	Vector4 GetLookAt(void) {return m_vLookat;}
	Vector4 GetEye(void) {return m_vEye;}
	Vector4 GetUp(void) {return m_vUp;}
	float GetNear(void) {return m_zNear;}
	float GetFar(void) {return m_zFar;}
	float GetRatio(void) {return m_fRatio;}
	void SetRatio(float ratio) {m_fRatio=ratio;}
	HGLRC GetHRC(void) {return m_hGLRC;}
	void SetHRC(HGLRC hrc) {m_hGLRC=hrc;}

	Vector4 GetScreenX(void); //得到屏幕X方向(向右为正方向)单位矢量，以整体坐标表达
	Vector4 GetScreenY(void); //得到屏幕Y方向(向上为正方向)单位矢量，以整体坐标表达

	GLvoid KillFont(GLvoid);									// Delete The Font
	GLvoid KillFontFixed(GLvoid);									// Delete The Font
	GLvoid BuildFont(BOOL bVectorFontFilled=TRUE); //bVectorFont是否矢量字体用m_bVectorFont 控制 邱海增加空心实心字体切换 2017年8月22日

	//图元有效性,超出坐标范围或者楼层范围将视为无效
	BOOL IsVisible(const CVertex &primitive) const;
	BOOL IsVisible(const CLine &primitive) const; 
	BOOL IsVisible(const CBeamStruc &primitive) const; 
	BOOL IsVisible(const CPlateStruc &primitive) const; 
	BOOL IsVisible(const CBeamElm &primitive) const; 
	BOOL IsVisible(const CTriangleElm &primitive) const; 
	BOOL IsVisible(const CQuadElm &primitive) const; 
	//20241225 涂天驰
	BOOL IsResultVisible(const CBeamElm& primitive) const;
	BOOL IsResultVisible(const CTriangleElm& primitive) const;
	BOOL IsResultVisible(const CQuadElm& primitive) const;

	BOOL IsInClientRect(const CVertex &p,int iErr); //判断点是否在屏幕内，留出iErr像素的余地
	BOOL IsDrawBody(void); //是否绘制实体，根据缩放尺寸进行判断

	//得到实际绘图的坐标范围，更新m_vDrawRangeMin,m_vDrawRangeMax
	void GetDrawRange(void);

	GLvoid SetBackgroudColor(GLvoid);
	void SetTextType(int type);
	void InitPlateShowVexIndex();
	void InitBodyShow();
	bool bPickUpdate() {return m_bPickUpdate;}
	void SetBcGroupId(int iBc) { m_iBC = iBc; }
private:
	//属性

	//缓存区
	//int m_idVexBuffer;

	//捕捉图形
	int m_iCaptureID;   //最后确定的ID
	int *m_pPickedIDG;  //临时捕捉的图元IDG
	int *m_pPickBuf;  //捕捉用的临时数组
	int m_nPickedObj;  //同时捕捉到的图元数
	unsigned int m_iPrimaryType;
	bool m_bPickUpdate;

	//图元属性数据######### 交换数据区 ###########
	//以下仅保存指针，由外部程序维护内存,未注明的数据均为物理坐标

	//共用几何数据
	int m_iStoryMin,m_iStoryMax; //楼层显示范围
	Vector4 m_vMin,m_vMax; //坐标显示范围
	int m_iStageMin,m_iStageMax; ////可显示图元的起始和截止编号,框架和网格共用

	int m_nProfile;      //剖面轮廓点数
	Vector4 m_pProfile[4]; //剖面轮廓点

	//网格数据
	int m_nNode;
	const CVertex *m_pNode;   //原始点坐标数组
	int m_nBeamElm,m_nTriangleElm,m_nQuadElm;
	const CBeamElm *m_pBeamElm; //梁单元数组
	const CTriangleElm *m_pTriangleElm; //三角形单元数组
	const CQuadElm *m_pQuadElm;
	const CVertex *m_pDeformNode;   //变形点坐标数组,点数与未变形一致
	const CNode2ElmIndex *m_pNode2Elm;  //结点到单元的索引
	const SUB_ELM_INFO2 *m_pSubBeamInfo;
	const SUB_ELM_INFO3 *m_pSubTriInfo;
	const SUB_ELM_INFO4 *m_pSubQuadInfo;
	const Vector4* m_pTriPrim;
	const Vector4* m_pQuadPrim;
	int m_BoundaryMesh;
	const CBoundary *m_pBoundaryMesh;   //节点约束数组


	int m_nGroundLine;  //虚拟地面网格线数
	const RECT *m_pGroundLine;  //虚拟地面网格线坐标(取整)
	Vector4 m_vOffset; //坐标偏移量，模拟地面地震

	//框架数据
	int m_nVex;
	const CVertex *m_pVex;   //原始点坐标数组
	int m_nGuides,m_nLineStruc,m_nBeamStruc,m_nPlateStruc;  //网格或框架图元数量，两者不同时出现
	const CLine *m_pGuides;    //辅助线数组
	const CLine *m_pLineStruc;    //结构线数组
	const CBeamStruc *m_pBeamStruc;    //梁数组
	const CPlateStruc *m_pPlateStruc; //多边形数组
	const CSectionCollection *m_pSec; //截面数据
	const CDamperSectionCollection *m_pDamperSec; //一般连接截面信息	//乔保娟 2015.5.19

	const CEdgeStrucCollection *m_pEdgeCollection;    //边缘构件数组
	const CVisibleStruct *m_pVisible;  //构件可见信息类指针,对应活跃集
	const CVisibleMesh *m_pVisibleElm;
	const CVisibleStruct * m_pVisibleResult;//20241225 tutianchi
	int m_nBoundaryFrame;
	const CBoundary *m_pBoundaryFrame;   //节点约束数组
	int m_iBC;//当前边界组号

	//橡皮筋线
	BOOL m_DragLineType;  //橡皮筋显示标志,0-不显示,1-屏幕坐标线段,2-屏幕坐标矩形,3-线段(vex1为世界坐标,vex2为屏幕坐标)
	float m_ElasticVex1[3], m_ElasticVex2[3];  //橡皮筋坐标(物理坐标),或者拖动矩形的顶点(屏幕坐标,绘图时进行转换)
	BOOL m_bDrawElasticVex1,m_bDrawElasticVex2; //是否绘制橡皮筋首末点

	//绘制虚拟多边形或边界线，世界坐标
	const int *m_pDragPolyVex;  //点号数组
	int m_nDragPolyVex; //点数
	int m_iDragPolyType;  //类型：0--绘制封闭边界线；1--绘制不封闭边界线；2--绘制填充多边形

	//虚点信息
	const VIRTUAL_POINT_TYPE *m_piVirtualPoint;  //是否存在虚点
	const Vector4 *m_pvVirtualPoint;  //虚点坐标

	//选取图元的坐标范围
	BOOL m_bShowSelectZone; //是否显示选取图元所在的范围
	Vector4 m_vSelectMin;  //选取图元的最小坐标
	Vector4 m_vSelectMax;  //选取图元的最大坐标

	//显示层间位移角位置
	BOOL m_bShowDriftPos;

	CString m_sHint;  //提示信息
	float m_fAspect;  //高宽比，用于拾取时计算投影矩阵，在调用绘图投影时设置

	//图标数据,窗口坐标
	CRect m_rectZoomIcon; //缩放图标位置,起始点坐标,长度和宽度
	CRect m_rectRotateIcon; //旋转工具图标位置,起始点坐标,长度和宽度
	CRect m_rectMiniMapIcon; //小地图工具图标位置,起始点坐标,长度和宽度

	//#############


	//OpenGL设备参数---------------------------------------------------
	HWND m_hWnd;  //窗口句柄，外部输入
	HDC m_hDC;    //设备句柄，内部获得
	HGLRC m_hGLRC;//GL设备句柄，内部获得
	BOOL m_bDeviceReady;  //设备状态
	GLUquadricObj *m_quad_obj;  //用于绘制二次对象 

	//绘图参数-----------------------------------------------------------
	Matrix4x4 m_ModelMatrix;  //模型变换矩阵
	float m_zNear;  //近距，相对于镜头
	float m_zFar;   //远距，相对于镜头

	Vector4 m_vEye; // 镜头位置
	Vector4 m_vLookat; // 镜头对准的点
	Vector4 m_vUp; // 镜头正上方的方向
	float m_fRatio;  // m_fRatio放大倍数倒数

	//显示字符用的基础数据----------------------------------------------
	GLuint	m_iBase;				// Base Display List For The Font Set
	GLuint	m_iBaseFixed;			// 固定大小的位图字体
	//BOOL m_bVectorFont;  //是否矢量字体
	GLYPHMETRICSFLOAT m_gmf[256];	// Storage For Information About Our Outline Font Characters,bVectorFont=TRUE时有效
	GLYPHMETRICSFLOAT m_agmf[1];

	//背景

	typedef struct													// Create A Structure
	{
		GLubyte	*imageData;											// Image Data (Up To 32 Bits)
		GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
		GLuint	width;												// Image Width
		GLuint	height;												// Image Height
		GLuint	texID;												// Texture ID Used To Select A Texture
	} TextureImage;													// Structure Name

	TextureImage m_Textures[2];
	float m_Roll;

	//实现
	//设备准备
	BOOL InitGraphicsDevice(void);
	void MatrixOrthro(int ScreenWidth,int ScreenHeight); //正交投影矩阵
	void MatrixOrthoSelect(const CPoint &point); //用于拾取
	//计算选取用的正交投影矩阵,给定选区区域矩形
	void MatrixOrthoSelect(const CRect &rect);
	void FixupGLExt(void);
	void InitResource(void);     //初始化绘图资源，例如灯光、材质、贴图等
	BOOL ReleaseResource(void);  //释放所有绘图资源

	//绘图
	//pVex为原始坐标或者变形坐标，绘制框架结构或网格，不包括辅助图元（轴网、橡皮筋、坐标轴等）
	//bOriginal为TRUE时绘制虚线和灰色图
	void DrawPrimitives(const CVertex *pVex, unsigned int PrimitiveType,BOOL bOriginal, int SecondaryType=0);  //绘制所有图元

	void DrawPoints( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal );  //绘制点，有限元结点或框架顶点，数据统一
	void DrawLines( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //绘制框架--构造线
	void DrawGuides( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //辅助线

	void DrawBeams(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //绘制梁，被DrawPrimitive调用
	void DrawPillars(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //绘制柱和斜撑构件，被DrawPrimitive调用
	void DrawPlates(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //串行绘制板，被DrawPrimitive调用
	void DrawWalls(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal, int SecondaryType=0); //绘制墙，被DrawPrimitive调用
	void DrawEdges(const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal);  //绘制边缘构件


	void DrawBeamWithBox(const CVertex *pVex,const CBeamStruc &line,COLORREF color,unsigned int PrimaryType); //绘制长方体柱
	void DrawPlateWithBody(const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); //绘制三维板
	//网格化绘制三维板  //乔保娟 2015.3.11
	void DrawPlateWithBodyTess(GLUtesselator* tobj,const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); 
	void DrawWallWithBody(const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); //绘制三维墙

	void DrawBeamElmWithBody(const CVertex *pVex,const CBeamElm &elm,const COLORREF *color,COLOR_TYPE color_type,unsigned int PrimaryType);  //实体方式绘制梁单元
	void DrawTriElmWithBody(const CVertex *pVex,const CTriangleElm &elm,const COLORREF *color,COLOR_TYPE color_type);  //实体方式绘制三角形单元
	void DrawQuadElmWithBody(const CVertex *pVex,const CQuadElm &elm,const COLORREF *color,COLOR_TYPE color_type);  //实体方式绘制四边形单元


	void DrawBeamElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal );  //绘制有限元--梁单元
	void DrawTriangleElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //绘制有限元--四边形单元
	void DrawQuadElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal); //绘制有限元--三角形单元
	void DrawShadowPolys(unsigned int PrimaryType);  //绘制重心多边形网格


	void DrawOutlineCuboid(void); //绘制外轮廓长方体
	void DrawProfileFrame(void); //绘制剖面框架

	void DrawAxis(void);   //绘制坐标轴
	void DrawLocalAxis(float *coor,const Vector4& u,const Vector4& v,const Vector4& w);   //绘制局部坐标轴 邱海 2017年12月18日
	void DrawSelectZone(void);  //绘制选取区域的标记
	void DrawScale(void);  //在边框上绘制坐标刻度
	void DrawBackGround(void);
	void DrawGround(void);	//绘制地面网格
	void DrawRestraints(const float *coor,const CBoundary &cbind);   //绘制位移约束 邱海 2017年12月18日
	void DrawRestraints(const float* coor, const int& pin); 
	void DrawAnticulate(const CBeamStruc& beam, const CVertex& v1, const CVertex& v2);

	BOOL LoadTGA(TextureImage *texture, LPCTSTR filename);

	//显示字符串，支持宽字符,逐个分别处理ASCII字符和宽字符，ASCII字符采用模板，效率较高
	void glPrint(const CString &str);
	void glPrint(const char* str);

	//显示固定大小字符串，只支持ASCII码
	void glPrintFixed(const char* str);

	//显示固定大小字符串，显示在p1，沿X轴方向//
	void DrawFixedTextAt(const char* str, const float *p1);

	//显示字符串，显示在p1，沿X轴方向
	void DrawTextAt(const CString &str, const float *p1);

	//显示字符串，显示在p1--p2之间
	void DrawTextRotate(const CString &str, const CVertex &p1, const CVertex &p2);  

	void GetStrings(const CString& cText, std::vector<short> &vPos);

	void DrawTextRotateMultiLine(const CString &str, const CVertex &p1, const CVertex &p2);

	//显示扩展字符函数,全部转换为双字节字符后输出，效率比较低
	void DrawStringByWideChar(const char* str);

	//面内画圆coor[3]coor为圆心物理坐标,r--物理半径，iPlane：0-XY平面，1-YZ平面，2-ZX平面
	void DrawCircle(float *coor,float r,int nPoint=4,int iPlane=0);
	void DrawSolidCircle(float *coor,float r,int nPoint=4,int iPlane=0);


	//绘制标记点，vex为物理坐标，mark_type标记形状,MARKER_TYPE组合类型，radius标记尺寸的半径（像素）
	void DrawMarkerPoint(const Vector4 &vex, int mark_type, int radius=5);

	//多边形表面模拟光照效果,计算颜色值，并调用OpenGL函数设置绘图颜色
	//vn--法线方向
	BOOL SetGLColor(const Vector4 &vn,const BYTE * RGBA,BYTE alpha=127);

	//多边形表面模拟光照效果,计算颜色值，并调用OpenGL函数设置绘图颜色
	//给定的三个点不能共线
	BOOL SetGLColor(const CVertex &p1,const CVertex &p2,const CVertex &p3,const BYTE *RGBA,BYTE alpha=127); //设置修正的多边形绘图颜色,成功返回TRUE
	BOOL SetGLColor(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,const BYTE *RGBA,BYTE alpha=127); //设置修正的多边形绘图颜色,成功返回TRUE

	BOOL CheckValid(void);

	//显示梁配筋，显示在p1--p2之间
	void DrawBeamRein(const CBeamStruc &beam, const CVertex &p1,const CVertex &p2);  
	//显示柱配筋，显示在p1--p2之间
	void DrawPillarRein(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);  
	//显示墙配筋，显示在p1--p2之间
	void DrawWallRein(const CPlateStruc &wall,const CVertex &p1,const CVertex &p2,const CVertex &p3,const CVertex &p4);  
	//矢量显示文字在
	void DrawVectorTextAt(const CString &str,const Vector4 &p1,const Vector4 &p2, int iRowPos=1);
	//显示构件内力，显示在p1--p2之间
	void DrawForce(const CString &str1,const CString &str2,const CVertex &p1,const CVertex &p2);  
	//显示梁上文字
	void	DrawBeamText(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);
	//显示字符串，显示在p1--p2之间
	void DrawTextMulineXY(const CString &str, const float* p1, const float* p2);  
	//显示字符串，显示在p1--p2之间
	void DrawTextMulineXZ(const CString &str, const float* p1, const float* p2);  
	//显示柱撑上文字
	void	DrawPillarText(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);
	//显示墙上文字
	void	DrawWallText(const int &iWall, const CVertex *pVex);

	//2021 Qiuhai add
	bool ShowAuxVariablesInit();
	bool bInitBodyShow;
	void SetVertexVisible();
	void GetPlateBox(std::unordered_map<Vector4, unsigned int, hash_vec> VertexIndex, std::vector<Vector4> &vVex, std::vector<std::vector<std::vector<int>>> &vPlateBox);
	void GetBeamBox(std::unordered_map<Vector4, unsigned int, hash_vec> VertexIndex, std::vector<Vector4>& vVex, std::vector<std::vector<std::vector<int>>>& vBeamBox, std::vector<short>& pShape);

	enum SHOWTYPE
	{
		TYPE_OLD,
		TYPE_CALLIST,
		TYPE_VBO,
	}m_ShowType;
	void BulidBeamCallList();
	std::vector<bool> m_vbPtVisible;
	std::vector<std::vector<int>> m_vPlateId;
	std::vector<float> m_vPlateCenter;
	std::vector<Vector4> m_vShowVex;
	std::vector<short> m_pBeamShape;
	std::vector<std::vector<std::vector<int>>> m_vBeamBox;
	std::vector<std::vector<std::vector<int>>> m_vPlateBox;
	std::vector<bool> m_vbConcavePolygon;//for ConcavePolygon
	std::vector<GLdouble> m_vPolygonCoor;//for ConcavePolygon

	void DrawBeamWithBox(const CVertex *pVex, int iBeam,COLORREF color,unsigned int PrimaryType); //绘制长方体柱
	void DrawPlateWithBox(const CVertex *pVex, int iPlate,COLORREF *pcolor); //绘制三维板
	void DrawPlateWithBoxTess(GLUtesselator* tobj, const CVertex* pVex, int iPlate, COLORREF* pcolor);
	bool isConcavePolygon(const CVertex* pVex, int iPlate);

	void UpdateConstVars();
	GLfloat m_UnitPhysicalLength;
	GLfloat m_UnitScreenLength;
	GLfloat m_fLocalAxisLenth;
	GLfloat m_fGlobalAxisLenth;
	GLfloat m_fVFontR;
	bool m_bDrawBody;

	GLuint m_ListLocalAxis;
	GLuint m_ListGlobalAxis;
	GLuint m_ListBnd;
	GLvoid BuildLocalAxis(GLvoid);
	GLvoid KillLocalAxis(GLvoid);		
	GLvoid BuildGlobalAxis(GLvoid);
	GLvoid KillGlobalAxis(GLvoid);	
	GLvoid BuildRestraints(GLvoid);
	GLvoid KillRestraints(GLvoid);	
	GLclampf m_BackgroundColor[3];
	HFONT m_Font;
	GLfloat m_fFontH;
	float m_fFontPos[3];
	Vector4 m_vOffSetEye;
	enum LABEL_TYPE
	{
		LABEL_DEFAULT = -1,
		LABEL_NONE,      //清除标签
		LABEL_SECTION,   //截面
		LABEL_THICKNESS, //厚度
		LABEL_RATIO,	 //配筋率
		LABEL_DIRECTION, //钢筋方向
		LABEL_MAT,		 //材料
		LABEL_LOAD,		 //荷载
		LABEL_XBIND,     //X方向约束
		LABEL_YBIND,	 //Y方向约束
		LABEL_ZBIND,	 //Z方向约束
		LABEL_XROTATE,	 //X轴转动
		LABEL_YROTATE,	 //Y轴转动
		LABEL_ZROTATE,	 //Z轴转动
		LABEL_VEXID,      //结点号或构件点号
		LABEL_ID,			//单元号或构件号
		LABEL_BEAM,			//梁类型 主次梁 邱海 2016年2月17日
		LABEL_RESULTS,		//计算结果 邱海 2016年3月8日
		LABEL_WALLBEAMCOEF,	//计算结果 邱海 2016年3月8日
		LABEL_MIDCONSTITUTIVE,	//中震构件性能目标 邱海 2016年8月11日
		LABEL_RARECONSTITUTIVE,	//大震构件性能目标 邱海 2016年8月11日
		LABEL_MEMBERPERFORMOBJECT,	//大震构件性能目标 侯晓武 2022年12月23日
		LABEL_VIPTYPE,			//重要性类型
		LABEL_DETAILSSEISMICGRADE,//构件抗震构造措施等级 邱海 2017年10月9日
		LABEL_SEISMICGRADE,		//构件抗震等级 邱海 2017年10月9日
		LABEL_MEMBERNAME,		//构件名称
		LABEL_CHECKRESULTS,		// 验算结果
		LABEL_TOWERID,			//塔号
		LABEL_STEELSECCALC,		//钢结构截面验算
		LABEL_REINFORCEMENT,   //构件配筋
		LABEL_FORCEADJUSTMENT,//内力调整系数
		LABEL_MEMBERFORCE,//构件内力
		LABEL_DEFECT,		 //缺陷
		LABEL_SEMIRIGID,    //半刚性连接标识显示 辛业文 2022年12月21日
		LABEL_SHEARNONLINEAR,  //剪切非线性信息 周璋鑫 2023年1月15日
		LABEL_REINFORCEDCOMPONENTS, // 加固构件标识显示 辛业文 2023年4月14日
		LABEL_BLASTWALL, //抗爆墙体类型 贾苏20230710
		LABEL_MAT_REINFORCED,		 //加固材料 辛业文 2023年8月16日
		LABEL_RATIO_JG,
	};
	char m_TextType;
};

