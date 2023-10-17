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


	// 找到司机成功，向主窗口，发送NM_OK消息，参数如下

	//生成driver类
	int count = 0;
	Driver driver(count);

	//生成一个Order类
	double point_1[2] = { 3.0,4.0 };
	double point_2[2] = { 20.0,9.0 };
	Order aOrder(driver.ToString(), L"passenger", point_1, point_2);

	CString myString = aOrder.ToCString();
	MessageBox(myString);

	LPARAM lParam = reinterpret_cast<LPARAM>(static_cast<LPCTSTR>(myString));
	::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_OK, (WPARAM)NM_OK, lParam);

	//CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	//pMainFrame->PostMessage(NM_OK, (WPARAM)NM_OK, reinterpret_cast<LPARAM>(myWCharString));

	// TODO: 在此添加控件通知处理程序代码
}

LRESULT CCarServiceDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{


	}
	return 0;

}
