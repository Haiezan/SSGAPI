#pragma once

//坐标轴类型
enum AAXIS_TYPE
{
	AAXIS_LINEAR,  //线性浮点数
	AAXIS_LINEAR_INTEGER,  //线性整数标注
	AAXIS_LINEAR_STORY_HEIGHT,   //楼层+高程标注
	AAXIS_LOG,     //对数
	AAXIS_RECIPROCAL,   //线性轴，倒数标注，分母为整数，分子为1
};

enum ALEGEND_POS
{
	ALPOS_TOPRIGHT,
	ALPOS_TOPLEFT,
	ALPOS_BTNRIGHT,
	ALPOS_BTNLEFT
};

static int g_ReciprocalA[]={500,200,100,50,10};  //可选的倒数分母

//旋转显示字符串
void TextOutRotateA(CDC *pDC,int x,int y,const CString &str,LONG lfHeight=14,LONG angle=0,LONG lpWeight=FW_NORMAL);

// 一副图的设置参数,便于函数间的调用
struct CDrawSetting
{
	CString sTitle;
	CRect rc;
	int nRightWidth,nSingleHeit;		// 右边预留宽度、单行高度
	int nLeft,nTop,nRight,nBottom;		// imargain
	CString sXAxisName,sYAxisName;
	int nXAxisMesh,nYAxisMesh;
	BOOL bXAxis,bYAxis;		//是否显示坐标轴和刻度
	AAXIS_TYPE tXAxis,tYAxis;
	BOOL bDrawRect;
	BOOL bLegend;
	BOOL bSeries;
	BOOL bSeriesMaxOrMin;	// max=true
	BOOL bMainAxis;			// x-true y-false主轴，用于确定图例的最大值和输出格式
	ALEGEND_POS posLegend;
	ALEGEND_POS posSeries;
	CDrawSetting() {nRightWidth=0;tXAxis=tYAxis=AAXIS_LINEAR;bXAxis=bYAxis=TRUE;bDrawRect=TRUE;bLegend=bSeries=FALSE;bSeriesMaxOrMin=TRUE;
	nLeft=nTop=nRight=nBottom=0;bMainAxis=TRUE;posLegend=ALPOS_TOPRIGHT;posSeries=ALPOS_BTNRIGHT;}
};

//一个条线的数据
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
	int nPoint;    //点数
	int nStart;		// 起始绘制点号（为了满足轴上刻度和实际绘制存在差别的情况）
	CString sName;	// 曲线名称
	float *pX;     //X数组
	float *pY;     //Y数组
};
// CADrawCurve


class CADrawCurve 
{
public:

	BOOL m_bShowLegend;  //是否显示图例
	BOOL m_bEnvelopeVisible;  //是否显示包络线
	BOOL m_bCurveVisible;  //是否显示动态曲线

	//多条曲线数据，每条曲线数据独立，但共用坐标系
	CArray<CACurveData> m_aCurveData;

	//增加一条曲线，返回曲线序号
	int AddCurve(const CString &sName);  

	//增加一条曲线的时间步数据，返回曲线序号
	int AddCurve(int idCurve,int nPoint,int nStart,const float *px,const float *py);  

	//设置坐标轴格式
	void SetAxisX(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AAXIS_TYPE type=AAXIS_LINEAR);
	void SetAxisY(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AAXIS_TYPE type=AAXIS_LINEAR);

	//获得曲线条数
	int GetCurveCount(void) {return m_aCurveData.GetCount();}

	//获取物理坐标
	float ClientToPhysics_X(int ix);  //绘图坐标转换为物理坐标,ix为控件窗口局部坐标x
	float ClientToPhysics_Y(int iy);  //绘图坐标转换为物理坐标,iy为控件窗口局部坐标y


	//绘图,fTime--时刻
	void Paint();
	// 是否绘制外框
	void SetDrawRect(BOOL bDrawRect);

	//计算绘图点和包络数据
	int CreateGraphData( int i, float &fTime, float *&px,float *&py);

	//设置绘图区域与控件窗口边界的距离
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);
	// 设置图例位置
	void SetLegend(ALEGEND_POS pos,int iMargn,BOOL bLegend=TRUE);
	// 设置绘制线条说明
	void SetSeries(ALEGEND_POS pos,int iMargn,BOOL bSeries=TRUE);
	//  设置侧边预留给图例的宽度
	void SetRight(int iRightWidth,int iRightHeit);

	//设置门槛值显示状态及门槛值
	void SetThreshold(BOOL bThresholdX, float fThresholdX, BOOL bThresholdY, float fThresholdY);

	COLORREF m_CurveColor[6];  //前六条曲线的颜色
	int m_PenStype[6];   //前六条曲线的线型, 参考CPen的nPenStyle取值
	COLORREF m_EnvelopColor;  //包络线颜色
	LONG m_textSize;		// 文字大小，统一的

	void SetTitle(const CString &sTitle) {m_sTitle=sTitle;}  //设置曲线标题

	void Clear();  //清除全部数据


public:
	CADrawCurve(CDC* pDC);
	virtual ~CADrawCurve();

	CDC* m_pDC;
	CString m_sTitle;  //图形标题
	CDrawSetting m_dSetting;		// 一幅图的设置

	//最大最小值，自动计算
	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxX_Y; //X最大值对应的Y坐标
	float m_fMinX_Y; //X最小值对应的Y坐标

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //有效绘图区域与控件窗口四个边界的距离
	CRect m_DrawRect;  //有效曲线绘图区域，客户窗口坐标
	CRect m_ClientRect;	// 总的绘图大小
	int m_widthRight;	// 右侧图例栏的宽度
	BOOL m_bDrawRect;

	// 图例和线条系列参数
	BOOL m_bLegend;
	BOOL m_bSeries;
	int m_nSHeit;		// 图例单行高度
	CRect m_LegendRect;	// 图例大小
	CRect m_SeriesRect;	// 曲线系列描述

	//以下与放大矩形有关
	float m_fRatioX,m_fRatioY;

	//坐标轴参数
	float m_fScaleMinX;
	float m_fScaleMinY;
	float m_fScaleMaxX;
	float m_fScaleMaxY;
	float m_fDX,m_fDY;  //刻度间隔

	//门槛值
	float m_fThresholdX,m_fThresholdY;
	BOOL m_bThresholdX,m_bThresholdY;

	enum
	{
		MOVING,
		ENLARGE,
		NOTHINGTODO,
	}m_Tools;


protected:
	CPoint PhysicsToClient(float x,float y);  //物理坐标转换为绘图坐标
	void UpdateRatio(); //计算绘图比例
	void DrawAxis(); //绘坐标轴
	void DrawLegend();		// 绘制图例(即某条曲线的最大值)
	void DrawLegend_N();	// 新版的，统一到右侧上
	void DrawSeries();		// 描绘曲线说明
	float ScaleAxis(float init_min_value,float init_max_value,int init_point_num, 
		float &axis_min_value,float &axis_max_value, int &axis_point_num,int &iex);		// 要实现

};


