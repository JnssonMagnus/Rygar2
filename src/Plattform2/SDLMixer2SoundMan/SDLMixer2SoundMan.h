#pragma once
#include <map>
#include <string>
typedef struct _Mix_Music Mix_Music;
typedef struct Mix_Chunk;


class SDLMixer2SoundMan
{
public:
	SDLMixer2SoundMan();
	void PlayMusic(const char* aPath);
	void LoadSoundEvent(const std::string& aName, const std::string& aPath);
	void PlaySoundEvent(const std::string& aEventName);

private:
	Mix_Music* myMusic = nullptr;
	std::map<std::string, Mix_Chunk*> mySoundEvents;
};
