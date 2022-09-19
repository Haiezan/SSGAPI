#pragma once

#include "HeadDefine.h"
//#include "Vector4.h"
//#include "Matrix4x4.h"
////#include "SysPara.h"
//#include "PublicFunc.h"
//#include "PublicFunc_MFC.h"
//#include "PublicFunc_Cpp.h"
//
//#include "ASCFile.h"
//#include "UserDefine.h"
//#include "BeamSection.h"
//#include "Material.h"
//#include "EdgeStruct.h"
//#include "PlateSection.h"
//#include "Loadmap.h"

//#include <afxtempl.h>
//#include <vector>
//#include <map>
////#include <algorithm>
////#include <functional>
//
//using namespace std;

#include "DataPrimitive.h"
#include "DataVertex.h"
#include "DataLineSurface.h"

//class CLine;
//class CFrame;
//class CMesh;

#include "DataPointWallIndex.h"

//�ඨ��------------------------------------------------------------------------

#include "DataStrucProp.h"
#include "DataBoundary.h"

#include "DataDamper.h"
#include "DataBeamStruc.h"
#include "DataPlateStruc.h"
#include "DataSolidStruc.h"

#include "DataStory.h"

#include "DataBeamElm.h"
#include "DataTriangleElm.h"
#include "DataQuadElm.h"

#include "DataOutput.h"
#include "DataGroup.h"
#include "DataStoryItem.h"
#include "DataStage.h"
#include "DataDataPath.h"
#include "DataRemoveInvalidPrimitive.h"

_SSG_DLLIMPEXP STRUCT_TYPE GetStructType(const CBeamElm &elm);
_SSG_DLLIMPEXP STRUCT_TYPE GetStructType(const CTriangleElm &elm);
_SSG_DLLIMPEXP STRUCT_TYPE GetStructType(const CQuadElm &elm);

//�õ�g_StructKeyword�еĵĽṹ����������
//int GetStructKeywordIndex(STRUCT_TYPE itype);
int _SSG_DLLIMPEXP GetStructKeywordIndex(STRUCT_TYPE itype);
extern "C" _SSG_DLLIMPEXP int GetStructKeywordIndex(const CString  &keyword);




//���򹹼��Ƿ�λ���û�ѡ��Ĳ��λ�ƽ����λ�õļ����ڣ�������ţ��������򷵻�-1
//����û�δ���壬�򷵻�-2����ʾȱʡȫ�����
extern "C" _SSG_DLLIMPEXP int DriftPosEle(const CBeamElm &elm);
extern "C" _SSG_DLLIMPEXP int DriftPos(const CBeamStruc &pillar);


//�ߵ�Ԫ�Ƿ�ȫ�����ھ��η�Χ��
int IsInRect(const CBeamElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CTriangleElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CQuadElm &elm,float xmin,float ymin,float xmax,float ymax);
//�߹����Ƿ�ȫ�����ھ��η�Χ��
BOOL IsInRect(const CBeamStruc &beam,float xmin,float ymin,float xmax,float ymax);
BOOL IsInRect(const CPlateStruc &plate,float xmin,float ymin,float xmax,float ymax);

//ȫ�ֺ���---------------------------------------------------------------------

#include "DataFunc.h"

//��ĿȺ��Ϣ
struct MUL_PROJRCT  //û��ʵ��ʹ��
{
	MUL_PROJRCT(void)
	{
		sFile=L"";
		iFirstNode=0;
		iFirstBeamElm=0;
		iFirstTriElm=0;
		iFirstQuadElm=0;
		nNode=0;
		nBeamElm=0;
		nTriElm=0;
		nQuadElm=0;

		c0.x=0.0f;
		c0.y=0.0f;
		c0.z=0.0f;
		angle=0.0f;

		sName=L"";

		fRadium=0;
		fHalfHeight=0;
	};

	CString sFile;
	int iFirstNode;
	int iFirstBeamElm;
	int iFirstTriElm;
	int iFirstQuadElm;
	int nNode;
	int nBeamElm;
	int nTriElm;
	int nQuadElm;

	CVertex c0; //����ԭ��ƫ����
	Vector4 vMin,vMax; //ʵ�����귶Χ������������ƫ�ƺ���ת
	float fRadium; //���ռ�ذ뾶����
	float fHalfHeight; //¥�ߵ�һ�룬��
	float angle; //��z��ת�ǣ���λ��
	CString sName; //����������
};

class _SSG_DLLIMPEXP CRefPoint  //û��ʵ��ʹ��
{
public:
	CRefPoint(void){;}
	~CRefPoint() {aVex.RemoveAll();}

	void Clear(void) {aVex.RemoveAll();}


	//�л�һ����,���������������������TRUE������Ѿ�������ɾ��������FALSE
	BOOL SetVex(int vexid)
	{
		for (int i=0;i<aVex.GetCount();i++)
		{
			if(aVex[i]==vexid)
			{
				aVex.RemoveAt(i);
				return FALSE;
			}
		}
		aVex.Add(vexid);
		return TRUE;
	}

	CArray<int,int> aVex; //�������⽻����õĲο���ID
};

