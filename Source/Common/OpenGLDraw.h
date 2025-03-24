#pragma once

//#include "SysPara.h"
#include "HeadDefine.h"
#include "..\Common\Vector4.h"
#include "..\Common\Matrix4x4.h"
#include "..\Common\UserDefine.h"
#include "..\Common\EdgeStruct.h"
#include "..\Common\VisibleStruct.h"
#include "..\Common\EdgeStruct.h"
//#include "DebugInfoDlg.h"
//#include "Timediff.h"
#include "..\Common\Mesh.h"
#include "Shader.h"
#include "..\Platform\Profile.h"
#include<unordered_map>

#include "../../Lib/gl/include/GL/glew.h"
//#include "../../Lib/gl/include/GL/glxew.h"
#include "../../Lib/gl/include/GL/wglew.h"

const int DISPLAY_PATA1_NUM=12;  //��ʾ���ز�������
const int DISPLAY_PATA2_NUM=13;  //��ʾ���ز�������
const int DISPLAY_PATA3_NUM=8;  //��ʾ���ز�������	//20156.1.12

const int BUFSIZE=512;  //ʰȡ��������С
const Vector4 Sys_LightPosition(-0.436f,0.218f,0.873f);  //�ƹ�ķ�������
//const float Sys_AmbientRatio=0.1f;   //������ǿ��,��Χ[0,1]
//const float Sys_DirectRatio=1.0f;    //�����������ǿ�ȣ���Χ[0,1]



enum RENDER_TYPE
{
	RENDER_VERTEX,      //��������ɫ��Ⱦ
	RENDER_PRIMITIVE,   //��ͼԪ��ɫ��Ⱦ
	RENDER_SMOOTH,      //����Ԫƽ���������Ⱦ
};

enum COLOR_TYPE
{
	COLOR_BODY,    //��ʵ����ɫ����
	COLOR_VERTEX,  //��������ɫ����
};

struct hash_vec
{
	size_t operator()(const Vector4& vc)const
	{
		return hash<float>()(vc.x) ^ hash<float>()(vc.y) ^ hash<float>()(vc.z);
	}
};

class _SSG_OPENGLDLL COpenGL//:CProfile
{
public:
	COpenGL(void);
	~COpenGL(void);

public:


	//����
	BOOL m_bShowFrame; //TRUE--���ƿ�ܣ�FALSE--��������


	float m_fDiameter;  //ͼ�����ߴ�,���ڿ�����ʾ��������ȳߴ�
	Vector4 m_MinCoor;
	Vector4 m_MaxCoor;  //���귶Χ
	struct MUL_PROJRCT *m_MP; //��Ŀ��Ϣ
	int m_nProjects; //��Ŀ��
	float m_fPointSize;  //��ͨ��Ĵ�С����λ������

	/*m_bShowAuxVex(���¼�Ϊa)��m_bShowVex(���¼�Ϊb)�Ĺ�ϵ��
	�������е�=a         �Ƿ�����е�=a && b
	�渨����  =A         �Ƿ����Ӧ��=A && b
	��ṹ��  =B         �Ƿ����Ӧ��=B && b
	�湹��    =C         �Ƿ����Ӧ��=C && ~B && b

	���ԣ�b���ܷ񿴵��κε�Ŀ��أ�a���ܷ񿴵�������Ŀ��أ�������ֻ��������������

	(a,b)��������У���a=TRUE,ͬʱb=FALSE��״̬��Ч
	���ò���ʱӦǿִ���������:a=TRUE��һ��Ҫb=TRUE����������ָ������ã�
	��b=FALSE,a���κ�״̬���޹ؽ�Ҫ���������Ϊa=FALSE
	*/

	union 
	{
		struct
		{
			BOOL m_bShowVex;		  //�Ƿ���ʾ��
			BOOL m_bShowBeam;         //�Ƿ���ʾ��
			BOOL m_bShowPillar;       //�Ƿ���ʾ��
			BOOL m_bShowPlate;        //�Ƿ���ʾ��
			BOOL m_bShowWallColumn;         //�Ƿ���ʾǽ��
			BOOL m_bShowWallBeam;         //�Ƿ���ʾǽ��
			BOOL m_bShowBracing;      //�Ƿ���ʾб��
			BOOL m_bShowEdge;         //�Ƿ���ʾ��Ե����
			BOOL m_bShowHideBeam;     //�Ƿ���ʾ����
			BOOL m_bShowLongiRebar;   //�Ƿ���ʾ�����ݽ�
			BOOL m_bShowLink;     //�Ƿ���ʾ������	//�Ǳ��� 2015.5.21
			BOOL m_bShowRigid; //�Ƿ���ʾ���Ը��� ���� 20231214
		};
		BOOL m_pbDisplayPara1[DISPLAY_PATA1_NUM];
	};

	union 
	{
		struct
		{
			BOOL m_bShowAuxVex;       //�Ƿ���ʾ�����㣬m_bShowVex=TRUE����Ч
			BOOL m_bShowGuides;       //�Ƿ���ʾ������
			BOOL m_bShowStructLines;  //�Ƿ���ʾ�ṹ��
			BOOL m_bShowBoundaryLine;  //�Ƿ���ʾ�߽���
			BOOL m_bShowAnticulate;   //�Ƿ���ʾ�½ӱ�ʶ
			BOOL m_bShowComments;     //�Ƿ���ʾ��ע��Ϣ
			BOOL m_bShowLC;           //�Ƿ���ʾԼ��������
			BOOL m_bShowAxis;         //�Ƿ���ʾ������
			BOOL m_bShowScale;        //�Ƿ���ʾ���ڿ̶�
			BOOL m_bShowOuterFrame;   //�Ƿ���ʾ�����
			BOOL m_bShowLocalAxis;			//�Ƿ���ʾ�ֲ�����ϵ 2017��12��18��
			BOOL m_bShowRestraints;			//�Ƿ���ʾλ��Լ�� 2017��12��18��
			BOOL m_bShowVexCross;		//�Ƿ���ʾ�����ʶ
		};
		BOOL m_pbDisplayPara2[DISPLAY_PATA2_NUM];
	};

