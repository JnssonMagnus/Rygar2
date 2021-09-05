#pragma once
#include <string>
#include <AK/SoundEngine/Common/AkTypes.h>
#include "../../../CommonUtilities/GrowingArray.h"

class CAkDefaultIOHookBlocking;
//typedef __w64 unsigned int AkUIntPtr;			///< Integer (unsigned) type for pointers
//typedef AkUIntPtr AkGameObjectID;		 	///< Game object ID
//typedef unsigned long AkUInt32;			///< Unsigned 32-bit integer


namespace SoundManager
{
	struct PlayEventBuffer
	{
		unsigned long myEventID;
		AkGameObjectID myGameObjectID;
	};

	struct SetSwitchBuffer
	{
		std::string	mySwitchName;
		std::string mySwitchValue;
	};

	struct UpdateObjectPositionBuffer
	{
		AkGameObjectID myGameObjectID;
		AkSoundPosition mySoundPosition;
	};

	struct UpdateListenerPositionBuffer
	{
		AkUInt32 myListenerID;
		AkSoundPosition mySoundPosition;
	};

	struct OneshotSoundEvents
	{
		std::string	myEventName;
		AkSoundPosition mySoundPosition;
	};

	struct SoundEventBuffer
	{
		std::string myEventName;
		AkGameObjectID myGameObjectID;
	};

	struct SoundTasksBuffer
	{
		CU::GrowingArray<AkGameObjectID>				mySoundObjectIDsToRegister;
		CU::GrowingArray<AkGameObjectID>				mySoundObjectIDsToUnregister;
		CU::GrowingArray<UpdateObjectPositionBuffer>	myPositionsToUpdate;
		CU::GrowingArray<UpdateListenerPositionBuffer>	myListenersToUpdate;
		CU::GrowingArray<OneshotSoundEvents>			myOneshotSoundEvents;
		CU::GrowingArray<SoundEventBuffer>				mySoundEvents;
		CU::GrowingArray<SetSwitchBuffer>				mySwitchEvents;
	};
}