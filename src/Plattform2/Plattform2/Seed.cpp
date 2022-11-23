#include "stdafx.h"
#include "Seed.h"
#include "Megaton.h"
#include "MapChunk.h"
#include "Player.h"
#include "GameObjectTypes.h"
#include <postmaster/postmaster.h>

bool Seed::Use(Player& aPlayer)
{
	if (Megaton::GetInstance().GetMap().Collided(aPlayer.GetPhysicBody().GetMiddleBottom()) == true)
	{
		Message message;
		message.myMessageType = eMessageTypes::eCreateObject;
		message.myIntData = 7; // tree
		message.myPosition = aPlayer.GetPhysicBody().GetMiddleBottom();
			
		PostMaster::GetInstance()->SendMessage(message);
		return true;
	}

	return false;
}
