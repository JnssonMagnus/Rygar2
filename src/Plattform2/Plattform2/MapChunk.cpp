#include "stdafx.h"
#include "MapChunk.h"
#include "waterMap.h"
#include "player.h"
#include "Tileset.h"
#include <fstream>

MapChunk::MapChunk()
{
	myTileset = nullptr;
	myMapHeight = 0;
	myMapWidth = 0;
	myFilename = "not loaded";
	myTilesetName = "not loaded";
	myWaterMap = nullptr;
}

MapChunk::~MapChunk()
{
	SAFE_DELETE(myWaterMap);
}

void MapChunk::UpdateWaterMovement()
{
	myWaterMap->Update();
}

void MapChunk::UpdatePlayerVsWaterCollisions(Player& aPlayer)
{
	if (IsOutsideMap(aPlayer.GetPhysicBody()) == false) {
		myWaterMap->UpdatePlayerCollision(aPlayer);
	}
}

void MapChunk::Draw(const Vector2f& aCameraPosition, const float aCameraZoom)
{
	DL_ASSERT(myTileset != nullptr && "MapChunk is not initiated with tileset!");
	const Vector2<int>& tileSize = myTileset->GetTileSize();

	const int halfScreenWidth = static_cast<int>((SCREEN_WIDTH / 2.f) / aCameraZoom + 0.5f);
	const int halfScreenHeight = static_cast<int>((SCREEN_HEIGHT / 2.f) / aCameraZoom + 0.5f);

	int startTileX = static_cast<int>((aCameraPosition.myX - halfScreenWidth - myWorldPosition.myX) / myTileWidth);
	int endTileX = static_cast<int>((aCameraPosition.myX + halfScreenWidth - myWorldPosition.myX) / myTileWidth + 1);
	int startTileY = static_cast<int>((aCameraPosition.myY - halfScreenHeight - myWorldPosition.myY) / myTileHeight);
	int endTileY = static_cast<int>((aCameraPosition.myY + halfScreenHeight - myWorldPosition.myY) / myTileHeight + 1);

	startTileX = MAX(0, startTileX);
	startTileY = MAX(0, startTileY);
	endTileX = MIN(endTileX, myMapWidth);
	endTileY = MIN(endTileY, myMapHeight);

	for (int y = startTileY; y < endTileY; y++)
	{
		for (int x = startTileX; x < endTileX; x++)
		{
			myTileset->RenderTile(static_cast<float>(x * tileSize.myX) + myWorldPosition.myX,
				static_cast<float>(y * tileSize.myY) + myWorldPosition.myY, myTileData[x + y * myMapWidth]);
		}
	}	
}

void MapChunk::DrawWater(const Vector2f& aCameraPosition)
{
	myWaterMap->Draw(aCameraPosition);
}

void MapChunk::DebugDraw(const Vector2f& aCameraPosition)
{

}

void MapChunk::Init(std::map<std::string, Tileset>& aTilesets, const Vector2f& aWorldPosition)
{
	DL_ASSERT(aTilesets.size() > 0 && "Tilesets not loaded!");
	DL_ASSERT(myWaterMap == nullptr && "MapChunk already initiated!");

	auto it = aTilesets.find(myTilesetName);
	if (it == aTilesets.end())
	{
		DL_DEBUG("MapChunk %s tried to used a unknown tileset named %s", myFilename.c_str(), myTilesetName.c_str());
		DL_ASSERT(it != aTilesets.end() && "Tileset not found!");
	}

	myTileset = &(*it).second;
	myTileWidth = myTileset->GetTileSize().myX;
	myTileHeight = myTileset->GetTileSize().myY;
	
	myWorldPosition = aWorldPosition;

	myWaterMap = new WaterMap();
	myWaterMap->Init(*this);

	Message newLevelMsg;
	newLevelMsg.myIntData = myMapWidth * myTileWidth;
	newLevelMsg.mySecondIntData = myMapHeight * myTileHeight;
	newLevelMsg.myMessageType = eMessageTypes::eLevelLoaded;
	PostMaster::GetInstance()->SendMessage(newLevelMsg);

}

