// main.cpp
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define BUFSIZE 2048
using namespace std;

int main(int argc, char* argv[])
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	srand(static_cast<unsigned>(time(nullptr)));

	wchar_t chBuf[BUFSIZE];
	wchar_t Buf[BUFSIZE];


	DWORD len;
	HANDLE handle_read;
	HANDLE handle_write;

	//获取管道的读写
	handle_read = GetStdHandle(STD_INPUT_HANDLE);
	handle_write = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0;; i++) {
		// Read from standard input and stop on error or no data.
		bool ret = ReadFile(handle_read, chBuf, BUFSIZE, &len, NULL);

		memset(Buf, 0, BUFSIZE);
		int randomNumber = rand() % 9000 + 1000;
		wsprintf(Buf, L"%d", randomNumber);

		ret = WriteFile(handle_write, Buf, BUFSIZE, &len, NULL);
	}

	return 0;
}

