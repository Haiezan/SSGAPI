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
	char iType;			//��������
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

	BOOL Read(CASCFile &fin);
	void Write(CFile &fout);
	CString &AutoName(void);
	void	Clear();
	//
	BOOL GetNodeLoad(float *fload);
	static int GetLoadDataNum(int iType);
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