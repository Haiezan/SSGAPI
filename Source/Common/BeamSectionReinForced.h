#pragma once

#include "HeadDefine.h"
#include "..\Common\SysPara.h"
#include "ASCFile.h"
#include "..\Common\XYSect.h"
#include <afxtempl.h>
#include <afxwin.h>


////预定义的截面形状个数

#define gSectionMethodNum 10 // 加固方法的个数，梁柱各5个
#define Sys_ReinForcedSubSectionShapeNum 10 //加固方法的子截面形状个数



//由加固方法转为截面类型组合，提取类型应该用&运算
extern "C" _SSG_DLLIMPEXP int GetStructTypeByMethod(REINFORCED_METHOD iReinForcedType);




//线构件截面类 加固
class _SSG_DLLIMPEXP CBeamSectionReinForced
{
public:
	//构造与析构函数
	CBeamSectionReinForced(void) {
		pConcFibreBuf = pSteelFibreBuf = NULL;
		pConcFibre2Buf = NULL;
		Clear();
	}


	CBeamSectionReinForced(const CBeamSectionReinForced& sec)
	{
		pConcFibreBuf = pSteelFibreBuf = NULL; nUsedCount = 0;
		pConcFibre2Buf = NULL;
		*this = sec;
	}

	~CBeamSectionReinForced(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称
	SECTION_MAT_TYPE iMatType;		//截面材料类型代码
	REINFORCED_METHOD iReinForcedMethod;	//加固方法,模板ID
	//CArray<CSubSectionReinForced,CSubSectionReinForced&> aSubSecReinForced; //子截面数组


	COLORREF dwColor; //显示颜色, 便于快速寻找



	//截面特征值参数,持久数据，保存到文件，用户可以自行输入和修改，修改截面时调用GetFeatures进行计算
	enum { BEAMSECTION_PARA = 12 };	//截面特征参数个数
	float ConcArea, SteelArea;			//混凝土面积,钢材面积(不包括用配筋率计算的钢筋，下同)
	float ConcShearArea2, SteelShearArea2;	//2方向抗剪面积
	float ConcShearArea3, SteelShearArea3;	//3方向抗剪面积
	float ConcI2, SteelI2;			//2方向转动惯量，对应力矩M2分量
	float ConcI3, SteelI3;			//3方向转动惯量，对应力矩M3分量
	float ConcJ1, SteelJ1;			//1方向转动惯量，极惯性矩，对应扭矩M1

	//临时数据,不保存到文件,读取截面、修改截面时、修改纤维控制参数时调用GetFibres计算
	float fWidth, fHeight; //宽度范围,高度范围，用于轮廓显示及范围测定，未考虑转角，因为转角是构件属性，不是截面属性
	int nConcFibre, nStructSteelFibre;  //混凝土纤维数量，钢纤维数量（不包括钢筋）
	BEAM_FIBRE_GEO* pConcFibreBuf, * pSteelFibreBuf;   //混凝土纤维数组，钢纤维数组（不包括分布钢筋，但包括边缘构件的钢筋柱）

	BEAM_FIBRE_GEO* pConcFibre2Buf;		//暂时使用这种方式。

	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据

	//根据模板创建截面，清除原有数据
	BOOL CreateSectionByTemplete(REINFORCED_METHOD iMethod);

	//计算截面特征值参数，修改后进行调用
	void GetFeaturesReinForced(void);


	//重新计算最大尺寸fWidth,fHeight，用于绘图
	void GetMaxSize(BOOL bDiagram); // bDiagram主要是用来区分 加固截面信息及配筋和其他的图

	//根据截面命名规则自动获得名称
	CString& AutoName(void);


	//判断是不是某类型结构的可用截面
	int IsUsable(STRUCT_TYPE iType);
	STRUCT_TYPE GetType(); //得到该截面的结构类型

	CBeamSectionReinForced& operator=(const CBeamSectionReinForced& sec);
	BOOL operator==(const CBeamSectionReinForced& sec) const;
	BOOL operator!=(const CBeamSectionReinForced& sec) const;

	void Clear(void);

	float DrawSection(CDC* pDC, BOOL bGrid, BOOL bFibre, const CRect& re, BOOL bDiagram);  //绘制组合截面,返回绘制比例

	BOOL Read(CASCFile& fin);
	void Write(CASCFile& fout);


	float Original_p2; // 加固截面的坐标
	float Original_p3;  // 加固截面的坐标

	void GenerateReinforceSec(CBeamSection*& pSec, const CBeamSection* pSec0);
	BOOL bReinforceConc();
	BOOL bReinforceFiber();
	float GetSteelArea(float& areaB, float& areaT);
	float GetFiberThick(float& fwide, float& Dis);
	float GetConcArea(const CBeamSection* pSec);
	float GetBeamRebarArea(const CBeamSection* pSec0);
	float GetPillarRebarArea(const CBeamSection* pSec0, float& fCorner);//fCorner--角筋面积（单根）,单位：m^2，若无法确定角筋，给0


public:
	//成员变量--------------------
	SUBSECTION_REINFORCED_TYPE iMethod;	//加固方法类型
	SUBSECTION_MAT_TYPE iSubMatType; //子截面材料类型（混凝土或型钢等单一材料,不能是混合材料）

	CString sConcGrade; //混凝土等级
	CString sRebarGrade; //钢筋等级
	CString sSteelModel; //钢材型号
	float fRatioB, fRatioH;  //配筋率，加固梁：面筋、底筋。加固柱和斜撑：B、H方向的单边配筋率（包含角筋）,单位：百分数
	float fStirArea; // 箍筋配筋率


	//加固方法的几何参数
	union
	{
		// 梁加固方法
		struct BEAM_ENLARGED_SECTION beam_enlarge_section;
		struct BEAM_DISPLACEMENT_CONCRETE beam_displacement_concrete;
		struct BEAM_WRAPPED_SECTION_STEEL beam_wrapped_section_steel;
		struct BEAM_PASTE_STELL_PLATE beam_paste_steel_plate;
		struct BEAM_PASTE_FIBER beam_paste_fiber;

		// 柱加固方法
		struct PILLAR_ENLARGED_SECTION pillar_enlarge_section;
		struct PILLAR_DISPLACEMENT_CONCRETE pillar_displacement_concrete;
		struct PILLAR_WRAPPED_SECTION_STEEL pillar_wrapped_section_steel;
		struct PILLAR_PASTE_STELL_PLATE pillar_paste_steel_plate;
		struct PILLAR_PASTE_FIBER pillar_paste_fiber;

		float fValue[Sys_SubSectionParaNum];  //单位：米
	};
	int nValue;		//2020版本 增加 nPara数
	float p2, p3;	//子截面2和3方向的偏心距（m），子截面形心到组合截面局部坐标原点的距离，组合截面坐标原点选在外包矩形的中心点

	float angle;

	//临时传数
	float m_Area;
	float m_shearArea2;
	float m_shearArea3;
	float m_I2;
	float m_I3;
	float m_J1;



	//计算外包矩形尺寸
	void GetRectSize(float& fWidth, float& fHeight);
	float Area(void); //计算截面面积
	float ShearArea2(void); //计算2方向有效剪切面积
	float ShearArea3(void); //计算3方向有效剪切面积

	void CalcI2I3(float& I2, float& I3);
	float J1(void);  //扭转惯性矩，相对于组合截面的局部坐标原点，故需要单独考虑偏心距

	void RotateProperty(float Iy, float Iz, float Iyz, float alpha, float& Iy1, float& Iz1, float& Iyz1);


	float Original_B;  // 截面初始化的尺寸
	float Original_H;  // 截面初始化的尺寸

	//临时传数
	float Temp_Original_B;  // 仅在加固截面对话框尺寸显示作用
	float Temp_Original_H;  // 仅在加固截面对话框的尺寸显示作用

	void CreatBeamSectionReinForcedParameter(SUBSECTION_REINFORCED_TYPE imethod, SUBSECTION_MAT_TYPE isectype);

};


//截面类集合
class _SSG_DLLIMPEXP CSectionCollectionReinForced
{
public:
	CSectionCollectionReinForced(void) { ; }
	~CSectionCollectionReinForced(void) { Clear(); }