	union
	{
		struct
		{
			//����Ч������
			BOOL m_bShowFace;       //ʵ��ģʽ
			BOOL m_bSmoothVex;      //���⻬
			BOOL m_bDrawByBody;     //�ṹ����
			BOOL m_bBeamBlend;      //ˮƽ�߹�����͸��ģʽ
			BOOL m_bPillarBlend;    //�����߹�����͸��ģʽ
			BOOL m_bPlateBlend;     //���͸��ģʽ
			BOOL m_bWallBlend;      //ǽ��͸��ģʽ
			BOOL m_bRenderBlend;		//��͸����ͼ
			BOOL m_bRenderLight;		//��ͼģ�����Ч�� //2016.1.12
		};
		BOOL m_pbDisplayPara3[DISPLAY_PATA3_NUM];
	};

	BOOL m_bShowHinge;			//�Ƿ���ʾ���Խ�	//2015.5.9
	BOOL m_bUseShader;
	BOOL m_bShowUndeform;     //�Ƿ���ʾԭʼ�ο�ͼ
	BOOL m_bOrtho;            //����ͶӰģʽ	
	BOOL m_bNodeCenterSmooth; //��Ԫ���ĵ��Ƿ��������ƽ����ʾ
	BOOL m_bCoorOffset;       //������Ƿ��Ѿ����ǹ���ƫ��
	BOOL m_bShowCrack;

	enum DRAWTYPE m_DrawType; //��ͼ����
	enum RENDER_TYPE m_iRenderType; //��ɫ��Ⱦ��ʽ��ֻ�ڻ��Ƶ�Ԫʱ��Ч�����ڴ���������ӳ�䷽ʽ

	float m_fFontRatio;  //����Ŵ����
	BOOL m_bVectorFont;  //�Ƿ�ʸ������
	BOOL m_bBusy;  //��ֹ��ͼ��������

	//Shader
	CShader m_cSmoothShader;

	BOOL m_bBackDraw;	//��̨��ͼ	2016.1.13

	//ʵ��

	COpenGL & operator=(const COpenGL & gl)
	{
		if(this==&gl) return *this;

		ASSERT(FALSE);

		return *this;
	}

	//OPENGL��ͼ׼��

	BOOL Init(HWND hWnd); //��ʼ����ͼ����
	void InitVariables(void);  //��ʼ������Ŀ�й�ϵ������,������Ŀ֮ǰҪ����,�����ʷ����
	BOOL ReleaseGraphicsDevice(void);  //�ر�OpenGL��ͼ�豸
	void CalProjectMatrix(int ScreenWidth,int ScreenHeight); //����ͶӰ��ʽ
	void Active(void); //���ǰ���ڣ����豸������ͼ�����
	void ReSize(int width, int height);

	//ȫ����ʾ
	BOOL FullScreen(BOOL bFullScreen=TRUE);

	//ͼ�ν����任
	void InitSize(const Vector4 &vmin,const Vector4 &vmax,float maxDiameter,float ratio); //�������ߴ�,���ָ���ԭʼ�Ŵ���
	void SetStory(int storymin,int storymax){m_iStoryMin=storymin;m_iStoryMax=storymax;} //����¥����ʾ��Χ
	void SetStage(int stepmin,int stepmax) {m_iStageMin=stepmin;m_iStageMax=stepmax;} //����ʩ���׶���ʾ��Χ
	void UpdateCoorRange(Vector4 &vmin,Vector4 &vmax){m_vMin=vmin;m_vMax=vmax;}  //����������ʾ��Χ
	BOOL SetProfile(const Vector4 *pProfile=NULL,int nProfile=4);  //��������������,���߽�˳�����У�ȱʡ4�������㣬������֮ǰ��ͬ�򷵻�TRUE
	void ShowSelectZone(const Vector4 &vMin,const Vector4 &vMax,BOOL bShow); //����ѡȡͼԪ������
	void ClearSelectZone() { m_bShowSelectZone = FALSE; };
	void ShowDriftPos(BOOL bShow);  //��ʾ���λ�ƽ�λ����Ϣ

	//�������в����������ԭ��������
	void Zoom(float fRatio,int ScreenWidth,int ScreenHeight); //�Ŵ���
	void RotateX(float ang); //����ĻX����ת
	void RotateY(float ang); //����ĻY����ת
	void Translate(int cx,int cy,int WinHeight); //�ƶ�ͼ��, cx,cyΪ�ƶ�����Ļ����,WinHeightΪ���ڸ߶�
	void LookAtRH(Vector4 &eye, Vector4 &lookat, Vector4 &up);  //����ģ�;���
	void SetViewRange(float fNear,float fFar);  //������Ұ��Χ,<=0ʱʹ��ȱʡֵ

	//��ʾʵ��
	void ShowByBody(void);
	//��ʾ���棬fNearΪ�������۾�����,bCrossSection�� TRUE-����ͼ����FALSE--����ͼ
	void ShowByProfile(float fNear,BOOL bCrossSection);

