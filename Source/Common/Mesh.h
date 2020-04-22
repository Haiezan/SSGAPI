#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "..\Common\SysPara.h"
#include "ASCFile.h"
#include "UserDefine.h"
//#include "SectionDefine.h"
//#include "Material.h"
#include "ASCFile.h"
//#include "Profile.h"
#include "..\Common\Data.h"
#include <afxtempl.h>
#include <vector>
#include <algorithm>
#include <functional>


//结点到单元的映射关系
class _SSG_DLLIMPEXP CNode2ElmIndex
{
public:

	CNode2ElmIndex(void) {nelm=0;}

	enum{MAX_ELM=16};

	int nelm;
	struct ELEM_INFO
	{
		int elmid;  //单元编码
		char vx,vy,vz;  //面单元所在的平面法线矢量，或线单元的轴线方向
		char elmtype;  //单元类型，0-梁单元，1-三角形壳单元，2-四边形壳单元

		//判断是否共面
		BOOL InOnePlane(char vx1,char vy1,char vz1) const
		{
			if( vx==vx1 && vy==vy1 && vz==vz1 ) return TRUE;
			if( vx==(-vx1) && vy==(-vy1) && vz==(-vz1) ) return TRUE;
			return FALSE;
		}
	}elminfo[MAX_ELM];

	inline int AddElm(int elmid,char vx,char vy,char vz,char elmtype1)
	{
		if(nelm>=MAX_ELM) return -1;
		elminfo[nelm].elmid=elmid;
		elminfo[nelm].vx=vx;
		elminfo[nelm].vy=vy;
		elminfo[nelm].vz=vz;
		elminfo[nelm].elmtype=elmtype1;
		nelm++;
		return nelm;
	}
};


//线单元单元细分信息
struct SUB_ELM_INFO2
{
	int neighborElm[2];				//边界点相邻单元，必须共线，所以每点只有一个，-1时无效
	STRUCT_TYPE neighborType[2];    //相邻单元类型，目前只能是STRUCT_BEAM_ELM、STRUCT_UNKNOWN
	COLORREF vertexColor[2];		//顶点颜色,R-G-B-S,字节S为规格化场值：0--透明，ff--不透明
};

//三角形单元细分信息
struct SUB_ELM_INFO3
{
	int neighborElm[3];				//边界线相邻单元，必须共面，所以每边只有一个，-1时无效
	STRUCT_TYPE neighborType[3];    //相邻单元类型，目前只能是STRUCT_TRI3_SHELL、STRUCT_QUAD4_SHELL、STRUCT_UNKNOWN
	COLORREF vertexColor[3];		//顶点颜色,R-G-B-S,字节S为颜色标识：0--场值为0(透明)，ff--场值不为0（不透明）
	COLORREF lineColor[3];			//边线中点颜色
	Vector4 lineCoor[3];			//边线中点坐标
	Vector4 centerCoor;				//重心坐标
	Vector4 deform_lineCoor[3];		//边线中点变形坐标
	Vector4 deform_centerCoor;		//重心变形坐标
};

//四边形单元细分信息
struct SUB_ELM_INFO4
{
	int neighborElm[4];				//边界线相邻单元，必须共面，所以每边只有一个，-1时无效
	STRUCT_TYPE neighborType[4];    //相邻单元类型，目前只能是STRUCT_TRI3_SHELL、STRUCT_QUAD4_SHELL、STRUCT_UNKNOWN
	COLORREF vertexColor[4];		//顶点颜色,R-G-B-S,字节S为颜色标识：0--场值为0(透明)，ff--场值不为0（不透明）
	COLORREF lineColor[4];			//边线中点颜色
	Vector4 lineCoor[4];			//边线中点坐标
	Vector4 centerCoor;				//重心坐标
	Vector4 deform_lineCoor[4];		//边线中点变形坐标
	Vector4 deform_centerCoor;		//重心变形坐标
};

