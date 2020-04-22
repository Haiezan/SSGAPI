#pragma once
#include "HeadDefine.h"
#include "..\Common\SysPara.h"
#include "ASCFile.h"
#include "SectionBase.h"
#include <afxtempl.h>

#define gSectionTypeNum 5	//梁柱截面分类个数
#define gPlateSectionNum 3	//板截面类型最大个数

//预定义的截面形状个数
//去掉任意截面BEAM_ARBITRARY、PILLAR_ARBITRARY和变截面梁和柱BEAM_RC_VAR、PILLAR_RC_VAR
#define gSectionShapeNum 71   

#define Sys_SubSectionShapeNum 16 //预定义的子截面形状个数

//计算矩形截面的扭转惯性矩J1，自动判断B,H大小
extern "C" _SSG_DLLIMPEXP float J1_Rect(float B,float H);

//根据材料名称得到材料类型
extern "C" _SSG_DLLIMPEXP SECTION_MAT_TYPE GetSecType(const CString &sConc,const CString &sRebar,const CString &sSteel);

//由模板得到材料类型
extern "C" _SSG_DLLIMPEXP SECTION_MAT_TYPE GetSectionMatType(SECTION_SHAPE iSectionShape);

//得到模板在全局属性数组gSectionShapeTable中的序号,失败返回-1
extern "C" _SSG_DLLIMPEXP int GetSectionPropIndex(SECTION_SHAPE iSectionShape);

//由材料类型找数据项
extern "C" _SSG_DLLIMPEXP PLATE_SECTION_MAT_TYPE *GetPlateSectionType(SECTION_MAT_TYPE MatType);

static SECTION_TYPE_PROP_TABLE gSectionTypeTable[gSectionTypeNum]={
#ifdef _SIMPLIFIED_CHINESE
	SECTION_MAT_TYPE_RC,	 L"RC",	L"钢筋混凝土",
	SECTION_MAT_TYPE_ST,	 L"ST",	L"钢材",
	SECTION_MAT_TYPE_CFT,	 L"CFT",	L"钢管混凝土",		//Concrete Filled Tube
	SECTION_MAT_TYPE_SRC,	 L"SRC",	L"钢骨混凝土",		//Steel Reinforced Concrete
	SECTION_MAT_TYPE_REBAR,	 L"REBAR",	L"钢筋",
#else
	SECTION_MAT_TYPE_RC,	 L"RC",	L"Reinforced Concrete",
	SECTION_MAT_TYPE_ST,	 L"ST",	L"Section Steel",
	SECTION_MAT_TYPE_CFT,	 L"CFT",	L"Concrete Filled Tube",
	SECTION_MAT_TYPE_SRC,	 L"SRC",	L"Steel Reinforced Concrete",
	SECTION_MAT_TYPE_REBAR,	 L"REBAR",	L"Rebar",
#endif
};

//板截面类型对应的名称
static PLATE_SECTION_MAT_TYPE gPlateSectionTypeTable[gPlateSectionNum]=
{
#ifdef _SIMPLIFIED_CHINESE
	SECTION_MAT_TYPE_RC, L"RC",	L"钢筋混凝土",
	SECTION_MAT_TYPE_ST, L"ST",	L"钢板",
	SECTION_MAT_TYPE_SRC,L"SRC",L"钢板混凝土",  
#else
	SECTION_MAT_TYPE_RC, L"RC",	L"Reforced Concrete",
	SECTION_MAT_TYPE_ST, L"ST",	L"Steel Plate",
	SECTION_MAT_TYPE_SRC,L"SRC",L"Steel Reinforced Concrete",
#endif
};

