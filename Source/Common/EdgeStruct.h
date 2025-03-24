#pragma once
#include "HeadDefine.h"
#include "SysPara.h"
#include "ASCFile.h"
#include "PublicFunc.h"
#include "BeamSection.h"

#include <list>
using namespace std;

enum EDGE_REBAR_AREA_TYPE
{
	EDGE_REBAR_AREA_IMPORT=0,	//���õ���������0ʱ���ü���ֵ
	EDGE_REBAR_AREA_COMPUTE=1,	//ȡ�淶����ֵ��������ֵAc*ratio������С�ֽ�ֱ������ֵasmin���������
	EDGE_REBAR_AREA_MAX=2,		//ȡ4�����ֵ
};

enum EDGE_REBAR_GENERATE_METHOD
{
	EDGE_REBAR_NONE = -1,
	EDGE_REBAR_REGENERATE = 0,	//�������ɱ�Ե����
	EDGE_REBAR_SUPPLEMENT_GENERATION = 1,	// �������ɱ�Ե����
};


class CVertex;
class CBeamStruc;
class CLine;

//��Ե���������ԣ�ÿ��������ж����Ե��������ʼʱ�������㴴��������ÿ�������㶼�п��ܴ�����Ե����
//�����ļ�ʱ���������Ч�ĵ�,	���Դ˵�ͽṹ�㲻һ����Ӧ
class _SSG_DLLIMPEXP  CPointEdgeProp
{
public:
	CPointEdgeProp(void);
	~CPointEdgeProp(void);

	int nWalls;  //��˿��ܵı�Ե����������ǽ��֧��
	int nBeam;  //�˶����µı�Ե��������ͬһ¥���У�ͬһ�������¿����кܶ�νṹ�ߣ����Ҳ���ܰ����ܶ�α�Ե����
	int *pBeamID;  //��Ե����IDM,ע�⣺��malloc����
	float fImportRebarArea;  //�ݽ�������,��ָ��PKPM��������=max(���������, �淶��С�����)���û������޸ġ�
	float fImportRebarRatio;  //�ݽ������,��ָ��PKPM��������=max(���������, �淶��С�����)��������Ӱ�����,����ֱ�ӵ��������ʣ��û������޸ġ�
	float fRebarArea; //ʵ���������m^2��,�ӿڵ���ʱ��fImportRebarArea��ʼ��, ����Ϊ�û��޸ĺ����ݣ��û��ɽ����޸�
	float fVolumeStirrupRatio; //����乿��
	bool bYBZ; //�Ƿ�Լ����Ե����

	int idWall[Sys_Max_Connect_Wall];	//ǽ��IDM
	float fAng[Sys_Max_Connect_Wall];   //�˵���idPoint���ɵ�������X��нǣ����ȣ�0-2*PI
	float lc[Sys_Max_Connect_Wall];		//Լ�������ȣ��ӽ������λ������
	
	float fStirDist[Sys_Max_Connect_Wall],fStirDiam[Sys_Max_Connect_Wall]; //������(m)������ֱ��(m)
	int nStirL[Sys_Max_Connect_Wall],nStirW[Sys_Max_Connect_Wall]; //Լ�������ȷ��򹿽�֫����ȱʡΪ0��,Լ������ȷ��򹿽�֫����ȱʡΪ0��

    int nWallBeam[Sys_Max_Connect_Wall];//ͬnBeam�����Ǹ�ǽ֫�ϵ�
    int *pWallBeamID[Sys_Max_Connect_Wall];//ͬ*pBeamID�����Ǹ�ǽ֫�ϵ�
	//��ʱ����
	int idPillar;  //����IDM��-1��ʾû�У� ֻ��nWalls>0ʱ����Ч
	float fOverlapArea;  //�ص����
	
	
	int idPoint[Sys_Max_Connect_Wall];  //ǽ���г��õ�������˵��IDM��-1��ʾ��Ч
	int idFarPoint[Sys_Max_Connect_Wall];  //���й������ǽ�����Զ�˵��IDM��-1��ʾ��Ч

	CPointEdgeProp & operator=(const CPointEdgeProp &prop)
	{
		if(this==&prop) return *this;

		Clear();

		nWalls=prop.nWalls; 
		nBeam=prop.nBeam;

		pBeamID=(int *)malloc(nBeam*sizeof(int));
		memcpy(pBeamID,prop.pBeamID,nBeam*sizeof(int));

		fImportRebarRatio=prop.fImportRebarRatio;
		fImportRebarArea=prop.fImportRebarArea;
		fRebarArea=prop.fRebarArea;
		fVolumeStirrupRatio = prop.fVolumeStirrupRatio;   
		bYBZ = prop.bYBZ;   

		for(int i=0;i<nWalls;i++)
		{
			idWall[i]=prop.idWall[i];
			fAng[i]=prop.fAng[i];
			lc[i]=prop.lc[i];

			fStirDist[i]=prop.fStirDist[i];
			fStirDiam[i]=prop.fStirDiam[i];
			nStirL[i]=prop.nStirL[i];
			nStirW[i]=prop.nStirW[i];
			nWallBeam[i]=prop.nWallBeam[i];
			pWallBeamID[i]=(int *)malloc(nWallBeam[i]*sizeof(int));
			memcpy(pWallBeamID[i],prop.pWallBeamID[i],nWallBeam[i]*sizeof(int));

			idPoint[i]=prop.idPoint[i];   
			idFarPoint[i]=prop.idFarPoint[i];
		}

		idPillar=prop.idPillar;
		fOverlapArea=prop.fOverlapArea; 

		return *this;
	}

