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
		CString OrderStr = static_cast<LPCTSTR>(reinterpret_cast<LPCWSTR>(lParam));
		MessageBox(OrderStr);

		//ToDo::
		break;
	}
	return 0;

}

