#pragma once
#include "HeadDefine.h"

#include "SysPara.h"
#include "..\Common\DataDamper.h"


class CASCFile;

class _SSG_DLLIMPEXP CSemiRigidSection : public CDamperSection
{
public:
	//构造与析构函数
	CSemiRigidSection(void):bReletiveStiffness(false){}
	CSemiRigidSection(const CSemiRigidSection& sec) { nUsedCount = 0; *this = sec; }
	~CSemiRigidSection(void) { Clear(); }

	int bReletiveStiffness; // 0 表示相对刚度 1表示绝对刚度
	CSemiRigidSection& operator=(const CSemiRigidSection& sec) ;

	void Clear(void);
	BOOL Read(CASCFile& fin);
	void Write(CASCFile& fout);

};


//截面类集合
class _SSG_DLLIMPEXP CSemiRigidSectionCollection
{
public:
	CSemiRigidSectionCollection(void) { ; }
	~CSemiRigidSectionCollection(void) { Clear(); }

	CSemiRigidSectionCollection(const CSemiRigidSectionCollection& sec)
	{
		*this = sec;
	}

	CArray<CSemiRigidSection*, CSemiRigidSection*> aSemiRigidSectionPtr;  //梁截面类指针
	int iMaxID;  //当前用到的最大ID

	CSemiRigidSection* GetSemiRigidSection(int id) const;  //根据给定的梁截面id返回截面指针
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	int* CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendSection(CSemiRigidSection* psec);  //增加新截面，自动获取ID
	int GetSecNumByType(LINK_SUBTYPE iStrucType);// 得到同类型截面的数量 邱海 2016年3月24日


	CSemiRigidSectionCollection& operator=(const CSemiRigidSectionCollection& sec)
	{
		if (this == &sec) return *this; //自身赋值时直接返回

		Clear();
		for (int i = 0; i < sec.aSemiRigidSectionPtr.GetCount(); i++)
		{
			CSemiRigidSection* s1 = new CSemiRigidSection(*(sec.aSemiRigidSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aSemiRigidSectionPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID = max(iMaxID, s1->id);  //记录最大ID
		}

		return *this;
	}
	int GetID(const CString& sName);
	void Clear();
	void Read(CASCFile& fin);
	void Write(CASCFile& fout);
	void Write2020(CASCFile& fout);
	void LoadDefaultLib(void);  //加载系统库
	BOOL ExportSecProperty(int iType, CArray<int, int>& SecArr, CString*& pContents, int& nRows, int& nCols);
};