	//���ݽ���
	//�����߶�������
	void SetVex(int n,const CVertex *p);         //���붥�������ַ
	void SetNode(int n,const CVertex *p);         //���������������ַ
	const CVertex *GetNode(void){return m_pNode;}         //�õ���������ַ
	void SetDeformNode(int n,const CVertex *p){m_nNode=n; m_pDeformNode=p;}
	void SetNodeCenterSmooth(BOOL bNodeCenterSmooth) {m_bNodeCenterSmooth=bNodeCenterSmooth;}

	//��Ԫ����
	void SetQuadElm(int n,const CQuadElm *p) {m_nQuadElm=n;m_pQuadElm=p;} //�����ı��ε�Ԫ����
	void SetTriangleElm(int n,const CTriangleElm *p) {m_nTriangleElm=n;m_pTriangleElm=p;} //���������ε�Ԫ����
	void SetBeamElm(int n,const CBeamElm *p){m_nBeamElm=n;m_pBeamElm=p;}                 //��������Ԫ����
	void SetGroundElm(int nline,const RECT *pline) {m_nGroundLine=nline; m_pGroundLine=pline;}//���������������
	void SetGroundOffset(Vector4 offset) {m_vOffset=offset;} //��������ƫ�ƣ�һ��ÿ��ʱ����Ӧ��Ҫ���ø��£�ģ��������
	void SetBoundaryMesh(int n,const CBoundary *p){m_BoundaryMesh=n;m_pBoundaryMesh=p;}//����ڵ�Լ������


	//�������
	void SetGuides(int n,const CLine *p) {m_nGuides=n; m_pGuides=p;}             //���븨��������
	void SetLine(int n,const CLine *p) {m_nLineStruc=n; m_pLineStruc=p;}         //����ṹ������
	void SetBeam(int n,const CBeamStruc *p){m_nBeamStruc=n; m_pBeamStruc=p;}     //�����������ṹ����
	void SetSurf(int n,const CPlateStruc *p) {m_nPlateStruc=n; m_pPlateStruc=p;} //������ṹ����
	void SetSection(const CSectionCollection *pSec) {m_pSec=(CSectionCollection *)pSec;} //����������ݣ�ͨ��������ʾ
	void SetDamperSection(const CDamperSectionCollection *pSec) {m_pDamperSec =(CDamperSectionCollection *)pSec;} //����������ݣ�ͨ��������ʾ
	void SetEdgeStruc(const CEdgeStrucCollection *p){m_pEdgeCollection=p;}     //�����Ե��������
	void SetVisible(const CVisibleStruct *pVisible) {m_pVisible=pVisible;} //���빹���ɼ���Ϣ��ָ��
	void SetVisibleMesh(const CVisibleMesh *pVisibleMesh) {m_pVisibleElm = pVisibleMesh;} //���빹���ɼ���Ϣ��ָ��
	void SetVisibleResult(const CVisibleStruct* pVisibleResult) { m_pVisibleResult = pVisibleResult; } //���빹������ɼ���Ϣ��ָ�� 20241225 Ϳ���
	void SetBoundaryFrame(int n,const CBoundary *p){m_nBoundaryFrame=n;m_pBoundaryFrame=p;}//����ڵ�Լ������

	void SetSubElm(const SUB_ELM_INFO2 *pSubBeamInfo,const SUB_ELM_INFO3 *pSubTriInfo,
		const SUB_ELM_INFO4 *pSubQuadInfo,const CNode2ElmIndex *pNode2Elm) 
	{
		m_pNode2Elm=pNode2Elm;
		m_pSubQuadInfo=pSubQuadInfo;
		m_pSubTriInfo=pSubTriInfo;
		m_pSubBeamInfo=pSubBeamInfo;
	};
	void SetElmPrim(const Vector4* pTri, const Vector4* pQuad) { m_pTriPrim = pTri; m_pQuadPrim = pQuad;};

	//������Ƥ����ʾ״̬, ������Ƥ���������ζ�������
	//0-����ʾ
	//1-��Ļ�����߶Σ�vex1,vex2��Ϊ��Ļ���꣩
	//2-��Ļ������Σ�vex1,vex2��Ϊ��Ļ���꣩
	//3-��������߶�(vex1Ϊ��������,��Ϊͼ�ο����Ѿ����ƶ�����Ļ�����Ѿ���Ч��vex2Ϊ��Ļ����)
	//4-���������߶Σ�vex1,vex2��Ϊ��������
	int SetDragLine(int iType, float* vex1 = NULL, float* vex2 = NULL, BOOL bDrawVex1 = FALSE, BOOL bDrawVex2 = TRUE)
	{
		int oldtype = m_DragLineType;
		m_DragLineType = iType;
		if(vex1 == NULL)
			memset(m_ElasticVex1, 0,  3*sizeof(float));
		else
			memcpy(m_ElasticVex1, vex1, 3*sizeof(float));

		if(vex2 == NULL)
			memset(m_ElasticVex2, 0,  3*sizeof(float));
		else
			memcpy(m_ElasticVex2, vex2, 3*sizeof(float));

		m_bDrawElasticVex1 = bDrawVex1;
		m_bDrawElasticVex2 = bDrawVex2;

		return oldtype;
	}

	//������������, ���ͣ�0--���Ʒ�ձ߽��ߣ�1--���Ʋ���ձ߽��ߣ�2--�����������
	void SetDragPoly(int iType,const int *pvex1,int nvex) {m_iDragPolyType=iType,m_pDragPolyVex=pvex1;m_nDragPolyVex=nvex;} 

