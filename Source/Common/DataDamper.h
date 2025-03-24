#pragma once
#include "HeadDefine.h"

#include "SysPara.h"

//一般连接构件截面类
struct SEC_KELVIN
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1DmpC,fU1DmpE,fU1InvaidDatas[22];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2DmpC,fU2DmpE,fU2InvaidDatas[22];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3DmpC,fU3DmpE,fU3InvaidDatas[22];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K,fU4DmpC,fU4DmpE,fU4InvaidDatas[22];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K,fU5DmpC,fU5DmpE,fU5InvaidDatas[22];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K,fU6DmpC,fU6DmpE,fU6InvaidDatas[22];//U6方向
};
struct SEC_KELVINSPRING
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fU1Ke, fU1De, fU1K, fU1DmpC, fU1DmpE, fU1ConnectK, fU1InvaidDatas[21];//U1方向
	float fU2Linear, fU2NLinear, fU2InvaidData, fU2Ke, fU2De, fU2K, fU2DmpC, fU2DmpE, fU2ConnectK, fU2InvaidDatas[21];//U2方向
	float fU3Linear, fU3NLinear, fU3InvaidData, fU3Ke, fU3De, fU3K, fU3DmpC, fU3DmpE, fU3ConnectK, fU3InvaidDatas[21];//U3方向
	float fU4Linear, fU4NLinear, fU4InvaidData, fU4Ke, fU4De, fU4K, fU4DmpC, fU4DmpE, fU4ConnectK, fU4InvaidDatas[21];//U4方向
	float fU5Linear, fU5NLinear, fU5InvaidData, fU5Ke, fU5De, fU5K, fU5DmpC, fU5DmpE, fU5ConnectK, fU5InvaidDatas[21];//U5方向
	float fU6Linear, fU6NLinear, fU6InvaidData, fU6Ke, fU6De, fU6K, fU6DmpC, fU6DmpE, fU6ConnectK, fU6InvaidDatas[21];//U6方向
};
struct SEC_MAXWELL
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1DmpC,fU1DmpE,fU1InvaidDatas[22];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2DmpC,fU2DmpE,fU2InvaidDatas[22];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3DmpC,fU3DmpE,fU3InvaidDatas[22];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K,fU4DmpC,fU4DmpE,fU4InvaidDatas[22];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K,fU5DmpC,fU5DmpE,fU5InvaidDatas[22];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K,fU6DmpC,fU6DmpE,fU6InvaidDatas[22];//U6方向
};
struct SEC_DMPDISP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst,fU1InvaidDatas[22];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2InvaidDatas[22];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3InvaidDatas[22];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K0,fU4Fy,fU4Rst,fU4InvaidDatas[22];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K0,fU5Fy,fU5Rst,fU5InvaidDatas[22];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K0,fU6Fy,fU6Rst,fU6InvaidDatas[22];//U6方向
};
struct SEC_USERDISP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Hystype,fU1Deftype,fU1TNum,fU1CNum,fU1PointData[21];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2Hystype,fU2Deftype,fU2TNum,fU2CNum,fU2PointData[21];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3Hystype,fU3Deftype,fU3TNum,fU3CNum,fU3PointData[21];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4Hystype,fU4Deftype,fU4TNum,fU4CNum,fU4PointData[21];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5Hystype,fU5Deftype,fU5TNum,fU5CNum,fU5PointData[21];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6Hystype,fU6Deftype,fU6TNum,fU6CNum,fU6PointData[21];//U6方向
};
struct SEC_SPRING
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fKu1,fDu1,fU1InvaidDatas[25];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fKu2,fDu2,fU2InvaidDatas[25];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fKu3,fDu3,fU3InvaidDatas[25];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fKu4,fDu4,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fKu5,fDu5,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fKu6,fDu6,fU6InvaidDatas[25];//U6方向
};
struct SEC_TMD
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fKu1,fDu1,fU1InvaidDatas[25];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fKu2,fDu2,fU2InvaidDatas[25];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fKu3,fDu3,fU3InvaidDatas[25];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fKu4,fDu4,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fKu5,fDu5,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fKu6,fDu6,fU6InvaidDatas[25];//U6方向
};
struct SEC_BRB//BRB
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst;//U1方向
};
struct SEC_LRB//隔震支座
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Kc,fU1Kt,fU1InvaidDatas[23];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2InvaidDatas[22];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3InvaidDatas[22];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6方向
};
struct SEC_LRBWEN//隔震支座(Wen)
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Kc,fU1Kt,fU1InvaidDatas[23];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2Ey,fU2InvaidDatas[21];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3Ey,fU3InvaidDatas[21];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6方向
};
struct SEC_ESB
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1InvaidDatas[25];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Coef,fU2InvaidDatas[23];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Coef,fU3InvaidDatas[23];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6方向
};
struct SEC_FPS
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1InvaidDatas[25];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2Cslow,fU2Cfast,fU2CRatio,fU2Radius,fU2InvaidDatas[20];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3Cslow,fU3Cfast,fU3CRatio,fU3Radius,fU3InvaidDatas[20];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6方向
};
struct SEC_WEN
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst,fU1Ey,fU1InvaidDatas[21];//U1方向
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2Ey,fU2InvaidDatas[21];//U2方向
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3Ey,fU3InvaidDatas[21];//U3方向
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4方向
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5方向
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6方向
};
struct SEC_CABLE
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst;//U1方向
};
struct SEC_GAP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1D;//U1方向
};
struct SEC_HOOK
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1D;//U1方向
};
struct SEC_USER
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fKu1, fDu1, fU1Datas[25];//U1方向
	float fU2Linear, fU2NLinear, fU2InvaidData, fKu2, fDu2, fU2Datas[25];//U2方向
	float fU3Linear, fU3NLinear, fU3InvaidData, fKu3, fDu3, fU3Datas[25];//U3方向
	float fU4Linear, fU4NLinear, fU4InvaidData, fKu4, fDu4, fU4Datas[25];//U4方向
	float fU5Linear, fU5NLinear, fU5InvaidData, fKu5, fDu5, fU5Datas[25];//U5方向
	float fU6Linear, fU6NLinear, fU6InvaidData, fKu6, fDu6, fU6Datas[25];//U6方向
};
struct SEC_TVMD
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fU1Ke, fU1De, fU1K0, fU1DmpC, fU1DmpE, fU1Mass, fU1InvaidDatas[21];//U1方向
	float fU2Linear, fU2NLinear, fU2InvaidData, fU2Ke, fU2De, fU2K0, fU2DmpC, fU2DmpE, fU2Mass, fU2InvaidDatas[21];//U2方向
	float fU3Linear, fU3NLinear, fU3InvaidData, fU3Ke, fU3De, fU3K0, fU3DmpC, fU3DmpE, fU3Mass, fU3InvaidDatas[21];//U3方向
	float fU4Linear, fU4NLinear, fU4InvaidData, fU4Ke, fU4De, fU4K0, fU4DmpC, fU4DmpE, fU4Mass, fU4InvaidDatas[21];//U4方向
	float fU5Linear, fU5NLinear, fU5InvaidData, fU5Ke, fU5De, fU5K0, fU5DmpC, fU5DmpE, fU5Mass, fU5InvaidDatas[21];//U5方向
	float fU6Linear, fU6NLinear, fU6InvaidData, fU6Ke, fU6De, fU6K0, fU6DmpC, fU6DmpE, fU6Mass, fU6InvaidDatas[21];//U6方向
};

