#include "pch.h"
#include "Order.h"

#include <cmath>

Order::Order()
{
}

Order::Order(const CString& passenger, double* start, double* end)
	: m_passenger(passenger) {
	//坐标赋值
	m_start[0] = start[0];
	m_start[1] = start[1];
	m_end[0] = end[0];
	m_end[1] = end[1];

	//计算两点的距离
	m_distance = sqrt(pow(m_end[0] - m_start[0], 2) + pow(m_end[1] - m_start[1], 2));
	//放缩倍数
	const double multiple = 5.0;
	//放缩
	m_distance = m_distance * multiple;
	//计算账单
	m_billAmount = CalculateBillAmount();
	//计算时间
	m_estimatedTime = CalculateEstimatedTime();

	m_isCancelled = false;
}


Order::Order(const CString& driver, const CString& passenger, double* start, double* end)
	: m_driver(driver), m_passenger(passenger), m_start(start), m_end(end) {
	// 在构造函数中初始化订单的各个属性

	//计算两点的距离
	m_distance = sqrt(pow(m_end[0] - m_start[0], 2) + pow(m_end[1] - m_start[1], 2));
	//放缩倍数
	const double multiple = 5.5;
	//放缩
	m_distance = m_distance * multiple;
	//计算账单
	m_billAmount = CalculateBillAmount();
	//计算时间
	m_estimatedTime = CalculateEstimatedTime();

	m_isCancelled = false;
}

//返回坐标
double* Order::GetStart()
{
	return m_start;
}
double* Order::GetEnd()
{
	return m_end;
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

// 获取距离
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
	const double ratePerKilometer_1 = 3.0;
	const double ratePerKilometer_2 = 2.0;
	const double ratePerKilometer_3 = 1.0;
	if (m_distance < 5)
		return 8;
	if (m_distance < 20)
		return 8 + (m_distance - 5) * ratePerKilometer_1;
	if (m_distance < 100)
		return 8 + 45 + (m_distance - 20) * ratePerKilometer_2;
	return 8 + 45 + 160 + (m_distance - 100) * ratePerKilometer_3;
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
	strOrder.Format(_T("Driver: %s, Passenger: %s, Start: %.2f, %.2f, End: %.2f, %.2f, Distance: %.2f km, Bill Amount: %.2f, Estimated Time: %s, Is Cancelled: %s"),
		m_driver, m_passenger, m_start[0], m_start[1], m_end[0], m_end[0], m_distance, m_billAmount, m_estimatedTime, m_isCancelled ? _T("Yes") : _T("No"));
	return strOrder;
}

void Order::FromCString(const CString& strOrder) {
	// 解析输入的字符串，以逗号和空格为分隔符
	CStringArray parts;
	int startPos = 0;
	int endPos = strOrder.Find(_T(','), startPos);

	while (endPos != -1) {
		parts.Add(strOrder.Mid(startPos, endPos - startPos));
		startPos = endPos + 2; // Skip the comma and space
		endPos = strOrder.Find(_T(','), startPos);
	}

	// 处理最后一个字段
	if (startPos < strOrder.GetLength()) {
		parts.Add(strOrder.Mid(startPos));
	}

	// 检查是否已取消
	m_isCancelled = (parts[9] == _T("Yes"));

	// 设置订单对象的各个属性
	m_driver = parts[0].Mid(parts[0].Find(_T(':')) + 2); // Skip "Driver: "
	m_passenger = parts[1].Mid(parts[1].Find(_T(':')) + 2); // Skip "Passenger: "
	m_start[0] = _tstof(parts[2].Mid(parts[2].Find(_T(':')) + 2)); // Skip "Start: "
	m_start[1] = _tstof(parts[3]);
	m_end[0] = _tstof(parts[4].Mid(parts[4].Find(_T(':')) + 2)); // Skip "End: "
	m_end[1] = _tstof(parts[5]);
	m_distance = _tstof(parts[6].Mid(parts[6].Find(_T(':')) + 2)); // Skip "Distance: "
	m_billAmount = _tstof(parts[7].Mid(parts[7].Find(_T(':')) + 2)); // Skip "Bill Amount: "
	m_estimatedTime = parts[8].Mid(parts[8].Find(_T(':')) + 2); // Skip "Estimated Time: "
}



Order& Order::operator=(const CString& strOrder) {
	FromCString(strOrder);
	return *this;
}