	void Clear(void)
	{
		nWalls=0; 
		nBeam=0;
		free(pBeamID); pBeamID=NULL;
		fImportRebarArea=0;
		fImportRebarRatio=0;
		fRebarArea=0;
		fVolumeStirrupRatio = 0;
		bYBZ = FALSE;

		idPillar=-1;
		fOverlapArea=0;

		for (int i=0;i<Sys_Max_Connect_Wall;i++)
		{
			idWall[i]=-1;
			fAng[i]=0;
			lc[i]=0;

			fStirDist[i]=0;
			fStirDiam[i]=0;
			nStirL[i]=0;
			nStirW[i]=0;
            nWallBeam[i]=0;
            free(pWallBeamID[i]); pWallBeamID[i]=NULL;

			idPoint[i]=-1;
			idFarPoint[i]=-1;
		}
	}

	BOOL IsValid(void) const {return pBeamID!=NULL;}

	void SwapWall(int n1,int n2)
	{
		CPublicFunc::SwapData(idPoint[n1],idPoint[n2]);
		CPublicFunc::SwapData(idWall[n1],idWall[n2]);
		CPublicFunc::SwapData(fAng[n1],fAng[n2]);
		CPublicFunc::SwapData(idFarPoint[n1],idFarPoint[n2]);
		CPublicFunc::SwapData(lc[n1],lc[n2]);
	}

	BOOL AddWall(int id_point,int id_wall,float angle)
	{
		if(nWalls>=Sys_Max_Connect_Wall) 
		{
			TRACE("too namy walls:  id_point=%d ,id_wall=%d\r\n",id_point,id_wall);
			return FALSE;
		}
		int iFind = -1;
		for (int i = 0; i < nWalls; i++)
		{
			if (id_wall == idWall[i])
			{
				iFind = i;
				break;
			}

		}
		if (iFind == -1)
		{
			idPoint[nWalls] = id_point;
			idWall[nWalls] = id_wall;
			fAng[nWalls] = angle;
			idFarPoint[nWalls] = -1;
			idPillar = -1;
			nWalls++;
		}
		else
		{
			idPoint[iFind] = id_point;
			idWall[iFind] = id_wall;
			fAng[iFind] = angle;
			idFarPoint[iFind] = -1;
			idPillar = -1;
		}

		return TRUE;
	}

	//�����ж�����Լ�����ߴ磬MainIndexΪҪ�����ǽ����ţ���Ϊpt��Ա������±�,
	float GetPillarSize(int MainIndex);

	//�õ�����֧Լ��������,v1,v2Ϊ��ֻǽ���������㣬����֧ʱ��Ч
	void GetLC(const CVertex &v1,const CVertex &v2);

	//����PKPM��������ݵõ���ʼָ��������
	float GetPKPM_As(void);

	//����������������
	float GetZoneArea( void);

	float GetSectionWidth(void);  //�����Ե���������ȣ������ν��棬ȡ���ǽ��ȵ����ֵ

	//��������������A=��(����֧����*����֧���)
	//���������=A*���������
	//ʵ�������=����ͬ��ʽ����
	//ʵ�������=ʵ�������/A

	
	//iType=0 Լ����Ե����
	//iType=1 �ײ���ǿ�����Ϲ����Ե����
	//iType=2 �ײ���ǿ�������Ե����
	static float GetSysRatio(int iStory); //�õ�ϵͳ��������ʣ��뿹��ȼ���¥���Ե���������йأ���λ1
	static float GetMinArea(int iStory); //�õ���С������

};

class _SSG_DLLIMPEXP  CEdgeStrucCollection
{
public:
	CEdgeStrucCollection(void);
	~CEdgeStrucCollection(void);

