#include "PhysicBody.h"
#include "CollisionPoint.h"
#include <StaticArray.h>

class Tileset;
class WaterMap;
class HeatMap;
class Player;

class Map
{
public:
						Map();
						~Map();
	void				Update(Player& aPlayer);
	void				Draw(const Vector2f& aCameraPosition, const float aCameraZoom = 1.f);
	void				DrawWater(const Vector2f& aCameraPosition);
	void				DebugDraw(const Vector2f& aCameraPosition);
	void				Init(std::map<std::string, Tileset>& aTilesets);
	void				LoadFromFile(const char* aFilename);
	eCollisionPoint		Collided(PhysicBody& aPhysicBody);
	bool				Collided(const int aNodeIndex) const;
	bool				Collided(const Vector2f& aPosition) const;
	int					GetMapWidth() const;
	int					GetMapHeight() const;
	const Vector2<int>& GetTileSize() const;

	void				AddWaterDrop(const Vector2f& aWorldPosition, const Vector2f& aForce);
	bool				TryTakeWater(const unsigned char aAmount, const Vector2f& aWorldPosition);

	void				DestroyTile(const Vector2f& aWorldPosition);

	bool				IsDestructable(const Vector2f& aWorldPosition) const;
	int					GetTileIndexFromWorldPosition(const Vector2f& aWorldPosition) const;

private:
	bool				Collided(const Vector2f& aStartPosition, const Vector2f& aEndPosition, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator) const;
	bool				Collided(const int aNodeIndexX, const int aNodeIndexY, PhysicBody& aPhysicBody, const PhysicBody::eLocator aLocator) const;

	inline bool			IsValidTileIndex(const int aTileIndex) const;

	void				ResolveWaterCollision(PhysicBody& aPhysicBody);

	std::string			myFilename;
	std::string			myTilesetName;

	int					myMapWidth = 40;
	int					myMapHeight = 30;
	int					myTileWidth = 0;
	int					myTileHeight = 0;

	Tileset*			myTileset;

	CU::GrowingArray<char>	myTileData;
	WaterMap*			myWaterMap;
};
