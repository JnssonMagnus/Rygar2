#pragma once
#include "../../../CommonUtilities/Matrix44.h"
#include <string>
#include <PostMaster/Observer.h>

class AkTransform;
class CAkDefaultIOHookBlocking;
typedef AkTransform AkSoundPosition;

namespace SoundManager
{
	typedef __w64 unsigned int GameObjectID;		 	///< Game object ID
	struct SoundTasksBuffer;

	class WWiseSoundManager : public Observer
	{
	public:
				WWiseSoundManager();
				~WWiseSoundManager();

		bool	Init();
		void	Update();
		void	Unload();
		void	InitBank(const char* aInitSoundBankFilename = "sound/Init.bnk");
		void	LoadBank(const char* aSoundBank);
		void	AddEvent(const char* aEventName, const GameObjectID aGameObjectID = 0);
		void	AddEvent(const char* aEventName, const Vector3f& aPosition);
		void	UpdateSoundObjectPosition(const GameObjectID aGameObjectID, const CU::Matrix44<float>& aSoundPosition);
		void	UpdateListenerPosition(const CU::Matrix44<float>& aSoundPosition);
		void	RegisterSoundObjectID(const GameObjectID aGameObjectID);
		void	UnregisterSoundObjectID(const GameObjectID aGameObjectID);
		void	SwapBuffer();
		void	SetRTPC(const char* aName, float aValue);

		void	RecieveMessage(const Message& aMessage) override;

	private:
		void	PlayEvent(const char* aEventName, const AkSoundPosition& aSoundPosition);
		void	PlayEvent(const char* aEventName, const GameObjectID aGameObjectID = 0);
		void	PlayEvent(const unsigned long aEventID, const GameObjectID aGameObjectID = 0);
		bool	InitOculusSpatializer();
		bool	InitMemoryManager();
		bool	InitStreamManager();
		bool	InitSoundEngine();
		bool	InitMusicEngine();
		bool	InitCommunication();
		bool	myUnloaded;
		CAkDefaultIOHookBlocking	*myIOHook;
		SoundTasksBuffer*			myTaskBuffert;
		int							myBufferToFill;
	};
}