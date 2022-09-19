#pragma once
#include "PublicFunc_MFC.h"
#include "map"

struct TreeData
{
	int idText;
	BOOL bCheck;
};

enum ITEMTYPE
{
	NOICON,
	ICON1,
	ICON2,
	BOTH,
};

struct InitTreeData
{
	int iRoot;					//�ڵ�ȼ�
	CString sItemText;		//��ʾ�ַ�
	int iIndex;					//Id Item
	ITEMTYPE iType;		//ͼ������
	int iIcon;						//����ǰͼ��
	InitTreeData()
	{
		iRoot=0;
		sItemText.Empty();
		iIndex=-1;
		iIcon=-1;//Ĭ��û��ͼ��
		iType=NOICON;
	};
	InitTreeData(int iRt,CString str,int id, ITEMTYPE itype=NOICON,int icon=-1)
	{
		iRoot=iRt;
		sItemText=str;
		iIndex=id;
		iIcon=icon;
		iType=itype;
	};
};

class CMyTreeCtrl:public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyTreeCtrl)
public:
	CMyTreeCtrl();
	virtual ~CMyTreeCtrl();

	//�ػ�
	CFont m_Font;
	HTREEITEM m_CurMouseItem;                        //��ǰ����ƶ����Ľڵ���
	CRect m_ClientRect;                              //���ؼ��ͻ��˴�С
	CImageList* m_pIconList;                         //���ICON
	CImageList* GetIconList(CImageList* pIconList);  //�õ�Icon
	HTREEITEM InsertItemEx(CString strText,HTREEITEM lparent=TVI_ROOT,int index=-1,
		ITEMTYPE=NOICON,int nIconIndex=-1, HTREEITEM lpFont = TVI_LAST);  
	void DrawBackGround(CDC* pDC);                   //���Ʊ���
	int GetItemIndent(HTREEITEM hItem);
	void DrawExpandButton(CDC * pDC,HTREEITEM hItem,CRect &Rect);
	BOOL IsDrawExpandButton(HTREEITEM hItem);
	void DrawCheckBox(CDC * pDC,HTREEITEM hItem,CRect &Rect);
	void DrawItemText(CDC * pDC,HTREEITEM hItem,CRect &Rect);//����ÿһ����ı�
	void	DrawItemLines(CDC * pDC,HTREEITEM hItem);
	BOOL IsDrawItemIcon(HTREEITEM hItem,int iPos);
	void	DrawItemIcon(CDC * pDC,HTREEITEM hItem,int iPos,CRect &Rect);
	void DrawItem(CDC* pDC);                         //�������ؼ��е�ÿһ��
	void DrawItemFocus(CDC * pDC,HTREEITEM hItem, CRect Rect);
	int GetItemPosRect(HTREEITEM hItem,int iPos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnClickFirstIcon(){};
	virtual void OnClickSecondIcon(){};
private:
	int m_nMargin;
	int m_nHSpacer;
	float m_fBoxSize;
	int m_nSmallIconWidth;
	LONG m_nStyle;
	int m_nIndent;
	

	struct ITEMDATA
	{
		CString sItemText;		//��ʾ�ַ�
		int iIndex;					//Id Item
		int iIcons[3];				//����ǰͼ��,���ֺ�ͼ��1�����ֺ�ͼ��2
		BOOL bCheck;
		ITEMDATA()
		{
			sItemText.Empty();
			iIndex=-1;
			iIcons[0]=-1;//Ĭ��û��ͼ��
			iIcons[1]=12;//button1.bmp��λ��
			iIcons[2]=13;//button1.bmp��λ��
			bCheck=TRUE;
		};
	};
	map<HTREEITEM,ITEMDATA*> m_mapItemData;          //ĳһ��ľ��<--->ĳһ���Ӧ���ı���Icon
	map<HTREEITEM,ITEMDATA*>::iterator m_iter;       //��Ӧ���͵ĵ�����
	HTREEITEM m_CurClickItem;
	BOOL m_bClickIcon1;
	BOOL m_bClickIcon2;
protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetItemCheck(HTREEITEM item);//�ػ�ʱʹ��
	void SetItemCheck(HTREEITEM item, BOOL bCheck);//�ػ�ʱʹ��
	void SetChildCheck(HTREEITEM item, BOOL bCheck);
	void SetParentCheck(HTREEITEM item, BOOL bCheck);
	void TravelItem(HTREEITEM hitem);
	void SetChildExpand(HTREEITEM item, int iExpand=TVE_EXPAND);
	void SetAllItemCheck(BOOL bCheck=TRUE);
	void SetAllItemExpand(int iExpand=TVE_EXPAND);
	int GetItemCheckType(HTREEITEM item);//0 False 1 True 2 part True 
	int GetItemIndex(HTREEITEM item);
	int GetClickedItem(BOOL &bFstIcon,BOOL &bSecIcon);
	void GetItemIconRect(CRect &rc,int iPos);
	BOOL InitTree(struct InitTreeData[],int iNum,DWORD dStyle=0);
	vector<struct TreeData> GetTreeCheck();
	void SetTreeCheck(vector<struct TreeData> treedata);
private:
	vector<struct TreeData> m_vTreeData;
};
