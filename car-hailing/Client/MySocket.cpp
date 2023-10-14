#include "pch.h"

#include "MySocket.h"


MySocket::MySocket()
{
	pWnd = nullptr;
	m_msgTotal = 0;
}


MySocket::~MySocket()
{
}


void MySocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pWnd) {
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, CLOSE);
	}
	CSocket::OnClose(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_msgTotal++;
	if (pWnd) {
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, RETURN);
	}
	CSocket::OnReceive(nErrorCode);
}

void MySocket::AttachCWnd(CWnd* cwnd) {
	pWnd = cwnd;
}
