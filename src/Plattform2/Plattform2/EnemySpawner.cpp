#include "stdafx.h"
#include "EnemySpawner.h"
#include "PhysicBody.h"

void EnemySpawner::Update(const float aDeltaTime)
{
	myTimeSinceLastSpawn += aDeltaTime;
	if (myTimeSinceLastSpawn >= mySpawnDelay && myCurrentSpawnCount < myMaxSpawnCount)
	{
		//Message message;
		//message.myMessageType = eMessageTypes::eCreateObject;
		//message.myIntData = static_cast<int>(mySpawnType);
		//message.myPosition = GetPhysicBody().GetPosition();

		//PostMaster::GetInstance()->SendMessage(message);
		myTimeSinceLastSpawn = 0.f;
		myCurrentSpawnCount++;
	}
}
