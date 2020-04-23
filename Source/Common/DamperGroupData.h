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
	GROUP_DATA(){	memset(this,0,sizeof(GROUP_DATA));}
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
		if(BeamMats) delete[] BeamMats; 
		BeamMats=NULL;

		if(Plates) delete[] Plates; 
		Plates=NULL;

		if(fPara) delete[] fPara; 
		fPara=NULL;
	};

	
	//���ظ�ֵ�����
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
};


class  _SSG_DLLIMPEXP CDamperGroupSec
{
public:
	//��������������
	CDamperGroupSec(void) {Clear();}
	CDamperGroupSec(const CDamperGroupSec &Grp)	{nUsedCount=0; *this=Grp; }
	~CDamperGroupSec(void) { Clear();}

	//��������
	int id;  //��ID
	CString sName;  //������
	GROUP_STYLE iStyle;	//����ʽ
	GROUP_DATA gData;//������
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	//�����
	CDamperGroupSec & operator=(const CDamperGroupSec &Grp);
	//�Զ��������
	CString &AutoName(void);
	//�����ʽ����
	CString GetStyleName(void);
	//��ʾ��ͼ��
	void ShowDamperGroupPic(CDC *pDC,const CRect &re);
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

class  _SSG_DLLIMPEXP CDamperGroupSecCollection
{
public:
	CDamperGroupSecCollection(void){Clear();}
	~CDamperGroupSecCollection(void){Clear();}

	CDamperGroupSecCollection(const CDamperGroupSecCollection &Grp)
	{
		*this=Grp;
	}

	CArray<CDamperGroupSec*,CDamperGroupSec*> aDamperGroupPtr;  //������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStyle,const CString &sName);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CDamperGroupSec *GetDamperGroupSec(int id) const;  //���ݸ�����������id���ؽ���ָ��
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendDamperGroupSec(CDamperGroupSec *pGrp);  //�����½��棬�Զ���ȡID

	CDamperGroupSecCollection & operator=(const CDamperGroupSecCollection &Grp)
	{
		if(this==&Grp) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<Grp.aDamperGroupPtr.GetCount();i++) 
		{
			CDamperGroupSec *s1=new CDamperGroupSec(*(Grp.aDamperGroupPtr[i]));
			aDamperGroupPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};
