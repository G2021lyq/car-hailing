#pragma once
#include <iostream>
#include <cstdlib> // 用于随机数生成
#include <ctime>   // 用于种子生成
#include <vector>
#include <afxstr.h>  // 用于CString

class Driver {
public:
	Driver();
	Driver(int& count);

	// Getter 和 Setter 函数
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

	CString ToString();
	Driver FromCString(CString str);
	//重载赋值运算
	Driver& operator=(const CString& str);

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
