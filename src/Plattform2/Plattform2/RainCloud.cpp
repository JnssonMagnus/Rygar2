#include "stdafx.h"
#include "RainCloud.h"
#include "PhysicBody.h"
#include "Megaton.h"
#include "Map.h"
#include "gameObjectType.h"

RainCloud::RainCloud()
{
	myDropsLeft = 0;
}

void RainCloud::Update(const float aDeltaTime)
{
	static float time = 0.f;
	time += 1 / 60.f;

	myPhysicBody->SetVelocity(Vector2f(cos(time), 0.f) * 5.f);

	Map& map = Megaton::GetInstance().GetMap();
	for (size_t i = 0; i < 10; i++)
	{
		Vector2f dropOffset;
		const Sprite& sprite = myGameObjectType->GetSprite();
		dropOffset.myX = (rand() % sprite.GetSize().myX) - (rand() % sprite.GetSize().myX);
		dropOffset.myY = (rand() % sprite.GetSize().myY) - (rand() % sprite.GetSize().myY);
		dropOffset.myX *= 0.5f;
		dropOffset.myY *= 0.25f;
		map.AddWaterDrop(myPhysicBody->GetPosition() + dropOffset, myPhysicBody->GetVelocity() / 10.f);
	}
	
}
