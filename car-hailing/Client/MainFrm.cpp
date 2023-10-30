
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
#include "CHistoryDlg.h"

#include "CSelectView.h"
#include "CDisplayView.h"
#include "CRegisterDlg.h"
#include "Account.h"
#include "Driver.h"
#include "Order.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE handle_write;
HANDLE handle_read;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)

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

//用来创建邮箱子系统，用于生成随机数验证码
void CMainFrame::CreateProcess_EmailSystem()
{
	//创建子系统
	//注意管道，管道的两个参数应该设置为该类的成员。
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	// Create a pipe for the child process's STDIN. 
	// 获取主窗口（CMainFrame）
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	bool ret = CreatePipe(&handle_read, &handle_write, &saAttr, 0);
	if (ret == false)	pMainFrame->MessageBox(L"创建管道失败");
	PROCESS_INFORMATION piProcInfo;
	// Set up members of the PROCESS_INFORMATION structure. 
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	// Set up members of the STARTUPINFO structure. // This structure specifies the STDIN handles for redirection.
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdInput = handle_read; //把管道的读句柄传给子进程
	si.hStdOutput = handle_write;// 把管道的写句柄给子进程
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;  // 隐藏子进程窗口
	//子进程、设置管道句柄的继承
	wchar_t cmdline[] = _T("EmailSystem.exe");
	ret = CreateProcess(NULL, cmdline, NULL, NULL, TRUE,   // handles are inherited 
		HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW // creation flags
		, NULL, NULL, &si, &piProcInfo);
	if (!ret) { pMainFrame->MessageBox(L"创建进程失败"); }
	else {
		// 把子进程加入到作业中
		HANDLE HandleJob = CreateJobObject(nullptr, nullptr);
		if (AssignProcessToJobObject(HandleJob, piProcInfo.hProcess)) {
			JOBOBJECT_EXTENDED_LIMIT_INFORMATION LimitInfo;
			ZeroMemory(&LimitInfo, sizeof(LimitInfo));
			LimitInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
			SetInformationJobObject(HandleJob, JobObjectExtendedLimitInformation, &LimitInfo, sizeof(LimitInfo));
		}
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}
}
//用来创建二维码进程
void CMainFrame::CreateProcess_Qrcode(Order& m_Order) {
	PROCESS_INFORMATION piProcInfo;
	// Set up members of the PROCESS_INFORMATION structure. 
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	// Set up members of the STARTUPINFO structure. // This structure specifies the STDIN handles for redirection.
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.wShowWindow = SW_SHOW;  // 隐藏子进程窗口
		//子进程、设置管道句柄的继承
	wchar_t cmdline[2048];
	wmemset(cmdline, 0, 2048);
	CStringW a;
	a.Format(L"%.2lf", m_Order.GetBillAmount());
	wsprintf(cmdline, L"Qrcode.exe %s %s", m_Account.getEmail().GetString(), a);

	bool ret = CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &piProcInfo);
	if (!ret) { MessageBox(L"创建进程失败"); }
	else
	{
		// 把子进程加入到作业中
		HANDLE HandleJob = CreateJobObject(nullptr, nullptr);
		if (AssignProcessToJobObject(HandleJob, piProcInfo.hProcess))
		{
			JOBOBJECT_EXTENDED_LIMIT_INFORMATION LimitInfo;
			ZeroMemory(&LimitInfo, sizeof(LimitInfo));
			LimitInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
			SetInformationJobObject(HandleJob, JobObjectExtendedLimitInformation, &LimitInfo, sizeof(LimitInfo));
		}
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}

}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	CFormView* pNewView = nullptr; // 在外部定义变量


	CStringW receivedString;
	wchar_t Buff[2048];

	switch (wParam)
	{
	case(NM_A):
	{
		receivedString = m_Account.ToCString();
		wsprintf(Buff, L"%s", receivedString.GetString());

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
	{
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
	}
	case (NM_C):
	{
		CStringW receivedString = static_cast<LPCTSTR>(reinterpret_cast<LPCWSTR>(lParam));
		Order m_Order;
		m_Order = receivedString;
		CreateProcess_Qrcode(m_Order);
		//定义发送字符串
		wchar_t pkt[2048];
		pkt[0] = 0x17;//默认pkt[0]为协议信息
		//定义主体信息
		wsprintf(pkt + 1, L"%s", m_Order.ToCString().GetString());
		//发送信息包含两部分，字符串和总空间，注意不能用wcslen代替
		if (m_socket.Send(pkt, 2048) == SOCKET_ERROR) {
			//每此写Send都要进行错误检测
			MessageBox(TEXT("发送测试SOCKET信息失败了"));
		}

		//SendMessage(NM_D, (WPARAM)NM_D, (LPARAM)0);
		//Sleep(100);
		break;
	}
	case (NM_D):
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CHistoryDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CHistoryDlg)
			, CSize(810, 720), &Context);
		pNewView = (CHistoryDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

		break;
	}
	case(NM_OK):
	{
		CStringW receivedString = static_cast<LPCTSTR>(reinterpret_cast<LPCWSTR>(lParam));
		wsprintf(Buff, L"%s", receivedString.GetString());
		MessageBox(Buff);

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
		Sleep(100);
		break;
	}
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
		//登录协议
	case 0x11:
	{
		wsprintf(GetBuff, L"%s", pkt + 1);
		if (wcscmp(GetBuff, L"password") == 0) {
			MessageBox(L"密码错误！！！");
			login_No = true;
		}
		else if (wcscmp(GetBuff, L"email") == 0) {
			MessageBox(L"邮箱没有被注册！！！");
			login_No = true;
		}
		else {
			login_flag = true;
			m_Account = GetBuff;
		}
		PostMessage(NM_Login, 0, 0);
		break;
	}
	//测试协议
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
		m_socket.Close();
		break;
	}
	case 0xA1:
	{
		//这些信息将写到显示里去
		wsprintf(GetBuff, L"%s\r\n", pkt + 1);
		//定义自定义消息，告诉CCarServiceDlg去执行相关业务。这里是显示。
		CCarServiceDlg* pCarServiceDlg = dynamic_cast<CCarServiceDlg*>(m_spliter.GetPane(0, 1));
		pCarServiceDlg->PostMessage(NM_SHOW_EDIT, (WPARAM)NM_SHOW_EDIT, reinterpret_cast<LPARAM>(GetBuff));
		Sleep(100);
		break;
	}
	case 0xA2:
	{
		wsprintf(GetBuff, L"%s", pkt + 1);
		CString OrderStr;
		OrderStr.Format(L"%s", GetBuff);
		Order m_Order;
		m_Order = GetBuff;
		CString myString = m_Order.ToCString();
		MessageBox(myString);

		LPARAM lParam = reinterpret_cast<LPARAM>(static_cast<LPCTSTR>(OrderStr));
		SendMessage(NM_OK, (WPARAM)NM_OK, lParam);

		// 		CCarServiceDlg* pCarServiceDlg = dynamic_cast<CCarServiceDlg*>(m_spliter.GetPane(0, 1));
		// 		pCarServiceDlg->PostMessage(NM_Finish, (WPARAM)NM_Finish, lParam);
		Sleep(100);
		break;
	}
	case 0x18:
	{
		wsprintf(GetBuff, L"%s", pkt + 1);
		CHistoryDlg* pCarServiceDlg = dynamic_cast<CHistoryDlg*>(m_spliter.GetPane(0, 1));
		pCarServiceDlg->PostMessage(NM_Page, (WPARAM)NM_Page, reinterpret_cast<LPARAM>(GetBuff));

		break;
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

	//创建邮箱子系统
	CreateProcess_EmailSystem();

	//在创建主窗口前，先弹出登录窗口，必须登录成功，才能进入主窗口
	//先填写服务器地址，默认地址是127.0.0.1
tryagain:
	login_flag = false;
	login_No = false;

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
		wsprintf(pkt + 1, L"%s,%s", cRegisterDlg.m_Email.GetString(), cRegisterDlg.m_Password.GetString());
		// 发送
		if (m_socket.Send(pkt, 200) == FALSE)
		{
			MessageBox(_T("发送数据错误!"));
		}
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
	Account a;
	if (a.IsEmailValid(cLoginDlg.m_username) == FALSE)
	{
		MessageBox(TEXT("邮箱格式不正确"));
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
	wsprintf(pkt + 1, L"%s,%s", cLoginDlg.m_username.GetString(), cLoginDlg.m_password.GetString());
	// 发送
	if (m_socket.Send(pkt, 200) == FALSE)
	{
		MessageBox(_T("发送数据错误!"));
	}


	// 在消息循环中等待接收消息
	MSG m_msg;
	while (::GetMessage(&m_msg, NULL, 0, 0)) {
		if (m_msg.message == NM_Login) {
			if (login_No == true)
				goto tryagain;
			else if (login_flag == true)
				break;
			// 处理自定义消息
			// 在这里执行你希望在接收消息后执行的代码
		}
		::TranslateMessage(&m_msg);
		::DispatchMessage(&m_msg);
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