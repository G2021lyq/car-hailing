#pragma once
#include <iostream>
#include <afx.h> 

class Order {
public:
    Order(const CString& driver, const CString& passenger, double* start, double* end);
    Order(const CString& passenger, double* start, double* end);

    CString GetDriver() const;
    CString GetPassenger() const;
    double GetDistance() const;
    double GetBillAmount() const;
    CString GetEstimatedTime() const;
    bool IsCancelled() const;
    void CancelOrder();

    //��������ת��Ϊ MFC �� CString �ַ�����
    CString ToCString() const;

    //���Ϸ��� MFC �� CString �ַ���ת�ض�����
    void FromCString(const CString& strOrder);

    //���ظ�ֵ��������� MFC �� CString ��ֵ��������ʵ��
    Order& operator=(const CString& strOrder);

private:
    CString m_driver;
    CString m_passenger;
    double m_distance;
    double m_billAmount;
    CString m_estimatedTime;
    bool m_isCancelled;
    //(0,21) (0,11)
    double m_start[2];
    double m_end[2];

    double CalculateBillAmount();
    CString CalculateEstimatedTime();
};
