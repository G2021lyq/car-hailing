// ShowDlg.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "ShowDlg.h"
#include "afxdialogex.h"

#include "ServerDlg.h"

// ShowDlg 对话框

IMPLEMENT_DYNAMIC(ShowDlg, CDialogEx)

ShowDlg::ShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_DIALOG, pParent)
	, Driver_sum(_T(""))
	, BufferSum(_T(""))
	, Order_sum(_T(""))
{

}

ShowDlg::~ShowDlg()
{
}

void ShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Driver_sum);
	DDX_Text(pDX, IDC_EDIT3, BufferSum);
	DDX_Text(pDX, IDC_EDIT1, Order_sum);
}


BEGIN_MESSAGE_MAP(ShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &ShowDlg::OnBnClickedButton2)

	ON_MESSAGE(NM_DiverSum, OnMyChange)
	ON_MESSAGE(NM_BufferSum, OnMyChange)
	ON_MESSAGE(NM_OrderSum, OnMyChange)
	ON_EN_CHANGE(IDC_EDIT3, &ShowDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON3, &ShowDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &ShowDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ShowDlg 消息处理程序


LRESULT ShowDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case (NM_DiverSum):
	{
		int sum = lParam;
		Driver_sum.Format(L"%d", sum);
		UpdateData(FALSE);
		break;
	}
	case (NM_BufferSum):
	{
		int sum = lParam;
		BufferSum.Format(L"%d", sum);
		UpdateData(FALSE);
		break;
	}
	case (NM_OrderSum):
	{
		int sum = lParam;
		Order_sum.Format(L"%d", sum);
		UpdateData(FALSE);
		break;
	}
	}
	return 0;
}

void ShowDlg::OnBnClickedButton2()
{

	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADD_Driver, (WPARAM)NM_ADD_Driver, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void ShowDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void ShowDlg::OnBnClickedButton3()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADD_Order, (WPARAM)NM_ADD_Order, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void ShowDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
