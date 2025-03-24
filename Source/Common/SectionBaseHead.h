#pragma once
#include "HeadDefine.h"

//子截面类型定义,单一材料
enum SUBSECTION_MAT_TYPE 
{
	SUBSECTION_MAT_TYPE_NONE=0,		//无材料
	SUBSECTION_MAT_TYPE_CONC=1,		//混凝土
	SUBSECTION_MAT_TYPE_REBAR=2,	//钢筋柱
	SUBSECTION_MAT_TYPE_ST=4,		//型钢
};

//截面分类定义，复合材料
enum SECTION_MAT_TYPE
{
	//按位组合：bit0—混凝土，bit1-钢筋，bit2-钢材；
	//名称				                           混凝土	   钢筋	   钢材
	SECTION_MAT_TYPE_RC=3,		//钢筋混凝土，      √			√
	SECTION_MAT_TYPE_ST=4,		//型钢，								√
	SECTION_MAT_TYPE_SRC=7,		//钢骨混凝土，      √			√		√
	SECTION_MAT_TYPE_CFT=5,		//钢管混凝土，      √					√
	SECTION_MAT_TYPE_REBAR=2,	//用于辅助构件截面，			√
	//必须从0开始连续编号,各项值不宜修改
};

// 截面类型：常规截面、型钢组合截面
enum SECTION_TYPE
{
	SECTION_UNKNOWN_SECTION = -1,		//未知
	REGULAR_CONCRETE_SECTION = 0, // 常规混凝土截面
	REGULAR_STEEL_SECTION = 1, // 常规型钢截面
	COMBIEND_SECTION = 2, // 组合截面
	STEEL_COMBIEND_SECTION = 3, //型钢组合截面
};

//截面形状定义,模板ID
//数值编码格式：
//RECT-实心矩形，BOX-空心矩形，CIRC-实心圆形，PIPE空心圆形，I-工字形，CROSS-十字工形，CRISS-十字形
//RC-钢筋混凝土，ST-型钢，SRC-钢骨混凝土，CFT-钢管混凝土
enum SECTION_SHAPE  
{
	//梁截面,0-99
	//BEAM_ARBITRARY	=0,		//任意组合截面梁

	BEAM_RC_RECT		=1,     //混凝土梁
	BEAM_ST_BOX			=2,     //方钢管梁
	BEAM_ST_I			=3,     //工字型钢梁
	BEAM_CFT_BOX_RECT	=4,     //方钢管混凝土梁（外包钢管）
	BEAM_SRC_RECT_I		=5,     //工字型-钢骨混凝土方梁

	//新增
	BEAM_RC_I			=6,		//工字型混凝土梁
	BEAM_RC_CIRC		=7,		//圆形混凝土梁
	BEAM_RC_REGPOLY		=8,		//正多边形混凝土梁
	BEAM_RC_CHANNEL		=9,		//槽型混凝土梁
	BEAM_RC_CRISS		=10,    //十字型混凝土梁，可退化为T型混凝土梁
	BEAM_RC_BOX			=11,	//矩形管混凝土梁
	BEAM_RC_DBLCHANNEL	=12,	//双槽型混凝土梁
	BEAM_RC_CROSS		=13,    //十字工型混凝土梁
	BEAM_RC_TRAP		=14,    //梯形混凝土梁

	BEAM_CFT_PIPE_CIRC	=15,    //圆钢管混凝土梁（外包钢管）

	BEAM_SRC_RECT_BOX	=16,    //方钢管-钢骨混凝土方梁
	BEAM_SRC_RECT_CROSS	=17,    //十字工型-钢骨混凝土方梁
	BEAM_RC_VAR			=18,    //变截面混凝土方梁--暂不支持
	BEAM_RC_L			=19,    //L型混凝土梁
	BEAM_SRC_RECT_PIPE	=20,    //圆型钢管-钢骨混凝土方梁

