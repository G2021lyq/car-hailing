#pragma once



// CHistoryDlg 窗体视图

class CHistoryDlg : public CFormView
{
	DECLARE_DYNCREATE(CHistoryDlg)

protected:
	CHistoryDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CHistoryDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_History };
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
	// 页数
	int m_page;
	virtual void OnInitialUpdate();
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	// 展示信息
	CEdit m_ShowEdit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void Send_message();
};


