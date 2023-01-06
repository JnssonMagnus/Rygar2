#include "stdafx.h"
#include "Apple.h"
#include "Player.h"

bool Apple::Use(Player& aPlayer)
{
	if (aPlayer.GetProperty<int>(PropertyKey::eLife) < 100.f)
	{
		aPlayer.ChangeProperty<int>(PropertyKey::eLife) += 10;
		return true;
	}

	return false;
}

void Apple::Collide(GameObject* aGameObject)
{
	// "epic" hack, check if uses same vptr
	int* a = reinterpret_cast<int*>(&(*aGameObject));
	int* b = reinterpret_cast<int*>(&(*this));
	if (*a != *b)
	{
		myPhysicBody->SetGravity(true);
	}
}
