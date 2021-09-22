#include "stdafx.h"
#include "Map.h"
#include "waterMap.h"
#include "player.h"
#include "Tileset.h"
#include <fstream>

Map::Map()
{
	myTileset = nullptr;
	myMapHeight = 0;
	myMapWidth = 0;
	myFilename = "not loaded";
	myTilesetName = "not loaded";
	myWaterMap = nullptr;
}

Map::~Map()
{
	SAFE_DELETE(myWaterMap);
}

void Map::Update(Player& aPlayer)
{
	if (IsOutsideMap(aPlayer.GetPhysicBody()) == false)
		myWaterMap->Update(aPlayer);
}

void Map::Draw(const Vector2f& aCameraPosition, const float aCameraZoom)
{
	DL_ASSERT(myTileset != nullptr && "Map is not initiated with tileset!");
	const Vector2<int>& tileSize = myTileset->GetTileSize();

	const int halfScreenWidth = static_cast<int>((SCREEN_WIDTH / 2.f) / aCameraZoom + 0.5f);
	const int halfScreenHeight = static_cast<int>((SCREEN_HEIGHT / 2.f) / aCameraZoom + 0.5f);

	int startTileX = static_cast<int>((aCameraPosition.myX - halfScreenWidth) / myTileWidth);
	int endTileX = static_cast<int>((aCameraPosition.myX + halfScreenWidth) / myTileWidth + 1);
	int startTileY = static_cast<int>((aCameraPosition.myY - halfScreenHeight) / myTileHeight);
	int endTileY = static_cast<int>((aCameraPosition.myY + halfScreenHeight) / myTileHeight + 1);

	startTileX = MAX(0, startTileX);
	startTileY = MAX(0, startTileY);
	endTileX = MIN(endTileX, myMapWidth);
	endTileY = MIN(endTileY, myMapHeight);

	for (int y = startTileY; y < endTileY; y++)
	{
		for (int x = startTileX; x < endTileX; x++)
		{
			myTileset->RenderTile(static_cast<float>(x * tileSize.myX),
				static_cast<float>(y * tileSize.myY), myTileData[x + y * myMapWidth]);
		}
	}	
}

void Map::DrawWater(const Vector2f& aCameraPosition)
{
	myWaterMap->Draw(aCameraPosition);
}

void Map::DebugDraw(const Vector2f& aCameraPosition)
{
}

void Map::Init(std::map<std::string, Tileset>& aTilesets)
{
	DL_ASSERT(aTilesets.size() > 0 && "Tilesets not loaded!");
	DL_ASSERT(myWaterMap == nullptr && "Map already initiated!");

	auto it = aTilesets.find(myTilesetName);
	if (it == aTilesets.end())
	{
		DL_DEBUG("Map %s tried to used a unknown tileset named %s", myFilename.c_str(), myTilesetName.c_str());
		DL_ASSERT(it != aTilesets.end() && "Tileset not found!");
	}

	myTileset = &(*it).second;
	myTileWidth = myTileset->GetTileSize().myX;
	myTileHeight = myTileset->GetTileSize().myY;

	myWaterMap = new WaterMap();
	myWaterMap->Init(*this);

	Message newLevelMsg;
	newLevelMsg.myIntData = myMapWidth * myTileWidth;
	newLevelMsg.mySecondIntData = myMapHeight * myTileHeight;
	newLevelMsg.myMessageType = eMessageTypes::eLevelLoaded;
	PostMaster::GetInstance()->SendMessage(newLevelMsg);
}

void Map::LoadFromFile(const std::string_view aFilename)
{
	std::ifstream loadFile;
	loadFile.open(aFilename.data(), std::fstream::in | std::fstream::binary);
	if (loadFile.is_open() == false)
	{
		DL_DEBUG("Failed to map-file: %s /n", aFilename);
	}
	DL_ASSERT(loadFile.is_open() == true && "Failed to open file!");

	char buffer[1024];

	// read crap from C#
	loadFile.read(buffer, 1);
	loadFile.getline(buffer, 1024);
	myFilename = buffer;

	// read crap from C#
	loadFile.read(buffer, 1);
	loadFile.getline(buffer, 1024);
	myTilesetName = buffer;

	loadFile.read(buffer, sizeof(int));
	myMapWidth = *(reinterpret_cast<int*>(buffer));

	loadFile.read(buffer, sizeof(int));
	myMapHeight = *(reinterpret_cast<int*>(buffer));

	const int numberOfTiles = myMapWidth * myMapHeight;
	myTileData.Resize(numberOfTiles);
	loadFile.read(&myTileData[0], numberOfTiles);

	// Load game objects
	struct ProxyGameObject
	{
		int ID;
		float x, y;
	};

	loadFile.read(buffer, sizeof(int));
	const int gameObjectCount = *(reinterpret_cast<int*>(buffer));
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

	loadFile.close();
}

