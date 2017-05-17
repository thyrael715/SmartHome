#include "FolderBrowser.h"
#include <codecvt>
#include <filesystem>
#include <iostream>


using namespace std;
using namespace std::tr2::sys;



FolderBrowser::FolderBrowser(void)
{
	this->Flags = BIF_USENEWUI;
	this->Owner = 0;
	this->Title = 0;
}


bool FolderBrowser::ShowDialog(void)
{
	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.hwndOwner = this->Owner;
	bi.lpszTitle = this->Title;
	bi.ulFlags = this->Flags;

	OleInitialize(NULL);

	LPITEMIDLIST pIDL = SHBrowseForFolder(&bi);

	if (pIDL == NULL)
	{
		return false;
	}

	TCHAR *buffer = new TCHAR[MAX_PATH];

	if (!SHGetPathFromIDList(pIDL, buffer) != 0)
	{
		CoTaskMemFree(pIDL);
		return false;
	}

	this->SelectedPath = buffer;

	CoTaskMemFree(pIDL);
	OleUninitialize();

	return true;
}


std::string FolderBrowser::getFolder() const
{
	std::vector<std::string> fileNames;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;

	return converter.to_bytes(this->SelectedPath);
}
