#include "stdafx.h"
#include "Hammer.h"
#include "MapChunk.h"
#include "Megaton.h"

bool Hammer::Use(Player& aPlayer)
{
	MapChunk& map = Megaton::GetInstance().GetMap();
	const Vector2f& attackPos = myPhysicBody->GetMiddleTop();
	if (map.IsDestructable(attackPos) == true)
	{
		map.DestroyTile(attackPos);
	}
	return false;
}