	BEAM_SRC_CIRC_I		=21,    //工字型-钢骨混凝土圆梁
	BEAM_SRC_CIRC_PIPE	=22,    //圆钢管-钢骨混凝土圆梁
	BEAM_SRC_CIRC_CROSS	=23,    //十字工型-钢骨混凝土圆梁
	BEAM_RC_T			=24,    //T型混凝土梁
	BEAM_RC_PIPE		=25,	//圆管形混凝土梁
	BEAM_ST_PIPE		=26,	//圆钢管梁
	BEAM_ST_RECT		=27,	//矩形钢梁  //乔保娟 2015.5.5
	BEAM_ST_CIRC		=28,	//实心圆形钢梁  //乔保娟 2015.5.5

	
	BEAM_ST_CROSS			=29,
	BEAM_ST_CRISS	    	=30,
	BEAM_ST_REGPOLY   		=31,
	BEAM_ST_CHANNEL			=32,
	BEAM_ST_DBLCHANNEL		=33,
	BEAM_ST_TRAP	    	=34,
	BEAM_ST_L	    		=35,
	BEAM_ST_T	    		=36,

	BEAM_ST_DOUBLELIMBS_CHANNEL = 37, // 双肢槽型钢
	BEAM_ST_DOUBLELIMBS_H = 38, // 双肢H型钢
	BEAM_ANGLE_ST_FOURLIMBS = 39, // 四肢角钢
	BEAM_ST_H_ADD_PLATE = 40, // H型加上板钢
	BEAM_ANGLE_ST_DOUBLELIMBS = 41, // 双肢角钢
	BEAM_ST_THREELIMBS_PIPE = 42, // 三肢圆管钢

	//柱、斜撑截面,100-199
	PILLAR_ARBITRARY		=100,		//任意组合截面柱

	PILLAR_RC_RECT			=101,      //混凝土方柱
	PILLAR_RC_CIRC			=102,      //混凝土圆柱

	PILLAR_ST_BOX			=103,      //方钢管柱
	PILLAR_ST_PIPE			=104,      //圆钢管柱
	PILLAR_ST_I				=105,      //工字型钢柱
	PILLAR_ST_CROSS			=106,      //十字工型钢柱

	PILLAR_CFT_BOX_RECT		=107,   //方钢管混凝土方柱（外包钢管）
	PILLAR_CFT_PIPE_CIRC	=108,   //圆钢管混凝土圆柱（外包钢管）

	PILLAR_SRC_RECT_BOX		=109,   //方钢管-钢骨混凝土方柱
	PILLAR_SRC_RECT_I		=110,   //工字型-钢骨混凝土方柱
	PILLAR_SRC_RECT_CROSS	=111,   //十字工型-钢骨混凝土方柱

	PILLAR_SRC_CIRC_PIPE	=112,   //圆钢管-钢骨混凝土圆柱
	PILLAR_SRC_CIRC_I		=113,   //工字型-钢骨混凝土圆柱
	PILLAR_SRC_CIRC_CROSS	=114,   //十字工型-钢骨混凝土圆柱

	//新增
	PILLAR_RC_I				=115,	//工字型混凝土柱
	PILLAR_RC_REGPOLY		=116,	//正多边形混凝土柱
	PILLAR_RC_CHANNEL		=117,	//槽型混凝土柱
	PILLAR_RC_CRISS		    =118,   //十字型混凝土柱，可退化为T型混凝土柱
	PILLAR_RC_BOX			=119,	//矩形管混凝土柱
	PILLAR_RC_DBLCHANNEL	=120,	//双槽型混凝土柱
	PILLAR_RC_CROSS			=121,   //十字工型混凝土柱
	PILLAR_RC_TRAP			=122,   //梯形混凝土柱
	PILLAR_RC_VAR			=123,   //变截面混凝土方柱--暂不支持
	PILLAR_RC_L				=124,   //L型混凝土柱
	PILLAR_RC_PIPE			=125,	//圆管形混凝土柱
	PILLAR_SRC_RECT_PIPE	=126,	//圆钢管-钢骨混凝土方柱
	PILLAR_RC_T				=127,	//T形混凝土柱		//乔保娟 2015.5.5
	PILLAR_ST_RECT			=128,	//矩形钢柱		//乔保娟 2015.5.5
	PILLAR_ST_CIRC			=129,	//实心圆形钢柱		//乔保娟 2015.5.5

	PILLAR_ST_CRISS			=130,
	PILLAR_ST_REGPOLY   	=131,
	PILLAR_ST_CHANNEL		=132,
	PILLAR_ST_DBLCHANNEL	=133,
	PILLAR_ST_TRAP			=134,
	PILLAR_ST_L	    		=135,
	PILLAR_ST_T	    		=136,

	PILLAR_HANLINHAI		=137,	//韩林海

	PILLAR_ST_DOUBLELIMBS_CHANNEL = 138, // 双肢槽型钢柱
	PILLAR_ST_DOUBLELIMBS_H = 139, // 双肢H型钢柱
	PILLAR_ANGLE_ST_FOURLIMBS = 140, // 四肢角钢柱
	PILLAR_ST_H_ADD_PLATE = 141, // H型加上板钢柱
	PILLAR_ANGLE_ST_DOUBLELIMBS = 142, // 双肢角钢柱
	PILLAR_ST_THREELIMBS_PIPE = 143, // 三肢圆管钢柱

	//边缘构件、虚梁、连梁纵筋截面,200-299
	AUX_REBAR_BOX	=200,		//辅助构件，包括边缘构件,虚梁，连梁纵筋，截面类型为SECTION_MAT_TYPE_REBAR，子截面类型为SUBSECTION_MAT_TYPE_REBAR，但材料只有钢筋
	AUX_REBAR_CIRC = 201,//连梁斜筋

	SHAPE_LAST, //结尾标识增加截面都放在这前面！！！
};

//子截面形状定义
enum SUBSECTION_SHAPE 
{
	SUBSHAPE_UNKNOWN	=-1,	//无效
	SUBSHAPE_ARBITRARY  =0,		//任意绘制
	SUBSHAPE_RECT       =1,		//实心矩形
	SUBSHAPE_BOX		=2,		//矩形管
	SUBSHAPE_CIRC       =3,		//实心圆
	SUBSHAPE_PIPE       =4,		//圆管
	SUBSHAPE_I          =5,		//工字形
	SUBSHAPE_CROSS		=6,		//十字工形
	SUBSHAPE_LINE		=7,		//一字线形，用轴线参数表示矩形
	SUBSHAPE_REBAR		=8,		//钢筋点，此时构件不再支持纵筋属性
	SUBSHAPE_CRISS      =9,     //十字形

	SUBSHAPE_REGPOLY    =10,	//正多边形
	SUBSHAPE_CHANNEL    =11,	//槽形
	SUBSHAPE_DBLCHANNEL =12,	//双槽形
	SUBSHAPE_TRAPEZOID  =13,	//梯形
	SUBSHAPE_L			=14,	//L形
	SUBSHAPE_T			=15,	//T形

	SUBSHAPE_HANLINHAI_OUTER		=16,	//韩林海外截面  韩林海以材料区分
	SUBSHAPE_HANLINHAI_INNERSTEEL	=17,	//韩林海内四个钢管截面
	SUBSHAPE_HANLINHAI_INNERCONC	=18,	//韩林海内四个混凝土，默认为外部的混凝土

	SUBSHAPE_DOUBLELIMBS_CHANNEL = 19,	//双肢槽型钢柱
	SUBSHAPE_DOUBLELIMBS_H = 20,	//双肢H型钢柱
	SUBSHAPE_FOURLIMBS_L = 21,	//四肢角钢柱
	SUBSHAPE_H_ADD_PLATE = 22,	//H型+板钢柱
	SUBSHAPE_DOUBLELIMBS_L = 23,	//双肢角钢柱
	SUBSHAPE_THREELIMBS_PIPE = 24,	//三肢圆管钢柱

};

