#pragma once

#include <string>

#ifdef GetCurrentDir

#elif _WIN64
#include <direct.h>
#define GetCurrentDir _getcwd
#elif _linux_
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

static std::string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}