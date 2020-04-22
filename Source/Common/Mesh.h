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


//��㵽��Ԫ��ӳ���ϵ
class _SSG_DLLIMPEXP CNode2ElmIndex
{
public:

	CNode2ElmIndex(void) {nelm=0;}

	enum{MAX_ELM=16};

	int nelm;
	struct ELEM_INFO
	{
		int elmid;  //��Ԫ����
		char vx,vy,vz;  //�浥Ԫ���ڵ�ƽ�淨��ʸ�������ߵ�Ԫ�����߷���
		char elmtype;  //��Ԫ���ͣ�0-����Ԫ��1-�����οǵ�Ԫ��2-�ı��οǵ�Ԫ

		//�ж��Ƿ���
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


//�ߵ�Ԫ��Ԫϸ����Ϣ
struct SUB_ELM_INFO2
{
	int neighborElm[2];				//�߽�����ڵ�Ԫ�����빲�ߣ�����ÿ��ֻ��һ����-1ʱ��Ч
	STRUCT_TYPE neighborType[2];    //���ڵ�Ԫ���ͣ�Ŀǰֻ����STRUCT_BEAM_ELM��STRUCT_UNKNOWN
	COLORREF vertexColor[2];		//������ɫ,R-G-B-S,�ֽ�SΪ��񻯳�ֵ��0--͸����ff--��͸��
};

//�����ε�Ԫϸ����Ϣ
struct SUB_ELM_INFO3
{
	int neighborElm[3];				//�߽������ڵ�Ԫ�����빲�棬����ÿ��ֻ��һ����-1ʱ��Ч
	STRUCT_TYPE neighborType[3];    //���ڵ�Ԫ���ͣ�Ŀǰֻ����STRUCT_TRI3_SHELL��STRUCT_QUAD4_SHELL��STRUCT_UNKNOWN
	COLORREF vertexColor[3];		//������ɫ,R-G-B-S,�ֽ�SΪ��ɫ��ʶ��0--��ֵΪ0(͸��)��ff--��ֵ��Ϊ0����͸����
	COLORREF lineColor[3];			//�����е���ɫ
	Vector4 lineCoor[3];			//�����е�����
	Vector4 centerCoor;				//��������
	Vector4 deform_lineCoor[3];		//�����е��������
	Vector4 deform_centerCoor;		//���ı�������
};

//�ı��ε�Ԫϸ����Ϣ
struct SUB_ELM_INFO4
{
	int neighborElm[4];				//�߽������ڵ�Ԫ�����빲�棬����ÿ��ֻ��һ����-1ʱ��Ч
	STRUCT_TYPE neighborType[4];    //���ڵ�Ԫ���ͣ�Ŀǰֻ����STRUCT_TRI3_SHELL��STRUCT_QUAD4_SHELL��STRUCT_UNKNOWN
	COLORREF vertexColor[4];		//������ɫ,R-G-B-S,�ֽ�SΪ��ɫ��ʶ��0--��ֵΪ0(͸��)��ff--��ֵ��Ϊ0����͸����
	COLORREF lineColor[4];			//�����е���ɫ
	Vector4 lineCoor[4];			//�����е�����
	Vector4 centerCoor;				//��������
	Vector4 deform_lineCoor[4];		//�����е��������
	Vector4 deform_centerCoor;		//���ı�������
};

//������,���������������ݺ�ѡȡ������
class _SSG_DLLIMPEXP  CMesh : public CRemoveInvalidPrimitive/*,public CProfile*/
{
public:
	CMesh(void);
	~CMesh(void);

	int m_nNode;  //�����
	CVertex *m_pNode;   //�����������

	int m_nBeam;  //����Ԫ��
	CBeamElm *m_pBeam;    //����Ԫ����

	int m_nTriangle;   //�����ε�Ԫ��
	CTriangleElm *m_pTriangle; //�浥Ԫ����

	int m_nQuad;   //�Ľ���ı��ε�Ԫ��
	CQuadElm *m_pQuad; //�Ľ���浥Ԫ����


	//��㵽��Ԫ�����������ڵ�Ԫ����ƽ������(���ڵ�Ԫƽ����Ӧ������ͬ�������ҷ�������һ��)
	//��������ʱ����뵥Ԫʱ����
	CNode2ElmIndex *m_pNode2Elm;

	//ϸ�ֵ�Ԫ��Ϣ����������ƽ��ӳ��
	SUB_ELM_INFO2 *m_pSubBeamInfo;
	SUB_ELM_INFO3 *m_pSubTriInfo;
	SUB_ELM_INFO4 *m_pSubQuadInfo;

	CBoundary *m_pBoundary;  //�߽��������飬�������غ�λ�ƣ������洢

	//���ز�����������Ӧ�������е�����һ��,�粻һ�£�������Ϊ��Ч���ݡ��˴�Ϊ�������ݣ���������ʱ�õ�
	//ԭʼ����ΪCFrame::m_cStage.aStagePtr.GetCount()��Ϊ�����������ļ���������
	int m_nStage;    //ʩ���׶���
	int *m_pStartNode;     //ĳ���ز��н����ʼ���,   ����Ϊm_nStage+1�����һ�����ݿ��Եõ��ܽ����
	int *m_pStartBeamElm;  //ĳ���ز�������Ԫ��ʼ���, ����Ϊm_nStage+1
	int *m_pStartTriElm;   //ĳ���ز��������οǵ�Ԫ��ʼ���, ����Ϊm_nStage+1
	int *m_pStartQuadElm;   //ĳ���ز����ı��οǵ�Ԫ��ʼ���, ����Ϊm_nStage+1

	CDataPathCollection m_cDataPath; //·��

	CMesh & operator=(const CMesh & mesh)
	{
		if(this==&mesh) return *this;
		ASSERT(FALSE);  //���ڸ��ٴ˺�������ʱ���ṩ���ƹ���
		return *this;
	}

	void Clear();
	float GetMinMax(CVertex &MinCoor,CVertex &MaxCoor); //�������ֱ��
	float GetMinMax(Vector4 &MinCoor,Vector4 &MaxCoor); //�������ֱ��
	int GetNodeID(float x,float y,float z);  //���������ҵ�����

	//����ػ��͵�����Լ��
	BOOL SetBoundary(void); 
	void AppendLine(int idVex1,int idVex2,CLine *pLine,int &nLine);  //�����߶�

	int GetBeamElmConnLowerLayer(vector<BEAM_CONN_LAYER> &vBeam); //�����õ����²���ɵ����򹹼�����Ԫ,���ص�Ԫ��
	int GetBeamElmConnUpperLayer(vector<BEAM_CONN_LAYER> &vBeam); //�����õ����ϲ���ɵ����򹹼�����Ԫ,���ص�Ԫ��

	int GetTriElmConnLowerLayer(vector<SHELL_CONN_LAYER> &vShell); //�����õ����²���ɵ�ǽ֫�����ε�Ԫ,���ص�Ԫ��
	int GetTriElmConnNode(int elmid, int &node1,int &node2);
	int GetTriElmConnUpperLayer(vector<SHELL_CONN_LAYER> &vShell); //�����õ����ϲ���ɵ�ǽ֫�����ε�Ԫ,���ص�Ԫ��

	int GetQuadElmConnLowerLayer(vector<SHELL_CONN_LAYER> &vShell); //�����õ����²���ɵ�ǽ֫�ı��ε�Ԫ,���ص�Ԫ��
	int GetQuadElmConnNode(int elmid, int &node1,int &node2);
	int GetQuadElmConnUpperLayer(vector<SHELL_CONN_LAYER> &vShell); //�����õ����ϲ���ɵ�ǽ֫�ı��ε�Ԫ,���ص�Ԫ��

	
	//�޳�δʹ�õĽ��
	BOOL RemoveUnusedNode();

	//���ص������ʷ�����
	struct MESH_INFO
	{
		int max_node_diff;  //��Ԫ��������
		int idm; //������ĵ�Ԫ��
		int iElmType; //������ĵ�Ԫ���ͣ�0--����Ԫ��1--�����οǵ�Ԫ��2--�ı��οǵ�Ԫ
		int iStory; //������ĵ�Ԫ����¥��
	};
	