//截面边界点
struct SECTION_POINT
{
	float x2,x3;  //单位：米
	int iBnd;  //边界序号，外边界为0,点逆时针排列，内边界为1（可以多个内边界，边界序号从1开始编号），顺时针排列，边界点要连续存放
};

//纤维几何数据结构
struct BEAM_FIBRE_GEO
{
	BEAM_FIBRE_GEO() :FibreH2(0), FibreH3(0), FibreArea(0) {}
	BEAM_FIBRE_GEO(float H2, float H3, float Area) :FibreH2(H2), FibreH3(H3), FibreArea(Area) {}
	float FibreH2, FibreH3, FibreArea; //纤维中心坐标和面积，相对整个截面坐标原点（而不是子截面），已经加上子截面偏心距
};

//截面参数定义，单位：米
struct GEO_RECT	//实心矩形
{
	float B,H;  //截面宽度B，截面高度H
};

struct GEO_BOX		//空心矩形
{
	float Bs,Hs,tf1,tf2,tw1,tw2; //截面总宽度B，截面总高度H，上翼缘厚度tf1,下翼缘厚度tf2,左腹板厚度tw1,右腹板厚度tw2
};

struct GEO_CIRC	//实心圆形
{
	float D;	//直径D
};

struct GEO_PIPE	//空心圆形
{
	float Ds,tw; //外直径D，壁厚tw
};

struct GEO_I	//工字形
{
	float Hs,tw,B1,tf1,B2,tf2;  //截面总高度Hs，腹板厚度tw1，上翼缘宽度B1，上翼缘厚度tf1，下翼缘宽度B2，下翼缘厚度tf2
};

struct GEO_CROSS	//十字工形
{
	//竖向工形总高度H1，竖向工形腹板厚度tw1，竖向工形上翼缘宽度B1，竖向工形上翼缘厚度tf1，竖向工形下翼缘宽度B2，竖向工形下翼缘厚度tf2；
	float H1,tw1,B1,tf1,B2,tf2;
	//横向工形总高度H2，横向工形腹板厚度tw2，横向工形左翼缘宽度B3，横向工形左翼缘厚度tf3，横向工形右翼缘宽度B4，横向工形右翼缘厚度tf4
	float H2,tw2,B3,tf3,B4,tf4;
};

struct GEO_CRISS	//十字形
{
	//L"腹板厚度(m)",L"截面高度(m)",L"翼缘上边距(m)",L"翼缘厚度(m)",L"翼缘左宽度(m)",L"翼缘右宽度(m)",
	float B,H,U,T,D,F;
};

struct GEO_REGPOLY	//正多边形
{
	//L"外接圆直径(m)",L"多边形边数"
	float B,N;
};

struct GEO_CHANNEL	//槽型
{
	//L"腹板厚度(m)",L"截面总高度(m)",L"上翼缘宽度(m左为+)",L"上翼缘厚度(m)",L"下翼缘宽度(m左为+)",L"下翼缘厚度(m)",
	float B,H,U,T,D,F;
};

struct GEO_DBLCHANNEL	//双槽型
{
	//L"腹板厚度(m)",L"截面总高度(m)",L"上翼缘宽度(m外伸+)",L"翼缘厚度(m)",L"下翼缘宽度(m外伸+)",L"肢间最小间距(m)",
	float B,H,U,T,D,F;
};

struct GEO_TRAPEZOID	//梯形
{
	//L"梯形底边宽度(m)",L"截面总高度(m)",L"左上边伸长(m外伸+)",L"右上边伸长(m外伸+)",
	float B,H,T,F;
};

struct GEO_L	//L形
{
	//L"腹板厚度(m)",L"截面总高度(m上为+)",L"翼缘宽度(m左为+)",L"翼缘厚度(m)",
	float B,H,D,F;
};

struct GEO_T	//T形
{
	//L"腹板厚度(m)",L"截面总高度(m上为+)",L"翼缘宽度(m)",L"翼缘厚度(m)",
	float B,H,D,F;
};

