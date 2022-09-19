#pragma once
#include "..\Common\SectionBaseHead.h"
#include "..\Common\SysPara.h"

struct SectPara
{
	SectPara():/*SectFlag(0),B(0),H(0),*/a0(0), ConcGrade(1), ZJGrade(1), GJGrade(1), KZGrade(0)/*,B1(0),H1(0),bfc(0),hfc(0),bft(0),hft(0)*/
	{
		type_column = 0;
		l0 = 2400;
		rho_w = 0.003f;
		typeStrength = 0;
	}
	SUBSECTION_SHAPE iShape; //截面形状（预定义形状或原始形状）
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
		struct GEO_TRAPEZOID trapzoid;
		struct GEO_L L;
		struct GEO_T T;
		struct GEO_RECT_VAR rect_var;
		float fValue[Sys_SubSectionParaNum];	//单位: 米
	};

	//int SectFlag; //混凝土构件截面 0 矩形 1 圆形 2 T形 3 工字形
	//float B;		//截面尺寸 r
	//float H;		//截面尺寸 rs

	float a0;		//保护层厚度
	int ConcGrade;	//
	int ZJGrade;	//纵筋等级
	int GJGrade;	//箍筋等级
	int KZGrade;	//抗震等级
	//float B1;	
	//float bfc;		受压区翼缘宽度

	//增加长度， 类型（梁、柱、撑）
	int type;		//类型

	int typeStrength;

	int type_column;	//柱子类型 //0=普通柱；1=角柱；2=框支柱；3=框支角柱；
	float l0;			//长度	柱子计算用
	float rho_w;		//墙的均匀
};

struct SectForce
{
	SectForce() : M(0), V(0), T(0), N(1), M1(1), V1(1) {}
	float M;	//梁弯矩
	float V;	//梁剪力
	float T;	//截面扭矩
	float N;	//截面轴力

	float M1;	//截面另一方向弯矩
	float V1;	//截面另一方向剪力
};

//截面输出
struct SectOut
{
	SectOut()
		//, AsT2(0), AsC2(1), TorSect1(1), ShearSect2(1)
	{
		Yis1 = 0;
		ShearSect1 = 0;
		Asu = 0;
		Asd = 0;
		Asv = 0;
		Ast = 0;
		//Yis2 = 0;
		//TorSect2 = 0;
		//AsShear2 = 0;
		//AsTor2 = 0;
		As = 0;
		Asc = 0;
		Asx = 0;
		Asy = 0;
		Asvx = 0;
		Asvy = 0;
		Asvx15 = 0;
		Asvy15 = 0;
		Ast = 0;
	}

	//梁
	int Yis1;			//受弯配筋标志    相对受压区高度				

	float Asu;			//拉钢筋
	float Asd;			//压钢筋

	int ShearSect1;		//剪切截面是否满足要求 标志
	//	int TorSect1;		//扭转截面是否满足要求			//不使用

	float Asv;		//剪切箍筋
	float Ast;		//扭转箍筋

	//	float Yis2;			//截面另一方向相对受压区高度	//不使用
	//	float AsT2;			//截面另一方向拉钢筋			//不使用	
	//	float AsC2;			//截面另一方向压钢筋			//不使用

	//	int ShearSect2;		//截面另一方向剪切截面是否满足要求 (1 满足  0 不满足)
	//	int TorSect2;		//截面另一方向剪切截面是否满足要求 (1 满足  0 不满足)		//不使用

	//	float AsShear2; 	//截面另一方向剪切箍筋
	//	float AsTor2;		//截面另一方向扭转箍筋

	//截面满足标识

	//配筋成功标识


	//柱子
	float As;			//柱子纵筋面积 -- 用于圆柱

	float Asc;			//角筋面积 单根

	float Asx;			//x方向纵筋面积 包含角筋
	float Asy;			//y方向纵筋面积 包含角筋

	float Asvx;			//x方向箍筋面积
	float Asvy;			//y方向箍筋面积

	float Asvx15;		//x方向非加密区箍筋面积
	float Asvy15;		//y方向非加密区箍筋面积
};
