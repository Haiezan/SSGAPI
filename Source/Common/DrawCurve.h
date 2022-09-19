#pragma once

#include "SysPara.h"
#include "HeadDefine.h"

//坐标轴类型
enum AXIS_TYPE
{
	AXIS_LINEAR,  //线性浮点数
	AXIS_LINEAR_INTEGER,  //线性整数标注
	AXIS_LINEAR_STORY_HEIGHT,   //楼层+高程标注
	AXIS_LOG,     //对数
	AXIS_RECIPROCAL,   //线性轴，倒数标注，分母为整数，分子为1
};

//static int g_Reciprocal[]={500,200,100,50,10};  //可选的倒数分母
static int g_Reciprocal[]={2000,1000,500,200,100,50,10};  //可选的倒数分母

//旋转显示字符串
extern "C" _SSG_DLLIMPEXP void  TextOutRotate(CDC *pDC,int x,int y,const CString &str,LONG lfHeight=Sys_DefaultFontSize,LONG angle=0,LONG lpWeight=FW_NORMAL);

//一个时间步的数据
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

	int nPoint;    //点数
	float fTime; //时刻
	float *pX;     //X数组
	float *pY;     //Y数组
};

//所有时间步数据集合
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

	CString sName; //曲线名称
	CArray<CCurveDataStatic*,CCurveDataStatic*> aDataPtr;   //数据，每一个时刻对应一个数组地址

	//包络线X值，不需要存储Y值
	float *m_pEnvelope1;  //第一象限包络线X值，楼层最大值
	float *m_pEnvelope2;  //第二象限包络线X值，楼层最小值
	BOOL m_bEnvelope1;
	BOOL m_bEnvelope2;
	void ClearEnvelope()  //仅初始化包络线数据，不删除数组
	{
		if(aDataPtr.GetCount()==0) return;
		int nPoint=aDataPtr[0]->nPoint;
		if(m_pEnvelope1)
			for(int i=0;i<nPoint;i++) m_pEnvelope1[i]=0;
		if(m_pEnvelope2)
			for(int i=0;i<nPoint;i++) m_pEnvelope2[i]=0;
	}
	void UpdateEnvelope(int iPoint,float x) //更新包络线数据
	{
		if(m_pEnvelope1)
			m_pEnvelope1[iPoint]=max(m_pEnvelope1[iPoint],x);
		if(m_pEnvelope2)
			m_pEnvelope2[iPoint]=min(m_pEnvelope2[iPoint],x);
	}

	int AddStep(int nPoint,float ftime,const float *px,const float *py)  //增加一个时间步，同时创建包络线数组
	{
		CCurveDataStatic *pstep=new CCurveDataStatic(nPoint,ftime,px,py);
		int istep=aDataPtr.Add(pstep);
		
		//加入第一时刻数据时创建包络线数组,并按第一时刻数据的Y轴坐标
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

	CCurveDataStatic *GetStepPtr(int istep)  //取得某个时间步得数据首地址
	{
		if(istep<0) return NULL;
		if(istep>=aDataPtr.GetCount()) return NULL;
		return aDataPtr[istep];
	}

	int GetStepCount(void) {return aDataPtr.GetCount();}  //得到总步数
};

// CDrawCurve

class  _SSG_DLLIMPEXP CDrawCurve : public CStatic
{
	DECLARE_DYNAMIC(CDrawCurve)

public:

	BOOL m_bShowLegend;  //是否显示图例
	BOOL m_bEnvelopeVisible;  //是否显示包络线
	BOOL m_bCurveVisible;  //是否显示动态曲线

	//多条曲线数据，每条曲线数据独立，但共用坐标系
	CArray<CCurveDataDyna*,CCurveDataDyna*> m_aCurvePtr;

	//增加一条曲线，返回曲线序号
	int AddCurve(const CString &sName,BOOL bEnvelope1,BOOL bEnvelope2);  

	//增加一条曲线的时间步数据，返回时间步序号
	int AddCurveStep(int idCurve,int nPoint,float ftime,const float *px,const float *py);  

	//设置坐标轴格式
	void SetAxisX(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AXIS_TYPE type=AXIS_LINEAR);
	void SetAxisY(const CString &sName=L"",const CString &sUnit=L"",int nScale=5,BOOL bShow=TRUE,AXIS_TYPE type=AXIS_LINEAR);

	//获得曲线条数
	int GetCurveCount(void) {return m_aCurvePtr.GetCount();}

	//获取时间步数
	int GetStepCount(int idCurve);

	//获取最大时间，单位：秒
	float GetMaxTime(int idCurve);

	//获取所有曲线最大时间，单位：秒 邱海 2021年3月1日
	float GetMaxTime();

	//获取某时间步的时刻，超过最大时间步时返回最大时刻，单位：秒
	float GetStepTime(int idCurve,int iStep);

	//获取物理坐标
	float ClientToPhysics_X(int ix);  //绘图坐标转换为物理坐标,ix为控件窗口局部坐标x
	float ClientToPhysics_Y(int iy);  //绘图坐标转换为物理坐标,iy为控件窗口局部坐标y


	//绘图,fTime--时刻
	void Paint(float fTime,BOOL bDrawEnvelop,BOOL bDrawCurve);