struct GEO_HANLINHAI_OUTER  //韩林海 外
{
	//float B, H, D, d, tc, ca, a, b;    //截面宽度B、高度H、外径D、厚度d、空心外边缘到混凝土外边缘距离外面缘距离tc、钢管外边缘到混凝土外边缘距离 ca
										//八边形空心边长 a、八边形空心边长b
	float B, H, D, t, b1, h1, hf1, hf2, tc1, tc2, ac1, ac2, ac3, ac4;
};

struct GEO_HANLINHAI_INNERSTEEL		//韩林海四个钢管
{
	float B, H, D, t, ac1, ac2, ac3, ac4;
};

struct GEO_HANLINHAI_INNERCONC		//韩林海四个混凝土
{
//	float B, H, D, d, ca;
	float B, H, D, t, ac1, ac2, ac3, ac4;
};

struct GEO_DOUBLELIMBS_H	//双肢H字型
{
	//L"截面总高度(m)",L"下翼缘宽度(m)",L"上翼缘宽度(m)",L"上翼缘厚度(m)",L"下翼缘厚度(m)",L"腹板1厚度(m)",,L"腹板2厚度(m)"L"上肢间间距(m)，L"下肢间间距(m)",
	float H, B1, tf1,tw1, d1;
};

struct GEO_FOURLIMBS_L	//四肢L型
{
	//L"翼缘宽度",L"截面总高度(m)",L"翼缘厚度(m)",L"腹板厚度(m)",L"横向肢间间距(m)",L"纵向肢间间距(m)"
	float D, H, F, B,d1,d2;
};

struct GEO_H_ADD_PLATE	//H字型 + 板
{
	//L"截面总高度(m)",L"下翼缘宽度(m)",L"上翼缘宽度(m)",L"上翼缘厚度(m)",L"下翼缘厚度(m)",L"腹板1厚度(m)",,L"腹板2厚度(m)"L"加劲板厚度(m)，L"加劲板间距(m)",
	float H, B1, tf1, tw1, ts,Bs;
};

struct GEO_DOUBLELIMBS_L	//双肢L型
{
	//L"翼缘宽度",L"截面总高度(m)",L"翼缘厚度(m)",L"腹板厚度(m)",L"间距(m)""
	float D, H, F, B, d1;
};

struct GEO_THREELIMBS_PIPE  // 三肢圆管钢柱
{
	//L"截面高度",L"截面宽度(m)",L"外直径(m)",L"壁厚(m)"
	float  H, B, Ds, tw;
};

struct GEO_RECT_VAR //变截面
{
	//L"截面宽度(m)",L"截面高度1(m)",L"截面高度2(m)",
	float B,H1,H2;
};

struct GEO_LINE	//一字形，轴线
{
	float y1,z1,y2,z2,t;  //局部坐标: 起点y坐标，起点z坐标，终点y坐标，终点z坐标，厚度
};

struct GEO_REBAR	//钢筋点
{
	float y,z,d;  //局部坐标，y坐标， z坐标，直径（m）
};

struct GEO_CONC	//混凝土纤维点
{
	float y,z,area;  //局部坐标，y坐标， z坐标，面积（m^2）
};

struct GEO_STEEL	//钢纤维点
{
	float y,z,area;  //局部坐标，y坐标， z坐标，面积（m^2）
};

//截面材料类型代码,1-混凝土；2-单层钢板混凝土；3-双层钢板混凝土；4-纯钢板
enum PALTESECTION_MAT_TYPE 
{
	PALTESECTION_MAT_TYPE_NONE=0,	//无材料
	PALTESECTION_MAT_TYPE_CONC=1,	//混凝土
	PALTESECTION_MAT_TYPE_SRC=2,		//单层钢板混凝土
	PALTESECTION_MAT_TYPE_CFT=3,		//双层钢板混凝土
	PALTESECTION_MAT_TYPE_ST=4,			//纯钢板
	PALTESECTION_MAT_TYPE_CONCHOLLOW=5,			//双层混凝土
	PALTESECTION_MAT_TYPE_STHOLLOW=6,			//双层钢板
};


