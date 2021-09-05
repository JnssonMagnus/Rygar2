#pragma once
#include <memory>

class Map;
class WaterMap;
class LuaManager;

class Megaton
{
public:
	Map&						GetMap() const;
	void						SetMap(Map* aMap);

	std::shared_ptr<LuaManager>	GetLuaManager();
	void						SetLuaManager(std::weak_ptr<LuaManager> aLuaManager);

	static void					Create();
	static Megaton&				GetInstance();
	static void					Destroy();

private:
								Megaton();
								~Megaton();
	static Megaton*				ourInstance;

	Map*						myMap;
	std::weak_ptr<LuaManager>	myLuaManager;

};
