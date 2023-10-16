// CCarContinueDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CCarContinueDlg.h"

#include "MainFrm.h"
#include "Driver.h"
#include "Order.h"

// CCarContinueDlg

IMPLEMENT_DYNCREATE(CCarContinueDlg, CFormView)

CCarContinueDlg::CCarContinueDlg()
	: CFormView(IDD_DIALOG_CarContinue)
{

}

CCarContinueDlg::~CCarContinueDlg()
{
}

void CCarContinueDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCarContinueDlg, CFormView)

	ON_MESSAGE(NM_START_SERVICE, OnMyChange)
END_MESSAGE_MAP()


// CCarContinueDlg 诊断

#ifdef _DEBUG
void CCarContinueDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCarContinueDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCarContinueDlg 消息处理程序
LRESULT CCarContinueDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
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

		//TODO::

		break;
	}
	return 0;

}

