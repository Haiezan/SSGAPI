#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SectionBase.h"
#include "..\Common\SysPara.h"

#define gPlateSectionMethodNum 5 // 墙板加固方法的个数，板3个、墙2个
#define Sys_PlateReinForcedSectionShapeNum 5 //墙板加固方法截面形状个数


//由加固方法转为截面类型组合，提取类型应该用&运算
extern "C" _SSG_DLLIMPEXP int GetStructTypeByPlateMethod(PLATE_REINFORCED_METHOD iMethod);


//面构件截面类
class _SSG_DLLIMPEXP CPlateSectionReinforced
{
public:
	//构造与析构函数
	CPlateSectionReinforced(void)
		: id(0)
		, sName(L"")
		, iPlateMatType(PALTESECTION_REINFORCED_MAT_TYPE_CONC)
		, dwColor(0)
		, nUsedCount(0)
	{
	}
	CPlateSectionReinforced(const CPlateSectionReinforced &sec)	{nUsedCount=0; *this=sec; }
	~CPlateSectionReinforced(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称

	PALTESECTION_REINFORCED_MAT_TYPE iPlateMatType;

	COLORREF dwColor; //显示颜色, 便于快速寻找
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据

	void Clear(void);

	CPlateSectionReinforced & operator=(const CPlateSectionReinforced &sec);
	BOOL operator==(const CPlateSectionReinforced &sec) const;
	BOOL operator!=(const CPlateSectionReinforced &sec) const;

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);


	//重新计算最大尺寸fWidth,fHeight，用于绘图
	void GetMaxSize(); // bDiagram主要是用来区分 加固截面信息及配筋和其他的图
	float DrawPlateSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //绘制组合截面,返回绘制比例
	STRUCT_TYPE GetPlateStructType();
	int GetPlateSecType();
	int IsUsable(STRUCT_TYPE iType);

	CString &AutoName(void);


public:
	float fWidth, fHeight; //宽度范围,高度范围，用于轮廓显示及范围测定，未考虑转角，因为转角是构件属性，不是截面属性

	//临时传数
	float Temp_Original_B;  // 仅在加固截面对话框尺寸显示作用
	float Temp_Original_H;  // 仅在加固截面对话框的尺寸显示作用


public:
	PLATE_REINFORCED_METHOD iReinForcedMethod;	//加固方法,模板ID

	CString sConcGrade; //混凝土等级
	CString sRebarGrade; //钢筋等级
	CString sSteelModel; //钢材型号



	float fRatioB, fRatioH;  //配筋率，加固板：面筋、底筋。加固墙：B 水平向配筋,单位：百分数

	//加固方法的几何参数
	union
	{
		// 板加固方法
		struct PLATE_ENLARGED_SECTION plate_enlarge_section;
		struct PLATE_PASTE_STELL_PLATE plate_paste_steel_plate;
		struct PLATE_PASTE_FIBER plate_paste_fiber;

		// 墙加固方法
		struct WALL_ENLARGED_SECTION wall_enlarge_section;
		struct WALL_PASTE_STELL_PLATE wall_paste_steel_plate;


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

	//根据模板创建截面，清除原有数据
	BOOL CreatePlateSectionByTemplete(PLATE_REINFORCED_METHOD iMethod);
	void CreatPlateSectionReinForcedParameter(PLATE_REINFORCED_METHOD imethod);

public:
	//截面特征值参数,持久数据，保存到文件，用户可以自行输入和修改，修改截面时调用GetFeatures进行计算
	enum { BEAMSECTION_PARA = 12 };	//截面特征参数个数
	float ConcArea, SteelArea;			//混凝土面积,钢材面积(不包括用配筋率计算的钢筋，下同)
	float ConcShearArea2, SteelShearArea2;	//2方向抗剪面积
	float ConcShearArea3, SteelShearArea3;	//3方向抗剪面积
	float ConcI2, SteelI2;			//2方向转动惯量，对应力矩M2分量
	float ConcI3, SteelI3;			//3方向转动惯量，对应力矩M3分量
	float ConcJ1, SteelJ1;			//1方向转动惯量，极惯性矩，对应扭矩M1

};

//截面类集合
class _SSG_DLLIMPEXP CPlateSectionReinforcedCollection
{
public:
	CPlateSectionReinforcedCollection(void){;}
	~CPlateSectionReinforcedCollection(void){Clear();}

	CPlateSectionReinforcedCollection(const CPlateSectionReinforcedCollection &sec)
	{
		*this=sec;
	}

	CArray<CPlateSectionReinforced*,CPlateSectionReinforced*> aPlateSectionReinForcedPtr;  //板截面类指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStrucType,const CString &sName,bool bIndep=false);  //根据结构类型和截面名称获得截面ID,找不到返回-1 bIndep是否按构件独立编号
	int GetShowId(int iStrucType,int id);//根据结构类型和截面编号得到该类型独立编号，梁柱撑分别从1开始编号只用于显示
	int GetIDByShowId(int iStrucType,int id);//根据结构类型和截面独立编号得到截面ID
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	CPlateSectionReinforced *GetPlateSectionReinforced(int id) const;  //根据给定的板截面id返回截面指针
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendSection(CPlateSectionReinforced *psec);  //增加新截面，自动获取ID

	CPlateSectionReinforcedCollection & operator=(const CPlateSectionReinforcedCollection &sec)
	{
		if(this==&sec) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<sec.aPlateSectionReinForcedPtr.GetCount();i++) 
		{
			CPlateSectionReinforced *s1=new CPlateSectionReinforced(*(sec.aPlateSectionReinForcedPtr[i]));

			aPlateSectionReinForcedPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->id);  //记录最大ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	void LoadDefaultLib(void);  //加载系统库
};


struct  PLATE_SECTION_REINFORCED_METHOD_PROP_TABLE
{
	PLATE_REINFORCED_METHOD iMethod;  //加固方法模板ID
	CString sName;   //形状模板名称
	PALTESECTION_REINFORCED_MAT_TYPE iType;  //材料类型
	
};

static  PLATE_SECTION_REINFORCED_METHOD_PROP_TABLE PlateSectReinForcedTable[gPlateSectionMethodNum] =
{
	PLATE_METHOD_ENLARGED_SECTION	,	L"板增大截面法",PALTESECTION_REINFORCED_MAT_TYPE_CONC,
	PLATE_METHOD_PASTE_STELL_PLATE	,	L"板外贴钢板法",PALTESECTION_REINFORCED_MAT_TYPE_ST,
	PLATE_METHOD_PASTE_FIBER		,	L"板外贴纤维法",PALTESECTION_REINFORCED_MAT_TYPE_FIBER,

	WALL_METHOD_ENLARGED_SECTION	,	L"墙增大截面法",PALTESECTION_REINFORCED_MAT_TYPE_CONC,
	WALL_METHOD_PASTE_STELL_PLATE	,	L"墙外贴钢板法",PALTESECTION_REINFORCED_MAT_TYPE_ST,
};

struct _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA
{
	PLATE_REINFORCED_METHOD iMethod;	//加固方法
	CString sName;				//方法名称
	int nPara;					//参数个数
	CString sParaName[Sys_SubSectionParaNum]; //参数名称
};

extern "C" _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA PlateSectionReinForcedMethodParaTable[Sys_PlateReinForcedSectionShapeNum];
extern "C" _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA * FindPlateSectionReinForcedMethodPropByID(PLATE_REINFORCED_METHOD id);
