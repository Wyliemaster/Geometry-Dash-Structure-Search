#ifndef __SETTINGS__
#define __SETTINGS__

#include <memory>

#include "Parser.h"
#include "util.h"

#define LOG_DIVIDER "==================================\n"
// Increased size by 10% due to float rounding issues
#define GRID_SQUARE_UNIT 33

class Settings
{
public:

	bool HAS_LOADED = false;

	// This will make sure to check the level for update 1.6
	bool VERSION_CHECK = true;


	// This will be used for relative threshold.
	// The bigger this number, the less accuracy
	float OBJECT_SIZE = 1 * GRID_SQUARE_UNIT;

	// Apparently, Update 1.6 supported 360 Degree rotations
	// However, the editor did not allow the user to do it
	// Unless the level was made using hacks, all objects
	// should be at 90 degree angles
	bool CHECK_90_DEGREES = true;
		
		
	// 1.6 Length Limit
	int LEVEL_LENGTH_LIMIT = 1000 * 30;

	float SIMULARITY_THRESHOLD = 0.75f;

	int STRUCTURE_INDEX = 0;

	bool FOLDER_MODE = true;

	unsigned int THREADS = 1;

	unsigned int LEVEL_INTERVAL = 50;

	unsigned int OBJECT_LIMIT = 40000;

public:
	static Settings* get() {
		static std::unique_ptr<Settings> s_settings(new Settings());
		return s_settings.get();
	}

	Settings() = default;

	~Settings() = default;

	void LoadSettingsFile()
	{
		std::ifstream t("settings.csv");

		if (!t.good())
		{
			printf("ERROR: unable to locate `settings.csv`\n");
			return;
		}

		std::string conf((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		auto lines = split(conf, "\n");

		t.close();


		const unsigned int CONFIG_NO = 8;
		if (lines.size() < CONFIG_NO)
		{
			printf("ERROR: Missing %zu configurations from `settings.csv`\n", CONFIG_NO - lines.size());
			return;
		}

		auto vCheck = split(lines[0], ",");
		auto gSquare = split(lines[1], ",");
		auto rotate = split(lines[2], ",");
		auto similar = split(lines[3], ",");
		auto struct_id = split(lines[4], ",");
		auto folder = split(lines[5], ",");
		auto thread = split(lines[6], ",");
		auto interval = split(lines[7], ",");
		auto obj_limit = split(lines[8], ",");



		this->VERSION_CHECK = vCheck[0] == "true";
		this->OBJECT_SIZE = std::stof(gSquare[0]) * GRID_SQUARE_UNIT;
		this->CHECK_90_DEGREES = rotate[0] == "true";
		this->SIMULARITY_THRESHOLD = std::stof(similar[0]);
		this->STRUCTURE_INDEX = std::stoi(struct_id[0]);
		this->FOLDER_MODE = folder[0] == "true";
		this->THREADS = std::stoi(thread[0]);
		this->LEVEL_INTERVAL = std::stoi(interval[0]);
		this->OBJECT_LIMIT = std::stoi(obj_limit[0]);
		this->HAS_LOADED = true;
	}

private:

};

#endif