void MapChunk::LoadFromFile(const std::string_view aFilename)
{
	std::ifstream loadFile;
	loadFile.open(aFilename.data(), std::fstream::in | std::fstream::binary);
	if (loadFile.is_open() == false)
	{
		DL_DEBUG("Failed to map-file: %s /n", aFilename);
	}
	DL_ASSERT(loadFile.is_open() == true && "Failed to open file!");

	char buffer[2048];

	// version
	loadFile.read(buffer, sizeof(int32_t));
	int32_t version = *(reinterpret_cast<int32_t*>(buffer));

	// read string length
	loadFile.read(buffer, 1);

	loadFile.getline(buffer, 1024);
	myFilename = buffer;

	// read string length
	loadFile.read(buffer, 1);

	loadFile.getline(buffer, 1024);
	myTilesetName = buffer;

	loadFile.read(buffer, sizeof(int32_t));
	myMapWidth = *(reinterpret_cast<int32_t*>(buffer));

	loadFile.read(buffer, sizeof(int32_t));
	myMapHeight = *(reinterpret_cast<int32_t*>(buffer));

	const int numberOfTiles = myMapWidth * myMapHeight;
	assert(numberOfTiles <= sizeof(buffer) && "Buffer size to small! Increase size!");
	loadFile.read(buffer, numberOfTiles);

	myTileData.Resize(numberOfTiles);
	memcpy(&myTileData[0], buffer, numberOfTiles);

	loadFile.read(buffer, sizeof(int32_t));
	int32_t gameObjectCount = *(reinterpret_cast<int32_t*>(buffer));

	// Load game objects
	struct ProxyGameObject
	{
		int32_t ID;
		float x, y;
	};

	if (gameObjectCount > 0) 
	{
		ProxyGameObject* gameObjects = new ProxyGameObject[gameObjectCount];

		loadFile.read(reinterpret_cast<char*>(gameObjects), sizeof(ProxyGameObject) * gameObjectCount);

		for (int gameObjectIndex = 0; gameObjectIndex < gameObjectCount; gameObjectIndex++)
		{
			Message newObjectMessage(eMessageTypes::eCreateObject);
			newObjectMessage.myPosition.myX = gameObjects[gameObjectIndex].x;
			newObjectMessage.myPosition.myY = gameObjects[gameObjectIndex].y;
			newObjectMessage.myIntData = gameObjects[gameObjectIndex].ID;
			PostMaster::GetInstance()->SendMessage(newObjectMessage);
		}

		delete[] gameObjects;
		gameObjects = nullptr;
	}

	// load enemies
	struct ProxyEnemy
	{
		int32_t ID;
		float x, y;
	};

	loadFile.read(buffer, sizeof(int32_t));
	const int32_t enemyCount = *(reinterpret_cast<int32_t*>(buffer));
	ProxyEnemy* enemies = new ProxyEnemy[enemyCount];
	loadFile.read(reinterpret_cast<char*>(enemies), sizeof(ProxyEnemy)* enemyCount);
	for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++)
	{
		Message newEnemyMessage(eMessageTypes::eCreateEnemy);
		newEnemyMessage.myPosition.myX = enemies[enemyIndex].x;
		newEnemyMessage.myPosition.myY = enemies[enemyIndex].y;
		newEnemyMessage.myIntData = enemies[enemyIndex].ID;
		PostMaster::GetInstance()->SendMessage(newEnemyMessage);
	}

	loadFile.close();
}