//  加固方法定义 辛业文 2023年5月5日
enum REINFORCED_METHOD
{
	METHOD_UNKNOWN = -1,				//无效

	// 梁
	BEAM_METHOD_ENLARGED_SECTION = 0,		//增大截面法
	BEAM_METHOD_DISPLACEMENT_CONCRETE = 1,	//置换混凝土法
	BEAM_METHOD_WRAPPED_SECTION_STEEL = 2,	//外包型刚法
	BEAM_METHOD_PASTE_STELL_PLATE = 3,		//外贴钢板法
	BEAM_METHOD_PASTE_FIBER = 4,			//外贴纤维法

	// 柱
	PILLAR_METHOD_ENLARGED_SECTION = 5,		//增大截面法
	PILLAR_METHOD_DISPLACEMENT_CONCRETE = 6,	//置换混凝土法
	PILLAR_METHOD_WRAPPED_SECTION_STEEL = 7,	//外包型刚法
	PILLAR_METHOD_PASTE_STELL_PLATE = 8,		//外贴钢板法
	PILLAR_METHOD_PASTE_FIBER = 9,				//外贴纤维法

};

//  加固截面方法定义 辛业文 2023年5月5日
enum SUBSECTION_REINFORCED_TYPE
{
	REINFORCED_TYPE_UNKNOWN = -1,				//无效

	// 梁
	BEAM_ENLARGED_SECTION_TYPE = 0,		//增大截面
	BEAM_DISPLACEMENT_CONCRETE_TYPE = 1,	//置换混凝土
	BEAM_WRAPPED_SECTION_STEEL_TYPE = 2,	//外包型刚
	BEAM_PASTE_STELL_PLATE_TYPE = 3,		//外贴钢板
	BEAM_PASTE_FIBE_TYPE = 4,				//外贴纤维

	// 柱
	PILLAR_ENLARGED_SECTION_TYPE = 5,		//增大截面
	PILLAR_DISPLACEMENT_CONCRETE_TYPE = 6,	//置换混凝土
	PILLAR_WRAPPED_SECTION_STEE_TYPE = 7,	//外包型刚
	PILLAR_PASTE_STELL_PLATE_TYPE = 8,		//外贴钢板
	PILLAR_PASTE_FIBER_TYPE = 9,			//外贴纤维

};



// 梁加固方法参数定义 辛业文 2023年5月5日义，单位：米
struct BEAM_ENLARGED_SECTION	//增大截面法
{
	float B, H1, H2;  //截面宽度B向增加，梁顶H1向增加, 梁底H2向增加
};

struct BEAM_DISPLACEMENT_CONCRETE		//置换混凝土法
{
	float H1, H2; //梁顶置换深度H1， 梁底置换深度H2
};

struct BEAM_WRAPPED_SECTION_STEEL		//外包钢板法
{
	float L1, L2, T1, L3, L4, T2, B, T3, D; //底部角钢的尺寸:Y向L1， X向L2， 厚度T1； 顶部角钢的尺寸:Y向L3， X向L4， 厚度T2； 箍板信息：宽度B，厚度T3， 间距D
};

struct BEAM_PASTE_STELL_PLATE		//外贴钢板法
{
	// 梁顶钢板宽度，梁顶钢板厚度，梁底钢板宽度，梁底钢板厚度，梁侧粘贴箍板宽度，梁侧粘贴箍板厚度， 梁侧粘贴箍板间距
	float B1, T1, B2, T2, B3, T3, D; 
};

struct BEAM_PASTE_FIBER		//外贴纤维法
{
	//梁顶复合材层数，梁顶复合材层数宽度，梁底复合材层数，梁底复合材层数宽度，梁侧复合材层数，梁侧复合材层数宽度，梁侧复合材间距，复合材的每层厚度,重要性 
	float N1, B1, N2, B2, N3, B3, D, T; 
	float iComponentType;  // 0：一般构件， 1：重要构件
};


