#ifndef __UTIL__
#define __UTIL__

#include <fstream>
#include <algorithm>

#include "GJGameLevel.h"
#include "settings.h"

std::string ReadFile(std::string path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

bool DistanceSort(Object& l, Object& r)
{
	// First compare x positions
	if (l.getposition_x() < r.getposition_x())
		return true;
	else if (l.getposition_x() > r.getposition_x())
		return false;
	else // If x positions are equal, compare y positions
		return l.getposition_y() < r.getposition_y();
}

void sortLevel(std::vector<Object>& level)
{
	std::sort(level.begin(), level.end(), DistanceSort);
}

bool isLevelCorrectVersion(std::vector<Object>& level)
{
	if ( !Settings::get()->VERSION_CHECK )
	{
		return true;
	}

	bool correctVersion = true;
	for (Object obj : level)
	{
		if ( obj.getposition_x() > Settings::get()->LEVEL_LENGTH_LIMIT )
		{
			correctVersion = false;
		}

		if ( obj.getrotation() % 90 != 0 && Settings::get()->CHECK_90_DEGREES )
		{
			correctVersion = false;
		}
	}

	return correctVersion;
}

#endif