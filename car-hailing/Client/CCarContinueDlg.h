#pragma once

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
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
};


