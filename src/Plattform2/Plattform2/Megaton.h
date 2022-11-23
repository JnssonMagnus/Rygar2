#pragma once
#include <memory>

class World;
class MapChunk;
class WaterMap;
class LuaManager;
class GameObjectFactory;

class Megaton
{
public:
	MapChunk&							GetMap() const;
	World&								GetWorld() const;
	std::vector<MapChunk*>				GetMapChunks(const Vector2f& aWorldPosition, const Vector2<int>& aHalfSize) const;
	MapChunk*							GetMapChunk(const Vector2f& aWorldPosition) const;
	void								SetWorld(World* aWorld);

	std::shared_ptr<LuaManager>			GetLuaManager();
	void								SetLuaManager(std::weak_ptr<LuaManager> aLuaManager);

	[[nodiscard]] GameObjectFactory&	GetGameObjectFactory();
	void								SetGameObjectFactory(GameObjectFactory& aGameObjectFactory);


	static void							Create();
	static Megaton&						GetInstance();
	static void							Destroy();

private:
										Megaton();
										~Megaton();
	static Megaton*						ourInstance;

	World*								myWorld;
	GameObjectFactory*					myGameObjectFactory = nullptr;
	std::weak_ptr<LuaManager>			myLuaManager;

};
