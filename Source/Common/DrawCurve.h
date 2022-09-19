#pragma once

#include "SysPara.h"
#include "HeadDefine.h"

//����������
enum AXIS_TYPE
{
	AXIS_LINEAR,  //���Ը�����
	AXIS_LINEAR_INTEGER,  //����������ע
	AXIS_LINEAR_STORY_HEIGHT,   //¥��+�̱߳�ע
	AXIS_LOG,     //����
	AXIS_RECIPROCAL,   //�����ᣬ������ע����ĸΪ����������Ϊ1
};

//static int g_Reciprocal[]={500,200,100,50,10};  //��ѡ�ĵ�����ĸ
static int g_Reciprocal[]={2000,1000,500,200,100,50,10};  //��ѡ�ĵ�����ĸ

//��ת��ʾ�ַ���
extern "C" _SSG_DLLIMPEXP void  TextOutRotate(CDC *pDC,int x,int y,const CString &str,LONG lfHeight=Sys_DefaultFontSize,LONG angle=0,LONG lpWeight=FW_NORMAL);

//һ��ʱ�䲽������
class CCurveDataStatic
{
public:
	CCurveDataStatic(int npoint,float ftime,const float *px,const float *py)
	{
		nPoint=npoint;
		fTime=ftime;
		pX=new float[nPoint];  ASSERT(pX);
		pY=new float[nPoint];  ASSERT(pY);
		for(int i=0;i<nPoint;i++)
		{
			pX[i]=px[i];
			pY[i]=py[i];
		}
	}

	~CCurveDataStatic()
	{
		nPoint=0;
		fTime=0;
		delete[] pX;
		delete[] pY;
	}

	int nPoint;    //����
	float fTime; //ʱ��
	float *pX;     //X����
	float *pY;     //Y����
};

//����ʱ�䲽���ݼ���
class CCurveDataDyna
{
public:
	CCurveDataDyna(const CString &sname,BOOL bEnvelope1,BOOL bEnvelope2) 
	{
		sName=sname;
		m_bEnvelope1=bEnvelope1;
		m_bEnvelope2=bEnvelope2;
		m_pEnvelope1=NULL;
		m_pEnvelope2=NULL;
	}

	~CCurveDataDyna()
	{
		for(int i=0;i<aDataPtr.GetCount();i++)
		{
			delete aDataPtr[i];
		}
		aDataPtr.RemoveAll();
		delete[] m_pEnvelope1;
		delete[] m_pEnvelope2;
	}

	CString sName; //��������
	CArray<CCurveDataStatic*,CCurveDataStatic*> aDataPtr;   //���ݣ�ÿһ��ʱ�̶�Ӧһ�������ַ

	//������Xֵ������Ҫ�洢Yֵ
	float *m_pEnvelope1;  //��һ���ް�����Xֵ��¥�����ֵ
	float *m_pEnvelope2;  //�ڶ����ް�����Xֵ��¥����Сֵ
	BOOL m_bEnvelope1;
	BOOL m_bEnvelope2;
	void ClearEnvelope()  //����ʼ�����������ݣ���ɾ������
	{
		if(aDataPtr.GetCount()==0) return;
		int nPoint=aDataPtr[0]->nPoint;
		if(m_pEnvelope1)
			for(int i=0;i<nPoint;i++) m_pEnvelope1[i]=0;
		if(m_pEnvelope2)
			for(int i=0;i<nPoint;i++) m_pEnvelope2[i]=0;
	}
	void UpdateEnvelope(int iPoint,float x) //���°���������
	{
		if(m_pEnvelope1)
			m_pEnvelope1[iPoint]=max(m_pEnvelope1[iPoint],x);
		if(m_pEnvelope2)
			m_pEnvelope2[iPoint]=min(m_pEnvelope2[iPoint],x);
	}

	int AddStep(int nPoint,float ftime,const float *px,const float *py)  //����һ��ʱ�䲽��ͬʱ��������������
	{
		CCurveDataStatic *pstep=new CCurveDataStatic(nPoint,ftime,px,py);
		int istep=aDataPtr.Add(pstep);
		
		//�����һʱ������ʱ��������������,������һʱ�����ݵ�Y������
		if(aDataPtr.GetCount()==1)
		{
			if(m_bEnvelope1) 
			{
				delete[] m_pEnvelope1;
				m_pEnvelope1=new float[nPoint];
			}
			if(m_bEnvelope2) 
			{
				delete[] m_pEnvelope2;
				m_pEnvelope2=new float[nPoint];
			}
			ClearEnvelope();
		}
		return istep;
	}

