#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

//���� ���淽ʽ�ο�PDB V4��ʽ
/*
LTYPE= 1:  B= a,Fx  : x��������
LTYPE= 2:  B= a,Fy  : y��������
LTYPE= 3:  B= a,Fz  : z��������
LTYPE= 4:  B= a,Mx  : x�����о�
LTYPE= 5:  B= a,My  : y�����о�
LTYPE= 6:  B= a,Mz  : z�����о�

LTYPE= 7:  B=a,b,qax,qbx : �������Էֲ���
LTYPE= 8:  B=a,b,qay,qby : y�������ηֲ���
LTYPE= 9:  B=a,b,qaz,qbz : z�������ηֲ���
LTYPE=10:  B= a,b,qy      : y�������ηֲ���
LTYPE=11:  B= a,b,qz      : z�������ηֲ���

LTYPE=12:  B= ALF,t       : ��������
LTYPE=13:  B= ALF,t       : y���¶��ݶ�
LTYPE=14:  B= ALF,t       : z���¶��ݶ�

LTYPE=15:  B= P,N,E0,EN,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xyƽ��ԤӦ������(�ֶ�����)
LTYPE=16:  B= P,N,E0,EN,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xzƽ��ԤӦ������(�ֶ�����)
LTYPE=17:  B= P,N,E0,EN,Thita0,{(Xi,Ei),i=1,N-1},AP,FPTK,EP !Nmax=5,MAXPAR=16
xyƽ��ԤӦ������(�ֶ�������)
LTYPE=18:  B= P,N,E0,EN,Thita0,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xzƽ��ԤӦ������(�ֶ�������)
LTYPE=19:  B=a,Fx,Fy,Fz,Mx,My,Mz

ALL THE LOADS OF TYPE 1 TO 19 ARE DEFINED IN LOCAL COOR.

LTYPE=20:  B=a,Fx,Fy,Fz,Mx,My,Mz                        !IN GLOBAL COOR.
LTYPE=21:  B=a,b,Qxa,Qya,Qza,Qxb,Qyb,Qzb                !IN GLOBAL COOR.
LTYPE=22:  B=a,b,c,Qxa,Qya,Qza,Qxb,Qyb,Qzb,Qxc,Qyc,Qzc  !IN GLOBAL COOR.
LTYPE=23:  B=a,b,c,Qxa,Qya,Qza,Qxb,Qyb,Qzb,Qxc,Qyc,Qzc  !IN LOCAL  COOR.
LTYPE=24:  B=N,(ai,qxi,qyi,qzi,mxi,myi,mzi,i=1,N)       !LOCAL  COOR.
LTYPE=25:  B=N,(ai,qxi,qyi,qzi,mxi,myi,mzi,i=1,N)       !GLOBAL COOR.
LTYPE=26:  B=N,(ai,qxi,qyi,qzi,mxi,myi,mzi,i=1,N)       !LOCAL  COOR.+(0,1)
LTYPE=27:  B=N,(ai,qxi,qyi,qzi,mxi,myi,mzi,i=1,N)       !GLOBAL COOR.+(0,1)p

LTYPE=28:  B=Q,Q1,Q2,Q3,Q4 IN LOCAL COOR. X
LTYPE=29:  B=Q,Q1,Q2,Q3,Q4 IN LOCAL COOR. Y
LTYPE=30:  B=Q,Q1,Q2,Q3,Q4 IN LOCAL COOR. Z
LTYPE=31:  B=Q,Q1,Q2,Q3,Q4 IN GLOBAL COOR. X
LTYPE=32:  B=Q,Q1,Q2,Q3,Q4 IN GLOBAL COOR. Y
LTYPE=33:  B=Q,Q1,Q2,Q3,Q4 IN GLOBAL COOR. Z

LTYPE=34:  B=t //�����¶�
LTYPE=35:  B=d //һά������Ӧ��
LTYPE=36:  B=dx,dy //��ά������Ӧ��

LTYPE=37:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. X  ����iTypeΪ����ص��ɷ�ʽ
LTYPE=38:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. Y  ����iTypeΪ����ص��ɷ�ʽ
LTYPE=39:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. Z  ����iTypeΪ����ص��ɷ�ʽ
LTYPE=40:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. X ����iTypeΪ����ص��ɷ�ʽ
LTYPE=41:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. Y ����iTypeΪ����ص��ɷ�ʽ
LTYPE=42:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. Z ����iTypeΪ����ص��ɷ�ʽ 

//LTYPE 21  �ֿ���ʾ
LTYPE=43:  B=a,b,Qxa,Qxb        !IN GLOBAL COOR.
LTYPE=44:  B=a,b,Qya,Qyb        !IN GLOBAL COOR.
LTYPE=45:  B=a,b,Qza,Qzb        !IN GLOBAL COOR.

LTYPE=46:  B=d //һά����������
LTYPE=47:  B=dx,dy //��ά����������

LTYPE=201:  B=iLoadType,iDir,iFunc,fArr,fScale//��������,���÷���,ʱ�̺���,����ʱ��,��������    �ڵ㶯����
LTYPE=202:  B=iStaticLoad,iFunc,fArr,fScale//��������Id ʱ�̺���,����ʱ��,��������    ʱ�����

LTYPE=301:  B=iLoadType,iDir,iFunc,fArr,fScale,iCOOR //�涯���� �ֲ�����ϵ
LTYPE=302:  B=iLoadType,iDir,iFunc,fArr,fScale,iCOOR //�涯���� ȫ������ϵ
*/

