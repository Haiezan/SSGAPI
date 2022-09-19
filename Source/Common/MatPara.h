#pragma once
#include "HeadDefine.h"

#include "..\Common\SysPara.h"
#include "..\Common\PublicFunc_Cpp.h"

const int g_iMax_Material=125;//因预应力筋添加将值从100改为120
const int g_iMax_Conc=80;
const int g_iMax_Steel=100;


//材料通用参数，包括混凝土和钢材、钢筋
struct MAT_PROP
{
	int id;
	wchar_t *sName;//sName[256];标准材料库的材料名称
	//CString sName;
	MATERIAL_TYPE iType;
	float E;	//单位：MPa
	float V;	//泊松比
	float fcuk;	//立方体抗压强度（标准值），单位：MPa	
	float fck;	//抗压强度（标准值），单位：MPa	
	float ftk;	//抗拉强度（标准值），单位：MPa		
	float fcd;	//抗压强度（设计值），单位：MPa，钢筋、钢材设计值没给值的按0.9标准值取值
	float ftd;	//抗拉强度（设计值），单位：MPa，钢筋、钢材设计值没给值的按0.9标准值取值
	float fcm;	//抗压强度（平均值，广东省），单位：MPa
	float ftm;	//抗拉强度（平均值，广东省），单位：MPa
	float fstk;	//极限强度(标准值），单位：MPa，混凝土为按0.88倍fcuk，钢筋为为按1.5倍ftk，钢材为为按1.5倍ftk，预应力筋为公称强度，朱衡给的
	float fTc;	//线膨胀系数1/C
	float fDen;	//质量密度
	//MAT_PROP & operator=(const MAT_PROP &mat_prop);
};

struct MAT_MECH_PROP
{
	float E;	//单位：MPa
	float V;	//泊松比
	float fcuk;	//立方体抗压强度（标准值），单位：MPa	
	float fck;	//抗压强度（标准值），单位：MPa	
	float ftk;	//抗拉强度（标准值），单位：MPa		
	float fcd;	//抗压强度（设计值），单位：MPa，钢筋、钢材设计值没给值的按0.9标准值取值
	float ftd;	//抗拉强度（设计值），单位：MPa，钢筋、钢材设计值没给值的按0.9标准值取值
	float fcm;	//抗压强度（平均值，广东省），单位：MPa
	float ftm;	//抗拉强度（平均值，广东省），单位：MPa
	float fstk;	//极限强度(标准值），单位：MPa，混凝土为按0.88倍fcuk，钢筋为为按1.5倍ftk，钢材为为按1.5倍ftk，预应力筋为公称强度，朱衡给的
	float fTc;	//线膨胀系数1/C
	float fDen;	//质量密度
	//MAT_PROP & operator=(const MAT_PROP &mat_prop);
};


//获取所有材料数
int _SSG_DLLIMPEXP GetMatNum(void);
extern _SSG_DLLIMPEXP MAT_PROP g_Material[];
