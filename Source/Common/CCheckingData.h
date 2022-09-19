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
	CString sUnitF;	//���嵥λ����{L"N",L"kN",L"kgf",L"tonf"};
	CString sUnitL;	//���嵥λ������{L"m",L"dm",L"cm",L"mm"}
	int nUnitM;			//���ٱ��:����
	int nUnitL;			//���ٱ��:����
	//ʱ�䲻����Ϊ���ʵ�λ
	float fRatio;		//���ϵ�����ڲ���ԶΪ���ʵ�λ��ͨ����ϵ������
	DATA_UNIT();
	DATA_UNIT(CString sUF,CString sUL,int nUM,int nUL);
	DATA_UNIT(DATA_UNIT &fmt);
	DATA_UNIT &operator=(const DATA_UNIT &data);
	void InitUnit(CString sUnitName);
	void ChangeDim(CString sUnitName);
	void GetUnitRatio();
	CString GetUnit();
};

//�������ݣ���Ӧһ����������
struct BaseCheckData
{
	int nPara;				//�м����ݸ���
	float *fPara;			//�м�����
	float fValue;			//��Ҫ����Ľ������
	float fLimit;			//����������ֵ
	float fCodeLimit;	//����淶��ֵ
	BOOL bSignisGT;	//Ҫ���Ǵ�����ֵ����С����ֵ
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
		//��ʾ����
		if(bShowLimit)
		{
			CString sLimit;
			sLimit.Format(sFormat,fLimit*fRatio);
			sText+=sSign+sLimit;
		}
		return sText;
	};
};

//�������Ŀ
enum ISOCHECKING_TYPE
{
	GRAVSTRESS,			//�������ش���ֵѹӦ��
	//GRAVDISDEV,			//�������ش���ֵ�������ƫ��
	DYNCMPSTRESS,	//ʱ�����ѹӦ��
	DYNTENSTRESS,		//ʱ�������Ӧ��
	DYNULTIMATEDIS,	//ʱ�̼���ˮƽλ��
	DYNTENSPERCENT,  //ʱ�������ٷֱ�
	DYNDESTROYDIS,	//ʱ���ƻ�ˮƽλ��
};

enum STYCHECKING_TYPE
{
	HORIZFORCE,			//ˮƽ��
	ECCENTRICITY,		//ƫ����
	ANTIWINDFORCE,	//����
	YIELDGRAVRATIO,	//���ر�	
	ELASTICFORCE	,		//���Իָ���	
};

//���������ࣺ��Ӧһ������һ������
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

	CString sName; //����
	int idShow;	//��ʾ���
	CString sType;//����
	int id;//��Ӧ��ʵ�߹������
	int nData;//�������ݸ���
	BaseCheckData *cData;//��������
	CMemberCheckingData(const CMemberCheckingData &cd)
	{
		cData = NULL;
		*this = cd;
	}
	CMemberCheckingData &operator=(const CMemberCheckingData &cd);
	void SetCheckData(int ndata);
	void Clear();
}; 

//֧�������ʽ��ʽ����Ӧ����֧��һ�����������ʽ
struct LinkDataFormat
{
	CString sName;//�������
	CString sNameAbbr;//�������Ӣ�ļ�д
	DATA_UNIT cUnit;//��λ/���ټ��͹��ʵ�λ�ı�ֵ
	CString sFormat;//�����ʽ
	float fRatio(){return cUnit.fRatio;};
	LinkDataFormat()
	{
		sName=L"";
		sNameAbbr=L"";
		sFormat=L"%3.2f";
	}
};

//֧�������������е�id��֧�����֣�id�������������֧����������
struct IdName
{
	int id;
	CString sName;
};

//���������༯��
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

	CArray<CMemberCheckingData*,CMemberCheckingData*> aMemberCheckingDataPtr;  //������ָ��
	int iMaxID;  //��ǰ�õ������ID
	int nDataNum;//����������Ŀ����
	//֧�������ʽ��ʽ
	LinkDataFormat *cFmt;
	//�Ƿ�����������
	BOOL *bReadData;
	
	int GetMemberCount(){return (int)aMemberCheckingDataPtr.GetCount();}
	void SetCheckDataCollection(int ndata);
	CMemberCheckingData *GetMemberCheckingDataByShowId(int idshow) const;  //���ݸ���������id��������ָ��
	int GetIndexByShowId(int idshow) const;  //���ݸ���������idshow��������id,�Ҳ�������-1
	void AppendMemberCheckingData(CMemberCheckingData *pdata);  //���������ݣ��Զ���ȡID

	CMemberCheckingDataCollection & operator=(const CMemberCheckingDataCollection &data)
	{
		if(this==&data) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<data.aMemberCheckingDataPtr.GetCount();i++) 
		{
			CMemberCheckingData *s1=new CMemberCheckingData(*(data.aMemberCheckingDataPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aMemberCheckingDataPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->idShow);  //��¼���ID
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
	//��CMemberCheckingData �� sName ����id
	void SortMemberCheckingData();
	////��ȡ�������ش���ֵ���
	//virtual BOOL  ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE){return FALSE;};
	////��ȡ����ʱ�̽��
	//virtual BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L""){return FALSE;};
};

//�������������ࣺ��Ӧһ��֧����������������
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

//����֧�����������༯��
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
	//���������ݣ��Զ���ȡID
	void AppendISOCheckingData(CISOCheckingData *pdata);  
	//���ݸ���������idshow��������idָ��
	CISOCheckingData *GetISOCheckingDataByShowId(int idshow) const;  
	//ֱ�ӷ��ض�ӦId������
	CISOCheckingData *GetISOCheckingData(int id) const; 
	//��ȡ�������ش���ֵ���
	BOOL ReadStaticCheckingData(CArray<float, float > &aIsoN, int iCheckType,BOOL bExactGetResult=FALSE,bool bShowError=false);
	//��ȡ����ʱ�̽��
	BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
};

