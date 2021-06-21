
// ReadSSGDlg.h : ͷ�ļ�
//

#pragma once


// CReadSSGDlg �Ի���
class CReadSSGDlg : public CDialogEx
{
// ����
public:
	CReadSSGDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ReadSSG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// �������
	int m_iCaseNum;
	// �Ƕȼ��
	int m_fAngleGap;
	// �Ƕ��ַ���
	CString m_sAngle;
	void SplitStr(CString strSrc, CString strGap, CStringArray &strResult);
	afx_msg void OnEnKillfocusEditNum();
	CEdit m_cEditMsg;
	// �Ƿ�򿪽���ļ�
	BOOL m_bOpenTxt;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonDispratio();
	float m_fError;
};
