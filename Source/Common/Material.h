#pragma once
#include "HeadDefine.h"
#include "../Common/MatPara.h"
#include "ASCFile.h"

#define MATERIAL_TYPE_NUM 7

struct _SSG_DLLIMPEXP MATERIAL_TYPE_PROP
{
	MATERIAL_TYPE type;  //材料类别 
	CString name;  //类别名称
};
extern _SSG_DLLIMPEXP MATERIAL_TYPE_PROP MaterialTypeProp[]; //张吟峰 增加 2021-10-26


//材料曲线点
struct _SSG_DLLIMPEXP MATCURVE
{
	float strain; //应变
	float stress; //应力
	float damage; //损伤
};


//材料类
class _SSG_DLLIMPEXP CMaterial
{
public:
	CMaterial(void);
	CMaterial(const MAT_PROP& prop);
	//复制构造函数
	CMaterial(const CMaterial &mat)
	{
		pConcPara1D = NULL; 
		pConcPara2DS = NULL; 
		pConcPara2DD = NULL; 
		pSteel1D = NULL; 
		pSteel2D = NULL; 

		*this=mat;
	};
	~CMaterial(void)
	{
		Clear();
	}
	void Clear(void);
	CMaterial & operator=(const CMaterial &mat);

	int id; //材料编号，唯一不变标识，根系统材料库编号不同 
	CString sName;   //材料用户自定义名称,名称作为索引
	MATERIAL_TYPE iType; //材料类型

	//各种材料通用参数
	MAT_MECH_PROP m_linearMatProps;//材料，包括混凝土和钢材、钢筋的线性参数，单位为MPa
	inline float G(void) {return 0.5f*m_linearMatProps.E/(1.0f+m_linearMatProps.V);}  //计算剪切模量,各种材料通用

	//非线性参数，单位为KPa
	float fc;	//混凝土、钢筋、钢材抗压强度，用于非线性计算，单位：KPa	
	float ft;	//混凝土、钢筋、钢材抗拉强度，用于非线性计算，单位：KPa


	//混凝土
	//一维
	int iCSkeleton_c;	//一维参数：(0-用户自定义,1-规范全曲线,2-Rusch,3-Hongnestad,4-Mander,5-钱稼茹,6-Kent-Park)
	int iCSkeletonTube;	//一维参数：(0-与iCSkeleton_c相同,1-韩林海)
	int iCSkeleton_t;	//一维参数：(0-用户自定义） (1-多段线(6points inc. zero)，2-双折线()
	int nConcComp1D;
	int nConcTens1D;
/*  一维骨架曲线，不同骨架曲线时参数含义不同
	受压段：21个
			自定义多段线：20个点，每个点3个数，分别是应变、应力、损伤
			规范全曲线: 无
			Rusch: fc,εc,εcu, n
			Hongnestad: fc,εc,εcu
			Mander: 无
			Qian: 无
			Kent-Park: 无
			Han: 无
	受拉段：18个
			自定义多段线：10个点，每个点3个数，分别是应变、应力、损伤
			规范全曲线: 无
			双折线：εtu
*/
	float *pConcPara1D;
	int iCHysRule;		//一维参数：旧(0-塑性损伤,1-简单，2-精细)

	//二维
	int nConcComp2DS;
	int nConcTens2DS;
	int nConcComp2DD;
	int nConcTens2DD;
	float *pConcPara2DS;
	float *pConcPara2DD;

	//钢筋、钢材
	//一维
	int iSSkeleton;		//(0-二折线，1-三折线，2-抛物线(Esmaeily-Xiao))
	int nSteelPara1D;   //pSteel1D数组的长度
/*  一维骨架曲线，不同骨架曲线时参数含义不同
		二折线: εcu,εtu,k
		三折线: εcu,εtu,k,k1
		抛物线: εcu,εtu,k,k1,k2,k3
*/
	float *pSteel1D;	//钢材、钢筋一维本构参数，每种材料6个
	int iSHysRule;		//(0-随动强化，1-Clough，2-Legeron)	
	//二维
	int nSteelPara2D;   //pSteel2D数组的长度
	float *pSteel2D;	//钢材、钢筋二维本构参数，2个点,每个点2个参数,分别是应力、塑性应变

	void GetDefaultPara();
	
	void Read2021(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);

};

class _SSG_DLLIMPEXP CMaterialCollection
{
public:
	CMaterialCollection(void);
	~CMaterialCollection(void){Clear();}

	CMaterialCollection(const CMaterialCollection &mat) 
	{
		*this=mat;
	}
	void Clear(void)
	{
		for (int i=0;i<aMaterial.GetCount();i++)
		{
			aMaterial[i].Clear();
		}
		aMaterial.RemoveAll();

	}
	CMaterialCollection & operator=(const CMaterialCollection &mat)
	{
		if(this==&mat) return *this;
		Clear();
		aMaterial.Copy(mat.aMaterial);
		return *this;
	}

	CArray<CMaterial,CMaterial&> aMaterial; 

public:
	int GetIndex(const CString &sName, int iType = MAT_CONC|MAT_REBAR|MAT_STEEL|MAT_TENDON|MAT_MASONRY| MAT_ALUMINIUM | MAT_FIBRE) const; 			//根据名字查找数组索引,找不到返回-1
	int GetIndexById(const int &id);

	int GetMatID(const CString &sName, int iType = MAT_CONC|MAT_REBAR|MAT_STEEL|MAT_TENDON | MAT_MASONRY| MAT_ALUMINIUM | MAT_FIBRE) const;
	CString GetMatName(const int &id);
	CMaterial *GetMat(const CString &sName); //根据名称查找材料地址

	float GetMatfc(CString& mat);
	float GetMatfck(CString &mat);
	float GetMatfcm(CString& mat);

	float GetMatft(CString& mat);
	float GetMatftk(CString& mat);
	float GetMatftm(CString& mat);

	float GetMatfcu(CString& mat);

	float GetMatE(CString &mat);
	float GetDensity(CString &mat);
	int GetMaterialType(CString& mat);
	float GetMatG(CString& mat);
	
	int GetConcCount(void);   //计算混凝土材料数
	int GetSteelCount(void);  //计算钢材材料数，包括钢筋			
	int GetMaxId();
	void GetNewName(CString &sName, const CString &originalName) const ;

	void Read2021(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);

	void LoadWholeLib(void);   //加载全部材料
	void LoadLibCommon();//加载常用材料
};
