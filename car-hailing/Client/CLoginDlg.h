#pragma once
#include "afxdialogex.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"

#include "MySocket.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// ip地址输入
	CIPAddressCtrl m_Ip;
	//将IP地址存储为char[16]的形式
	wchar_t m_ipAddr[16];
	// 用户名输入

	MySocket m_socket;
	CString m_username;
	afx_msg void OnBnClickedButton3();
};
