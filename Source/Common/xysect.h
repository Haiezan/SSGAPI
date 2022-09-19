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
	int attribute;	//����  0 ����  1--����   2--���ж�

	//	int idholept;
	XYPOINT holepoint;	//���ڶ���holepoint, ����ͨ������������ƽ��ֵ���Ƽ��㣬 �Ѵ��� ���ڲ���,
	//���� ������ �н�С��180��ʱ �����ҵ����ĵ�Ҳ���ԡ�

	float area;		//���
	float xcenter;	//���ĵ�����
	float ycenter;
	//float calc_area() 
	//{
	//}
	//	bool marked;
};


//struct XYHOLE //����
//{
//	XYHOLE(){marked=false;}
//
//	std::vector<XYPOINT> vPoint;
//	std::vector<XYLINE> vLine;	//������
//	int idHolePoint;			//������
//
////	std::vector<int> vPointId;			//�м����ݡ�polygon ���
//	bool marked;
//};


//struct XYHOLE //����
//{
//	XYHOLE() : marked(false) {}
//	std::vector<int> vLineId;	//������
//	int idHolePoint;			//������
//
//	std::vector<int> vPointId;			//�м����ݡ�polygon ���
//	bool marked;
//};


////��Ӧһ������Σ����ܰ��������� �ڶ����Ҫ�ӿ������ڶ�����ڲ��ж�
//struct XYREGION //������
//{
//	std::vector<int> vLineId;			//��, ��������
//	std::vector<int> vHoleId;			//�������
//
//	std::vector<int> vPointId;			//�м����ݡ��⻷���
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

	std::vector<XYPOINT> vPoint;					//�㣬�ɹ���
	std::vector<XYLINE> vLine;						//��, ��������

	//	std::vector<int> vOutPointId;					//��ߵ㣬���ڻ���
	//	std::vector<std::vector<int>> vInnerPointId;	//�ڱߵ㣬���ڻ���

	std::vector<XYPOINT> vHolePoint;		//������

	//	std::vector<XYHOLE> vHole;				//����
	//�����Ŀ������
	//	std::vector<int> vHolePtId;				//�������

	//	std::vector<XYREGION> vRegion;			//ÿ���Ӷ���Σ��ڲ����ܰ�������
	//	std::vector<XYHOLE> vHole;				//ÿ������

	std::vector<XYPOINT> m_vecMeshPoint;	//�����
	std::vector<XYPOLY> m_vecMeshFace;		//�浥Ԫ��Ŀǰֻ�������Σ������п������ı���
	std::vector<XYLINE> m_vecMeshLine;		//������

	float m_Area;
	float m_Ix;
	float m_Iy;
	float m_xCenter;
	float m_yCenter;

	float m_xMin;
	float m_xMax;
	float m_yMin;
	float m_yMax;
	float m_HalfLen;	//������ά�ܸߺͿ��һ��

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

	//��ÿ������ �鵽��Ӧ��������

	//�γ�С����Ԫ��������ĵ�
	void fnc_GenerateMeshLine();
	void fnc_CalcProperty();
	void fnc_MergeFiber();

	//	void MeshingRegion(XYREGION& region);
};