eCollisionPoint Map::Collided(PhysicBody& aPhysicBody)
{
	DL_ASSERT(myTileset != nullptr && "Map is not initiated with tileset!");
	if (aPhysicBody.IsEnabled() == false)
	{
		return eCollisionPoint::eNoCollision;
	}

	if (IsOutsideMap(aPhysicBody) == true)
		return eCollisionPoint::eNoCollision;

	eCollisionPoint collision = eCollisionPoint::eNoCollision;

	ResolveWaterCollision(aPhysicBody);

	const Vector2f& halfSize = aPhysicBody.GetHalfSize();
	const Vector2f& newPos = aPhysicBody.GetPosition();
	const Vector2f& oldPos = aPhysicBody.GetOldPosition();

	const Vector2f newTopOldLeft(oldPos.myX - halfSize.myX + 1, newPos.myY - halfSize.myY);
	const Vector2f newTopOldRight(oldPos.myX + halfSize.myX - 1, newPos.myY - halfSize.myY);

	const Vector2f newBottomOldLeft(oldPos.myX - halfSize.myX + 1, newPos.myY + halfSize.myY);
	const Vector2f newBottomOldRight(oldPos.myX + halfSize.myX - 1, newPos.myY + halfSize.myY);

	const Vector2f oldTopNewLeft(newPos.myX - halfSize.myX, oldPos.myY - halfSize.myY + 1);
	const Vector2f oldBottomNewLeft(newPos.myX - halfSize.myX, oldPos.myY + halfSize.myY - 1);

	const Vector2f oldTopNewRight(newPos.myX + halfSize.myX, oldPos.myY - halfSize.myY + 1);
	const Vector2f oldBottomNewRight(newPos.myX + halfSize.myX, oldPos.myY + halfSize.myY - 1);

	// collided bottom
	if (Collided(newBottomOldLeft, newBottomOldRight, aPhysicBody, PhysicBody::eLocator::eBottom) == true)
	{
		float bottomPosition = aPhysicBody.GetLeftBottom().myY;
		bottomPosition = static_cast<float>(static_cast<int>(bottomPosition / myTileHeight));
		bottomPosition = bottomPosition * myTileHeight - halfSize.myY;
		aPhysicBody.SetPosition({ aPhysicBody.GetPosition().myX, bottomPosition });
		aPhysicBody.SetVelocity({ aPhysicBody.GetVelocity().myX, -aPhysicBody.GetVelocity().myY * aPhysicBody.GetBounciness() });
		collision = eCollisionPoint::eBottom;
	}

	// collided top
	if (Collided(newTopOldLeft, newTopOldRight, aPhysicBody, PhysicBody::eLocator::eTop) == true)
	{
		float topPosition = aPhysicBody.GetLeftTop().myY;
		topPosition = static_cast<float>(static_cast<int>(topPosition / myTileHeight + 0.5f));
		topPosition = topPosition * myTileHeight + halfSize.myY;
		aPhysicBody.SetPosition({ aPhysicBody.GetPosition().myX, topPosition });
		aPhysicBody.SetVelocity({ aPhysicBody.GetVelocity().myX, -aPhysicBody.GetVelocity().myY * aPhysicBody.GetBounciness() });
		collision = eCollisionPoint::eTop;
	}

	// collided to left
	if (Collided(oldTopNewLeft, oldBottomNewLeft, aPhysicBody, PhysicBody::eLocator::eLeft) == true)
	{
		float leftPosition = aPhysicBody.GetLeftTop().myX;
		leftPosition = static_cast<float>(static_cast<int>(leftPosition / myTileWidth + 0.5f));
		leftPosition = (leftPosition * myTileWidth) + halfSize.myX;
		aPhysicBody.SetPosition({ leftPosition, aPhysicBody.GetPosition().myY });
		aPhysicBody.SetVelocity({ -aPhysicBody.GetVelocity().myX * aPhysicBody.GetBounciness(), aPhysicBody.GetVelocity().myY });
		collision = eCollisionPoint::eLeft;
	}

	// collided to right
	if (Collided(oldTopNewRight, oldBottomNewRight, aPhysicBody, PhysicBody::eLocator::eRight) == true)
	{
		float rightPosition = aPhysicBody.GetRightTop().myX;
		rightPosition = static_cast<float>(static_cast<int>(rightPosition / myTileWidth + 0.5f));
		rightPosition = (rightPosition * myTileWidth) - halfSize.myX;
		aPhysicBody.SetPosition({ rightPosition, aPhysicBody.GetPosition().myY });
		aPhysicBody.SetVelocity({ -aPhysicBody.GetVelocity().myX * aPhysicBody.GetBounciness(), aPhysicBody.GetVelocity().myY });
		collision = eCollisionPoint::eRight;
	}

	return collision;
}

