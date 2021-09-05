#pragma once
#include "Renderer.h"
#include "StateStack.h"
#include <InputObserver.h>
#include <WWiseSoundManager.h>
#include <memory>

class EngineDebugInfo;
class ParticleSystem;
class LuaManager;

class Engine : public Input::InputObserver
{
public:
									Engine();
									~Engine();
	void							Init();
	void							MainLoop();
	void							RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue) override;

private:

	StateStack						myStateStack;
	Renderer						myRenderer;
	ParticleSystem*					myParticleSystem = nullptr;
	SoundManager::WWiseSoundManager	mySoundManager;
	std::shared_ptr<LuaManager>		myLuaManager;

	bool							myQuit;

	EngineDebugInfo*				myEngineDebugInfo;

};

