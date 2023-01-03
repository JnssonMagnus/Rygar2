#pragma once
#include "Settings.h"
#include "Tileset.h"
#include "../CommonUtilities/Vector2.h"

class MapChunk;

class World
{
public:
							World();
	MapChunk*				GetMapChunk(const Vector2f worldPosition);
	std::vector<MapChunk*>	GetMapChunks(const Vector2f worldPosition, const Vector2<int> aHalfSize);
	using ChunkId = int;

	bool					PositionHasImpassibleTile(const Vector2f& aWorldPosition);
	void					UnloadWorld();
	
private:
	inline ChunkId			GetChunkIdFromWorldPosition(const Vector2f worldPosition) const;
	inline ChunkId			GetChunkIdFromChunkCoordinates(const int aX, const int aY) const;
	void					LoadTilesets(const std::string_view aTilesetDatafile);
	Vector2f				GetWorldPositionFromChunkId(ChunkId aMapId) const;
	MapChunk*				TryLoadAndReturnMapChunk(const ChunkId aMapId);
	std::unordered_map<ChunkId, MapChunk*>	myMapChunks;
	std::map<std::string, Tileset>			myTilesets;
};


World::ChunkId World::GetChunkIdFromWorldPosition(const Vector2f worldPosition) const
{
	constexpr int HIGH_ID = 10000000;

	const int highId = ((static_cast<int>(worldPosition.myX) / TILE_WIDTH) / MAP_WIDTH) * HIGH_ID;
	const int lowId = (static_cast<int>(worldPosition.myY) / TILE_HEIGHT) / MAP_HEIGHT;
	return lowId + highId;
}

World::ChunkId World::GetChunkIdFromChunkCoordinates(const int aX, const int aY) const
{
	constexpr int HIGH_ID = 10000000;

	const int highId = aX * HIGH_ID;
	const int lowId = aY;
	return lowId + highId;
}
