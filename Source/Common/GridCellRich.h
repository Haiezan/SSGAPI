// GridCellRich.h: interface for the CGridCellRich class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLRICH_H__51FDCB6F_A7D4_4213_BF6A_3987CB29214A__INCLUDED_)
#define AFX_GRIDCELLRICH_H__51FDCB6F_A7D4_4213_BF6A_3987CB29214A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGridCtrl;
#include "..\GRIDCTRL_SRC\GridCell.h"

#define IDC_RICHEDIT_TEMP	30


class CGridCellRich : public CGridCell
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellRich)
public:
	CGridCellRich();
	virtual ~CGridCellRich();
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect,  BOOL bEraseBkgnd =TRUE);
    virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
	void SetBold ();
	void SetItalic ();
	void SetUnderline ();
	void CGridCellRich::SetRichText(CStringA txt);
	void SetRich(CWnd *pParent);
protected:
	CRichEditCtrl* m_pRichEditTemp;
	CWnd* m_pParent;
};

#endif // !defined(AFX_GRIDCELLRICH_H__51FDCB6F_A7D4_4213_BF6A_3987CB29214A__INCLUDED_)
