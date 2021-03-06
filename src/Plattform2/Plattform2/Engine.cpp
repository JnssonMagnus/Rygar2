#include "stdafx.h"
#include "Engine.h"
#include "PhysicManager.h"
#include "EngineDebugInfo.h"
#include "gameObjectManager.h"
#include "GameState.h"
#include "ParticleSystem.h"
#include "LuaManager.h"
#include "Megaton.h"
#include <ThreadPool.h>
#include <InputWrapper.h>
#include <InputMapper.h>
#include <Time/TimerManager.h>
#include <SDL.h>


Engine::Engine()
{
	myQuit = false;
	myEngineDebugInfo = nullptr;
}

void Engine::Init()
{
	DL_Debug::Debug::Create();
	Megaton::Create();

	myLuaManager = std::make_shared<LuaManager>();
	myLuaManager->Init();
	Megaton::GetInstance().SetLuaManager(myLuaManager);

	myRenderer.Init();

	Input::InputWrapper::GetInstance(); // Make a separate create function for this later
	Input::InputMapper::Create();
	Input::InputWrapper::GetInstance()->Init(GetModuleHandle(NULL), GetActiveWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
	ResourceManager::Create();
	ResourceManager::GetInstance()->Init(myRenderer.GetSDL_Renderer());
	Timer::TimerManager::Create();
	PhysicManager::Create();
	ThreadPool::Create();

	PostMaster::GetInstance();  // Make a separate create function for this later
	PhysicManager::GetInstance()->Init();

	myParticleSystem = new ParticleSystem();
	myParticleSystem->Init(&myRenderer);
	myParticleSystem->LoadParticleEmitterBlueprints("data/json/ParticleEmitterBlueprints.json");

	mySoundManager.Init();
	mySoundManager.InitBank("data/sound/init.bnk");
	mySoundManager.LoadBank("data/sound/New_SoundBank.bnk");

	myEngineDebugInfo = new EngineDebugInfo();
	myEngineDebugInfo->Init();
	
	myStateStack.PushMainState(new GameState(myStateStack.GetProxyObject()));

	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyF10, Input::eInputEvent::eCaptureMouse);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyESCAPE, Input::eInputEvent::eExit);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eCaptureMouse, this);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eExit, this);
	Input::InputWrapper::GetInstance()->CaptureWindowsMouse();
}

Engine::~Engine()
{
	SAFE_DELETE(myParticleSystem);
	Input::InputMapper::Destroy();
	Input::InputWrapper::GetInstance()->Destroy();
	PhysicManager::GetInstance()->Destroy();
	ResourceManager::Destroy();
	Timer::TimerManager::Destroy();
	PostMaster::GetInstance()->Destroy();
	DL_Debug::Debug::Destroy();
	mySoundManager.Unload();
}

void Engine::MainLoop()
{
	float timeSinceLastFrame = 0.f;
	constexpr float fixedFrameRate = (1.f / 60.f) * 1000000.f;
	constexpr float fixedDeltaTime = 1.f / 60.f;
	int fps = 0;
	float countToOne = 0.f;

	Timer::TimerManager::GetInstance()->UpdateTimers();
	while (myQuit == false)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event));

		Timer::TimerManager::GetInstance()->UpdateTimers();

		timeSinceLastFrame += DELTA_TIME.GetMicroseconds();		
		
 		countToOne += DELTA_TIME.GetMicroseconds();
		if (countToOne >= 1000000)
		{
			myEngineDebugInfo->SetFPS(fps);
			countToOne -= 1000000;
			fps = 0;
		}

		// if time to spare, and stop from getting frame time of 0
		if (timeSinceLastFrame < fixedFrameRate)
			std::this_thread::yield();

		while (timeSinceLastFrame >= fixedFrameRate)
		{			
			fps++;
			ThreadPool::GetInstance()->AddWork([&]
				{
					Input::InputWrapper::GetInstance()->Update();
					Input::InputMapper::GetInstance()->Update();

					PhysicManager::GetInstance()->UpdatePhysicBodies();
					PhysicManager::GetInstance()->ResolveCollisions();
					myRenderer.UpdateCamera();

					myStateStack.UpdateCurrentState(fixedDeltaTime);
					myStateStack.RenderCurrentState(fixedDeltaTime);

					GameObjectManager::GetInstance()->UpdateGameObjects(fixedDeltaTime);

					mySoundManager.Update();
					mySoundManager.SwapBuffer();

					myEngineDebugInfo->Draw();
					
					GameObjectManager::GetInstance()->AddAndRemoveObjects();
					PhysicManager::GetInstance()->AddAndRemovePhysicBodies();
					
				}
			);

			ThreadPool::GetInstance()->AddWork([&] 
				{ 
					myParticleSystem->Draw();
					myParticleSystem->Update(fixedDeltaTime); 
				});

			if (timeSinceLastFrame - fixedFrameRate <= fixedFrameRate)
			{
				ThreadPool::GetInstance()->AddWork([this] { myRenderer.Draw(); });
			}

			ThreadPool::GetInstance()->DoAllWork();
			PostMaster::GetInstance()->SendDelayedMessages();
			myRenderer.SwapRenderBuffer();
			
			timeSinceLastFrame -= fixedFrameRate;
		}		
	}
}

void Engine::RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue)
{
	switch (aEvent)
	{
	case Input::eInputEvent::eCaptureMouse:
		Input::InputWrapper::GetInstance()->SwapWindowsMouseCaptureState();
		break;
	case Input::eInputEvent::eExit:
		myQuit = true;
		break;
	}
}

