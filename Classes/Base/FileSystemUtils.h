#pragma once

#include "FileBrowser.h"
#include "FolderBrowser.h"
#include <filesystem>



class FileSystemUtils
{
public:

	typedef std::list<std::tr2::sys::basic_directory_entry<std::tr2::sys::path>::path_type> DirectoryEntryList;

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