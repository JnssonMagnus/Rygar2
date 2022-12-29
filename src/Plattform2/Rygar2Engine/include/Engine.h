#pragma once
#include "Renderer.h"
#include "StateStack.h"
#include <InputObserver.h>
#include <memory>

class EngineDebugInfo;
class ParticleSystem;
class LuaManager;
class SoundPlayerInterface;

class Engine : public Input::InputObserver
{
public:
									Engine();
									~Engine();
	void							Init();
	void							MainLoop();
	void							RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue) override;

	template<class T, class ...args>
	void							AddState(args...);
private:

	StateStack							myStateStack;
	Renderer							myRenderer;
	ParticleSystem*						myParticleSystem = nullptr;
	SoundPlayerInterface*				mySoundManager = nullptr;
	std::shared_ptr<LuaManager>			myLuaManager;

	bool								myQuit;

	EngineDebugInfo*					myEngineDebugInfo;

};

template<class T, class ...args>
void Engine::AddState(args...arg) 
{
	myStateStack.PushMainState(new T(myStateStack.GetProxyObject(), arg...));
}
