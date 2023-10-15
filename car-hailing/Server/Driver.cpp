#include "pch.h"
#include "Driver.h"

Driver::Driver(int& count) {
    // ��ʼ�����������
    //srand(static_cast<unsigned>(time(nullptr)));
    //std::cout << rand() << std::endl;


    // ����Ψһ�������ɵ� ID ֵ
    id = generateUniqueId(count);

    // ����������ͣ�1-3��
    carModel = generateRandomCarModel();

    // ���������ǰλ�ã�λ���� xy �����ʾ����Χ 0-20��
    //currentPositionX = generateRandomCoordinate(0, 20);
    //currentPositionY = generateRandomCoordinate(0, 20);
    // ע�����ɵ������ǰλ��Ӧ�������ͷ�Χ֮��
    //currentPositionX = generateRandomCoordinate(���ͷ�Χx1, ���ͷ�Χx2);
    //currentPositionY = generateRandomCoordinate(���ͷ�Χy1, ���ͷ�Χy2);

    // �������ͷ�Χ�����Ͻ���������½�����ķ��Σ�
    pickUpAreaLeftTopX = generateRandomCoordinate(0, 10);
    pickUpAreaLeftTopY = generateRandomCoordinate(0, 10);
    pickUpAreaRightBottomX = generateRandomCoordinate(11, 20);
    pickUpAreaRightBottomY = generateRandomCoordinate(11, 20);

    // ���������ǰλ�ã�λ���� xy �����ʾ����Χ ���ͷ�Χ��
    currentPositionX = generateRandomCoordinate(pickUpAreaLeftTopX, pickUpAreaRightBottomX);
    currentPositionY = generateRandomCoordinate(pickUpAreaLeftTopY, pickUpAreaRightBottomY);
}

// Getter �� Setter ����
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
    // ʵ������Ψһ ID ���߼�
    // �����ʹ��ʱ����������������ȷ�ʽ����Ψһ ID
    return count++; // ����ʾ������ 0����Ҫ���ݾ�������ʵ��
}

int Driver::generateRandomCarModel() {
    // ���� 1-3 ֮������������Ϊ����
    return rand() % 3 + 1;
}

int Driver::generateRandomCoordinate(int min, int max) {
    // ����ָ����Χ�ڵ��������
    return rand() % (max - min + 1) + min;
}


/*
    int main() {
        // �����洢˾�����������
        std::vector<Driver> drivers;

        // ����10��˾��������ӵ�������
        for (int i = 0; i < 10; ++i) {
            Driver driver;
            drivers.push_back(driver);
        }

        // ����˾��������������������
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


