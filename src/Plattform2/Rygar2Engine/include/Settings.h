#pragma once
#include <unordered_map>
#include <string>
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768
#define GRAVITY 0.20f
#define MAP_CHUNK_SIZE 3000
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MAP_WIDTH 25
#define MAP_HEIGHT 25
#define CHUNK_WIDTH (MAP_WIDTH*TILE_WIDTH)
#define CHUNK_HEIGHT (MAP_HEIGHT*TILE_HEIGHT)
static const char* gDataPath = "C:/Users/Magnus.jonsson/Dropbox/C++/RygarRemake/";


enum class Setting { ePlayerJumpForce, eGravity, eScreenWidth, eScreenHeight, eWindowsWidth, eWindowsHeight };

class Settings
{
public:
	Settings();
	int GetFloat(const Setting setting) const;
	int GetInt(const Setting setting) const;

	void SetFloat(const Setting setting, const float value);
	void SetInt(const Setting setting, const float value);

	static void Create();
	static void Delete();


private:
	static inline Settings* ourInstance = nullptr;

	std::unordered_map<Setting, float> mKeyFloatValues;
	std::unordered_map<Setting, float> mKeyIntValues;

	std::string mDataPath;
};