	//������㣬�����ַ������һ�μ���
	void SetVirtualPoint(const VIRTUAL_POINT_TYPE *piVirtualPoint,const Vector4 *pvVirtualPoint) 
		{m_piVirtualPoint=piVirtualPoint;m_pvVirtualPoint=pvVirtualPoint;} 

	//������ʾ��Ϣ,��ʾ�ڲ�׽��
	void SetHintMsg(CString &Hint){m_sHint=Hint;}  

	//���ù���ͼ����ʾλ��
	void SetZoomIconRect(const CRect &rect){m_rectZoomIcon=rect;} //�������Ź���ͼ��λ��
	void SetRotateIconRect(const CRect &rect){m_rectRotateIcon=rect;} //������ת����ͼ��λ��
	void SetMiniMapIconRect(const CRect &rect){m_rectMiniMapIcon=rect;} //����С��ͼ����ͼ��λ��

	//��ͼ��ʰȡ���̣�ֻ��ʰȡ��ͼ��ʱ����ṩ����
	void Draw(unsigned int PrimitiveType=STRUCT_UNKNOWN, unsigned int SecondaryType=0);
	int Pick(const CPoint &point,unsigned int PrimitiveType,int **pPBuf, unsigned int SecondaryType);  //��׽ĳһ���㴦��ͼԪ��pointΪ���λ��,PrimitiveTypeͼԪ����
	const int *GetPickedObj(void) {return m_pPickedIDG;}
	int GetPickedNum(void) {return m_nPickedObj;}
	int PickGroup(const CRect &rect,unsigned int PrimitiveType,int *&pNames, unsigned int SecondaryType=0); //��ѡһ��ͼԪ
	void SetCaptureID(int iCaptureID,bool bDraw = true) {m_iCaptureID = iCaptureID; if(bDraw) Draw();}
	int GetCaptureID(){return m_iCaptureID;}
	CPoint World2Client(const CVertex &p); //��������������Ļ����(ʵ��Ϊ��������)
	void World2Client(float *v, int *pt, const int nP); //��������������Ļ����(ʵ��Ϊ��������)
	Vector4 Client2World(int x, int y); //��Ļ���꣨ʵ��Ϊ�������꣩תΪ��������
	void Client2World(float *pt, float *pCoor, const int nPt = 1); //��Ļ���꣨ʵ��Ϊ�������꣩תΪ��������
	void Client2WorldCenter(int x, int y, float *pCoor); //��Ļ���꣨ʵ��Ϊ�������꣩תΪ��������,��Ұ������
	float GetPhysicalLength(int iClientLength); //�õ������ȣ���λ����
	float GetScreenLength(float fPhyLength); //�õ���Ļ���ȣ���λ������



	//���߶�p1-p2��ƽ��vPlaneNormal(��λʸ��)���ƶ�������Ļ����point����λ��q1-q2
	//�����ƶ��ķ�����룺0-ʧ�ܣ�1-X��2-Y��3-Z��4-�߶εķ���
	int MoveLineInPlane(const Vector4 &oldpoint,const CPoint &point,const Vector4 &vPlaneNormal,
		const CVertex &p1,const CVertex &p2, Vector4 &q1,Vector4 &q2);  
	//����vOld���߶�vOld-pConnPoint[i]�ƶ����µ�vNew���Զ��ж����������߶�
	//�����ƶ��ķ�����룺0-ʧ�ܣ�5-�߶η���
	int MovePointAlongLine(const CPoint &point,int nConnPoint,	const Vector4 *pConnPoint, const Vector4 &vOld, Vector4 &vNew);

	//��������
	//void SetTimeLoop(int iTimeLoop){m_iTimeLoop=iTimeLoop;}

	//ʵ�ʻ�ͼ�����귶Χ
	Vector4 m_vDrawRangeMin,m_vDrawRangeMax;


	//�����ӵ�ʸ��,��Ҫ���ڵ���
	Vector4 GetLookAt(void) {return m_vLookat;}
	Vector4 GetEye(void) {return m_vEye;}
	Vector4 GetUp(void) {return m_vUp;}
	float GetNear(void) {return m_zNear;}
	float GetFar(void) {return m_zFar;}
	float GetRatio(void) {return m_fRatio;}
	void SetRatio(float ratio) {m_fRatio=ratio;}
	HGLRC GetHRC(void) {return m_hGLRC;}
	void SetHRC(HGLRC hrc) {m_hGLRC=hrc;}

	Vector4 GetScreenX(void); //�õ���ĻX����(����Ϊ������)��λʸ����������������
	Vector4 GetScreenY(void); //�õ���ĻY����(����Ϊ������)��λʸ����������������

	GLvoid KillFont(GLvoid);									// Delete The Font
	GLvoid KillFontFixed(GLvoid);									// Delete The Font
	GLvoid BuildFont(BOOL bVectorFontFilled=TRUE); //bVectorFont�Ƿ�ʸ��������m_bVectorFont ���� �����ӿ���ʵ�������л� 2017��8��22��

