#pragma once
#include <growingArray.h>
#include "Sprite.h"

class Tile;

struct TileData
{
	bool	myIsObstacle;
	bool	myIsDestructable;
	bool	myIsFallout;
};

class Tileset
{
public:
	void							Load(std::ifstream& aStreamLoader);
	const std::string&				GetName() const;
	void							RenderTile(const float aX, const float aY, const unsigned char aTileIndex);
	const Vector2<int>&				GetTileSize() const;
	inline bool						IsObstacle(const unsigned char aTileIndex) const;
	inline bool						IsDestructable(const unsigned char aTileIndex) const;
	inline bool						IsFallout(const unsigned char aTileIndex) const;
	const TileData&					GetTileData(const unsigned char aTileIndex) const;

private:
	void							CalculateTileSourcePositions();
	std::string						myTilesetName;
	std::string						myTilesetImage;
	Vector2<int>					myTileSize;
	Vector2<int>					myTileCount;
	CU::GrowingArray<TileData>		myTileData;
	CU::GrowingArray<Vector2<int>>	myTileSourcePositions;
	Sprite							mySprite;
	int								myVersion;
};

inline const Vector2<int>& Tileset::GetTileSize() const
{
	return myTileSize;
}

inline bool Tileset::IsObstacle(const unsigned char aTileIndex) const
{
	DL_ASSERT(aTileIndex < myTileData.Size() && "Tile index out of bounds!");
	return aTileIndex < 0 || myTileData[aTileIndex].myIsObstacle;
}

inline bool Tileset::IsDestructable(const unsigned char  aTileIndex) const
{
	DL_ASSERT(aTileIndex < myTileData.Size() && "Tile index out of bounds!");
	return myTileData[aTileIndex].myIsDestructable;
}

inline bool Tileset::IsFallout(const unsigned char aTileIndex) const
{
	DL_ASSERT(aTileIndex < myTileData.Size() && "Tile index out of bounds!");
	return myTileData[aTileIndex].myIsFallout;
}

inline const TileData& Tileset::GetTileData(const unsigned char aTileIndex) const
{
	return myTileData[aTileIndex];
}
