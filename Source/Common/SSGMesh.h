#pragma once
#include "SSGData.h"

BOOL FindLongirebarElm(const CFrame &frame,  CMesh &mesh, int nLongirebar, const int * pLongiRebar, 
	const CPointWallIndex * pPointConnect, const LINE_USED * pLineUsed, 
	const CVertex * pNode,CBeamElm * pBeamElm, const CTriangleElm * pTriangleElm, const CQuadElm * pQuadElm,
	int tri_start, int quad_start);

BOOL SubdivisionBeam(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
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

extern "C" _MESH_DLLIMPEXP int MeshingStruct(MESHING_METHOD iSlabMethod,MESHING_METHOD iWallMethod,const CFrame &frame,CMesh &mesh);
