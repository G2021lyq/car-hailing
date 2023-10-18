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
	CString AccountFilePath = L"./Accounts.txt";
	CString HistoryFilePath = L"History.txt";
	CString filePath;
	std::ifstream i_file;//处理Ansi的
	CStdioFile w_file;//处理Unicode的

	//设置文件路径的
	void SetFilePath(CString& f_path);
	void WriteString(CString& text);
	CString ReadString();
	void OpenWriteFile();
	void ClosWriteFile();

public:
	void AccountSetFilePath();
	void HistorySetFilePath(CString& userName);
	void OpenReadFile();
	void CloseReadFile();
	void WriteAccount(CString& text);
	CString ReadAccount();

};