class _SSG_DLLIMPEXP CLoad
{
public:
	CLoad(void);
	CLoad(int iType);
	CLoad(CLoad &ld)
	{
		*this=ld;
	}

	~CLoad(){Clear();}

	int id;
	int iType;			    //��������
	bool bProj;			//����ͶӰ���������൱�ھ�����
	bool bRelDis;		//�Ƿ���Ծ���
	int nData;				//��������
	float *pData;			//��������
	CString sName;	//��������
	CString sMemo;  //˵��

	CLoad& operator=(const CLoad& ld);
	CLoad& operator+(const CLoad& ld);
	BOOL operator==(const CLoad& ld);
	BOOL bSimilarForce(const CLoad& ld);
	BOOL bInvalid();
	BOOL bInvalidDyna();

	BOOL Read(CASCFile &fin);
	void Write(CFile &fout);
	CString &AutoName(void);
	void	Clear();
	//
	BOOL GetNodeLoad(float *fload);
	static int GetLoadDataNum(int iType);
	//�Ƿ���������ϵ
	bool bGlobalLoad();

	static float ErrForce;
	static float ErrStrain;
};

class _SSG_DLLIMPEXP CLoadSet
{
public:
	CLoadSet(){;}
	CLoadSet(const CLoadSet &load) 
	{
		*this=load;
	};
	~CLoadSet(){RemoveAll();}

	int Append(CLoad *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aLoadPtr.GetCount();}

	CLoad *GetAt(int i) {return aLoadPtr.GetAt(i);}

	CLoad *operator[](int i) {return aLoadPtr[i];}

	CLoad *GetLoad(int id) const;  //���ݸ�����Load id����Loadָ��

	void SetAt(int i,CLoad *load) {aLoadPtr[i]=load;}

	CLoadSet& operator=(const CLoadSet&load);

	void Write(CFile &fout); 
	void Read(CASCFile &fin);
private:
	CArray<CLoad*,CLoad*> aLoadPtr; //���ع�����ϼ���
};



///////////////////////////////////////////////////////// ��������///////////////////////////////////////////////////////////////////////////////
//class _SSG_DLLIMPEXP CDynaLoad
//{
//public:
//	CDynaLoad(void);
//	CDynaLoad(CDynaLoad &ld)
//	{
//		*this=ld;
//	}
//	~CDynaLoad(){Clear();}
//
//	char iType;			//�������� 0 �ڵ㶯���� 1 ʱ�����
//	int iFunc;				//ʱ�̺���
//	float fArr;				//����ʱ��
//	float fScale;			//��������
//	int iDir[6];				//���÷���
//
//	CDynaLoad& operator=(const CDynaLoad& dyld);
//	BOOL operator==(const CDynaLoad& dyld);
//	BOOL bInvalid();
//
//	BOOL Read(CASCFile &fin);
//	void Write(CFile &fout);
//	CString &AutoName(void);
//	void	Clear();
//	//
//	BOOL GetNodeLoad(float *fload);
//	static int GetLoadDataNum(int iType);
//private:
//	int id;					//����id
//	CString sName;		//��������
//	CString sMemo;	//˵��
//};
