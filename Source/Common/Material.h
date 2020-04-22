#pragma once
#include "HeadDefine.h"
//#include "..\Common\SysPara.h"
#include "../Common/MatPara.h"
#include "ASCFile.h"


#define MATERIAL_TYPE_NUM 3


struct _SSG_DLLIMPEXP MATERIAL_TYPE_PROP
{
	MATERIAL_TYPE type;  //材料类别 
	CString name;  //类别名称
};

//材料曲线点
struct _SSG_DLLIMPEXP MATCURVE
{
	float strain; //应变
	float stress; //应力
	float damage; //损伤
};

//得到材料数组g_Material对应的下标
int GetMatIndex(int id);
float GetMatE(int id);
float GetMatV(int id);

//材料类
class _SSG_DLLIMPEXP CMaterial
{
public:
	CMaterial(void){pComp=NULL;pTension=NULL;sName=L"";nCompPara=nTensPara=0;iConcType=0;id=-1;Fy=0;B=0;}

	//复制构造函数
	CMaterial(const CMaterial &mat)
	{
		pComp=NULL;pTension=NULL;
		*this=mat;
	}

	~CMaterial(void)
	{
		if(pComp) delete[] pComp; pComp=NULL;
		if(pTension) delete[] pTension; pTension=NULL;
		nCompPara=nTensPara=0;
	}

	//基本属性
	int id; //材料编号，不一定连续 
	CString sName;   //材料名称,名称作为索引
	MATERIAL_TYPE iType; //材料类型
	int iConcType;  //iType==MAT_CONC时使用，混凝土材料类别，0--通用混凝土，1--自定义

	//各种材料通用参数
	float E;  //初始弹性模量（MPa=N/mm^2）
	float V;  //泊松比

	//通用混凝土材料参数，具体含义见文档,iType==MAT_CONC && iConcType==0时有效
	float ConcPara[Sys_Conc_Para_Num];

	//自定义混凝土特有参数
	int nCompPara,nTensPara;  //压、拉参数个数
	MATCURVE *pComp;  //压曲线参数
	MATCURVE *pTension;  //拉曲线参数

	//钢材特有参数
	float Fy; //屈服强度，kN/m^2
	float B; //强化参数

	//float G(void) {return E/(1.0f+2.0f*V);}  //计算剪切模量,各种材料通用
	/*Modified by Hexf 2010-10-08*/ 
	inline float G(void) {return 0.5f*E/(1.0f+V);}  //计算剪切模量,各种材料通用

	//设置自定义混凝土材料参数,将数组中的数据进行复制
	void SetConc(CString &sname,/*float dens,*/float e,float poission,int ntenpara,MATCURVE *ptension,int ncomppara,MATCURVE *pcomp);
	//设置钢筋材料参数
	void SetRebr(CString &sname,/*float dens,*/float e,float poission,float fy,float b);
	//设置钢材材料参数
	void SetSteel(CString &sname,/*float dens,*/float e,float poission,float fy,float b);

	CMaterial & operator=(const CMaterial &mat);

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CMaterialCollection
{
public:
	CMaterialCollection(void);
	~CMaterialCollection(void){Clear();}

	//复制构造函数
	CMaterialCollection(const CMaterialCollection &mat) 
	{
		*this=mat;
	}

	CArray<CMaterial,CMaterial&> aMaterial; 

public:
	int GetIndex(const CString &sName);				//根据名字查找数组索引,找不到返回-1
	int GetConcIndex(const CString &sName);			//根据名字查找混凝土材料索引（混凝土材料单独编码）,找不到返回-1
	int GetSteelIndex(const CString &sName);		//根据名字查找型钢材料索引（型钢材料单独编码包括钢筋和型钢、钢板）,找不到返回-1
	//int GetID(CString &sName);   //根据名字查找ID
	CMaterial *GetMat(const CString &sName); //根据名称查找材料地址

	int GetConcCount(void);   //计算混凝土材料数
	int GetSteelCount(void);  //计算钢材材料数，包括钢筋

	void Clear(void)
	{
		aMaterial.RemoveAll();
	}

	CMaterialCollection & operator=(const CMaterialCollection &mat)
	{
		if(this==&mat) return *this;

		Clear();

		aMaterial.Copy(mat.aMaterial);
		//for(int i=0;i<mat.aMaterial.GetCount();i++)
		//{
		//	CMaterial imat=(mat.aMaterial[i]);
		//	aMaterial.Add(imat);
		//}
		return *this;
	}

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadWholeLib(void);   //加载全部材料
};