//ģ����������
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

	CString sName;					//������Ŀ����
	int iCheckType;					//������������
	int nNum;							//�������ݸ��� Ĭ��X Y Z
	BaseCheckData *cData;	//��������
	LinkDataFormat *fmt;		//���ݵ������ʽ
	BOOL bInit;						//�����Ƿ��ʼ��
	BOOL bGetData;				//�����Ƿ��Ѷ���
	 //��ʼ������
	BOOL InitStoryCheckData(int iChkType);
	 //��ȡ����
	BOOL ReadStoryCheckData(int iChkType);
	//�γɱ������
	BOOL GenerateExcelText(CString *&pText,int &nRow,int &nCol);
	void Clear();

	static CArray<int,int> m_aIsoTower;
	static CArray<float,float> m_aIsoN;
	static vector<vector<int>> m_vIsoTowerData;
	static CISOCheckingDataCollection m_cIsolatorData;
private:
	//��ƫ����
	void	GetEccentricityData();
	//�����ر�
	void	GetYieldGravRatioData();
	//����
	void GetAntiWindForceData();
	//ˮƽ��
	void	GetHorizForceData();
	//���Իָ���
	void	GetElasticForceData();
}; 

//�ֽṹ��������
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

//�ֽṹ���������༯��
class  _SSG_DLLIMPEXP CSTLCheckingDataCollection: public CMemberCheckingDataCollection
{
public:
	CSTLCheckingDataCollection(void)
	{
		SetCheckDataCollection(StlChkNum);
	}
	~CSTLCheckingDataCollection(void){}

	void InitDataFormat();
	//���������ݣ��Զ���ȡID
	void AppendSTLCheckingData(CSTLCheckingData *pdata);  
	//���ݸ���������idshow��������idָ��
	CSTLCheckingData *GetSTLCheckingDataByShowId(int idshow) const;  
	//ֱ�ӷ��ض�ӦId������
	CSTLCheckingData *GetSTLCheckingData(int id) const; 
	////��ȡ�������ش���ֵ���
	//BOOL ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE);
	//��ȡ����ʱ�̽�� ��Ӧ����Ӧ��������
	BOOL ReadDynaCheckingDataOld(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
	//��ȡ����ʱ�̽��
	BOOL ReadDynaCheckingData(int iCheckType,BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
};

//������������
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
//�����Դ����ɶ����ݣ�
	BOOL m_bDof[6];//���ɶ�
	int m_nChk;//��������ƺ��ء����λ�ơ�����ٶ�
	BOOL m_bX;//���������÷���
}; 

//�������������༯��
class  _SSG_DLLIMPEXP CDMPCheckingDataCollection: public CMemberCheckingDataCollection
{
public:
	CDMPCheckingDataCollection(void)
	{
		SetCheckDataCollection(DmpChkNum);
	}
	~CDMPCheckingDataCollection(void){}

	void InitDataFormat();
	//���������ݣ��Զ���ȡID
	void AppendDMPCheckingData(CDMPCheckingData *pdata);  
	//���ݸ���������idshow��������idָ��
	CDMPCheckingData *GetDMPCheckingDataByShowId(int idshow) const;  
	//ֱ�ӷ��ض�ӦId������
	CDMPCheckingData *GetDMPCheckingData(int id) const; 
	////��ȡ�������ش���ֵ���
	//BOOL ReadStaticCheckingData(int iCheckType,BOOL bExactGetResult=FALSE);
	//��ȡ����ʱ�̽��
	BOOL ReadDynaCheckingData(BOOL bExactGetResult=FALSE,CString sDirName=L"",bool bShowError=false);
	//������ͳ��

	//�������㲻ͬ
	CString GetMemberCheckingDataText(int id,int iCheckType,BOOL bShowLimit=TRUE);
};

//ģ������������
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

	//���庯��
	void Clear();
	//����֧����������
	CISOCheckingDataCollection m_cIsolatorData;
	BOOL InitIsolatorCheckingData();
    BOOL m_bInitIsolatorData;
	//�������������
	CStoryCheckingData *m_cStoryData;
	BOOL InitStoryCheckingData();
	BOOL m_bInitStoryData;
	int  m_iIsoStory;
	CArray<int,int>m_aIsoTower;
	CArray<float,float>m_aIsoN;
	vector<vector<int>> m_vIsoTowerData;
	//�ֽṹ�����������������
	CSTLCheckingDataCollection m_cSteelData;
	BOOL InitSteelCheckingData();
	BOOL m_bInitSteelData;
	//������������
	CDMPCheckingDataCollection m_cDmpData;
	BOOL InitDmpCheckingData();
	BOOL m_bInitDmpData;
//
private:
	//�õ�֧������
	void GetAllIsoForce();
}; 
