#pragma once
#include <vector>

struct XYPOINT
{
	XYPOINT() { id = -1;}
	//	XYPOINT(double x0, double y0) : x(x0), y(y0), id(-1) {}
	int id;
	float x;
	float y;
};

struct XYLINE
{
	XYLINE() { id = -1; }
	int id;
	int id1;
	int id2;
};

struct XYPOLY
{
	XYPOLY() { 
		id = -1; 
		attribute = 0; 
		area = 0; 
		xcenter = 0; 
		ycenter = 0;
		//		marked = false;
	} // xoff = 0; yoff = 0; }
	int id;
	std::vector<int> m_vecPointID;
	int attribute;	//属性  0 正常  1--洞口   2--洞中洞

	//	int idholept;
	XYPOINT holepoint;	//用于定义holepoint, 可以通过计算各个点的平均值近似计算， 已代替 找内部点,
	//后续 两条边 夹角小于180度时 可以找到中心点也可以。

	float area;		//面积
	float xcenter;	//中心点坐标
	float ycenter;
	//float calc_area() 
	//{
	//}
	//	bool marked;
};


//struct XYHOLE //开洞
//{
//	XYHOLE(){marked=false;}
//
//	std::vector<XYPOINT> vPoint;
//	std::vector<XYLINE> vLine;	//开洞线
//	int idHolePoint;			//开洞点
//
////	std::vector<int> vPointId;			//中间数据、polygon 点号
//	bool marked;
//};


//struct XYHOLE //开洞
//{
//	XYHOLE() : marked(false) {}
//	std::vector<int> vLineId;	//开洞线
//	int idHolePoint;			//开洞点
//
//	std::vector<int> vPointId;			//中间数据、polygon 点号
//	bool marked;
//};


////对应一个多边形，可能包含开洞， 内多变性要从开洞点在多边形内部判断
//struct XYREGION //子区域
//{
//	std::vector<int> vLineId;			//线, 可区域共用
//	std::vector<int> vHoleId;			//开洞编号
//
//	std::vector<int> vPointId;			//中间数据、外环点号
//};


struct XYFIBER
{
	XYFIBER() { area = 0; xoff = 0; yoff = 0; }

	float xoff;
	float yoff;
	float area;
};

struct XYSect
{
public:
	XYSect() {
		m_Area =0;
		m_Ix = 0;
		m_Iy = 0;
		m_xCenter = 0;
		m_yCenter = 0;
		m_div = 8;
		//		isHole = false;
		areatype = 0;
		marked = false;
	}

	//	bool isHole;
	int areatype;
	bool marked;
	XYPOINT holePoint;

	std::vector<XYPOINT> vPoint;					//点，可共用
	std::vector<XYLINE> vLine;						//线, 可区域共用

	//	std::vector<int> vOutPointId;					//外边点，用于绘制
	//	std::vector<std::vector<int>> vInnerPointId;	//内边点，用于绘制

	std::vector<XYPOINT> vHolePoint;		//开洞点

	//	std::vector<XYHOLE> vHole;				//开洞
	//包含的开洞点号
	//	std::vector<int> vHolePtId;				//开洞编号

	//	std::vector<XYREGION> vRegion;			//每个子多边形，内部可能包含开洞
	//	std::vector<XYHOLE> vHole;				//每个开洞

	std::vector<XYPOINT> m_vecMeshPoint;	//网格点
	std::vector<XYPOLY> m_vecMeshFace;		//面单元、目前只是三角形，后面有可能是四边形
	std::vector<XYLINE> m_vecMeshLine;		//网格线

	float m_Area;
	float m_Ix;
	float m_Iy;
	float m_xCenter;
	float m_yCenter;

	float m_xMin;
	float m_xMax;
	float m_yMin;
	float m_yMax;
	float m_HalfLen;	//网格纤维总高和宽的一半

	int m_div;

	std::vector<XYFIBER> m_vecFiber;
	//	int GetMeshLineID(int id1, int id2);

	int GetPointID(float x, float y) 
	{
		int num = (int)vPoint.size();
		for(int i=0; i<num; i++) {
			XYPOINT &point = vPoint[i];
			if(fabsf(point.x -x) + fabsf(point.y-y) < 0.001f)
				return i;
		}
		return -1;
	}

	int AddPoint(float x, float y)
	{
		int id = GetPointID(x, y);
		if(id < 0) {
			id = (int)vPoint.size();
			XYPOINT pt;
			pt.id = id;
			pt.x = x;
			pt.y = y;
			vPoint.push_back(pt);
		}
		return id;
	}

	int GetLine(int id1, int id2)
	{
		int num = vLine.size();
		for(int i=0; i<num; i++) {
			if(vLine[i].id1 == id1 && vLine[i].id2 == id2) {
				return i;
			}
		}
		return -1;
	}

	int AddLine(int id1, int id2)
	{
		int id = GetLine(id1, id2);
		if(id < 0) {
			id = (int)vLine.size();
			XYLINE line;
			line.id1 = id1;
			line.id2 = id2;
			vLine.push_back(line);
		}
		return id;
	}

	//	XYSect & operator=(const XYSect & mesh)
	//	{
	//		if(this==&mesh) return *this;
	////		ASSERT(FALSE);
	//		return *this;
	//	}

	//将每个开洞 归到相应的区域中

	//形成小网格单元面积、形心等
	void fnc_GenerateMeshLine();
	void fnc_CalcProperty();
	void fnc_MergeFiber();

	//	void MeshingRegion(XYREGION& region);
};


