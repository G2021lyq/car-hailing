#pragma once

#include <afx.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>


class MyFile
{
private:
	//一些默认的文件路径
	std::wstring AccountFilePath = L"./Account";
	CString AccountPath = L".//Account//Accounts.txt";

	//应该保存的文件的路径
	CString Path;

	//文件本身
	std::ifstream i_file; //用于读文件
	std::ofstream w_file; //用于写文件

public:
	//得到文件路径
	std::wstring& GetFilePathAccount();
	CString& GetPathAccount();

	//设置文件路径
	void SetFilePathAccount(std::wstring FilePath, CString Path);

	void OpenFile();//打开文件：
	void CloseFile();//关闭文件
	void ReStartFile();//重启文件

	//读取一行
	CString ReadLine();

	//在末尾添加
	void WriteLine(CString& unicodeString);

	//判断某个字符串是否存在,如果存在返回它的行号
	int is_StringExistInFile(CString& searchString);

	//根据行号返回字符串
	CString GetStringByNumber(int Number);

	//将某一行号的字符串删除
	void DeleteStringByNumber(int Number);

	//将某一行号的字符串修改为指定内容
	void ReplaceLineByNumber(int Number, CString& ReplaceString);


};

