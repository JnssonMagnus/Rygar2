#include "stdafx.h"
#include "WWiseSoundManager.h"
#include "AK/SoundEngine/Common/AkMemoryMgr.h"                  // Memory Manager
#include "AK/SoundEngine/Common/AkModule.h"  
#include "AK/SoundEngine/Common/AkSoundEngine.h"                // Sound engine
#include "AK/MusicEngine/Common/AkMusicEngine.h"  
#include "AK/SoundEngine/Common/IAkStreamMgr.h"                 // Streaming Manager
#include "AK/Tools/Common/AkPlatformFuncs.h"                    // Thread defines
#include "AK/SoundEngine/Common/AkStreamMgrModule.h"
#include "AkDefaultIOHookBlocking.h"
#include "OculusSpatializer.h"
#include "soundTasksBuffer.h"
#include <PostMaster/PostMaster.h>
#include <functional>

#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>
#endif
//#include "Debug\sound\Wwise_IDs.h"

namespace SoundManager
{
	WWiseSoundManager::WWiseSoundManager()
	{
		myIOHook = new CAkDefaultIOHookBlocking();
		myBufferToFill = 0;
		myUnloaded = false;
		myTaskBuffert = nullptr;
	}

	WWiseSoundManager::~WWiseSoundManager()
	{
		delete[]myTaskBuffert;
		myTaskBuffert = 0;

		delete myIOHook;
		myIOHook = nullptr;
		assert(myUnloaded == true && "Unload not called! SoundManager may not exit correctly!");
	}

	bool WWiseSoundManager::Init()
	{
		bool result = false;
		result = InitMemoryManager();
		assert(result == true && "Failed to init sound memory manager!");

		result = InitStreamManager();
		assert(result == true && "Failed to init sound stream manager!");

		result = InitSoundEngine();
		assert(result == true && "Failed to init sound engine!");

		result = InitMusicEngine();
		assert(result == true && "Failed to init sound music engine!");

		result = InitCommunication();
		assert(result == true && "Failed to init sound communication!");

		result = InitOculusSpatializer();
		//assert(result == true && "Failed to init oculus spatializer");

		myTaskBuffert = new SoundTasksBuffer[2];

		PostMaster::GetInstance()->Register(this, eMessageTypes::ePlaySoundEvent);
		PostMaster::GetInstance()->Register(this, eMessageTypes::eUpdateListenerPosition);

		return true;
	}

	void WWiseSoundManager::Update()
	{
		SoundTasksBuffer &buffer = myTaskBuffert[myBufferToFill ^ 1];
		for (int i = 0; i < buffer.mySoundObjectIDsToUnregister.Size(); ++i)
		{
			AK::SoundEngine::StopAll(buffer.mySoundObjectIDsToUnregister[i]);
			auto result = AK::SoundEngine::UnregisterGameObj(buffer.mySoundObjectIDsToUnregister[i]);
			assert(result == AK_Success  && "Failed to unregister sound object!");
		}

		for (int i = 0; i < buffer.mySoundObjectIDsToRegister.Size(); ++i)
		{
			auto result = AK::SoundEngine::RegisterGameObj(buffer.mySoundObjectIDsToRegister[i]);
			assert(result == AK_Success  && "Failed to register sound object!");
		}

		for (int i = 0; i < buffer.myPositionsToUpdate.Size(); ++i)
		{
			auto result = AK::SoundEngine::SetPosition(buffer.myPositionsToUpdate[i].myGameObjectID, buffer.myPositionsToUpdate[i].mySoundPosition);
			assert(result == AK_Success  && "Failed to update sound position!");
		}

		for (int i = 0; i < buffer.myListenersToUpdate.Size(); ++i)
		{
			auto result = AK::SoundEngine::SetListenerPosition(buffer.myListenersToUpdate[i].mySoundPosition, 0);
			assert(result == AK_Success  && "Failed to update sound position!");
		}

		for (int i = 0; i < buffer.mySoundEvents.Size(); ++i)
		{
			PlayEvent(buffer.mySoundEvents[i].myEventName.c_str(), buffer.mySoundEvents[i].myGameObjectID);
		}

		for (int i = 0; i < buffer.myOneshotSoundEvents.Size(); ++i)
		{
			PlayEvent(buffer.myOneshotSoundEvents[i].myEventName.c_str(), buffer.myOneshotSoundEvents[i].mySoundPosition);
		}

		for (int i = 0; i < buffer.mySwitchEvents.Size(); ++i)
		{
			AKRESULT result = AK::SoundEngine::SetSwitch(buffer.mySwitchEvents[i].mySwitchName.c_str(), buffer.mySwitchEvents[i].mySwitchValue.c_str(), 0);
			assert(result == AKRESULT::AK_Success && "Switch not found in wwise!");
		}

		AK::SoundEngine::RenderAudio();
	}

