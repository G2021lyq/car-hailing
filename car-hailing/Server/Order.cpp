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
CString GetDriver() const {
    return m_driver;
}

// ��ȡ�˿�����
CString GetPassenger() const {
    return m_passenger;
}

// ��ȡ�������
double GetDistance() const {
    return m_distance;
}

// ��ȡ�˵����
double GetBillAmount() const {
    return m_billAmount;
}

// ��ȡԤ��ʣ��ʱ��
CString GetEstimatedTime() const {
    return m_estimatedTime;
}

// ��鶩���Ƿ���ȡ��
bool IsCancelled() const {
    return m_isCancelled;
}

// ȡ������
void CancelOrder() {
    m_isCancelled = true;
}


CString m_driver;         // ˾��
CString m_passenger;      // �˿�
double m_distance;        // �������
double m_billAmount;      // �˵����
CString m_estimatedTime;  // Ԥ��ʣ��ʱ��
bool m_isCancelled;       // �Ƿ�ȡ������

// �����˵����
double CalculateBillAmount() {
    // ������Ը��ݾ���ļƷѹ�����м���
    // ����ÿ�����շ� 10 Ԫ
    const double ratePerKilometer = 10.0;
    return m_distance * ratePerKilometer;
}

// ����Ԥ��ʣ��ʱ��
CString CalculateEstimatedTime() {
    // ������Ը��ݾ����·�̺ͽ�ͨ������й���
    // ����ÿ������ʻ 1 ����
    const double speed = 1.0; // ����/����
    double estimatedTime = m_distance / speed;

    int hours = static_cast<int>(estimatedTime / 60);
    int minutes = static_cast<int>(estimatedTime) % 60;

    CString strEstimatedTime;
    strEstimatedTime.Format(_T("%dСʱ%d����"), hours, minutes);
    return strEstimatedTime;
}
