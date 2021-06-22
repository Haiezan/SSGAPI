#pragma once


// CDlgReadDispRatio 对话框

class CDlgReadDispRatio : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReadDispRatio)

public:
	CDlgReadDispRatio(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgReadDispRatio();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DISPRATIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDispratio();

	CString m_sMsg;
	void AppendMsg(CString sMsg);
	void ClearMsg();

	// 工况编号
	int m_iCaseNum;

	CEdit m_cEditMsg;
	// 是否打开结果文件
	BOOL m_bOpenTxt;

	float m_fError; //剔除误差
	float m_fAngle; //计算角度
};
