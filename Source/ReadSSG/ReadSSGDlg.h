
// ReadSSGDlg.h : 头文件
//

#pragma once


// CReadSSGDlg 对话框
class CReadSSGDlg : public CDialogEx
{
// 构造
public:
	CReadSSGDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ReadSSG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonReadSSG();
	afx_msg void OnBnClickedButtonHelp();
	CString m_sMsg;
	void AppendMsg(CString sMsg);
	void ClearMsg();

	
	afx_msg void OnBnClickedButtonDisp();
	afx_msg void OnBnClickedButtonHarmDisp();
	// 工况编号
	int m_iCaseNum;
	// 角度间隔
	int m_fAngleGap;
	// 角度字符串
	CString m_sAngle;
	void SplitStr(CString strSrc, CString strGap, CStringArray &strResult);
	afx_msg void OnEnKillfocusEditNum();
	CEdit m_cEditMsg;
	// 是否打开结果文件
	BOOL m_bOpenTxt;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonDispratio();
	float m_fError;
};
