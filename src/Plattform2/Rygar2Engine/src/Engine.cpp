#include "stdafx.h"
#include "Engine.h"
#include "PhysicManager.h"
#include "EngineDebugInfo.h"
#include "gameObjectManager.h"
#include "ParticleSystem.h"
#include "LuaManager.h"
#include "SoundPlayerInterface.h"
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
	
	myLuaManager = std::make_shared<LuaManager>();
	myLuaManager->Init();

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
	myParticleSystem->LoadParticleEmitterBlueprints((std::string(gDataPath) + "data/json/ParticleEmitterBlueprints.json").c_str());

	mySoundManager = new SoundPlayerInterface();

	myEngineDebugInfo = new EngineDebugInfo();
	myEngineDebugInfo->Init();	

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
	mySoundManager->Unload();
}

void Engine::MainLoop()
{
	double timeSinceLastFrame = 0.f;
	constexpr double fixedFrameRate = (1.0 / 60.0) * 1000000000.0;
	constexpr double fixedDeltaTime = 1.0 / 60.0;
	int fps = 0;
	double countToOne = 0.0;

	Timer::TimerManager::GetInstance()->UpdateTimers();
	while (myQuit == false)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event));

		Timer::TimerManager::GetInstance()->UpdateTimers();

		timeSinceLastFrame += DELTA_TIME.GetNanoSeconds();
		
 		countToOne += DELTA_TIME.GetNanoSeconds();
		if (countToOne >= 1000000000)
		{
			myEngineDebugInfo->SetFPS(fps);
			countToOne -= 1000000000;
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

					mySoundManager->Update();

					myEngineDebugInfo->Draw();
					
					GameObjectManager::GetInstance()->AddAndRemoveObjects();
					PhysicManager::GetInstance()->AddAndRemovePhysicBodies();					
				}
			);

			ThreadPool::GetInstance()->AddWork([&] 
				{ 
					myParticleSystem->Update(static_cast<float>(fixedDeltaTime)); 
					myParticleSystem->Draw();					
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