MapCollisionData MapChunk::Collided(PhysicBody& aPhysicBody)
{
	MapCollisionData mapCollisionData;

	DL_ASSERT(myTileset != nullptr && "MapChunk is not initiated with tileset!");
	if (aPhysicBody.IsEnabled() == false)
	{
		return mapCollisionData;
	}

	if (IsOutsideMap(aPhysicBody) == true)
		return mapCollisionData;

	eCollisionPoint collision = eCollisionPoint::eNoCollision;

	ResolveWaterCollision(aPhysicBody);

	const Vector2f& halfSize = aPhysicBody.GetHalfSize();
	const Vector2f& newPos = aPhysicBody.GetPosition();
	const Vector2f& oldPos = aPhysicBody.GetOldPosition();

	Vector2f newTopOldLeft(oldPos.myX - halfSize.myX + 1, newPos.myY - halfSize.myY);
	Vector2f newTopOldRight(oldPos.myX + halfSize.myX - 1, newPos.myY - halfSize.myY);

	Vector2f newBottomOldLeft(oldPos.myX - halfSize.myX + 1, newPos.myY + halfSize.myY);
	Vector2f newBottomOldRight(oldPos.myX + halfSize.myX - 1, newPos.myY + halfSize.myY);

	Vector2f oldTopNewLeft(newPos.myX - halfSize.myX, oldPos.myY - halfSize.myY + 1);
	Vector2f oldBottomNewLeft(newPos.myX - halfSize.myX, oldPos.myY + halfSize.myY - 1);

	Vector2f oldTopNewRight(newPos.myX + halfSize.myX, oldPos.myY - halfSize.myY + 1);
	Vector2f oldBottomNewRight(newPos.myX + halfSize.myX, oldPos.myY + halfSize.myY - 1);

	int safeGuard = 0;
	// collided bottom
	while (Collided(newBottomOldLeft, newBottomOldRight, aPhysicBody, PhysicBody::eLocator::eBottom, mapCollisionData) == true)
	{
		float bottomPosition = aPhysicBody.GetLeftBottom().myY;
		bottomPosition = static_cast<float>(static_cast<int>(bottomPosition / myTileHeight));
		bottomPosition = bottomPosition * myTileHeight - halfSize.myY;
		aPhysicBody.SetPosition({ aPhysicBody.GetPosition().myX, bottomPosition });
		aPhysicBody.SetVelocity({ aPhysicBody.GetVelocity().myX, -aPhysicBody.GetVelocity().myY * aPhysicBody.GetBounciness() });
		newBottomOldLeft.y = newBottomOldRight.y = bottomPosition;
		collision = eCollisionPoint::eBottom;		
		if (safeGuard++ > 20) break;
	}

	safeGuard = 0;
	// collided top
	while (Collided(newTopOldLeft, newTopOldRight, aPhysicBody, PhysicBody::eLocator::eTop, mapCollisionData) == true)
	{
		float topPosition = aPhysicBody.GetLeftTop().myY;
		topPosition = static_cast<float>(std::ceil(topPosition / myTileHeight));
		topPosition = topPosition * myTileHeight + halfSize.myY + 1;
		aPhysicBody.SetPosition({ aPhysicBody.GetPosition().myX, topPosition });
		aPhysicBody.SetVelocity({ aPhysicBody.GetVelocity().myX, -aPhysicBody.GetVelocity().myY * aPhysicBody.GetBounciness() });
		newTopOldLeft.y = newTopOldRight.y = topPosition;
		collision = eCollisionPoint::eTop;
		if (safeGuard++ > 20) break;
	}

	safeGuard = 0;
	// collided to left
	while (Collided(oldTopNewLeft, oldBottomNewLeft, aPhysicBody, PhysicBody::eLocator::eLeft, mapCollisionData) == true)
	{
		float leftPosition = aPhysicBody.GetLeftTop().myX;
		leftPosition = static_cast<float>(std::ceil(leftPosition / myTileWidth));
		leftPosition = (leftPosition * myTileWidth) + halfSize.myX + 1;
		aPhysicBody.SetPosition({ leftPosition, aPhysicBody.GetPosition().myY });
		aPhysicBody.SetVelocity({ -aPhysicBody.GetVelocity().myX * aPhysicBody.GetBounciness(), aPhysicBody.GetVelocity().myY });

		oldTopNewLeft.x = oldBottomNewLeft.x = leftPosition;
		collision = eCollisionPoint::eLeft;
		if (safeGuard++ > 20) break;
	}

	safeGuard = 0;
	// collided to right
	while (Collided(oldTopNewRight, oldBottomNewRight, aPhysicBody, PhysicBody::eLocator::eRight, mapCollisionData) == true)
	{
		float rightPosition = aPhysicBody.GetRightTop().myX;
		rightPosition = static_cast<float>(static_cast<int>(rightPosition / myTileWidth));
		rightPosition = (rightPosition * myTileWidth) - halfSize.myX - 1;
		aPhysicBody.SetPosition({ rightPosition, aPhysicBody.GetPosition().myY });
		aPhysicBody.SetVelocity({ -aPhysicBody.GetVelocity().myX * aPhysicBody.GetBounciness(), aPhysicBody.GetVelocity().myY });
		oldTopNewRight.x = oldBottomNewRight.x = rightPosition;
		collision = eCollisionPoint::eRight;
		if (safeGuard++ > 20) break;
	}

	return mapCollisionData;
}

bool MapChunk::Collided(const int aNodeIndex) const
{
	return myTileset->IsObstacle(myTileData[aNodeIndex]);
}

bool MapChunk::Collided(const Vector2f& aPosition) const
{
	const int nodeX = static_cast<int>((aPosition.myX - myWorldPosition.myX) / myTileWidth);
	const int nodeY = static_cast<int>((aPosition.myY - myWorldPosition.myY) / myTileHeight);

	const int nodeIndex = nodeX + nodeY * myMapWidth;

	return nodeIndex < myTileData.Size() && nodeIndex >= 0 && myTileset->IsObstacle(myTileData[nodeX + nodeY * myMapWidth]);
}

