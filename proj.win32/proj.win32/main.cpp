#include <iostream>
#include "Application.h"
#include "FileSystemUtils.h"


int main()
{
	Application* app = Application::create();
	
	//FileSystemUtils fd;
	//if (fd.showFolderDialog())
	//{
	//	auto files = fd.getFilesWithinFolder(fd.getFolderBrowser()->getFolder());

	//	for each (auto file in files)
	//	{
	//		std::cout << "directory_string = " << file.directory_string() << std::endl;
	//		std::cout << "branch_path = " << file.branch_path() << std::endl;
	//		std::cout << "filename = " << file.filename() << std::endl;
	//		std::cout << "parent_path = " << file.parent_path() << std::endl;
	//		std::cout << "relative_path = " << file.relative_path() << std::endl;
	//		std::cout << "root_directory = " << file.root_directory() << std::endl;
	//		std::cout << "root_name = " << file.root_name() << std::endl;
	//		std::cout << "root_path = " << file.root_path() << std::endl;
	//		std::cout << " =================================== \n";

	//	}
	//}

	//FolderBrowser* fb = FolderBrowser::getInstance();
	//
	//if (fb->ShowDialog())
	//{
	//	auto files = fb->getFileNames();

	//	for each (auto file in files)
	//	{
	//		std::cout << "FILENAME = " << file << std::endl;
	//	}
	//}


	app->run();

	delete app;

	return EXIT_SUCCESS;
}


//
//
///*
//id3dump: Print ID3 tags of files, scanned using libmpg123.
//
//copyright 2007 by the mpg123 project - free software under the terms of the LGPL 2.1
//see COPYING and AUTHORS files in distribution or http://mpg123.org
//initially written by Thomas Orgis
//*/
//
//#include "mpg123.h"
//#include <string.h>
//#include "stdio.h"
//#include "sys/types.h"
//
///* Helper for v1 printing, get these strings their zero byte. */
//void safe_print(char* name, char *data, size_t size)
//{
//	char safe[31];
//	if (size>30) return;
//
//	memcpy(safe, data, size);
//	safe[size] = 0;
//	printf("%s: %s\n", name, safe);
//}
//
///* Print out ID3v1 info. */
//void print_v1(mpg123_id3v1 *v1)
//{
//	safe_print("Title", v1->title, sizeof(v1->title));
//	safe_print("Artist", v1->artist, sizeof(v1->artist));
//	safe_print("Album", v1->album, sizeof(v1->album));
//	safe_print("Year", v1->year, sizeof(v1->year));
//	safe_print("Comment", v1->comment, sizeof(v1->comment));
//	printf("Genre: %i", v1->genre);
//}
//
///* Split up a number of lines separated by \n, \r, both or just zero byte
//and print out each line with specified prefix. */
//void print_lines(const char* prefix, mpg123_string *inlines)
//{
//	size_t i;
//	int hadcr = 0, hadlf = 0;
//	char *lines = NULL;
//	char *line = NULL;
//	size_t len = 0;
//
//	if (inlines != NULL && inlines->fill)
//	{
//		lines = inlines->p;
//		len = inlines->fill;
//	}
//	else return;
//
//	line = lines;
//	for (i = 0; i<len; ++i)
//	{
//		if (lines[i] == '\n' || lines[i] == '\r' || lines[i] == 0)
//		{
//			char save = lines[i]; /* saving, changing, restoring a byte in the data */
//			if (save == '\n') ++hadlf;
//			if (save == '\r') ++hadcr;
//			if ((hadcr || hadlf) && hadlf % 2 == 0 && hadcr % 2 == 0) line = "";
//
//			if (line)
//			{
//				lines[i] = 0;
//				printf("%s%s\n", prefix, line);
//				line = NULL;
//				lines[i] = save;
//			}
//		}
//		else
//		{
//			hadlf = hadcr = 0;
//			if (line == NULL) line = lines + i;
//		}
//	}
//}
//
///* Print out the named ID3v2  fields. */
//void print_v2(mpg123_id3v2 *v2)
//{
//	print_lines("Title: ", v2->title);
//	print_lines("Artist: ", v2->artist);
//	print_lines("Album: ", v2->album);
//	print_lines("Year: ", v2->year);
//	print_lines("Comment: ", v2->comment);
//	print_lines("Genre: ", v2->genre);
//}
//
///* Print out all stored ID3v2 fields with their 4-character IDs. */
//void print_raw_v2(mpg123_id3v2 *v2)
//{
//	size_t i;
//	for (i = 0; i<v2->texts; ++i)
//	{
//		char id[5];
//		memcpy(id, v2->text[i].id, 4);
//		id[4] = 0;
//		printf("%s\n", id);
//		print_lines(" ", &v2->text[i].text);
//	}
//	for (i = 0; i<v2->extras; ++i)
//	{
//		char id[5];
//		memcpy(id, v2->extra[i].id, 4);
//		id[4] = 0;
//		printf("%s description(%s)\n",
//			id,
//			v2->extra[i].description.fill ? v2->extra[i].description.p : "");
//		print_lines(" ", &v2->extra[i].text);
//	}
//	for (i = 0; i<v2->comments; ++i)
//	{
//		char id[5];
//		char lang[4];
//		memcpy(id, v2->comment_list[i].id, 4);
//		id[4] = 0;
//		memcpy(lang, v2->comment_list[i].lang, 3);
//		lang[3] = 0;
//		printf("%s description(%s) language(%s): \n",
//			id,
//			v2->comment_list[i].description.fill ? v2->comment_list[i].description.p : "",
//			lang);
//		print_lines(" ", &v2->comment_list[i].text);
//	}
//}
//
//int main()
//{
//	sf::Clock clock;
//	int i;
//	mpg123_handle* m;
//	
//	mpg123_init();
//	m = mpg123_new(NULL, NULL);
//
//
//	mpg123_id3v1 *v1;
//	mpg123_id3v2 *v2;
//	int meta;
//
//	const char* path = "Music/Oleg Kvasha - _Zelenoglazoe Taksi [Club Remix]_.mp3";
//
//	if (mpg123_open(m, path) != MPG123_OK)
//	{
//		fprintf(stderr, "Cannot open %s: %s\n", path, mpg123_strerror(m));
//		return 1;
//	}
//	mpg123_scan(m);
//	meta = mpg123_meta_check(m);
//
//	if (meta & MPG123_ID3 && mpg123_id3(m, &v1, &v2) == MPG123_OK)
//	{
//		printf("Tag data on %s:\n", path);
//		printf("\n====      ID3v1       ====\n");
//		if (v1 != NULL) print_v1(v1);
//
//		printf("\n====      ID3v2       ====\n");
//		if (v2 != NULL) print_v2(v2);
//
//		printf("\n==== ID3v2 Raw frames ====\n");
//		if (v2 != NULL) print_raw_v2(v2);
//	}
//	else
//		printf("Nothing found for %s.\n", path);
//
//	off_t length = mpg123_length(m);
//	std::cout << "\n\nlength = " << length << std::endl;
//
//	auto frameLength = mpg123_framelength(m);
//	auto frameDurationInSec = mpg123_tpf(m);
//
//	std::cout << "frameLength = " << frameLength << std::endl;
//	std::cout << "frameDurationInSec = " << frameDurationInSec << std::endl;
//
//	mpg123_close(m);
//
//	mpg123_delete(m);
//	mpg123_exit();
//
//	sf::Time deltaTime = clock.getElapsedTime();
//	std::cout << "deltaTime = " << deltaTime.asSeconds();
//
//
//	return 0;
//}