// 柱加固方法参数定义 辛业文 2023年5月5日义，单位：米
struct PILLAR_ENLARGED_SECTION	//增大截面法
{
	float B1,B2, H1, H2;  //截面宽度B1向增加，截面宽度B2向增加,截面宽度H1向增加, 截面宽度H2向增加
};

struct PILLAR_DISPLACEMENT_CONCRETE		//置换混凝土法
{
	float B, H; //截面宽度B向置换深度B， 截面宽度H向置换深度H
};

struct PILLAR_WRAPPED_SECTION_STEEL		//外包钢板法
{
	float  L1, L2, T1, B, T, D; ////角钢的尺寸:Y向L1， X向L2， 厚度T1；缀板信息：宽度B，厚度T， 间距D
};

struct PILLAR_PASTE_STELL_PLATE		//外贴钢板法
{
	float B, H, T; // 截面B向钢板宽度， 截面H向钢板宽度, 厚度T
};

struct PILLAR_PASTE_FIBER		//外贴纤维法
{
	float B1, H, B2, D, N, T; //截面B1向外贴材料宽度, 截面H1向外贴材料宽度, 环形箍宽度B2, 环形箍中心间距D, 复合材层数N, 复合材的每层厚度T,重要性 
	float iComponentType; // 0：一般构件， 1：重要构件
};


//  板墙加固方法定义 辛业文 2023年5月5日
enum PLATE_REINFORCED_METHOD
{
	PLATE_METHOD_UNKNOWN = -1,				//无效

	// 板
	PLATE_METHOD_ENLARGED_SECTION = 0,		//增大截面法
	PLATE_METHOD_PASTE_STELL_PLATE = 1,		//外贴钢板法
	PLATE_METHOD_PASTE_FIBER = 2,			//外贴纤维法

	// 墙
	WALL_METHOD_ENLARGED_SECTION = 3,		//增大截面法
	WALL_METHOD_PASTE_STELL_PLATE = 4,		//外贴钢板法
};

// 墙板加固材料
enum PALTESECTION_REINFORCED_MAT_TYPE
{
	PALTESECTION_REINFORCED_MAT_TYPE_NONE = 0,	//无材料
	PALTESECTION_REINFORCED_MAT_TYPE_CONC = 1,	//混凝土
	PALTESECTION_REINFORCED_MAT_TYPE_ST = 2,	//纯钢板
	PALTESECTION_REINFORCED_MAT_TYPE_FIBER = 3,	//纤维
};

// 板加固方法参数定义 辛业文  2023年10月18日义，单位：米
struct PLATE_ENLARGED_SECTION	//增大截面法
{
	float H1, H2;  // 板顶H1向增加, 板底H2向增加
};

struct PLATE_PASTE_STELL_PLATE		//外贴钢板法
{
	// 钢板的加固方向， 板顶钢板宽度，板顶钢板厚度，板顶钢板间距，钢板的加固方向， 板顶钢板宽度，板顶钢板厚度，板顶钢板间距
	float Location1, B1, T1, D1, Location2, B2, T2, D2; // Location1 和 Location2 用-1、0、1、2表示：-1表示不加固， 0 表示X向， 1表示Y向，2表示 表示双向
};

struct PLATE_PASTE_FIBER		//外贴纤维法
{
	//梁底复合材层数，梁底复合材层数宽度，梁顶复合材层数，梁顶复合材层数宽度，梁侧复合材层数，梁侧复合材层数宽度，梁侧复合材间距，复合材的每层厚度
	float N1, B1, N2, B2, N3, B3, D, T;
};

// 墙加固方法参数定义 辛业文 2023年10月18日义，单位：米
struct WALL_ENLARGED_SECTION	//增大截面法
{
	float B1, B2;  // 墙1侧增加, 墙2侧增加
};

struct WALL_PASTE_STELL_PLATE		//外贴钢板法
{
	// 墙1侧钢板宽度，墙1侧钢板厚度，墙1侧钢板间距，  墙2钢板宽度， 墙2钢板厚度， 墙2钢板间距
	float B1, T1, D1, B2, T2, D2;
};