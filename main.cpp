#include <iostream>
#include "GJGameLevel.h"
#include "Parser.h"
#include <fstream>

#include "util.h"


int main(int argc, char** argv)
{

	auto str = ReadFile("6508283.gmd");
	auto a = parseLevelCompressed(str);
	
	for (auto b : a)
	{
		printf("ID: %i, Position: [%i, %i], flipped: [%i, %i], Rotation: %i\n", b.getobjectId(), b.getposition_x(), b.getposition_y(), b.getflip_x(), b.getflip_y(), b.getrotation());
	}

	return 1;
}