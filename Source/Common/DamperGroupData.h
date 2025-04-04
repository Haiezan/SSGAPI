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


struct GROUP_DATA
{
public:
	int nLink;
	int *LinkIDs;
	int nBeam;
	int *BeamIDs;
	int *BeamMats;
	int nPlate;
	CPlateStruc *Plates;
	int nPara;
	float *fPara;

	GROUP_DATA()
		: nLink(0)
		, LinkIDs(NULL)
		, nBeam(0)
		, BeamIDs(NULL)
		, BeamMats(NULL)
		, nPlate(0)
		, Plates(NULL)
		, nPara(0)
		, fPara(NULL)
	{
	}

	void InitData(int LinkNum,int BeamNum,int DataNum,int PlateNum=0)
	{		
		nLink=LinkNum;
		if(nLink>0)
		{
			if(LinkIDs) delete[] LinkIDs; 
			LinkIDs=new int[nLink];
		}
		nBeam=BeamNum;
		if(nBeam>0)
		{
			if(BeamIDs) delete[] BeamIDs; 
			BeamIDs=new int[nBeam];
			if(BeamMats) delete[] BeamMats; 
			BeamMats=new int[nBeam];
		}
		nPlate=PlateNum;
		if(nPlate>0)
		{
			if(Plates) delete[] Plates; 
			Plates=new CPlateStruc[nPlate];
		}
		nPara=DataNum;
		if(nPara>0)
		{
			if(fPara) delete[] fPara; 
			fPara=new float[nPara];
			memset(fPara,0,sizeof(float)*nPara);
		}
	};

	~GROUP_DATA()
	{			
		if(LinkIDs) delete[] LinkIDs; 
		LinkIDs=NULL;

		if(BeamIDs) delete[] BeamIDs; 
		BeamIDs=NULL;
		if(BeamMats)delete[] BeamMats;
		BeamMats=NULL;

		if(Plates) delete[] Plates; 
		Plates=NULL;

		if(fPara) delete[] fPara; 
		fPara=NULL;
	};

	
	//重载赋值运算符
	GROUP_DATA & operator=(const GROUP_DATA &gdata)
	{
		if(this==&gdata) return *this;

		nLink=gdata.nLink;
		if(LinkIDs) delete[] LinkIDs; 
		if (nLink>0)
		{
			LinkIDs=new int[nLink];
			for(int i=0;i<nLink;i++) LinkIDs[i]=gdata.LinkIDs[i];
		}

		nBeam=gdata.nBeam;
		if(BeamIDs) delete[] BeamIDs; 
		if (BeamMats) delete[] BeamMats; //20250304 内存泄漏
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

		nPlate=gdata.nPlate;
		if(Plates) delete[] Plates; 
		if (nPlate>0)
		{
			Plates=new CPlateStruc[nPlate];
			for(int i=0;i<nPlate;i++) Plates[i]=gdata.Plates[i];
		}

        return *this;
	}
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
};


class  _SSG_DLLIMPEXP CDamperGroupSec
{
public:
	//构造与析构函数
	CDamperGroupSec(void)
		: id(-1)
		, sName(L"")
		, iStyle(STYLE_BEAM)
		, nUsedCount(0)
	{
	}
	CDamperGroupSec(const CDamperGroupSec &Grp)	{nUsedCount=0; *this=Grp; }
	~CDamperGroupSec(void) { Clear();}

	//基本数据
	int id;  //组ID
	CString sName;  //组名称
	GROUP_STYLE iStyle;	//组样式
	GROUP_DATA gData;//组内容
	int nUsedCount;  //被构件使用的次数，一定要先计算再使用,临时数据

	//运算符
	CDamperGroupSec & operator=(const CDamperGroupSec &Grp);
	//自动获得名称
	CString &AutoName(void);
	//获得样式名称
	CString GetStyleName(void);
	//显示组图像
	void ShowDamperGroupPic(CDC *pDC,const CRect &re,bool modify = false);
    //清除数据
	void Clear(void);
	//数据读写
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	//建模警告
	CString BuildWarning(int iStory,int iType=0);
	//数据自检
	BOOL CheckGroupData();
};

class  _SSG_DLLIMPEXP CDamperGroupSecCollection
{
public:
	CDamperGroupSecCollection(void){Clear();}
	~CDamperGroupSecCollection(void){Clear();}

	CDamperGroupSecCollection(const CDamperGroupSecCollection &Grp)
	{
		*this=Grp;
	}

	CArray<CDamperGroupSec*,CDamperGroupSec*> aDamperGroupPtr;  //消能器指针
	int iMaxID;  //当前用到的最大ID

	int GetID(int iStyle,const CString &sName);  //根据结构类型和截面名称获得截面ID,找不到返回-1
	int GetIndex(int id) const;  //根据给定的梁截面id返回索引,找不到返回-1
	CDamperGroupSec *GetDamperGroupSec(int id) const;  //根据给定的梁截面id返回截面指针
	int *CreateIndex(void);  //创建ID-->序号的索引数组，调用程序需要删除它，数组长度为iMaxID+1
	void AppendDamperGroupSec(CDamperGroupSec *pGrp);  //增加新截面，自动获取ID

	CDamperGroupSecCollection & operator=(const CDamperGroupSecCollection &Grp)
	{
		if(this==&Grp) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<Grp.aDamperGroupPtr.GetCount();i++) 
		{
			CDamperGroupSec *s1=new CDamperGroupSec(*(Grp.aDamperGroupPtr[i]));
			aDamperGroupPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->id);  //记录最大ID
		}

		return *this;
	}

	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
};