int MapChunk::GetMapWidth() const
{
	return myMapWidth;
}

int MapChunk::GetMapHeight() const
{
	return myMapHeight;
}

const Vector2<int>& MapChunk::GetTileSize() const
{
	return myTileset->GetTileSize();
}

const Vector2f& MapChunk::GetWorldPosition() const
{
	return myWorldPosition;
}

void MapChunk::AddWaterDrop(const Vector2f& aWorldPosition, const Vector2f& aForce)
{
	myWaterMap->AddDrop(aWorldPosition, aForce);
}

void MapChunk::DestroyTile(const Vector2f& aWorldPosition)
{
	const int tileIndex = GetTileIndexFromWorldPosition(aWorldPosition);
	myTileData[tileIndex] = 0;
}

bool MapChunk::TryTakeWater(const unsigned char aAmount, const Vector2f& aWorldPosition)
{
	return myWaterMap->TryTakeWater(aAmount, aWorldPosition);
}

void MapChunk::AddToWaterLevel(const unsigned char aAmount, const Vector2f& aWorldPosition)
{
	myWaterMap->AddToWaterLevel(aAmount, aWorldPosition);
}

bool MapChunk::IsDestructable(const Vector2f& aWorldPosition) const
{
	const int tileIndex = GetTileIndexFromWorldPosition(aWorldPosition);
	return myTileset->IsDestructable(myTileData[tileIndex]);
}

bool MapChunk::PositionHasImpassibleTile(const Vector2f& aWorldPosition) const
{
	const auto tileIndex = GetTileIndexFromWorldPosition(aWorldPosition);
	return tileIndex >= 0 && myTileset->IsObstacle(myTileData[tileIndex]);
	
}

int MapChunk::GetTileIndexFromWorldPosition(const Vector2f& aWorldPosition) const
{
	return static_cast<int>((aWorldPosition.myX - myWorldPosition.myX) / myTileWidth) +
		static_cast<int>((aWorldPosition.myY - myWorldPosition.myY) / myTileHeight) * myMapWidth;
}

bool MapChunk::Collided(const Vector2f& aStartPosition, const Vector2f& aEndPosition, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator, MapCollisionData& mapCollisionData) const
{
	Vector2<int> startNode = { static_cast<int>(floor((aStartPosition.myX - myWorldPosition.myX) / myTileWidth)),
								static_cast<int>(floor((aStartPosition.myY - myWorldPosition.myY) / myTileHeight)) };
	Vector2<int> endNode = { static_cast<int>(floor((aEndPosition.myX - myWorldPosition.myX) / myTileWidth)),
								static_cast<int>(floor((aEndPosition.myY - myWorldPosition.myY) / myTileHeight)) };
	
	startNode.x = std::max(0, startNode.x);
	startNode.y = std::max(0, startNode.y);
	endNode.x = std::min(myMapWidth - 1, endNode.x);
	endNode.y = std::min(myMapHeight - 1, endNode.y);

	for (int y = startNode.myY; y <= endNode.myY; y++)
	{
		for (int x = startNode.myX; x <= endNode.myX; x++)
		{
			const int nodeIndex = x + y * myMapWidth;
			mapCollisionData.myCollidedTileTypes.emplace(&myTileset->GetTileData(myTileData[nodeIndex]));
			if (Collided(nodeIndex, aPhysicBody, aLocator) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool MapChunk::Collided(const int aNodeIndex, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator) const
{
	
	if (IsValidTileIndex(aNodeIndex) && myTileset->IsObstacle(myTileData[aNodeIndex]) == true)
	{
		aPhysicBody.AddPhysicState(ePhysicStates::eOnGround, aLocator);
		return true;
	}

	return false;
}

bool MapChunk::IsOutsideMap(const PhysicBody& aPhysicBody) const
{
	return aPhysicBody.GetRightBottom().x < myWorldPosition.myX || aPhysicBody.GetRightBottom().y < myWorldPosition.myY ||
		aPhysicBody.GetLeftTop().x > myWorldPosition.myX + myMapWidth * myTileWidth ||
		aPhysicBody.GetLeftTop().y > myWorldPosition.myY + myMapHeight * myTileHeight;
}

inline bool MapChunk::IsValidTileIndex(const int aTileIndex) const
{
	return aTileIndex >= 0 && aTileIndex < myTileData.Size();
}

void MapChunk::ResolveWaterCollision(PhysicBody& aPhysicBody)
{
	//myWaterMap->ResolveWaterCollision(aPhysicBody);
}
