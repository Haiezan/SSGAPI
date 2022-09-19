#pragma once
#include "SSGData.h"

BOOL FindLongirebarElm(const CFrame &frame,  CMesh &mesh, int nLongirebar, const int * pLongiRebar, 
	const CPointWallIndex * pPointConnect, const LINE_USED * pLineUsed, 
	const CVertex * pNode,CBeamElm * pBeamElm, const CTriangleElm * pTriangleElm, const CQuadElm * pQuadElm,
	int tri_start, int quad_start);

BOOL SubdivisionBeam(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
	CBeamElm * &pBeamElm,int &MaxBeamElm,int &nLongirebar,int * &pLongiRebar, int &MaxLongirebar, 
	LINE_USED * pLineUsed,int beamid);

//����FALSE--�������ش��󣬱���ֹͣ��������
//�����������ĵ�Ԫû�������򷵻�TRUE
BOOL SubdivisionPlate(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
	CVertex * &pNode, int &MaxNode, CTriangleElm *&pTriangleElm,int &MaxTriElm,CQuadElm *&pQuadElm,int &MaxQuadElm,
	MESHING_METHOD iMethod,STRUCT_TYPE iStructType,int plateid);

//�ʷ�һ���ṹ��
BOOL SubdivisionLine (int lineid, const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, 
	CVertex * &pNode, int &MaxNode, int nSub );

extern "C" _MESH_DLLIMPEXP int MeshingStruct(MESHING_METHOD iSlabMethod,MESHING_METHOD iWallMethod,const CFrame &frame,CMesh &mesh);
