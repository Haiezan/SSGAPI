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

//������ЧͼԪ
class _SSG_DLLIMPEXP CRemoveInvalidPrimitive
{
public:
	CRemoveInvalidPrimitive(void) {;}
	~CRemoveInvalidPrimitive(void) {;}

protected:
	virtual void RearrangeID()=0;  //���±���ID��ȥ����ЧͼԪ
	void RemoveInvalidVex(int &nVex,CVertex *pVex,int *index1,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);      //ȥ����Ч��ܵ㣬��RearrengeID����
	void RemoveInvalidNode(int &nVex,CVertex *pVex,int *index1);      //ȥ����Ч�����㣬��RearrengeID����
	void RemoveInvalidBeamElm(int &nElm,CBeamElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidTriangleElm(int &nElm,CTriangleElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidQuadElm(int &nElm,CQuadElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidLine(int &nLine,CLine *pLine,CArray<CVertex,CVertex&> &aVex,int *index2,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //��RearrengeID���� 
	void RemoveInvalidGuides(int &nGuides,CVertex *pVex,CLine *pLine,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //��RearrengeID����
	BOOL RemoveInvalidBeamStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CBeamStruc *pStruc,int *index4,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //��RearrengeID����  ���أ�TRUE�������Ѹı�
	BOOL RemoveInvalidPlateStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CPlateStruc *pStruc,int *index3,CGroupCollection &aGroup,CGroupCollection *DmpGroup=NULL);   //��RearrengeID����  ���أ�TRUE�������Ѹı�

	void RemoveInvalidGroup(STRUCT_TYPE iPrimType,int nStruc,const int *index1,CGroupCollection &aGroup);  //�����ϸ�ͼԪ��������
public:
	static void RemoveMemberFromGroup(int *pSelNames, int nSel, CGroupCollection &aGroup);
};
