#pragma once

#include "afx.h"

class MyFile
{
private:
	CString filePath;
	CStdioFile file;

	void SetFilePath(CString f_path);

	bool OpenFile();
	bool OpenFile(CString f_path);

	void WriteString(CString textToAppend);

	void CloseFile();

public:
	void My_Try();

};

