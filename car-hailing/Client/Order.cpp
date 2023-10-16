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
CString Order::GetDriver() const
{
    return m_driver;
}

// 获取乘客名称
CString Order::GetPassenger() const {
    return m_passenger;
}

// 获取已走里程
double Order::GetDistance() const {
    return m_distance;
}

// 获取账单金额
double Order::GetBillAmount() const {
    return m_billAmount;
}

// 获取预计剩余时间
CString Order::GetEstimatedTime() const {
    return m_estimatedTime;
}

// 检查订单是否已取消
bool Order::IsCancelled() const {
    return m_isCancelled;
}

// 取消订单
void Order::CancelOrder() {
    m_isCancelled = true;
}

// 计算账单金额
double Order::CalculateBillAmount() {
    // 这里可以根据具体的计费规则进行计算
    // 假设每公里收费 10 元
    const double ratePerKilometer = 10.0;
    return m_distance * ratePerKilometer;
}

// 计算预计剩余时间
CString Order::CalculateEstimatedTime() {
    // 这里可以根据具体的路程和交通情况进行估算
    // 假设每分钟行驶 1 公里
    const double speed = 1.0; // 公里/分钟
    double estimatedTime = m_distance / speed;

    int hours = static_cast<int>(estimatedTime / 60);
    int minutes = static_cast<int>(estimatedTime) % 60;

    CString strEstimatedTime;
    strEstimatedTime.Format(_T("%dh%dmin"), hours, minutes);
    return strEstimatedTime;
}

CString Order::ToCString() const {
    CString strOrder;
    strOrder.Format(_T("Driver: %s, Passenger: %s, Distance: %.2f km, Bill Amount: %.2f, Estimated Time: %s, Is Cancelled: %s"),
                    m_driver, m_passenger, m_distance, m_billAmount, m_estimatedTime, m_isCancelled ? _T("Yes") : _T("No"));
    return strOrder;
}

void Order::FromCString(const CString& strOrder) {
    CString strDriver, strPassenger, strDistance, strBillAmount, strEstimatedTime, strIsCancelled;
    int nMatches = _stscanf_s(strOrder, _T("Driver: %s, Passenger: %s, Distance: %lf km, Bill Amount: %lf, Estimated Time: %s, Is Cancelled: %s"),
                              strDriver.GetBufferSetLength(100), 100,
                              strPassenger.GetBufferSetLength(100), 100,
                              &m_distance, &m_billAmount,
                              strEstimatedTime.GetBufferSetLength(100), 100,
                              strIsCancelled.GetBufferSetLength(100), 100);

    m_driver = strDriver;
    m_passenger = strPassenger;
    m_estimatedTime = strEstimatedTime;
    m_isCancelled = (strIsCancelled.CompareNoCase(_T("Yes")) == 0);
}


Order& Order::operator=(const CString& strOrder) {
    FromCString(strOrder);
    return *this;
}