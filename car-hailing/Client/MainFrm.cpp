
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "MainFrm.h"
#include "CLoginDlg.h"
#include "CUserDlg.h"
#include "CCarServiceDlg.h"
#include "CCarContinueDlg.h"

#include "CSelectView.h"
#include "CDisplayView.h"
#include "CRegisterDlg.h"
#include "Account.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)

	ON_MESSAGE(NM_OK, OnMyChange)

	ON_MESSAGE(SOCKET_EVENT, OnSocket)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	CFormView* pNewView = nullptr; // 在外部定义变量

	Account a(L"1@qq.com", L"username", L"avatar", L"123", L"这个人很懒什么是都没写");

	CStringW receivedString;
	wchar_t Buff[2048];

	switch (wParam)
	{
	case(NM_A):
	{
		receivedString = a.ToCString();
		wsprintf(Buff, L"%s", receivedString);

		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg)
			, CSize(810, 720), &Context);
		pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

		pNewView->PostMessage(NM_START_ACCOUNT, (WPARAM)NM_START_ACCOUNT, reinterpret_cast<LPARAM>(Buff));
		break;
	}
	case(NM_B):

		Context.m_pNewViewClass = RUNTIME_CLASS(CCarServiceDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCarServiceDlg)
			, CSize(810, 720), &Context);
		pNewView = (CCarServiceDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

		pNewView->PostMessage(NM_START_ORDER, (WPARAM)NM_START_ORDER, 0);
		break;

	case(NM_OK):
		CStringW receivedString = static_cast<LPCTSTR>(reinterpret_cast<LPCWSTR>(lParam));
		wsprintf(Buff, L"%s", receivedString);

		Context.m_pNewViewClass = RUNTIME_CLASS(CCarContinueDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCarContinueDlg)
			, CSize(810, 720), &Context);
		pNewView = (CCarContinueDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

		pNewView->PostMessage(NM_START_SERVICE, (WPARAM)NM_START_SERVICE, reinterpret_cast<LPARAM>(Buff));
		break;
	}

	return 0;
}

