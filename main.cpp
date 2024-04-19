#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>

#include "GJGameLevel.h"
#include "Parser.h"
#include "util.h"
#include "structure.h"

void writeToLogFile(int threadID, const std::string& logMessage) {
	std::string fileName = "log_" + std::to_string(threadID) + ".txt";
	std::ofstream file(fileName, std::ios::app);
	if (file.is_open()) {
		file << logMessage << std::endl;
		file.close();
	}
	else {
		std::cerr << "Failed to open file: " << fileName << ": " << logMessage << "\n";
	}
}

std::vector<std::vector<std::string>> splitVector(const std::vector<std::string>& vec, size_t n) {
	std::vector<std::vector<std::string>> result;
	result.reserve(n);

	size_t chunkSize = vec.size() / n;
	size_t remainder = vec.size() % n;

	size_t startIndex = 0;

	for (size_t i = 0; i < n; ++i) {
		size_t chunkLength = chunkSize;

		if (remainder > 0) {
			chunkLength++;
			remainder--;
		}

		result.emplace_back(std::vector<std::string>(vec.begin() + startIndex, vec.begin() + startIndex + chunkLength));

		startIndex += chunkLength;
	}

	return result;
}

// Used in threads for faster processing
void processLevels(std::vector<std::string> paths, std::vector<ObjectCollection> structures, const int THREAD_ID)
{
	// For progress logging
	const int LEVELS_IN_VEC = paths.size();
	int counter = 0;
	for (std::string& path : paths)
	{
		counter++;

		if (counter % Settings::get()->LEVEL_INTERVAL == 0)
		{
			printf("Thread %d: %d / %d\n", THREAD_ID, counter, LEVELS_IN_VEC);
		}

		std::string level = ReadFile(path);

		std::vector<Object> parsed;

		// Checking the format of the level string
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
				normalise(structures[Settings::get()->STRUCTURE_INDEX]),
				normalise(obj)
			);

			if ( score > Settings::get()->SIMULARITY_THRESHOLD )
			{
				std::stringstream log;
				log << path.c_str() << " contained a Simularity score of " << score;
				printf("%sLevel Path: %s\nScore: %f\n%s", LOG_DIVIDER, path.c_str(), score, LOG_DIVIDER);
				writeToLogFile(THREAD_ID, log.str());
			}
		}

		// cleanup
		parsed.clear();

		for (std::vector<Object>& vec : parsed_obj)
		{
			vec.clear();
		}
		parsed_obj.clear();
	}

	printf("%sThread %d has finished\n%s", LOG_DIVIDER, THREAD_ID, LOG_DIVIDER);
}

int main(int argc, char** argv)
{
	printf("Geometry Dash Structure Search\n");
	printf("Author: Wylie\n%s", LOG_DIVIDER);
	Settings::get()->LoadSettingsFile();

	if (!Settings::get()->HAS_LOADED)
	{
		return 0;
	}

	auto structure = ReadFile("structure.txt");

	if (structure.empty())
	{
		printf("ERROR: No `structure.txt` content found\n");
		return 0;
	}

	auto struct_data = parseLevelCompressed(structure);
	sortLevel(struct_data);
	auto struct_obj = structure::getStructures(struct_data);

	std::vector<std::string> paths;

	if (Settings::get()->FOLDER_MODE)
	{
		paths = getAllFilesInDirectory("levels/");
	}
	else
	{
		auto levels = ReadFile("levels.txt");
		paths = split(levels, ",");
	}

	printf("Number of threads: %d\n", Settings::get()->THREADS);
	printf("Number of levels to analyse: %zu\n%s", paths.size(), LOG_DIVIDER);


	std::vector<std::thread> threads;
	threads.reserve(Settings::get()->THREADS);

	std::vector<std::vector<std::string>> path_data = splitVector(paths, Settings::get()->THREADS);

	for (size_t i = 0; i < Settings::get()->THREADS; i++)
	{
		threads.emplace_back(std::thread(processLevels, path_data[i], struct_obj, i + 1));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	return 1;
}