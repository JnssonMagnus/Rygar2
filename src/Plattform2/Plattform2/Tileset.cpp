#include "stdafx.h"
#include "Tileset.h"

void Tileset::Load(std::ifstream& aStreamLoader)
{
	char buffer[1024];
	char stringSize;
	for (char& c : buffer)
		c = 0;

	aStreamLoader.read(buffer, sizeof(int));
	myVersion = *(reinterpret_cast<int*>(buffer));

	aStreamLoader.read(&stringSize, 1);
	aStreamLoader.read(buffer, stringSize);
	myTilesetName = buffer;

	aStreamLoader.read(&stringSize, 1);
	aStreamLoader.read(buffer, stringSize);
	myTilesetImage = buffer;

	aStreamLoader.read(buffer, sizeof(int));
	myTileSize.myX = *(reinterpret_cast<int*>(buffer));

	aStreamLoader.read(buffer, sizeof(int));
	myTileSize.myY = *(reinterpret_cast<int*>(buffer));

	aStreamLoader.read(buffer, sizeof(int));
	int tileCount = *(reinterpret_cast<int*>(buffer));

	myTileData.Resize(tileCount);
	aStreamLoader.read(reinterpret_cast<char*>(&myTileData[0]), sizeof(TileData) * tileCount);

	// read past autotile info, not used in game mode
	for (size_t i = 0; i < 16; i++)
	{
		aStreamLoader.read(buffer, sizeof(int));
		int autoTiles = *reinterpret_cast<int*>(buffer);
		for (int tileOption = 0; tileOption < autoTiles; tileOption++)
		{
			aStreamLoader.read(buffer, sizeof(int));
		}
	}

	std::stringstream texturePath;
	texturePath << "data/gfx/tilesets/" << myTilesetImage;
	mySprite.Init(texturePath.str().c_str());

	myTileCount = mySprite.GetSize() / myTileSize;
	CalculateTileSourcePositions();
}

const std::string& Tileset::GetName() const
{
	return myTilesetName;
}

void Tileset::RenderTile(const float aX, const float aY, const unsigned char aTileIndex)
{
	Vector2<int> tileSource((aTileIndex % myTileCount.myX) * myTileSize.myX, 
								(aTileIndex / myTileCount.myX) * myTileSize.myY);
	mySprite.Draw({ aX, aY }, tileSource, myTileSize);
}

void Tileset::CalculateTileSourcePositions()
{
	for (int tileIndex = 0; tileIndex < myTileCount.myX * myTileCount.myY; tileIndex++)
	{
		myTileSourcePositions.Add(Vector2<int>((tileIndex % myTileCount.myX) * myTileSize.myX,
												(tileIndex / myTileCount.myX) * myTileSize.myY));
	}
}

