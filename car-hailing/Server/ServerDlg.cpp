
// ServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#include "MySocket.h"
#include "Order.h"
#include "HistoryRecord.h"
#include "MyFile.h"
#include "Account.h"
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int maxBufferSize = 5; // 队列的最大容量
int BufferSum;
int DriverSum;
int OrderSum;
std::list<CString> buffer; // 共享队列
std::mutex buffer_mtx; // 互斥锁，用于保护共享队列
std::condition_variable notFull; // 缓冲区不满条件变量
std::condition_variable notEmpty; // 缓冲区不空条件变量

// CServerDlg 对话框

CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
	, m_showMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UserList, m_list);
	DDX_Text(pDX, IDC_EDIT_INF, m_showMsg);
	DDX_Control(pDX, IDC_BUTTON_Start, m_startBtn);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_UserList, &CServerDlg::OnLvnItemchangedUserlist)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CServerDlg::OnBnClickedButtonStart)

	ON_MESSAGE(SOCKET_EVENT, OnSocket)
	ON_MESSAGE(NM_ADD_Driver, OnMyChange)
	ON_MESSAGE(NM_ADD_Order, OnMyChange)

END_MESSAGE_MAP()
void producer(ShowDlg* mydlg) {
	//获取锁，尝试访问共享队列
	std::unique_lock<std::mutex> lock(buffer_mtx);
	Driver driver(mydlg->count); //使用随机方式
	//如果内容多了，先等待
	while (buffer.size() >= maxBufferSize) {
		notFull.wait(lock);
	}
	//生产内容
	CString newDriverStr = driver.ToString();
	mydlg->MessageBox(newDriverStr);
	buffer.push_back(newDriverStr);

	DriverSum--;
	BufferSum++;
	mydlg->PostMessage(NM_DiverSum, (WPARAM)NM_DiverSum, (LPARAM)DriverSum);
	mydlg->PostMessage(NM_BufferSum, (WPARAM)NM_BufferSum, (LPARAM)BufferSum);
	lock.unlock();
	//成功生产数据
	notEmpty.notify_all(); // 通知消费者队列非空
	//生产出数据，进程则死亡
}

//添加参数，SOCKET
void consumer(ShowDlg* mydlg) {
	//获取锁
	std::unique_lock<std::mutex> lock(buffer_mtx);
	//空了则等待
	while (buffer.size() <= 0) {
		notEmpty.wait(lock);
	}
	//补充算法
	CString driverStr = buffer.back(); // 获取尾部元素
	buffer.pop_back(); // 删除尾部元素
	//补充算法

	BufferSum--;
	OrderSum--;
	mydlg->PostMessage(NM_OrderSum, (WPARAM)NM_OrderSum, (LPARAM)OrderSum);
	mydlg->PostMessage(NM_BufferSum, (WPARAM)NM_BufferSum, (LPARAM)BufferSum);

	lock.unlock();
	notFull.notify_all(); // 通知生产者队列非满
	//这里应该进行一次网络通信
}


//添加参数，SOCKET
void consumerSocket(ShowDlg* mydlg, MySocket* from, CString OrderStr) {
	//获取锁
	std::unique_lock<std::mutex> lock(buffer_mtx);
	//空了则等待
	while (buffer.size() <= 0) {
		notEmpty.wait(lock);
	}

	//补充算法
	CString driverStr = buffer.back(); // 获取尾部元素
	buffer.pop_back(); // 删除尾部元素
	//补充算法

	BufferSum--;
	OrderSum--;
	mydlg->PostMessage(NM_OrderSum, (WPARAM)NM_OrderSum, (LPARAM)OrderSum);
	mydlg->PostMessage(NM_BufferSum, (WPARAM)NM_BufferSum, (LPARAM)BufferSum);

	lock.unlock();
	notFull.notify_all(); // 通知生产者队列非满
	//这里应该进行一次网络通信
	Order m_Order;
	m_Order = OrderStr;
	m_Order.SetDriver(driverStr);

	//回消息，客户端显示
	wchar_t newMessage[2048];
	wmemset(newMessage, 0, 2048);
	newMessage[0] = 0xA1;//该协议用于显示于用户的显示屏上
	wsprintf(newMessage + 1, L"匹配成功，享受你的旅程");
	if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
		mydlg->MessageBox(L"服务器发送消息失败！");
	}
	wmemset(newMessage, 0, 2048);
	newMessage[0] = 0xA2;//该协议用于显示于用户的显示屏上
	wsprintf(newMessage + 1, m_Order.ToCString());
	if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
		mydlg->MessageBox(L"服务器发送消息失败！");
	}
}


