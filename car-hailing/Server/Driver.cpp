#include "pch.h"
#include "Driver.h"

Driver::Driver()
{
}

Driver::Driver(int& count) {
	id = generateUniqueId(count);
	srand(static_cast<unsigned int>(time(nullptr))); // 使用当前时间作为种子
	// 生成随机车型（1-3）
	carModel = generateRandomCarModel();

	// 生成拉客范围（左上角坐标和右下角坐标的方形）
	pickUpAreaLeftTopX = generateRandomCoordinate(1, 19 - 5);
	pickUpAreaLeftTopY = generateRandomCoordinate(1, 14 - 5);
	pickUpAreaRightBottomX = generateRandomCoordinate(pickUpAreaLeftTopX + 1, 20 - 5);
	pickUpAreaRightBottomY = generateRandomCoordinate(pickUpAreaLeftTopY + 1, 15 - 5);
	srand(static_cast<unsigned int>(time(nullptr))); // 使用当前时间作为种子
	// 生成随机当前位置（位置用 xy 坐标表示，范围 拉客范围）
	currentPositionX = generateRandomCoordinate(pickUpAreaLeftTopX, pickUpAreaRightBottomX);
	currentPositionY = generateRandomCoordinate(pickUpAreaLeftTopY, pickUpAreaRightBottomY);
}

// Getter 和 Setter 函数
int Driver::getId() {
	return id;
}

int Driver::getCarModel() {
	return carModel;
}

void Driver::setCarModel(int model) {
	carModel = model;
}

int Driver::getCurrentPositionX() {
	return currentPositionX;
}

int Driver::getCurrentPositionY() {
	return currentPositionY;
}

void Driver::setCurrentPosition(int x, int y) {
	currentPositionX = x;
	currentPositionY = y;
}

int Driver::getPickUpAreaLeftTopX() {
	return pickUpAreaLeftTopX;
}

int Driver::getPickUpAreaLeftTopY() {
	return pickUpAreaLeftTopY;
}

int Driver::getPickUpAreaRightBottomX() {
	return pickUpAreaRightBottomX;
}

int Driver::getPickUpAreaRightBottomY() {
	return pickUpAreaRightBottomY;
}

void Driver::setPickUpArea(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY) {
	pickUpAreaLeftTopX = leftTopX;
	pickUpAreaLeftTopY = leftTopY;
	pickUpAreaRightBottomX = rightBottomX;
	pickUpAreaRightBottomY = rightBottomY;
}



int Driver::generateUniqueId(int& count) {
	// 实现生成唯一 ID 的逻辑
	// 你可以使用时间戳、自增计数器等方式生成唯一 ID
	return count++; // 这里示例返回 0，需要根据具体需求实现
}

int Driver::generateRandomCarModel() {
	// 生成 1-3 之间的随机整数作为车型
	return rand() % 3 + 1;
}

int Driver::generateRandomCoordinate(int min, int max) {
	// 生成指定范围内的随机坐标
	return rand() % (max - min + 1) + min;
}

CString Driver::ToString() {
	CString str;
	str.Format(_T("Driver ID: %d, Car Model: %d, Current Position: (%d, %d), Pick Up Area: (%d, %d) - (%d, %d)"),
		id, carModel, currentPositionX, currentPositionY,
		pickUpAreaLeftTopX, pickUpAreaLeftTopY, pickUpAreaRightBottomX, pickUpAreaRightBottomY);
	return str;
}

Driver Driver::FromCString(CString str) {
	int count = 0;
	Driver driver(count);  // 使用默认的构造函数创建一个Driver实例
	int scanned = _stscanf_s(str, _T("Driver ID: %d, Car Model: %d, Current Position: (%d, %d), Pick Up Area: (%d, %d) - (%d, %d)"),
		&driver.id, &driver.carModel, &driver.currentPositionX, &driver.currentPositionY,
		&driver.pickUpAreaLeftTopX, &driver.pickUpAreaLeftTopY, &driver.pickUpAreaRightBottomX, &driver.pickUpAreaRightBottomY);
	if (scanned != 8) {
		// 处理解析失败的情况
		// 可以抛出异常或者返回一个默认值
	}
	return driver;
}

Driver& Driver::operator=(const CString& str) {
	// 使用FromCString函数将CString转换为Driver实例
	*this = FromCString(str);
	return *this;
}


