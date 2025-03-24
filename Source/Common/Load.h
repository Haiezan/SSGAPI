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

LTYPE=34:  B=t //构件温度
LTYPE=35:  B=d //一维构件初应变
LTYPE=36:  B=dx,dy //二维构件初应变

LTYPE=37:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. X  其中iType为面荷载导荷方式
LTYPE=38:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. Y  其中iType为面荷载导荷方式
LTYPE=39:  B=Q,Q1,Q2,Q3,Q4,iType IN LOCAL COOR. Z  其中iType为面荷载导荷方式
LTYPE=40:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. X 其中iType为面荷载导荷方式
LTYPE=41:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. Y 其中iType为面荷载导荷方式
LTYPE=42:  B=Q,Q1,Q2,Q3,Q4,iType IN GLOBAL COOR. Z 其中iType为面荷载导荷方式 

//LTYPE 21  分开表示
LTYPE=43:  B=a,b,Qxa,Qxb        !IN GLOBAL COOR.
LTYPE=44:  B=a,b,Qya,Qyb        !IN GLOBAL COOR.
LTYPE=45:  B=a,b,Qza,Qzb        !IN GLOBAL COOR.

LTYPE=46:  B=d //一维构件初拉力
LTYPE=47:  B=dx,dy //二维构件初拉力

LTYPE=201:  B=iLoadType,iDir,iFunc,fArr,fScale//荷载类型,作用方向,时程函数,到达时间,荷载缩放    节点动荷载
LTYPE=202:  B=iStaticLoad,iFunc,fArr,fScale//静力工况Id 时程函数,到达时间,荷载缩放    时变荷载

LTYPE=301:  B=iLoadType,iDir,iFunc,fArr,fScale,iCOOR //面动荷载 局部坐标系
LTYPE=302:  B=iLoadType,iDir,iFunc,fArr,fScale,iCOOR //面动荷载 全局坐标系
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
	int iType;			    //荷载类型
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
	BOOL bInvalidDyna();

	BOOL Read(CASCFile &fin);
	void Write(CFile &fout);
	CString &AutoName(void);
	void	Clear();
	//
	BOOL GetNodeLoad(float *fload);
	static int GetLoadDataNum(int iType);
	//是否整体坐标系
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

	CLoad *GetLoad(int id) const;  //根据给定的Load id返回Load指针

	void SetAt(int i,CLoad *load) {aLoadPtr[i]=load;}

	CLoadSet& operator=(const CLoadSet&load);

	void Write(CFile &fout); 
	void Read(CASCFile &fin);
private:
	CArray<CLoad*,CLoad*> aLoadPtr; //荷载工况组合集合
};



///////////////////////////////////////////////////////// 动力荷载///////////////////////////////////////////////////////////////////////////////
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
//	char iType;			//荷载类型 0 节点动荷载 1 时变荷载
//	int iFunc;				//时程函数
//	float fArr;				//到达时间
//	float fScale;			//荷载缩放
//	int iDir[6];				//作用方向
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
//	int id;					//荷载id
//	CString sName;		//荷载名称
//	CString sMemo;	//说明
//};
