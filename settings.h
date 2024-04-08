#ifndef __SETTINGS__
#define __SETTINGS__

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

public:

	Settings() = default;

	~Settings() = default;

	static Settings* s_settings;
	static Settings* get();

	void LoadSettingsFile();

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