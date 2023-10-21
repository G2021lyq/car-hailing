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

	//和子进程进行管道通信

	DWORD len;
	wchar_t chBuf[2048];
	wsprintf(chBuf, m_Email);
	//发送邮箱给它，发送
	bool ret = WriteFile(handle_write, chBuf, 2048, &len, NULL);//子进程读了后，父进程才可以继续写入管道
	if (ret == false) {
		MessageBox(L"管道通信失败，请尝试重启程序");
		return;
	}
	//获取到一个四位随机数，获取
	ret = ReadFile(handle_read, chBuf, 2048, &len, NULL);
	if (wcscmp(m_Email, chBuf) == 0) {
		MessageBox(L"管道通信失败，请尝试重启程序");
		return;
	}
	//将这个随机数存储给Code
	Code.Format(L"%s", chBuf);
	//弹出窗口，通知用户
	CString myCString;
	myCString.Format(_T("尊敬的用户，你的邮箱验证码是:%s"), chBuf);
	MessageBox(myCString);


	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON4);
	pButton->EnableWindow(FALSE);
	CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_STATIC_Code);
	// 使静态文本可视
	pStaticText->ShowWindow(SW_SHOW);
	// TODO: 在此添加控件通知处理程序代码
	EmailStaticCode.ShowWindow(SW_SHOW);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	pEdit->ShowWindow(SW_SHOW);
	pButton = (CButton*)GetDlgItem(IDC_BUTTON2);
	pButton->EnableWindow(TRUE);
}


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON2);
	pButton->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



