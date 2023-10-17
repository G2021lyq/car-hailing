// CCarServiceDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CCarServiceDlg.h"

#include "MainFrm.h"
#include "Driver.h"
#include "Order.h"
#include "resource.h"
// CCarServiceDlg

ClientAsk myclient;//定义这个结构体对象出来

IMPLEMENT_DYNCREATE(CCarServiceDlg, CFormView)

CCarServiceDlg::CCarServiceDlg()
	: CFormView(IDD_DIALOG_CarService)
	, m_valstartposx(_T(""))
	, m_valstartposy(_T(""))
	, m_valendposx(_T(""))
	, m_valendposy(_T(""))
{

}

CCarServiceDlg::~CCarServiceDlg()
{
}

void CCarServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARTYPE1, m_cartype1);
	DDX_Control(pDX, IDC_CARTYPE2, m_cartype2);
	DDX_Control(pDX, IDC_CARTYPE3, m_cartype3);
	DDX_Control(pDX, IDC_STARTNOW, m_startnow);
	DDX_Control(pDX, IDC_START10MIN, m_start10min);
	DDX_Control(pDX, IDC_START20MIN, m_start20min);
	DDX_Control(pDX, IDC_STARTPOSX, m_startposx);
	DDX_Control(pDX, IDC_STARTPOSY, m_startposy);
	DDX_Control(pDX, IDC_ENDPOSX, m_endposx);
	DDX_Control(pDX, IDC_ENDPOSY, m_endposy);
	DDX_Text(pDX, IDC_STARTPOSX, m_valstartposx);
	DDX_Text(pDX, IDC_STARTPOSY, m_valstartposy);
	DDX_Text(pDX, IDC_ENDPOSX, m_valendposx);
	DDX_Text(pDX, IDC_ENDPOSY, m_valendposy);
	DDX_Control(pDX, IDC_STARTMATCH, m_startmatch);
}

BEGIN_MESSAGE_MAP(CCarServiceDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CCarServiceDlg::OnBnClickedButton2)

	ON_BN_CLICKED(IDC_CARTYPE1, &CCarServiceDlg::OnBnClickedCartype1)
	ON_BN_CLICKED(IDC_CARTYPE2, &CCarServiceDlg::OnBnClickedCartype2)
	ON_BN_CLICKED(IDC_CARTYPE3, &CCarServiceDlg::OnBnClickedCartype3)
	ON_BN_CLICKED(IDC_STARTNOW, &CCarServiceDlg::OnBnClickedStartnow)
	ON_BN_CLICKED(IDC_START10MIN, &CCarServiceDlg::OnBnClickedStart10min)
	ON_BN_CLICKED(IDC_START20MIN, &CCarServiceDlg::OnBnClickedStart20min)
	ON_EN_CHANGE(IDC_STARTPOSX, &CCarServiceDlg::OnEnChangeStartposx)
	ON_EN_CHANGE(IDC_STARTPOSY, &CCarServiceDlg::OnEnChangeStartposy)
	ON_EN_CHANGE(IDC_ENDPOSX, &CCarServiceDlg::OnEnChangeEndposx)
	ON_EN_CHANGE(IDC_ENDPOSY, &CCarServiceDlg::OnEnChangeEndposy)
	ON_BN_CLICKED(IDC_STARTMATCH, &CCarServiceDlg::OnBnClickedStartmatch)
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


void CCarServiceDlg::OnBnClickedCartype1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cartype1.SetCheck(TRUE);
	m_cartype2.SetCheck(FALSE);
	m_cartype3.SetCheck(FALSE);
	//结构体赋值
	myclient.CarType = _T("1");
}


void CCarServiceDlg::OnBnClickedCartype2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cartype1.SetCheck(FALSE);
	m_cartype2.SetCheck(TRUE);
	m_cartype3.SetCheck(FALSE);

	myclient.CarType = _T("2");
}


void CCarServiceDlg::OnBnClickedCartype3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cartype1.SetCheck(FALSE);
	m_cartype2.SetCheck(FALSE);
	m_cartype3.SetCheck(TRUE);

	myclient.CarType = _T("3");
}


void CCarServiceDlg::OnBnClickedStartnow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_startnow.SetCheck(TRUE);
	m_start10min.SetCheck(FALSE);
	m_start20min.SetCheck(FALSE);

	myclient.TimerType = _T("0");
}


void CCarServiceDlg::OnBnClickedStart10min()
{
	// TODO: 在此添加控件通知处理程序代码
	m_startnow.SetCheck(FALSE);
	m_start10min.SetCheck(TRUE);
	m_start20min.SetCheck(FALSE);

	myclient.TimerType = _T("10");
}


void CCarServiceDlg::OnBnClickedStart20min()
{
	// TODO: 在此添加控件通知处理程序代码
	m_startnow.SetCheck(FALSE);
	m_start10min.SetCheck(FALSE);
	m_start20min.SetCheck(TRUE);

	myclient.TimerType = _T("20");
}


void CCarServiceDlg::OnEnChangeStartposx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//wchar_t edt[256];
	//m_startposx.GetWindowTextW(edt, 256);

	//myclient.StartX = m_startposx;
	UpdateData(TRUE);
	myclient.StartX = m_valstartposx;
}


void CCarServiceDlg::OnEnChangeStartposy()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	myclient.StartY = m_valstartposy;
}


void CCarServiceDlg::OnEnChangeEndposx()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	myclient.EndX = m_valendposx;
}


void CCarServiceDlg::OnEnChangeEndposy()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	myclient.EndY = m_valendposy;
}


void CCarServiceDlg::OnBnClickedStartmatch()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//点击开始匹配，将相关信息上传服务器
	//先把相关信息弹出消息框提示再说


	/*str.Format(_T("Driver ID: %d, Car Model: %d, Current Position: (%d, %d), Pick Up Area: (%d, %d) - (%d, %d)"),
		id, carModel, currentPositionX, currentPositionY,
		pickUpAreaLeftTopX, pickUpAreaLeftTopY, pickUpAreaRightBottomX, pickUpAreaRightBottomY);*/

	/*CString str = (_T("出发点坐标：（%s,%s）终点坐标：（%s,%s）车的种类：%s 发车时间：%s"), myclient.StartX, myclient.StartY, myclient.EndX, myclient.EndY, myclient.CarType, myclient.TimerType);
	AfxMessageBox(str);*/
}
