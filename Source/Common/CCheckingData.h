#pragma once
#include "PostData.h"
#include "SSGData.h"

#define IsoChkNum 5
#define GrvChkNum 1
#define DynChkNum 4
#define StyChkNum 5
#define StlChkNum 2
#define DmpChkNum 3

struct VALUE_SHOW
{
	float fValue;
	int id;
};

//#include "PostDefs.h"
struct _SSG_DLLIMPEXP DATA_UNIT
{
	CString sUnitF;	//具体单位：力{L"N",L"kN",L"kgf",L"tonf"};
	CString sUnitL;	//具体单位：长度{L"m",L"dm",L"cm",L"mm"}
	int nUnitM;			//量纲标记:质量
	int nUnitL;			//量纲标记:长度
	//时间不考虑为国际单位
	float fRatio;		//输出系数：内部永远为国际单位，通过该系数调整
	DATA_UNIT();
	DATA_UNIT(CString sUF,CString sUL,int nUM,int nUL);
	DATA_UNIT(DATA_UNIT &fmt);
	DATA_UNIT &operator=(const DATA_UNIT &data);
	void InitUnit(CString sUnitName);
	void ChangeDim(CString sUnitName);
	void GetUnitRatio();
	CString GetUnit();
};

//验算数据：对应一条验算数据
struct BaseCheckData
{
	int nPara;				//中间数据个数
	float *fPara;			//中间数据
	float fValue;			//需要验算的结果数据
	float fLimit;			//最终验算限值
	float fCodeLimit;	//验算规范限值
	BOOL bSignisGT;	//要求是大于限值还是小于限值
	BaseCheckData()
	{
		memset(this,0,sizeof(BaseCheckData));
	}
	BaseCheckData(int nParameter)
	{
		memset(this,0,sizeof(BaseCheckData));
		if (nParameter!=0)
		{
			nPara=nParameter;
			fPara=new float[nPara];
		}
	}
	~BaseCheckData()
	{
		Clear();
		memset(this,0,sizeof(BaseCheckData));
	}
	void Clear()
	{
		nPara			=0;
		if(fPara!=NULL)
		{
			delete []fPara; fPara=NULL;
		}
		fValue			=0.f;
		fLimit			=0.f;
		fCodeLimit=0.f;
		bSignisGT	=FALSE;
	};
	BaseCheckData &operator=(const BaseCheckData &data)
	{
		if(this==&data) return *this;

		Clear();

		fValue			=data.fValue;
		fLimit			=data.fLimit;
		fCodeLimit=data.fCodeLimit;
		bSignisGT	=data.bSignisGT;
		nPara			=data.nPara;
		if(nPara!=0)
		{
			fPara=new float[nPara];
			for (int i=0;i<nPara;i++)
				fPara[i]=data.fPara[i];
		}
		return *this;
	}
	BOOL bMeetCheckingLimit()
	{
		if( bSignisGT && fValue>=fLimit) return TRUE;
		if(!bSignisGT && fValue<=fLimit) return TRUE;
		return FALSE;
	};
	BOOL bMeetCodeLimit()
	{
		if( bSignisGT && fValue>=fCodeLimit) return TRUE;
		if(!bSignisGT && fValue<=fCodeLimit) return TRUE;
		return FALSE;
	};
	CString GetValueString(float fRatio=1.f,CString sFormat=L"%3.2f")
	{
		CString sText;
		sText.Format(sFormat,fValue*fRatio);
		return sText;
	};
	CString GetLimitString(float fRatio=1.f,CString sFormat=L"%3.2f")
	{
		CString sText;
		sText.Format(sFormat,fLimit*fRatio);
		return sText;
	};
	CString GetCheckResultsText(BOOL bShowLimit,float fRatio=1.f,CString sFormat=L"%3.2f")
	{
		CString sText;
		sText.Format(sFormat,fValue*fRatio);
		CString sSign;
		if(bMeetCheckingLimit()&& bSignisGT ||
			!bMeetCheckingLimit()&&!bSignisGT)
			sSign=L">";
		else 
			sSign=L"<";
		//显示限制
		if(bShowLimit)
		{
			CString sLimit;
			sLimit.Format(sFormat,fLimit*fRatio);
			sText+=sSign+sLimit;
		}
		return sText;
	};
};

