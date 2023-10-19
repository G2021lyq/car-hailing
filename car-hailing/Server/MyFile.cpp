#include "pch.h"
#include "MyFile.h"

std::wstring& MyFile::GetFilePathAccount()
{
	return AccountFilePath;
	// TODO: 在此处插入 return 语句
}

CString& MyFile::GetPathAccount()
{
	return AccountPath;
	// TODO: 在此处插入 return 语句
}

void MyFile::SetFilePathAccount(std::wstring FilePath, CString _Path)
{
	this->Path = _Path;

	// 使用CreateDirectory函数创建目录
	std::wstring filePath = FilePath;
	if (CreateDirectory(filePath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
		//创建成功
	}
	else {
		//创建失败
	}
}

void MyFile::OpenFile()
{
	//打开读文件
	i_file.open(this->Path);
	//打开写文件
}

void MyFile::CloseFile()
{
	i_file.close();
}

void MyFile::ReStartFile()
{
	CloseFile();
	OpenFile();
}

CString MyFile::ReadLine()
{
	std::string line;
	if (std::getline(i_file, line)) {
		int len = MultiByteToWideChar(CP_ACP, 0, line.c_str(), -1, nullptr, 0);
		if (len == 0) {
			//返回空串
			return L"";
		}

		CString cstr;
		cstr.GetBuffer(len);
		MultiByteToWideChar(CP_ACP, 0, line.c_str(), -1, cstr.GetBuffer(), len);

		std::wstring a = cstr.GetString();
		cstr = a.c_str();
		return CString(cstr);
	}

	//如果读到末尾，返回空串
	return L"";

}

void MyFile::WriteLine(CString& unicodeString)
{
	CloseFile();
	w_file.open(CT2A(this->Path), std::ios::app);

	std::wstring a = unicodeString.GetString();
	unicodeString = a.c_str();
	// 将Unicode字符串转换为Ansi编码的Ansi字符串
	int length = unicodeString.GetLength();
	int requiredLength = WideCharToMultiByte(CP_ACP, 0, unicodeString, length, NULL, 0, NULL, NULL);
	if (requiredLength > 0) {
		char* ansiBuffer = new char[requiredLength];
		if (WideCharToMultiByte(CP_ACP, 0, unicodeString, length, ansiBuffer, requiredLength, NULL, NULL) > 0) {
			// 写入Ansi字符串到文件
			w_file.write(ansiBuffer, requiredLength);
			w_file << std::endl;
		}
		delete[] ansiBuffer;
	}
	w_file.close();
	OpenFile();
}

int MyFile::is_StringExistInFile(CString& searchString)
{
	CString Line;
	for (int i = 0;; i++)
	{
		Line = ReadLine();//读取一行数据
		if (Line == L"") {
			ReStartFile();
			return -1; //返回错误值
		}
		if (Line.Find(searchString) != -1)
		{
			ReStartFile();
			return i;//返回行号
		}
	}

}

CString MyFile::GetStringByNumber(int Number)
{
	CString m_String;
	for (int i = 0; i <= Number; i++)
	{
		m_String = ReadLine();
	}
	ReStartFile();
	return m_String;
}

void MyFile::DeleteStringByNumber(int Number)
{
	CString Line;
	std::vector<CString> Lines;
	for (int i = 0;; i++)
	{
		Line = ReadLine();
		if (Line == "") break;
		if (i == Number) continue;
		Lines.push_back(Line);
	}
	ReStartFile();
	w_file.open(Path, std::ios::trunc);
	w_file.close();
	for (CString m_item : Lines) {
		WriteLine(m_item);
	}
	ReStartFile();

}

void MyFile::ReplaceLineByNumber(int Number, CString& ReplcaString)
{
	CString Line;
	std::vector<CString> Lines;
	for (int i = 0;; i++)
	{
		Line = ReadLine();
		if (Line == "") break;
		if (i == Number) Line = ReplcaString;
		Lines.push_back(Line);
	}
	ReStartFile();
	w_file.open(Path, std::ios::trunc);
	w_file.close();
	for (CString m_item : Lines) {
		WriteLine(m_item);
	}
	ReStartFile();

}


