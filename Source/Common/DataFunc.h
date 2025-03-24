#pragma once

#include "HeadDefine.h"
#include "Vector4.h"
#include "DataPrimitive.h"

//��ȡ������ȱʡ��ɫ
extern "C" _SSG_DLLIMPEXP COLORREF GetStructDefaultColor(STRUCT_TYPE type,int iSubType);

//���ڴ�ID(IDM)����ʰȡID(IDG),�궨���б�������ţ�����������Ԥ֪
//#define GETIDG(IDM,ArrayType) ((IDM)+(ArrayType))  
extern "C" _SSG_DLLIMPEXP int GetIDG(int idm,STRUCT_TYPE iType); 

//��ʰȡID(IDG)�����ڴ�ID(IDM)
extern "C" _SSG_DLLIMPEXP int GetIDM(int IDG);
//���ڴ�ID(IDM)����ʰȡID(IDG)
extern "C" _SSG_DLLIMPEXP STRUCT_TYPE GetPickedType(int IDG);
//ʰȡ˳���ж�
extern "C" _SSG_DLLIMPEXP int GetPickedOrder(int IDG);
//��IDG����������ʼ����ֵ
extern "C" _SSG_DLLIMPEXP int GetBaseType(int IDG);

extern "C" _SSG_DLLIMPEXP BOOL ValidHit(int iHit);   //�ж�ʰȡ����iHit�Ƿ���Ч

//��������ͬ�ĵ���кϲ�,���ؾɵ��ŵ��µ��ŵ�����index�� ͬʱԭ����������鱻���£���������Ϊ���������Ķ�̬�ڴ棬���ó��������Ӧ�ͷ�
//ʧ���򷵻ؿ�ָ��
extern "C" _SSG_DLLIMPEXP int *Merge(CVertex *pVex,int nOldNPoint,int &nNewPoint);

//��������Ժϲ�
//pVex2��pVex1����ƥ�䣬���ҵ��򷵻�pVex1��Ӧ��pID1���룬���򷵻�StartID��ʼ�ı���
//pID1��pVex2��pVex1�����±����0��ʼ
//pID1ΪpVex1��Ӧ�Ľ�����
extern "C" _SSG_DLLIMPEXP int *MergeWithArray(const int *pID1, int nVex1, const Vector4 *pVex1, int nVex2, const Vector4 *pVex2, int StartID);

//���ض���ζ����������,��β�㲻�غ�,���ɹ��򷵻�NULL
//��������Ľ�����겻�غϣ���û��������ͬ�����벻ͬ�ĵ�,���ó���Ӧ�ͷŷ��ص�ָ���ڴ�
//����: pPolygonLine--��˳��Χ�ɶ���ε��߶�����,�߶α��밴˳��������߶α�ŷ����������
extern "C" _SSG_DLLIMPEXP int *GetPolygonVexID(int nLine, const CLine *pPolygonLine);

//���׶�����,vex--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortNodeByStage(int nData, CVertex  *vex); 

//���׶�����,beam--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortBeamElmByStage(int nData, CBeamElm  *beam); 

//���׶�����,tri--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortTriElmByStage(int nData,CTriangleElm  *tri); 
extern "C" _SSG_DLLIMPEXP int *StackSortQuadElmByStage(int nData,CQuadElm  *quad); 


//����XY���ڵ���ת�ǣ���λ���ȣ�center--��ת���ģ�p1,p2--��ת�������յ㣬��������Բ���ͬһԲ���ϣ�ֻ�����center�����������ϵĵ�
//��������ֻ��x,y����
extern "C" _SSG_DLLIMPEXP double RotateAngleDouble(const CVertex &center,const CVertex &p1,const CVertex &p2);


extern "C" _SSG_DLLIMPEXP STRUCT_KEYWORD g_StructKeyword[Sys_StructTypeNum];
extern "C" _SSG_DLLIMPEXP STRUCT_PROPERTY1 g_PropTable1[17];


extern "C" _SSG_DLLIMPEXP void GetBeamInitialImperfection(CBeamStruc &beam,bool bRewrite=false);


extern "C" _SSG_DLLIMPEXP void LinearSmooth3 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void LinearSmooth5 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void LinearSmooth7 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void QuadraticSmooth5(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void QuadraticSmooth7(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void CubicSmooth5 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void CubicSmooth7(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void GaussianSmooth(float in[], float out[], int N);

extern "C" _SSG_DLLIMPEXP void OnFrame2elm(CFrame& frame, CMesh& mesh);  //�����������������Ҫ����
