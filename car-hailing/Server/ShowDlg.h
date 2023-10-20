#pragma once


// ShowDlg 对话框

class ShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShowDlg)

public:
	int count = 0;
	ShowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShowDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton2();
	// 阻塞的司机的数量
	CString Driver_sum;
	afx_msg void OnEnChangeEdit3();
	// 显示缓冲区的资源数量
	CString BufferSum;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	// 显示现在阻塞了多少名乘客
	CString Order_sum;
};
