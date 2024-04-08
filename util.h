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
	if (l.getposition_x() < r.getposition_x())
		return true;
	else if (l.getposition_x() > r.getposition_x())
		return false;
	else 
		return l.getposition_y() < r.getposition_y(); // Secondary Sort by Y pos
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


std::vector<Object> normalise(std::vector<Object>& obj)
{
	if (obj.empty())
	{
		return obj;
	}

	std::vector<Object> normalised;

	sortLevel(obj);

	int x = obj[0].getposition_x();
	int y = obj[0].getposition_y();


	for (Object o : obj)
	{
		if (x > o.getposition_x())
		{
			x = o.getposition_x();
		}

		if (y > o.getposition_y())
		{
			y = o.getposition_y();
		}
	}


	for (Object object : obj)
	{
		object.setposition_x(object.getposition_x() - x);
		object.setposition_y(object.getposition_y() - y);

		normalised.emplace_back(object);
	}

	return normalised;
}
#endif