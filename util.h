#ifndef __UTIL__
#define __UTIL__

#include <fstream>

std::string ReadFile(std::string path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

#endif