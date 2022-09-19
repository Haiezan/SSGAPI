#pragma once

#include "data.h"
#include "Vector4.h"

//#define TRUE     1
//#define FALSE    0

struct POINT_LIST 
{
	union 
	{
		float x[4];  //0-间距d,1-坐标x，2-坐标y，3-坐标z
		struct 
		{
			union
			{
				float dist;
				float angle;
			};
			float x0;
			float y0;
			float z0;
		};
	};
	int bnd,next; //bnd--该点所在的边界线号（>0为边界点，0为内部点），next--邻接的下一个点号
	int m;  //初始化为next值
};

struct LINE_LIST
{
	int vexid[2];	//线的端点，如果是边界点，按照右手定则排序,编码从1开始
	int isp;		//可供使用的次数,边界线初始为1，内部线初始为2
	int neighbor;	//相邻三角形编码，编码从1开始,只记录最后一个邻居
};

struct ELEM_LIST 
{
	int n[4];  //n[1],n[2],n[3]为结点编码, n[0]--原来所在的三角形编号或新插入点的编号
	int t[4],nt; //t--相邻三角形编号([1]~[3])，nt--相邻三角形个数,t[0]：0--三角形有效，1--三角形无效
	POINT_LIST xc;  //外接圆圆心
	float R;  //外接圆半径的平方
};

struct BOUNDARY_INDEX 
{
	int n1,n2;
};

struct INTEGER_POINT 
{
	long x[3];
};

//每个格网块包含的线段
struct GRID_LINE
{
	int nLine;//线段数
	int id[100];//线段ID，每个块中最多100个线段
};

//XY平面内三角网生长法形成大三角形，支持多联通域,pBndNode
void BigTri(int nBndPoint,const Vector4 *pBndNode,int &nTri,ELEM_LIST *pTri);

//计算线段剖分数,len--线段长度，size_ratio--子段参考长度的倒数,fMinSize--最小控制尺寸
int GetSegmentsNum(float len,float size_ratio,float fMinSize);

//2D三角形网格自动生成,支持复连通域和凹多边形,支持3D平面
class CMeshingTri
{
public:
	CMeshingTri(void);
	~CMeshingTri(void);

	CMeshingTri & operator=(const CMeshingTri & mesh)
	{
		if(this==&mesh) return *this;

		ASSERT(FALSE);

		return *this;
	}

	//生成空间多边形内三角形网格
	//输入: nbndpoint--多边形边界点数,pBndPoint--边界点3D坐标
	//输出: nnode--结点数,ntri--单元数，pvNode--结点坐标（调用程序维护此内存），ptri--单元结点编码（调用程序维护此内存），编码从0开始
	BOOL AutoTriangle3D(const Vector4 &c0,const Vector4 &u,const Vector4 &v,const Vector4 &w,float MinElmSize,float alpha0,float beta0,
		int nbndpoint,Vector4 *pBndPoint,int &nnode,Vector4 *&pvNode,int &ntri,CTriangleElm *&ptri,int id=0);
		
	//多连通域生成网格程序
	//输入参数：
	//nBoundary--边界线数
	//pBoundary--边界线数组(每条边界的结点编码范围),边界点编号从0开始
	//nbndpoint--边界点数
	//pBndX,pBndY,pBndZ边界点局部坐标数组
	//fBndDist--边界点间距，为NULL时该程序自动计算
	//输出参数：
	//nnode--结点数
	//pPointCoor--结点坐标，下标从0开始，（调用程序维护此内存）
	//ntri--单元数
	//pTri--单元结点编码，编码从0开始，下标从0开始，（调用程序维护此内存）
	void AutoTriangle2D_SCD(float MinElmSize,float alpha0,float beta0,int nbndpoint,float *pBndX,float *pBndY,float *pBndZ,
		int &npoint,POINT_LIST *pPointCoor,int &ntri,ELEM_LIST *ptri);
	void AutoTriangle2D_MCD(float MinElmSize,float alpha0,float beta0,int nBoundary,const BOUNDARY_INDEX *pBoundary,int nbndpoint,
		const float *pBndX,const float *pBndY,const float *pBndZ,const float *fBndDist,
			   int &nnode,POINT_LIST *pPointCoor,
			   int &ntri,ELEM_LIST *pTri);
	//void TriangleMeshing2D();

