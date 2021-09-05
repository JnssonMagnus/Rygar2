#include "stdafx.h"
#include "WaterMap.h"
#include "Map.h"
#include "PhysicBody.h"
#include "player.h"
#include <commonUtils.h>

constexpr unsigned char MAX_WATERLEVEL = 255_uc;

WaterMap::WaterMap()
{
	myMap = nullptr;
	myMapWidth = 0;
	myMapHeight = 0;
	myPlayerWaterHitFreq = 0;
}

void WaterMap::Init(Map& aMap)
{
	DL_ASSERT(myMap == nullptr && "WaterMap already initiated!");
	myMap = &aMap;
	myMapWidth = myMap->GetMapWidth();
	myMapHeight = myMap->GetMapHeight();

	myWaterSprite.Init("data/gfx/water.png");
	myDropSprite.Init("data/gfx/waterDrop.png");

	myDropSprite.SetPivot({ 4, 8 });

	myWaterLevel.Resize(myMapWidth * myMapHeight);
	myWaterLevel.Fill(0);
}

void WaterMap::Draw(const Vector2f& aCameraPosition)
{
	DrawDrops(aCameraPosition);
	const Vector2<int>& tileSize = myMap->GetTileSize();

	int startTileX = (aCameraPosition.myX - (SCREEN_WIDTH / 2.f) + 0.5f) / tileSize.myX;
	int endTileX = startTileX + (SCREEN_WIDTH / tileSize.myX) + 1;
	int startTileY = (aCameraPosition.myY - (SCREEN_HEIGHT / 2.f) + 0.5f) / tileSize.myY;
	int endTileY = startTileY + (SCREEN_HEIGHT / tileSize.myY) + 1;

	startTileX = MAX(0, startTileX);
	startTileY = MAX(0, startTileY);
	endTileX = MIN(endTileX, myMapWidth);
	endTileY = MIN(endTileY, myMapHeight);

	for (int y = startTileY; y < endTileY; y++)
	{
		for (int x = startTileX; x < endTileX; x++)
		{
			const unsigned char waterLevel = myWaterLevel[x + y * myMapWidth];
			if (waterLevel > 0_uc)
			{
				int waterHeight = tileSize.myY * (waterLevel / static_cast<float>(MAX_WATERLEVEL));
				const Vector2f pos(x * tileSize.myX, y * tileSize.myY + (tileSize.myY - waterHeight));
				const Vector2<int> size(tileSize.myX, waterHeight);
				myWaterSprite.Draw(pos, size);
			}
		}
	}
}

