#pragma once
#include "afxsock.h"

//自定义一个Socket消息，包含三种类型:
//自定义消息必须大于WM_USER
#define SOCKET_EVENT WM_USER + 1001  
//枚举消息类型
enum { ACCEPT = 0, SEND = 1, RETURN = 2, CLOSE = 3 };

// MySocket 命令目标

class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	CString m_Player;//保存用户名

	void AttachCwnd(CWnd* pWnd);//保存关联的窗口
private:
	//非常重要，保存关联的窗口
	CWnd* pWnd;
};


