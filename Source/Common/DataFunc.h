#pragma once

#include "HeadDefine.h"
#include "Vector4.h"
#include "DataPrimitive.h"

//获取构件的缺省颜色
extern "C" _SSG_DLLIMPEXP COLORREF GetStructDefaultColor(STRUCT_TYPE type,int iSubType);

//从内存ID(IDM)换成拾取ID(IDG),宏定义中必须加括号，否则结果不可预知
//#define GETIDG(IDM,ArrayType) ((IDM)+(ArrayType))  
extern "C" _SSG_DLLIMPEXP int GetIDG(int idm,STRUCT_TYPE iType); 

//从拾取ID(IDG)换成内存ID(IDM)
extern "C" _SSG_DLLIMPEXP int GetIDM(int IDG);
//从内存ID(IDM)换成拾取ID(IDG)
extern "C" _SSG_DLLIMPEXP STRUCT_TYPE GetPickedType(int IDG);
//拾取顺序判断
extern "C" _SSG_DLLIMPEXP int GetPickedOrder(int IDG);
//从IDG换成类型起始特征值
extern "C" _SSG_DLLIMPEXP int GetBaseType(int IDG);

extern "C" _SSG_DLLIMPEXP BOOL ValidHit(int iHit);   //判断拾取索引iHit是否有效

//对坐标相同的点进行合并,返回旧点编号到新点编号的索引index， 同时原结点坐标数组被更新，索引数组为函数创建的动态内存，调用程序用完后应释放
//失败则返回空指针
extern "C" _SSG_DLLIMPEXP int *Merge(CVertex *pVex,int nOldNPoint,int &nNewPoint);

//多个结点配对合并
//pVex2与pVex1进行匹配，若找到则返回pVex1对应的pID1编码，否则返回StartID开始的编码
//pID1、pVex2和pVex1数组下标均从0开始
//pID1为pVex1对应的结点编码
extern "C" _SSG_DLLIMPEXP int *MergeWithArray(const int *pID1, int nVex1, const Vector4 *pVex1, int nVex2, const Vector4 *pVex2, int StartID);

//返回多边形顶点编码数组,首尾点不重合,不成功则返回NULL
//假设给定的结点坐标不重合，即没有坐标相同但编码不同的点,调用程序应释放返回的指针内存
//输入: pPolygonLine--按顺序围成多边形的线段数组,线段必须按顺序给出，线段编号方向可以任意
extern "C" _SSG_DLLIMPEXP int *GetPolygonVexID(int nLine, const CLine *pPolygonLine);

//按阶段排序,vex--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortNodeByStage(int nData, CVertex  *vex); 

//按阶段排序,beam--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortBeamElmByStage(int nData, CBeamElm  *beam); 

//按阶段排序,tri--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortTriElmByStage(int nData,CTriangleElm  *tri); 
extern "C" _SSG_DLLIMPEXP int *StackSortQuadElmByStage(int nData,CQuadElm  *quad); 


//计算XY面内的旋转角，单位：度，center--旋转中心，p1,p2--旋转的起点和终点，两个点可以不在同一圆弧上，只代表从center发出的射线上的点
//所有坐标只用x,y分量
extern "C" _SSG_DLLIMPEXP double RotateAngleDouble(const CVertex &center,const CVertex &p1,const CVertex &p2);


extern "C" _SSG_DLLIMPEXP STRUCT_KEYWORD g_StructKeyword[Sys_StructTypeNum];
extern "C" _SSG_DLLIMPEXP STRUCT_PROPERTY1 g_PropTable1[17];


extern "C" _SSG_DLLIMPEXP void GetBeamInitialImperfection(CBeamStruc &beam,bool bRewrite=false);


extern "C" _SSG_DLLIMPEXP void LinearSmooth3 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void LinearSmooth5 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void LinearSmooth7 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void QuadraticSmooth5(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void QuadraticSmooth7(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void CubicSmooth5 ( float in[], float out[], int N );
extern "C" _SSG_DLLIMPEXP void CubicSmooth7(float in[], float out[], int N);
extern "C" _SSG_DLLIMPEXP void GaussianSmooth(float in[], float out[], int N);

extern "C" _SSG_DLLIMPEXP void OnFrame2elm(CFrame& frame, CMesh& mesh);  //读入网格、生成网格后要调用
