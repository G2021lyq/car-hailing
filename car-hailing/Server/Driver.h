#pragma once
#include <iostream>
#include <cstdlib> // �������������
#include <ctime>   // ������������
#include <vector>

class Driver {
public:
    Driver(int& count);

    // Getter �� Setter ����
    int getId();

    int getCarModel();

    void setCarModel(int model);

    int getCurrentPositionX();

    int getCurrentPositionY();

    void setCurrentPosition(int x, int y);

    int getPickUpAreaLeftTopX();

    int getPickUpAreaLeftTopY();

    int getPickUpAreaRightBottomX();

    int getPickUpAreaRightBottomY();

    void setPickUpArea(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);

private:
    int id;
    int carModel;
    int currentPositionX;
    int currentPositionY;
    int pickUpAreaLeftTopX;
    int pickUpAreaLeftTopY;
    int pickUpAreaRightBottomX;
    int pickUpAreaRightBottomY;

    int generateUniqueId(int& count);

    int generateRandomCarModel();

    int generateRandomCoordinate(int min, int max);
};
