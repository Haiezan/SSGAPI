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
	EDGE_REBAR_AREA_IMPORT=0,	//采用导入配筋，遇到0时采用计算值
	EDGE_REBAR_AREA_COMPUTE=1,	//取规范计算值（配筋计算值Ac*ratio、按最小钢筋直径计算值asmin，两者最大）
	EDGE_REBAR_AREA_MAX=2,		//取4者最大值
};

enum EDGE_REBAR_GENERATE_METHOD
{
	EDGE_REBAR_NONE = -1,
	EDGE_REBAR_REGENERATE = 0,	//重新生成边缘构件
	EDGE_REBAR_SUPPLEMENT_GENERATION = 1,	// 补充生成边缘构件
};


class CVertex;
class CBeamStruc;
class CLine;

//边缘构件点属性，每个点可能有多个边缘构件，初始时按顶层结点创建，假设每个顶层结点都有可能创建边缘构件
//保存文件时可以清除无效的点,	所以此点和结构点不一定对应
class _SSG_DLLIMPEXP  CPointEdgeProp
{
public:
	CPointEdgeProp(void);
	~CPointEdgeProp(void);

	int nWalls;  //与此可能的边缘构件相连的墙分支数
	int nBeam;  //此顶点下的边缘构件数，同一楼层中，同一个顶点下可能有很多段结构线，因此也可能包含很多段边缘构件
	int *pBeamID;  //边缘构件IDM,注意：用malloc创建
	float fImportRebarArea;  //纵筋配筋面积,是指从PKPM导入的面积=max(构造配筋量, 规范最小配筋量)，用户不可修改。
	float fImportRebarRatio;  //纵筋配筋率,是指从PKPM导入的面积=max(构造配筋量, 规范最小配筋量)，除以阴影区面积,或者直接导入的配筋率，用户不可修改。
	float fRebarArea; //实际配筋量（m^2）,接口导入时按fImportRebarArea初始化, 否则为用户修改后数据，用户可交互修改
	float fVolumeStirrupRatio; //体积配箍率
	bool bYBZ; //是否约束边缘构件

	int idWall[Sys_Max_Connect_Wall];	//墙体IDM
	float fAng[Sys_Max_Connect_Wall];   //此点与idPoint构成的射线与X轴夹角，弧度，0-2*PI
	float lc[Sys_Max_Connect_Wall];		//约束区长度，从结点所在位置算起
	
	float fStirDist[Sys_Max_Connect_Wall],fStirDiam[Sys_Max_Connect_Wall]; //箍筋间距(m)，箍筋直径(m)
	int nStirL[Sys_Max_Connect_Wall],nStirW[Sys_Max_Connect_Wall]; //约束区长度方向箍筋肢数（缺省为0）,约束区厚度方向箍筋肢数（缺省为0）

    int nWallBeam[Sys_Max_Connect_Wall];//同nBeam这里是各墙肢上的
    int *pWallBeamID[Sys_Max_Connect_Wall];//同*pBeamID这里是各墙肢上的
	//临时数据
	int idPillar;  //端柱IDM，-1表示没有， 只有nWalls>0时才有效
	float fOverlapArea;  //重叠面积
	
	
	int idPoint[Sys_Max_Connect_Wall];  //墙体中除该点外最近端点的IDM，-1表示无效
	int idFarPoint[Sys_Max_Connect_Wall];  //所有共面关联墙体的最远端点的IDM，-1表示无效

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

	//计算有端柱的约束区尺寸，MainIndex为要计算的墙的序号，它为pt成员数组的下标,
	float GetPillarSize(int MainIndex);

	//得到各分支约束区长度,v1,v2为单只墙的两个顶点，单分支时有效
	void GetLC(const CVertex &v1,const CVertex &v2);

	//根据PKPM导入的数据得到初始指定配筋面积
	float GetPKPM_As(void);

	//计算总配筋区域面积
	float GetZoneArea( void);

	float GetSectionWidth(void);  //计算边缘构件截面宽度，正方形截面，取相关墙厚度的最大值

	//构造配筋区域面积A=Σ(各分支长度*各分支厚度)
	//构造配筋量=A*构造配筋率
	//实际配筋量=按不同方式计算
	//实际配筋率=实际配筋量/A

	
	//iType=0 约束边缘构件
	//iType=1 底部加强区以上构造边缘构件
	//iType=2 底部加强区构造边缘构件
	static float GetSysRatio(int iStory); //得到系统构造配筋率，与抗震等级和楼层边缘构件类型有关，单位1
	static float GetMinArea(int iStory); //得到最小配筋面积

};

class _SSG_DLLIMPEXP  CEdgeStrucCollection
{
public:
	CEdgeStrucCollection(void);
	~CEdgeStrucCollection(void);

	//交叉点与交叉点关系链表
	//总顶层点数，初始时可以按全部顶点数创建,保存后序号与点号不再对应
	//所以此点数和结构总点数可以不相等
	int m_nPoint;  //创建m_pPointConnect后如果进行了编辑，有新的点生成，访问m_pPointConnect时需要判断越界问题
	CPointEdgeProp *m_pPointConnect;  //关联点属性,按现有点索引
	//提高阴影区配筋率
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
	//创建边缘构件，iRebarType--配筋计算方式,fThickPrec--厚度级差，单位：米
	BOOL CreateConstraint(EDGE_REBAR_AREA_TYPE iRebarType,float fThickPrec,char chMothed=0,float fMinLen=1.0f, EDGE_REBAR_GENERATE_METHOD m_iReGen = EDGE_REBAR_NONE);
	BOOL OnWallGenerateConstraint(const int nSel, const int* pSelNames);
	//连接边缘构件和墙
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

	//根据边缘构件的id得到属性表m_pPointConnect的序号
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

	//设计信息读写
	BOOL ReadDesignInfo(CASCFile &fin,int idfPoint,CArray<CBeamStruc,CBeamStruc&> &aBeam);
	BOOL WriteDesignInfo(CASCFile &fout,int idfPoint);
	BOOL WriteDesignInfo2020(CASCFile &fout,int idfPoint);

private:
	BOOL AddPointConnect(int idVex1,int idVex2,int idWall); //登记一个墙体信息，加入双向关联关系,计算方向角，记录有效点数，若已存在则返回FALSE
	int TraceFarPoint(int idVex,float ang);  	//idVex--当前点，递归寻找最远端点,根据方向角相同的原则，返回最远点，可以是idVex

	//在x0,y0点创建边缘构件，并增加相应的截面信息，width为截面宽度（采用方钢管），area为截面面积，angle为绕全局坐标X轴转角
	//angle为旋转方向角,这里取墙的方向角
	//Ac--混凝土区域面积
	//fAs--PKPM导入的配筋量(m2)
	//fThickPrec--厚度级差，单位：米
	void AddConstraint(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,list<int> &vLines,float width,float Ac,float angle,float fThickPrec); 

	void AddConstraints(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,float fLcMin,float width,float Ac,float fThickPrec); 
	void AddConstraintsWithNoBox(EDGE_REBAR_AREA_TYPE iRebarType,int idProp,float Ac,int iType=1); 
	void AddEdge(int idProp,int idPoint,float area,float width,float fThickPrec,int iStory,float angle,int iWall);
	//计算约束区长度，监测区域是否重叠，若重叠则各取距离的一半
	//idVex1-点id
	static void CheckOverLap(int idVex1);

};
