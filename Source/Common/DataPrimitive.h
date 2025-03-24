#pragma once

#include <afxtempl.h>
#include <vector>
#include <map>

#include "SysPara.h"
#include "HeadDefine.h"
#include "ASCFile.h"

class CLine;

using namespace std;

//线与多边形相交结果
struct LINE_CROSS_POLY
{
	//type--相交类型：
	//-1 -- 其它错误
	//0--不相交，包括共面和不共面
	//1--线交于多边形1个顶点，包括共面和不共面
	//共面相交：2--线与多边形相交于2个点，3--线与多边形边线(部分)重合；6--线在多边形内
	//不共面相交：4--线与多边形边界线相交(由于在建立板构件之前就建立了结构线，并处理了线段之间的相交情况，因此该线段一般不可能交于边界线的中间点)，
	//			  5--线与多边形内部相交
	int type; 
	int pointid1;  //交点ID1，type=1,2有效
	int pointid2;  //交点ID2，type=2有效
	int plateid1,plateid2; //新的多边形ID
};

struct CROSS_POINT
{
	int id;
	float t;
	int iLine;
	CROSS_POINT *pPair;

	bool operator < (const CROSS_POINT& cp ) const //升序排序时必须写的函数
	{
		return t < cp.t;
	}
};

struct CROSS_PLATE
{
	int plateid;  //面构件ID
	int crossvexid;  //交叉点

	bool operator == (const CROSS_PLATE& cp)
	{
		return (plateid==cp.plateid) && (crossvexid==cp.crossvexid);
	};

	bool operator < (const CROSS_PLATE& cp) //升序排序时必须写的函数
	{
		if(plateid < cp.plateid) 
			return TRUE;
		else if(plateid == cp.plateid) 
			return crossvexid < cp.crossvexid;
		else
			return FALSE;
	};
};

//楼层范围结构
struct STORY_RANGE
{
	int iStoryMin;
	int iStoryMax; 
};

//层间过渡的竖向构件梁单元
struct BEAM_CONN_LAYER
{
	int idBeam;  //单元编号
	int idNode;  //局部结点序号，0-1
};

//层间过渡的壳单元
struct SHELL_CONN_LAYER
{
	int idShell;  //壳单元编号
	int idNode1;  //与楼层相连的局部编号,三角形0~2，四边形0~3
	int idNode2;  //与楼层相连的局部编号,三角形1~2，四边形1~3，-1表示不相连
};

//统计各类型数量
struct STRUCT_COUNT
{
	int nPoint   	;       //点
	int nLine    	;       //结构线
	int nBeam    	;       //梁
	int nPillar  	;       //柱
	int nBracing 	;       //斜撑
	int nEdge		;       //约束边缘构件
	int nHidebeam   ;       //虚梁
	int nLongirebar ;       //连梁纵筋
	int nLink ;       //阻尼器	//乔保娟 2015.5.21
	int nPlate 		;       //板
	int nWall  		;       //墙
	int nGuides    	;       //辅助线
};

//边界点和边界线关联关系
struct BND_NODE_LINE
{
	int nline;
	int line[2];  //线编号，最多2个
};

//结构名称及关键字
struct STRUCT_KEYWORD
{
	int iType;
	CString sTitle;
	CString sKeyword;

};

enum LOAD_TYPE
{
	LOAD_DEAD=0,		//0-梁上分布附加恒载；
	LOAD_LIVE=1,		//1-梁上分布附加活载；
	LOAD_SLAB_DEAD=2,	//2-板附加恒载传导于梁上分布荷载；
	LOAD_SLAB_LIVE=3,	//3-板附加活载传导于梁上分布荷载；
	LOAD_SLAB_WEIGHT=4,	//4-板自重传导于梁上分布荷载
};

//点到线构件(包括结构线、梁、柱等)的连接关系，二叉树
struct _SSG_DLLIMPEXP PT2LINESTRUCT
{
	PT2LINESTRUCT(void) {conn_vex1=conn_vex2=conn_beam1=conn_beam2=-1;}

	int conn_beam1,conn_vex1; //相连的第一个线构件的id和点号，以及线构件楼层号
	int conn_beam2,conn_vex2; //相连的第二个线构件的id和点号，以及线构件楼层号

