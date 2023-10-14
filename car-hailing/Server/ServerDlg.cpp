
// ServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#include "MySocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

END_MESSAGE_MAP()


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

	// 0x11---服务器接收用户进入聊天室
	if (SendBuff[0] == 0x11)
	{
		CString ipaddr;             // IP字符串
		UINT port;                 // 端口号
		// 与该套接字链接的对方的IP地址、端口号
		from->GetPeerName(ipaddr, port);
		// 与SOCKET通信的用户的称谓
		from->m_Player = SendBuff + 1; // 名称的记录会在为空时停止

		MessageBox(from->m_Player);

		// 向列表中插入一项，使用了锁的知识
		m_csList.Lock();
		// 插入到列表中（该列表存储所有的Socket），返回插入的行号
		item = m_list.InsertItem(0, (LPCTSTR)(SendBuff + 1));
		// 保存该SOCKET指针到该行的附加数据域
		m_list.SetItemData(item, (DWORD)from);
		// 设置第2列，IP地址列
		m_list.SetItemText(item, 1, ipaddr);
		m_csList.Unlock();

		// s1中保存新加入用户的socket
		s1 = (MySocket*)m_list.GetItemData(item);

		// 填写ShowBuff信息
		swprintf(ShowBuff, L" %s 连接成功\r\n", static_cast<const wchar_t*>(from->m_Player));

		//发送反馈信息
		//from->Send(L"你好吗？", 100);

		SendBuff[0] = 0x00;//0x00是协议类型，表示一个测试信息
		swprintf(SendBuff + 1, L"服务器收到了信息");
		from->Send(SendBuff, 2048);
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
	swprintf(out_msg, L"%s 退出聊天室\r\n", static_cast<const wchar_t*>(from->m_Player));
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

void CServerDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_socket.AttachCwnd(this);
	BOOL isTrue = m_socket.Create(0x8123, SOCK_STREAM);
	if (isTrue)
	{
		if (m_socket.Listen())
			AfxMessageBox(TEXT("开启服务器成功！"));
		GetDlgItem(IDC_BUTTON_Start)->EnableWindow(FALSE);
		return;
	}
	AfxMessageBox(TEXT("不好意思，出了点问题..."));
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
