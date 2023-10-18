#include "pch.h"
#include "MyFile.h"

void MyFile::SetFilePath(CString& f_path)
{
	filePath = f_path;
}

void MyFile::WriteString(CString& text)
{
	// 打开文件以进行追加写入操作，使用ANSI编码方式
	// 将文件指针移到文件的末尾
	w_file.SeekToEnd();

	// 如果原文件不为空，写入一个换行符以保持原有格式
	if (w_file.GetPosition() > 0) {
		w_file.WriteString(_T("\n"));
	}

	// 将CString字符串转换为ANSI编码
	int textLength = text.GetLength();
	int bufferSize = WideCharToMultiByte(CP_ACP, 0, text, textLength, NULL, 0, NULL, NULL);
	char* ansiBuffer = new char[bufferSize];
	WideCharToMultiByte(CP_ACP, 0, text, textLength, ansiBuffer, bufferSize, NULL, NULL);

	// 将ANSI字符串写入文件
	w_file.Write(ansiBuffer, bufferSize);

	// 释放分配的内存
	delete[] ansiBuffer;
}

CString MyFile::ReadString()
{
	std::string line;
	if (std::getline(i_file, line)) {
		int len = MultiByteToWideChar(CP_ACP, 0, line.c_str(), -1, nullptr, 0);
		if (len == 0) {
			return L"";
		}

		CStringW cstr;
		cstr.GetBuffer(len);
		MultiByteToWideChar(CP_ACP, 0, line.c_str(), -1, cstr.GetBuffer(), len);

		return CString(cstr);
	}
	return L"";

}

void MyFile::OpenWriteFile()
{
	w_file.Open(filePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
}

void MyFile::ClosWriteFile()
{
	w_file.Close();
}

void MyFile::AccountSetFilePath()
{
	SetFilePath(AccountFilePath);
}

void MyFile::HistorySetFilePath(CString& userName)
{
	CString m_path;
	m_path.Format(L".//%s//%s", userName, HistoryFilePath);
	SetFilePath(m_path);
}

void MyFile::OpenReadFile()
{
	i_file.open(filePath);
}

void MyFile::CloseReadFile()
{
	i_file.close();
}

void MyFile::WriteAccount(CString& text)
{
	AccountSetFilePath();
	OpenWriteFile();
	WriteString(text);
}

CString MyFile::ReadAccount()
{
	return ReadString();
}