LRESULT CServerDlg::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case (NM_ADD_Driver):
	{
		std::thread m_producer;
		std::unique_lock<std::mutex> lock(buffer_mtx);
		DriverSum++;
		mydlg->PostMessage(NM_DiverSum, (WPARAM)NM_DiverSum, (LPARAM)DriverSum);
		lock.unlock();
		m_producer = std::thread(producer, mydlg);
		m_producer.detach();
		break;
	}
	case (NM_ADD_Order):
	{
		std::thread m_consumer;
		std::unique_lock<std::mutex> lock(buffer_mtx);
		OrderSum++;
		mydlg->PostMessage(NM_OrderSum, (WPARAM)NM_OrderSum, (LPARAM)OrderSum);
		lock.unlock();
		m_consumer = std::thread(consumer, mydlg);
		m_consumer.detach();
		break;

	}
	}
	return 0;
}
// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//修改主对话框的背景
	m_brBg.DeleteObject();
	m_bmBg.DeleteObject();
	m_bmBg.LoadBitmap(IDB_bg);
	m_brBg.CreatePatternBrush(&m_bmBg);

	m_startBtn.LoadBitmaps(IDB_normalBtn, IDB_pushedBtn, NULL, IDB_stopBtn);
	m_startBtn.SizeToContent();//按钮自适应位图的大小

	//初始化列表控件的列标头
	m_list.InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, _T("IP"), LVCFMT_LEFT, 100);


	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argv) {
		if (argc > 0)
		{
			CString __msg;
			__msg.Format(L"%s", argv[1]);
			if (__msg.Compare(_T("open")) == 0)
				OnBnClickedButtonStart();

		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerDlg::OnLvnItemchangedUserlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


LRESULT CServerDlg::OnSocket(WPARAM wParam, LPARAM lParam)
{
	MySocket* sock = (MySocket*)wParam;
	MySocket* c;

	SOCKADDR_IN sockAddr;
	int nSize = sizeof(sockAddr);
	BOOL res;

	switch (lParam)
	{
		//新的连接消息
	case ACCEPT:
		c = new MySocket;
		c->AttachCwnd(this);

		res = sock->Accept(*c, (SOCKADDR*)&sockAddr, &nSize);
		if (res == FALSE)
		{
			MessageBox(_T("Accept Error!"));
		}
		break;
		//关闭连接消息

	case CLOSE:
		ClosePlayer(sock);
		break;

		//收到数据消息
	case RETURN:
		ParserPkt(sock);
		break;
	}
	return 1;
}

void CServerDlg::ParserPkt(MySocket* from)
{
	wchar_t SendBuff[2048];     // 发送缓冲
	wchar_t ShowBuff[2048];     // 显示缓冲
	wchar_t nbuf[100];         // 临时缓冲区

	// 初始化各缓冲区
	wmemset(SendBuff, 0, 2048);
	wmemset(ShowBuff, 0, 2048);
	wmemset(nbuf, 0, 100);

	int len;					//记录发送长度
	int item;					//列表序号
	MySocket* s1;				//发送一般消息的Socket
	MySocket* s;				//发送用户进入信息的Socket

	// 读取数据
	len = from->Receive(SendBuff, 2048);


	if (SendBuff[0] == 0x11) {
		// 0x11---服务器接收用户进入聊天室
		CString ipaddr;             // IP字符串
		UINT port;                 // 端口号
		// 与该套接字链接的对方的IP地址、端口号
		from->GetPeerName(ipaddr, port);
		// 与SOCKET通信的用户的称谓
		wsprintf(SendBuff, L"%s", SendBuff + 1);
		CString pkt = SendBuff;
		CString m_Email;
		CString m_Password;
		int commaPos = pkt.Find(_T(','));
		m_Email = pkt.Left(commaPos);
		m_Password = pkt.Mid(commaPos + 1);
		from->m_Player = m_Email;

		//设置返回信息，设置协议
		wchar_t newMessage[2048];
		wmemset(newMessage, 0, 2048);
		newMessage[0] = 0x11;
		//打开文件
		m_file.SetFilePathAccount(m_file.GetFilePathAccount(), m_file.GetPathAccount());
		m_file.OpenFile();
		int Number = m_file.is_StringExistInFile(m_Email);
		if (Number != -1)
		{
			//有记录，可以登录
			Account loginAccount;
			loginAccount = m_file.GetStringByNumber(Number);
			if (loginAccount.getPassword() == m_Password)
			{
				//脏化密码
				loginAccount.setPassword(L"******");
				//密码正确，可以登录
				wsprintf(newMessage + 1, L"%s", loginAccount.ToCString());
				// 填写ShowBuff信息
				wsprintf(ShowBuff, L" %s 登录成功\r\n", static_cast<const wchar_t*>(from->m_Player));

				// 向列表中插入一项，使用了锁的知识
				m_csList.Lock();
				// 插入到列表中（该列表存储所有的Socket），返回插入的行号
				item = m_list.InsertItem(0, (LPCTSTR)m_Email);
				// 保存该SOCKET指针到该行的附加数据域
				m_list.SetItemData(item, (DWORD)from);
				// 设置第2列，IP地址列
				m_list.SetItemText(item, 1, ipaddr);
				m_csList.Unlock();
				// s1中保存新加入用户的socket
				s1 = (MySocket*)m_list.GetItemData(item);
			}
			else {
				//不能登录
				wsprintf(newMessage + 1, L"password");
				// 填写ShowBuff信息
				wsprintf(ShowBuff, L" %s 登录失败,原因：密码错误\r\n", static_cast<const wchar_t*>(from->m_Player));
			}
		}
		else {
			//不能登录
			wsprintf(newMessage + 1, L"email");
			// 填写ShowBuff信息
			wsprintf(ShowBuff, L" %s 登录失败,原因：邮箱未注册\r\n", static_cast<const wchar_t*>(from->m_Player));
		}
		m_file.CloseFile();

		//发送反馈信息
		if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
			//每次写Send都应该进行错误处理
			MessageBox(L"服务器发送反馈信息失败！！");
		}

	}
	else if (SendBuff[0] == 0x10)
	{
		MessageBox(L"收到测试信息");

		//该协议为测试Socket的协议
		wsprintf(SendBuff, L"%s", SendBuff + 1);

		//对于信息进行处理，我这里省略没有写
		/*
		* XXXXXXXXXXXXXXXXXX
		* XXXXXXXXXXXXXXXXXX
		*/

		wchar_t newMessage[2048];
		wmemset(newMessage, 0, 2048);
		newMessage[0] = 0x10;
		wsprintf(newMessage + 1, L"知道了，%s-你走吧", from->m_Player);

		if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
			//每次写Send都应该进行错误处理
			MessageBox(L"服务器发送反馈信息失败！！");
		}

		//整理ShowBuff，会写到服务器的编辑框中
		wsprintf(ShowBuff, L" %s发送了:%s\r\n 发送给%s:%s\r\n",
			from->m_Player, SendBuff, from->m_Player, newMessage);
	}
	else if (SendBuff[0] == 0x07) //申请注册的方式
	{
		wsprintf(SendBuff, L"%s", SendBuff + 1);
		CString pkt = SendBuff;
		CString m_Email;
		CString m_Password;
		int commaPos = pkt.Find(_T(','));
		m_Email = pkt.Left(commaPos);
		m_Password = pkt.Mid(commaPos + 1);
		from->m_Player = m_Email;

		Account newAccount;
		newAccount.setUsername(L"无名之辈");
		newAccount.setEmail(m_Email);
		newAccount.setPassword(m_Password);
		newAccount.setBio(L"这个人很懒，还没有简介");
		newAccount.setAvatar(L"NULL");

		wchar_t newMessage[2048];
		wmemset(newMessage, 0, 2048);
		newMessage[0] = 0x07; //协议信息

		m_file.SetFilePathAccount(m_file.GetFilePathAccount(), m_file.GetPathAccount());
		m_file.OpenFile();
		if (m_file.is_StringExistInFile(m_Email) != -1)
		{
			//找到了相同的邮箱
			wsprintf(newMessage + 1, L"no");
			wsprintf(ShowBuff, L" %s尝试注册:失败.%s，该邮箱已经存在\r\n",
				from->m_Player, from->m_Player);

		}
		else {
			//写一条信息
			m_file.WriteLine(newAccount.ToCString());
			wsprintf(newMessage + 1, L"yes");
			wsprintf(ShowBuff, L" %s尝试注册:成功\r\n",
				from->m_Player);
		}
		m_file.CloseFile();

		//发送消息
		if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
			//每次写Send都应该进行错误处理
			MessageBox(L"服务器发送反馈信息失败！！");
		}
	}
	else if (SendBuff[0] == 0xA0) {
		wsprintf(SendBuff, L"%s", SendBuff + 1);
		Order newOrder;
		newOrder = SendBuff;

		//回消息，客户端显示
		wchar_t newMessage[2048];
		wmemset(newMessage, 0, 2048);
		newMessage[0] = 0xA1;//该协议用于显示于用户的显示屏上
		wsprintf(newMessage + 1, L"匹配中...");

		if (from->Send(newMessage, 2048) == SOCKET_ERROR) {
			MessageBox(_T("服务器发送消息失败！"));
		}
		std::unique_lock<std::mutex> lock(buffer_mtx);
		OrderSum++;
		mydlg->PostMessage(NM_OrderSum, (WPARAM)NM_OrderSum, (LPARAM)OrderSum);
		lock.unlock();
		std::thread m_consumer;
		m_consumer = std::thread(consumerSocket, mydlg, from, newOrder.ToCString());
		m_consumer.detach();
	}
	// 无论怎样都将信息传给edit里面
	Append(ShowBuff);
}

