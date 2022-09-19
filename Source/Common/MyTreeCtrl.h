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
	int iRoot;					//节点等级
	CString sItemText;		//显示字符
	int iIndex;					//Id Item
	ITEMTYPE iType;		//图标类型
	int iIcon;						//文字前图标
	InitTreeData()
	{
		iRoot=0;
		sItemText.Empty();
		iIndex=-1;
		iIcon=-1;//默认没有图标
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

	//重绘
	CFont m_Font;
	HTREEITEM m_CurMouseItem;                        //当前鼠标移动到的节点句柄
	CRect m_ClientRect;                              //树控件客户端大小
	CImageList* m_pIconList;                         //存放ICON
	CImageList* GetIconList(CImageList* pIconList);  //得到Icon
	HTREEITEM InsertItemEx(CString strText,HTREEITEM lparent=TVI_ROOT,int index=-1,
		ITEMTYPE=NOICON,int nIconIndex=-1, HTREEITEM lpFont = TVI_LAST);  
	void DrawBackGround(CDC* pDC);                   //绘制背景
	int GetItemIndent(HTREEITEM hItem);
	void DrawExpandButton(CDC * pDC,HTREEITEM hItem,CRect &Rect);
	BOOL IsDrawExpandButton(HTREEITEM hItem);
	void DrawCheckBox(CDC * pDC,HTREEITEM hItem,CRect &Rect);
	void DrawItemText(CDC * pDC,HTREEITEM hItem,CRect &Rect);//绘制每一项的文本
	void	DrawItemLines(CDC * pDC,HTREEITEM hItem);
	BOOL IsDrawItemIcon(HTREEITEM hItem,int iPos);
	void	DrawItemIcon(CDC * pDC,HTREEITEM hItem,int iPos,CRect &Rect);
	void DrawItem(CDC* pDC);                         //绘制树控件中的每一项
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
		CString sItemText;		//显示字符
		int iIndex;					//Id Item
		int iIcons[3];				//文字前图标,文字后图标1，文字后图标2
		BOOL bCheck;
		ITEMDATA()
		{
			sItemText.Empty();
			iIndex=-1;
			iIcons[0]=-1;//默认没有图标
			iIcons[1]=12;//button1.bmp中位置
			iIcons[2]=13;//button1.bmp中位置
			bCheck=TRUE;
		};
	};
	map<HTREEITEM,ITEMDATA*> m_mapItemData;          //某一项的句柄<--->某一项对应的文本和Icon
	map<HTREEITEM,ITEMDATA*>::iterator m_iter;       //对应类型的迭代器
	HTREEITEM m_CurClickItem;
	BOOL m_bClickIcon1;
	BOOL m_bClickIcon2;
protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetItemCheck(HTREEITEM item);//重绘时使用
	void SetItemCheck(HTREEITEM item, BOOL bCheck);//重绘时使用
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
