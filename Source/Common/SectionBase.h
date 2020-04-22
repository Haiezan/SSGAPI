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
};

class _SSG_DLLIMPEXP CSectionBase
{
public:
	CSectionBase(void);
	~CSectionBase(void);

public:
	static float DrawRect(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //宽,高
	static float DrawBox(CDC *pdc,float t2=0.5f,float t3=0.8f,float tf1=0.1f,float tw1=0.1f,float tf2=0.1f,float tw2=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCirc(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //直径
	static float DrawPipe(CDC *pdc,float t2=0.8f,float tw=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);  //外径,厚度
	static float DrawI(CDC *pdc,float H1=0.8f,float tw=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCross(CDC *pdc,float H1=0.8f,float tw1=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,
		float H2=0.8f,float tw2=0.1f,float B3=0.6f,float tf3=0.1f,float B4=0.7f,float tf4=0.1f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

	static float DrawCriss(CDC *pDC,float B=0.05f,float H=0.45f,float U=0.2f,float T=0.05f,float D=0.2f,float F=0.2f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawRegPoly(CDC *pdc,float B=0.8f,float N=6,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //最大外径
	static float DrawHex(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //最大外径
	static float DrawChannel(CDC *pDC,float B=0.1f,float H=0.8f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDblChannel(CDC *pDC,float B=0.1f,float H=0.6f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=1.1f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawT(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.4f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawL(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.2f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawTrapezoid(CDC *pdc,float B=0.4f,float H=0.8f,float T=0.1f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

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

};


class _SSG_DLLIMPEXP CColorButton:public CButton
{ 
public:
	COLORREF m_Color;

	CColorButton():CButton(),m_Color(0){}; //构造函数
	void ChangeColor(COLORREF color); //改变颜色
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//重载的函数
};