	//������뽻����ϵ����
	//�ܶ����������ʼʱ���԰�ȫ������������,�����������Ų��ٶ�Ӧ
	//���Դ˵����ͽṹ�ܵ������Բ����
	int m_nPoint;  //����m_pPointConnect����������˱༭�����µĵ����ɣ�����m_pPointConnectʱ��Ҫ�ж�Խ������
	CPointEdgeProp *m_pPointConnect;  //����������,�����е�����
	//�����Ӱ�������
	int m_iGenType;
	struct sWallLc
	{
		int idWall;
		float fRatio1;
		float X1min;float X1max;float Y1min;float Y1max;float Z1min;float Z1max;
		float fRatio2;
		float X2min;float X2max;float Y2min;float Y2max;float Z2min;float Z2max;
		sWallLc(){memset(this,0,sizeof(sWallLc));};
	} *m_pWallc;
	 void GetWallRebarLayer(int Wallid,int iElmType,int Elmid,double *pThick);
	 void GetWallRebarLayer(int Wallid,int iElmType,int Elmid,float *pThick);
public:
	//������Ե������iRebarType--�����㷽ʽ,fThickPrec--��ȼ����λ����
	BOOL CreateConstraint(EDGE_REBAR_AREA_TYPE iRebarType,float fThickPrec,char chMothed=0,float fMinLen=1.0f, EDGE_REBAR_GENERATE_METHOD m_iReGen = EDGE_REBAR_NONE);
	BOOL OnWallGenerateConstraint(const int nSel, const int* pSelNames);
	//���ӱ�Ե������ǽ
	BOOL ConnectWall();

	void Clear(void);

	CEdgeStrucCollection & operator=(const CEdgeStrucCollection &edge)
	{
		if(this==&edge) return *this;

		Clear();

		m_nPoint=edge.m_nPoint;

		m_pPointConnect=new CPointEdgeProp[edge.m_nPoint];

		for(int i=0;i<edge.m_nPoint;i++)
		{
			m_pPointConnect[i]=edge.m_pPointConnect[i];
		}

		return *this;
	}

	//���ݱ�Ե������id�õ����Ա�m_pPointConnect�����
	int GetIndexByBeamid(int beamid)
	{
		int idProp=-1;

		for(int k=0;k<m_nPoint;k++)
		{
			CPointEdgeProp &prop=m_pPointConnect[k];
			if(!prop.IsValid()) continue;
			for(int j=0;j<prop.nBeam;j++)
			{
				if(prop.pBeamID[j]==beamid)
				{
					idProp=k;
					break;
				}
			}
			if(idProp!=-1) break;
		}
		return idProp;
	}

	void Renew(int nPoint)
	{
		if(nPoint<=m_nPoint) return;
		CPointEdgeProp *newprop=new CPointEdgeProp[nPoint];
		if(!newprop) return;
		for (int i=0;i<nPoint;i++)
		{
			newprop[i].Clear();
			if(i>=m_nPoint) break;
			newprop[i]=m_pPointConnect[i];
		}
		delete[] m_pPointConnect;
		m_pPointConnect=newprop;
		m_nPoint=nPoint;
	}

	BOOL Read(CASCFile &fin,int idfPoint,CSectionCollection &cSection,CArray<CBeamStruc,CBeamStruc&> &aBeam,
		CArray<CLine,CLine&> &aLine,CArray<CVertex,CVertex&>&aVex);
	BOOL Write(CASCFile &fout,int idfPoint);
	BOOL Write2020(CASCFile &fout,int idfPoint);

	//�����Ϣ��д
	BOOL ReadDesignInfo(CASCFile &fin,int idfPoint,CArray<CBeamStruc,CBeamStruc&> &aBeam);
	BOOL WriteDesignInfo(CASCFile &fout,int idfPoint);
	BOOL WriteDesignInfo2020(CASCFile &fout,int idfPoint);

private:
	BOOL AddPointConnect(int idVex1,int idVex2,int idWall); //�Ǽ�һ��ǽ����Ϣ������˫�������ϵ,���㷽��ǣ���¼��Ч���������Ѵ����򷵻�FALSE
	int TraceFarPoint(int idVex,float ang);  	//idVex--��ǰ�㣬�ݹ�Ѱ����Զ�˵�,���ݷ������ͬ��ԭ�򣬷�����Զ�㣬������idVex

	//��x0,y0�㴴����Ե��������������Ӧ�Ľ�����Ϣ��widthΪ�����ȣ����÷��ֹܣ���areaΪ���������angleΪ��ȫ������X��ת��
	//angleΪ��ת�����,����ȡǽ�ķ����
	//Ac--�������������
	//fAs--PKPM����������(m2)
	//fThickPrec--��ȼ����λ����
	void AddConstraint(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,list<int> &vLines,float width,float Ac,float angle,float fThickPrec); 

	void AddConstraints(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,float fLcMin,float width,float Ac,float fThickPrec); 
	void AddConstraintsWithNoBox(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,float Ac,int iType=1); 
	void AddEdge(int idProp,int idPoint,float area,float width,float fThickPrec,int iStory,float angle,int iWall);
	//����Լ�������ȣ���������Ƿ��ص������ص����ȡ�����һ��
	//idVex1-��id
	static void CheckOverLap(int idVex1);

};
