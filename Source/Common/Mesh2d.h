#pragma once

#include "data.h"
#include "Vector4.h"

//#define TRUE     1
//#define FALSE    0

struct POINT_LIST 
{
	union 
	{
		float x[4];  //0-���d,1-����x��2-����y��3-����z
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
	int bnd,next; //bnd--�õ����ڵı߽��ߺţ�>0Ϊ�߽�㣬0Ϊ�ڲ��㣩��next--�ڽӵ���һ�����
	int m;  //��ʼ��Ϊnextֵ
};

struct LINE_LIST
{
	int vexid[2];	//�ߵĶ˵㣬����Ǳ߽�㣬�������ֶ�������,�����1��ʼ
	int isp;		//�ɹ�ʹ�õĴ���,�߽��߳�ʼΪ1���ڲ��߳�ʼΪ2
	int neighbor;	//���������α��룬�����1��ʼ,ֻ��¼���һ���ھ�
};

struct ELEM_LIST 
{
	int n[4];  //n[1],n[2],n[3]Ϊ������, n[0]--ԭ�����ڵ������α�Ż��²����ı��
	int t[4],nt; //t--���������α��([1]~[3])��nt--���������θ���,t[0]��0--��������Ч��1--��������Ч
	POINT_LIST xc;  //���ԲԲ��
	float R;  //���Բ�뾶��ƽ��
};

struct BOUNDARY_INDEX 
{
	int n1,n2;
};

struct INTEGER_POINT 
{
	long x[3];
};

//ÿ��������������߶�
struct GRID_LINE
{
	int nLine;//�߶���
	int id[100];//�߶�ID��ÿ���������100���߶�
};

//XYƽ�����������������γɴ������Σ�֧�ֶ���ͨ��,pBndNode
void BigTri(int nBndPoint,const Vector4 *pBndNode,int &nTri,ELEM_LIST *pTri);

//�����߶��ʷ���,len--�߶γ��ȣ�size_ratio--�Ӷβο����ȵĵ���,fMinSize--��С���Ƴߴ�
int GetSegmentsNum(float len,float size_ratio,float fMinSize);

//2D�����������Զ�����,֧�ָ���ͨ��Ͱ������,֧��3Dƽ��
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

	//���ɿռ�����������������
	//����: nbndpoint--����α߽����,pBndPoint--�߽��3D����
	//���: nnode--�����,ntri--��Ԫ����pvNode--������꣨���ó���ά�����ڴ棩��ptri--��Ԫ�����루���ó���ά�����ڴ棩�������0��ʼ
	BOOL AutoTriangle3D(const Vector4 &c0,const Vector4 &u,const Vector4 &v,const Vector4 &w,float MinElmSize,float alpha0,float beta0,
		int nbndpoint,Vector4 *pBndPoint,int &nnode,Vector4 *&pvNode,int &ntri,CTriangleElm *&ptri,int id=0);
		
	//����ͨ�������������
	//���������
	//nBoundary--�߽�����
	//pBoundary--�߽�������(ÿ���߽�Ľ����뷶Χ),�߽���Ŵ�0��ʼ
	//nbndpoint--�߽����
	//pBndX,pBndY,pBndZ�߽��ֲ���������
	//fBndDist--�߽���࣬ΪNULLʱ�ó����Զ�����
	//���������
	//nnode--�����
	//pPointCoor--������꣬�±��0��ʼ�������ó���ά�����ڴ棩
	//ntri--��Ԫ��
	//pTri--��Ԫ�����룬�����0��ʼ���±��0��ʼ�������ó���ά�����ڴ棩
	void AutoTriangle2D_SCD(float MinElmSize,float alpha0,float beta0,int nbndpoint,float *pBndX,float *pBndY,float *pBndZ,
		int &npoint,POINT_LIST *pPointCoor,int &ntri,ELEM_LIST *ptri);
	void AutoTriangle2D_MCD(float MinElmSize,float alpha0,float beta0,int nBoundary,const BOUNDARY_INDEX *pBoundary,int nbndpoint,
		const float *pBndX,const float *pBndY,const float *pBndZ,const float *fBndDist,
			   int &nnode,POINT_LIST *pPointCoor,
			   int &ntri,ELEM_LIST *pTri);
	//void TriangleMeshing2D();

	bool bUseBigTriangle;  //�Ƿ�ʹ�ô������η����㷨
	int ID; //Ϊ����ʾ��Ϣ,��1��ʼ���
	int nadapt; /*default number of adaptation cycles*/
	int smoothing; /*default flag for coordinate smoothing*/

	//������ά�ṹ������Ҫ������Ϊ�ı��Σ����ҶԱ߽��ֱ����n3=n1,n4=n2,pBndPoint��n1�߿�ʼ�洢
	BOOL StructuredTriangle3D(int n1,int n2,int nBndPoint,int iStart,Vector4 *pBndPoint,int &nnode,Vector4 *&pvNode,int &ntri,CTriangleElm *&pTriElm);
	void LaplaceSmoothing(void);


protected:
	int extra; /* extra nodes to be put in case of missing edges*/ 
	int pivot; //��ǰ���ڴ���������α��
	int bndextra; //���ӵı߽������������=4����������=0

	int nNode,nTri; //�ܽ�������ܵ�Ԫ��
	int nBndPoint;    //�߽����(����bUseBigTriangle=false��nBndPointExt=nBndPoint)
	int nBndPointExt; //��չ�ı߽����(����bUseBigTriangle=false��nBndPointExt=nBndPoint+4)
	int NSE,NewE,NE1,nBndLine,MNP,nblocks/*,nbnd*/;
	POINT_LIST    *pNode; //������飬������ʼ��������ζ���
	ELEM_LIST *pTri; //�����ε�Ԫ����
	int      suf[Sys_SUFFERED+1];
	ELEM_LIST ntc[3*Sys_SUFFERED+1];
	BOUNDARY_INDEX bindx[10];
	int Near[13],NNEARS;
	float MinElmSize,alpha,beta; //��С��Ԫ�ߴ磬С�ڸóߴ�ĵ�Ԫ����ϸ�֣�alpha,betaϸ�ֿ��Ʋ���(0-1֮��)
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
	
