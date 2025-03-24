#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "SSGData.h"

//��������
//iMethod={MESHING_TRI_INSERTPOINT,  MESHING_TRI_BLOCK,  MESHING_QUAD_TRI}
extern "C" _MESH_DLLIMPEXP int MeshingStruct(MESHING_METHOD iSlabMethod,MESHING_METHOD iWallMethod,CFrame &frame,CMesh &mesh);

extern "C" _MESH_DLLIMPEXP int MeshRelatedInfo(CFrame &frame,CMesh &mesh,CMesh::MESH_INFO &info);

void AutoDefineLinkGroup();//�Զ�����һ������������� �� 2016��11��10��

void AutoDefineSubStructGroup();//��һ�����ӵĹ����Զ�����Ϊ���Բ������������ �� 2017��12��27��

BOOL AutoCheckLinkDesignInfo();//��鹹���Ƿ��������Ϣ 

BOOL FindLongirebarElm(const CFrame &frame,  CMesh &mesh, int nLongirebar, const int * pLongiRebar, 
	const CPointWallIndex * pPointConnect, const LINE_USED * pLineUsed, 
	const CVertex * pNode,CBeamElm * pBeamElm, const CTriangleElm * pTriangleElm, const CQuadElm * pQuadElm,
	int tri_start, int quad_start);

BOOL SubdivisionBeam(const CFrame &frame,CMesh &mesh,SUB_LINE * pSubLineCollection, CVertex*& pNode,
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

//�ṹ�ṹ���ʷ��Ż�
BOOL SubLineOptByPlate(int plateid, const CFrame& frame, CMesh& mesh, SUB_LINE* pSubLineCollection,
	CVertex*& pNode, int& MaxNode);