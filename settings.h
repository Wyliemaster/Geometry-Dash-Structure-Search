#ifndef __SETTINGS__
#define __SETTINGS__

#include "Parser.h"
#include "util.h"

// Increased size by 10% due to float rounding issues
#define GRID_SQUARE_UNIT 33

class Settings
{
public:

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

public:

	Settings() = default;

	~Settings() = default;

	static Settings* s_settings;
	static Settings* get();

	void LoadSettingsFile()
	{
		std::ifstream t("settings.csv");
		std::string conf((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		auto lines = split(conf, "\n");

		auto vCheck = split(lines[0], ",");
		auto gSquare = split(lines[1], ",");
		auto rotate = split(lines[2], ",");
		auto similar = split(lines[3], ",");

		this->VERSION_CHECK = vCheck[0] == "true";
		this->OBJECT_SIZE = std::stof(gSquare[0]) * GRID_SQUARE_UNIT;
		this->CHECK_90_DEGREES = rotate[0] == "true";
		this->SIMULARITY_THRESHOLD = std::stof(similar[0]);

	}

private:

};

Settings* Settings::s_settings = nullptr;
Settings* Settings::get()
{
	if (s_settings == nullptr)
	{
		s_settings = new Settings();
	}
	return s_settings;
}
#endif