//子截面类型表
static SUBSECTIONTYPE_PROP_TABLE gSubSectionTypePropTable[]={
#ifdef _SIMPLIFIED_CHINESE
	SUBSECTION_MAT_TYPE_CONC, L"RC",	L"钢筋混凝土",  //混凝土     
	SUBSECTION_MAT_TYPE_ST, L"ST",	L"钢材",	//钢材
	SUBSECTION_MAT_TYPE_REBAR, L"REBAR",	L"钢筋",	//钢筋

#else
	SUBSECTION_MAT_TYPE_CONC, L"RC",	L"Reinforced Concrete",  //混凝土     
	SUBSECTION_MAT_TYPE_ST, L"ST",	L"Section Steel",	//钢材
	SUBSECTION_MAT_TYPE_REBAR, L"REBAR",	L"Rebar",	//钢筋
#endif
};

static SECTION_SHAPE_PROP_TABLE gSectionShapeTable[gSectionShapeNum]=
{
#ifdef _SIMPLIFIED_CHINESE
	//梁截面,0-99
	//BEAM_ARBITRARY		,	   L"任意组合截面混凝土梁", SECTION_MAT_TYPE_RC,

	BEAM_RC_RECT		,	L"混凝土梁",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_BOX			,	L"方钢管梁",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_I			,	L"工字型钢梁",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_CFT_BOX_RECT	,	L"方钢管混凝土梁",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	BEAM_SRC_RECT_I		,	L"工字型-钢骨混凝土梁",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	BEAM_RC_CRISS		,	L"十字型混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,
	
	BEAM_RC_I			,	L"工字型混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_RC_CIRC		,	L"圆形混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,
	BEAM_RC_REGPOLY		,	L"正多边形混凝土梁",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	BEAM_RC_CHANNEL		,	L"槽型混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	BEAM_RC_BOX			,	L"矩形管混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_RC_DBLCHANNEL	,	L"双槽型混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	BEAM_RC_CROSS		,	L"十字工型混凝土梁",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	BEAM_RC_TRAP		,	L"梯形混凝土梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	BEAM_CFT_PIPE_CIRC	,	L"圆钢管混凝土梁",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	BEAM_SRC_RECT_BOX	,	L"方钢管-钢骨混凝土方梁",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	BEAM_SRC_RECT_CROSS	,	L"十字工型-钢骨混凝土方梁",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	//BEAM_RC_VAR		,	L"变截面混凝土方梁",SECTION_MAT_TYPE_RC,
	BEAM_RC_L			,	L"L型混凝土梁",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,

	BEAM_SRC_RECT_PIPE	,	L"圆型钢管-钢骨混凝土方梁",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_PIPE,

	BEAM_SRC_CIRC_I		,	L"工字型-钢骨混凝土圆梁",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	BEAM_SRC_CIRC_PIPE	,	L"圆钢管-钢骨混凝土圆梁",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	BEAM_SRC_CIRC_CROSS	,	L"十字工型-钢骨混凝土圆梁",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,

	BEAM_RC_T			,	L"T型混凝土梁",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,
	BEAM_RC_PIPE		,	L"混凝土圆管梁",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_PIPE		,	L"圆钢管梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_RECT		,	L"矩形钢梁",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	BEAM_ST_CIRC		,	L"圆形钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5

	BEAM_ST_CROSS	    ,	L"十字工型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_CRISS	    ,	L"十字型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_REGPOLY   ,	L"正多边形钢梁",SECTION_MAT_TYPE_ST,		SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_CHANNEL	 ,	L"槽型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_DBLCHANNEL ,	L"双槽型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,	SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_TRAP	     ,	L"梯形钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_L	    ,	L"L型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6	
	BEAM_ST_T	    ,	L"T型钢梁",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6


//柱截面,100-199
//PILLAR_ARBITRARY	,	L"任意组合截面混凝土柱",SECTION_MAT_TYPE_RC,

	PILLAR_RC_RECT		,	L"混凝土方柱",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_CIRC		,	L"混凝土圆柱",SECTION_MAT_TYPE_RC,				SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,

	PILLAR_ST_BOX		,	L"方钢管柱",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_PIPE		,	L"圆钢管柱",SECTION_MAT_TYPE_ST,				SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_I			,	L"工字型钢柱",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_ST_CROSS		,	L"十字工型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,

	PILLAR_CFT_BOX_RECT ,	L"方钢管混凝土柱",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	PILLAR_CFT_PIPE_CIRC,	L"圆钢管混凝土柱",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	PILLAR_SRC_RECT_BOX		,L"方钢管-钢骨混凝土柱",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	PILLAR_SRC_RECT_I		,L"工字型-钢骨混凝土方柱",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	PILLAR_SRC_RECT_CROSS	,L"十字工型-钢骨混凝土方柱",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	PILLAR_SRC_CIRC_PIPE,	L"圆钢管-钢骨混凝土柱",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	PILLAR_SRC_CIRC_I	,	L"工字型-钢骨混凝土圆柱",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	PILLAR_SRC_CIRC_CROSS,	L"十字工型-钢骨混凝土圆柱",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,
	PILLAR_RC_CRISS	    ,	L"十字型混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,

	PILLAR_RC_I			,	L"工字型混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_REGPOLY	,	L"正多边形混凝土柱",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_CHANNEL	,	L"槽型混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_BOX		,	L"矩形管混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_DBLCHANNEL,	L"双槽型混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	PILLAR_RC_CROSS		,	L"十字工型混凝土柱",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_TRAP		,	L"梯形混凝土柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	//PILLAR_RC_VAR		,	L"变截面混凝土方柱",SECTION_MAT_TYPE_RC,
	PILLAR_RC_L			,	L"L型混凝土柱",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_PIPE		,	L"混凝土圆管柱",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_SRC_RECT_PIPE,		L"圆钢管-钢骨混凝土方柱",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_PIPE,
	PILLAR_RC_T			,	L"T型混凝土柱",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	PILLAR_ST_RECT		,	L"矩形钢柱",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	PILLAR_ST_CIRC		,	L"圆形钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5

	PILLAR_ST_CRISS	    ,	L"十字型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_REGPOLY	    ,	L"正多边形钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_CHANNEL	    ,	L"槽型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_DBLCHANNEL    ,	L"双槽型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_TRAP	    ,	L"梯形钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_L	    ,		L"L型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6	
	PILLAR_ST_T	    ,		L"T型钢柱",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6

	AUX_REBAR_BOX		,	L"辅助构件",SECTION_MAT_TYPE_REBAR,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
#else
	//梁截面,0-99
	//BEAM_ARBITRARY		,	   L"任意组合截面混凝土梁", SECTION_MAT_TYPE_RC,

	BEAM_RC_RECT		,	L"Concrete Rectangular Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_BOX			,	L"Steel Box Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_I			,	L"Steel I-shaped Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_CFT_BOX_RECT	,	L"Concrete Filled Steel Box Beam",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	BEAM_SRC_RECT_I		,	L"I-shaped Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	BEAM_RC_CRISS		,	L"Concrete Cross-shaped Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,
	
	BEAM_RC_I			,	L"Concrete I-shaped Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_RC_CIRC		,	L"Concrete Circular Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,
	BEAM_RC_REGPOLY		,	L"Concrete Regular Polygon Beam",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	BEAM_RC_CHANNEL		,	L"Concrete Channel Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	BEAM_RC_BOX			,	L"Concrete Box Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_RC_DBLCHANNEL	,	L"Concrete Double Channel Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	BEAM_RC_CROSS		,	L"Concrete Cross-I-shaped Beam",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	BEAM_RC_TRAP		,	L"Concrete Trapezoidal Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	BEAM_CFT_PIPE_CIRC	,	L"Concrete Filled Steel Pipe Beam",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	BEAM_SRC_RECT_BOX	,	L"Box Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	BEAM_SRC_RECT_CROSS	,	L"Cross-I-shaped Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	//BEAM_RC_VAR		,	L"变截面混凝土方梁",SECTION_MAT_TYPE_RC,
	BEAM_RC_L			,	L"Concrete L-shaped Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,

	BEAM_SRC_RECT_PIPE	,	L"Pipe Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_PIPE,

	BEAM_SRC_CIRC_I		,	L"I-shaped Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	BEAM_SRC_CIRC_PIPE	,	L"Pipe Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	BEAM_SRC_CIRC_CROSS	,	L"Cross-I-shaped Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,

	BEAM_RC_T			,	L"Concrete T-shaped Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,
	BEAM_RC_PIPE		,	L"Concrete Pipe Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_PIPE		,	L"Steel Pipe Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_RECT		,	L"Steel Rectangular Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	BEAM_ST_CIRC		,	L"Steel Circular Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5

	BEAM_ST_CROSS	    ,	L"Steel Cross-I-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_CRISS	    ,	L"Steel Cross-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_REGPOLY   ,	L"Steel Regular Polygon Beam",SECTION_MAT_TYPE_ST,		SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_CHANNEL	 ,	L"Steel Channel Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_DBLCHANNEL ,	L"Steel Double Channel Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,	SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_TRAP	     ,	L"Steel Trapezoidal Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	BEAM_ST_L	    ,	L"Steel L-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6	
	BEAM_ST_T	    ,	L"Steel T-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6


//柱截面,100-199
//PILLAR_ARBITRARY	,	L"任意组合截面混凝土柱",SECTION_MAT_TYPE_RC,

	PILLAR_RC_RECT		,	L"Concrete Rectangular Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_CIRC		,	L"Concrete Circular Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,

	PILLAR_ST_BOX		,	L"Steel Box Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_PIPE		,	L"Steel Pipe Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_I			,	L"Steel I-shaped Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_ST_CROSS		,	L"Steel Cross-I-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,

	PILLAR_CFT_BOX_RECT ,	L"Concrete Filled Steel Box Column",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	PILLAR_CFT_PIPE_CIRC,	L"Concrete Filled Steel Pipe Column",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	PILLAR_SRC_RECT_BOX		,L"Box Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	PILLAR_SRC_RECT_I		,L"I-shaped Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	PILLAR_SRC_RECT_CROSS	,L"Cross-I-shaped Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	PILLAR_SRC_CIRC_PIPE,	L"Pipe Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	PILLAR_SRC_CIRC_I	,	L"I-shaped Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	PILLAR_SRC_CIRC_CROSS,	L"Cross-I-shaped Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,
	PILLAR_RC_CRISS	    ,	L"Concrete Cross-shaped Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,

	PILLAR_RC_I			,	L"Concrete I-shaped Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_REGPOLY	,	L"Concrete Regular Polygon Column",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_CHANNEL	,	L"Concrete Channel Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_BOX		,	L"Concrete Box Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_DBLCHANNEL,	L"Concrete Double Channel Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	PILLAR_RC_CROSS		,	L"Concrete Cross-I-shaped Column",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_TRAP		,	L"Concrete Trapezoidal Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	//PILLAR_RC_VAR		,	L"变截面混凝土方柱",SECTION_MAT_TYPE_RC,
	PILLAR_RC_L			,	L"Concrete L-shaped Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_PIPE		,	L"Concrete Pipe Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_SRC_RECT_PIPE,		L"Pipe Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_PIPE,
	PILLAR_RC_T			,	L"Concrete T-shaped Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	PILLAR_ST_RECT		,	L"Steel Rectangular Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5
	PILLAR_ST_CIRC		,	L"Steel Circular Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //乔保娟 2015.5.5

	PILLAR_ST_CRISS	    ,	L"Steel Cross-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_REGPOLY	    ,	L"Steel Regular Polygon Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_CHANNEL	    ,	L"Steel Channel Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_DBLCHANNEL    ,	L"Steel Double Channel Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_TRAP	    ,	L"Steel Trapezoidal Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6
	PILLAR_ST_L	    ,		L"Steel L-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6	
	PILLAR_ST_T	    ,		L"Steel T-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//乔保娟 2015.7.6

	AUX_REBAR_BOX		,	L"Auxiliary Member",SECTION_MAT_TYPE_REBAR,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
#endif
};


