#include "FileBrowser.h"
#include <codecvt>
#include <iostream>

FileBrowser::FileBrowser(void)
{
	this->DefaultExtension = 0;
	this->FileName = new TCHAR[MAX_PATH];
	this->Filter = 0;
	this->FilterIndex = 0;
	this->Flags = /*OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;*/ OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	this->InitialDir = 0;
	this->Owner = 0;
	this->Title = 0;
}


bool FileBrowser::ShowDialog()
{
	if (m_ofn)
		delete m_ofn;

	m_ofn = new OPENFILENAME();

	ZeroMemory(m_ofn, sizeof(*m_ofn));

	m_ofn->lStructSize = sizeof(*m_ofn);
	m_ofn->hwndOwner = this->Owner;
	m_ofn->lpstrDefExt = this->DefaultExtension;
	m_ofn->lpstrFile = this->FileName;
	m_ofn->lpstrFile[0] = '\0';
	m_ofn->nMaxFile = MAX_PATH;
	m_ofn->lpstrFilter = this->Filter;
	m_ofn->nFilterIndex = this->FilterIndex;
	m_ofn->lpstrInitialDir = this->InitialDir;
	m_ofn->lpstrTitle = this->Title;
	m_ofn->Flags = this->Flags;

	GetOpenFileName(m_ofn);

	if (_tcslen(this->FileName) == 0)
		return false;

	return true;
}


std::vector<std::string> FileBrowser::getFileNamesWithFolder() const
{
	std::vector<std::string> resVec;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;

	wchar_t* str = this->FileName;
	std::wstring dirOrFullpath = str;
	resVec.push_back(converter.to_bytes(dirOrFullpath));

	str += (dirOrFullpath.length() + 1);

	while (*str)
	{
		std::wstring filename = str;
		str += (filename.length() + 1);
		resVec.push_back(converter.to_bytes(dirOrFullpath) + "\\" + converter.to_bytes(filename));
	}

	if (resVec.size() > 1)
	{
		resVec.erase(resVec.begin());
	}

	return resVec;
}
