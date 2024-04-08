#include <iostream>
#include "GJGameLevel.h"
#include "Parser.h"
#include <fstream>

#include "util.h"
#include "structure.h"


int main(int argc, char** argv)
{

	auto str = ReadFile("test.gmd");
	auto a = parseLevelCompressed(str);
	sortLevel(a);
	
	auto s = structure::getStructures(a);	
	printf("Structures Found: %s", s.size());

	return 1;
}