struct INFO_LRB
{
	float	fShearModule,fType,fDiameter,fHoleDia,fTireTh,fS1,fS2,fArea,fFlangeTh,fHeight,
		fAxialStiff,fInitStiff,fSecStiff,fYieldF,
		fEqStiffMid,fEqDmpMid,fEqStiffRare,fEqDmpRare,fEqStiffSmall,fEqDmpSmall;
};
struct INFO_ESB
{
	float	fShearModule,fDiameter,fTireTh,fS1,fS2,fArea, fCoef, fAxialStiff, fInitStiff, fDisMax;
};
struct INFO_FPS
{
	float	fType, fRaidus, fH, fDiameter, fDisMax, fCslow, fCfast, fCRatio, fArea, fAxialStiff, fInitStiff, fEqvStiff, fAxialF;
};
struct INFO_BRB
{
	float	fYieldF, fYieldDis, fInitStiff, fYieldExp, fSecStiffRatio, fUltimateF, fUltimateDis, fLen, fAxialLen;
};
struct INFO_VFD
{
	float	fDampCoef, fDampExp, fInitStiff, fDesignFLow, fDesignFUp, fDesignDisLow, fDesignDisUp, fMaxVelo, fLen;
};
struct INFO_MYD
{
	float	fYieldF, fYieldDis, fInitStiff, fYieldExp, fSecStiffRatio, fUltimateF, fUltimateDisLow, fUltimateDisUp;
};

class CASCFile;

