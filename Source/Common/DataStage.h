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

//һ��ʩ���׶���Ϣ
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void);
	CStage(const CStage& stage)
	{
		*this = stage;
	}
	~CStage(void);

	//��Ա����
	CStage& operator=(const CStage& stage);

	void ReadOld(CASCFile& fin);
	void Write2020(CASCFile& fout);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout);

	//��Ա����
	CString sName;

	float fDay;

	int iStoryMin;  //¥�㷶Χ,��ͬ�ļ��ز�¥�㲻���ظ�����������ز�������¥��֮�⣬������¥�㷶ΧΪ��-1��-1��
	int iStoryMax;

	std::vector<CString> aGroupAdd;   //���ڱ��μ��ز��ķ�����������
	std::vector<CString> aGroupDel;
	std::vector<CString> aGroupBcAdd;
	std::vector<CString> aGroupBcDel;
	std::vector<CString> aGroupLdAdd;	 
	std::vector<CString> aGroupLdDel;	
	std::map<CString, CString> aSecChange;//Group map change section

	static CString GetGroupKey(STAGE_ACT nAct);
	static std::map<CString, STAGE_ACT> stage_act;
};


//ʩ���׶����ݼ���
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}
	~CStageCollection(void);

	//��Ա����
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
	//��Ա����
	CArray<CStage*, CStage*> aStagePtr; //¥��ʩ���׶����飬���еĹ���Ҫ�ų�ǰ���������ù�������
};
