#include <iostream>
#include "GJGameLevel.h"
#include "Parser.h"
#include <fstream>

#include "util.h"
#include "structure.h"


int main(int argc, char** argv)
{
	printf("Running Program...\n");
	Settings::get()->LoadSettingsFile();

	auto levels = ReadFile("levels.txt");
	auto structure = ReadFile("structure.txt");
	auto struct_data = parseLevelCompressed(structure);
	sortLevel(struct_data);
	auto struct_obj = structure::getStructures(struct_data);

	auto paths = split(levels, ",");

	for (auto path : paths)
	{
		auto level = ReadFile(path);

		std::vector<Object> parsed;

		if (level[0] == 'k')
		{
			parsed = parseLevel(level);
		}
		else
		{
			parsed = parseLevelCompressed(level);
		}
		sortLevel(parsed);
		auto parsed_obj = structure::getStructures(parsed);

		for (auto obj : parsed_obj)
		{
			float score = structure::compareStructures(
				normalise(struct_obj[3]),
				normalise(obj)
			);

			if (score > Settings::get()->SIMULARITY_THRESHOLD)
			{
				printf("Level Path: %s\nScore: %f\n=====\n", path, score);
			}
		}

	}


	return 1;
}