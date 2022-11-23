#include "stdafx.h"
#include "Megaton.h"
#include "World.h"

Megaton* Megaton::ourInstance = nullptr;

Megaton::Megaton()
{
	myWorld = nullptr;
}

Megaton::~Megaton()
{	
	myWorld = nullptr;
}

MapChunk& Megaton::GetMap() const
{
	assert(myWorld != nullptr && "MapChunk not initiated in megaton!");
	return *myWorld->GetMapChunk({ 0.f, 0.f });
}

World& Megaton::GetWorld() const
{
	DL_ASSERT(myWorld != nullptr && "World is nullptr!");
	return *myWorld;
}

std::vector<MapChunk*> Megaton::GetMapChunks(const Vector2f& aWorldPosition, const Vector2<int>& aHalfSize) const
{
	return myWorld->GetMapChunks(aWorldPosition, aHalfSize);
}

MapChunk* Megaton::GetMapChunk(const Vector2f& aWorldPosition) const
{
	return myWorld->GetMapChunk(aWorldPosition);
}

void Megaton::SetWorld(World* aWorld)
{
	assert(aWorld != nullptr && "World is nullptr!");
	myWorld = aWorld;
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
