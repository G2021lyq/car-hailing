#pragma once
#include <afx.h>

class HistoryRecord
{
public:
	HistoryRecord();
	HistoryRecord(int count, const CString& account, const CString& driver, const CString& order);

	CString GetAccount() const;
	int GetCount() const;
	CString GetDriver() const;
	CString GetOrder() const;

	// 将历史记录类转换为 MFC 的 CString 字符串。
	CString ToCString() const;
	// 将合法的 MFC 的 CString 字符串转回历史记录类。
	void FromCString(const CString& strRecord);
	// 重载赋值运算符，将 MFC 的 CString 赋值给历史记录类实例。
	HistoryRecord& operator=(const CString& strRecord);

private:
	CString m_account;
	int m_count;
	CString m_driver;
	CString m_order;

};