#pragma once
#include "HeadDefine.h"
#include "SectionBaseHead.h"


//����������
struct SECTION_PARA
{
	CString name;
	CString memo;
};

struct _SSG_DLLIMPEXP SECTION_TYPE_PROP_TABLE  //�����������Ա�
{
	SECTION_MAT_TYPE iMatType;		//����ID
	CString sMatCode;		//����������д
	CString sMatName;		//��������
};

//��������Ͷ�Ӧ������
struct _SSG_DLLIMPEXP PLATE_SECTION_MAT_TYPE
{
	SECTION_MAT_TYPE iMatType; //����ID
	CString sMatCode;		//����������д
	CString sMatName;		//��������
};

//�ӽ������ͱ�
struct _SSG_DLLIMPEXP SUBSECTIONTYPE_PROP_TABLE
{
	SUBSECTION_MAT_TYPE iMatType;	//�������ʹ���
	CString sMatCode;					//����������д
	CString sMatName;			//��������

	static CString &GetNameByType(SUBSECTION_MAT_TYPE itype);
};

//������״���Ա�
struct _SSG_DLLIMPEXP SECTION_SHAPE_PROP_TABLE   
{
	SECTION_SHAPE iShape;  //��״ģ��ID
	CString sName;   //��״ģ������
	SECTION_MAT_TYPE iType;  //��������
	SUBSECTION_SHAPE subshape[2]; //��Ӧ���ӽ�����
	SECTION_TYPE iSectionType; //�������� ��ҵ�� 2024��12��26��
};

