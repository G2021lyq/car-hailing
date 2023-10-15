#include "pch.h"
#include "Driver.h"

Driver::Driver(int& count) {
    // 初始化随机数种子
    //srand(static_cast<unsigned>(time(nullptr)));
    //std::cout << rand() << std::endl;


    // 生成唯一按序生成的 ID 值
    id = generateUniqueId(count);

    // 生成随机车型（1-3）
    carModel = generateRandomCarModel();

    // 生成随机当前位置（位置用 xy 坐标表示，范围 0-20）
    //currentPositionX = generateRandomCoordinate(0, 20);
    //currentPositionY = generateRandomCoordinate(0, 20);
    // 注意生成的随机当前位置应该在拉客范围之内
    //currentPositionX = generateRandomCoordinate(拉客范围x1, 拉客范围x2);
    //currentPositionY = generateRandomCoordinate(拉客范围y1, 拉客范围y2);

    // 生成拉客范围（左上角坐标和右下角坐标的方形）
    pickUpAreaLeftTopX = generateRandomCoordinate(0, 10);
    pickUpAreaLeftTopY = generateRandomCoordinate(0, 10);
    pickUpAreaRightBottomX = generateRandomCoordinate(11, 20);
    pickUpAreaRightBottomY = generateRandomCoordinate(11, 20);

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



int Driver::generateUniqueId(int &count) {
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


/*
    int main() {
        // 创建存储司机对象的向量
        std::vector<Driver> drivers;

        // 生成10个司机对象并添加到向量中
        for (int i = 0; i < 10; ++i) {
            Driver driver;
            drivers.push_back(driver);
        }

        // 遍历司机对象向量并访问属性
        for (Driver& driver : drivers) {
            std::cout << "Driver ID: " << driver.getId() << std::endl;
            std::cout << "Car Model: " << driver.getCarModel() << std::endl;
            std::cout << "Current Position: (" << driver.getCurrentPositionX() << ", " << driver.getCurrentPositionY() << ")" << std::endl;
            std::cout << "Pick-up Area: (" << driver.getPickUpAreaLeftTopX() << ", " << driver.getPickUpAreaLeftTopY() << ") - (" << driver.getPickUpAreaRightBottomX() << ", " << driver.getPickUpAreaRightBottomY() << ")" << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
        //Driver driver1;
        //Driver driver2;

        return 0;
    }
*/