class _SSG_DLLIMPEXP CDamperSection
{
public:
	//构造与析构函数
	CDamperSection(void)
		: id(-1)
		, sName(L"")
		, iSectionType(LINK_UNKNOWN)
		, iSubType(0)
		, fMass(0)
		, dwColor(0)
		, fDamperSecPara()
		, fDamperDesPara()
		, nUsedCount(0)
		, bPDelta(false)
		, nDamperGrade(0)
		, fDamperGrade_n()
		, fDamperGrade_t()
	{}
	CDamperSection(const CDamperSection &sec)	{ nUsedCount=0; *this=sec; }
	~CDamperSection(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称
	LINK_SUBTYPE iSectionType;	//
	int iSubType; //备用
	COLORREF dwColor; //显示颜色, 便于快速寻找
	//截面特征值参数,持久数据，保存到文件，用户可以自行输入和修改，修改截面时调用GetFeatures进行计算
	enum {DAMPERSECTION_PARA=6*Sys_nLinkData};//每个自由度 Sys_nLinkHead =30，共6*30；
	union
	{
		struct SEC_KELVIN Kelvin;
		struct SEC_MAXWELL Maxwell;
		struct SEC_DMPDISP DmpDisp;
		struct SEC_TMD Tmd;
		struct SEC_BRB Brb;
		struct SEC_LRB Isolator;
		struct SEC_ESB Esb;
		struct SEC_FPS Fps;
		struct SEC_WEN Wen;
		struct SEC_SPRING Spring;
		struct SEC_CABLE Cable;
		struct SEC_GAP Gap;
		struct SEC_HOOK Hook;
		struct SEC_LRBWEN IoslatorWen;
		struct SEC_KELVINSPRING KelvinSpring;
		struct SEC_USER User;
		struct SEC_TVMD Tvmd;
		float fDamperSecPara[DAMPERSECTION_PARA];
	};
	float fMass;
	enum {DAMPERDESIGN_PARA=28};	//设计参数
	union
	{
		struct INFO_LRB IsolatorInfo;
		struct INFO_ESB ESBInfo;
		struct INFO_FPS FPSInfo;
		struct INFO_BRB BRBInfo;
		struct INFO_MYD MYDInfo;
		struct INFO_VFD	VFDInfo;
		float fDamperDesPara[DAMPERDESIGN_PARA];
	};
	bool bPDelta;
	int nDamperGrade;//阻尼器性能评价等级
	float fDamperGrade_n[6];//阻尼器轴向性能等级参数
	float fDamperGrade_t[6];//阻尼器切向性能等级参数

	//临时数据,不保存到文件,读取截面、修改截面时、修改纤维控制参数时调用GetFibres计算
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据
	//根据截面命名规则自动获得名称
	
	CDamperSection & operator=(const CDamperSection &sec);
	void Clear(void);
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	CString sTypeName()const; //得到截面类型名称 邱海 2016年6月15日
	//设计信息读写
	BOOL ReadDesignInfo(CASCFile &fin);
	void WriteDesignInfo(CASCFile &fout);
	void WriteDesignInfo2020(CASCFile &fout);
	//
	void GenerateDamperGradeOld();
	int GenerateDamperGrade(float* fDamperGrade_n = NULL, float* fDamperGrade_t = NULL);
};


//截面类集合
class _SSG_DLLIMPEXP CDamperSectionCollection
{
public:
	CDamperSectionCollection(void){;}
	~CDamperSectionCollection(void){Clear();}

	CDamperSectionCollection(const CDamperSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CDamperSection*,CDamperSection*> aDamperSectionPtr;  //梁截面类指针
	int iMaxID;  //当前用到的最大ID

	CDamperSection *GetDamperSection(int id) const;  //根据给定的梁截面id返回截面指针
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendSection(CDamperSection *psec);  //增加新截面，自动获取ID
	int GetSecNumByType(LINK_SUBTYPE iStrucType)const ;// 得到同类型截面的数量 邱海 2016年3月24日


	CDamperSectionCollection & operator=(const CDamperSectionCollection &sec)
	{
		if(this==&sec) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<sec.aDamperSectionPtr.GetCount();i++) 
		{
			CDamperSection *s1=new CDamperSection(*(sec.aDamperSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aDamperSectionPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->id);  //记录最大ID
		}

		return *this;
	}
	int GetID(const CString &sName) const;
	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	void LoadDefaultLib(void);  //加载系统库
	BOOL ExportSecProperty(int iType,CArray<int,int>&SecArr,CString *&pContents,int &nRows,int &nCols);
};
