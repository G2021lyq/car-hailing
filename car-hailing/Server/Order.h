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

    //将订单类转换为 MFC 的 CString 字符串。
    CString ToCString() const;

    //将合法的 MFC 的 CString 字符串转回订单类
    void FromCString(const CString& strOrder);

    //重载赋值运算符，将 MFC 的 CString 赋值给订单类实例
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
