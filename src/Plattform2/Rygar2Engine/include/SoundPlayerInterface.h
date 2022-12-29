#pragma once
#include <PostMaster/Observer.h>

class SDLMixer2SoundMan;

class SoundPlayerInterface : public Observer
{
public:
			SoundPlayerInterface();
	void	Unload();
	void	Update();
	void	RecieveMessage(const Message& aMessage) override;
private:
#ifdef USE_SDLMIXER2
	SDLMixer2SoundMan* mySoundManager = nullptr;
#endif
};