	//���ֳ�ʼ�������ɷ���
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
	void Set_Next_Fields(void);  //���õ��������
	long Crossi(INTEGER_POINT p1,INTEGER_POINT p2);
	void Remove_Unwanted_Triangles(void);
	void Near_Nodes(int tno,int *nn);
	void Compute_Centroids(int tno,float *xc,float *yc,float *zc);
	void Smooth(void);
	void Insert_Nodes(/*float alpha,float beta*/);
};

//�����ı�������
class CMeshingQuad
{
public:
	//ElmSize--��Ԫ�����ߴ�						
	//max_quad_angle--����ı��ε�Ԫ�ڽǣ��ȣ�	
	//max_tri_angle--��������ε�Ԫ�ڽǣ��ȣ�	
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
	float fDist;  //����������
	int nGridX;  //X�����������
	int nGridY;  //Y�����������
	int nBndPoint; //�߽����

	float fElmSize;  //������Ԫ�ߴ�
	float fMinElmSize; //��С��Ԫ�ߴ�,�ϲ����������,С�ڸ�ֵ�ĵ�಻����Ϊ��Ԫ�ı�,���ܻ�������������
	float fMaxQuadAngle;
	float fMaxTriAngle;
	int nSmooth;

	Vector4 *pVex3D;  //3D����
	Vector4 *pVexLocal;  //3D�ֲ�����
	CQuadElm *pQuad;
	CTriangleElm *pTriangle;
	GRID_LINE *pGrid;

	
public:
	//��·�����ɿռ��������Ľ���ı�������	
	//c0--���ھֲ�����ԭ��
	//u,v--���ھֲ������ʸ��
	//nBndPoint--����α߽����
	//pBndPoint--�߽��3D����			
	BOOL AutoQuad3D(const Vector4 &c0,const Vector4 &u,const Vector4 &v,const Vector4 &w,int nBndPoint,const Vector4 *pBndPoint);

	//��·�����ɵ���ͨƽ���������Ľ���ı�������
	//nBndPoint--����α߽����
	//pvex2d--�߽��2D����					
	BOOL AutoQuad2D_SCD(int nBndPoint,Vector4 *pvex2d);

	//������ά�ṹ������Ҫ������Ϊ�ı��Σ����ҶԱ߽��ֱ����,n1-n4�ֱ��Ӧ����ֱ�߶εĵĽ������n3=n1,n4=n2��  iStart--��һ��ֱ�߶ε���ʼ���
	BOOL StructuredQuad3D(int n1,int n2,int nBndPoint,int iStart,Vector4 *pBndPoint);

	//�б߷�������ά�ǽṹ����������Ϊ͹����Σ�iStart--��һ��ֱ�߶ε���ʼ���
	BOOL NonStructuredPoly3D(int nBndPoint,int iStart,Vector4 *pBndPoint);

	int GetNodeNum(void) const {return nVex;}
	Vector4 *GetVex3D(void) const {return pVex3D;}
	Vector4 *GetVexLocal(void) const {return pVexLocal;}

	int GetTriNum(void) const {return nTri;}
	CTriangleElm *GetTriPtr(void) const {return pTriangle;}

	int GetQuadNum(void) const {return nQuad;}
	CQuadElm *GetQuadPtr(void) const {return pQuad;}

protected:
	//����߽��߶μн�(��)
	//pvex2dΪ2D�ֲ����꣬��߽��߶η�������ʱ�뷽��pAngleΪ��㴦���߶μн�(��)
	//ֻʹ��XY����
	float GetAngle2D( int line1, int line2, const CLine * pLine, const Vector4 * pvex2d);

	void GetZoneRange2D(void);

	void AddLineToGrid(int iLine,const Vector4 &p1,const Vector4 &p2);
	void AddNewQuad( int n1, int n2, int n3, int n4,int &nLine,CLine *pLine);

	//�жϾֲ�ƽ�����߶��ཻ��ֻʹ��XY���꣩������ֵ��0���ཻ��1Ϊ���߶��ཻ��1�㡢��ȫ�򲿷��غϣ�n -- ��n��ӽ����غ�
	//Ӧ�ų�������nExclude1,nExclude2
	int LineCross(int nExclude1,int nExclude2,Vector4 p1,Vector4 p2,const CLine *pLine);

	//����3D�߶��Ƿ��ཻ
	//����ֵ��0���ཻ��1Ϊ���߶��ཻ��1�㣬11,12,21,22--��������һ���˵��غ��Ҳ����ߣ�-1��������ȫ�غϣ�-2�����߲����غ�
	int VectorLineCross3D(const Vector4 &pa, const Vector4 &pb, const Vector4 &qa, const Vector4 &qb);
	void LaplaceSmoothing(int nBndPoint,Vector4 *pVex,int nloop);  //�õ�nVex,nQuad,nTri,pQuad,pTriangle,pVexΪpVex2D��pVex3D�������ڶ�ά����ά���

	//��ֽǶȹ�����ı���
	void SplitToTriangle(int &nLine, CLine *pLine,const Vector4 *pVex,int nDim);

	//�ϲ����ߵ��������������Σ�nDim����ά��
	void MergeTriangle( int &nLine, CLine *pLine,const Vector4 *pVex,int nDim);

};
