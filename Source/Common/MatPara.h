#pragma once
#include "HeadDefine.h"

#include "..\Common\SysPara.h"
#include "..\Common\PublicFunc_Cpp.h"

const int g_iMax_Material=261;//因铝合金、纤维复合材料添加将值从200改为261
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
	MAT_MECH_PROP()
		: E(0)
		, V(0)
		, fcuk(0)
		, fck(0)
		, ftk(0)
		, fcd(0)
		, ftd(0)
		, fcm(0)
		, ftm(0)
		, fstk(0)
		, fTc(0)
		, fDen(0)
	{
	}
	MAT_MECH_PROP(const MAT_PROP& mat_prop)
		: E(mat_prop.E)
		, V(mat_prop.V)
		, fcuk(mat_prop.fcuk)
		, fck(mat_prop.fck)
		, ftk(mat_prop.ftk)
		, fcd(mat_prop.fcd)
		, ftd(mat_prop.ftd)
		, fcm(mat_prop.fcm)
		, ftm(mat_prop.ftm)
		, fstk(mat_prop.fstk)
		, fTc(mat_prop.fTc)
		, fDen(mat_prop.fDen)
	{
	}

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
};



int _SSG_DLLIMPEXP GetMatNum(void);//获取所有材料数

MAT_PROP _SSG_DLLIMPEXP GetMatPropById(int id);

int _SSG_DLLIMPEXP GetMatByName(const CString& sMat);

extern _SSG_DLLIMPEXP MAT_PROP g_Material[];
