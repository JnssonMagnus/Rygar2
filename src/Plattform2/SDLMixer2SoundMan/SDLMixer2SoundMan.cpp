#include "SDLMixer2SoundMan.h"
#include <SDL_mixer.h>
#include <assert.h>
#include <iostream>


SDLMixer2SoundMan::SDLMixer2SoundMan()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        assert(false && "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    std::cout << "SDL Mixer 2 Audio inited!" << std::endl;
}

void SDLMixer2SoundMan::PlayMusic(const char* aPath)
{
    myMusic = Mix_LoadMUS(aPath);
    std::cout << Mix_GetError() << std::endl;
    Mix_PlayMusic(myMusic, -1);
}

void SDLMixer2SoundMan::LoadSoundEvent(const std::string& aName, const std::string& aPath)
{
    mySoundEvents[aName] = Mix_LoadWAV(aPath.c_str());
}

void SDLMixer2SoundMan::PlaySoundEvent(const std::string& aEventName)
{
    Mix_PlayChannel(-1, mySoundEvents[aEventName], 0);
}