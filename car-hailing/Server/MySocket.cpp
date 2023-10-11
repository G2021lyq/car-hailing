// MySocket.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "MySocket.h"


// MySocket

MySocket::MySocket()
{
	pWnd = NULL;
}

MySocket::~MySocket()
{
}


// MySocket 成员函数


void MySocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	//如果pWnd存在，发送一个SOCKET_EVENT消息，参数是ACCEPT
	if (pWnd) {
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, ACCEPT);
	}
	CSocket::OnAccept(nErrorCode);
}


void MySocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, CLOSE);
	//该函数将指定的消息发送到一个或多个窗口。此函数为指定的窗口调用窗口程序，直到窗口程序处理完消息再返回

	CSocket::OnClose(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, RETURN);


	CSocket::OnReceive(nErrorCode);
}

void MySocket::AttachCwnd(CWnd* pW)
{
	pWnd = pW;
}
