#pragma once

#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>
#include <vector>


class FileBrowser
{
public:

	FileBrowser(void);

	TCHAR* DefaultExtension;
	TCHAR* FileName;
	TCHAR* Filter;
	int FilterIndex;
	int Flags;
	TCHAR*InitialDir;
	HWND Owner;
	TCHAR*Title;

	bool ShowDialog();

	std::vector<std::string> getFileNamesWithFolder() const;
	std::vector<std::string> getFileNamesWithoutFolder() const;
	
private:

	OPENFILENAME* m_ofn;
	std::string m_rootFolder;
};