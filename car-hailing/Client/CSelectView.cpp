// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CSelectView.h"

#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//加载图片
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_Papper);

	//图片列表创建
	m_imageList.Create(60, 60, ILC_COLOR32, 1, 1);
	//添加图片
	m_imageList.Add(icon);
	//获取树控件
	m_treeCtrl = &GetTreeCtrl();
	//为树控件设置图片列表
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);
	//树控件设置每一个节点
	m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("打车服务"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("历史记录"), 0, 0, NULL);

}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);


	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前的选项值
	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//通过选项，来获取选项的内容
	CString str = m_treeCtrl->GetItemText(item);

	//MessageBox(str);

	//不能使用Switch，必须用if
	if (str == TEXT("个人信息"))
	{
		// 如果是"个人信息"，向主窗口，发送NM_A消息，参数如下
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	if (str == TEXT("打车服务"))
	{
		// 如果是"打车服务"，向主窗口，发送NM_B消息，参数如下
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);

	}
}
