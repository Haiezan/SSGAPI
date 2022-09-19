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

//类定义------------------------------------------------------------------------

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

//得到g_StructKeyword中的的结构类型索引号
//int GetStructKeywordIndex(STRUCT_TYPE itype);
int _SSG_DLLIMPEXP GetStructKeywordIndex(STRUCT_TYPE itype);
extern "C" _SSG_DLLIMPEXP int GetStructKeywordIndex(const CString  &keyword);




//竖向构件是否位于用户选择的层间位移角输出位置的集合内，返回序号，不存在则返回-1
//如果用户未定义，则返回-2，表示缺省全部输出
extern "C" _SSG_DLLIMPEXP int DriftPosEle(const CBeamElm &elm);
extern "C" _SSG_DLLIMPEXP int DriftPos(const CBeamStruc &pillar);


//线单元是否全部都在矩形范围内
int IsInRect(const CBeamElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CTriangleElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CQuadElm &elm,float xmin,float ymin,float xmax,float ymax);
//线构件是否全部都在矩形范围内
BOOL IsInRect(const CBeamStruc &beam,float xmin,float ymin,float xmax,float ymax);
BOOL IsInRect(const CPlateStruc &plate,float xmin,float ymin,float xmax,float ymax);

//全局函数---------------------------------------------------------------------

#include "DataFunc.h"

//项目群信息
struct MUL_PROJRCT  //没有实际使用
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

	CVertex c0; //坐标原点偏移量
	Vector4 vMin,vMax; //实际坐标范围，考虑了坐标偏移和旋转
	float fRadium; //最大占地半径，米
	float fHalfHeight; //楼高的一半，米
	float angle; //绕z轴转角，单位度
	CString sName; //建筑物名称
};

class _SSG_DLLIMPEXP CRefPoint  //没有实际使用
{
public:
	CRefPoint(void){;}
	~CRefPoint() {aVex.RemoveAll();}

	void Clear(void) {aVex.RemoveAll();}


	//切换一个点,如果不存在则新增，返回TRUE；如果已经存在则删除，返回FALSE
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

	CArray<int,int> aVex; //计算虚拟交叉点用的参考点ID
};