	//ͼԪ��Ч��,�������귶Χ����¥�㷶Χ����Ϊ��Ч
	BOOL IsVisible(const CVertex &primitive) const;
	BOOL IsVisible(const CLine &primitive) const; 
	BOOL IsVisible(const CBeamStruc &primitive) const; 
	BOOL IsVisible(const CPlateStruc &primitive) const; 
	BOOL IsVisible(const CBeamElm &primitive) const; 
	BOOL IsVisible(const CTriangleElm &primitive) const; 
	BOOL IsVisible(const CQuadElm &primitive) const; 
	//20241225 Ϳ���
	BOOL IsResultVisible(const CBeamElm& primitive) const;
	BOOL IsResultVisible(const CTriangleElm& primitive) const;
	BOOL IsResultVisible(const CQuadElm& primitive) const;

	BOOL IsInClientRect(const CVertex &p,int iErr); //�жϵ��Ƿ�����Ļ�ڣ�����iErr���ص����
	BOOL IsDrawBody(void); //�Ƿ����ʵ�壬�������ųߴ�����ж�

	//�õ�ʵ�ʻ�ͼ�����귶Χ������m_vDrawRangeMin,m_vDrawRangeMax
	void GetDrawRange(void);

	GLvoid SetBackgroudColor(GLvoid);
	void SetTextType(int type);
	void InitPlateShowVexIndex();
	void InitBodyShow();
	bool bPickUpdate() {return m_bPickUpdate;}
	void SetBcGroupId(int iBc) { m_iBC = iBc; }
private:
	//����

	//������
	//int m_idVexBuffer;

	//��׽ͼ��
	int m_iCaptureID;   //���ȷ����ID
	int *m_pPickedIDG;  //��ʱ��׽��ͼԪIDG
	int *m_pPickBuf;  //��׽�õ���ʱ����
	int m_nPickedObj;  //ͬʱ��׽����ͼԪ��
	unsigned int m_iPrimaryType;
	bool m_bPickUpdate;

	//ͼԪ��������######### ���������� ###########
	//���½�����ָ�룬���ⲿ����ά���ڴ�,δע�������ݾ�Ϊ��������

	//���ü�������
	int m_iStoryMin,m_iStoryMax; //¥����ʾ��Χ
	Vector4 m_vMin,m_vMax; //������ʾ��Χ
	int m_iStageMin,m_iStageMax; ////����ʾͼԪ����ʼ�ͽ�ֹ���,��ܺ�������

	int m_nProfile;      //������������
	Vector4 m_pProfile[4]; //����������

	//��������
	int m_nNode;
	const CVertex *m_pNode;   //ԭʼ����������
	int m_nBeamElm,m_nTriangleElm,m_nQuadElm;
	const CBeamElm *m_pBeamElm; //����Ԫ����
	const CTriangleElm *m_pTriangleElm; //�����ε�Ԫ����
	const CQuadElm *m_pQuadElm;
	const CVertex *m_pDeformNode;   //���ε���������,������δ����һ��
	const CNode2ElmIndex *m_pNode2Elm;  //��㵽��Ԫ������
	const SUB_ELM_INFO2 *m_pSubBeamInfo;
	const SUB_ELM_INFO3 *m_pSubTriInfo;
	const SUB_ELM_INFO4 *m_pSubQuadInfo;
	const Vector4* m_pTriPrim;
	const Vector4* m_pQuadPrim;
	int m_BoundaryMesh;
	const CBoundary *m_pBoundaryMesh;   //�ڵ�Լ������


	int m_nGroundLine;  //���������������
	const RECT *m_pGroundLine;  //�����������������(ȡ��)
	Vector4 m_vOffset; //����ƫ������ģ��������

	//�������
	int m_nVex;
	const CVertex *m_pVex;   //ԭʼ����������
	int m_nGuides,m_nLineStruc,m_nBeamStruc,m_nPlateStruc;  //�������ͼԪ���������߲�ͬʱ����
	const CLine *m_pGuides;    //����������
	const CLine *m_pLineStruc;    //�ṹ������
	const CBeamStruc *m_pBeamStruc;    //������
	const CPlateStruc *m_pPlateStruc; //���������
	const CSectionCollection *m_pSec; //��������
	const CDamperSectionCollection *m_pDamperSec; //һ�����ӽ�����Ϣ	//�Ǳ��� 2015.5.19

	const CEdgeStrucCollection *m_pEdgeCollection;    //��Ե��������
	const CVisibleStruct *m_pVisible;  //�����ɼ���Ϣ��ָ��,��Ӧ��Ծ��
	const CVisibleMesh *m_pVisibleElm;
	const CVisibleStruct * m_pVisibleResult;//20241225 tutianchi
	int m_nBoundaryFrame;
	const CBoundary *m_pBoundaryFrame;   //�ڵ�Լ������
	int m_iBC;//��ǰ�߽����

	//��Ƥ����
	BOOL m_DragLineType;  //��Ƥ����ʾ��־,0-����ʾ,1-��Ļ�����߶�,2-��Ļ�������,3-�߶�(vex1Ϊ��������,vex2Ϊ��Ļ����)
	float m_ElasticVex1[3], m_ElasticVex2[3];  //��Ƥ������(��������),�����϶����εĶ���(��Ļ����,��ͼʱ����ת��)
	BOOL m_bDrawElasticVex1,m_bDrawElasticVex2; //�Ƿ������Ƥ����ĩ��

	//�����������λ�߽��ߣ���������
	const int *m_pDragPolyVex;  //�������
	int m_nDragPolyVex; //����
	int m_iDragPolyType;  //���ͣ�0--���Ʒ�ձ߽��ߣ�1--���Ʋ���ձ߽��ߣ�2--�����������

	//�����Ϣ
	const VIRTUAL_POINT_TYPE *m_piVirtualPoint;  //�Ƿ�������
	const Vector4 *m_pvVirtualPoint;  //�������

