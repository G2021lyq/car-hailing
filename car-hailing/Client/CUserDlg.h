#pragma once

#define NM_TEST_SOCKET (WM_USER+2025)

// CUserDlg 窗体视图

class CUserDlg : public CFormView
{
	DECLARE_DYNCREATE(CUserDlg)

protected:
	CUserDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_User };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 展示Server返回的反馈信息
	CEdit m_ShowMessage;
	afx_msg void OnBnClickedButton2();
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();




//
public:
	CString m_strUsername;// 用户名
	CString m_strPassword;// 密码
	int m_nSelectedAvatar;// 选中的头像编号
	CString m_strIntroduction;// 个人简介
};