	CSectionCollectionReinForced(const CSectionCollectionReinForced& sec)
	{
		*this = sec;
	}

	CArray<CBeamSectionReinForced*, CBeamSectionReinForced*> aBeamSectionReinForcedPtr;  //梁截面类指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStrucType, const CString& sName, bool bIndep = false);  //根据结构类型和截面名称获得截面ID,找不到返回-1 bIndep是否按构件独立编号
	int GetShowId(int iStrucType, int id);//根据结构类型和截面编号得到该类型独立编号，梁柱撑分别从1开始编号只用于显示
	int GetIDByShowId(int iStrucType, int id);//根据结构类型和截面独立编号得到截面ID
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	CBeamSectionReinForced* GetBeamSectionReinForced(int id) const;  //根据给定的梁截面id返回截面指针

	int* CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	int GetSecID(const CBeamSectionReinForced* pSec);//查找截面ID 找不到返回-1

	void AppendSection(CBeamSectionReinForced* psec);  //增加新截面，自动获取ID


	CSectionCollectionReinForced& operator=(const CSectionCollectionReinForced& sec)
	{
		if (this == &sec) return *this; //自身赋值时直接返回

		Clear();
		for (int i = 0; i < sec.aBeamSectionReinForcedPtr.GetCount(); i++)
		{
			CBeamSectionReinForced* s1 = new CBeamSectionReinForced(*(sec.aBeamSectionReinForcedPtr[i]));
			aBeamSectionReinForcedPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID = max(iMaxID, s1->id);  //记录最大ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile& fin);
	void Write(CASCFile& fout);

};

//加固截面形状属性表
struct  SECTION_METHOD_PROP_TABLE
{
	REINFORCED_METHOD iMethod;  //加固方法模板ID
	CString sName;   //形状模板名称
	SECTION_MAT_TYPE iType;  //材料类型
	SUBSECTION_SHAPE subshape[2]; //对应的子截面编号
};

static SECTION_METHOD_PROP_TABLE gSectionMethodTable[gSectionMethodNum] =
{
	BEAM_METHOD_ENLARGED_SECTION	,	L"梁增大截面法",SECTION_MAT_TYPE_RC,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_DISPLACEMENT_CONCRETE,	L"梁置换混凝土法",SECTION_MAT_TYPE_RC,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_WRAPPED_SECTION_STEEL,	L"梁外包型钢法",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_PASTE_STELL_PLATE	,	L"梁外贴钢板法",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_PASTE_FIBER	,			L"梁外贴纤维法",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,

	PILLAR_METHOD_ENLARGED_SECTION		,	L"柱增大截面法",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_DISPLACEMENT_CONCRETE,	L"柱置换混凝土法",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_WRAPPED_SECTION_STEEL,	L"柱外包型钢法",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_PASTE_STELL_PLATE	,		L"柱外贴钢板法",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_PASTE_FIBER,				L"柱外贴纤维法",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN
};

struct _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE
{
	SUBSECTION_REINFORCED_TYPE iMethod;	//加固方法
	CString sName;				//方法名称
	int nPara;					//参数个数
	CString sParaName[Sys_SubSectionParaNum]; //参数名称
};


extern "C" _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE aSubMethodPropTable[Sys_ReinForcedSubSectionShapeNum];
extern "C" _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE * FindMethodPropByID(SUBSECTION_REINFORCED_TYPE id);




