// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Login, pParent)
	, m_username(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_Ip);
	DDX_Text(pDX, IDC_EDIT1, m_username);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CLoginDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT2, &CLoginDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON5, &CLoginDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	type = 0;//设置窗口类型为0
	UpdateData(TRUE);
	m_Ip.GetWindowText(m_ipAddr, 16);

	OnOK();//关闭对话框
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	type = 0;   //设置登录窗口序号为0
	OnOK();
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	type = 1;  //设置注册窗口序号为1
	OnOK();//关闭对话框
}


void CLoginDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	type = 2; // 设置为找回密码
	OnOK();
}


void CLoginDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CLoginDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_Ip.GetWindowText(m_ipAddr, 16);
	CIPAddressCtrl* pIPAddressCtrl = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	pIPAddressCtrl->EnableWindow(FALSE);

	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
	pButton->EnableWindow(TRUE);

	CButton* pButton2 = (CButton*)GetDlgItem(IDC_BUTTON2);
	pButton2->EnableWindow(TRUE);

	CButton* pButton4 = (CButton*)GetDlgItem(IDC_BUTTON4);
	pButton4->EnableWindow(TRUE);

	CButton* pButton5 = (CButton*)GetDlgItem(IDC_BUTTON5);
	pButton5->EnableWindow(FALSE);

}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CIPAddressCtrl* pIPAddressCtrl = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	pIPAddressCtrl->SetAddress(127, 0, 0, 1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
