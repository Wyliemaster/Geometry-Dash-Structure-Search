#include <iostream>
#include "GJGameLevel.h"
#include "Parser.h"
#include <fstream>

#include "util.h"


int main(int argc, char** argv)
{

	auto str = ReadFile("10000046.gmd");
	auto a = parseLevelCompressed(str);
	sortLevel(a);
	
	bool correct = isLevelCorrectVersion(a);

	for (auto &b : a)
	{
		printf("ID: %i, Position: [%i, %i], flipped: [%i, %i], Rotation: %i\n", b.getobjectId(), b.getposition_x(), b.getposition_y(), b.getflip_x(), b.getflip_y(), b.getrotation());
	}

	printf("1.6 <=: %s", correct ? "True" : "False");

	return 1;
}