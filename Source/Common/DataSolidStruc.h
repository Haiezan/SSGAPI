#pragma once
#include <afxtempl.h>
#include <vector>
#include <map>

#include "HeadDefine.h"
#include "Vector4.h"
//#include "Vector4_Reference.h"
//#include "DataPrimitive.h"
#include "DataStrucProp.h"

class CASCFile;
using namespace std;

//class _SSG_DLLIMPEXP CFace
//{
//public:
//	CFace(void);
//
//	CFace(const CFace &plate)
//	{
//		pLineIDM=NULL;
//		*this=plate;
//	}
//
//	~CFace(void){
//		if(pLineIDM)
//		{
//			delete[] pLineIDM; 
//			pLineIDM=NULL;
//		}
//	}
//
//	//int id; //本构件的id，从1开始编号，各类面构件独立编号
//	//边界线段数
//	int nLine; 
//	//边界线段数组
//	int *pLineIDM;
//	int iSectionID;  //截面ID
//
//	//重载赋值运算符
//	CFace & operator=(const CFace &plate);
//
//	void Clear();
//
//	//设置边数，并调整数组大小原数据被清除
//	void SetLineNum(int nline) 
//	{
//		//nLine=nline;
//		//if(pLineIDM) delete[] pLineIDM; 
//		//pLineIDM=new int[nLine];
//		//ASSERT(pLineIDM);
//	}
//
//	//返回顶点个数，及按顺序排列的顶点编码PointID，首尾点不重合，外部程序维护内存PointID，pLine为系统线段编码数组，
//	//假设给定的结点坐标不重合，即没有坐标相同但编码不同的点
//	int GetVexID(int *PointID,const CLine *pLine) const; 
//
//	//返回点到线ID的关联表
//	BOOL GetPt2Line(PT2LINE *pPt2Line,const CLine *pLine);
//
//	//按几何关系计算局部坐标矢量：w为法线，顶点编号符合右手定则
//	BOOL PlateLocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray);
//
//	//重新排列线段ID，从第j个线段开始，way>0，正方向排列，way<0，反方向排列
//	void RenewLineID(int j,int way);
//
//	//混凝土分层,nLayer--分层数，fThick--每层厚度，均匀分层，pos--每层位置数组，iMaxLayers--pos的最大个数
//	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);
//
//	//配筋,返回分层数，pThick--每层厚度，iMaxLayers--最大层数
//	int GetRebarLayer(double *pThick,int iMaxLayers);
//	int GetRebarLayer(float *pThick,int iMaxLayers);
//	// 邱海 2020年10月28日
//	int GetRebarLayer(float *pThick);
//
//	//得到坐标范围
//	void GetRange(Vector4 &rMin,Vector4 &rMax);
//
//	//计算墙的高度和宽度，内包矩形
//	void GetWallSize(float &fWidth,float &fHeight);
//
//	//计算墙的规定间距范围内配筋面积
//	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);
//
//	//计算板或墙钢筋重量，单位：kN
//	float GetRebarWeight();
//
//	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf,CPlateSectionCollection &cPlateSection,CProjectPara &cPrjPara);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
//	virtual BOOL Write(CASCFile &fout,int idf);
//
//	//设计信息读写
//	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
//	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
//
//	//根据截面信息刷新构件信息
//	void RenewPlate();
//
//	void GenLoadId(bool bRewrite=true);//由	float fDeadLoad 和float fLiveLoad生成Load加入mapload 供2020之后版本读取
//	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取
//
//	//按边界顺序返回四个角点ID，左下、右下、右上、左上
//	BOOL GetCornerPoint(int &left_bottom,int &right_bottom,int &right_top,int &left_top)const;
//};

//typedef shared_ptr<Vector4 *> PVector4;

class _SSG_DLLIMPEXP CSolidFace
{
public:
	std::vector<int> vVertexIDM;

	//不保存
	//对应的edge 编号
	std::vector<int> vEdgeIDM;
	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动点和线时需要调用PlateLocalCoorVector重新计算
//	Vector4 u,v,w,c0;  //工程局部坐标系基矢量及坐标原点，w为法线方向,
	Vector4 v;		//法线方向
};

//typedef std::vector<std::vector<int>> vec
//template <typename T> std::vector<std::vector<T>> vecvec;

//实体类
//暂时 还是按 板壳的属性定义
//这里面是存在问题的，后续版本需要将钢筋、钢材等单独提出来。具有共性
//第1步 是均质材料，带有节点荷载

class _SSG_DLLIMPEXP CSolidStruc : public CPrimitiveProp //public CStrucProp
{
public:
	CSolidStruc(void);
	//{
	//	nVertex=0; 
	//	pVertex=NULL;
	//	color=0;
	//}

	~CSolidStruc()
	{
		delete[] pVertex;
	}

	CSolidStruc(const CSolidStruc &surf)
	{
		pVertex=NULL;
		*this=surf;
	}

	CSolidStruc(STRUCT_TYPE istructype, int istory, DWORD color);

	void Clear();

	//赋值运算符重载
	//CSolidStruc & operator=(const CSolidStruc& surf)
	//{
	//	if(this==&surf) return *this;

	//	delete[] pVertex;
	//	nVertex=surf.nVertex;
	//	pVertex=new Vector4[nVertex];
	//	for(int i=0;i<nVertex;i++)
	//	{
	//		pVertex[i]=surf.pVertex[i];
	//	}
	//	return *this;
	//}

//数据
	std::vector<CSolidFace> vFaceSet;		//Face 编号
	int iStrucType;							//类型, future

//临时 根据face生成
//需要生成发现向量，暂时以逆时针为面的正向
	int nVertex;							//顶点数
	Vector4 *pVertex;						//顶点坐标数组，相对于构件的局部坐标
	//std::vector<Vector4 *> vVertex;

	int nLine; 
	int *pLineIDM;						//Edge 
	
	//备注, 暂时 只支持 uniaxial 各项同性材料， 弹性的。
	//材料不用 字符串表示，而是用 通用的编号表示
	int iMat;							//材料编号

	std::vector<int> vLoadID;			//荷载id
	std::vector<int> vSolidTag;			//其他

	//int solidtag[5];					//备用
	//根据FACE生成
//	std::vector<int> vVertexIDM;		//顶点编号
//	std::vector<int> vEdge;				//Edge (Line) 编号
	//要有方法遍历每个面形成边

	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动点和线时需要调用PlateLocalCoorVector重新计算
	Vector4 u,v,w,c0;  //工程局部坐标系基矢量及坐标原点，w为法线方向,

	//Vertex List
	//Face List

	//Edge 是生成量
	//vertex
	//0 0 0
	//0 0 1
	//0 1 1
	//0 1 0
	//4 0 1 2 3  {start of face list}
	//4 7 6 5 4
	//4 1 5 6 2

	DWORD color;		//实际绘制颜色

	virtual bool Read(CASCFile &fin, STRUCT_TYPE iType, int &idf);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
	virtual bool Write(CASCFile &fout, int idf);

	bool ReadPly(std::string filename);		//读入 Ply
	bool WritePly(std::string filename);	//写入 Ply
};
