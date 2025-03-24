#pragma once
#include "HeadDefine.h"
#include "DataVertex.h"

//�߶���
class _SSG_DLLIMPEXP CLine : public CPrimitiveProp
{
public:
	CLine(void);
	CLine(int i1,int i2,int istory);
	~CLine()
	{
		if (pNodes != nullptr)
		{
			delete[]pNodes;
			pNodes = nullptr;
		}
	};

	int VexIDM1,VexIDM2;  //�˵�IDM
	float fDeadLoad,fLiveLoad; //���غ�,�����в���ȡ����Ӧ��ʱ��д��ֵ��KN/m
	int idmBoundary;  //�߽�����ID�����������д����������2
	LOADASSIGN aload;  //��Ӧ���ع����ĺ��� 
	int *pNodes;//��ʱ����  //�ڵ㼯��,����ȫ�������Լ�����������γ�
	int nNodes;
	CPinData aPin;

	//�жϱ�����ͬ
	BOOL operator==(const CLine& line) const
	{
		if (line.VexIDM1 == VexIDM1 && line.VexIDM2 == VexIDM2)
			return TRUE;

		if (line.VexIDM1 == VexIDM2 && line.VexIDM2 == VexIDM1)
			return TRUE;

		return FALSE;
	}

	//���ƹ��캯��
	CLine(const CLine& line)
	{
		pNodes = nullptr;
		*this = line;
	}

	//�жϱ�����ͬ: pNodes
	CLine& operator=(const CLine& line)
	{
		if (this == &line)
			return *this;

		if (pNodes != nullptr)
		{
			delete[]pNodes;
			pNodes = nullptr;
			nNodes = 0;
		}

		*(CPrimitiveProp*)this = (CPrimitiveProp&)line;

		VexIDM1 = line.VexIDM1;
		VexIDM2 = line.VexIDM2;
		fDeadLoad = line.fDeadLoad;
		fLiveLoad = line.fLiveLoad;
		idmBoundary = line.idmBoundary;
		aload = line.aload;
		aPin = line.aPin;
		//nNodes=line.nNodes;
		//if(line.pNodes)
		//{
		//	pNodes=new int[nNodes];
		//	for (int i=0;i<nNodes;i++)
		//		pNodes[i]=line.pNodes[i];
		//}

		return *this;
	}

	BOOL IsCrossStory(const CVertex* vex) const;
	//void SetCrossStory(BOOL bCrossStory=TRUE);  //ʵ�����������ߵĶ˵㣬�����ݱ��п�����ԣ�Ӧ����ʹ�õ����Դ���

	inline float Length(const CVertex *vex) const //vexΪ������������
	{
		float x = vex[VexIDM1].x - vex[VexIDM2].x;
		float y = vex[VexIDM1].y - vex[VexIDM2].y;
		float z = vex[VexIDM1].z - vex[VexIDM2].z;

		return sqrtf(x * x + y * y + z * z);
	}

	inline float Angle(const CVertex *vex) const //vexΪ������������
	{
		float x = vex[VexIDM1].x - vex[VexIDM2].x;
		float y = vex[VexIDM1].y - vex[VexIDM2].y;
		float z = vex[VexIDM1].z - vex[VexIDM2].z;

		float length= sqrtf(x * x + y * y + z * z);

		float high=abs(z);

		return acos(high/length);
	}

	inline BOOL InRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ���ȫ�ھ��η�Χ�ڣ������߽��غ�
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)>0) return FALSE;
		if((vex1.y-vMin.y)*(vex1.y-vMax.y)>0) return FALSE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)>0) return FALSE;
		if((vex2.y-vMin.y)*(vex2.y-vMax.y)>0) return FALSE;
		return TRUE;
	}

	inline BOOL CrossRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ�������ص��������߽��غ�
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)<0 && (vex1.y-vMin.y)*(vex1.y-vMax.y)<0) return TRUE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)<0 && (vex2.y-vMin.y)*(vex2.y-vMax.y)<0) return TRUE;
		return FALSE;
	}

	void Clear(void);
	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ
};

//�����Ĺ����棬������ʾ����
class _SSG_DLLIMPEXP CSurface
{
public:
	CSurface(void) {nVertex=0;pVertex=NULL;color=0;}
	~CSurface() {delete[] pVertex;}

	CSurface(CSurface &surf)
	{
		pVertex=NULL;
		*this=surf;
	}

	//��ֵ���������
	CSurface & operator=(const CSurface& surf)
	{
		if(this==&surf) return *this;

		delete[] pVertex;
		nVertex=surf.nVertex;
		pVertex=new Vector4[nVertex];
		for(int i=0;i<nVertex;i++)
		{
			pVertex[i]=surf.pVertex[i];
		}
		return *this;
	}

	int nVertex; //������
	Vector4 *pVertex; //�����������飬����ڹ����ľֲ�����
	DWORD color; //ʵ�ʻ�����ɫ
};

class _SSG_DLLIMPEXP CBeamFace
{
public:
	CBeamFace(void);
	~CBeamFace();

	Vector4 a1,b1,c1,d1; //��һ����Ķ���
	Vector4 a2,b2,c2,d2; //�ڶ�����Ķ���
	float fColor1,fColor2,fColor3; //a1-a2����ϵ����a1-b1����ϵ����a1-d1����ϵ��
};


class _SSG_DLLIMPEXP CStraightLine
{
public:
	int N;
	int Line[100];
	int Node[100];
	CStraightLine()
	{
		N = 0;
		memset(Line, 0, 100 * sizeof(int));
		memset(Node, 0, 100 * sizeof(int));
	}
	void AddLine(int iLine)
	{
		Line[N++] = iLine;
	}
};