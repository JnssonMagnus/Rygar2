#pragma once
#include "CollisionPoint.h"
#include <set>

struct TileData;

struct MapCollisionData
{
	eCollisionPoint myCollisionPoint;
	std::set<const TileData*> myCollidedTileTypes;
};
