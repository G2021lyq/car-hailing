#include "pch.h"
#include "HistoryRecord.h"

HistoryRecord::HistoryRecord()
{
}

HistoryRecord::HistoryRecord(int count, const CString& account, const CString& driver, const CString& order)
	: m_account(account), m_count(count), m_driver(driver), m_order(order)
{
}

CString HistoryRecord::GetAccount() const
{
	return m_account;
}

int HistoryRecord::GetCount() const
{
	return m_count;
}

CString HistoryRecord::GetDriver() const
{
	return m_driver;
}

CString HistoryRecord::GetOrder() const
{
	return m_order;
}

CString HistoryRecord::ToCString() const
{
	CString strRecord;
	strRecord.Format(_T("%s|%d|%s|%s"), m_account, m_count, m_driver, m_order);
	return strRecord;
}

void HistoryRecord::FromCString(const CString& strRecord)
{
	int delimiter1 = strRecord.Find(_T('|'));
	int delimiter2 = strRecord.Find(_T('|'), delimiter1 + 1);
	int delimiter3 = strRecord.Find(_T('|'), delimiter2 + 1);

	if (delimiter1 != -1 && delimiter2 != -1 && delimiter3 != -1)
	{
		m_account = strRecord.Mid(0, delimiter1);
		m_count = _ttoi(strRecord.Mid(delimiter1 + 1, delimiter2 - delimiter1 - 1));
		m_driver = strRecord.Mid(delimiter2 + 1, delimiter3 - delimiter2 - 1);
		m_order = strRecord.Mid(delimiter3 + 1);
	}
}

HistoryRecord& HistoryRecord::operator=(const CString& strRecord)
{
	FromCString(strRecord);
	return *this;
}