//验算的项目
enum ISOCHECKING_TYPE
{
	GRAVSTRESS,			//重力荷载代表值压应力
	//GRAVDISDEV,			//重力荷载代表值竖向变形偏差
	DYNCMPSTRESS,	//时程最大压应力
	DYNTENSTRESS,		//时程最大拉应力
	DYNULTIMATEDIS,	//时程极限水平位移
	DYNTENSPERCENT,  //时程受拉百分比
	DYNDESTROYDIS,	//时程破坏水平位移
};

enum STYCHECKING_TYPE
{
	HORIZFORCE,			//水平力
	ECCENTRICITY,		//偏心率
	ANTIWINDFORCE,	//抗风
	YIELDGRAVRATIO,	//屈重比	
	ELASTICFORCE	,		//弹性恢复力	
};

//验算数据类：对应一个构件一组验算
class _SSG_DLLIMPEXP CMemberCheckingData
{
public:
	CMemberCheckingData()
	{	
		sName="";
		idShow=-1;
		sType="";
		id=-1;	
		nData=0;
		cData=NULL;
	};
	virtual ~CMemberCheckingData(){Clear();};

	CString sName; //名称
	int idShow;	//显示编号
	CString sType;//类型
	int id;//对应真实线构件编号
	int nData;//验算数据个数
	BaseCheckData *cData;//验算数据
	CMemberCheckingData(const CMemberCheckingData &cd)
	{
		cData = NULL;
		*this = cd;
	}
	CMemberCheckingData &operator=(const CMemberCheckingData &cd);
	void SetCheckData(int ndata);
	void Clear();
}; 

//支座输出格式样式：对应所有支座一个验算输出格式
struct LinkDataFormat
{
	CString sName;//结果名称
	CString sNameAbbr;//结果名称英文简写
	DATA_UNIT cUnit;//单位/量纲及和国际单位的比值
	CString sFormat;//输出格式
	float fRatio(){return cUnit.fRatio;};
	LinkDataFormat()
	{
		sName=L"";
		sNameAbbr=L"";
		sFormat=L"%3.2f";
	}
};

//支座在验算数据中的id和支座名字，id用于输出，根据支座名字排序
struct IdName
{
	int id;
	CString sName;
};

//验算数据类集合
class  _SSG_DLLIMPEXP CMemberCheckingDataCollection
{
public:
	CMemberCheckingDataCollection(void)
	{
		iMaxID=0;
		bReadData=NULL;
		cFmt=NULL;
	}
	CMemberCheckingDataCollection(const CMemberCheckingDataCollection &data)
	{
		*this=data;
	}
	virtual ~CMemberCheckingDataCollection(void){Clear();}

	CArray<CMemberCheckingData*,CMemberCheckingData*> aMemberCheckingDataPtr;  //数据类指针
	int iMaxID;  //当前用到的最大ID
	int nDataNum;//验算数据项目数量
	//支座输出格式样式
	LinkDataFormat *cFmt;
	//是否已载入数据
	BOOL *bReadData;
	
	int GetMemberCount(){return (int)aMemberCheckingDataPtr.GetCount();}
	void SetCheckDataCollection(int ndata);
	CMemberCheckingData *GetMemberCheckingDataByShowId(int idshow) const;  //根据给定的数据id返回数据指针
	int GetIndexByShowId(int idshow) const;  //根据给定的数据idshow返回索引id,找不到返回-1
	void AppendMemberCheckingData(CMemberCheckingData *pdata);  //增加新数据，自动获取ID