//由截面形状转为截面类型组合，提取类型应该用&运算
extern "C" _SSG_DLLIMPEXP int GetStructTypeByShape(SECTION_SHAPE iShape);

//标注类
class _SSG_DLLIMPEXP CLabel
{
public:
	void SetLabel(float a2,float a3,float b2,float b3,CString str)
	{
		A2=a2;
		A3=a3;
		B2=b2;
		B3=b3;
		Str=str;
	};

	//void Draw(CDC *pdc,DWORD color); //绘制标注，包括端线、标注线、文字
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);

private:
	float A2,A3,B2,B3;  //起始点坐标，靠近结构边界
	CString Str; //标注文字

	//标注,首末点逻辑坐标,字符串
	//Pos=文字位置，0-线间，1-右端，2-左端
	//ArrowType箭头类型，0-两端，1-右端，2-左端,3-无箭头
	void DrawLabel(CDC *pdc,float ratio,COLORREF color=RGB(0,0,0),int ArrowType=0,int Pos=0);  //画标注线和文字,ratio为坐标变换系数
};

//梁的子截面,一个独立区域是一个截面，可以是复连通域，一个截面必须是单一材料,只定义几何尺寸，不涉及类型和材料
class _SSG_DLLIMPEXP CSubSection
{
public:
	CSubSection(SUBSECTION_SHAPE ishape=SUBSHAPE_RECT,SUBSECTION_MAT_TYPE iSubMatType=SUBSECTION_MAT_TYPE_CONC);
	CSubSection(const CSubSection &sec) {pPoint=NULL; *this=sec; }  //复制构造函数
	~CSubSection(void) { Clear(); }

