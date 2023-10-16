// CCarServiceDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CCarServiceDlg.h"

#include "MainFrm.h"
#include "Driver.h"
#include "Order.h"
// CCarServiceDlg

IMPLEMENT_DYNCREATE(CCarServiceDlg, CFormView)

CCarServiceDlg::CCarServiceDlg()
	: CFormView(IDD_DIALOG_CarService)
{

}

CCarServiceDlg::~CCarServiceDlg()
{
}

void CCarServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCarServiceDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CCarServiceDlg::OnBnClickedButton2)

	ON_MESSAGE(NM_START_SERVICE, OnMyChange)
END_MESSAGE_MAP()


// CCarServiceDlg 诊断

#ifdef _DEBUG
void CCarServiceDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCarServiceDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCarServiceDlg 消息处理程序


void CCarServiceDlg::OnBnClickedButton2()
{

	// 寻找到司机成功，向主窗口，发送NM_OK消息，参数如下
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_OK, (WPARAM)NM_OK, (LPARAM)0);

	// TODO: 在此添加控件通知处理程序代码
}

LRESULT CCarServiceDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_START_SERVICE:
		// 获取到参数,参数是一个字符串，表示订单
		wchar_t* getStr = reinterpret_cast<wchar_t*>(lParam);
		CString OrderStr(getStr); // 将wchar_t*转换为CString

		//将这个字符串赋值给订单实例
		int count = 0;
		Order m_order;
		m_order = OrderStr;

		MessageBox(OrderStr);
		break;
	}
	return 0;

}
