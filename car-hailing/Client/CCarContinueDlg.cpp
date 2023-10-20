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
	//m_pen.CreatePen(PS_SOLID, 4, RGB(244, 244, 244));
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
	//	ON_WM_PAINT()
	ON_WM_TIMER()
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
		Order m_Order;
		m_Order = OrderStr;
		Driver m_Driver;
		m_Driver = m_Order.GetDriver();
		//测试数据
		start[0] = m_Order.getStart()[0];
		start[1] = m_Order.getStart()[1];
		m_end[0] = m_Order.getEnd()[0];
		m_end[1] = m_Order.getEnd()[1];
		driver[0] = m_Driver.getCurrentPositionX();
		driver[1] = m_Driver.getCurrentPositionY();


		CRect rect;
		(this->GetDlgItem(IDC_STATIC))->GetWindowRect(&rect);  // 获取控件相对于屏幕的位置
		ScreenToClient(rect); // 转化为相对于客户区的位置
		GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, 560, 420, false);

		CDC* pClientDC = GetDC();
		(this->GetDlgItem(IDC_STATIC))->GetWindowRect(&rect);  // 获取控件相对于屏幕的位置
		ScreenToClient(rect); // 转化为相对于客户区的位置

		CBitmap carbmp, mapbmp, userbmp;
		carbmp.LoadBitmapW(IDB_CAR);
		mapbmp.LoadBitmapW(IDB_BG);
		userbmp.LoadBitmapW(IDB_USER);
		m_brush[0].CreatePatternBrush(&mapbmp);
		m_brush[1].CreatePatternBrush(&carbmp);
		m_brush[2].CreatePatternBrush(&userbmp);

		CDC* pdc = GetDlgItem(IDC_STATIC)->GetWindowDC();
		CBrush* pOldBrs = pdc->SelectObject(&m_brush[0]);
		//黑边不知道如何去除，要么出现白边
		//CPen* pOldPen = pdc->SelectObject(&m_pen);
		//画出地图 i为行
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 20; j++) {
				m_map[i][j].left = 0 + j * 28;
				m_map[i][j].right = 28 + j * 28;
				m_map[i][j].top = 0 + i * 28;
				m_map[i][j].bottom = 28 + i * 28;
				pdc->SelectObject(&m_brush[0]);
				pdc->Rectangle(m_map[i][j]);
			}
		}
		if (!m_ispicked) {
			//也可以加一个 目的地的图
			pdc->SelectObject(&m_brush[2]);
			pdc->Rectangle(m_map[start[0] - 1][start[1] - 1]);
			pdc->SelectObject(&m_brush[1]);
			pdc->Rectangle(m_map[driver[0] - 1][driver[1] - 1]);
		}
		pdc->SelectObject(&pOldBrs);
		SetTimer(1, driverspeed, NULL);

		break;
	}
	return 0;

}



//void CCarContinueDlg::OnPaint()
//{
//	// CPaintDC dc(this); // device context for painting
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CFormView::OnPaint()
//
//
//	CPaintDC pDC(this);
//	SetTimer(1, 1000, NULL);
//}


void CCarContinueDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UpdateData(true);
	CDC* pdc = GetDlgItem(IDC_STATIC)->GetWindowDC();
	CBrush* pOdBrs = pdc->SelectObject(&m_brush[0]);
	// cpen可以把边描成白色，但是部分线看不清楚
	//CPen* pOldPen = pdc->SelectObject(&m_pen);
	if (!m_ispicked)
	{
		pdc->Rectangle(m_map[driver[0] - 1][driver[1] - 1]);
		pdc->SelectObject(pOdBrs);
		if (start[0] < driver[0]) driver[0] -= 1;
		else if (start[0] > driver[0]) driver[0] += 1;
		else {
			if (start[1] < driver[1]) driver[1] -= 1;
			else driver[1] += 1;
		}
		CBrush* p1dBrs = pdc->SelectObject(&m_brush[1]);
		pdc->SelectObject(&m_brush[1]);
		pdc->Rectangle(m_map[driver[0] - 1][driver[1] - 1]);
		pdc->DeleteDC();
		if (start[0] == driver[0] && start[1] == driver[1])
			m_ispicked = true;
	}
	else {

		pdc->Rectangle(m_map[start[0] - 1][start[1] - 1]);
		pdc->SelectObject(pOdBrs);

		if (m_end[0] < start[0]) start[0] -= 1;
		else if (m_end[0] > start[0]) start[0] += 1;
		else {
			if (m_end[1] < start[1]) start[1] -= 1;
			else start[1] += 1;
		}
		CBrush* p1dBrs = pdc->SelectObject(&m_brush[1]);
		pdc->SelectObject(&m_brush[1]);
		pdc->Rectangle(m_map[start[0] - 1][start[1] - 1]);
		pdc->DeleteDC();
	}
	if (start[1] == m_end[1] && start[0] == m_end[0])
		KillTimer(1);
	//可以加 结束行程flag

	CFormView::OnTimer(nIDEvent);
}
