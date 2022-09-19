#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SectionBase.h"

//面构件截面类
class _SSG_DLLIMPEXP CPlateSection
{
public:
	//构造与析构函数
	CPlateSection(void) {pLayers=NULL; Clear();}
	CPlateSection(const CPlateSection &sec)	{ pLayers=NULL; nUsedCount=0; *this=sec; }
	~CPlateSection(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称
	int iStructType;  //构件类型：1-板；2-墙
	PALTESECTION_MAT_TYPE iPlateMatType;		//截面材料类型代码,1-混凝土；2-单层钢板混凝土；3-双层钢板混凝土；4-纯钢板
	int nLayers; //层数量
	struct LAYER_INFO
	{
		float fLayerThick;				//层厚度，单位：米
		SUBSECTION_MAT_TYPE iLayerMatType;	//层材料
		float fOffset;					//层中心位置,单位：米
	} *pLayers; //层信息
	
	float fThick; //总厚度，由各层累加得到，读入及修改要更新
	COLORREF dwColor; //显示颜色, 便于快速寻找
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据

	void Clear(void);
	//void GetThick(void);//计算厚度
	CPlateSection & operator=(const CPlateSection &sec);
	BOOL operator==(const CPlateSection &sec) const;
	BOOL operator!=(const CPlateSection &sec) const;

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	CString sMatName();
	BOOL CheckPlateSect();//检查截面类型及层数是否对应
	float DrawPlateSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //绘制组合截面,返回绘制比例
	BOOL GetPlateSec(SECTION_MAT_TYPE &secType,float &fThickness,int &nSteelLayer,float &fSteelThick,float &fConcThick);
	int GetPlateStructType();
	int GetPlateSecType();

	//检查截面参数是否正常
	BOOL CheckSectParameter(float fMin=0.f);
	//根据数据截面类型初始化截面数据
	BOOL SetSectParameter(float fSteelThk);
	//根据截面命名规则自动获得名称
	CString &AutoName(void);
	//得到截面厚度
	float GetSecThickness(SUBSECTION_MAT_TYPE iType);
};

//截面类集合
class _SSG_DLLIMPEXP CPlateSectionCollection
{
public:
	CPlateSectionCollection(void){;}
	~CPlateSectionCollection(void){Clear();}

	CPlateSectionCollection(const CPlateSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CPlateSection*,CPlateSection*> aPlateSectionPtr;  //板截面类指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStrucType,const CString &sName,bool bIndep=false);  //根据结构类型和截面名称获得截面ID,找不到返回-1 bIndep是否按构件独立编号
	int GetShowId(int iStrucType,int id);//根据结构类型和截面编号得到该类型独立编号，梁柱撑分别从1开始编号只用于显示
	int GetIDByShowId(int iStrucType,int id);//根据结构类型和截面独立编号得到截面ID
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	CPlateSection *GetPlateSection(int id) const;  //根据给定的板截面id返回截面指针
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendSection(CPlateSection *psec);  //增加新截面，自动获取ID

	CPlateSectionCollection & operator=(const CPlateSectionCollection &sec)
	{
		if(this==&sec) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<sec.aPlateSectionPtr.GetCount();i++) 
		{
			CPlateSection *s1=new CPlateSection(*(sec.aPlateSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aPlateSectionPtr.Add(s1);  //这里不调用AppendSection，不改变ID
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



