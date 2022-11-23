#pragma once
#include "Sprite.h"
#include <GrowingArray.h>
#include <Vector2.h>

class PhysicBody;

class MapChunk;
class Player;

class WaterMap
{
public:
									WaterMap();
	void							Init(MapChunk& aMap);
	void							Draw(const Vector2f& aCameraPosition);
	void							Update();
	void							UpdatePlayerCollision(const Player& aPlayer);
	void							ResolveWaterCollision(PhysicBody& aPhysicBody);
	bool							TryTakeWater(const unsigned char aAmount, const Vector2f& aWorldPosition);
	bool							AddToWaterLevel(const unsigned char aAmount, const Vector2f& aWorldPosition);
	void							AddDrop(const Vector2f& aPosition, const Vector2f& aForce);

private:
	struct WaterDrop
	{
		Vector2f					myPosition;
		Vector2f					myVelocity;
	};

	int								GetWaterYFromPosition(const Vector2f& aPosition) const;
	int								GetNodeIndex(const Vector2f& aWorldPosition) const;
	void							FloatOnWater(PhysicBody& aPhysicBody);
	void							SplashWater(PhysicBody& aPhysicBody);
	void							CollideDropsVsPlayer(const Player& aPlayer);
	void							PlayerWading(const Player& aPlayer);
	inline void						AddWaterToNode(const unsigned char aAmount, const int aNode);
	inline void						RemoveWaterFromNode(const unsigned char aAmount, const int aNode);
	void							UpdateDrops();
	void							DrawDrops(const Vector2f& aCameraPosition);
	unsigned char					GetWaterLevelAtPoint(const Vector2f& aWorldPosition) const;
	void							TranferOutsideDropsToChunk();
	bool							IsOutsideChunk(const Vector2f& aPosition) const;
	void							TransferWaterInsideChunk(const int aNodeIndex);

	CU::GrowingArray<int>			myActiveTiles;
	CU::GrowingArray<WaterDrop>		myDrops;
	CU::GrowingArray<unsigned char>	myWaterLevel;
	Vector2f						myWorldPosition;
	MapChunk*						myMap;
	Sprite							myWaterSprite;
	Sprite							myDropSprite;
	int								myMapWidth;
	int								myMapHeight;
	int								myPlayerWaterHitFreq;
};

void WaterMap::AddWaterToNode(const unsigned char aAmount, const int aNode)
{
	if (myWaterLevel[aNode] == 0)
	{
		myActiveTiles.Add(aNode);
	}

	myWaterLevel[aNode] += aAmount;
}

void WaterMap::RemoveWaterFromNode(const unsigned char aAmount, const int aNode)
{
	myWaterLevel[aNode] -= aAmount;
	if (myWaterLevel[aNode] == 0)
	{
		myActiveTiles.RemoveCyclic(aNode);
	}
}