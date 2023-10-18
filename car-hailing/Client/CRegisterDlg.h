#pragma once


// CRegisterDlg 对话框

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 注册使用的邮箱
	CString m_Email;
	// 注册使用的密码
	CString m_Password;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// //邮箱验证码的文字
	CButton EmailStaticCode;

	//
	CString Code;

	// 邮箱验证码
	CString EmailCode;
};
