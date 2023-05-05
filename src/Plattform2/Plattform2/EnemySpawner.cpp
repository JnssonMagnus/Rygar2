#include "stdafx.h"
#include "EnemySpawner.h"
#include "PhysicBody.h"

void EnemySpawner::Update(const float aDeltaTime)
{
	myTimeSinceLastSpawn += aDeltaTime;
	if (myTimeSinceLastSpawn >= mySpawnDelay && myCurrentSpawnCount < myMaxSpawnCount)
	{
		Message message;
		message.myMessageType = eMessageTypes::eCreateEnemy;
		message.myText = myEnemyName;
		message.myPosition = GetPhysicBody().GetPosition();

		PostMaster::GetInstance()->SendMessage(message);
		myTimeSinceLastSpawn = 0.f;
		myCurrentSpawnCount++;
	}
}

void EnemySpawner::Init(GameObjectType& aGameObjectType)
{
	GameObject::Init(aGameObjectType);
	mySpawnDelay = GetGameObjectTypeVariable<float>("frequence");
	myEnemyName = GetGameObjectTypeVariable<std::string>("type");
}
