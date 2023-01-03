#include "stdafx.h"
#include "World.h"
#include "MapChunk.h"
#include "Settings.h"
#include <filesystem>

World::World()
{
	LoadTilesets(std::string(gDataPath) + "data/tilesets/tilesets.dat");
}

MapChunk* World::GetMapChunk(const Vector2f worldPosition)
{
    const ChunkId chunkId = GetChunkIdFromWorldPosition(worldPosition);
    const auto it = myMapChunks.find(chunkId);
	if (it == myMapChunks.end()) {
		return TryLoadAndReturnMapChunk(chunkId);
	}
    return it->second;
}

std::vector<MapChunk*> World::GetMapChunks(const Vector2f worldPosition, const Vector2<int> aHalfSize)
{
	std::vector<MapChunk*> mapChunks;
	const int startX = std::floor((worldPosition.myX - aHalfSize.myX) / CHUNK_WIDTH);
	const int endX = std::floor((worldPosition.myX + aHalfSize.myX) / CHUNK_WIDTH);
	const int startY = std::floor((worldPosition.myY - aHalfSize.myY) / CHUNK_HEIGHT);
	const int endY = std::floor((worldPosition.myY + aHalfSize.myY) / CHUNK_HEIGHT);
	for (int x = startX; x <= endX; x++) {
		for (int y = startY; y <= endY; y++) {
			auto chunkId = GetChunkIdFromChunkCoordinates(x, y);
			auto chunk = myMapChunks.find(chunkId);
			if (chunk != myMapChunks.end()) {
				mapChunks.push_back(chunk->second);
			}
			else
			{
				if (MapChunk* loadedChunk = TryLoadAndReturnMapChunk(chunkId)) {
					mapChunks.push_back(loadedChunk);
				}
			}
		}
	}

	return mapChunks;
}

bool World::PositionHasImpassibleTile(const Vector2f& aWorldPosition)
{
	auto mapChunk = GetMapChunk(aWorldPosition);
	if (!mapChunk) {
		return false;
	}

	return mapChunk->PositionHasImpassibleTile(aWorldPosition);
}

void World::UnloadWorld()
{
	for (auto [id, chunk] : myMapChunks)
	{
		delete chunk;
	}

	myMapChunks.clear();
}

void World::LoadTilesets(const std::string_view aTilesetDatafile)
{
	std::ifstream tilesetLoader;
	tilesetLoader.open(aTilesetDatafile.data(), std::fstream::in | std::fstream::binary);
	if (tilesetLoader.is_open() == false)
	{
		DL_DEBUG("Failed to open tileset data file: %s", aTilesetDatafile);
		DL_ASSERT(tilesetLoader.is_open() == true && "Failed to open tilsets datafile!");
	}

	char buffer[1024];

	tilesetLoader.read(buffer, sizeof(int));
	int tilesetCount = (*reinterpret_cast<int*>(buffer));

	for (int tilesetIndex = 0; tilesetIndex < tilesetCount; tilesetIndex++)
	{
		Tileset newTileset;
		newTileset.Load(tilesetLoader);
		myTilesets[newTileset.GetName()] = newTileset;
	}

	tilesetLoader.close();
}

Vector2f World::GetWorldPositionFromChunkId(ChunkId aMapId) const
{
	constexpr int HIGH_ID = 10000000;
	Vector2f worldPosition;
	worldPosition.x = (aMapId / HIGH_ID) * CHUNK_WIDTH;
	worldPosition.y = (aMapId - ((aMapId / HIGH_ID) * HIGH_ID)) * CHUNK_HEIGHT;
	return worldPosition;
}

MapChunk* World::TryLoadAndReturnMapChunk(const ChunkId aChunkId)
{
	std::string chunkFilename = gDataPath + std::string("data/levels/chunk_") + std::to_string(aChunkId);
	if (std::filesystem::exists(chunkFilename) == false)
	{
		return nullptr;
	}

	MapChunk* newChunk = new MapChunk();
	newChunk->LoadFromFile(chunkFilename);
	newChunk->Init(myTilesets, GetWorldPositionFromChunkId(aChunkId));
	myMapChunks[aChunkId] = newChunk;
	return newChunk;
}
