// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CUserDlg.h"

#include "MySocket.h"
#include "MainFrm.h"
// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(IDD_DIALOG_User)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_ShowMessage);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)

	ON_MESSAGE(NM_TEST_SOCKET, OnMyChange)
	ON_EN_CHANGE(IDC_EDIT2, &CUserDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取主窗口（CMainFrame）
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame) {
		//主窗口，存放了Socket。

		MySocket& p_mySocket = pMainFrame->m_socket;
		//定义发送字符串
		wchar_t pkt[2048];
		pkt[0] = 0x10;//默认pkt[0]为协议信息，定义为：测试SOCKET的协议
		//定义主体信息
		wsprintf(pkt + 1, L"我要过来了");

		MessageBox(pkt + 1);
		//发送信息包含两部分，字符串和总空间，注意不能用wcslen代替
		if (p_mySocket.Send(pkt, 2048) == SOCKET_ERROR) {
			//每此写Send都要进行错误检测
			MessageBox(TEXT("发送测试SOCKET信息失败了"));
		}
	}
}

LRESULT CUserDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_TEST_SOCKET:
		// 获取到参数
		wchar_t* myString = reinterpret_cast<wchar_t*>(lParam);
		//MessageBox(myString);
		m_ShowMessage.SetWindowText(myString); // 在CUserDlg内操作test_edit
		break;
	}
	return 0;
}


void CUserDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