//网格类,保存所有网格数据和选取的物理场
class _SSG_DLLIMPEXP  CMesh : public CRemoveInvalidPrimitive/*,public CProfile*/
{
public:
	CMesh(void);
	~CMesh(void);

	int m_nNode;  //结点数
	CVertex *m_pNode;   //结点坐标数组

	int m_nBeam;  //梁单元数
	CBeamElm *m_pBeam;    //梁单元数组

	int m_nTriangle;   //三角形单元数
	CTriangleElm *m_pTriangle; //面单元数组

	int m_nQuad;   //四结点四边形单元数
	CQuadElm *m_pQuad; //四结点面单元数组


	//结点到单元的索引，用于单元物理场平滑处理(相邻单元平均，应考虑相同物理场并且分量方向一致)
	//生成网格时或读入单元时创建
	CNode2ElmIndex *m_pNode2Elm;

	//细分单元信息，用于物理场平滑映射
	SUB_ELM_INFO2 *m_pSubBeamInfo;
	SUB_ELM_INFO3 *m_pSubTriInfo;
	SUB_ELM_INFO4 *m_pSubQuadInfo;

	CBoundary *m_pBoundary;  //边界条件数组，包括荷载和位移，按结点存储

	//加载步数，此数据应该与框架中的数据一致,如不一致，则以下为无效数据。此处为冗余数据，生成网格时得到
	//原始数据为CFrame::m_cStage.aStagePtr.GetCount()，为了网格数据文件的完整性
	int m_nStage;    //施工阶段数
	int *m_pStartNode;     //某加载步中结点起始编号,   长度为m_nStage+1，最后一个数据可以得到总结点数
	int *m_pStartBeamElm;  //某加载步中梁单元起始编号, 长度为m_nStage+1
	int *m_pStartTriElm;   //某加载步中三角形壳单元起始编号, 长度为m_nStage+1
	int *m_pStartQuadElm;   //某加载步中四边形壳单元起始编号, 长度为m_nStage+1

	CDataPathCollection m_cDataPath; //路径

	CMesh & operator=(const CMesh & mesh)
	{
		if(this==&mesh) return *this;
		ASSERT(FALSE);  //用于跟踪此函数，暂时不提供复制功能
		return *this;
	}

	void Clear();
	float GetMinMax(CVertex &MinCoor,CVertex &MaxCoor); //返回外包直径
	float GetMinMax(Vector4 &MinCoor,Vector4 &MaxCoor); //返回外包直径
	int GetNodeID(float x,float y,float z);  //根据坐标找到结点号

	//处理地基和地下室约束
	BOOL SetBoundary(void); 
	void AppendLine(int idVex1,int idVex2,CLine *pLine,int &nLine);  //增加线段

	int GetBeamElmConnLowerLayer(vector<BEAM_CONN_LAYER> &vBeam); //搜索得到与下层过渡的竖向构件梁单元,返回单元数
	int GetBeamElmConnUpperLayer(vector<BEAM_CONN_LAYER> &vBeam); //搜索得到与上层过渡的竖向构件梁单元,返回单元数

	int GetTriElmConnLowerLayer(vector<SHELL_CONN_LAYER> &vShell); //搜索得到与下层过渡的墙肢三角形单元,返回单元数
	int GetTriElmConnNode(int elmid, int &node1,int &node2);
	int GetTriElmConnUpperLayer(vector<SHELL_CONN_LAYER> &vShell); //搜索得到与上层过渡的墙肢三角形单元,返回单元数

	int GetQuadElmConnLowerLayer(vector<SHELL_CONN_LAYER> &vShell); //搜索得到与下层过渡的墙肢四边形单元,返回单元数
	int GetQuadElmConnNode(int elmid, int &node1,int &node2);
	int GetQuadElmConnUpperLayer(vector<SHELL_CONN_LAYER> &vShell); //搜索得到与上层过渡的墙肢四边形单元,返回单元数

	
	//剔除未使用的结点
	BOOL RemoveUnusedNode();

