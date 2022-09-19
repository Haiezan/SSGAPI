#pragma once
#include "HeadDefine.h"
#include "SysPara.h"

#define NUM_STORY_PROP 13  //¥�����Բ�������

class CASCFile;

//¥����
class _SSG_DLLIMPEXP CStory
{
public:
	CStory(void)
	{
		Init();
	}

	~CStory(void){;}

	CStory(CStory &story)
	{
		*this=story;
	}

	float fHeight; //���
	float zTop;  //�ݶ����
	int iStoryType;  //1-��ͨ¥�㣻2-�ռ�¥��

	float fStifCenterX;
	float fStifCenterY;
	float fMassCenterX;
	float fMassCenterY;
	//��Ե��������
	//bit0-2: ��ֵ���壬����λ��0--Լ����Ե������1-�ײ���ǿ֮�ڵĹ����Ե������2-�ײ���ǿ֮�ϵĹ����Ե����
	//bit8-15:  ��ֵ���壬����λ��������ȼ�,0-- ��һ����1 -- һ��(9��)��2 -- һ��(8��)��3 -- ������ 4 -- ������5 -- �ļ�
	////bit3-5: ��ֵ���壬����λ������ȼ� 0-��һ����1-һ����2 -- ������ 3-- ����,4- �ļ���5-������
	int iStoryProp;

	//¥�㹹������,��Ϊ�������ݶ�д,��9�ֹ���
	float fPara[16][Sys_StructTypeNum];  //16��������STRUCT_PROPERTY1˳�򱣳�һ��(��3��ʼ),0-12���ã����ݵ�λ�����һ��
	CString sRebar[Sys_StructTypeNum],sStirrup[Sys_StructTypeNum],sConc[Sys_StructTypeNum],sSteel[Sys_StructTypeNum]; //������g_StructKeywordһ��
	float zBottom(void) const {return zTop-fHeight;} //��ױ��

	int GetEarthQuakeClass(void)
	{
		int k=(iStoryProp>>8)&0xff;
		//if(k==0xff) k=-1;
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		return k;
	};
	void SetEarthQuakeClass(int k)
	{
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		//if(k==-1) k=0xff;
		k=k<<8;
		iStoryProp &= 0xffff00ff;
		iStoryProp |= k;
	};

	//��ע��¥�㿹��ȼ� 2017��10��9��
	//int GetEarthQuakeGrade(void)
	//{
	//	int k=(iStoryProp>>3)&0x1f;
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	return k;
	//};
	//void SetEarthQuakeGrade(int k)
	//{
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	k=k<<3;
	//	iStoryProp &= 0xffffffe3;
	//	iStoryProp |= k;
	//};

	int GetEdgeType(void)
	{
		int k=iStoryProp&0x07;
		if(k<0) k=0;
		if(k>2) k=2;
		return k;
	}

	void SetEdgeType(int k)
	{
		iStoryProp &= 0xfffffff8;
		iStoryProp |= k;
		if(k<0) k=0;
		if(k>2) k=2;
	}

	void Init(void); //����Ĭ��ֵ

	void SetName(CString sname)
	{
		sname.Trim(); 
		if(sname==L"") 
		{
			AfxMessageBox(L"Story name is empty.");
			return;
		}
		sName=sname;
	}
	CString GetName(void) const {return sName;}
	void SetGroup(CString sgroup)
	{
		sgroup.Trim();
		if(sgroup==L"") 
		{
			AfxMessageBox(L"Group name is empty.");
			return;
		}
		sGroup=sgroup;
	}
	CString GetGroup(void) const {return sGroup;}

	CStory & operator=(const CStory &story)
	{
		if(this==&story) return *this;
		sName=story.sName;
		sGroup=story.sGroup;
		fHeight=story.fHeight;
		iStoryType=story.iStoryType;
		zTop=story.zTop;
		iStoryProp=story.iStoryProp;
		fStifCenterX		=story.fStifCenterX		;
		fStifCenterY		=story.fStifCenterY		;
		fMassCenterX	=story.fMassCenterX	;
		fMassCenterY	=story.fMassCenterY	;
		for(int j=0;j<Sys_StructTypeNum;j++) 
		{
			for(int i=0;i<16;i++) 
			{
				fPara[i][j]=story.fPara[i][j];
			}
			sRebar[j]=story.sRebar[j];
			sStirrup[j]=story.sStirrup[j];
			sConc[j] =story.sConc[j] ;
			sSteel[j]=story.sSteel[j];
		}
		return *this;
	}

	virtual void Read(CASCFile &fin);   
	virtual void Write(CASCFile &fout,int idf);
	virtual void Write2020(CASCFile &fout,int idf);
	//�����Ϣ��д
	virtual void ReadDesignInfo(CASCFile &fin);   
	virtual void WriteDesignInfo(CASCFile &fout,int idf);
	virtual void WriteDesignInfo2020(CASCFile &fout,int idf);

protected:
	//¥����Ʋ���
	CString sName;  //¥����
	CString sGroup; //��������
};
