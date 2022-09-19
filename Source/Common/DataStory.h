#pragma once
#include "HeadDefine.h"
#include "SysPara.h"

#define NUM_STORY_PROP 13  //楼层属性参数个数

class CASCFile;

//楼层类
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

	float fHeight; //层高
	float zTop;  //屋顶标高
	int iStoryType;  //1-普通楼层；2-空间楼层

	float fStifCenterX;
	float fStifCenterY;
	float fMassCenterX;
	float fMassCenterY;
	//边缘构件类型
	//bit0-2: 按值定义，不按位，0--约束边缘构件，1-底部加强之内的构造边缘构件，2-底部加强之上的构造边缘构件
	//bit8-15:  按值定义，不按位，抗震构造等级,0-- 特一级，1 -- 一级(9度)，2 -- 一级(8度)，3 -- 二级， 4 -- 三级，5 -- 四级
	////bit3-5: 按值定义，不按位，抗震等级 0-特一级，1-一级，2 -- 二级， 3-- 三级,4- 四级，5-不抗震
	int iStoryProp;

	//楼层构件参数,作为附属数据读写,共9种构件
	float fPara[16][Sys_StructTypeNum];  //16个分量与STRUCT_PROPERTY1顺序保持一致(从3开始),0-12有用，数据单位与界面一致
	CString sRebar[Sys_StructTypeNum],sStirrup[Sys_StructTypeNum],sConc[Sys_StructTypeNum],sSteel[Sys_StructTypeNum]; //分量与g_StructKeyword一致
	float zBottom(void) const {return zTop-fHeight;} //层底标高

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

	//邱海注释楼层抗震等级 2017年10月9日
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

	void Init(void); //设置默认值

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
	//设计信息读写
	virtual void ReadDesignInfo(CASCFile &fin);   
	virtual void WriteDesignInfo(CASCFile &fout,int idf);
	virtual void WriteDesignInfo2020(CASCFile &fout,int idf);

protected:
	//楼层控制参数
	CString sName;  //楼层标记
	CString sGroup; //分组名称
};
