#pragma once

#define SOCKET_EVENT WM_USER+1001
enum { ACCEPT = 0, SEND = 1, RETURN = 2, CLOSE = 3 };//定义消息类型枚举常量
// MySocket 命令目标

class MySocket : public CSocket
{
public:

	MySocket();
	virtual ~MySocket();

	void AttachCWnd(CWnd* cwnd);
	CWnd* pWnd;//保存关联窗口
	virtual void OnClose(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
};