	void Append(int beam, int vex)
	{
		if(conn_beam1==-1)
		{
			conn_beam1=beam;
			conn_vex1=vex;
		}
		else
		{
			conn_beam2=beam;
			conn_vex2=vex;
		}
	}
};

//一个点到两条线段的关联，-1为无效ID，用于多边形边界
struct _SSG_DLLIMPEXP PT2LINE
{
	PT2LINE(void) {iVexID=-1;iLeftLineID=iRightLineID=-1;}
	int iVexID; //点ID
	int iLeftLineID,iRightLineID;  //左边的线段ID，右边的线段ID
};

//组合构件
struct _SSG_DLLIMPEXP COMBO_STRUCT
{
	COMBO_STRUCT(void) {sName=L"";}
	~COMBO_STRUCT() {Clear();}
	void Clear(void) {vIDG.clear();sName=L"";}
	CString sName;
	vector<int> vIDG;
};

struct _SSG_DLLIMPEXP STRUCT_PROPERTY1
{
	int iCode;  //属性代码=数组元素序号，不可随意更改
	CString sName;  //属性名称
	CString sUnit;  //属性单位
	BOOL bBeam,bPillar,bBrace,bPlate,bWall,bBeamWall;  //是否允许某类构件使用
	int iDataType; //0-float,1-CString
};

//结构线剖分网格所生成的子线段
struct _SSG_DLLIMPEXP SUB_LINE
{
	int		nSubLine;	//初始化为0，表示没有划分子线段
	CLine	*pSubLine;	//子线段数组，初始化为NULL
};

//结构线是否被梁和墙用到
struct _SSG_DLLIMPEXP LINE_USED
{
	LINE_USED(void)
		:bBeam(FALSE)
		, bPillar(FALSE)
		, bWall(FALSE)
		, bBeamWall(FALSE)
		, bAlong(TRUE)
		, bLink(FALSE)
		, bAnti(FALSE)
		, fWeight(0)
		, fMeshRatio(1.f)
	{
	}
	BOOL bBeam;    //是否被梁用到
	BOOL bPillar;  //是否被柱用到
	BOOL bWall;    //是否被墙用到，不管墙与结构线是否同楼层，墙梁不算墙
	BOOL bBeamWall;//是否被墙梁用到，不管墙梁与结构线是否同楼层
	BOOL bAlong;   //是否仅仅被两端铰接的线构件使用
	BOOL bLink;    //是否被一般连接使用
	BOOL bAnti;    //是否被两端铰接的线构件使用
	float	fWeight;	//加密累计权重
	float	fMeshRatio;	//网格累计加密系数
};

//类定义------------------------------------------------------------------------


//图元属性
class _SSG_DLLIMPEXP CPrimitiveProp
{
public:
	CPrimitiveProp(void);
	CPrimitiveProp(DWORD clc, int iStory = 0);

	int idmStory;     //楼层IDF=IDM,从0开始编号,0为地面
	int iStage;        //施工阶段,从0开始编号
	int iTower;		//分块号，塔号，从0开始编号

	//临时数据,不保存文件
	union
	{
		DWORD dwColor;  //颜色
		unsigned char RGBA[4];
	};

	int tag;			//tag 标记
	unsigned char iStatus;  //状态标志，0无效，1-正常，2-选中，3-参考点(目前只对点有效)
	CString sComments;  //用于显示的说明文字,由程序随时更新

	CPrimitiveProp & operator=(const CPrimitiveProp &prop)
	{
		if(this==&prop) return *this;

		idmStory=prop.idmStory; 
		iStage=prop.iStage;
		iTower=prop.iTower;
		dwColor=prop.dwColor;
		iStatus=prop.iStatus;  
		//iStatus=1; //被复制的图元自动变成有效2012-10-25
		sComments=prop.sComments;
		tag = prop.tag;

		return *this;
	}

	void Clear();

	virtual BOOL Read(CASCFile &fin);   
	virtual BOOL Write(CASCFile &fout);
	virtual BOOL Write2020(CASCFile &fout);

	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);

	virtual BOOL IsValid(void) const;
};
