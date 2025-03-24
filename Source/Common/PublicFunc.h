#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include <vector>

using namespace std;

#ifndef max3
#define max3(a,b,c) (max(max(a,b),c))
#endif

#ifndef min3
#define min3(a,b,c) (min(min(a,b),c))
#endif

#ifndef max4
#define max4(a,b,c,d) (max(max(max(a,b),c),d))
#endif

#ifndef min4
#define min4(a,b,c) (min(min(min(a,b),c),d))
#endif

#define sqr(x) (x)*(x)
#define sgn(x) (x>0?1:0)



class _SSG_DLLIMPEXP  CPublicFunc 
{
public:
	CPublicFunc();
	~CPublicFunc();
public:

	//交换数据
	static void SwapData(int &d1,int &d2);
	static void SwapData(float &d1,float &d2);
	static void SwapData(Vector4 &v1,Vector4 &v2);

	//取绝对值较大的整型数，例如ff=1.5返回2，ff=-1.5返回-2
	static int BigInt(float ff);
	
	
	//排序程序,depth被从小到大排列,index索引数组（新到旧）,nData数组大小
	static BOOL StackSort(int nData,float  *depth,int *index); 
	static BOOL StackSort(int nData,int  *depth,int *index); 
	static BOOL StackSort(int nData,unsigned __int64 *depth,UINT *index); 
	static BOOL StackSort(int nData,float  *depth,Vector4 *index); 
	//已经排好顺序的数组，去掉重复的元素，index索引数组（新到旧），nData数组大小
	static BOOL Clean(int &nData,int *index);
	static BOOL Clean(int &nData,Vector4 *index);

	//图像格式编码器，返回到pClsID
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	//对坐标相同的点进行合并,返回旧点编号到新点编号的索引index， 同时原结点坐标数组被更新
	//索引数组为函数创建的动态内存，调用程序用完后应释放
	//失败则返回空指针
	static int *Merge(Vector4 *pVex,int nOldNPoint,int &nNewPoint);
	static int *MergeFast(Vector4 *pVex,int nOldNPoint,int &nNewPoint);

	//求三角形有向面积，给定顶点坐标
	static float TriangleArea(float x1,float y1,float x2,float y2,float x3,float y3);
	static int TriangleArea(int x1,int y1,int x2,int y2,int x3,int y3);

	//求四边形有向面积，给定顶点坐标
	static float QuadArea(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4);
	static int QuadArea(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);

	//打印千位符,返回buf地址，buf须事先创建
	static char *FormatK(char *buf,unsigned int len, __int64 d);
	static int GetLegendGrade(float v,int nGrade,float* fGrade);
	static int GetLegendGradeCollapseDc(float v, int nGrade, float *fGrade);
	static float GetLegendGradeGDNL(float v, int nGrade, int nGroup, float *fGrade1, float ntime = 1.0f, float *fGrade2 = NULL,  float limit_result0 = 0.0f,float *fGrade3 = NULL, float *fGrade4 = NULL, float limit_result1 = 0.0f);

	//由物理值计算标准颜色：fmin对应(0,0,255)，中值对应(0,255,0)，fmax对应(255,0,0)，之间线性插值
	static COLORREF GetColor(float v,float fMin,float fMax,BOOL bRedOnly);
	//static COLORREF GetRGBColor(float v,float fMin,float fMax);
	static COLORREF GetLegendColor(float v,float fMin,float fMax);
	//任意颜色换算为标准颜色
	//标准颜色进行四则运算后会变为非标准颜色


	//构造局部坐标系基矢量u,v,w
	//p1->p2构成u，p1-p2-p3的面法线构成w
	//输入：p1,p2,p3
	//输出：u,v,w
	//返回：TRUE--成功，FALSE--三点共线，无法构造坐标系
	static BOOL LocalCoorVectorByTri(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,Vector4 &u,Vector4 &v,Vector4 &w);