	//成员变量--------------------
	SUBSECTION_SHAPE iShape;  //截面形状（预定义形状或自绘形状）
	SUBSECTION_MAT_TYPE iSubMatType; //子截面材料类型（混凝土或型钢等单一材料,不能是混合材料）

	//截面几何参数
	//预定义形状几何参数
	union
	{
		struct GEO_RECT rect;
		struct GEO_BOX box;
		struct GEO_CIRC circ;
		struct GEO_PIPE pipe;
		struct GEO_I I;
		struct GEO_CROSS cross;
		struct GEO_REBAR rebar;
		struct GEO_CRISS criss;
		struct GEO_REGPOLY regpoly;
		struct GEO_CHANNEL channel;
		struct GEO_DBLCHANNEL dblchannel;
		struct GEO_TRAPEZOID trapezoid;
		struct GEO_L L;
		struct GEO_T T;
		struct GEO_RECT_VAR rect_var;
		float fValue[Sys_SubSectionParaNum];  //单位：米
	};
	float p2,p3; //子截面2和3方向的偏心距（m），子截面形心到组合截面局部坐标原点的距离，组合截面坐标原点选在外包矩形的中心点

	//自定义形状几何参数
	int nPoint;  //边界点数
	SECTION_POINT *pPoint;  //边界点坐标，坐标原点在形心，支持复连通域
	int nLabel; //标注个数
	CLabel Label[Sys_MaxLabel]; //标注