bool Map::Collided(const int aNodeIndex) const
{
	return myTileset->IsObstacle(myTileData[aNodeIndex]);
}

bool Map::Collided(const Vector2f& aPosition) const
{
	const int nodeX = static_cast<int>(aPosition.myX / myTileWidth);
	const int nodeY = static_cast<int>(aPosition.myY / myTileHeight);

	return myTileset->IsObstacle(myTileData[nodeX + nodeY * myMapWidth]);
}

int Map::GetMapWidth() const
{
	return myMapWidth;
}

int Map::GetMapHeight() const
{
	return myMapHeight;
}

const Vector2<int>& Map::GetTileSize() const
{
	return myTileset->GetTileSize();
}

void Map::AddWaterDrop(const Vector2f& aWorldPosition, const Vector2f& aForce)
{
	myWaterMap->AddDrop(aWorldPosition, aForce);
}

void Map::DestroyTile(const Vector2f& aWorldPosition)
{
	const int tileIndex = GetTileIndexFromWorldPosition(aWorldPosition);
	myTileData[tileIndex] = 0;
}

bool Map::TryTakeWater(const unsigned char aAmount, const Vector2f& aWorldPosition)
{
	return myWaterMap->TryTakeWater(aAmount, aWorldPosition);
}

bool Map::IsDestructable(const Vector2f& aWorldPosition) const
{
	const int tileIndex = GetTileIndexFromWorldPosition(aWorldPosition);
	return myTileset->IsDestructable(myTileData[tileIndex]);
}

int Map::GetTileIndexFromWorldPosition(const Vector2f& aWorldPosition) const
{
	return static_cast<int>(aWorldPosition.myX / myTileWidth) +
		static_cast<int>(aWorldPosition.myY / myTileHeight) * myMapWidth;
}

bool Map::Collided(const Vector2f& aStartPosition, const Vector2f& aEndPosition, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator) const
{
	Vector2<int> startNode = { static_cast<int>(aStartPosition.myX / myTileWidth),
								static_cast<int>(aStartPosition.myY / myTileWidth) };
	Vector2<int> endNode = { static_cast<int>(aEndPosition.myX / myTileWidth),
								static_cast<int>(aEndPosition.myY / myTileWidth) };

	for (int y = startNode.myY; y <= endNode.myY; y++)
	{
		for (int x = startNode.myX; x <= endNode.myX; x++)
		{
			if (Collided(x, y, aPhysicBody, aLocator) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool Map::Collided(const int aNodeIndexX, const int aNodeIndexY, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator) const
{
	const int nodeIndex = aNodeIndexX + aNodeIndexY * myMapWidth;
	if (IsValidTileIndex(nodeIndex) && myTileset->IsObstacle(myTileData[nodeIndex]) == true)
	{
		aPhysicBody.AddPhysicState(ePhysicStates::eOnGround, aLocator);
		return true;
	}

	return false;
}

bool Map::IsOutsideMap(const PhysicBody& aPhysicBody) const
{
	return aPhysicBody.GetLeftTop().x < 0 || aPhysicBody.GetLeftTop().y < 0 ||
		aPhysicBody.GetRightBottom().x > myMapWidth * myTileWidth || 
		aPhysicBody.GetRightBottom().y > myMapHeight * myTileHeight;
}

inline bool Map::IsValidTileIndex(const int aTileIndex) const
{
	return aTileIndex >= 0 && aTileIndex < myTileData.Size();
}

void Map::ResolveWaterCollision(PhysicBody& aPhysicBody)
{
	myWaterMap->ResolveWaterCollision(aPhysicBody);
}
