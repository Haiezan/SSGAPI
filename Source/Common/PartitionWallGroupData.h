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


struct PARTITIONWALL_GROUP_DATA
{
public:
	int nBeam;
	int *BeamIDs;
	int *BeamMats;
	int nPara;
	float *fPara;

	PARTITIONWALL_GROUP_DATA()
		: nBeam(0)
		, BeamIDs(NULL)
		, BeamMats(NULL)
		, nPara(0)
		, fPara(NULL)
	{
	}

	void InitData(int BeamNum,int DataNum)
	{		
		nBeam=BeamNum;
		if(nBeam>0)
		{
			if(BeamIDs) delete[] BeamIDs; 
			BeamIDs=new int[nBeam];
			if(BeamMats) delete[] BeamMats; 
			BeamMats=new int[nBeam];
		}

		nPara=DataNum;
		if(nPara>0)
		{
			if(fPara) delete[] fPara; 
			fPara=new float[nPara];
			memset(fPara,0,sizeof(float)*nPara);
		}
	};

	~PARTITIONWALL_GROUP_DATA()
	{			
		if(BeamIDs) delete[] BeamIDs; 
		BeamIDs=NULL;
		if(BeamMats) delete[] BeamMats; 
		BeamMats=NULL;

		if(fPara) delete[] fPara; 
		fPara=NULL;
	};

	
	//重载赋值运算符
	PARTITIONWALL_GROUP_DATA & operator=(const PARTITIONWALL_GROUP_DATA &gdata)
	{
		if(this==&gdata) return *this;


		nBeam=gdata.nBeam;
		if(BeamIDs) delete[] BeamIDs; 
		if (nBeam>0)
		{
			BeamIDs=new int[nBeam];
			for(int i=0;i<nBeam;i++) BeamIDs[i]=gdata.BeamIDs[i];
			BeamMats=new int[nBeam];
			for(int i=0;i<nBeam;i++) BeamMats[i]=gdata.BeamMats[i];
		}

		nPara=gdata.nPara;
		if(fPara) delete[] fPara; 
		if (nPara>0)
		{
			fPara=new float[nPara];
			for(int i=0;i<nPara;i++) fPara[i]=gdata.fPara[i];
		}

        return *this;
	}
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


class  _SSG_DLLIMPEXP CPartitionWallGroupSec
{
public:
	//构造与析构函数
	CPartitionWallGroupSec(void)
		: id(-1)
		, sName(L"")
		, iStyle(STYLE_SINGLE_DIAGONAL_BRACING)
		, nUsedCount(0)
	{
	}
	CPartitionWallGroupSec(const CPartitionWallGroupSec &Grp)	{nUsedCount=0; *this=Grp; }
	~CPartitionWallGroupSec(void) { Clear();}

	//基本数据
	int id;  //组ID
	CString sName;  //组名称
	PARTITIONWALL_GROUP_STYLE iStyle;	//组样式
	PARTITIONWALL_GROUP_DATA gData;//组内容
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据

	//运算符
	CPartitionWallGroupSec & operator=(const CPartitionWallGroupSec &Grp);
	//自动获得名称
	CString &AutoName(void);
	//显示组图像
	void ShowPartitionWallGroupPic(CDC *pDC,const CRect &re);
    //清除数据
	void Clear(void);
	//数据读写
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	//建模警告
	CString BuildWarning(int iStory,int iType=0);
	//数据自检
	BOOL CheckGroupData();
};

class  _SSG_DLLIMPEXP CPartitionWallGroupSecCollection
{
public:
	CPartitionWallGroupSecCollection(void){Clear();}
	~CPartitionWallGroupSecCollection(void){Clear();}

	CPartitionWallGroupSecCollection(const CPartitionWallGroupSecCollection &Grp)
	{
		*this=Grp;
	}

	CArray<CPartitionWallGroupSec*,CPartitionWallGroupSec*> aPartitionWallGroupPtr;  //消能器指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStyle,const CString &sName);  //根据结构类型和截面名称获得截面ID,找不到返回-1
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	CPartitionWallGroupSec *GetPartitionWallGroupSec(int id) const;  //根据给定的梁截面id返回截面指针
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendPartitionWallGroupSec(CPartitionWallGroupSec *pGrp);  //增加新截面，自动获取ID

	CPartitionWallGroupSecCollection & operator=(const CPartitionWallGroupSecCollection &Grp)
	{
		if(this==&Grp) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<Grp.aPartitionWallGroupPtr.GetCount();i++) 
		{
			CPartitionWallGroupSec *s1=new CPartitionWallGroupSec(*(Grp.aPartitionWallGroupPtr[i]));
			aPartitionWallGroupPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->id);  //记录最大ID
		}

		return *this;
	}

	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};
