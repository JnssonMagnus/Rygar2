#include "SoundPlayerInterface.h"
#ifdef USE_WWISE
#include <WWiseSoundManager.h>
#else
#include <SDLMixer2SoundMan.h>
#endif

#include "Settings.h"
#include "PostMaster/PostMaster.h"

SoundPlayerInterface::SoundPlayerInterface()
{
#ifdef USE_WWISE
	mySoundManager = new SoundManager::WWiseSoundManager();
	mySoundManager->Init();
	mySoundManager->InitBank((std::string(gDataPath) + "data/sound/init.bnk").c_str());
	mySoundManager->LoadBank((std::string(gDataPath) + "data/sound/New_SoundBank.bnk").c_str());
#endif

#ifdef USE_SDLMIXER2
	mySoundManager = new SDLMixer2SoundMan();
	std::string musicPath = gDataPath + std::string("data/music/01 Starting Point (Sunset).mp3");
	//mySoundManager->PlayMusic(musicPath.c_str());


	mySoundManager->LoadSoundEvent("jump", gDataPath + std::string("data/sfx/RygarJump.wav"));
	mySoundManager->LoadSoundEvent("rygarAttack", gDataPath + std::string("data/sfx/RygarAttack.wav"));
	mySoundManager->LoadSoundEvent("rygarAttackHitWall", gDataPath + std::string("data/sfx/RygarAttackHitWall.wav"));
	mySoundManager->LoadSoundEvent("rygarHookStuck", gDataPath + std::string("data/sfx/RygarHookStuck.wav"));
	mySoundManager->LoadSoundEvent("rygarHookThrow", gDataPath + std::string("data/sfx/RygarHookThrow.wav"));
	mySoundManager->LoadSoundEvent("rygarLand", gDataPath + std::string("data/sfx/RygarLand.wav"));
	mySoundManager->LoadSoundEvent("rygarTakeDamage", gDataPath + std::string("data/sfx/RygarTakeDamage.wav"));
	mySoundManager->LoadSoundEvent("rygarJumpStagger", gDataPath + std::string("data/sfx/RygarJumpStagger.wav"));
	mySoundManager->LoadSoundEvent("enemyHit", gDataPath + std::string("data/sfx/EnemyHit.wav"));
	mySoundManager->LoadSoundEvent("enemyDeath", gDataPath + std::string("data/sfx/EnemyDeath.wav"));
	

#endif

	PostMaster::GetInstance()->Register(this, eMessageTypes::ePlaySoundEvent);
}

void SoundPlayerInterface::Unload()
{
}

void SoundPlayerInterface::Update()
{
}

void SoundPlayerInterface::RecieveMessage(const Message& aMessage)
{
	mySoundManager->PlaySoundEvent(aMessage.myText);
}