	bool bUseBigTriangle;  //是否使用大三角形分区算法
	int ID; //为了显示信息,从1开始编号
	int nadapt; /*default number of adaptation cycles*/
	int smoothing; /*default flag for coordinate smoothing*/

	//划分三维结构化网格，要求区域为四边形，并且对边结点分别相等n3=n1,n4=n2,pBndPoint从n1边开始存储
	BOOL StructuredTriangle3D(int n1,int n2,int nBndPoint,int iStart,Vector4 *pBndPoint,int &nnode,Vector4 *&pvNode,int &ntri,CTriangleElm *&pTriElm);
	void LaplaceSmoothing(void);


protected:
	int extra; /* extra nodes to be put in case of missing edges*/ 
	int pivot; //当前正在处理的三角形编号
	int bndextra; //附加的边界点数，逐点插入=4，三角生长=0

	int nNode,nTri; //总结点数，总单元数
	int nBndPoint;    //边界点数(对于bUseBigTriangle=false，nBndPointExt=nBndPoint)
	int nBndPointExt; //扩展的边界点数(对于bUseBigTriangle=false，nBndPointExt=nBndPoint+4)
	int NSE,NewE,NE1,nBndLine,MNP,nblocks/*,nbnd*/;
	POINT_LIST    *pNode; //结点数组，包括初始的外包矩形顶点
	ELEM_LIST *pTri; //三角形单元数组
	int      suf[Sys_SUFFERED+1];
	ELEM_LIST ntc[3*Sys_SUFFERED+1];
	BOUNDARY_INDEX bindx[10];
	int Near[13],NNEARS;
	float MinElmSize,alpha,beta; //最小单元尺寸，小于该尺寸的单元不再细分，alpha,beta细分控制参数(0-1之间)
	POINT_LIST max,min/*,a,b*/;
	int sufdel[Sys_SUFFERED];

	/* Implementation of Functions */

	inline void Load_Triangle(int,int,int,int,int);
	POINT_LIST Vector(const POINT_LIST &p,const POINT_LIST &q);
	float Cross(const POINT_LIST&,const POINT_LIST&);
	float Dot(const POINT_LIST&,const POINT_LIST&);
	int Node_In(int,int);
	void Add_Boundary_Node(int);
	short InCircleTest(const POINT_LIST&,const ELEM_LIST&);
	void Compute_Circumcircle(ELEM_LIST &);
	
	//三种初始网格生成方法
	void Initialize2Tri(void);
	void InitializeLoopBigTri(void);
	void InitializeBigTri(void);
	
	void Suffered(int,int);
	void Construct_New_Triangles(int);
	int Newplaces(int);
	BOOL Engine(int);
	void Construct_New_Neighbors1(void);
	BOOL Construct_New_Neighbors2(void);
	int Find_Missing_Edges(void);
	void Set_Next_Fields(void);  //设置点的相邻域
	long Crossi(INTEGER_POINT p1,INTEGER_POINT p2);
	void Remove_Unwanted_Triangles(void);
	void Near_Nodes(int tno,int *nn);
	void Compute_Centroids(int tno,float *xc,float *yc,float *zc);
	void Smooth(void);
	void Insert_Nodes(/*float alpha,float beta*/);
};

//生成四边形网格
class CMeshingQuad
{
public:
	//ElmSize--单元特征尺寸						
	//max_quad_angle--最大四边形单元内角（度）	
	//max_tri_angle--最大三角形单元内角（度）	
	CMeshingQuad(float ElmSize,float MaxQuadAngle,float MaxTriAngle,int nsmooth) 
	{
		fElmSize=ElmSize;
		fMinElmSize=fElmSize*0.1f;
		fMaxQuadAngle=MaxQuadAngle;
		fMaxTriAngle=MaxTriAngle;
		nSmooth=nsmooth;

		nVex=0;
		nTri=0;
		nQuad=0;
		fDist=0;  
		nGridX=0; 
		nGridY=0; 

		pVex3D=NULL;
		pVexLocal=NULL;
		pTriangle=NULL;
		pQuad=NULL;
		pGrid=NULL;
	}

	~CMeshingQuad()
	{
		delete[] pVex3D;        pVex3D=NULL;
		delete[] pVexLocal;        pVexLocal=NULL;
		delete[] pQuad;			pQuad=NULL;
		delete[] pTriangle;		pTriangle=NULL;
		delete[] pGrid;	pGrid=NULL;
	}

