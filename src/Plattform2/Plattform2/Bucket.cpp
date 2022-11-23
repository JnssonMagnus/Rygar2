#include "stdafx.h"
#include "Bucket.h"
#include "MapChunk.h"
#include "Megaton.h"
#include "player.h"

Bucket::Bucket()
{
	myWaterAmount = 0;
	myWaterCapacity = 50;
}

bool Bucket::Use(Player& aPlayer)
{
	MapChunk& map = Megaton::GetInstance().GetMap();

	if (myWaterAmount < myWaterCapacity)
	{
		bool waterTaken = map.TryTakeWater(1_uc, aPlayer.GetPhysicBody().GetPosition());
		myWaterAmount += static_cast<int>(waterTaken);
	}
	else
	{
		EmptyBucket();
	}

	return false;
}

void Bucket::EmptyBucket()
{
	while (myWaterAmount-- > 0)
	{
		Vector2f pos = myPhysicBody->GetMiddleTop();
		pos.myX += (rand() % static_cast<int>(myPhysicBody->GetHalfSize().myX)) - (rand() % static_cast<int>(myPhysicBody->GetHalfSize().myX));
		Vector2f force = Vector2f((rand() % 100) / 50.f - (rand() % 100) / 50.f, -5 - (rand() % 100) / 20.f);
		MapChunk& map = Megaton::GetInstance().GetMap();
		map.AddWaterDrop(pos, force);
	}
}
