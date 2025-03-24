#pragma once
#include "HeadDefine.h"
#include "SectionBaseHead.h"


//截面描述表
struct SECTION_PARA
{
	CString name;
	CString memo;
};

struct _SSG_DLLIMPEXP SECTION_TYPE_PROP_TABLE  //截面类型属性表
{
	SECTION_MAT_TYPE iMatType;		//类型ID
	CString sMatCode;		//类型名称缩写
	CString sMatName;		//类型名称
};

//板截面类型对应的名称
struct _SSG_DLLIMPEXP PLATE_SECTION_MAT_TYPE
{
	SECTION_MAT_TYPE iMatType; //类型ID
	CString sMatCode;		//类型名称缩写
	CString sMatName;		//类型名称
};

//子截面类型表
struct _SSG_DLLIMPEXP SUBSECTIONTYPE_PROP_TABLE
{
	SUBSECTION_MAT_TYPE iMatType;	//材料类型代号
	CString sMatCode;					//材料名称缩写
	CString sMatName;			//类型名称

	static CString &GetNameByType(SUBSECTION_MAT_TYPE itype);
};

//截面形状属性表
struct _SSG_DLLIMPEXP SECTION_SHAPE_PROP_TABLE   
{
	SECTION_SHAPE iShape;  //形状模板ID
	CString sName;   //形状模板名称
	SECTION_MAT_TYPE iType;  //材料类型
	SUBSECTION_SHAPE subshape[2]; //对应的子截面编号
	SECTION_TYPE iSectionType; //截面类型 辛业文 2024年12月26日
};

class _SSG_DLLIMPEXP CSectionBase
{
public:
	CSectionBase(void);
	~CSectionBase(void);

public:
	static float DrawRect(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float theta=0, float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,BOOL bShowLabel=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //宽,高
	static float DrawBox(CDC *pdc,float t2=0.5f,float t3=0.8f,float tf1=0.1f,float tw1=0.1f,float tf2=0.1f,float tw2=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCirc(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //直径
	static float DrawPipe(CDC *pdc,float t2=0.8f,float tw=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);  //外径,厚度
	static float DrawI(CDC *pdc,float H1=0.8f,float tw=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC, BOOL bLabelChange = FALSE);
	static float DrawCross(CDC *pdc,float H1=0.8f,float tw1=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,
		float H2=0.8f,float tw2=0.1f,float B3=0.6f,float tf3=0.1f,float B4=0.7f,float tf4=0.1f,
		float p2=0,float p3=0,float theta=0,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

	static float DrawCriss(CDC *pDC,float B=0.05f,float H=0.45f,float U=0.2f,float T=0.05f,float D=0.2f,float F=0.2f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawRegPoly(CDC *pdc,float B=0.8f,float N=6,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //最大外径
	static float DrawHex(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //最大外径
	static float DrawChannel(CDC *pDC,float B=0.1f,float H=0.8f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDblChannel(CDC *pDC,float B=0.1f,float H=0.6f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=1.1f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDoubleLimbsChannel(CDC* pDC, float B = 0.1f, float H = 0.6f, float U = 0.4f, float T = 0.1f, float D = 0.4f, float F = 0.1f, float maxsize = 1.1f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC);
	static float DrawT(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.4f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawL(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.2f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawTrapezoid(CDC *pdc,float B=0.4f,float H=0.8f,float T=0.1f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawArbitrary(CDC *pDC, float *fValue, int num, BOOL clockwise, float p2, float p3, float fWidth, float fHeight, float maxsize=1.0f, BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDoubleLimbsH(CDC* pDC, float Hs, float tw1, float B1, float tf1, float d1, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawFourLimbsL(CDC* pDC, float B, float H, float D, float F, float d1, float d2, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawHSteelAddPlate(CDC* pDC, float Hs, float tw1, float B1, float tf1, float ts,float Bs, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawDoubleLimbsL(CDC* pDC, float B, float H, float D, float F, float d1, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawThreeLimbsPipe(CDC* pdc, float B, float H, float Ds = 0.8f, float tw = 0.1f, float p2 = 0, float p3 = 0, float theta = 0, float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC);  //外径,厚度


	static float DrawHanOuter(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float b1=0.4f, float h1=0.4f, float hf1=0.15f, float hf2=0.15f,
		float tc1=0.15f, float tc2=0.15f, float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawHanInnerConc(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawHanInnerPipe(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	//绘制标注线和标注符号,x1,y1,x2,y2--首末点逻辑坐标,str-字符串,为空时只画线
	//Pos=文字位置，0-线间，1-右端，2-左端
	//ArrowType箭头类型，0-两端，1-右端，2-左端,3-无箭头
	static void DrawLabel(CDC *pdc,int x1,int y1,int x2,int y2,LPCTSTR str,COLORREF color=RGB(0,0,0),int ArrowType=0,int Pos=0,float ratio=1.0f); 

    //绘制长方形纤维,xc,yc,b,h--中心和边长
    static void DrawRectFibre(CDC *pDC,const float ratio,float xc,float yc,float b,float h);

    //绘制圆形纤维,xc,yc,r--中心和半径
    static void DrawCircFibre(CDC *pDC,const float ratio,float xc,float yc,float r);

    //绘制圆形钢筋,xc,yc,r--中心和半径
    static void DrawRebar(CDC *pDC,const float ratio,float xc,float yc,float r);

	//绘制墙板截面
	static float DrawThick(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //宽,高

public:
	//加固构件截面 辛业文 2023年5月16
	static float DrawBoxReinForced(CDC* pdc, float t2 = 0.5f, float t3 = 0.8f, float tf1 = 0.1f, float tw1 = 0.1f, float tf2 = 0.1f, float tw2 = 0.1f, float p2 = 0, float p3 = 0, float theta = 0,
		float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC, SUBSECTION_REINFORCED_TYPE iMethod = BEAM_ENLARGED_SECTION_TYPE, BOOL bDiagram = FALSE);
	static float DrawRectReinForced(CDC* pDC, float B, float H, BOOL bClockwise, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, BOOL bShowLabel, SUBSECTION_MAT_TYPE iMatType);
	static float DrawArbitraryReinForced(CDC* pDC, float* fValue, int nValue, BOOL bClockwise, float p2, float p3, float fWidth, float fHeight,
		float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType, SUBSECTION_REINFORCED_TYPE iMethod, int num, BOOL bDiagram=FALSE);
	static float DrawPlateBoxReinForced(CDC* pdc, float t2 = 0.5f, float t3 = 0.8f, float tf1 = 0.1f, float tw1 = 0.1f, float tf2 = 0.1f, float tw2 = 0.1f, float p2 = 0, float p3 = 0, float theta = 0,
		float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC, PLATE_REINFORCED_METHOD iMethod = PLATE_METHOD_ENLARGED_SECTION);

};


class _SSG_DLLIMPEXP CColorButton:public CButton
{ 
public:
	COLORREF m_Color;

	CColorButton():CButton(),m_Color(0){}; //构造函数
	void ChangeColor(COLORREF color); //改变颜色
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//重载的函数
};

void RotateCoord(float &x1, float &y1, float x, float y, float theta);
