// CCarContinueDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CCarContinueDlg.h"


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
