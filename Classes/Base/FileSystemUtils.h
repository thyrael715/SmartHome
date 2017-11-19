#pragma once

#include "FileBrowser.h"
#include "FolderBrowser.h"
#include <filesystem>

using namespace std::tr2::sys;



class FileSystemUtils
{

public:

	typedef std::list<basic_directory_entry<path>::path_type> DirectoryEntryList;

public:

	FileSystemUtils();

	bool showFolderDialog();
	bool showFileDialog();
	
	FileBrowser* getFileBrowser() const;
	FolderBrowser* getFolderBrowser() const;

	DirectoryEntryList getFilesWithinFolder(const std::string& dirPath) const;

private:

	FileBrowser* m_fileBrowser;
	FolderBrowser* m_folderBrowser;
};