class _SSG_DLLIMPEXP CSectionBase
{
public:
	CSectionBase(void);
	~CSectionBase(void);

public:
	static float DrawRect(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float theta=0, float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,BOOL bShowLabel=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //��,��
	static float DrawBox(CDC *pdc,float t2=0.5f,float t3=0.8f,float tf1=0.1f,float tw1=0.1f,float tf2=0.1f,float tw2=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCirc(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //ֱ��
	static float DrawPipe(CDC *pdc,float t2=0.8f,float tw=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);  //�⾶,���
	static float DrawI(CDC *pdc,float H1=0.8f,float tw=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,float p2=0,float p3=0,float theta=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC, BOOL bLabelChange = FALSE);
	static float DrawCross(CDC *pdc,float H1=0.8f,float tw1=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,
		float H2=0.8f,float tw2=0.1f,float B3=0.6f,float tf3=0.1f,float B4=0.7f,float tf4=0.1f,
		float p2=0,float p3=0,float theta=0,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

	static float DrawCriss(CDC *pDC,float B=0.05f,float H=0.45f,float U=0.2f,float T=0.05f,float D=0.2f,float F=0.2f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawRegPoly(CDC *pdc,float B=0.8f,float N=6,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //����⾶
	static float DrawHex(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //����⾶
	static float DrawChannel(CDC *pDC,float B=0.1f,float H=0.8f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDblChannel(CDC *pDC,float B=0.1f,float H=0.6f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=1.1f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDoubleLimbsChannel(CDC* pDC, float B = 0.1f, float H = 0.6f, float U = 0.4f, float T = 0.1f, float D = 0.4f, float F = 0.1f, float maxsize = 1.1f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC);
	static float DrawT(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.4f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawL(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.2f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawTrapezoid(CDC *pdc,float B=0.4f,float H=0.8f,float T=0.1f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawArbitrary(CDC *pDC, float *fValue, int num, BOOL clockwise, float p2, float p3, float fWidth, float fHeight, float maxsize=1.0f, BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDoubleLimbsH(CDC* pDC, float Hs, float tw1, float B1, float tf1, float d1, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawFourLimbsL(CDC* pDC, float B, float H, float D, float F, float d1, float d2, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawHSteelAddPlate(CDC* pDC, float Hs, float tw1, float B1, float tf1, float ts,float Bs, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawDoubleLimbsL(CDC* pDC, float B, float H, float D, float F, float d1, float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType);
	static float DrawThreeLimbsPipe(CDC* pdc, float B, float H, float Ds = 0.8f, float tw = 0.1f, float p2 = 0, float p3 = 0, float theta = 0, float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC);  //�⾶,���


	static float DrawHanOuter(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float b1=0.4f, float h1=0.4f, float hf1=0.15f, float hf2=0.15f,
		float tc1=0.15f, float tc2=0.15f, float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawHanInnerConc(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawHanInnerPipe(CDC *pDC, float B=2.0f, float H=2.0f, float D=0.4f, float t=0.08f,
		float ac1=0.04f, float ac2=0.04f, float ac3=0.04f, float ac4=0.04f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE, SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	//���Ʊ�ע�ߺͱ�ע����,x1,y1,x2,y2--��ĩ���߼�����,str-�ַ���,Ϊ��ʱֻ����
	//Pos=����λ�ã�0-�߼䣬1-�Ҷˣ�2-���
	//ArrowType��ͷ���ͣ�0-���ˣ�1-�Ҷˣ�2-���,3-�޼�ͷ
	static void DrawLabel(CDC *pdc,int x1,int y1,int x2,int y2,LPCTSTR str,COLORREF color=RGB(0,0,0),int ArrowType=0,int Pos=0,float ratio=1.0f); 

    //���Ƴ�������ά,xc,yc,b,h--���ĺͱ߳�
    static void DrawRectFibre(CDC *pDC,const float ratio,float xc,float yc,float b,float h);

    //����Բ����ά,xc,yc,r--���ĺͰ뾶
    static void DrawCircFibre(CDC *pDC,const float ratio,float xc,float yc,float r);

    //����Բ�θֽ�,xc,yc,r--���ĺͰ뾶
    static void DrawRebar(CDC *pDC,const float ratio,float xc,float yc,float r);

	//����ǽ�����
	static float DrawThick(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //��,��

public:
	//�ӹ̹������� ��ҵ�� 2023��5��16
	static float DrawBoxReinForced(CDC* pdc, float t2 = 0.5f, float t3 = 0.8f, float tf1 = 0.1f, float tw1 = 0.1f, float tf2 = 0.1f, float tw2 = 0.1f, float p2 = 0, float p3 = 0, float theta = 0,
		float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC, SUBSECTION_REINFORCED_TYPE iMethod = BEAM_ENLARGED_SECTION_TYPE, BOOL bDiagram = FALSE);
	static float DrawRectReinForced(CDC* pDC, float B, float H, BOOL bClockwise, float p2, float p3, float theta, float maxsize, BOOL bShowCoorAxis, BOOL bShowLabel, SUBSECTION_MAT_TYPE iMatType);
	static float DrawArbitraryReinForced(CDC* pDC, float* fValue, int nValue, BOOL bClockwise, float p2, float p3, float fWidth, float fHeight,
		float maxsize, BOOL bShowCoorAxis, SUBSECTION_MAT_TYPE iMatType, SUBSECTION_REINFORCED_TYPE iMethod, int num, BOOL bDiagram=FALSE);
	static float DrawPlateBoxReinForced(CDC* pdc, float t2 = 0.5f, float t3 = 0.8f, float tf1 = 0.1f, float tw1 = 0.1f, float tf2 = 0.1f, float tw2 = 0.1f, float p2 = 0, float p3 = 0, float theta = 0,
		float maxsize = 0.8f, BOOL bShowCoorAxis = TRUE, SUBSECTION_MAT_TYPE iMatType = SUBSECTION_MAT_TYPE_CONC, PLATE_REINFORCED_METHOD iMethod = PLATE_METHOD_ENLARGED_SECTION);

};


class _SSG_DLLIMPEXP CColorButton:public CButton
{ 
public:
	COLORREF m_Color;

	CColorButton():CButton(),m_Color(0){}; //���캯��
	void ChangeColor(COLORREF color); //�ı���ɫ
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//���صĺ���
};

void RotateCoord(float &x1, float &y1, float x, float y, float theta);
