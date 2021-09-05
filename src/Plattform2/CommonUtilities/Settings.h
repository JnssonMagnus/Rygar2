#pragma once
#include <StaticArray.h>

enum class eSetting
{
	ePhysics,
	eSound,
	eMusic,
	eFullscreen,
	eVRActive,
	eNumSettings,
};

class Settings
{
public:
	void					LoadSettings(const char* aFilename);
	int						GetScreenWidth();
	int						GetScreenHeight();
	int						GetFixedFramerate();
	const std::string&		GetWindowTitle();
	const std::string&		GetSoundLibrary();
	const std::string&		GetMusicLibrary();
	bool					GetFlag(const eSetting aSetting);
	void					SetFlag(const eSetting aSetting, bool aValue);
	float					GetMasterVolume();
	void					SetMasterVolume(const float aVolume);
	float					GetMusicVolume();
	void					SetMusicVolume(const float aVolume);
	static Settings&		GetInstance();
	static void				Create();
	static void				Destroy();

private:
	Settings();
	static Settings*	myInstance;
	std::string			myWindowTitle;
	std::string			mySoundLibrary;
	std::string			myMusicLibrary;
	float				myMasterVolume;
	float				myMusicVolume;
	int					myScreenWidth;
	int					myScreenHeight;
	int					myFixedFramerate;
	CU::StaticArray<bool, static_cast<int>(eSetting::eNumSettings)>	
						myFlags;
};

