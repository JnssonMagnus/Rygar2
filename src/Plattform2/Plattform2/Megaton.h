#pragma once
#include <memory>

class Map;
class WaterMap;
class LuaManager;
class GameObjectFactory;

class Megaton
{
public:
	Map&								GetMap() const;
	void								SetMap(Map* aMap);

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

	Map*								myMap;
	GameObjectFactory*					myGameObjectFactory = nullptr;
	std::weak_ptr<LuaManager>			myLuaManager;

};