	//ѡȡͼԪ�����귶Χ
	BOOL m_bShowSelectZone; //�Ƿ���ʾѡȡͼԪ���ڵķ�Χ
	Vector4 m_vSelectMin;  //ѡȡͼԪ����С����
	Vector4 m_vSelectMax;  //ѡȡͼԪ���������

	//��ʾ���λ�ƽ�λ��
	BOOL m_bShowDriftPos;

	CString m_sHint;  //��ʾ��Ϣ
	float m_fAspect;  //�߿�ȣ�����ʰȡʱ����ͶӰ�����ڵ��û�ͼͶӰʱ����

	//ͼ������,��������
	CRect m_rectZoomIcon; //����ͼ��λ��,��ʼ������,���ȺͿ��
	CRect m_rectRotateIcon; //��ת����ͼ��λ��,��ʼ������,���ȺͿ��
	CRect m_rectMiniMapIcon; //С��ͼ����ͼ��λ��,��ʼ������,���ȺͿ��

	//#############


	//OpenGL�豸����---------------------------------------------------
	HWND m_hWnd;  //���ھ�����ⲿ����
	HDC m_hDC;    //�豸������ڲ����
	HGLRC m_hGLRC;//GL�豸������ڲ����
	BOOL m_bDeviceReady;  //�豸״̬
	GLUquadricObj *m_quad_obj;  //���ڻ��ƶ��ζ��� 

	//��ͼ����-----------------------------------------------------------
	Matrix4x4 m_ModelMatrix;  //ģ�ͱ任����
	float m_zNear;  //���࣬����ھ�ͷ
	float m_zFar;   //Զ�࣬����ھ�ͷ

	Vector4 m_vEye; // ��ͷλ��
	Vector4 m_vLookat; // ��ͷ��׼�ĵ�
	Vector4 m_vUp; // ��ͷ���Ϸ��ķ���
	float m_fRatio;  // m_fRatio�Ŵ�������

	//��ʾ�ַ��õĻ�������----------------------------------------------
	GLuint	m_iBase;				// Base Display List For The Font Set
	GLuint	m_iBaseFixed;			// �̶���С��λͼ����
	//BOOL m_bVectorFont;  //�Ƿ�ʸ������
	GLYPHMETRICSFLOAT m_gmf[256];	// Storage For Information About Our Outline Font Characters,bVectorFont=TRUEʱ��Ч
	GLYPHMETRICSFLOAT m_agmf[1];

	//����

	typedef struct													// Create A Structure
	{
		GLubyte	*imageData;											// Image Data (Up To 32 Bits)
		GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
		GLuint	width;												// Image Width
		GLuint	height;												// Image Height
		GLuint	texID;												// Texture ID Used To Select A Texture
	} TextureImage;													// Structure Name

	TextureImage m_Textures[2];
	float m_Roll;

	//ʵ��
	//�豸׼��
	BOOL InitGraphicsDevice(void);
	void MatrixOrthro(int ScreenWidth,int ScreenHeight); //����ͶӰ����
	void MatrixOrthoSelect(const CPoint &point); //����ʰȡ
	//����ѡȡ�õ�����ͶӰ����,����ѡ���������
	void MatrixOrthoSelect(const CRect &rect);
	void FixupGLExt(void);
	void InitResource(void);     //��ʼ����ͼ��Դ������ƹ⡢���ʡ���ͼ��
	BOOL ReleaseResource(void);  //�ͷ����л�ͼ��Դ

	//��ͼ
	//pVexΪԭʼ������߱������꣬���ƿ�ܽṹ�����񣬲���������ͼԪ����������Ƥ�������ȣ�
	//bOriginalΪTRUEʱ�������ߺͻ�ɫͼ
	void DrawPrimitives(const CVertex *pVex, unsigned int PrimitiveType,BOOL bOriginal, int SecondaryType=0);  //��������ͼԪ

