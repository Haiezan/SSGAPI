#pragma once

//����������
enum AAXIS_TYPE
{
	AAXIS_LINEAR,  //���Ը�����
	AAXIS_LINEAR_INTEGER,  //����������ע
	AAXIS_LINEAR_STORY_HEIGHT,   //¥��+�̱߳�ע
	AAXIS_LOG,     //����
	AAXIS_RECIPROCAL,   //�����ᣬ������ע����ĸΪ����������Ϊ1
};

enum ALEGEND_POS
{
	ALPOS_TOPRIGHT,
	ALPOS_TOPLEFT,
	ALPOS_BTNRIGHT,
	ALPOS_BTNLEFT
};

static int g_ReciprocalA[]={500,200,100,50,10};  //��ѡ�ĵ�����ĸ

//��ת��ʾ�ַ���
void TextOutRotateA(CDC *pDC,int x,int y,const CString &str,LONG lfHeight=14,LONG angle=0,LONG lpWeight=FW_NORMAL);

// һ��ͼ�����ò���,���ں�����ĵ���
struct CDrawSetting
{
	CString sTitle;
	CRect rc;
	int nRightWidth,nSingleHeit;		// �ұ�Ԥ����ȡ����и߶�
	int nLeft,nTop,nRight,nBottom;		// imargain
	CString sXAxisName,sYAxisName;
	int nXAxisMesh,nYAxisMesh;
	BOOL bXAxis,bYAxis;		//�Ƿ���ʾ������Ϳ̶�
	AAXIS_TYPE tXAxis,tYAxis;
	BOOL bDrawRect;
	BOOL bLegend;
	BOOL bSeries;
	BOOL bSeriesMaxOrMin;	// max=true
	BOOL bMainAxis;			// x-true y-false���ᣬ����ȷ��ͼ�������ֵ�������ʽ
	ALEGEND_POS posLegend;
	ALEGEND_POS posSeries;
	CDrawSetting() {nRightWidth=0;tXAxis=tYAxis=AAXIS_LINEAR;bXAxis=bYAxis=TRUE;bDrawRect=TRUE;bLegend=bSeries=FALSE;bSeriesMaxOrMin=TRUE;
	nLeft=nTop=nRight=nBottom=0;bMainAxis=TRUE;posLegend=ALPOS_TOPRIGHT;posSeries=ALPOS_BTNRIGHT;}
};

//һ�����ߵ�����
class CACurveData
{
public:
	CACurveData() {nPoint=0;pX=pY=NULL;}
	CACurveData(int npoint,CString szstr,const float *px,const float *py,int nSta)
	{
		nPoint=npoint;
		nStart=nSta;
		sName=szstr;
		pX=new float[nPoint];  ASSERT(pX);
		pY=new float[nPoint];  ASSERT(pY);
		for(int i=0;i<nPoint;i++)
		{
			pX[i]=px[i];
			pY[i]=py[i];
		}
	}

	CACurveData& operator = (const CACurveData& src)
	{
		nPoint=src.nPoint;
		nStart=src.nStart;
		sName=src.sName;
		pX=new float[nPoint];  ASSERT(pX);
		pY=new float[nPoint];  ASSERT(pY);
		for(int i=0;i<nPoint;i++)	pX[i]=src.pX[i];
		for(int i=0;i<nPoint;i++)	pY[i]=src.pY[i];
		return * this;
	}
	void Set(int npoint,CString szstr,const float *px,const float *py,int nSta)
	{
		nPoint=npoint;
		nStart=nSta;
		sName=szstr;
		pX=new float[nPoint];  ASSERT(pX);
		pY=new float[nPoint];  ASSERT(pY);
		for(int i=0;i<nPoint;i++)
		{
			pX[i]=px[i];
			pY[i]=py[i];
		}
	}
	float GetMaxX()
	{
		float fmax=-10000.f;
		for(int i=0;i<nPoint;i++) 
			if(fmax<pX[i]) fmax=pX[i];
		return fmax;
	}
	float GetMaxY()
	{
		float fmax=-10000.f;
		for(int i=0;i<nPoint;i++) 
			if(fmax<pY[i]) fmax=pY[i];
		return fmax;
	}
	float GetMinX()
	{
		float fmax=1000000.f;
		for(int i=0;i<nPoint;i++) 
			if(fmax>pX[i]) fmax=pX[i];
		return fmax;
	}
	float GetMinY()
	{
		float fmax=10000000.f;
		for(int i=0;i<nPoint;i++) 
			if(fmax>pY[i]) fmax=pY[i];
		return fmax;
	}
	~CACurveData()
	{
		nPoint=0;
		nStart=0;
		delete[] pX;
		delete[] pY;
	}
	int nPoint;    //����
	int nStart;		// ��ʼ���Ƶ�ţ�Ϊ���������Ͽ̶Ⱥ�ʵ�ʻ��ƴ��ڲ��������
	CString sName;	// ��������
	float *pX;     //X����
	float *pY;     //Y����
};
// CADrawCurve


