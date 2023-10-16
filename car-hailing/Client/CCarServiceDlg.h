#pragma once


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

};


