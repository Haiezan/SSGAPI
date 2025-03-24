#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "SSGData.h"

//生成网格
//iMethod={MESHING_TRI_INSERTPOINT,  MESHING_TRI_BLOCK,  MESHING_QUAD_TRI}
extern "C" _MESH_DLLIMPEXP int MeshingStruct(MESHING_METHOD iSlabMethod,MESHING_METHOD iWallMethod,CFrame &frame,CMesh &mesh);

extern "C" _MESH_DLLIMPEXP int MeshRelatedInfo(CFrame &frame,CMesh &mesh,CMesh::MESH_INFO &info);

void AutoDefineLinkGroup();//自动定义一般连接输出分组 邱海 2016年11月10日

void AutoDefineSubStructGroup();//与一般连接的构件自动设置为弹性并定义输出分组 邱海 2017年12月27日

BOOL AutoCheckLinkDesignInfo();//检查构件是否有设计信息 

BOOL FindLongirebarElm(const CFrame &frame,  CMesh &mesh, int nLongirebar, const int * pLongiRebar, 
	const CPointWallIndex * pPointConnect, const LINE_USED * pLineUsed, 
	const CVertex * pNode,CBeamElm * pBeamElm, const CTriangleElm * pTriangleElm, const CQuadElm * pQuadElm,
	int tri_start, int quad_start);

BOOL SubdivisionBeam(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, CVertex*& pNode,
	CBeamElm * &pBeamElm,int &MaxBeamElm,int &nLongirebar,int * &pLongiRebar, int &MaxLongirebar, 
	LINE_USED * pLineUsed,int beamid);

//返回FALSE--代表严重错误，必须停止网格生成
//不符合条件的单元没有生成则返回TRUE
BOOL SubdivisionPlate(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
	CVertex * &pNode, int &MaxNode, CTriangleElm *&pTriangleElm,int &MaxTriElm,CQuadElm *&pQuadElm,int &MaxQuadElm,
	MESHING_METHOD iMethod,STRUCT_TYPE iStructType,int plateid);

//剖分一条结构线
BOOL SubdivisionLine (int lineid, const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
	CVertex * &pNode, int &MaxNode, int nSub );

//结构结构线剖分优化
BOOL SubLineOptByPlate(int plateid, const CFrame& frame, CMesh& mesh, SUB_LINE* pSubLineCollection,
	CVertex*& pNode, int& MaxNode);