	//��㰴ʩ���׶�--¥���С��������¥���ڱ�֤��С���������ʷ���Ϣ,�õ�m_pStartBeamElm��m_pStartTriElm
	MESH_INFO RearrangeNodeByStage(int nStage);

	//��Ԫ��ʩ���׶�--¥���С��������,�õ�m_pStartBeamElm��m_pStartTriElm
	void RearrangeElmByStage(int nStage);	

	//��ÿ����Ԫ�Ľ���С��������
	void RearrangeElmLocalNode(void);	

	//ͳ��ÿ�׶ε���ʼ����
	void GetStageStartNode(int nStage);	

	//���ÿ����㱻¥����ʹ�õ���Ϣ��ÿ������౻����¥��ʹ�ã���x/yֵΪ-1��û��ʹ��
	void GetNodeStory(POINT *pNodeStory);

	//���ɽ�㵽��Ԫ����������m_pNode2Elm������������Լ����������Ҫ����
	BOOL CreateNode2Elm(void);

	//����ϸ�ֵ�Ԫ����������ƽ��,����m_pSubTriInfo��m_pSubQuadInfo����Ҫm_pNode2Elm
	BOOL CreateShellSubElm(void);
	//�������ڵ�Ԫ����Ҫm_pSubTriInfo��m_pSubQuadInfo
	void SetShellSubElmNeighbor(void);
	//��ʼ���ӵ�Ԫԭʼ����
	void InitShellSubElmOriginalCoor(void);
	//��������仯������ӵ�Ԫ��������
	void UpdateShellSubElmDeformCoor(CVertex *pNode);


	//�õ����λ�ƽǵ�Ԫ
	//Sty_Col_id: ���ӣ�����ģ��,����б�š���Ե��������Ϣ�������ϲ�ڵ��š��²�ڵ��š�¥��ţ�����Sty_Col_Num��3
	//Sty_Col_Type: �������ͣ�����Sty_Col_Num,�������Ͱ���STRUCT_TYPE����
	//���أ����������ݵ�ַ
	//�������ݣ�
	//iFilter: �������˷�����		0--�����η�Χ����							1--�����Ź���	2--��ָ�������
	//pFilterData:�����õ����ݣ�	float[4] ���η�Χ(xmin,ymin,xmax,ymax)		int* ����		NULL
	int CreateDriftElm( int *&Sty_Col_id,int *&Sty_Col_Type,int iFilter,const void *pFilterData);

	//�õ���������Ԫ
	//�������ݣ�
	//iFilter: �������˷�����		0--�����η�Χ����							1--�����Ź���	2--��ָ�������
	//pFilterData:�����õ����ݣ�	float[4] ���η�Χ(xmin,ymin,xmax,ymax)		int* ����		NULL
	int CreateStoryShearElm(vector<BEAM_CONN_LAYER> &vBottomBeamElm,vector<SHELL_CONN_LAYER> &vBottomShell,vector<SHELL_CONN_LAYER> &vBottomQuad,
		int iFilter,const void *pFilterData);


	BOOL ReadMeshBin(int &nStory,CStory *pStory); //��ȡ��Ԫ������
	BOOL WriteMeshBin(void);
	BOOL WriteMeshTxt(void);

	//������ά���Ĵ���
	void PostMesh(void);

private:
	void RearrangeID();  //���±���ID��ȥ����ЧͼԪ

	BOOL IsMerge(int iNodeSta, int iNodeEnd, int *pNode_BeamCnt, int *pNode_BeamId);
	BOOL MergeQuad(int &iNodeSta, int &iNodeEnd, int iNodeAngle, int *pNode_QuadCnt, int *pNode_QuadId);

	//������ά���Ĵ���
	float GetLengthLine(float *pCoorSta, float *pCoorEnd);
	void CrossProductV(float *pCoor_resu, float *pCoor1, float *pCoor2);
	float DotProductV(float *pCoor1, float *pCoor2);
	float CosV(float *pCoor0, float *pCoor1, float *pCoor2);
	float GetLengthV(float *pCoor);
};



