// DaemonApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <tchar.h>
#include "ProcessFunc.h"
#include <Shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")

#include "SimpleFileLog.h"
#include "common.h"


void DbgInfoA(std::string str)
{
	std::string strLog;
	strLog = GetTimeA();
	strLog.append(" ");
	strLog.append(str);
	OutputDebugStringA(strLog.c_str());
	CSimpleFileLog* pLog = CSimpleFileLog::GetIns();
	pLog->log(str.c_str());
}

void DbgInfoW(std::wstring str)
{
	std::string strLog = UnicodeToAnsi(str);
	DbgInfoA(strLog);
}


int main()
{
	//关闭交互
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//设置本地环境为中文
	setlocale(LC_ALL, "chs");
	//判断ini文件是否存在
	bool bExist = PathFileExists(L"./Setting.ini");
	wchar_t szBuf[MAX_PATH] = { 0 };
	//获取报错的名字
	::GetPrivateProfileString(L"AppSetting", L"CheckAppName", L"osk.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strCheckAppName = szBuf;
	//获取守护的名字
	::GetPrivateProfileString(L"AppSetting", L"RunAppName", L"Server.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strRunAppName = szBuf;
	//获取守护的路径（用于去打开守护的进程）
	::GetPrivateProfileString(L"AppSetting", L"AppFullPath", L"Server.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strAppFullPath = szBuf;
	//获取每次的休眠时间
	int nCycleTime = GetPrivateProfileIntW(L"AppSetting", L"CycleTime", 3000, L"./Setting.ini");
	if (nCycleTime < 3000)
		nCycleTime = 3000;

	//创建文件日志，日志类定义在SimpleFile.h
	CSimpleFileLog* pLog = CSimpleFileLog::GetIns();
	pLog->InitLogFile("DaemonApp-");
	pLog->log("\tStart");
	pLog->log(UnicodeToAnsi(strAppFullPath).c_str());

	//循环检查
	do
	{
		//检测两个进程是否存活
		bool bFind1 = FindProcessW(strCheckAppName);
		bool bFind2 = FindProcessW(strRunAppName);
		//如果报错没有出现，守护依然活着
		if (bFind1 == false && bFind2 == true)
		{
			DbgInfoW(L"未发现报错进程！");
			Sleep(nCycleTime);
			continue;
		}
		//如果报错出现
		if (bFind1)
		{
			DbgInfoW(L"关闭报错和卡死程序！");

			//使用两种方法关闭
			KillProcessW(strCheckAppName);
			KillProcessW(strRunAppName);
			TerminateApp(strCheckAppName);
			TerminateApp(strRunAppName);
			Sleep(nCycleTime);
			continue;
		}
		//如果守护没有活
		if (bFind2 == false)
		{
			//检测对应路径的文件是否存在
			if (PathFileExists(strAppFullPath.c_str()))
			{
				DbgInfoW(L"启动进程！");
				//使用shell的方法去打开进程
				ShellExecute(NULL, _T("open"), strAppFullPath.c_str(), _T("open"), NULL, SW_SHOWDEFAULT);
			}
			else {
				DbgInfoW(L"启动进程不存在！");
			}
			Sleep(nCycleTime);
			continue;
		}
		Sleep(nCycleTime);
	} while (1);

	return 0;
}