	void DrawPoints( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal );  //���Ƶ㣬����Ԫ�����ܶ��㣬����ͳһ
	void DrawLines( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //���ƿ��--������
	void DrawGuides( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //������

	void DrawBeams(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //����������DrawPrimitive����
	void DrawPillars(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //��������б�Ź�������DrawPrimitive����
	void DrawPlates(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal); //���л��ư壬��DrawPrimitive����
	void DrawWalls(const CVertex *pVex,unsigned int PrimitiveType,BOOL bOriginal, int SecondaryType=0); //����ǽ����DrawPrimitive����
	void DrawEdges(const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal);  //���Ʊ�Ե����


	void DrawBeamWithBox(const CVertex *pVex,const CBeamStruc &line,COLORREF color,unsigned int PrimaryType); //���Ƴ�������
	void DrawPlateWithBody(const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); //������ά��
	//���񻯻�����ά��  //�Ǳ��� 2015.3.11
	void DrawPlateWithBodyTess(GLUtesselator* tobj,const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); 
	void DrawWallWithBody(const CVertex *pVex,const CPlateStruc &surf,COLORREF *pcolor,const int *PointID,int npoint); //������άǽ

	void DrawBeamElmWithBody(const CVertex *pVex,const CBeamElm &elm,const COLORREF *color,COLOR_TYPE color_type,unsigned int PrimaryType);  //ʵ�巽ʽ��������Ԫ
	void DrawTriElmWithBody(const CVertex *pVex,const CTriangleElm &elm,const COLORREF *color,COLOR_TYPE color_type);  //ʵ�巽ʽ���������ε�Ԫ
	void DrawQuadElmWithBody(const CVertex *pVex,const CQuadElm &elm,const COLORREF *color,COLOR_TYPE color_type);  //ʵ�巽ʽ�����ı��ε�Ԫ


	void DrawBeamElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal );  //��������Ԫ--����Ԫ
	void DrawTriangleElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal ); //��������Ԫ--�ı��ε�Ԫ
	void DrawQuadElms( const CVertex *pVex,unsigned int PrimaryType,BOOL bOriginal); //��������Ԫ--�����ε�Ԫ
	void DrawShadowPolys(unsigned int PrimaryType);  //�������Ķ��������


	void DrawOutlineCuboid(void); //����������������
	void DrawProfileFrame(void); //����������

	void DrawAxis(void);   //����������
	void DrawLocalAxis(float *coor,const Vector4& u,const Vector4& v,const Vector4& w);   //���ƾֲ������� �� 2017��12��18��
	void DrawSelectZone(void);  //����ѡȡ����ı��
	void DrawScale(void);  //�ڱ߿��ϻ�������̶�
	void DrawBackGround(void);
	void DrawGround(void);	//���Ƶ�������
	void DrawRestraints(const float *coor,const CBoundary &cbind);   //����λ��Լ�� �� 2017��12��18��
	void DrawRestraints(const float* coor, const int& pin); 
	void DrawAnticulate(const CBeamStruc& beam, const CVertex& v1, const CVertex& v2);

	BOOL LoadTGA(TextureImage *texture, LPCTSTR filename);

	//��ʾ�ַ�����֧�ֿ��ַ�,����ֱ���ASCII�ַ��Ϳ��ַ���ASCII�ַ�����ģ�壬Ч�ʽϸ�
	void glPrint(const CString &str);
	void glPrint(const char* str);

	//��ʾ�̶���С�ַ�����ֻ֧��ASCII��
	void glPrintFixed(const char* str);

	//��ʾ�̶���С�ַ�������ʾ��p1����X�᷽��//
	void DrawFixedTextAt(const char* str, const float *p1);

	//��ʾ�ַ�������ʾ��p1����X�᷽��
	void DrawTextAt(const CString &str, const float *p1);

	//��ʾ�ַ�������ʾ��p1--p2֮��
	void DrawTextRotate(const CString &str, const CVertex &p1, const CVertex &p2);  

	void GetStrings(const CString& cText, std::vector<short> &vPos);

	void DrawTextRotateMultiLine(const CString &str, const CVertex &p1, const CVertex &p2);

	//��ʾ��չ�ַ�����,ȫ��ת��Ϊ˫�ֽ��ַ��������Ч�ʱȽϵ�
	void DrawStringByWideChar(const char* str);

	//���ڻ�Բcoor[3]coorΪԲ����������,r--����뾶��iPlane��0-XYƽ�棬1-YZƽ�棬2-ZXƽ��
	void DrawCircle(float *coor,float r,int nPoint=4,int iPlane=0);
	void DrawSolidCircle(float *coor,float r,int nPoint=4,int iPlane=0);


	//���Ʊ�ǵ㣬vexΪ�������꣬mark_type�����״,MARKER_TYPE������ͣ�radius��ǳߴ�İ뾶�����أ�
	void DrawMarkerPoint(const Vector4 &vex, int mark_type, int radius=5);

	//����α���ģ�����Ч��,������ɫֵ��������OpenGL�������û�ͼ��ɫ
	//vn--���߷���
	BOOL SetGLColor(const Vector4 &vn,const BYTE * RGBA,BYTE alpha=127);

	//����α���ģ�����Ч��,������ɫֵ��������OpenGL�������û�ͼ��ɫ
	//�����������㲻�ܹ���
	BOOL SetGLColor(const CVertex &p1,const CVertex &p2,const CVertex &p3,const BYTE *RGBA,BYTE alpha=127); //���������Ķ���λ�ͼ��ɫ,�ɹ�����TRUE
	BOOL SetGLColor(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,const BYTE *RGBA,BYTE alpha=127); //���������Ķ���λ�ͼ��ɫ,�ɹ�����TRUE

	BOOL CheckValid(void);

	//��ʾ������ʾ��p1--p2֮��
	void DrawBeamRein(const CBeamStruc &beam, const CVertex &p1,const CVertex &p2);  
	//��ʾ������ʾ��p1--p2֮��
	void DrawPillarRein(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);  
	//��ʾǽ����ʾ��p1--p2֮��
	void DrawWallRein(const CPlateStruc &wall,const CVertex &p1,const CVertex &p2,const CVertex &p3,const CVertex &p4);  
	//ʸ����ʾ������
	void DrawVectorTextAt(const CString &str,const Vector4 &p1,const Vector4 &p2, int iRowPos=1);
	//��ʾ������������ʾ��p1--p2֮��
	void DrawForce(const CString &str1,const CString &str2,const CVertex &p1,const CVertex &p2);  
	//��ʾ��������
	void	DrawBeamText(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);
	//��ʾ�ַ�������ʾ��p1--p2֮��
	void DrawTextMulineXY(const CString &str, const float* p1, const float* p2);  
	//��ʾ�ַ�������ʾ��p1--p2֮��
	void DrawTextMulineXZ(const CString &str, const float* p1, const float* p2);  
	//��ʾ����������
	void	DrawPillarText(const CBeamStruc &beam,const CVertex &p1,const CVertex &p2);
	//��ʾǽ������
	void	DrawWallText(const int &iWall, const CVertex *pVex);

	//2021 Qiuhai add
	bool ShowAuxVariablesInit();
	bool bInitBodyShow;
	void SetVertexVisible();
	void GetPlateBox(std::unordered_map<Vector4, unsigned int, hash_vec> VertexIndex, std::vector<Vector4> &vVex, std::vector<std::vector<std::vector<int>>> &vPlateBox);
	void GetBeamBox(std::unordered_map<Vector4, unsigned int, hash_vec> VertexIndex, std::vector<Vector4>& vVex, std::vector<std::vector<std::vector<int>>>& vBeamBox, std::vector<short>& pShape);

	enum SHOWTYPE
	{
		TYPE_OLD,
		TYPE_CALLIST,
		TYPE_VBO,
	}m_ShowType;
	void BulidBeamCallList();
	std::vector<bool> m_vbPtVisible;
	std::vector<std::vector<int>> m_vPlateId;
	std::vector<float> m_vPlateCenter;
	std::vector<Vector4> m_vShowVex;
	std::vector<short> m_pBeamShape;
	std::vector<std::vector<std::vector<int>>> m_vBeamBox;
	std::vector<std::vector<std::vector<int>>> m_vPlateBox;
	std::vector<bool> m_vbConcavePolygon;//for ConcavePolygon
	std::vector<GLdouble> m_vPolygonCoor;//for ConcavePolygon

	void DrawBeamWithBox(const CVertex *pVex, int iBeam,COLORREF color,unsigned int PrimaryType); //���Ƴ�������
	void DrawPlateWithBox(const CVertex *pVex, int iPlate,COLORREF *pcolor); //������ά��
	void DrawPlateWithBoxTess(GLUtesselator* tobj, const CVertex* pVex, int iPlate, COLORREF* pcolor);
	bool isConcavePolygon(const CVertex* pVex, int iPlate);

	void UpdateConstVars();
	GLfloat m_UnitPhysicalLength;
	GLfloat m_UnitScreenLength;
	GLfloat m_fLocalAxisLenth;
	GLfloat m_fGlobalAxisLenth;
	GLfloat m_fVFontR;
	bool m_bDrawBody;

	GLuint m_ListLocalAxis;
	GLuint m_ListGlobalAxis;
	GLuint m_ListBnd;
	GLvoid BuildLocalAxis(GLvoid);
	GLvoid KillLocalAxis(GLvoid);		
	GLvoid BuildGlobalAxis(GLvoid);
	GLvoid KillGlobalAxis(GLvoid);	
	GLvoid BuildRestraints(GLvoid);
	GLvoid KillRestraints(GLvoid);	
	GLclampf m_BackgroundColor[3];
	HFONT m_Font;
	GLfloat m_fFontH;
	float m_fFontPos[3];
	Vector4 m_vOffSetEye;
	enum LABEL_TYPE
	{
		LABEL_DEFAULT = -1,
		LABEL_NONE,      //�����ǩ
		LABEL_SECTION,   //����
		LABEL_THICKNESS, //���
		LABEL_RATIO,	 //�����
		LABEL_DIRECTION, //�ֽ��
		LABEL_MAT,		 //����
		LABEL_LOAD,		 //����
		LABEL_XBIND,     //X����Լ��
		LABEL_YBIND,	 //Y����Լ��
		LABEL_ZBIND,	 //Z����Լ��
		LABEL_XROTATE,	 //X��ת��
		LABEL_YROTATE,	 //Y��ת��
		LABEL_ZROTATE,	 //Z��ת��
		LABEL_VEXID,      //���Ż򹹼����
		LABEL_ID,			//��Ԫ�Ż򹹼���
		LABEL_BEAM,			//������ ������ �� 2016��2��17��
		LABEL_RESULTS,		//������ �� 2016��3��8��
		LABEL_WALLBEAMCOEF,	//������ �� 2016��3��8��
		LABEL_MIDCONSTITUTIVE,	//���𹹼�����Ŀ�� �� 2016��8��11��
		LABEL_RARECONSTITUTIVE,	//���𹹼�����Ŀ�� �� 2016��8��11��
		LABEL_MEMBERPERFORMOBJECT,	//���𹹼�����Ŀ�� ������ 2022��12��23��
		LABEL_VIPTYPE,			//��Ҫ������
		LABEL_DETAILSSEISMICGRADE,//�����������ʩ�ȼ� �� 2017��10��9��
		LABEL_SEISMICGRADE,		//��������ȼ� �� 2017��10��9��
		LABEL_MEMBERNAME,		//��������
		LABEL_CHECKRESULTS,		// ������
		LABEL_TOWERID,			//����
		LABEL_STEELSECCALC,		//�ֽṹ��������
		LABEL_REINFORCEMENT,   //�������
		LABEL_FORCEADJUSTMENT,//��������ϵ��
		LABEL_MEMBERFORCE,//��������
		LABEL_DEFECT,		 //ȱ��
		LABEL_SEMIRIGID,    //��������ӱ�ʶ��ʾ ��ҵ�� 2022��12��21��
		LABEL_SHEARNONLINEAR,  //���з�������Ϣ ����� 2023��1��15��
		LABEL_REINFORCEDCOMPONENTS, // �ӹ̹�����ʶ��ʾ ��ҵ�� 2023��4��14��
		LABEL_BLASTWALL, //����ǽ������ ����20230710
		LABEL_MAT_REINFORCED,		 //�ӹ̲��� ��ҵ�� 2023��8��16��
		LABEL_RATIO_JG,
	};
	char m_TextType;
};

