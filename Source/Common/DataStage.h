#pragma once
#include "HeadDefine.h"

class CASCFile;

//一个施工阶段信息
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void) {iStoryMin=iStoryMax=-1;}
	~CStage(void) {aGroupName.RemoveAll();}

	//成员变量
	int iStoryMin;  //楼层范围,不同的加载步楼层不能重复，如果本加载步独立于楼层之外，可以设楼层范围为（-1，-1）
	int iStoryMax;
	CArray<CString,CString&> aGroupName;   //属于本次加载步的分组名称数组

	//成员函数
	CStage & operator=(const CStage &stage)
	{
		if(this==&stage) return *this;
		iStoryMin=stage.iStoryMin;
		iStoryMax=stage.iStoryMax;
		aGroupName.RemoveAll();
		aGroupName.Copy(stage.aGroupName);
		//for(int i=0;i<stage.aGroupName.GetCount();i++)
		//{
		//	CString str=stage.aGroupName[i];
		//	aGroupName.Add(str);
		//}
		return *this;
	}


	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
};


//施工阶段数据集合
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}

	~CStageCollection(void);
	//成员变量
	CArray<CStage*,CStage*> aStagePtr; //楼层施工阶段数组，其中的构件要排除前面其他组用过的数据

	//成员函数

	void Clear(void) ;

	CStageCollection & operator=(const CStageCollection &stage)
	{
		if(this==&stage) return *this;

		Clear();

		for(int i=0;i<stage.aStagePtr.GetCount();i++)
		{
			CStage *pstage=new CStage;
			*pstage=*(stage.aStagePtr[i]);
			aStagePtr.Add(pstage);
		}

		return *this;
	}

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
};
