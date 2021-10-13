#include "stdafx.h"
#include "Megaton.h"

Megaton* Megaton::ourInstance = nullptr;

Megaton::Megaton()
{
	myMap = nullptr;
}

Megaton::~Megaton()
{
	myMap = nullptr;
}

Map& Megaton::GetMap() const
{
	assert(myMap != nullptr && "Map not initiated in megaton!");
	return *myMap;
}

void Megaton::SetMap(Map* aMap)
{
	assert(aMap != nullptr && "Map is nullptr!");
	myMap = aMap;
}

std::shared_ptr<LuaManager> Megaton::GetLuaManager()
{
	return std::shared_ptr<LuaManager>(myLuaManager);
}

void Megaton::SetLuaManager(std::weak_ptr<LuaManager> aLuaManager)
{
	assert(aLuaManager.expired() == false && "LuaManger is nullptr!");
	myLuaManager = aLuaManager;
}

GameObjectFactory& Megaton::GetGameObjectFactory()
{
	DL_ASSERT(myGameObjectFactory != nullptr && "GameObjectFactory not initiated!");
	return *myGameObjectFactory;
}

void Megaton::SetGameObjectFactory(GameObjectFactory& aGameObjectFactory)
{
	DL_ASSERT(myGameObjectFactory == nullptr && "GameObject Factory aready initiated!");
	myGameObjectFactory = &aGameObjectFactory;
}

void Megaton::Create()
{
	assert(ourInstance == nullptr && "Megaton already created!");
	ourInstance = new Megaton();
}

Megaton& Megaton::GetInstance()
{
	assert(ourInstance != nullptr && "Megaton not initated!");
	return *ourInstance;
}

void Megaton::Destroy()
{
	assert(ourInstance != nullptr && "Can't destroy megaton, is nullptr!");
	SAFE_DELETE(ourInstance);
}
