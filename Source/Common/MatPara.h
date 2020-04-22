#pragma once

const int Sys_Conc_Para_Num=14; //材料库中混凝土参数个数
const int g_iMax_Material=100;
const int g_iMax_Conc=80;
const int g_iMax_Steel=80;


//材料类型，枚举值不得随意更改
enum MATERIAL_TYPE
{
	MAT_UNKNOWN=0, //未定义
	MAT_CONC=1, //混凝土
	MAT_REBAR=2, //钢筋
	MAT_STEEL=4, //型钢和钢板
};

//材料通用参数，包括混凝土和钢材、钢筋
struct MAT_PROP
{
	int id;
	wchar_t sName[256];
	MATERIAL_TYPE iType;
	float E;  //单位：MPa
	float V;
	float fck; //抗压强度 （标准强度）,单位：MPa
	float ftk; //抗拉强度（标准强度）,单位：MPa
};

//混凝土材料参数
struct MAT_CONCETE_PROP
{
	int id;
	double Para[Sys_Conc_Para_Num];  //具体含义和单位未知
};

//金属材料附加参数，不包括E,V
struct MAT_STEEL_PROP
{
	int id;
	double Fy,B;
};

//获取所有材料数
int GetMatNum(void);

//获取混凝土材料数
int GetConcNum(void);

//获取钢材和钢筋材料总数
int GetSteelNum(void);

extern MAT_PROP g_Material[];
extern MAT_CONCETE_PROP g_Concete_Prop[];
extern MAT_STEEL_PROP g_Steel_Prop[];