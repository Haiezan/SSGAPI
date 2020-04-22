#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"


#include "ASCFile.h"
#include "UserDefine.h"


#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>
#include "Data.h"

using namespace std;

//一般连接构件截面类
class _SSG_DLLIMPEXP CDamperSection
{
public:
	//构造与析构函数
	CDamperSection(void) { Clear();}
	CDamperSection(const CDamperSection &sec)	{ nUsedCount=0; *this=sec; }
	~CDamperSection(void) { Clear(); }

	//基本数据
	int id;  //截面ID
	CString sName;  //截面名称,梁构件采用截面名称属性，一旦截面名称被改动，则根据改动前后的对应关系替换新名称
	LINK_SUBTYPE iSectionType;	//
	int iSubType; //备用
	COLORREF dwColor; //显示颜色, 便于快速寻找
	//截面特征值参数,持久数据，保存到文件，用户可以自行输入和修改，修改截面时调用GetFeatures进行计算
	enum {DAMPERSECTION_PARA=48};	//截面特征参数个数修改 邱海 2016年3月29日
	float fDamperSecPara[DAMPERSECTION_PARA];
	float fMass;
	enum {DAMPERDESIGN_PARA=28};	//设计参数
	float fDamperDesPara[DAMPERDESIGN_PARA];


	//临时数据,不保存到文件,读取截面、修改截面时、修改纤维控制参数时调用GetFibres计算
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据
	//根据截面命名规则自动获得名称
	
	CDamperSection & operator=(const CDamperSection &sec);
	void Clear(void);
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	CString sTypeName(); //得到截面类型名称 邱海 2016年6月15日
	void CheckParameter();//保护截面非线性参数 邱海 2017年1月12日
	//设计信息读写
	BOOL ReadDesignInfo(CASCFile &fin);
	void WriteDesignInfo(CASCFile &fout);
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
	int GetSecNumByType(LINK_SUBTYPE iStrucType);// 得到同类型截面的数量 邱海 2016年3月24日


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
	int GetID(const CString &sName);
	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadDefaultLib(void);  //加载系统库

};

