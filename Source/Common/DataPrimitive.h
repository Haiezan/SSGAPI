#pragma once

#include <afxtempl.h>
#include <vector>
#include <map>

#include "SysPara.h"
#include "HeadDefine.h"
#include "ASCFile.h"

class CLine;

using namespace std;

//���������ཻ���
struct LINE_CROSS_POLY
{
	//type--�ཻ���ͣ�
	//-1 -- ��������
	//0--���ཻ����������Ͳ�����
	//1--�߽��ڶ����1�����㣬��������Ͳ�����
	//�����ཻ��2--���������ཻ��2���㣬3--�������α���(����)�غϣ�6--���ڶ������
	//�������ཻ��4--�������α߽����ཻ(�����ڽ����幹��֮ǰ�ͽ����˽ṹ�ߣ����������߶�֮����ཻ�������˸��߶�һ�㲻���ܽ��ڱ߽��ߵ��м��)��
	//			  5--���������ڲ��ཻ
	int type; 
	int pointid1;  //����ID1��type=1,2��Ч
	int pointid2;  //����ID2��type=2��Ч
	int plateid1,plateid2; //�µĶ����ID
};

struct CROSS_POINT
{
	int id;
	float t;
	int iLine;
	CROSS_POINT *pPair;

	bool operator < (const CROSS_POINT& cp ) const //��������ʱ����д�ĺ���
	{
		return t < cp.t;
	}
};

struct CROSS_PLATE
{
	int plateid;  //�湹��ID
	int crossvexid;  //�����

	bool operator == (const CROSS_PLATE& cp)
	{
		return (plateid==cp.plateid) && (crossvexid==cp.crossvexid);
	};

	bool operator < (const CROSS_PLATE& cp) //��������ʱ����д�ĺ���
	{
		if(plateid < cp.plateid) 
			return TRUE;
		else if(plateid == cp.plateid) 
			return crossvexid < cp.crossvexid;
		else
			return FALSE;
	};
};

//¥�㷶Χ�ṹ
struct STORY_RANGE
{
	int iStoryMin;
	int iStoryMax; 
};

//�����ɵ����򹹼�����Ԫ
struct BEAM_CONN_LAYER
{
	int idBeam;  //��Ԫ���
	int idNode;  //�ֲ������ţ�0-1
};

//�����ɵĿǵ�Ԫ
struct SHELL_CONN_LAYER
{
	int idShell;  //�ǵ�Ԫ���
	int idNode1;  //��¥�������ľֲ����,������0~2���ı���0~3
	int idNode2;  //��¥�������ľֲ����,������1~2���ı���1~3��-1��ʾ������
};

//ͳ�Ƹ���������
struct STRUCT_COUNT
{
	int nPoint   	;       //��
	int nLine    	;       //�ṹ��
	int nBeam    	;       //��
	int nPillar  	;       //��
	int nBracing 	;       //б��
	int nEdge		;       //Լ����Ե����
	int nHidebeam   ;       //����
	int nLongirebar ;       //�����ݽ�
	int nLink ;       //������	//�Ǳ��� 2015.5.21
	int nPlate 		;       //��
	int nWall  		;       //ǽ
	int nGuides    	;       //������
};

//�߽��ͱ߽��߹�����ϵ
struct BND_NODE_LINE
{
	int nline;
	int line[2];  //�߱�ţ����2��
};

//�ṹ���Ƽ��ؼ���
struct STRUCT_KEYWORD
{
	int iType;
	CString sTitle;
	CString sKeyword;

};

enum LOAD_TYPE
{
	LOAD_DEAD=0,		//0-���Ϸֲ����Ӻ��أ�
	LOAD_LIVE=1,		//1-���Ϸֲ����ӻ��أ�
	LOAD_SLAB_DEAD=2,	//2-�帽�Ӻ��ش��������Ϸֲ����أ�
	LOAD_SLAB_LIVE=3,	//3-�帽�ӻ��ش��������Ϸֲ����أ�
	LOAD_SLAB_WEIGHT=4,	//4-�����ش��������Ϸֲ�����
};

//�㵽�߹���(�����ṹ�ߡ���������)�����ӹ�ϵ��������
struct _SSG_DLLIMPEXP PT2LINESTRUCT
{
	PT2LINESTRUCT(void) {conn_vex1=conn_vex2=conn_beam1=conn_beam2=-1;}

	int conn_beam1,conn_vex1; //�����ĵ�һ���߹�����id�͵�ţ��Լ��߹���¥���
	int conn_beam2,conn_vex2; //�����ĵڶ����߹�����id�͵�ţ��Լ��߹���¥���

	void Append(int beam, int vex)
	{
		if(conn_beam1==-1)
		{
			conn_beam1=beam;
			conn_vex1=vex;
		}
		else
		{
			conn_beam2=beam;
			conn_vex2=vex;
		}
	}
};

//һ���㵽�����߶εĹ�����-1Ϊ��ЧID�����ڶ���α߽�
struct _SSG_DLLIMPEXP PT2LINE
{
	PT2LINE(void) {iVexID=-1;iLeftLineID=iRightLineID=-1;}
	int iVexID; //��ID
	int iLeftLineID,iRightLineID;  //��ߵ��߶�ID���ұߵ��߶�ID
};

//��Ϲ���
struct _SSG_DLLIMPEXP COMBO_STRUCT
{
	COMBO_STRUCT(void) {sName=L"";}
	~COMBO_STRUCT() {Clear();}
	void Clear(void) {vIDG.clear();sName=L"";}
	CString sName;
	vector<int> vIDG;
};

struct _SSG_DLLIMPEXP STRUCT_PROPERTY1
{
	int iCode;  //���Դ���=����Ԫ����ţ������������
	CString sName;  //��������
	CString sUnit;  //���Ե�λ
	BOOL bBeam,bPillar,bBrace,bPlate,bWall,bBeamWall;  //�Ƿ�����ĳ�๹��ʹ��
	int iDataType; //0-float,1-CString
};

//�ṹ���ʷ����������ɵ����߶�
struct _SSG_DLLIMPEXP SUB_LINE
{
	int		nSubLine;	//��ʼ��Ϊ0����ʾû�л������߶�
	CLine	*pSubLine;	//���߶����飬��ʼ��ΪNULL
};

//�ṹ���Ƿ�����ǽ�õ�
struct _SSG_DLLIMPEXP LINE_USED
{
	LINE_USED(void)
		:bBeam(FALSE)
		, bPillar(FALSE)
		, bWall(FALSE)
		, bBeamWall(FALSE)
		, bAlong(TRUE)
		, bLink(FALSE)
		, bAnti(FALSE)
		, fWeight(0)
		, fMeshRatio(1.f)
	{
	}
	BOOL bBeam;    //�Ƿ����õ�
	BOOL bPillar;  //�Ƿ����õ�
	BOOL bWall;    //�Ƿ�ǽ�õ�������ǽ��ṹ���Ƿ�ͬ¥�㣬ǽ������ǽ
	BOOL bBeamWall;//�Ƿ�ǽ���õ�������ǽ����ṹ���Ƿ�ͬ¥��
	BOOL bAlong;   //�Ƿ���������˽½ӵ��߹���ʹ��
	BOOL bLink;    //�Ƿ�һ������ʹ��
	BOOL bAnti;    //�Ƿ����˽½ӵ��߹���ʹ��
	float	fWeight;	//�����ۼ�Ȩ��
	float	fMeshRatio;	//�����ۼƼ���ϵ��
};

//�ඨ��------------------------------------------------------------------------


//ͼԪ����
class _SSG_DLLIMPEXP CPrimitiveProp
{
public:
	CPrimitiveProp(void);
	CPrimitiveProp(DWORD clc, int iStory = 0);

	int idmStory;     //¥��IDF=IDM,��0��ʼ���,0Ϊ����
	int iStage;        //ʩ���׶�,��0��ʼ���
	int iTower;		//�ֿ�ţ����ţ���0��ʼ���

	//��ʱ����,�������ļ�
	union
	{
		DWORD dwColor;  //��ɫ
		unsigned char RGBA[4];
	};

	int tag;			//tag ���
	unsigned char iStatus;  //״̬��־��0��Ч��1-������2-ѡ�У�3-�ο���(Ŀǰֻ�Ե���Ч)
	CString sComments;  //������ʾ��˵������,�ɳ�����ʱ����

	CPrimitiveProp & operator=(const CPrimitiveProp &prop)
	{
		if(this==&prop) return *this;

		idmStory=prop.idmStory; 
		iStage=prop.iStage;
		iTower=prop.iTower;
		dwColor=prop.dwColor;
		iStatus=prop.iStatus;  
		//iStatus=1; //�����Ƶ�ͼԪ�Զ������Ч2012-10-25
		sComments=prop.sComments;
		tag = prop.tag;

		return *this;
	}

	void Clear();

	virtual BOOL Read(CASCFile &fin);   
	virtual BOOL Write(CASCFile &fout);
	virtual BOOL Write2020(CASCFile &fout);

	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);

	virtual BOOL IsValid(void) const;
};
