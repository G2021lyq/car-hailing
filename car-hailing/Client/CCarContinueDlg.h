#pragma once

#include "Order.h"

//自定义的消息
#define NM_START_SERVICE (WM_USER+2026)
#define NM_D (WM_USER+2027)

////////////////////////////////////
// CCarContinueDlg 窗体视图

class CCarContinueDlg : public CFormView
{
	DECLARE_DYNCREATE(CCarContinueDlg)

protected:
	CCarContinueDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CCarContinueDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CarContinue };
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
	Order m_Order;
	//自定义消息处理函数
	//图片刷
	CBrush m_brush[3];
	//地图大小
	CRect m_map[20][15];
	///CPen m_pen;
	int driver[2];
	int start[2];
	int m_end[2];
	//是否接到客
	BOOL m_ispicked = false;
	int driverspeed = 1000; //ms
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
};