void WaterMap::Update(const Player& aPlayer)
{
	//for (int node = myMapWidth * myMapHeight - 1; node >= 0; node--)
	for (int i = myActiveTiles.Size() - 1; i >= 0; --i)
	{
		const int node = myActiveTiles[i];
		if (myWaterLevel[node] > 0_uc)
		{
			// transfer water to node under
			if (myMap->Collided(node + myMapWidth) == false && myWaterLevel[node + myMapWidth] < MAX_WATERLEVEL && myWaterLevel[node + myMapWidth] > 0_uc)
			{
				constexpr int maxDropsToFallFromAbove = 10;
				int drops = maxDropsToFallFromAbove;
				drops = MIN(drops, myWaterLevel[node]);
				while (drops-- > 0 && myWaterLevel[node + myMapWidth] < MAX_WATERLEVEL)
				{
					RemoveWaterFromNode(1, node);
					AddWaterToNode(1, node + myMapWidth);
				}
			}
			// emtpy under, make drops fall down
			if (myMap->Collided(node + myMapWidth) == false && myWaterLevel[node + myMapWidth] == 0_uc)
			{
				constexpr int maxDropsToFallFromAbove = 10;
				int drops = rand() % maxDropsToFallFromAbove + 1;
				drops = MIN(drops, myWaterLevel[node]);
				while (drops-- > 0)
				{
					const Vector2<int>& tileSize = myMap->GetTileSize();
					float x = (node + myMapWidth) % myMapWidth;
					x *= tileSize.myX;
					x += rand() % tileSize.myX;

					float y = (node) / myMapWidth;
					y *= tileSize.myY;
					y += tileSize.myY;

					RemoveWaterFromNode(1, node);

					AddDrop({ x, y }, { 0.f, 0.f });
				}
			}
			// make drops at sides
			else if (myWaterLevel[node] > 0_uc)
			{
				float amount = static_cast<float>(myWaterLevel[node]) / MAX_WATERLEVEL;
				int drops = rand() % (static_cast<int>(amount * 20.f) + 1);
				drops = MIN(drops, myWaterLevel[node]);
				while (drops-- > 0)
				{
					int randDir = (((rand() % 2) * 2) - 1);
					if (myMap->Collided(node + randDir + myMapWidth) == false &&
						myMap->Collided(node + randDir) == false &&
						myWaterLevel[node + randDir + myMapWidth] < MAX_WATERLEVEL)
					{
						const Vector2<int>& tileSize = myMap->GetTileSize();
						float x = (node + randDir + myMapWidth) % myMapWidth;
						x *= tileSize.myX;
						if (randDir == 1)
							x += 1;
						else
							x += tileSize.myX - 2.f;

						float y = (node + randDir) / myMapWidth;
						y *= tileSize.myY;
						y += myMap->GetTileSize().myY + myDropSprite.GetSize().myY / 2.f;

						y -= rand() % static_cast<int>(tileSize.myY * amount);

						RemoveWaterFromNode(1, node);
						AddDrop({ x, y }, { static_cast<float>((randDir * 10.f * amount) / (4.f + rand() % 13)), 0 });
					}
					else if (myMap->Collided(node + randDir) == false && myWaterLevel[node + randDir] < myWaterLevel[node] && myWaterLevel[node + randDir] < MAX_WATERLEVEL)
					{
						RemoveWaterFromNode(1, node);
						AddWaterToNode(1, node + randDir);
					}
				}
			}
		}
	}

	PlayerWading(aPlayer);
	CollideDropsVsPlayer(aPlayer);
	UpdateDrops();
}

void WaterMap::ResolveWaterCollision(PhysicBody& aPhysicBody)
{
	if (aPhysicBody.GetOption(ePhysicBodyOptions::eKinetic) == false)
	{
		FloatOnWater(aPhysicBody);
	}
	SplashWater(aPhysicBody);
}

unsigned char WaterMap::GetWaterLevelAtPoint(const Vector2f& aWorldPosition) const
{
	const int nodeX = aWorldPosition.myX / myMap->GetTileSize().myX;
	const int nodeY = aWorldPosition.myY / myMap->GetTileSize().myY;
	const int node = nodeX + nodeY * myMapWidth;

	const unsigned char waterLevel = myWaterLevel[node];
	const float topTilePos = static_cast<int>(nodeY) * myMap->GetTileSize().myY;
	const float waterYPos = topTilePos + myMap->GetTileSize().myY - ((waterLevel / static_cast<float>(MAX_WATERLEVEL)) * static_cast<float>(myMap->GetTileSize().myY));

	return myWaterLevel[node] * static_cast<int>(aWorldPosition.myY >= waterYPos);
}

bool WaterMap::TryTakeWater(const unsigned char aAmount, const Vector2f& aWorldPosition)
{
	const int nodeX = static_cast<int>(aWorldPosition.myX / this->myMap->GetTileSize().myX);
	const int nodeY = static_cast<int>(aWorldPosition.myY / this->myMap->GetTileSize().myY);

	const int node = nodeX + nodeY * myMapWidth;
	assert(node < myWaterLevel.Size() && "Tried to take water outside of map!");
	if (myWaterLevel[node] >= aAmount)
	{
		RemoveWaterFromNode(aAmount, node);
		return true;
	}

	return false;
}