	//static int GetValueIndex(CString &sValueName);  //由参数名得到参数序号

	//成员函数--------------------
	//int CalBoundary(void); //根据预定义形状的特征尺寸计算边界点，对于自定义形状什么都不做，返回边界数，=1单连通域，>1则为复连通域
	SECTION_POINT *GetOuterBoundary(int &n);  //返回外边界点首地址和边界点数
	SECTION_POINT *GetNextBoundary(const SECTION_POINT *p0,int &n);  //返回下一个边界点首地址和边界点数,p0为当前边界首地址

	//剖分纤维单元,返回纤维数及动态数组,不包括钢筋
	BEAM_FIBRE_GEO *FibreMesh(int nFibre);
	//根据三角网计算纤维参数，结果放在返回的动态创建的pmesh数组中，适用于不规则截面
	//BEAM_FIBRE_GEO *GetFibrePara(int nFibre,POINT_LIST *PointCoor,ELEM_LIST *Tri);

	//计算外包矩形尺寸
	void GetRectSize(float &fWidth,float &fHeight);
	float Area(void); //计算截面面积
	float ShearArea2(void); //计算2方向有效剪切面积
	float ShearArea3(void); //计算3方向有效剪切面积
	float I2(void); //2方向惯性矩(对应2方向弯矩矢量)，相对于组合截面的局部坐标原点，故需要单独考虑偏心距
	float I3(void); //3方向惯性矩(对应3方向弯矩矢量)，相对于组合截面的局部坐标原点，故需要单独考虑偏心距
	float J1(void);  //扭转惯性矩，相对于组合截面的局部坐标原点，故需要单独考虑偏心距

