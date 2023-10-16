#include "pch.h"
#include "Order.h"

Order::Order(const CString& driver, const CString& passenger, double distance)
    : m_driver(driver), m_passenger(passenger), m_distance(distance) {
    // �ڹ��캯���г�ʼ�������ĸ�������
    m_billAmount = CalculateBillAmount();
    m_estimatedTime = CalculateEstimatedTime();
    m_isCancelled = false;
}


// ��ȡ˾������
CString Order::GetDriver() const
{
    return m_driver;
}

// ��ȡ�˿�����
CString Order::GetPassenger() const {
    return m_passenger;
}

// ��ȡ�������
double Order::GetDistance() const {
    return m_distance;
}

// ��ȡ�˵����
double Order::GetBillAmount() const {
    return m_billAmount;
}

// ��ȡԤ��ʣ��ʱ��
CString Order::GetEstimatedTime() const {
    return m_estimatedTime;
}

// ��鶩���Ƿ���ȡ��
bool Order::IsCancelled() const {
    return m_isCancelled;
}

// ȡ������
void Order::CancelOrder() {
    m_isCancelled = true;
}

// �����˵����
double Order::CalculateBillAmount() {
    // ������Ը��ݾ���ļƷѹ�����м���
    // ����ÿ�����շ� 10 Ԫ
    const double ratePerKilometer = 10.0;
    return m_distance * ratePerKilometer;
}

// ����Ԥ��ʣ��ʱ��
CString Order::CalculateEstimatedTime() {
    // ������Ը��ݾ����·�̺ͽ�ͨ������й���
    // ����ÿ������ʻ 1 ����
    const double speed = 1.0; // ����/����
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