int WaterMap::GetWaterYFromPosition(const Vector2f& aPosition) const
{
	const unsigned char waterLevel = GetWaterLevelAtPoint(aPosition);
	const float waterHeight = (waterLevel / static_cast<float>(MAX_WATERLEVEL)) * myMap->GetTileSize().myY;
	int y = static_cast<int>(aPosition.myY / myMap->GetTileSize().myY) * myMap->GetTileSize().myY;
	y += myMap->GetTileSize().myY - waterHeight;
	return y;
}

int WaterMap::GetNodeIndex(const Vector2f& aWorldPosition) const
{
	return (static_cast<int>(aWorldPosition.myX / myMap->GetTileSize().myX)) +
		(static_cast<int>(aWorldPosition.myY / myMap->GetTileSize().myY) * myMapWidth);
}

void WaterMap::FloatOnWater(PhysicBody& aPhysicBody)
{
	unsigned char waterLevel = GetWaterLevelAtPoint(aPhysicBody.GetPosition());
	float waterHeight = (waterLevel / static_cast<float>(MAX_WATERLEVEL)) * myMap->GetTileSize().myY;

	if (waterHeight > myMap->GetTileSize().myY - (aPhysicBody.GetPosition().myY - ((int)(aPhysicBody.GetPosition().myY / myMap->GetTileSize().myY) * myMap->GetTileSize().myY)))
	{
		aPhysicBody.AddForce({ 0, -1.2f / aPhysicBody.GetMass() });
	}
}

void WaterMap::SplashWater(PhysicBody& aPhysicBody)
{
	if (aPhysicBody.GetVelocity().myY != 0.f && aPhysicBody.GetMass() > 4.f)
	{	
		const Vector2f& middleBottom = aPhysicBody.GetMiddleBottom();
		const Vector2f oldMiddleBottom = aPhysicBody.GetOldPosition() + Vector2f(0, aPhysicBody.GetHalfSize().myY + 1);
		const unsigned char bottomWaterLevel = GetWaterLevelAtPoint(middleBottom);
		const char prevBottomWaterLevel = GetWaterLevelAtPoint(oldMiddleBottom);
		if (aPhysicBody.GetVelocity().myY > 0.f && bottomWaterLevel > 0 && prevBottomWaterLevel == 0_uc)
		{
			const float topTilePos = static_cast<int>(middleBottom.myY / myMap->GetTileSize().myY) * myMap->GetTileSize().myY;
			const float waterYPos = topTilePos + myMap->GetTileSize().myY - ((bottomWaterLevel / static_cast<float>(MAX_WATERLEVEL)) * static_cast<float>(myMap->GetTileSize().myY));
			if (middleBottom.myY >= waterYPos)
			{
				TryTakeWater(bottomWaterLevel / 2, middleBottom);
				PostMaster::GetInstance()->SendSoundEvent("waterSplash", aPhysicBody.GetPosition());
				for (int dropCount = 0; dropCount < bottomWaterLevel / 2; dropCount++)
				{
					Vector2f dropCreationPos(middleBottom.myX + CU::RandomF(-8.f, 8.f), waterYPos);
					AddDrop(dropCreationPos, { CU::RandomF(-1.3f, 1.3f), CU::RandomF(-6.f, -4.f) });
				}
			}
		}
		else if (aPhysicBody.GetVelocity().myY < 0.f && prevBottomWaterLevel > 0 && bottomWaterLevel == 0)
		{
			PostMaster::GetInstance()->SendSoundEvent("waterUp", aPhysicBody.GetPosition());
			int drops = MIN(10, prevBottomWaterLevel);
			TryTakeWater(drops, oldMiddleBottom);
			for (int dropCount = 0; dropCount < drops; dropCount++)
			{
				Vector2f dropCreationPos(middleBottom.myX + CU::RandomF(-8.f, 8.f), middleBottom.myY);
				AddDrop(dropCreationPos, Vector2f(CU::RandomF(-0.5f, 0.5f), CU::RandomF(-2.f, 1.f)) + aPhysicBody.GetVelocity() / 2.f);
			}
		}
	}
}

