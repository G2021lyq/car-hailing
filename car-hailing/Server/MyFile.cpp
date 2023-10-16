#include "pch.h"
#include "MyFile.h"

void MyFile::SetFilePath(CString f_path)
{
	filePath = f_path;
}

bool MyFile::OpenFile()
{
	return file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::modeNoTruncate);
}

bool MyFile::OpenFile(CString f_path)
{
	SetFilePath(f_path);
	return OpenFile();
}

void MyFile::WriteString(CString textToAppend)
{
	CStringW Str(textToAppend);
	file.WriteString(Str);
}

void MyFile::CloseFile()
{
	file.Close();
}

void MyFile::My_Try()
{

	//return TRUE;
}