class CADrawCurve 
{
public:

	BOOL m_bShowLegend;  //�Ƿ���ʾͼ��
	BOOL m_bEnvelopeVisible;  //�Ƿ���ʾ������
	BOOL m_bCurveVisible;  //�Ƿ���ʾ��̬����

	//�����������ݣ�ÿ���������ݶ���������������ϵ
	CArray<CACurveData> m_aCurveData;

	//����һ�����ߣ������������
	int AddCurve(const CString &sName);  

	//����һ�����ߵ�ʱ�䲽���ݣ������������
	int AddCurve(int idCurve,int nPoint,int nStart,const float *px,const float *py);  

	//�����������ʽ
	void SetAxisX(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AAXIS_TYPE type=AAXIS_LINEAR);
	void SetAxisY(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AAXIS_TYPE type=AAXIS_LINEAR);

	//�����������
	int GetCurveCount(void) {return m_aCurveData.GetCount();}

	//��ȡ��������
	float ClientToPhysics_X(int ix);  //��ͼ����ת��Ϊ��������,ixΪ�ؼ����ھֲ�����x
	float ClientToPhysics_Y(int iy);  //��ͼ����ת��Ϊ��������,iyΪ�ؼ����ھֲ�����y


	//��ͼ,fTime--ʱ��
	void Paint();
	// �Ƿ�������
	void SetDrawRect(BOOL bDrawRect);

	//�����ͼ��Ͱ�������
	int CreateGraphData( int i, float &fTime, float *&px,float *&py);

	//���û�ͼ������ؼ����ڱ߽�ľ���
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);
	// ����ͼ��λ��
	void SetLegend(ALEGEND_POS pos,int iMargn,BOOL bLegend=TRUE);
	// ���û�������˵��
	void SetSeries(ALEGEND_POS pos,int iMargn,BOOL bSeries=TRUE);
	//  ���ò��Ԥ����ͼ���Ŀ��
	void SetRight(int iRightWidth,int iRightHeit);

	//�����ż�ֵ��ʾ״̬���ż�ֵ
	void SetThreshold(BOOL bThresholdX, float fThresholdX, BOOL bThresholdY, float fThresholdY);

	COLORREF m_CurveColor[6];  //ǰ�������ߵ���ɫ
	int m_PenStype[6];   //ǰ�������ߵ�����, �ο�CPen��nPenStyleȡֵ
	COLORREF m_EnvelopColor;  //��������ɫ
	LONG m_textSize;		// ���ִ�С��ͳһ��

	void SetTitle(const CString &sTitle) {m_sTitle=sTitle;}  //�������߱���

	void Clear();  //���ȫ������


public:
	CADrawCurve(CDC* pDC);
	virtual ~CADrawCurve();

	CDC* m_pDC;
	CString m_sTitle;  //ͼ�α���
	CDrawSetting m_dSetting;		// һ��ͼ������

	//�����Сֵ���Զ�����
	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxX_Y; //X���ֵ��Ӧ��Y����
	float m_fMinX_Y; //X��Сֵ��Ӧ��Y����

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //��Ч��ͼ������ؼ������ĸ��߽�ľ���
	CRect m_DrawRect;  //��Ч���߻�ͼ���򣬿ͻ���������
	CRect m_ClientRect;	// �ܵĻ�ͼ��С
	int m_widthRight;	// �Ҳ�ͼ�����Ŀ��
	BOOL m_bDrawRect;

	// ͼ��������ϵ�в���
	BOOL m_bLegend;
	BOOL m_bSeries;
	int m_nSHeit;		// ͼ�����и߶�
	CRect m_LegendRect;	// ͼ����С
	CRect m_SeriesRect;	// ����ϵ������

	//������Ŵ�����й�
	float m_fRatioX,m_fRatioY;

	//���������
	float m_fScaleMinX;
	float m_fScaleMinY;
	float m_fScaleMaxX;
	float m_fScaleMaxY;
	float m_fDX,m_fDY;  //�̶ȼ��

	//�ż�ֵ
	float m_fThresholdX,m_fThresholdY;
	BOOL m_bThresholdX,m_bThresholdY;

	enum
	{
		MOVING,
		ENLARGE,
		NOTHINGTODO,
	}m_Tools;


protected:
	CPoint PhysicsToClient(float x,float y);  //��������ת��Ϊ��ͼ����
	void UpdateRatio(); //�����ͼ����
	void DrawAxis(); //��������
	void DrawLegend();		// ����ͼ��(��ĳ�����ߵ����ֵ)
	void DrawLegend_N();	// �°�ģ�ͳһ���Ҳ���
	void DrawSeries();		// �������˵��
	float ScaleAxis(float init_min_value,float init_max_value,int init_point_num, 
		float &axis_min_value,float &axis_max_value, int &axis_point_num,int &iex);		// Ҫʵ��

};


