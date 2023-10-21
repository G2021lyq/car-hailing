// CRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CRegisterDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Account.h"
// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Register, pParent)
	, m_Email(_T(""))
	, m_Password(_T(""))
	, EmailCode(_T(""))
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
	DDX_Control(pDX, IDC_BUTTON2, EmailStaticCode);
	DDX_Text(pDX, IDC_EDIT2, EmailCode);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &CRegisterDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegisterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRegisterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRegisterDlg::OnBnClickedButton4)
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
	UpdateData(TRUE);
	OnOK();
}


void CRegisterDlg::OnBnClickedButton3()
{
	OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void CRegisterDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	if (m_Email.IsEmpty()) {
		MessageBox(L"请填写邮箱");
		return;
	}
	Account a;
	if (a.IsEmailValid(m_Email) == false)
	{
		MessageBox(L"邮箱不合法，请填写正确的邮箱");
		return;
	}
	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON4);
	pButton->EnableWindow(FALSE);
	CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_STATIC_Code);
	// 使静态文本可视
	pStaticText->ShowWindow(SW_SHOW);
	// TODO: 在此添加控件通知处理程序代码
	EmailStaticCode.ShowWindow(SW_SHOW);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	pEdit->ShowWindow(SW_SHOW);

	//和子进程进行管道通信

	//发送邮箱给它，发送

	//获取到一个四位随机数，获取
	srand(static_cast<unsigned>(time(nullptr)));
	int randomNumber = rand() % 9000 + 1000;

	//将这个随机数存储给Code
	Code.Format(L"%d", randomNumber);
	//弹出窗口，通知用户
	CString myCString;
	myCString.Format(_T("尊敬的用户，你的邮箱验证码是:%d"), randomNumber);
	MessageBox(myCString);
}
