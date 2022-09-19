#if !defined(AFX_CHECKCOMBOBOX_H__66750D93_95DB_11D3_9325_444553540000__INCLUDED_My)
#define AFX_CHECKCOMBOBOX_H__66750D93_95DB_11D3_9325_444553540000__INCLUDED_My

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef _WIN64
#define MY_GWL_ID GWL_ID
#define MY_GWL_WNDPROC GWL_WNDPROC 
#define MY_GetWindowLong GetWindowLong 
#define MY_SetWindowLong SetWindowLong 
#define MY_LONG LONG
#else
#define MY_GWL_ID GWLP_ID
#define MY_GWL_WNDPROC GWLP_WNDPROC 
#define MY_GetWindowLong GetWindowLongPtr 
#define MY_SetWindowLong SetWindowLongPtr 
#define MY_LONG LONG_PTR
#endif


class CMyCheckComboBox : public CComboBox
{
public:
	CMyCheckComboBox();
	virtual ~CMyCheckComboBox();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// Selects all/unselects the specified item
	INT SetCheck(INT nIndex, BOOL bFlag);

	// Returns checked state
	BOOL GetCheck(INT nIndex);

	// Selects all/unselects all
	void SelectAll(BOOL bCheck = TRUE);
	void ReverseSelect(void);

	int m_iSelectAll,m_iReverseSelect,m_iClearAll; //全选及取消功能所在的序号

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCheckComboBox)
	protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMyCheckComboBox)
	afx_msg LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropDown();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	// Routine to update the text
	void RecalcText();

	// The subclassed COMBOLBOX window (notice the 'L')
	HWND m_hListBox;

	// The string containing the text to display
	CString m_strText;
	BOOL m_bTextUpdated;

	// A flag used in MeasureItem, see comments there
	BOOL m_bItemHeightSet;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKCOMBOBOX_H__66750D93_95DB_11D3_9325_444553540000__INCLUDED_)