	CSubSection & operator=(const CSubSection &sec); //重载赋值函数

	void Clear(void); //清除数据

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//线构件截面类
class _SSG_DLLIMPEXP CBeamSection
{
public:
	//构造与析构函数
	CBeamSection(void) {pConcFibreBuf=pSteelFibreBuf=NULL; Clear();}
	//CBeamSection(CString &sName) {pConcFibreBuf=pSteelFibreBuf=NULL; Clear(); this->sName=sName;}

	CBeamSection(const CBeamSection &sec)	{ pConcFibreBuf=pSteelFibreBuf=NULL; nUsedCount=0; *this=sec; }

	~CBeamSection(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称
	SECTION_MAT_TYPE iMatType;		//截面材料类型代码
	SECTION_SHAPE iSectionShape;	//截面形状类型,模板ID
	CArray<CSubSection,CSubSection&> aSubSec; //子截面数组

	//iFibreMethod--纤维剖分方案：
	//0--常规剖分（用系统参数，混凝土用Sys_RC_Double_ConcFibre）
	//1--简化剖分（用系统参数，混凝土用Sys_RC_Single_ConcFibre）
	//2--自定义剖分,使用iUserConcFibre和iUserSteelFibre
	int iFibreMethod;

	COLORREF dwColor; //显示颜色, 便于快速寻找

	//截面特征值参数,持久数据，保存到文件，用户可以自行输入和修改，修改截面时调用GetFeatures进行计算
	enum {BEAMSECTION_PARA=12};	//截面特征参数个数
	float ConcArea,      SteelArea;			//混凝土面积,钢材面积(不包括用配筋率计算的钢筋，下同)
	float ConcShearArea2,SteelShearArea2;	//2方向抗剪面积
	float ConcShearArea3,SteelShearArea3;	//3方向抗剪面积
	float ConcI2,        SteelI2;			//2方向转动惯量，对应力矩M2分量
	float ConcI3,        SteelI3;			//3方向转动惯量，对应力矩M3分量
	float ConcJ1,        SteelJ1;			//1方向转动惯量，极惯性矩，对应扭矩M1

	//临时数据,不保存到文件,读取截面、修改截面时、修改纤维控制参数时调用GetFibres计算
	float fWidth,fHeight; //宽度范围,高度范围，用于轮廓显示及范围测定，未考虑转角，因为转角是构件属性，不是截面属性
	int nConcFibre,nStructSteelFibre;  //混凝土纤维数量，钢纤维数量（不包括钢筋）
	BEAM_FIBRE_GEO *pConcFibreBuf,*pSteelFibreBuf;   //混凝土纤维数组，钢纤维数组（不包括分布钢筋，但包括边缘构件的钢筋柱）

	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据
	
	//根据模板创建截面，清除原有数据
	BOOL CreateSectionByTemplete(SECTION_SHAPE iShape);

	//计算截面特征值参数，修改后进行调用
	void GetFeatures(void);  

	//计算水平构件截面的钢筋总面积,配筋率单位1
	float GetBeamRebarArea(float ratioB,float ratioH);

	//根据配筋率计算竖向构件截面的钢筋总面积
	//fCorner--角筋面积（单根）,单位：m^2，若无法确定角筋，给0
	float GetPillarRebarArea(float ratioB,float ratioH,float &fCorner);

	//寻找混凝土子截面序号，返回-1：未找到
	int GetConcSubSecIndex(void);

	//重新计算最大尺寸fWidth,fHeight，用于绘图
	void GetMaxSize(void);

	//计算所有临时数据，强制剖分截面纤维单元,自动开内存.直接返回纤维数据，不包括钢筋,里面调用了GetMaxSize()
	void GetFibres(int iUserConcFibre=0,int iUserSteelFibre=0);

	//根据截面命名规则自动获得名称
	CString &AutoName(void);

	//根据组合截面中外层子截面计算内部子截面的尺寸
	//对单子截面什么都不做，直接返回
	//钢管混凝土内部截面应与外层截面紧密结合
	//钢骨混凝土内部截面的尺寸要小于外部截面尺寸，超出部分被截断
	void GetInnerSubSectionSize(void);

	//梁构件钢筋纤维,给定配筋率和钢筋直径，只对混凝土截面进行配筋，截面中最多只有一个混凝土截面，返回纤维坐标动态内存及纤维个数，不保存到类成员临时数组
	//配筋，ratioUpper面筋配筋率,ratioLower底筋配筋率,单位1
	BEAM_FIBRE_GEO *CreateBeamRebar(float ratioUpper,float ratioLower);

	//柱构件钢筋纤维,给定配筋率和钢筋直径，只对混凝土截面进行配筋，截面中最多只有一个混凝土截面，返回纤维坐标动态内存及纤维个数，不保存到类成员临时数组
	//配筋，ratioB--B方向配筋率,ratioH--H方向配筋率，圆截面只用第一个配筋率,单位1
	BEAM_FIBRE_GEO *CreatePillarRebar(float ratioB,float ratioH,float &fCorner);

	//判断是不是某类型结构的可用截面
	int IsUsable(STRUCT_TYPE iType);
	STRUCT_TYPE GetType(); //得到该截面的结构类型

	//规格化边缘构件方钢管截面的尺寸
	//area--给定的截面面积，ref_width--给定的截面宽度，sec_width--返回的规格化截面宽度，sec_t--返回的规格化壁厚
	//fThickPrec--厚度级差，单位：米
	static float GetEdgeSize(float area,float ref_width,float &sec_width,float &sec_t,float fThickPrec=0.0002f);

	CBeamSection & operator=(const CBeamSection &sec);

	void Clear(void);

	float DrawSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //绘制组合截面,返回绘制比例

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//截面类集合
class _SSG_DLLIMPEXP CSectionCollection
{
public:
	CSectionCollection(void){;}
	~CSectionCollection(void){Clear();}

	CSectionCollection(const CSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CBeamSection*,CBeamSection*> aBeamSectionPtr;  //梁截面类指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStrucType,const CString &sName);  //根据结构类型和截面名称获得截面ID,找不到返回-1
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	int GetIDByArea(STRUCT_TYPE iStrucType,float area); //根据截面面积获得截面ID,双边误差限5%，找不到返回-1
	CBeamSection *GetBeamSection(int id) const;  //根据给定的梁截面id返回截面指针
	//int GetIndex(const CString &SecName);  //根据给定的梁截面名称返回索引,找不到返回-1
	//CBeamSection *GetBeamSection(const CString &SecName);  //根据给定的梁截面名称返回截面指针
	//int GetAvailableID(void);  //得到有效的新增ID
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1

	void AppendSection(CBeamSection *psec);  //增加新截面，自动获取ID

	//增加或搜索边缘构件截面，fThickPrec--厚度级差
	//返回截面ID
	int AppendEdgeSection(float area,float width,float fThickPrec=0.0002f);

	CSectionCollection & operator=(const CSectionCollection &sec)
	{
		if(this==&sec) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<sec.aBeamSectionPtr.GetCount();i++) 
		{
			CBeamSection *s1=new CBeamSection(*(sec.aBeamSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aBeamSectionPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->id);  //记录最大ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadDefaultLib(void);  //加载系统库

};

struct _SSG_DLLIMPEXP SUBSECTION_SHAPE_PROP_TABLE
{
	SUBSECTION_SHAPE iShape;	//形状代号
	CString sName;				//形状名称
	int nPara;					//参数个数
	CString sParaName[Sys_SubSectionParaNum]; //参数名称
};

extern "C" _SSG_DLLIMPEXP SUBSECTION_SHAPE_PROP_TABLE aSubShapePropTable[Sys_SubSectionShapeNum];