void WaterMap::CollideDropsVsPlayer(const Player& aPlayer)
{
	static int lastFreq = 0;

	if (myPlayerWaterHitFreq > 0)
		myPlayerWaterHitFreq -= 4;

	if (myPlayerWaterHitFreq > lastFreq && myPlayerWaterHitFreq <= 40)
		PostMaster::GetInstance()->SendSoundEvent("randomDrop");

	lastFreq = myPlayerWaterHitFreq;

	if (myPlayerWaterHitFreq < 40)
	{
		PostMaster::GetInstance()->SendSoundEvent("dropHitStop");
	}
	else if (myPlayerWaterHitFreq > 60)
	{
		PostMaster::GetInstance()->SendSoundEvent("dropHit");
	}

	for (int dropIndex = 0; dropIndex < myDrops.Size(); dropIndex++)
	{
		if (aPlayer.GetPhysicBody().Collides(myDrops[dropIndex].myPosition) )//&&
			//aPlayer.GetPhysicBody().GetVelocity().myY * myDrops[dropIndex].myVelocity.myY < 0.f) // has not same sign
		{
			if (myDrops[dropIndex].myVelocity.myY > 2.f && aPlayer.GetPhysicBody().GetVelocity().myY < 1.f)
			{
				if (myPlayerWaterHitFreq < 60)
					myPlayerWaterHitFreq += 10;
			}
			if (myDrops[dropIndex].myPosition.myY < aPlayer.GetPhysicBody().GetPosition().myY)
			{
				if (myDrops[dropIndex].myVelocity.myY > 0.f)
					myDrops[dropIndex].myVelocity.myY *= -0.6f;
			}
			if (myDrops[dropIndex].myPosition.myX < aPlayer.GetPhysicBody().GetPosition().myX)
			{
				myDrops[dropIndex].myVelocity.myX -= 0.8f - (rand() % 100) / 200.f;
			}
			else
			{
				myDrops[dropIndex].myVelocity.myX += 0.8f + (rand() % 100) / 200.f;
			}
		}
	}
}

void WaterMap::PlayerWading(const Player& aPlayer)
{
	Vector2f point;
	if (aPlayer.GetPhysicBody().GetVelocity().myX > 0.f)
		point = aPlayer.GetPhysicBody().GetRightBottom();
	else
		point = aPlayer.GetPhysicBody().GetLeftBottom();

	point.myY -= 2;
	constexpr int wadeDropAmount = 1;
	if (abs(aPlayer.GetPhysicBody().GetVelocity().myX) > 1.f)
	{
		const unsigned char waterLevel = GetWaterLevelAtPoint(point);
		const unsigned char waterLevelAbove = GetWaterLevelAtPoint(point - Vector2f(0, myMap->GetTileSize().myY));
		if (waterLevel > 25_uc && waterLevelAbove == 0)
		{
			if (TryTakeWater(wadeDropAmount, point))
			{
				float from = 0;
				float to = aPlayer.GetPhysicBody().GetVelocity().myX;
				if (from > to)
					std::swap(from, to);
				int y = GetWaterYFromPosition(point);
				AddDrop(Vector2f(point.myX, y), { CU::RandomF(from, to), CU::RandomF(-4.f, -1.f) });
			}

			PostMaster::GetInstance()->SendSoundEvent("waterWade");
		}
	}
	else
	{
		PostMaster::GetInstance()->SendSoundEvent("waterWadeStop");
	}
}

