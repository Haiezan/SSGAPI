#pragma once
#include "HeadDefine.h"

class CASCFile;

//һ��ʩ���׶���Ϣ
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void) {iStoryMin=iStoryMax=-1;}
	~CStage(void) {aGroupName.RemoveAll();}

	//��Ա����
	int iStoryMin;  //¥�㷶Χ,��ͬ�ļ��ز�¥�㲻���ظ�����������ز�������¥��֮�⣬������¥�㷶ΧΪ��-1��-1��
	int iStoryMax;
	CArray<CString,CString&> aGroupName;   //���ڱ��μ��ز��ķ�����������

	//��Ա����
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


//ʩ���׶����ݼ���
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}

	~CStageCollection(void);
	//��Ա����
	CArray<CStage*,CStage*> aStagePtr; //¥��ʩ���׶����飬���еĹ���Ҫ�ų�ǰ���������ù�������

	//��Ա����

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
