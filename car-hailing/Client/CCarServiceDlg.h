#pragma once

#define NM_START_ORDER (WM_USER+2029)

// CCarServiceDlg 窗体视图

class CCarServiceDlg : public CFormView
{
	DECLARE_DYNCREATE(CCarServiceDlg)

protected:
	CCarServiceDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CCarServiceDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CarService };
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
	afx_msg void OnBnClickedButton2();
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	//时间总数
	int TimerSum;
	//订单字符串
	CString m_OrderStr;

	CButton m_cartype1;
	CButton m_cartype2;
	CButton m_cartype3;
	CButton m_startnow;
	CButton m_start10min;
	CButton m_start20min;
	afx_msg void OnBnClickedCartype1();
	afx_msg void OnBnClickedCartype2();
	afx_msg void OnBnClickedCartype3();
	afx_msg void OnBnClickedStartnow();
	afx_msg void OnBnClickedStart10min();
	afx_msg void OnBnClickedStart20min();
	CEdit m_startposx;
	CEdit m_startposy;
	CEdit m_endposx;
	CEdit m_endposy;
	afx_msg void OnEnChangeStartposx();
	CString m_valstartposx;
	CString m_valstartposy;
	CString m_valendposx;
	CString m_valendposy;
	afx_msg void OnEnChangeStartposy();
	afx_msg void OnEnChangeEndposx();
	afx_msg void OnEnChangeEndposy();
	CButton m_startmatch;
	afx_msg void OnBnClickedStartmatch();
	CProgressCtrl m_progressbar;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_showtime;
	// 展示框的内含物
	CString m_valmessage = L"";
};

//写一个结构体用来传递信息
struct ClientAsk
{
	//首先给到坐标点
	CString StartX, StartY, EndX, EndY;
	//车型
	CString CarType;
	//出发时间
	CString TimerType;
};