void WaterMap::UpdateDrops()
{
	for (int dropIndex = 0; dropIndex < myDrops.Size(); dropIndex++)
	{
		myDrops[dropIndex].myVelocity.myY += GRAVITY / 2.f;
		myDrops[dropIndex].myVelocity.myY *= 0.985f;
		myDrops[dropIndex].myPosition += myDrops[dropIndex].myVelocity;
	}

	for (int dropIndex = myDrops.Size()-1; dropIndex >= 0; dropIndex--)
	{
		int nodeIndex = GetNodeIndex(myDrops[dropIndex].myPosition);

		// Remove drops outsize of map
		if (nodeIndex > myWaterLevel.Size() || nodeIndex < 0)
		{
			myDrops.RemoveCyclicAtIndex(dropIndex);
		}
		else if (myWaterLevel[nodeIndex] > 0_uc)
		{
			// Check if drop has reached waterlevel at current node
			const int waterHeight = (myWaterLevel[nodeIndex] / 255.f) * myMap->GetTileSize().myY;
			if (myDrops[dropIndex].myVelocity.myY + (static_cast<int>(myDrops[dropIndex].myPosition.myY) % myMap->GetTileSize().myY) + waterHeight > myMap->GetTileSize().myY)
			{
				myDrops.RemoveCyclicAtIndex(dropIndex);
				int levelToFill = nodeIndex;
				while (myWaterLevel[levelToFill] == MAX_WATERLEVEL)
				{
					levelToFill -= myMapWidth;
				}
				if (levelToFill > myMapWidth)
					AddWaterToNode(1, levelToFill);
			}
		}
		// No water existed at node, check if node was obstacle and land drop there
		else if (myMap->Collided(nodeIndex) == true && nodeIndex >= myMapWidth)
		{
			// Hit was from side?
			int previousNodeIndex = GetNodeIndex(myDrops[dropIndex].myPosition - Vector2f(myDrops[dropIndex].myVelocity.myX, 0.f));
			if (abs(nodeIndex - previousNodeIndex) == 1)
			{
				myDrops[dropIndex].myPosition.myX -= myDrops[dropIndex].myVelocity.myX;
				myDrops[dropIndex].myVelocity.myX = -myDrops[dropIndex].myVelocity.myX / ((rand()% 20) + 3);
				myDrops[dropIndex].myVelocity.myY *= 0.2f;
			}
			else
			{
				myDrops.RemoveCyclicAtIndex(dropIndex);
				// if two drops lands at full waterlevel at same frame, just kill the other one
				if (myWaterLevel[nodeIndex - myMapWidth] < 255_uc)
					AddWaterToNode(1, nodeIndex - myMapWidth);
			}
		}
	}		
}

void WaterMap::DrawDrops(const Vector2f& aCameraPosition)
{
	Vector2<int> size(myDropSprite.GetSize().myX, 0);
	const float dropHeight = myDropSprite.GetSize().myY;
	for (int dropIndex = 0; dropIndex < myDrops.Size(); dropIndex++)
	{

		if (myDrops[dropIndex].myPosition.myX > aCameraPosition.x - SCREEN_WIDTH / 2 &&
			myDrops[dropIndex].myPosition.myX < aCameraPosition.x + SCREEN_WIDTH / 2 &&
			myDrops[dropIndex].myPosition.myY > aCameraPosition.y - SCREEN_HEIGHT / 2 &&
			myDrops[dropIndex].myPosition.myY < aCameraPosition.y + SCREEN_HEIGHT / 2)
		{
			const float angle = -atan2f(myDrops[dropIndex].myVelocity.myX, myDrops[dropIndex].myVelocity.myY);
			size.myY = dropHeight + (myDrops[dropIndex].myVelocity.Length2() / 2.f);
			myDropSprite.Draw({ myDrops[dropIndex].myPosition.myX, myDrops[dropIndex].myPosition.myY }, size, angle);
		}
	}
}

void WaterMap::AddDrop(const Vector2f& aPosition, const Vector2f& aForce)
{
	myDrops.Add({ aPosition, aForce });
}