	//计算绘图点和包络数据
	int CreateGraphData( int i, float &fTime, float *&px,float *&py);

	//恢复原始尺寸
	void Restore();


	//设置绘图区域与控件窗口边界的距离
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);

	//设置门槛值显示状态及门槛值
	void SetThreshold(BOOL bThresholdX, float fThresholdX, BOOL bThresholdY, float fThresholdY);

	COLORREF m_CurveColor[7];  //前六条曲线的颜色
	int m_PenStype[7];   //前六条曲线的线型, 参考CPen的nPenStyle取值
	COLORREF m_EnvelopColor;  //包络线颜色

	void SetTitle(const CString &sTitle) {m_sTitle=sTitle;}  //设置曲线标题

	void Clear();  //清除全部数据

	void ClearEnvelope(void)   //只清除包络数据，不删除包络数组
	{
		for(int i=0;i<GetCurveCount();i++)
		{
			CCurveDataDyna *pCurve=m_aCurvePtr[i];
			if(!pCurve) continue;
			pCurve->ClearEnvelope();
		}
	}

	//根据已有曲线增加包络曲线（iEnv=0 包络 1 平均）只有最后一步结果的包络不能播放动画 邱海 2017年11月27日
	void AddEnvelopeCurve(int iEnv);
	//改变Y坐标轴的输出范围 邱海 2018年5月11日
	void SetAxisRangeY(float fStart,float fEnd);

	//更新包络线最大值数据
	void UpdateRange();
public:
	CDrawCurve();
	virtual ~CDrawCurve();

protected:

	CString m_sTitle;  //图形标题

	//最大最小值，自动计算
	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxX_Y; //X最大值对应的Y坐标
	float m_fMinX_Y; //X最小值对应的Y坐标

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //有效绘图区域与控件窗口四个边界的距离
	CRect m_DrawRect;  //有效绘图区域，客户窗口坐标

	//以下与放大矩形有关
	float m_fRatioX,m_fRatioY;
	float m_fVisibleMinX,m_fVisibleMaxX;  //用于窗口放大,窗口X轴物理值范围
	float m_fVisibleMinY,m_fVisibleMaxY;  //用于窗口放大,窗口Y轴物理值范围

	BOOL m_bLPressed;  //左键按下
	CRect m_Drag,m_oldDrag;  //拖动矩形

	//坐标轴参数
	CString m_sXName,m_sYName;  //坐标轴名称
	float m_fScaleMinX;
	float m_fScaleMinY;
	float m_fScaleMaxX;
	float m_fScaleMaxY;
	float m_fDX,m_fDY;  //刻度间隔
	AXIS_TYPE m_XAxisType;  //X轴类型
	AXIS_TYPE m_YAxisType;  //X轴类型
	BOOL m_bShowX,m_bShowY;  //是否显示坐标轴和刻度

	//门槛值
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

	CRect m_rtLegend;  //图例矩形

protected:
	CPoint PhysicsToClient(float x,float y);  //物理坐标转换为绘图坐标
	void UpdateRatio(); //计算绘图比例
	void DrawAxis(CDC &dc); //绘坐标轴
	void DrawLegend(CDC &dc); //绘制图例

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

	//下面数据由外部传进来
	int m_nStage;   //时间点数
	float *m_pTime; //时间数组，一维，长度为m_nStage  层间位移
	int m_nCurve;  //分量数
	float * m_pData;  //按曲线顺序存储，多维，大小为m_nCurve*m_nStage	层间剪力
	float * m_pTime0;  //时间数组，一维，长度为m_nStage
	CString * m_psName;  //分量名称数组，一维，长度为m_nCurve
	CString m_sID;  //图元标识
	CString sXName;
	CString sYName;
	CRect m_rtLegend;  //图例矩形
	BOOL m_pbShow[64]; //是否显示每个分量


public:
	//pTime--时间点，pData-按曲线顺序依次存储数据，多维，大小为nCurve*nStage，psName--分量名称数组
	void SetData(int iType,int nStage, float *pTime0,int nCurve, float * m_pTime,float * pData, CString * psName);
	CPoint GetClientCoor(float x,float y);  //物理坐标转换为绘图坐标
	void GetRatio(); //计算绘图比例m_fRatioX和m_fRatioY,屏幕长度=ratio*物理长度
	void DrawAxis(CDC &dc); //绘坐标轴
	void Restore(void);
	//设置绘图区域与控件窗口边界的距离
	void SetMargins(int iLeftMargin,int iTopMargin,int iRightMargin,int iBottomMargin);

	void Viewdata();

private:

	//以下与放大矩形无关
	float m_fMax,m_fMin;  //分量值范围.

	//以下与放大矩形有关
	float m_fRatioX,m_fRatioY; //屏幕长度=ratio*物理长度
	float m_fX0,m_fX1;  //用于窗口放大

	int m_iLeftMargin,m_iTopMargin,m_iRightMargin,m_iBottomMargin;  //有效绘图区域与控件窗口四个边界的距离
	CRect m_DrawRect;  //有效绘图区域

	COLORREF m_CurveColor[7];

	DECLARE_MESSAGE_MAP()
public:
	void Paint(float fTime);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Clear(void);

};