LRESULT CMainFrame::OnSocket(WPARAM wParam, LPARAM lParam)
{
	MySocket* sock = (MySocket*)wParam;

	LVFINDINFO   info;
	LVITEM lvitem;

	switch (lParam)
	{
	case RETURN:
		ParserPkt(sock);
		break;
	case CLOSE:
		MessageBox(L"服务器已关闭!");
		break;
	}
	return LRESULT();
}
void CMainFrame::ParserPkt(MySocket* m_server) {
	wchar_t	pkt[2048];
	wchar_t GetBuff[2048];
	wmemset(pkt, 0, 2048);
	wmemset(GetBuff, 0, 2048);

	m_socket.Receive(pkt, 2048);
	//判断协议
	switch (pkt[0])
	{
	case 0x00://0x00是一个测试的信息
		//MessageBox(pkt + 1);
		break;
	case 0x10:
	{
		wsprintf(GetBuff, L"%s", pkt + 1);

		//发送一个自定义消息，从而告诉CUserDlg去执行相应的业务
		// 获取指向 CUserDlg 的指针
		CUserDlg* pUserDlg = dynamic_cast<CUserDlg*>(m_spliter.GetPane(0, 1));
		// 发送自定义消息给 CUserDlg
		pUserDlg->PostMessage(NM_TEST_SOCKET, (WPARAM)NM_TEST_SOCKET, reinterpret_cast<LPARAM>(GetBuff));
		break;
	}
	case 0x07:
	{
		wsprintf(GetBuff, L"%s", pkt + 1);
		if (wcscmp(GetBuff, L"yes") == 0) {
			MessageBox(L"注册成功！！！");
		}
		else {
			MessageBox(L"邮箱已经被注册！！！");
		}
	}
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	//TODO::

	//在创建主窗口前，先弹出登录窗口，必须登录成功，才能进入主窗口
	//先填写服务器地址，默认地址是127.0.0.1
tryagain:
	//创建登录窗口，并以阻塞方式创建
	CLoginDlg cLoginDlg;
	if (cLoginDlg.DoModal() != IDOK) {//没有按确认建
							   //退出程序
		PostQuitMessage(0);
		return TRUE;
	}
	if (cLoginDlg.type == 1) {//实现注册逻辑
	registragin:
		CRegisterDlg cRegisterDlg;
		int flag = cRegisterDlg.DoModal();
		if (flag != IDOK) {//没有按确认建
			if (flag == IDCANCEL)
				goto tryagain;
			PostQuitMessage(0);
			return TRUE;
		}
		//输入信息校验
		if (!(cRegisterDlg.Code == cRegisterDlg.EmailCode)) {
			MessageBox(TEXT("邮箱验证码不正确"));
			goto registragin;
		}
		if (cRegisterDlg.m_Email.IsEmpty()) {
			MessageBox(TEXT("请填写对应的邮箱"));
			goto registragin;
		}
		if (cRegisterDlg.m_Password.IsEmpty()) {
			MessageBox(TEXT("请填写对应的密码"));
			goto registragin;
		}
		//到了现在，就是填好了信息了
		//应该去发送一条协议信息，并等待响应
			//填写了信息，尝试与服务器连接
		CString msg;
		DWORD err;
		//把SOCKET与对话框联系起来，SOCKET有消息就会通知本对话
		m_socket.AttachCWnd(this);
		//自动完成SOCKET的初始化、设置
		if (m_socket.Create() == FALSE)
		{
			err = GetLastError();
			msg.Format(_T("创建Socket失败!\r\n错误代码:%d"), err);
			//输出错误信息并结束
			MessageBox(msg);
			PostQuitMessage(0);           //退出
			return TRUE;
		}
		//连接到服务器计算机，端口为0x8123的程序
		if (m_socket.Connect(cLoginDlg.m_ipAddr, 0x8123) == FALSE)
		{
			//如果连接成功，对方创建新的SOCKET，新的端口号，就与新的SOCKET，新的端口号通信。
			err = GetLastError();
			msg.Format(_T("连接服务器失败! \r\n错误代码:%d"), err);
			//输出错误信息并结束
			MessageBox(msg);
			PostQuitMessage(0);           //退出
			return TRUE;
		}
		//连接成功，发送一条协议信息
		wchar_t pkt[200];
		pkt[0] = 0x07; // 默认pkt[0]为协议信息
		// 定义0x11为登录所发送的信息,并补充具体传递的信息
		wsprintf(pkt + 1, L"%s,%s", cRegisterDlg.m_Email, cRegisterDlg.m_Password);
		// 发送
		if (m_socket.Send(pkt, 200) == FALSE)
		{
			MessageBox(_T("发送数据错误!"));
		}

		m_socket.Close();
		goto tryagain;
	}
	//输入信息校验
	if (wcslen(cLoginDlg.m_ipAddr) == 0) {
		MessageBox(TEXT("请填写对应的IP地址"));
		goto tryagain;
	}
	if (cLoginDlg.m_username.IsEmpty()) {
		MessageBox(TEXT("请填写邮箱"));
		goto tryagain;
	}

	//填写了信息，尝试与服务器连接
	CString msg;
	DWORD err;
	//把SOCKET与对话框联系起来，SOCKET有消息就会通知本对话
	m_socket.AttachCWnd(this);
	//自动完成SOCKET的初始化、设置
	if (m_socket.Create() == FALSE)
	{
		err = GetLastError();
		msg.Format(_T("创建Socket失败!\r\n错误代码:%d"), err);
		//输出错误信息并结束
		MessageBox(msg);
		PostQuitMessage(0);           //退出
		return TRUE;
	}
	//连接到服务器计算机，端口为0x8123的程序
	if (m_socket.Connect(cLoginDlg.m_ipAddr, 0x8123) == FALSE)
	{
		//如果连接成功，对方创建新的SOCKET，新的端口号，就与新的SOCKET，新的端口号通信。
		err = GetLastError();
		msg.Format(_T("连接服务器失败! \r\n错误代码:%d"), err);
		//输出错误信息并结束
		MessageBox(msg);
		PostQuitMessage(0);           //退出
		return TRUE;
	}

	Sleep(1000);
	// 代码运行到这里，就说明已经和服务器连接上了，现在向服务器发送一条协议信息，“XXX已经登录”
	// 构造协议信息
	// 登入聊天室,给服务器发送用户登录信息
	wchar_t pkt[200];
	pkt[0] = 0x11; // 默认pkt[0]为协议信息
	// 定义0x11为登录所发送的信息,并补充具体传递的信息
	wsprintf(pkt + 1, cLoginDlg.m_username);
	// 发送
	if (m_socket.Send(pkt, 200) == FALSE)
	{
		MessageBox(_T("发送数据错误!"));
	}

	//设置标题
	SetTitle(__TEXT("网约车服务"));
	//设置窗口大小
	MoveWindow(0, 0, 1080, 720);
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	//静态拆分，拆分成1行2列
	m_spliter.CreateStatic(this, 1, 2);
	//分配这两个视图位置
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView)
		, CSize(270, 720), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView)
		, CSize(810, 720), pContext);

	return TRUE;

}