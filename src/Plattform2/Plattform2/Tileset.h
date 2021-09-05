#pragma once
#include <growingArray.h>
#include "Sprite.h"

class Tile;

struct TileData
{
	bool	myIsObstacle;
	bool	myIsDestructable;
};

class Tileset
{
public:
	void							Load(std::ifstream& aStreamLoader);
	const std::string&				GetName() const;
	void							RenderTile(const float aX, const float aY, const char aTileIndex);
	const Vector2<int>&				GetTileSize() const;
	inline bool						IsObstacle(const char aTileIndex) const;
	inline bool						IsDestructable(const char aTileIndex) const;

private:
	void							CalculateTileSourcePositions();
	std::string						myTilesetName;
	std::string						myTilesetImage;
	Vector2<int>					myTileSize;
	Vector2<int>					myTileCount;
	CU::GrowingArray<TileData>		myTileData;
	CU::GrowingArray<Vector2<int>>	myTileSourcePositions;
	Sprite							mySprite;
};

inline const Vector2<int>& Tileset::GetTileSize() const
{
	return myTileSize;
}

inline bool Tileset::IsObstacle(const char aTileIndex) const
{
	DL_ASSERT(aTileIndex < myTileData.Size() && "Tile index out of bounds!");
	return aTileIndex < 0 || myTileData[aTileIndex].myIsObstacle;
}

inline bool Tileset::IsDestructable(const char aTileIndex) const
{
	DL_ASSERT(aTileIndex < myTileData.Size() && "Tile index out of bounds!");
	return myTileData[aTileIndex].myIsDestructable;

}
