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

	
	//���ظ�ֵ�����
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
	//��������������
	CPartitionWallGroupSec(void)
		: id(-1)
		, sName(L"")
		, iStyle(STYLE_SINGLE_DIAGONAL_BRACING)
		, nUsedCount(0)
	{
	}
	CPartitionWallGroupSec(const CPartitionWallGroupSec &Grp)	{nUsedCount=0; *this=Grp; }
	~CPartitionWallGroupSec(void) { Clear();}

	//��������
	int id;  //��ID
	CString sName;  //������
	PARTITIONWALL_GROUP_STYLE iStyle;	//����ʽ
	PARTITIONWALL_GROUP_DATA gData;//������
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	//�����
	CPartitionWallGroupSec & operator=(const CPartitionWallGroupSec &Grp);
	//�Զ��������
	CString &AutoName(void);
	//��ʾ��ͼ��
	void ShowPartitionWallGroupPic(CDC *pDC,const CRect &re);
    //�������
	void Clear(void);
	//���ݶ�д
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	//��ģ����
	CString BuildWarning(int iStory,int iType=0);
	//�����Լ�
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

	CArray<CPartitionWallGroupSec*,CPartitionWallGroupSec*> aPartitionWallGroupPtr;  //������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStyle,const CString &sName);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CPartitionWallGroupSec *GetPartitionWallGroupSec(int id) const;  //���ݸ�����������id���ؽ���ָ��
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendPartitionWallGroupSec(CPartitionWallGroupSec *pGrp);  //�����½��棬�Զ���ȡID

	CPartitionWallGroupSecCollection & operator=(const CPartitionWallGroupSecCollection &Grp)
	{
		if(this==&Grp) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<Grp.aPartitionWallGroupPtr.GetCount();i++) 
		{
			CPartitionWallGroupSec *s1=new CPartitionWallGroupSec(*(Grp.aPartitionWallGroupPtr[i]));
			aPartitionWallGroupPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};
