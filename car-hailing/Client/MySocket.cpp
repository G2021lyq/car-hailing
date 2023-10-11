// MySocket.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
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

void MySocket::AttachCWnd(CWnd* cwnd) {
	pWnd = cwnd;
}


void MySocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pWnd) {
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, CLOSE);
	}
	CSocket::OnClose(nErrorCode);
}


int MySocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pWnd) {
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, RETURN);
	}
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}
