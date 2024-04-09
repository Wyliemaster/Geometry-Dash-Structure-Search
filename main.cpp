#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

#include "GJGameLevel.h"
#include "Parser.h"
#include "util.h"
#include "structure.h"

void writeToLogFile(int threadID, const std::string& logMessage) {
	// Create a stringstream to construct the file name
	std::stringstream ss;
	ss << "log_" << threadID << ".txt";
	std::string fileName = ss.str();

	// Create a mutex to ensure thread safety
	static std::mutex fileMutex;

	// Acquire the lock to write to the file
	std::lock_guard<std::mutex> lock(fileMutex);

	// Open the file in append mode
	std::ofstream file(fileName, std::ios::app);
	if (file.is_open()) {
		file << logMessage << std::endl;
		file.close();
	}
	else {
		std::cerr << "Failed to open file: " << fileName << std::endl;
	}
}

// Stolen from ChatGPT
std::vector<std::vector<std::string>> splitVector(const std::vector<std::string>& vec, size_t n) {
	std::vector<std::vector<std::string>> result;

	// Calculate the size of each smaller vector
	size_t chunkSize = vec.size() / n;
	size_t remainder = vec.size() % n; // Handle any remaining elements

	// Starting index for each chunk
	size_t startIndex = 0;

	for (size_t i = 0; i < n; ++i) {
		size_t chunkLength = chunkSize + (remainder-- > 0 ? 1 : 0); // Add remainder to first chunks

		// Create a smaller vector from the original vector
		result.push_back(std::vector<std::string>(vec.begin() + startIndex, vec.begin() + startIndex + chunkLength));

		// Update the start index for the next chunk
		startIndex += chunkLength;
	}

	return result;
}
void processLevels(std::vector<std::string> paths, std::vector<ObjectCollection> structures, const int THREAD_ID)
{
	for (std::string& path : paths)
	{
		std::string level = ReadFile(path);

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
				normalise(structures[Settings::get()->STRUCTURE_INDEX]),
				normalise(obj)
			);

			if ( score > Settings::get()->SIMULARITY_THRESHOLD )
			{
				std::stringstream log;
				log << path.c_str() << " contained a Simularity score of " << score;
				printf("Level Path: %s\nScore: %f\n%s", path.c_str(), score, LOG_DIVIDER);
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
}

int main(int argc, char** argv)
{
	printf("Running Program...\n");
	Settings::get()->LoadSettingsFile();

	auto structure = ReadFile("structure.txt");
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

	printf("Number of levels to analyse: %d\n%s", paths.size(), LOG_DIVIDER);

	std::vector<std::thread> threads;
	std::vector<std::vector<std::string>> path_data = splitVector(paths, Settings::get()->THREADS);

	for (size_t i = 0; i < Settings::get()->THREADS; i++)
	{
		threads.push_back(std::thread(processLevels, path_data[i], struct_obj, i + 1));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}





	return 1;
}