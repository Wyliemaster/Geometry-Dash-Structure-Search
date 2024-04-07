#ifndef __UTIL__
#define __UTIL__

#include <fstream>
#include <algorithm>

#include "GJGameLevel.h"

std::string ReadFile(std::string path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

bool CompareHorizontalDistance(Level& l, Level& r)
{
	return l.getposition_x() < r.getposition_x();
}

void sortLevels(std::vector<Level>& levels)
{
	std::sort(levels.begin(), levels.end(), CompareHorizontalDistance);
}

#endif