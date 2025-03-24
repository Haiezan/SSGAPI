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


struct PRESTRESSINGTENDONGROUP_DATA
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
	PRESTRESSINGTENDONGROUP_DATA(){	memset(this,0,sizeof(PRESTRESSINGTENDONGROUP_DATA));}
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

	~PRESTRESSINGTENDONGROUP_DATA()
	{			
		if(LinkIDs) delete[] LinkIDs; 
		LinkIDs=NULL;

		if(BeamIDs) delete[] BeamIDs; 
		BeamIDs=NULL;
		if(BeamMats) delete[] BeamMats; 
		BeamMats=NULL;

		if(Plates) delete[] Plates; 
		Plates=NULL;

		if(fPara) delete[] fPara; 
		fPara=NULL;

	};

	
	//���ظ�ֵ�����
	PRESTRESSINGTENDONGROUP_DATA & operator=(const PRESTRESSINGTENDONGROUP_DATA &gdata)
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
	//void Write2020(CASCFile &fout);
};


class  _SSG_DLLIMPEXP CPrestressingTendonGroupSec
{
public:
	//��������������
	CPrestressingTendonGroupSec(void) {Clear();}
	CPrestressingTendonGroupSec(const CPrestressingTendonGroupSec &Grp)	{nUsedCount=0; *this=Grp; }
	~CPrestressingTendonGroupSec(void) { Clear();}

	//��������
	int id;  //��ID
	CString sName;  //������
	PRESTRESSINGTENDONGROUP_STYLE iStyle;	//����ʽ
	PRESTRESSINGTENDONGROUP_DATA gData;//������
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	//�����
	CPrestressingTendonGroupSec & operator=(const CPrestressingTendonGroupSec &Grp);
	//�Զ��������
	CString &AutoName(void);
	//�����ʽ����
	CString GetStyleName(void);
	//��ʾ��ͼ��
	void ShowPrestressingTendonGroupPic(CDC *pDC,const CRect &re);
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

class  _SSG_DLLIMPEXP CPrestressingTendonGroupSecCollection
{
public:
	CPrestressingTendonGroupSecCollection(void){Clear();}
	~CPrestressingTendonGroupSecCollection(void){Clear();}

	CPrestressingTendonGroupSecCollection(const CPrestressingTendonGroupSecCollection &Grp)
	{
		*this=Grp;
	}

	CArray<CPrestressingTendonGroupSec*,CPrestressingTendonGroupSec*> aPrestressingTendonGroupPtr;  // ԤӦ����ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStyle,const CString &sName);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CPrestressingTendonGroupSec *GetPrestressingTendonGroupSec(int id) const;  //���ݸ�����������id���ؽ���ָ��
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendPrestressingTendonGroupSec(CPrestressingTendonGroupSec *pGrp);  //�����½��棬�Զ���ȡID

	CPrestressingTendonGroupSecCollection & operator=(const CPrestressingTendonGroupSecCollection &Grp)
	{
		if(this==&Grp) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<Grp.aPrestressingTendonGroupPtr.GetCount();i++) 
		{
			CPrestressingTendonGroupSec *s1=new CPrestressingTendonGroupSec(*(Grp.aPrestressingTendonGroupPtr[i]));
			aPrestressingTendonGroupPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};