	CCurveDataStatic *GetStepPtr(int istep)  //ȡ��ĳ��ʱ�䲽�������׵�ַ
	{
		if(istep<0) return NULL;
		if(istep>=aDataPtr.GetCount()) return NULL;
		return aDataPtr[istep];
	}

	int GetStepCount(void) {return aDataPtr.GetCount();}  //�õ��ܲ���
};

// CDrawCurve

class  _SSG_DLLIMPEXP CDrawCurve : public CStatic
{
	DECLARE_DYNAMIC(CDrawCurve)

public:

	BOOL m_bShowLegend;  //�Ƿ���ʾͼ��
	BOOL m_bEnvelopeVisible;  //�Ƿ���ʾ������
	BOOL m_bCurveVisible;  //�Ƿ���ʾ��̬����

	//�����������ݣ�ÿ���������ݶ���������������ϵ
	CArray<CCurveDataDyna*,CCurveDataDyna*> m_aCurvePtr;

	//����һ�����ߣ������������
	int AddCurve(const CString &sName,BOOL bEnvelope1,BOOL bEnvelope2);  

	//����һ�����ߵ�ʱ�䲽���ݣ�����ʱ�䲽���
	int AddCurveStep(int idCurve,int nPoint,float ftime,const float *px,const float *py);  

	//�����������ʽ
	void SetAxisX(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AXIS_TYPE type=AXIS_LINEAR);
	void SetAxisY(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AXIS_TYPE type=AXIS_LINEAR);

	//�����������
	int GetCurveCount(void) {return m_aCurvePtr.GetCount();}

	//��ȡʱ�䲽��
	int GetStepCount(int idCurve);

	//��ȡ���ʱ�䣬��λ����
	float GetMaxTime(int idCurve);

	//��ȡ�����������ʱ�䣬��λ���� �� 2021��3��1��
	float GetMaxTime();

	//��ȡĳʱ�䲽��ʱ�̣��������ʱ�䲽ʱ�������ʱ�̣���λ����
	float GetStepTime(int idCurve,int iStep);

	//��ȡ��������
	float ClientToPhysics_X(int ix);  //��ͼ����ת��Ϊ��������,ixΪ�ؼ����ھֲ�����x
	float ClientToPhysics_Y(int iy);  //��ͼ����ת��Ϊ��������,iyΪ�ؼ����ھֲ�����y


	//��ͼ,fTime--ʱ��
	void Paint(float fTime,BOOL bDrawEnvelop,BOOL bDrawCurve);

	//�����ͼ��Ͱ�������
	int CreateGraphData( int i, float &fTime, float *&px,float *&py);

	//�ָ�ԭʼ�ߴ�
	void Restore();


	//���û�ͼ������ؼ����ڱ߽�ľ���
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);

	//�����ż�ֵ��ʾ״̬���ż�ֵ
	void SetThreshold(BOOL bThresholdX, float fThresholdX, BOOL bThresholdY, float fThresholdY);

	COLORREF m_CurveColor[7];  //ǰ�������ߵ���ɫ
	int m_PenStype[7];   //ǰ�������ߵ�����, �ο�CPen��nPenStyleȡֵ
	COLORREF m_EnvelopColor;  //��������ɫ

	void SetTitle(const CString &sTitle) {m_sTitle=sTitle;}  //�������߱���

	void Clear();  //���ȫ������

	void ClearEnvelope(void)   //ֻ����������ݣ���ɾ����������
	{
		for(int i=0;i<GetCurveCount();i++)
		{
			CCurveDataDyna *pCurve=m_aCurvePtr[i];
			if(!pCurve) continue;
			pCurve->ClearEnvelope();
		}
	}

	//���������������Ӱ������ߣ�iEnv=0 ���� 1 ƽ����ֻ�����һ������İ��粻�ܲ��Ŷ��� �� 2017��11��27��
	void AddEnvelopeCurve(int iEnv);
	//�ı�Y������������Χ �� 2018��5��11��
	void SetAxisRangeY(float fStart,float fEnd);

	//���°��������ֵ����
	void UpdateRange();
