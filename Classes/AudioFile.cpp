#include "AudioFile.h"


AudioFile::AudioFile(const std::string &filename)
	: m_fileName("")
	, m_fullName("")
	, m_title("")
	, m_artist("")
	, m_album("")
	, m_year(0)
	, m_duration(sf::Time::Zero)
{
	openFromFile(filename);
}


AudioFile::~AudioFile()
{ 
	this->stop();
}


bool AudioFile::openFromFile(const std::string &filename)
{
	m_fileName = filename;

	//if (sf::Music::openFromFile(m_fileName))
	//{
	//	initInternalData();
	//	return true;
	//}

	try
	{
		if (sfe::Mp3::OpenFromFile(m_fileName))
		{
			initInternalData();
			return true;
		}
	}
	catch (...)
	{
		// TODO: cannot be opened
	}
	
	return false;
}


std::string AudioFile::getFileExtension() const
{
	auto ext = m_fileName.substr(m_fileName.rfind(".") + 1);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	return ext;
}


std::string AudioFile::getFileNameWithoutExt() const
{
	// the result without +1 would be = "\\<audio file name>"
	size_t start = m_fileName.rfind("\\") + 1;
	size_t end = (m_fileName.rfind(".")) - start;

	std::string retVal = m_fileName.substr(start, end);
	
	return retVal;
}


void AudioFile::initInternalData()
{
	if (!m_fileName.empty())
	{
		m_fullName = getFileNameWithoutExt();

		// Read Mp3 file and fill member variables

		mpg123_handle* m;	
		mpg123_id3v1 *v1 = nullptr;
		mpg123_id3v2 *v2 = nullptr;
		int meta;

		mpg123_init();
		m = mpg123_new(NULL, NULL);

		if (mpg123_open(m, m_fileName.c_str()) != MPG123_OK)
		{
			fprintf(stderr, "Cannot open %s: %s\n", m_fileName.c_str(), mpg123_strerror(m));
		}
		else
		{
			mpg123_scan(m);

			mpg123_scan(m);
			meta = mpg123_meta_check(m);

			if (meta & MPG123_ID3 && mpg123_id3(m, &v1, &v2) == MPG123_OK)
			{
				if (v2 != nullptr)
				{
					if (v2->title)
						m_title = std::string(v2->title->p, v2->title->size);

					if (v2->artist)
						m_artist = std::string(v2->artist->p, v2->artist->size);

					if (v2->album)
						m_album = std::string(v2->album->p, v2->album->size);
					
					if (v2->year)
						m_year = (unsigned short)(atoi(std::string(v2->year->p, v2->year->size).c_str()));					
				}
			}
			
			if (getFileExtension() == "mp3")
			{
				auto frameNum = mpg123_framelength(m);
				auto frameDurationInSec = mpg123_tpf(m);

				m_duration = sf::microseconds((sf::Int32)(frameNum * frameDurationInSec * 1000000));
			}
			else
			{
				//m_internalData.duration = sf::Music::getDuration();
				m_duration = sf::seconds(0);
			}

			mpg123_close(m);
			mpg123_delete(m);
			mpg123_exit();
		}
	}
}
