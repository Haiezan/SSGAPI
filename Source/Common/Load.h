#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"

//荷载 保存方式参考PDB V4格式
/*
LTYPE= 1:  B= a,Fx  : x方向集中力
LTYPE= 2:  B= a,Fy  : y方向集中力
LTYPE= 3:  B= a,Fz  : z方向集中力
LTYPE= 4:  B= a,Mx  : x方向集中矩
LTYPE= 5:  B= a,My  : y方向集中矩
LTYPE= 6:  B= a,Mz  : z方向集中矩

LTYPE= 7:  B=a,b,qax,qbx : 轴向线性分布力
LTYPE= 8:  B=a,b,qay,qby : y方向梯形分布力
LTYPE= 9:  B=a,b,qaz,qbz : z方向梯形分布力
LTYPE=10:  B= a,b,qy      : y方向梯形分布力
LTYPE=11:  B= a,b,qz      : z方向梯形分布力

LTYPE=12:  B= ALF,t       : 均匀升温
LTYPE=13:  B= ALF,t       : y向温度梯度
LTYPE=14:  B= ALF,t       : z向温度梯度

LTYPE=15:  B= P,N,E0,EN,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xy平面预应力荷载(分段折线)
LTYPE=16:  B= P,N,E0,EN,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xz平面预应力荷载(分段折线)
LTYPE=17:  B= P,N,E0,EN,Thita0,{(Xi,Ei),i=1,N-1},AP,FPTK,EP !Nmax=5,MAXPAR=16
xy平面预应力荷载(分段抛物线)
LTYPE=18:  B= P,N,E0,EN,Thita0,{(Xi,Ei),i=1,N-1},AP,FPTK,EP
xz平面预应力荷载(分段抛物线)
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
	char iType;			//荷载类型
	bool bProj;			//考虑投影：不考虑相当于均布力
	bool bRelDis;		//是否相对距离
	int nData;				//参数个数
	float *pData;			//荷载数据
	CString sName;	//荷载名称
	CString sMemo;  //说明

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

	CLoad *GetLoad(int id) const;  //根据给定的Load id返回Load指针

	void SetAt(int i,CLoad *load) {aLoadPtr[i]=load;}

	CLoadSet& operator=(const CLoadSet&load);

	void Write(CFile &fout); 
	void Read(CASCFile &fin);
private:
	CArray<CLoad*,CLoad*> aLoadPtr; //荷载工况组合集合
};
