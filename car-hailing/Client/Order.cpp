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
	: m_driver(driver), m_passenger(passenger) {
	// 在构造函数中初始化订单的各个属性
		//坐标赋值
	m_start[0] = start[0];
	m_start[1] = start[1];
	m_end[0] = end[0];
	m_end[1] = end[1];

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

double* Order::getStart()
{
	return this->m_start;
}

double* Order::getEnd()
{
	return this->m_end;
}

void Order::SetDriver(CString driverStr)
{
	this->m_driver = driverStr;
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
	// 使用CString的Format方法将订单类的成员格式化为字符串
	CString strOrder;
	strOrder.Format(_T("%s#%s#%.2f#%.2f#%s#%d#%.2f#%.2f#%.2f#%.2f"),
		m_driver, m_passenger, m_distance, m_billAmount,
		m_estimatedTime, m_isCancelled, m_start[0], m_start[1], m_end[0], m_end[1]);

	return strOrder;
}

void Order::FromCString(const CString& strOrder) {
	// 使用Tokenize方法将CString字符串分割成多个子串
	CString str = strOrder;
	CString delimiter = _T("#");

	int pos = 0;
	CString token = str.Tokenize(delimiter, pos);
	m_driver = token;

	token = str.Tokenize(delimiter, pos);
	m_passenger = token;

	token = str.Tokenize(delimiter, pos);
	m_distance = _tstof(token);

	token = str.Tokenize(delimiter, pos);
	m_billAmount = _tstof(token);

	token = str.Tokenize(delimiter, pos);
	m_estimatedTime = token;

	token = str.Tokenize(delimiter, pos);
	m_isCancelled = (_tstoi(token) != 0);

	token = str.Tokenize(delimiter, pos);
	m_start[0] = _tstof(token);

	token = str.Tokenize(delimiter, pos);
	m_start[1] = _tstof(token);

	token = str.Tokenize(delimiter, pos);
	m_end[0] = _tstof(token);

	token = str.Tokenize(delimiter, pos);
	m_end[1] = _tstof(token);
}





Order& Order::operator=(const CString& strOrder) {
	FromCString(strOrder);
	return *this;
}