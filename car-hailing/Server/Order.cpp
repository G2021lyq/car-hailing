#include "pch.h"
#include "Order.h"


Order::Order(const CString& driver, const CString& passenger, double distance)
    : m_driver(driver), m_passenger(passenger), m_distance(distance) {
    // 在构造函数中初始化订单的各个属性
    m_billAmount = CalculateBillAmount();
    m_estimatedTime = CalculateEstimatedTime();
    m_isCancelled = false;
}

// 获取司机名称
CString GetDriver() const {
    return m_driver;
}

// 获取乘客名称
CString GetPassenger() const {
    return m_passenger;
}

// 获取已走里程
double GetDistance() const {
    return m_distance;
}

// 获取账单金额
double GetBillAmount() const {
    return m_billAmount;
}

// 获取预计剩余时间
CString GetEstimatedTime() const {
    return m_estimatedTime;
}

// 检查订单是否已取消
bool IsCancelled() const {
    return m_isCancelled;
}

// 取消订单
void CancelOrder() {
    m_isCancelled = true;
}


CString m_driver;         // 司机
CString m_passenger;      // 乘客
double m_distance;        // 已走里程
double m_billAmount;      // 账单金额
CString m_estimatedTime;  // 预计剩余时间
bool m_isCancelled;       // 是否取消订单

// 计算账单金额
double CalculateBillAmount() {
    // 这里可以根据具体的计费规则进行计算
    // 假设每公里收费 10 元
    const double ratePerKilometer = 10.0;
    return m_distance * ratePerKilometer;
}

// 计算预计剩余时间
CString CalculateEstimatedTime() {
    // 这里可以根据具体的路程和交通情况进行估算
    // 假设每分钟行驶 1 公里
    const double speed = 1.0; // 公里/分钟
    double estimatedTime = m_distance / speed;

    int hours = static_cast<int>(estimatedTime / 60);
    int minutes = static_cast<int>(estimatedTime) % 60;

    CString strEstimatedTime;
    strEstimatedTime.Format(_T("%d小时%d分钟"), hours, minutes);
    return strEstimatedTime;
}
