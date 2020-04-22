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
};

class _SSG_DLLIMPEXP CSectionBase
{
public:
	CSectionBase(void);
	~CSectionBase(void);

public:
	static float DrawRect(CDC *pdc,float t2=0.5f,float t3=0.8f,float p2=0,float p3=0,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //��,��
	static float DrawBox(CDC *pdc,float t2=0.5f,float t3=0.8f,float tf1=0.1f,float tw1=0.1f,float tf2=0.1f,float tw2=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCirc(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //ֱ��
	static float DrawPipe(CDC *pdc,float t2=0.8f,float tw=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);  //�⾶,���
	static float DrawI(CDC *pdc,float H1=0.8f,float tw=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawCross(CDC *pdc,float H1=0.8f,float tw1=0.1f,float B1=0.6f,float tf1=0.1f,float B2=0.7f,float tf2=0.1f,
		float H2=0.8f,float tw2=0.1f,float B3=0.6f,float tf3=0.1f,float B4=0.7f,float tf4=0.1f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

	static float DrawCriss(CDC *pDC,float B=0.05f,float H=0.45f,float U=0.2f,float T=0.05f,float D=0.2f,float F=0.2f,
		float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);

	static float DrawRegPoly(CDC *pdc,float B=0.8f,float N=6,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //����⾶
	static float DrawHex(CDC *pdc,float t2=0.8f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); //����⾶
	static float DrawChannel(CDC *pDC,float B=0.1f,float H=0.8f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawDblChannel(CDC *pDC,float B=0.1f,float H=0.6f,float U=0.4f,float T=0.1f,float D=0.4f,float F=0.1f,float maxsize=1.1f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC);
	static float DrawT(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.4f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawL(CDC *pdc,float B=0.1f,float H=0.4f,float D=0.2f,float F=0.1f,float maxsize=0.6f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 
	static float DrawTrapezoid(CDC *pdc,float B=0.4f,float H=0.8f,float T=0.1f,float F=0.1f,float maxsize=0.8f,BOOL bShowCoorAxis=TRUE,SUBSECTION_MAT_TYPE iMatType=SUBSECTION_MAT_TYPE_CONC); 

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

};


class _SSG_DLLIMPEXP CColorButton:public CButton
{ 
public:
	COLORREF m_Color;

	CColorButton():CButton(),m_Color(0){}; //���캯��
	void ChangeColor(COLORREF color); //�ı���ɫ
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//���صĺ���
};
