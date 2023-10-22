// CHistoryDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CHistoryDlg.h"
#include "MainFrm.h"
#include "Order.h"
#include "Driver.h"
#include "Account.h"

// CHistoryDlg

IMPLEMENT_DYNCREATE(CHistoryDlg, CFormView)

CHistoryDlg::CHistoryDlg()
	: CFormView(IDD_DIALOG_History)
	, m_page(0)

{

}

CHistoryDlg::~CHistoryDlg()
{
}

void CHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_page);
	DDX_Control(pDX, IDC_EDIT1, m_ShowEdit);
}

BEGIN_MESSAGE_MAP(CHistoryDlg, CFormView)
	ON_MESSAGE(NM_Page, OnMyChange)
	ON_BN_CLICKED(IDC_BUTTON1, &CHistoryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHistoryDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHistoryDlg 诊断

#ifdef _DEBUG
void CHistoryDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHistoryDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHistoryDlg 消息处理程序



void CHistoryDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	Send_message();
	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON2);
	pButton->EnableWindow(FALSE);

}

LRESULT CHistoryDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_Page:
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CStringW receivedString = static_cast<LPCTSTR>(reinterpret_cast<LPCWSTR>(lParam));
		Order m_Order;
		m_Order = receivedString;
		Account& m_Account = pMainFrame->m_Account;
		Driver driver;
		driver = m_Order.GetDriver();
		CString carmode(L"123");

		if (driver.getCarModel() == 0) carmode.Format(L"豪华车");
		else if (driver.getCarModel() == 1) carmode.Format(L"普通轿车");
		else  carmode.Format(L"高级三轮");

		CString ans;
		ans.Format(L"账号名:%s\r\n邮箱:%s\r\n第%d次使用网约车服务\r\n路程:%.2lf\r\n花费:%.2lf\r\n车型:%s\r\n",
			m_Account.getUsername().GetString(), m_Account.getEmail().GetString()
			, m_page + 1, m_Order.GetDistance(), m_Order.GetBillAmount()
			, carmode);

		m_ShowEdit.SetWindowText(ans);
		//m_Order.ToCString().GetString()
		UpdateData(FALSE);
		break;
	}
	}
	return 0;
}


void CHistoryDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_page++;
	if (m_page == 1)
	{
		CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON2);
		pButton->EnableWindow(TRUE);
	}
	Send_message();
}


void CHistoryDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_page--;
	if (m_page == 0) {
		CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON2);
		pButton->EnableWindow(FALSE);
	}
	Send_message();
}

void CHistoryDlg::Send_message()
{
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame) {
		//主窗口，存放了Socket。
		MySocket& p_mySocket = pMainFrame->m_socket;
		//定义发送字符串
		wchar_t pkt[2048];
		pkt[0] = 0x18;//默认pkt[0]为协议信息，定义为：测试SOCKET的协议
		//定义主体信息
		wsprintf(pkt + 1, L"%d", m_page);
		//发送信息包含两部分，字符串和总空间，注意不能用wcslen代替
		if (p_mySocket.Send(pkt, 2048) == SOCKET_ERROR) {
			//每此写Send都要进行错误检测
			MessageBox(TEXT("发送测试SOCKET信息失败了"));
		}
	}
}
