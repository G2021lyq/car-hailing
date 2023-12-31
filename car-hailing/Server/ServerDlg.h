﻿
// ServerDlg.h: 头文件
//

#pragma once

#include "Driver.h"
#include "MySocket.h"
#include "MyFile.h"
#include "ShowDlg.h"
#include <vector>

#define NM_ADD_Driver (WM_USER + 4000)
#define NM_ADD_Order (WM_USER + 4001)

#define NM_DiverSum (WM_USER + 4002)
#define NM_BufferSum (WM_USER + 4003)
#define NM_OrderSum (WM_USER + 4004)

// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
	// 构造
public:
	CServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	ShowDlg* mydlg;
	HICON m_hIcon;

	CBitmap m_bmBg;//背景的图
	CBrush m_brBg;//背景的画刷

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void CreatDriver();
	int count = 0;
	// 创建存储司机对象的向量
	std::vector<Driver> drivers;

	afx_msg void OnLvnItemchangedUserlist(NMHDR* pNMHDR, LRESULT* pResult);
	// //记录所有成功登录的用户
	CListCtrl m_list;
	// 展示一系列的信息
	CString m_showMsg;
	// 开始按钮控件
	CBitmapButton m_startBtn;

	CCriticalSection m_csList;
	//文件类
	MyFile m_file;
	MySocket m_socket;
	//自定义SOCKET的消息解析方法
	afx_msg LRESULT OnSocket(WPARAM wParam, LPARAM lParam);

	//三个自定义的方法
	void ParserPkt(MySocket* from);
	//向聊天室追加动态信息
	void Append(wchar_t* msg);
	void ClosePlayer(MySocket* from);

	afx_msg void OnBnClickedButtonStart();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