	CMeshingQuad & operator=(const CMeshingQuad & mesh)
	{
		if(this==&mesh) return *this;

		ASSERT(FALSE);

		return *this;
	}

protected:
	int nVex;
	int nTri;
	int nQuad;

	float fMinX,fMaxX,fMinY,fMaxY;
	float fDist;  //区域格网间距
	int nGridX;  //X方向格网块数
	int nGridY;  //Y方向格网块数
	int nBndPoint; //边界点数

	float fElmSize;  //正常单元尺寸
	float fMinElmSize; //最小单元尺寸,合并点的最大距离,小于该值的点距不能作为单元的边,可能会生成网格不正常
	float fMaxQuadAngle;
	float fMaxTriAngle;
	int nSmooth;

	Vector4 *pVex3D;  //3D坐标
	Vector4 *pVexLocal;  //3D局部坐标
	CQuadElm *pQuad;
	CTriangleElm *pTriangle;
	GRID_LINE *pGrid;

	
public:
	//铺路法生成空间多边形内四结点四边形网格	
	//c0--面内局部坐标原点
	//u,v--面内局部坐标基矢量
	//nBndPoint--多边形边界点数
	//pBndPoint--边界点3D坐标			
	BOOL AutoQuad3D(const Vector4 &c0,const Vector4 &u,const Vector4 &v,const Vector4 &w,int nBndPoint,const Vector4 *pBndPoint);

	//铺路法生成单联通平面多边形内四结点四边形网格
	//nBndPoint--多边形边界点数
	//pvex2d--边界点2D坐标					
	BOOL AutoQuad2D_SCD(int nBndPoint,Vector4 *pvex2d);

	//划分三维结构化网格，要求区域为四边形，并且对边结点分别相等,n1-n4分别对应各条直线段的的结点数，n3=n1,n4=n2，  iStart--第一条直线段的起始点号
	BOOL StructuredQuad3D(int n1,int n2,int nBndPoint,int iStart,Vector4 *pBndPoint);

	//切边法划分三维非结构化网格，区域为凸多边形，iStart--第一条直线段的起始点号
	BOOL NonStructuredPoly3D(int nBndPoint,int iStart,Vector4 *pBndPoint);

	int GetNodeNum(void) const {return nVex;}
	Vector4 *GetVex3D(void) const {return pVex3D;}
	Vector4 *GetVexLocal(void) const {return pVexLocal;}

	int GetTriNum(void) const {return nTri;}
	CTriangleElm *GetTriPtr(void) const {return pTriangle;}

	int GetQuadNum(void) const {return nQuad;}
	CQuadElm *GetQuadPtr(void) const {return pQuad;}

protected:
	//计算边界线段夹角(度)
	//pvex2d为2D局部坐标，外边界线段方向沿逆时针方向，pAngle为结点处的线段夹角(度)
	//只使用XY坐标
	float GetAngle2D( int line1, int line2, const CLine * pLine, const Vector4 * pvex2d);

	void GetZoneRange2D(void);

	void AddLineToGrid(int iLine,const Vector4 &p1,const Vector4 &p2);
	void AddNewQuad( int n1, int n2, int n3, int n4,int &nLine,CLine *pLine);

	//判断局部平面内线段相交（只使用XY坐标），返回值：0不相交，1为两线段相交于1点、完全或部分重合，n -- 与n点接近或重合
	//应排除自身结点nExclude1,nExclude2
	int LineCross(int nExclude1,int nExclude2,Vector4 p1,Vector4 p2,const CLine *pLine);

	//计算3D线段是否相交
	//返回值：0不相交，1为两线段相交于1点，11,12,21,22--两条线有一个端点重合且不共线，-1两条线完全重合，-2两条线部分重合
	int VectorLineCross3D(const Vector4 &pa, const Vector4 &pb, const Vector4 &qa, const Vector4 &qb);
	void LaplaceSmoothing(int nBndPoint,Vector4 *pVex,int nloop);  //用到nVex,nQuad,nTri,pQuad,pTriangle,pVex为pVex2D或pVex3D，适用于二维和三维情况

	//拆分角度过大的四边形
	void SplitToTriangle(int &nLine, CLine *pLine,const Vector4 *pVex,int nDim);

	//合并共线的两个相邻三角形，nDim坐标维数
	void MergeTriangle( int &nLine, CLine *pLine,const Vector4 *pVex,int nDim);

};
