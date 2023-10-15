// CRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CRegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Register, pParent)
	, m_Email(_T(""))
	, m_Password(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Email);
	DDX_Text(pDX, IDC_EDIT3, m_Password);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &CRegisterDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegisterDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


void CRegisterDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRegisterDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
