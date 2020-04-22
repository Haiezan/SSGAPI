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
	int iPlateMatType;		//截面材料类型代码,1-混凝土；2-单层钢板混凝土；3-双层钢板混凝土；4-纯钢板
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

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	CString sMatName();
};


