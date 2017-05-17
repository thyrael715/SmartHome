#pragma once

#include <Windows.h>
#include <Shlobj.h>
#include <Commdlg.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <vector>

#pragma comment(lib, "Shell32.lib")


class FolderBrowser
{
public:

	FolderBrowser(void);

	bool ShowDialog();
	std::string getFolder() const;

	int		Flags;
	HWND	Owner;
	TCHAR*	SelectedPath;
	TCHAR*	Title;
};