public:
	CDrawCurve();
	virtual ~CDrawCurve();

protected:

	CString m_sTitle;  //ͼ�α���

	//�����Сֵ���Զ�����
	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxX_Y; //X���ֵ��Ӧ��Y����
	float m_fMinX_Y; //X��Сֵ��Ӧ��Y����

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //��Ч��ͼ������ؼ������ĸ��߽�ľ���
	CRect m_DrawRect;  //��Ч��ͼ���򣬿ͻ���������

	//������Ŵ�����й�
	float m_fRatioX,m_fRatioY;
	float m_fVisibleMinX,m_fVisibleMaxX;  //���ڴ��ڷŴ�,����X������ֵ��Χ
	float m_fVisibleMinY,m_fVisibleMaxY;  //���ڴ��ڷŴ�,����Y������ֵ��Χ

	BOOL m_bLPressed;  //�������
	CRect m_Drag,m_oldDrag;  //�϶�����

	//���������
	CString m_sXName,m_sYName;  //����������
	float m_fScaleMinX;
	float m_fScaleMinY;
	float m_fScaleMaxX;
	float m_fScaleMaxY;
	float m_fDX,m_fDY;  //�̶ȼ��
	AXIS_TYPE m_XAxisType;  //X������
	AXIS_TYPE m_YAxisType;  //X������
	BOOL m_bShowX,m_bShowY;  //�Ƿ���ʾ������Ϳ̶�

	//�ż�ֵ
	float m_fThresholdX,m_fThresholdY;
	BOOL m_bThresholdX,m_bThresholdY;

	enum
	{
		MOVING,
		ENLARGE,
		NOTHINGTODO,
	}m_Tools;

	enum
	{
		DRAGNONE,
		DRAGINFO,
		DRAGLEGEND,
	}m_DragType;

	CRect m_rtLegend;  //ͼ������

protected:
	CPoint PhysicsToClient(float x,float y);  //��������ת��Ϊ��ͼ����
	void UpdateRatio(); //�����ͼ����
	void DrawAxis(CDC &dc); //��������
	void DrawLegend(CDC &dc); //����ͼ��

protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


class  _SSG_DLLIMPEXP CHysCurvePic : public CStatic
{
	DECLARE_DYNAMIC(CHysCurvePic)

public:
	CHysCurvePic(void);
	virtual ~CHysCurvePic();

	//�����������ⲿ������
	int m_nStage;   //ʱ�����
	float *m_pTime; //ʱ�����飬һά������Ϊm_nStage  ���λ��
	int m_nCurve;  //������
	float * m_pData;  //������˳��洢����ά����СΪm_nCurve*m_nStage	������
	float * m_pTime0;  //ʱ�����飬һά������Ϊm_nStage
	CString * m_psName;  //�����������飬һά������Ϊm_nCurve
	CString m_sID;  //ͼԪ��ʶ
	CString sXName;
	CString sYName;
	CRect m_rtLegend;  //ͼ������
	BOOL m_pbShow[64]; //�Ƿ���ʾÿ������


public:
	//pTime--ʱ��㣬pData-������˳�����δ洢���ݣ���ά����СΪnCurve*nStage��psName--������������
	void SetData(int iType,int nStage, float *pTime0,int nCurve, float * m_pTime,float * pData, CString * psName);
	CPoint GetClientCoor(float x,float y);  //��������ת��Ϊ��ͼ����
	void GetRatio(); //�����ͼ����m_fRatioX��m_fRatioY,��Ļ����=ratio*������
	void DrawAxis(CDC &dc); //��������
	void Restore(void);
	//���û�ͼ������ؼ����ڱ߽�ľ���
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);

	void Viewdata();

private:

	//������Ŵ�����޹�
	float m_fMax,m_fMin;  //����ֵ��Χ.

	//������Ŵ�����й�
	float m_fRatioX,m_fRatioY; //��Ļ����=ratio*������
	float m_fX0,m_fX1;  //���ڴ��ڷŴ�

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //��Ч��ͼ������ؼ������ĸ��߽�ľ���
	CRect m_DrawRect;  //��Ч��ͼ����

	COLORREF m_CurveColor[7];

	DECLARE_MESSAGE_MAP()
public:
	void Paint(float fTime);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Clear(void);

};