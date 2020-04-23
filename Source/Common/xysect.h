#pragma once
#include <vector>

struct XYPOINT
{
	XYPOINT() { id = -1;}
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
	XYPOLY() { id = -1; attribute = 0; area = 0; xcenter=0; ycenter=0;} // xoff = 0; yoff = 0; }
	int id;
	std::vector<int> m_vecPointID;
	int attribute;	//属性  0 正常  1--洞口   2--洞中洞

	XYPOINT holepoint;	//用于定义holepoint

	float area;
	float xcenter;
	float ycenter;
	//float calc_area() 
	//{

	//}
};

struct XYFIBER
{
	XYFIBER() { 
		//id = -1; 
		area = 0; 
		xoff = 0; 
		yoff = 0; 
	}
	//int id;

	float xoff;
	float yoff;
	float area;
};

class XYSect
{
public:
	XYSect() 
	{
		m_Area =0;
		m_Ix = 0;
		m_Iy = 0;
		m_xCenter = 0;
		m_yCenter = 0;
		m_div = 8;
	}
	std::vector<XYPOINT> m_vecPoint;		//点，可共用
	std::vector<XYPOLY> m_vecRegion;		//区域， 可包含
	std::vector<XYLINE> m_vecLine;			//线, 可区域共用

	std::vector<XYPOINT> m_vecMeshPoint;	//网格点
	std::vector<XYPOLY> m_vecMeshFace;		//面单元、目前只是三角形，后面有可能是四边形
	std::vector<XYLINE> m_vecMeshLine;		//网格线

	//void Clear();

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

	int m_div;		//division

	std::vector<XYFIBER> m_vecFiber;
	int GetMeshLineID(int id1, int id2);
	int GetPointID(float x, float y);
	//形成小网格单元面积、形心等
	void fnc_GenerateMeshLine();
	void fnc_CalcProperty();
	void fnc_MergeFiber();
};

