#pragma once
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768
#define GRAVITY 0.25f
#define MAP_CHUNK_SIZE 3000
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MAP_WIDTH 25
#define MAP_HEIGHT 25
#define CHUNK_WIDTH (MAP_WIDTH*TILE_WIDTH)
#define CHUNK_HEIGHT (MAP_HEIGHT*TILE_HEIGHT)
static const char* gDataPath = "C:/Users/Magnus.jonsson/Dropbox/C++/RygarRemake/";

class Settings
{
public:


private:
	int mScreenWidth;
	int mScreenHeight;
	int mWindowHeight;
	int mWindowWidth;
	float mGravity;
	std::string mDataPath;
};