	//返回的网格剖分数据
	struct MESH_INFO
	{
		int max_node_diff;  //单元的最大结点差
		int idm; //最大结点差的单元号
		int iElmType; //最大结点差的单元类型，0--梁单元，1--三角形壳单元，2--四边形壳单元
		int iStory; //最大结点差的单元所在楼层
	};
	
	//结点按施工阶段--楼层从小到大排序，楼层内保证最小带宽，返回剖分信息,用到m_pStartBeamElm和m_pStartTriElm
	MESH_INFO RearrangeNodeByStage(int nStage);

	//单元按施工阶段--楼层从小到大排序,用到m_pStartBeamElm和m_pStartTriElm
	void RearrangeElmByStage(int nStage);	

	//对每个单元的结点从小到大排序
	void RearrangeElmLocalNode(void);	

	//统计每阶段的起始结点号
	void GetStageStartNode(int nStage);	

	//获得每个结点被楼层所使用的信息，每个点最多被两个楼层使用，若x/y值为-1则没被使用
	void GetNodeStory(POINT *pNodeStory);

	//生成结点到单元的索引数组m_pNode2Elm，读入网格后以及生成网格后要调用
	BOOL CreateNode2Elm(void);

	//创建细分单元，用于物理场平滑,生成m_pSubTriInfo及m_pSubQuadInfo。需要m_pNode2Elm
	BOOL CreateShellSubElm(void);
	//搜索相邻单元，需要m_pSubTriInfo及m_pSubQuadInfo
	void SetShellSubElmNeighbor(void);
	//初始化子单元原始坐标
	void InitShellSubElmOriginalCoor(void);
	//网格坐标变化后更新子单元变形坐标
	void UpdateShellSubElmDeformCoor(CVertex *pNode);


	//得到层间位移角单元
	//Sty_Col_id: 柱子（几何模型,包括斜撑、边缘构件）信息，包括上层节点编号、下层节点编号、楼层号，长度Sty_Col_Num×3
	//Sty_Col_Type: 柱子类型，长度Sty_Col_Num,变量类型按照STRUCT_TYPE定义
	//返回：数量和数据地址
	//输入数据：
	//iFilter: 构件过滤方法，		0--按矩形范围过滤							1--按塔号过滤	2--按指定点过滤
	//pFilterData:过滤用的数据，	float[4] 矩形范围(xmin,ymin,xmax,ymax)		int* 塔号		NULL
	int CreateDriftElm( int *&Sty_Col_id,int *&Sty_Col_Type,int iFilter,const void *pFilterData);

	//得到层间剪力单元
	//输入数据：
	//iFilter: 构件过滤方法，		0--按矩形范围过滤							1--按塔号过滤	2--按指定点过滤
	//pFilterData:过滤用的数据，	float[4] 矩形范围(xmin,ymin,xmax,ymax)		int* 塔号		NULL
	int CreateStoryShearElm(vector<BEAM_CONN_LAYER> &vBottomBeamElm,vector<SHELL_CONN_LAYER> &vBottomShell,vector<SHELL_CONN_LAYER> &vBottomQuad,
		int iFilter,const void *pFilterData);


	BOOL ReadMeshBin(int &nStory,CStory *pStory); //读取单元和坐标
	BOOL WriteMeshBin(void);
	BOOL WriteMeshTxt(void);

	//由王欣维护的代码
	void PostMesh(void);

private:
	void RearrangeID();  //重新编排ID，去掉无效图元

	BOOL IsMerge(int iNodeSta, int iNodeEnd, int *pNode_BeamCnt, int *pNode_BeamId);
	BOOL MergeQuad(int &iNodeSta, int &iNodeEnd, int iNodeAngle, int *pNode_QuadCnt, int *pNode_QuadId);

	//由王欣维护的代码
	float GetLengthLine(float *pCoorSta, float *pCoorEnd);
	void CrossProductV(float *pCoor_resu, float *pCoor1, float *pCoor2);
	float DotProductV(float *pCoor1, float *pCoor2);
	float CosV(float *pCoor0, float *pCoor1, float *pCoor2);
	float GetLengthV(float *pCoor);
};