void CServerDlg::Append(wchar_t* msg)
{
	//读取消息框中所有的消息
	m_showMsg += msg;
	UpdateData(FALSE);
}

void CServerDlg::ClosePlayer(MySocket* from)
{
	int i, msg_len;
	wchar_t out_msg[200];

	// 填写out_msg信息
	wsprintf(out_msg, L"%s 退出聊天室\r\n", static_cast<const wchar_t*>(from->m_Player));
	msg_len = wcslen(out_msg) + 1;

	//去列表中找到这个用户，把它删除
	m_csList.Lock();
	for (i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemData(i) == (DWORD)from)
		{
			delete from;
			m_list.DeleteItem(i);
			break;
		}
	}
	m_csList.Unlock();

	//不论如何，将信息写入edit里面
	Append(out_msg);
}


DWORD WINAPI ShowMessageBox(LPVOID lpParam) {
	MessageBox(NULL, L"成功打开服务器", L"消息框", MB_OK);
	return 0;
}

void CServerDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_socket.AttachCwnd(this);
	BOOL isTrue = m_socket.Create(0x8123, SOCK_STREAM);
	if (isTrue)
	{
		if (m_socket.Listen())
			HANDLE hThread = CreateThread(NULL, 0, ShowMessageBox, NULL, 0, NULL);
		GetDlgItem(IDC_BUTTON_Start)->EnableWindow(FALSE);
		CreatDriver();
		return;
	}
	AfxMessageBox(TEXT("不好意思，出了点问题..."));
}

void CServerDlg::CreatDriver()
{
	mydlg = new ShowDlg;
	mydlg->Create(IDD_SHOW_DIALOG, this);
	mydlg->ShowWindow(SW_SHOW);

	mydlg->PostMessage(NM_DiverSum, (WPARAM)NM_DiverSum, (LPARAM)DriverSum);
	mydlg->PostMessage(NM_OrderSum, (WPARAM)NM_OrderSum, (LPARAM)OrderSum);
	mydlg->PostMessage(NM_BufferSum, (WPARAM)NM_BufferSum, (LPARAM)BufferSum);
}



HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_brBg;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
