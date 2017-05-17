#include "FileSystemUtils.h"


using namespace std::tr2::sys;


FileSystemUtils::FileSystemUtils()
	: m_fileBrowser(nullptr)
	, m_folderBrowser(nullptr)
{
	m_fileBrowser = new FileBrowser();
	m_folderBrowser = new FolderBrowser();
}


FileBrowser* FileSystemUtils::getFileBrowser() const
{
	return m_fileBrowser;
}


FolderBrowser* FileSystemUtils::getFolderBrowser() const
{
	return m_folderBrowser;
}


bool FileSystemUtils::showFileDialog()
{
	return m_fileBrowser->ShowDialog();
}


bool FileSystemUtils::showFolderDialog()
{
	return m_folderBrowser->ShowDialog();
}


FileSystemUtils::DirectoryEntryList FileSystemUtils::getFilesWithinFolder(const std::string& dirPath) const
{
	FileSystemUtils::DirectoryEntryList files;

	for (recursive_directory_iterator i(dirPath.c_str()), end; i != end; ++i)
	{
		if (!is_directory(i->path()))
		{
			files.push_back(i->path());
		}
	}
	
	return files;
}