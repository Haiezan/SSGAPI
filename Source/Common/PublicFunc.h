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

	//��������
	static void SwapData(int &d1,int &d2);
	static void SwapData(float &d1,float &d2);
	static void SwapData(Vector4 &v1,Vector4 &v2);

	//ȡ����ֵ�ϴ��������������ff=1.5����2��ff=-1.5����-2
	static int BigInt(float ff);
	
	
	//�������,depth����С��������,index�������飨�µ��ɣ�,nData�����С
	static BOOL StackSort(int nData,float  *depth,int *index); 
	static BOOL StackSort(int nData,int  *depth,int *index); 
	static BOOL StackSort(int nData,unsigned __int64 *depth,UINT *index); 
	static BOOL StackSort(int nData,float  *depth,Vector4 *index); 
	//�Ѿ��ź�˳������飬ȥ���ظ���Ԫ�أ�index�������飨�µ��ɣ���nData�����С
	static BOOL Clean(int &nData,int *index);
	static BOOL Clean(int &nData,Vector4 *index);

	//ͼ���ʽ�����������ص�pClsID
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	//��������ͬ�ĵ���кϲ�,���ؾɵ��ŵ��µ��ŵ�����index�� ͬʱԭ����������鱻����
	//��������Ϊ���������Ķ�̬�ڴ棬���ó��������Ӧ�ͷ�
	//ʧ���򷵻ؿ�ָ��
	static int *Merge(Vector4 *pVex,int nOldNPoint,int &nNewPoint);
	static int *MergeFast(Vector4 *pVex,int nOldNPoint,int &nNewPoint);

	//�����������������������������
	static float TriangleArea(float x1,float y1,float x2,float y2,float x3,float y3);
	static int TriangleArea(int x1,int y1,int x2,int y2,int x3,int y3);

	//���ı������������������������
	static float QuadArea(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4);
	static int QuadArea(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);

	//��ӡǧλ��,����buf��ַ��buf�����ȴ���
	static char *FormatK(char *buf,unsigned int len, __int64 d);
	static int GetLegendGrade(float v,int nGrade,float* fGrade);
	static int GetLegendGradeCollapseDc(float v, int nGrade, float *fGrade);
	static float GetLegendGradeGDNL(float v, int nGrade, int nGroup, float *fGrade1, float ntime = 1.0f, float *fGrade2 = NULL,  float limit_result0 = 0.0f,float *fGrade3 = NULL, float *fGrade4 = NULL, float limit_result1 = 0.0f);

	//������ֵ�����׼��ɫ��fmin��Ӧ(0,0,255)����ֵ��Ӧ(0,255,0)��fmax��Ӧ(255,0,0)��֮�����Բ�ֵ
	static COLORREF GetColor(float v,float fMin,float fMax,BOOL bRedOnly);
	//static COLORREF GetRGBColor(float v,float fMin,float fMax);
	static COLORREF GetLegendColor(float v,float fMin,float fMax);
	//������ɫ����Ϊ��׼��ɫ
	//��׼��ɫ���������������Ϊ�Ǳ�׼��ɫ


	//����ֲ�����ϵ��ʸ��u,v,w
	//p1->p2����u��p1-p2-p3���淨�߹���w
	//���룺p1,p2,p3
	//�����u,v,w
	//���أ�TRUE--�ɹ���FALSE--���㹲�ߣ��޷���������ϵ
	static BOOL LocalCoorVectorByTri(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,Vector4 &u,Vector4 &v,Vector4 &w);

	//���ܣ��жϵ��Ƿ��ڶ�����ڣ�֧�ֶ�ά���(������ֻ�õ�x,y����)���������
	//���������ͨ���õ��ˮƽ�������θ��ߵĽ���
	//���ۣ����ڶ�����ڣ�����1
	//		���ڶ�����⣬����0
	//		�������ڶ���α߽���Ϸ���-���
	//		�������ڶ���εı߽����Ϸ���-100
	//������ 
	//p-- ָ����ĳ���� 
	//ptPolygon--����εĸ����������꣨��ĩ�㲻һ�£� 
	//nCount--����ζ���ĸ��� 
	static int PtInPolygon2D(const Vector4 &p, const Vector4 *ptPolygon,int nCount);

	//�ж��ĸ����Ƿ���ͬһƽ����
	//p1��p2��p3����һ��ƽ�棬�ж�p4�Ƿ������ƽ���ڣ����ж�ʸ��p1->p3�Ƿ�ֱ��ƽ�淨��ʸ��w
	//����p1,p2,p3,p4
	//����TRUE:�ĵ㹲�棬FALSE:�ĵ㲻����
	static BOOL InaPlate(const Vector4 &p1,const Vector4 &p2,const Vector4 &p3,const Vector4 &p4);

	//���ݱ߽�������ó�ֱ����Ϣ
	static void GetLongStraightEdge(int nBndPoint,const Vector4 *pBndPoint,int &nStraightEdge,int *pStraightPos);

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ�ڵ��ú����þ�ָ��ΪNULL
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

	//��ȡ�����Сֵ,һ��Ҫ��-9999.0f����
	static double GetMax(double first,...);
	static double GetMin(double first,...);

	//�ж��Ƿ�͹�����,vNormalΪƽ�淨��λʸ����֧����ά����
	static BOOL IsConvex3D(int nVex,const Vector4 *pVex,const Vector4 &vNormal);

	//�ж��Ƿ�͹�����,vNormalΪƽ�淨��λʸ����֧�ֶ�ά���꣬���е�z���������ͬ
	static BOOL IsConvex2D(int nVex,const Vector4 *pVex);


	struct compx {float real,imag;}; //����һ�������ṹ

	//�����p��q1-q2ֱ�ߵĴ���
	static Vector4 Perpendicular(const Vector4 &p,const Vector4 &q1,const Vector4 &q2);

	//������Pkpm.h
	//��񻯽�����������ڱ�Ե�����������ݽ�
	static float NormalRebarArea(float fAs);

	//Ѱ�Ҳ�ֵ����
	static void LookInterval(const float *pValue,int nSteps,float val, int &iIntervalStart,int &iIntervalEnd,float &left_coef);

	//���Ĳ�֣�order:����,ֻ�ܵ���1��2
	static float Difference(int order,float dx,float y0,float y1,float y2);

	//�����ַ������ֽ���
	static int GetStringBytes(const CString &s);
	//��Ҫ��ĳ��ȷ����ַ���������ĺ��油��ո񣬳��Ȱ��ֽڼ���
	static CString GetStringByLen(const CString &s,int len);

	static CString GetExePath(void); //�õ������Ŀ¼������"c:\program files\sausage\"

	static BOOL GetRayliDamp(float T1,float T2,float Ksi1,float Ksi2,float &alpha,float &beta);

	//���Բ�ֵ
	static float LinearInter(float x, float x1, float x2, float y1, float y2);
	static float LinearInter(float x, float* x1, float* y1, int N);

	//static char* _CHS(const char* chs, const char* eng="");
//	static wchar_t* _CHS(const wchar_t* chs, const wchar_t* eng=L"");

	//�ж϶�����Ƿ�Ϊ������Σ����ڽ��Ǵ���180��Լ3����ݲ�sin3=0.05��
	//-1 ��ʾΪ͹����� 0~n Ϊ��󰼽Ǳ��
	static int IsConcave(Vector4* p, int n);
};

void LastErrorMessage_Debug(LPTSTR lpszFunction);  //��ȡ����ʾ���Ĵ���

//extern "C" _SSG_DLLIMPEXP  char* _CHS(const char* chs, const char* eng="");
//extern "C" _SSG_DLLIMPEXP  wchar_t* _CHSL(const wchar_t* chs, const wchar_t* eng=L"");