	void WWiseSoundManager::Unload()
	{
#ifndef AK_OPTIMIZED
		AK::Comm::Term();
#endif
		AK::MusicEngine::Term();
		AK::SoundEngine::Term();
		if (AK::IAkStreamMgr::Get())
		{
			AK::IAkStreamMgr::Get()->Destroy();
		}
		AK::MemoryMgr::Term();

		myUnloaded = true;
	}

	void WWiseSoundManager::InitBank(const char* aInitSoundBankFilename)
	{
		AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));
		AkBankID bankID;
		AKRESULT result = AK::SoundEngine::LoadBank(aInitSoundBankFilename, AK_DEFAULT_POOL_ID, bankID);
		assert(result != AKRESULT::AK_WrongBankVersion && "Wrong sound bank version! OMG!!!! Not again!");
		assert(result == AK_Success && "Failed to load sound bank!");

		//AK::SoundEngine::SetSwitch("Level", "Level1", 0);

	}

	void WWiseSoundManager::LoadBank(const char* aSoundBank)
	{
		AkBankID bankID;
		AKRESULT result = AK::SoundEngine::LoadBank(aSoundBank, AK_DEFAULT_POOL_ID, bankID);
		assert(result == AK_Success && "Failed to find sound bank or wrong bank version or run init.bnk first!");
	}

	void WWiseSoundManager::PlayEvent(const unsigned long aEventID, const GameObjectID aGameObjectID)
	{
		auto playingID = AK::SoundEngine::PostEvent(aEventID, aGameObjectID);
		assert(playingID != AK_INVALID_PLAYING_ID && "Sound event not found!");
	}

	void WWiseSoundManager::AddEvent(const char* aEventName, const Vector3f& aPosition)
	{
		AkSoundPosition pos;
		pos.SetPosition({ aPosition.x, aPosition.y, aPosition.z });
		pos.SetOrientation(AkVector{ 0, -1, 0 }, AkVector{ 0, 0, 1 });
		myTaskBuffert[myBufferToFill].myOneshotSoundEvents.Add(OneshotSoundEvents{ std::string(aEventName), pos });		
	}

	void WWiseSoundManager::AddEvent(const char* aEventName, const GameObjectID aGameObjectID)
	{
		myTaskBuffert[myBufferToFill].mySoundEvents.Add(SoundEventBuffer{ std::string(aEventName), aGameObjectID });
	}

	void WWiseSoundManager::PlayEvent(const char* aEventName, const AkSoundPosition& aSoundPosition)
	{
		static int ID = 10;
		AK::SoundEngine::RegisterGameObj(++ID);
		AK::SoundEngine::SetPosition(ID, aSoundPosition);
		auto f = [&](AkCallbackType, AkCallbackInfo*) { UnregisterSoundObjectID(ID); };

		auto playingID = AK::SoundEngine::PostEvent(aEventName, ID);
		assert(playingID != AK_INVALID_PLAYING_ID && "Sound event not found!");
	}

	void WWiseSoundManager::PlayEvent(const char* aEventName, const GameObjectID aGameObjectID)
	{
		auto playingID = AK::SoundEngine::PostEvent(aEventName, aGameObjectID);
		assert(playingID != AK_INVALID_PLAYING_ID && "Sound event not found!");
	}

	void WWiseSoundManager::UpdateSoundObjectPosition(const GameObjectID aGameObjectID, const CU::Matrix44<float>& aPosition)
	{
		AkSoundPosition updatedPosition;
		const Vector3f newPosition = aPosition.GetPosition3();
		const Vector3f newUp = aPosition.GetUp3();
		const Vector3f newForward = aPosition.GetForward3();
		updatedPosition.SetPosition(newPosition.x, newPosition.y, newPosition.z);
		updatedPosition.SetOrientation(newForward.x, newForward.y, newForward.z, newUp.x, newUp.y, newUp.z);

		myTaskBuffert[myBufferToFill].myPositionsToUpdate.Add(UpdateObjectPositionBuffer{ aGameObjectID, updatedPosition });
	}

	void WWiseSoundManager::UpdateListenerPosition(const CU::Matrix44<float>& aPosition)
	{
		AkSoundPosition updatedPosition;
		const Vector3f newPosition = aPosition.GetPosition3();
		const Vector3f newUp = aPosition.GetUp3();
		const Vector3f newForward = aPosition.GetForward3();
		updatedPosition.SetPosition(newPosition.x, newPosition.y, newPosition.z);
		updatedPosition.SetOrientation(newForward.x, newForward.y, newForward.z, newUp.x, newUp.y, newUp.z);

		auto result = AK::SoundEngine::SetListenerPosition(updatedPosition, 0);
		assert(result == AK_Success  && "Failed to update sound position!");
	}

	void WWiseSoundManager::RegisterSoundObjectID(const GameObjectID aGameObjectID)
	{
		myTaskBuffert[myBufferToFill].mySoundObjectIDsToRegister.Add(aGameObjectID);
	}

	void WWiseSoundManager::UnregisterSoundObjectID(const GameObjectID aGameObjectID)
	{
		myTaskBuffert[myBufferToFill].mySoundObjectIDsToUnregister.Add(aGameObjectID);
	}

	void WWiseSoundManager::SwapBuffer()
	{
		myTaskBuffert[myBufferToFill^1].myOneshotSoundEvents.Clear();
		myTaskBuffert[myBufferToFill^1].mySoundEvents.Clear();
		myTaskBuffert[myBufferToFill^1].myListenersToUpdate.Clear();
		myTaskBuffert[myBufferToFill^1].myPositionsToUpdate.Clear();
		myTaskBuffert[myBufferToFill^1].mySoundObjectIDsToRegister.Clear();
		myTaskBuffert[myBufferToFill^1].mySoundObjectIDsToUnregister.Clear();
		myTaskBuffert[myBufferToFill^1].mySwitchEvents.Clear();

		myBufferToFill ^= 1;
	}

	void WWiseSoundManager::SetRTPC(const char* aName, float aValue)
	{
		AK::SoundEngine::SetRTPCValue(aName, aValue);
	}

	void WWiseSoundManager::RecieveMessage(const Message& aMessage)
	{
		switch (aMessage.myMessageType)
		{
		case eMessageTypes::ePlaySoundEvent:
			if (aMessage.myIntData == -1)
			{
				AddEvent(aMessage.myText.c_str(), aMessage.myMatrix.GetPosition3());
			}
			else
			{
				AddEvent(aMessage.myText.c_str(), aMessage.myIntData);
			}
			break;
		case eMessageTypes::eUpdateListenerPosition:
			UpdateListenerPosition(aMessage.myMatrix);

			break;
		}
	}

	bool WWiseSoundManager::InitOculusSpatializer()
	{
		// Load Oculus Spatializer dll plug-in
		HMODULE OculusSpatializerLibrary = LoadLibrary(L"OculusSpatializerWwise.dll");

		// Successful?
		if (OculusSpatializerLibrary)
		{
			typedef bool(__stdcall *AkGetSoundEngineCallbacksType)
				(unsigned short in_usCompanyID,
					unsigned short in_usPluginID,
					AkCreatePluginCallback& out_funcEffect,
					AkCreateParamCallback&  out_funcParam);

			AkGetSoundEngineCallbacksType AkGetSoundEngineCallbacks =
				(AkGetSoundEngineCallbacksType)(void*)GetProcAddress(OculusSpatializerLibrary, "AkGetSoundEngineCallbacks");

			if (AkGetSoundEngineCallbacks)
			{
				AkCreatePluginCallback CreateOculusFX;
				AkCreateParamCallback  CreateOculusFXParams;

				// Register plugin effect
				if (AkGetSoundEngineCallbacks(AKEFFECTID_OCULUS, AKEFFECTID_OCULUS_SPATIALIZER, CreateOculusFX, CreateOculusFXParams))
				{
					if (AK::SoundEngine::RegisterPlugin(AkPluginTypeMixer, AKEFFECTID_OCULUS, AKEFFECTID_OCULUS_SPATIALIZER, CreateOculusFX, CreateOculusFXParams) != AK_Success)
					{
						printf("Failed to register OculusSpatializer plugin.");
						return false;
					}
				}
				else
				{
					printf("Failed call to AkGetSoundEngineCallbacks in OculusSpatializer.dll");
					return false;
				}

				// Register plugin attachment (for data attachment on individual sounds, like frequency hints etc.)
				if (AkGetSoundEngineCallbacks(AKEFFECTID_OCULUS, AKEFFECTID_OCULUS_SPATIALIZER_ATTACHMENT, CreateOculusFX, CreateOculusFXParams))
				{
					if (AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKEFFECTID_OCULUS, AKEFFECTID_OCULUS_SPATIALIZER_ATTACHMENT, NULL, CreateOculusFXParams) != AK_Success)
					{
						printf("Failed to register OculusSpatializer attachment.");
						return false;
					}
				}
				else
				{
					printf("Failed call to AkGetSoundEngineCallbacks in OculusSpatializer.dll");
					return false;
				}
			}
			else
			{
				printf("Failed to load functions AkGetSoundEngineCallbacks in OculusSpatializer.dll");
				return false;
			}
		}
		else
		{
			printf("Failed to load OculusSpatializer.dll");
			return false;
		}

		return true;
	}

	bool WWiseSoundManager::InitMemoryManager()
	{
		AkMemSettings memSettings;
		memSettings.uMaxNumPools = 20;

		if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
		{
			assert(!"Could not create the memory manager.");
			return false;
		}

		return true;
	}

	bool WWiseSoundManager::InitSoundEngine()
	{
		AkInitSettings initSettings;
		AkPlatformInitSettings platformInitSettings;
		AK::SoundEngine::GetDefaultInitSettings(initSettings);
		AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

		if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
		{
			assert(!"Could not initialize the Sound Engine.");
			return false;
		}

		return true;
	}

	bool WWiseSoundManager::InitMusicEngine()
	{
		AkMusicSettings musicInit;
		AK::MusicEngine::GetDefaultInitSettings(musicInit);

		if (AK::MusicEngine::Init(&musicInit) != AK_Success)
		{
			assert(!"Could not initialize the Music Engine.");
			return false;
		}

		return true;
	}

	bool WWiseSoundManager::InitCommunication()
	{
#ifndef AK_OPTIMIZED
		AkCommSettings commSettings;
		AK::Comm::GetDefaultInitSettings(commSettings);
		if (AK::Comm::Init(commSettings) != AK_Success)
		{
			assert(!"Could not initialize communication.");
			return false;
		}
#endif 

		return true;
	}

	bool WWiseSoundManager::InitStreamManager()
	{
		AkStreamMgrSettings stmSettings;
		AK::StreamMgr::GetDefaultSettings(stmSettings);

		if (!AK::StreamMgr::Create(stmSettings))
		{
			assert(!"Could not create the Streaming Manager");
			return false;
		}

		AkDeviceSettings deviceSettings;		
		AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
		myIOHook->Init(deviceSettings);


		return true;
	}
}