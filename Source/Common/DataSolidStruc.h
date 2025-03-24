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
//	//int id; //��������id����1��ʼ��ţ������湹���������
//	//�߽��߶���
//	int nLine; 
//	//�߽��߶�����
//	int *pLineIDM;
//	int iSectionID;  //����ID
//
//	//���ظ�ֵ�����
//	CFace & operator=(const CFace &plate);
//
//	void Clear();
//
//	//���ñ����������������Сԭ���ݱ����
//	void SetLineNum(int nline) 
//	{
//		//nLine=nline;
//		//if(pLineIDM) delete[] pLineIDM; 
//		//pLineIDM=new int[nLine];
//		//ASSERT(pLineIDM);
//	}
//
//	//���ض������������˳�����еĶ������PointID����β�㲻�غϣ��ⲿ����ά���ڴ�PointID��pLineΪϵͳ�߶α������飬
//	//��������Ľ�����겻�غϣ���û��������ͬ�����벻ͬ�ĵ�
//	int GetVexID(int *PointID,const CLine *pLine) const; 
//
//	//���ص㵽��ID�Ĺ�����
//	BOOL GetPt2Line(PT2LINE *pPt2Line,const CLine *pLine);
//
//	//�����ι�ϵ����ֲ�����ʸ����wΪ���ߣ������ŷ������ֶ���
//	BOOL PlateLocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray);
//
//	//���������߶�ID���ӵ�j���߶ο�ʼ��way>0�����������У�way<0������������
//	void RenewLineID(int j,int way);
//
//	//�������ֲ�,nLayer--�ֲ�����fThick--ÿ���ȣ����ȷֲ㣬pos--ÿ��λ�����飬iMaxLayers--pos��������
//	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);
//
//	//���,���طֲ�����pThick--ÿ���ȣ�iMaxLayers--������
//	int GetRebarLayer(double *pThick,int iMaxLayers);
//	int GetRebarLayer(float *pThick,int iMaxLayers);
//	// �� 2020��10��28��
//	int GetRebarLayer(float *pThick);
//
//	//�õ����귶Χ
//	void GetRange(Vector4 &rMin,Vector4 &rMax);
//
//	//����ǽ�ĸ߶ȺͿ�ȣ��ڰ�����
//	void GetWallSize(float &fWidth,float &fHeight);
//
//	//����ǽ�Ĺ涨��෶Χ��������
//	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);
//
//	//������ǽ�ֽ���������λ��kN
//	float GetRebarWeight();
//
//	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf,CPlateSectionCollection &cPlateSection,CProjectPara &cPrjPara);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
//	virtual BOOL Write(CASCFile &fout,int idf);
//
//	//�����Ϣ��д
//	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
//	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
//
//	//���ݽ�����Ϣˢ�¹�����Ϣ
//	void RenewPlate();
//
//	void GenLoadId(bool bRewrite=true);//��	float fDeadLoad ��float fLiveLoad����Load����mapload ��2020֮��汾��ȡ
//	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ
//
//	//���߽�˳�򷵻��ĸ��ǵ�ID�����¡����¡����ϡ�����
//	BOOL GetCornerPoint(int &left_bottom,int &right_bottom,int &right_top,int &left_top)const;
//};

//typedef shared_ptr<Vector4 *> PVector4;

class _SSG_DLLIMPEXP CSolidFace
{
public:
	std::vector<int> vVertexIDM;

	//������
	//��Ӧ��edge ���
	std::vector<int> vEdgeIDM;
	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ������ʱ��Ҫ����PlateLocalCoorVector���¼���
//	Vector4 u,v,w,c0;  //���ֲ̾�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,
	Vector4 v;		//���߷���
};

//typedef std::vector<std::vector<int>> vec
//template <typename T> std::vector<std::vector<T>> vecvec;

//ʵ����
//��ʱ ���ǰ� ��ǵ����Զ���
//�������Ǵ�������ģ������汾��Ҫ���ֽ�ֲĵȵ�������������й���
//��1�� �Ǿ��ʲ��ϣ����нڵ����

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

	//��ֵ���������
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

//����
	std::vector<CSolidFace> vFaceSet;		//Face ���
	int iStrucType;							//����, future

//��ʱ ����face����
//��Ҫ���ɷ�����������ʱ����ʱ��Ϊ�������
	int nVertex;							//������
	Vector4 *pVertex;						//�����������飬����ڹ����ľֲ�����
	//std::vector<Vector4 *> vVertex;

	int nLine; 
	int *pLineIDM;						//Edge 
	
	//��ע, ��ʱ ֻ֧�� uniaxial ����ͬ�Բ��ϣ� ���Եġ�
	//���ϲ��� �ַ�����ʾ�������� ͨ�õı�ű�ʾ
	int iMat;							//���ϱ��

	std::vector<int> vLoadID;			//����id
	std::vector<int> vSolidTag;			//����

	//int solidtag[5];					//����
	//����FACE����
//	std::vector<int> vVertexIDM;		//������
//	std::vector<int> vEdge;				//Edge (Line) ���
	//Ҫ�з�������ÿ�����γɱ�

	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ������ʱ��Ҫ����PlateLocalCoorVector���¼���
	Vector4 u,v,w,c0;  //���ֲ̾�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,

	//Vertex List
	//Face List

	//Edge ��������
	//vertex
	//0 0 0
	//0 0 1
	//0 1 1
	//0 1 0
	//4 0 1 2 3  {start of face list}
	//4 7 6 5 4
	//4 1 5 6 2

	DWORD color;		//ʵ�ʻ�����ɫ

	virtual bool Read(CASCFile &fin, STRUCT_TYPE iType, int &idf);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
	virtual bool Write(CASCFile &fout, int idf);

	bool ReadPly(std::string filename);		//���� Ply
	bool WritePly(std::string filename);	//д�� Ply
};
