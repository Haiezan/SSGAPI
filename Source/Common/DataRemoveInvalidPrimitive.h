#pragma once
#include "HeadDefine.h"
#include "SysPara.h"

class CVertex;
class CBeamElm;
class CQuadElm;
class CLine;
class CGroupCollection;
class CTriangleElm;
class CBeamStruc;
class CPlateStruc;

//清理无效图元
class _SSG_DLLIMPEXP CRemoveInvalidPrimitive
{
public:
	CRemoveInvalidPrimitive(void) {;}
	~CRemoveInvalidPrimitive(void) {;}

protected:
	virtual void RearrangeID()=0;  //重新编排ID，去掉无效图元
	void RemoveInvalidVex(int &nVex,CVertex *pVex,int *index1,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);      //去掉无效框架点，被RearrengeID调用
	void RemoveInvalidNode(int &nVex,CVertex *pVex,int *index1);      //去掉无效网格结点，被RearrengeID调用
	void RemoveInvalidBeamElm(int &nElm,CBeamElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidTriangleElm(int &nElm,CTriangleElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidQuadElm(int &nElm,CQuadElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidLine(int &nLine,CLine *pLine,CArray<CVertex,CVertex&> &aVex,int *index2,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //被RearrengeID调用 
	void RemoveInvalidGuides(int &nGuides,CVertex *pVex,CLine *pLine,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //被RearrengeID调用
	BOOL RemoveInvalidBeamStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CBeamStruc *pStruc,int *index4,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //被RearrengeID调用  返回：TRUE，数据已改变
	BOOL RemoveInvalidPlateStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CPlateStruc *pStruc,int *index3,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //被RearrengeID调用  返回：TRUE，数据已改变

	void RemoveInvalidGroup(STRUCT_TYPE iPrimType,int nStruc,const int *index1,CGroupCollection &aGroup);  //被以上各图元函数调用
public:
	static void RemoveMemberFromGroup(int *pSelNames, int nSel, CGroupCollection &aGroup);
};