	//功能：判断点是否在多边形内，支持二维情况(参数中只用到x,y坐标)、凹多边形
	//方法：求解通过该点的水平线与多边形各边的交点
	//结论：点在多边形内，返回1
	//		点在多边形外，返回0
	//		给定点在多边形边界点上返回-点号
	//		给定点在多边形的边界线上返回-100
	//参数： 
	//p-- 指定的某个点 
	//ptPolygon--多边形的各个顶点坐标（首末点不一致） 
	//nCount--多边形顶点的个数 
	static int PtInPolygon2D(const Vector4 &p, const Vector4 *ptPolygon,int nCount);

	//判断四个点是否在同一平面内
	//p1、p2、p3构成一个平面，判断p4是否在这个平面内，即判断矢量p1->p3是否垂直于平面法线矢量w
	//输入p1,p2,p3,p4
	//返回TRUE:四点共面，FALSE:四点不共面
	static BOOL InaPlate(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,const Vector4 &p4);

	//根据边界点数组获得长直边信息
	static void GetLongStraightEdge(int nBndPoint,const Vector4 *pBndPoint,int &nStraightEdge,int *pStraightPos);

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应在调用后设置旧指针为NULL
	static int *Renew(int *&oldp,int oldCount,int newCount);
	static DWORD *Renew(DWORD *&oldp,int oldCount,int newCount);

	static inline BOOL IsValidFloat(float f)
	{
		return (~((DWORD)f>>23))&0xff;
	}

	//GUID SetPowerScheme(GUID myDefaultPowerScheme);
	static void ShutDown();

	static float ScaleAxis(float init_min_value,float init_max_value,int init_point_num, 
		float &axis_min_value,float &axis_max_value, int &axis_point_num,int &iex);

	//获取最大最小值,一定要以-9999.0f结束
	static double GetMax(double first,...);
	static double GetMin(double first,...);

	//判断是否凸多边形,vNormal为平面法向单位矢量，支持三维坐标
	static BOOL IsConvex3D(int nVex,const Vector4 *pVex,const Vector4 &vNormal);

	//判断是否凸多边形,vNormal为平面法向单位矢量，支持二维坐标，所有点z坐标必须相同
	static BOOL IsConvex2D(int nVex,const Vector4 *pVex);


	struct compx {float real,imag;}; //定义一个复数结构

	//计算点p到q1-q2直线的垂足
	static Vector4 Perpendicular(const Vector4 &p,const Vector4 &q1,const Vector4 &q2);

	//定义在Pkpm.h
	//规格化截面积，适用于边缘构件和连梁纵筋
	static float NormalRebarArea(float fAs);

	//寻找插值区间
	static void LookInterval(const float *pValue,int nSteps,float val, int &iIntervalStart,int &iIntervalEnd,float &left_coef);

	//中心差分，order:阶数,只能等于1或2
	static float Difference(int order,float dx,float y0,float y1,float y2);

	//返回字符串的字节数
	static int GetStringBytes(const CString &s);
	//按要求的长度返回字符串，不足的后面补充空格，长度按字节计算
	static CString GetStringByLen(const CString &s,int len);

	static CString GetExePath(void); //得到程序根目录，例："c:\program files\sausage\"

	static BOOL GetRayliDamp(float T1,float T2,float Ksi1,float Ksi2,float &alpha,float &beta);

	//线性插值
	static float LinearInter(float x, float x1, float x2, float y1, float y2);
	static float LinearInter(float x, float* x1, float* y1, int N);

	//static char* _CHS(const char* chs, const char* eng="");
//	static wchar_t* _CHS(const wchar_t* chs, const wchar_t* eng=L"");

	//判断多边形是否为凹多边形，即内角是大于180（约3°的容差sin3=0.05）
	//-1 表示为凸多边形 0~n 为最大凹角编号
	static int IsConcave(Vector4* p, int n);
};

void LastErrorMessage_Debug(LPTSTR lpszFunction);  //获取并显示最后的错误

//extern "C" _SSG_DLLIMPEXP  char* _CHS(const char* chs, const char* eng="");
//extern "C" _SSG_DLLIMPEXP  wchar_t* _CHSL(const wchar_t* chs, const wchar_t* eng=L"");