	CMemberCheckingDataCollection & operator=(const CMemberCheckingDataCollection &data)
	{
		if(this==&data) return *this; //自身赋值时直接返回

		Clear();
		for(int i=0;i<data.aMemberCheckingDataPtr.GetCount();i++) 
		{
			CMemberCheckingData *s1=new CMemberCheckingData(*(data.aMemberCheckingDataPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aMemberCheckingDataPtr.Add(s1);  //这里不调用AppendSection，不改变ID
			iMaxID=max(iMaxID,s1->idShow);  //记录最大ID
		}
		
		SetCheckDataCollection(data.nDataNum);
		for(int i=0;i<nDataNum;i++) 
		{
			cFmt[i]=data.cFmt[i];
			bReadData[i]=data.bReadData[i];
		}

		return *this;
	}
	void Clear();
	static bool Cmp(const IdName &tmp1,const IdName &tmp2)
	{
       if (tmp1.sName.GetLength()==tmp2.sName.GetLength())
       {
			return tmp1.sName<tmp2.sName ? true:false;
       }
		else
			return tmp1.sName.GetLength()<tmp2.sName.GetLength() ? true:false;
	}
	CString GetMemberCheckingDataText(int id,int iCheckType,BOOL bShowLimit=TRUE);
	//按CMemberCheckingData 中 sName 重排id
	void SortMemberCheckingData();
	////读取重力荷载代表值结果
	//virtual BOOL  ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE){return FALSE;};
	////读取动力时程结果
	//virtual BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L""){return FALSE;};
};

//隔震验算数据类：对应一个支座的所有验算数据
class  _SSG_DLLIMPEXP CISOCheckingData: public CMemberCheckingData
{
public:
	CISOCheckingData()
	{
		SetCheckData(IsoChkNum);
		iBType=LINK_ISOLATOR;
	};
	~CISOCheckingData(){};
	LINK_SUBTYPE iBType;

	BOOL InitCheckingCodeLimit(int iBuildingCategory);
	CISOCheckingData &operator=(const CISOCheckingData &cd);

	static float fLimitCode_Grav[];
	static float fLimitCode_Tens[];
	static float fLimitCode_Cmp[];
	static float fLimitCode_GravESB[];
	static float fLimitCode_GravFPS[];
	static float fLimitCode_CmpESB[];
	static float fLimitCode_TensESB;
	static float fLimitCode_CmpFPS[];
	static float fLimitCode_TensFPS;
}; 

//隔震支座验算数据类集合
class  _SSG_DLLIMPEXP CISOCheckingDataCollection: public CMemberCheckingDataCollection
{
public:
	CISOCheckingDataCollection(void)
	{
		SetCheckDataCollection(IsoChkNum);
	}
	~CISOCheckingDataCollection(void){}

	void InitDataFormat();
	CISOCheckingDataCollection &operator=(const CISOCheckingDataCollection &cd);
	//增加新数据，自动获取ID
	void AppendISOCheckingData(CISOCheckingData *pdata);  
	//根据给定的数据idshow返回数据id指针
	CISOCheckingData *GetISOCheckingDataByShowId(int idshow) const;  
	//直接返回对应Id的数据
	CISOCheckingData *GetISOCheckingData(int id) const; 
	//读取重力荷载代表值结果
	BOOL ReadStaticCheckingData(CArray<float, float > &aIsoN, int iCheckType,BOOL bExactGetResult=FALSE,bool bShowError=false);
	//读取动力时程结果
	BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
};

//模型验算数据
class  _SSG_DLLIMPEXP CStoryCheckingData
{
public:
	CStoryCheckingData()
	{
		cData=NULL;
		fmt=NULL;
		Clear();
	};
	CStoryCheckingData(int iChkType)
	{
		InitStoryCheckData(iChkType);
	};
	~CStoryCheckingData(){Clear();};

	CString sName;					//验算项目名称
	int iCheckType;					//类型验算类型
	int nNum;							//验算数据个数 默认X Y Z
	BaseCheckData *cData;	//验算数据
	LinkDataFormat *fmt;		//数据的输出格式
	BOOL bInit;						//数据是否初始化
	BOOL bGetData;				//数据是否已读入
	 //初始化数据
	BOOL InitStoryCheckData(int iChkType);
	 //读取数据
	BOOL ReadStoryCheckData(int iChkType);
	//形成表格数据
	BOOL GenerateExcelText(CString *&pText,int &nRow,int &nCol);
	void Clear();

	static CArray<int,int> m_aIsoTower;
	static CArray<float,float> m_aIsoN;
	static vector<vector<int>> m_vIsoTowerData;
	static CISOCheckingDataCollection m_cIsolatorData;
private:
	//求偏心率
	void	GetEccentricityData();
	//求屈重比
	void	GetYieldGravRatioData();
	//抗风
	void GetAntiWindForceData();
	//水平力
	void	GetHorizForceData();
	//弹性恢复力
	void	GetElasticForceData();
}; 

//钢结构验算数据
class  _SSG_DLLIMPEXP CSTLCheckingData: public CMemberCheckingData
{
public:
	CSTLCheckingData()
	{	
		SetCheckData(StlChkNum);
	};
	~CSTLCheckingData(){};

	BOOL InitCheckingCodeLimit();
}; 

//钢结构验算数据类集合
class  _SSG_DLLIMPEXP CSTLCheckingDataCollection: public CMemberCheckingDataCollection
{
public:
	CSTLCheckingDataCollection(void)
	{
		SetCheckDataCollection(StlChkNum);
	}
	~CSTLCheckingDataCollection(void){}

	void InitDataFormat();
	//增加新数据，自动获取ID
	void AppendSTLCheckingData(CSTLCheckingData *pdata);  
	//根据给定的数据idshow返回数据id指针
	CSTLCheckingData *GetSTLCheckingDataByShowId(int idshow) const;  
	//直接返回对应Id的数据
	CSTLCheckingData *GetSTLCheckingData(int id) const; 
	////读取重力荷载代表值结果
	//BOOL ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE);
	//读取动力时程结果 正应力按应力比验算
	BOOL ReadDynaCheckingDataOld(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
	//读取动力时程结果
	BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
};

//减震构验算数据
class  _SSG_DLLIMPEXP CDMPCheckingData: public CMemberCheckingData
{
public:
	CDMPCheckingData()
	{	
		SetCheckData(DmpChkNum);
		memset(&m_bDof,0,6*sizeof(BOOL));
		m_nChk=3;
		m_bX=TRUE;
	};
	~CDMPCheckingData(){};

	BOOL InitCheckingCodeLimit();
//减震自带自由度数据：
	BOOL m_bDof[6];//自由度
	int m_nChk;//参数：设计荷载、设计位移、设计速度
	BOOL m_bX;//阻尼器作用方向
}; 

//减震验算数据类集合
class  _SSG_DLLIMPEXP CDMPCheckingDataCollection: public CMemberCheckingDataCollection
{
public:
	CDMPCheckingDataCollection(void)
	{
		SetCheckDataCollection(DmpChkNum);
	}
	~CDMPCheckingDataCollection(void){}

	void InitDataFormat();
	//增加新数据，自动获取ID
	void AppendDMPCheckingData(CDMPCheckingData *pdata);  
	//根据给定的数据idshow返回数据id指针
	CDMPCheckingData *GetDMPCheckingDataByShowId(int idshow) const;  
	//直接返回对应Id的数据
	CDMPCheckingData *GetDMPCheckingData(int id) const; 
	////读取重力荷载代表值结果
	//BOOL ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE);
	//读取动力时程结果
	BOOL ReadDynaCheckingData(BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
	//消能器统计

	//减震验算不同
	CString GetMemberCheckingDataText(int id,int iCheckType,BOOL bShowLimit=TRUE);
};

//模型验算数据类
class  _SSG_DLLIMPEXP CCheckingData
{
public:
	CCheckingData()
	{
		m_bInitIsolatorData=FALSE;
		m_bInitStoryData=FALSE;
		m_cStoryData=NULL;
		m_iIsoStory=1;
		m_bInitSteelData=FALSE;
		m_bInitSteelData=FALSE;
	};
	~CCheckingData(){Clear();};

	//整体函数
	void Clear();
	//隔震支座验算数据
	CISOCheckingDataCollection m_cIsolatorData;
	BOOL InitIsolatorCheckingData();
    BOOL m_bInitIsolatorData;
	//隔震层验算数据
	CStoryCheckingData *m_cStoryData;
	BOOL InitStoryCheckingData();
	BOOL m_bInitStoryData;
	int  m_iIsoStory;
	CArray<int,int>m_aIsoTower;
	CArray<float,float>m_aIsoN;
	vector<vector<int>> m_vIsoTowerData;
	//钢结构截面承载力验算数据
	CSTLCheckingDataCollection m_cSteelData;
	BOOL InitSteelCheckingData();
	BOOL m_bInitSteelData;
	//减震验算数据
	CDMPCheckingDataCollection m_cDmpData;
	BOOL InitDmpCheckingData();
	BOOL m_bInitDmpData;
//
private:
	//得到支座轴力
	void GetAllIsoForce();
}; 
