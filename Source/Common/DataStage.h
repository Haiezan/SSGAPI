#pragma once
#include "HeadDefine.h"
#include <map>
#include <vector>

enum STAGE_ACT
{
	ADD_GRP,
	DEL_GRP,
	ADD_GBC,
	DEL_GBC,
	ADD_GLD,
	DEL_GLD,
	REP_SEC,
	ACT_NUM,
};

class CASCFile;

//一个施工阶段信息
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void);
	CStage(const CStage& stage)
	{
		*this = stage;
	}
	~CStage(void);

	//成员函数
	CStage& operator=(const CStage& stage);

	void ReadOld(CASCFile& fin);
	void Write2020(CASCFile& fout);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout);

	//成员变量
	CString sName;

	float fDay;

	int iStoryMin;  //楼层范围,不同的加载步楼层不能重复，如果本加载步独立于楼层之外，可以设楼层范围为（-1，-1）
	int iStoryMax;

	std::vector<CString> aGroupAdd;   //属于本次加载步的分组名称数组
	std::vector<CString> aGroupDel;
	std::vector<CString> aGroupBcAdd;
	std::vector<CString> aGroupBcDel;
	std::vector<CString> aGroupLdAdd;	 
	std::vector<CString> aGroupLdDel;	
	std::map<CString, CString> aSecChange;//Group map change section

	static CString GetGroupKey(STAGE_ACT nAct);
	static std::map<CString, STAGE_ACT> stage_act;
};


//施工阶段数据集合
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}
	~CStageCollection(void);

	//成员函数
	int GetCount() const { return aStagePtr.GetCount(); }

	CStage* operator[](int i)const { return aStagePtr[i]; }

	int Add(CStage* stage) { return aStagePtr.Add(stage); }
	void InsertAt(int iPos, CStage* stage) { aStagePtr.InsertAt(iPos, stage); }
	void SetSize(int nSize) 
	{ 
		for (size_t i = nSize, nMax = aStagePtr.GetCount(); i < nMax; i++)
		{
			delete aStagePtr[i];
		}
		aStagePtr.SetSize(nSize);
	}

	void RemoveAt(int i)
	{
		delete aStagePtr[i];
		aStagePtr.RemoveAt(i);
	}

	void Clear(void) ;

	CStageCollection& operator=(const CStageCollection& stage);

	void Read(CASCFile& fin, bool bNew = true);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);

private:
	//成员变量
	CArray<CStage*, CStage*> aStagePtr; //楼层施工阶段数组，其中的构件要排除前面其他组用过的数据
};
