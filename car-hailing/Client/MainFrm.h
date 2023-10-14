
// MainFrm.h: CMainFrame 类的接口
//


#pragma once

//自定义消息
//WM_USER 是起始值
#define NM_A (WM_USER+2021)
#define NM_B (WM_USER+2022)
#define NM_C (WM_USER+2023)

#define NM_OK (WM_USER+2024)


#include "MySocket.h"

class CMainFrame : public CFrameWnd
{

protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

	// 特性
public:

	// 操作
public:

	// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 实现
public:
	MySocket m_socket;

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;
	//切分窗口对象
private:
	CSplitterWnd m_spliter;
	//自定义消息处理函数
private:
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSocket(WPARAM wParam, LPARAM lParam);//Socket的消息响应
	// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	//分割来着
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


