#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObjectType.h"
#include <ObjectPool.h>
#include "..\external\rapidJSON\document.h"
#include "..\external\rapidJSON\reader.h"

#include "Apple.h"
#include "Hammer.h"
#include "Seed.h"
#include "Boulder.h"
#include "RainCloud.h"
#include "bucket.h"
#include "Tree.h"
#include "TreeType.h"
#include "FireFlower.h"
#include "Player.h"
#include "Enemy.h"
#include "Sink.h"
#include "Bullet.h"
#include "Grenade.h"
#include "Explosion.h"
#include "EnemySpawner.h"
#include "BigEnemy.h"
#include "BloodPortal.h"
#include "Disk.h"
#include <istream>

GameObjectFactory::GameObjectFactory()
{
}

void GameObjectFactory::Init()
{
	LoadGameObjectTypes();
	LoadEnemyTypes();
	InitTypeIDToEnums();
}

std::unique_ptr<GameObject> GameObjectFactory::CreateObject(const eGameObjectTypes aGameObjectType)
{
	std::unique_ptr<GameObject> newGameObject;
	switch (aGameObjectType)
	{
	case eGameObjectTypes::eApple:
		newGameObject = std::make_unique<Apple>(); break;
	case eGameObjectTypes::eBoulder:
		newGameObject = std::make_unique<Boulder>(); break;
	case eGameObjectTypes::eSeed:
		newGameObject = std::make_unique<Seed>(); break;
	//case eGameObjectTypes::eEnemy:
	//	newGameObject = std::make_unique<Enemy>(); break;
	case eGameObjectTypes::eRollerEnemy:
		newGameObject = std::make_unique<BigEnemy>(); break;
	case eGameObjectTypes::eBullet:
		newGameObject = std::make_unique<Bullet>(); break;
	case eGameObjectTypes::eHammer:
		newGameObject = std::make_unique<Hammer>(); break;
	case eGameObjectTypes::eRainCloud:
		newGameObject = std::make_unique<RainCloud>(); break;
	case eGameObjectTypes::eBucket:
		newGameObject = std::make_unique<Bucket>(); break;
	case eGameObjectTypes::eFireFlower:
		newGameObject = std::make_unique<FireFlower>(); break;
	case eGameObjectTypes::ePlayer:
		newGameObject = std::make_unique<Player>(); break;
	case eGameObjectTypes::eSink:
		newGameObject = std::make_unique<Sink>(); break;
	case eGameObjectTypes::eEnemySpawner:
		newGameObject = std::make_unique<EnemySpawner>(); break;
	case eGameObjectTypes::eGrenade:
		newGameObject = std::make_unique<Grenade>(); break;
	case eGameObjectTypes::eExplosion:
		newGameObject = std::make_unique<Explosion>(); break;
	case eGameObjectTypes::eBloodPortal:
		newGameObject = std::make_unique<BloodPortal>(); break;
	case eGameObjectTypes::eDisk:
		newGameObject = std::make_unique<Disk>(); break;
	case eGameObjectTypes::ePlayerSpawn:
		newGameObject = std::make_unique<GameObject>();
	default:
		DL_ASSERT("Tried to create unknown object in factory!");
	}

	newGameObject->Init(GetGameObjectType(aGameObjectType));
		
	return newGameObject;
}

GameObjectType& GameObjectFactory::GetGameObjectType(const eGameObjectTypes aGameObjectType)
{
	std::string nameToFind;
	switch (aGameObjectType)
	{
	case eGameObjectTypes::eApple:
		nameToFind = "apple"; break;
	case eGameObjectTypes::eBoulder:
		nameToFind = "boulder"; break;
	case eGameObjectTypes::eBucket:
		nameToFind = "bucket"; break;
	case eGameObjectTypes::eFireFlower:
		nameToFind = "fireFlower"; break;
	case eGameObjectTypes::eHammer:
		nameToFind = "hammer"; break;
	case eGameObjectTypes::eRainCloud:
		nameToFind = "rainCloud"; break;
	case eGameObjectTypes::eSeed:
		nameToFind = "seed"; break;
	case eGameObjectTypes::eBullet:
		nameToFind = "bullet"; break;
	case eGameObjectTypes::eTree:
		nameToFind = "tree"; break;
	case eGameObjectTypes::eSink:
		nameToFind = "sink"; break;
	case eGameObjectTypes::ePlayer:
		nameToFind = "player"; break;
	case eGameObjectTypes::eEnemy:
		nameToFind = "enemy"; break;
	case eGameObjectTypes::eRollerEnemy:
		nameToFind = "rollerEnemy"; break;
	case eGameObjectTypes::eEnemySpawner:
		nameToFind = "enemySpawner"; break;
	case eGameObjectTypes::eGrenade:
		nameToFind = "grenade"; break;
	case eGameObjectTypes::eExplosion:
		nameToFind = "explosion"; break;
	case eGameObjectTypes::eBloodPortal:
		nameToFind = "bloodPortal"; break;
	case eGameObjectTypes::eDisk:
		nameToFind = "disk"; break;
	case eGameObjectTypes::ePlayerSpawn:
		nameToFind = "playerSpawn"; break;
	default:
		nameToFind = "objectNotFound";
	}

	for (auto& gameObjectType : myGameObjectTypes)
	{
		if (gameObjectType.second.GetName() == nameToFind)
		{				
			return gameObjectType.second;
		}
	}

	DL_ASSERT(false && "GameObjectType not found!");
	GameObjectType* error = new GameObjectType();
	return *error;
}

std::unique_ptr<GameObject> GameObjectFactory::CreateObject(const int aGameObjectTypeID)
{
	const auto& it = myGameObjectTypes.find(aGameObjectTypeID);
	DL_ASSERT(it != myGameObjectTypes.end() && "ObjectType not found!");
		
	eGameObjectTypes gameObjectTypeEnum = myGameObjectTypeIDToEnum[it->first];		
	return std::move(CreateObject(gameObjectTypeEnum));
}

std::unique_ptr<GameObject> GameObjectFactory::CreateEnemy(const int aGameObjectTypeID)
{
	const auto& it = myEnemyTypes.find(aGameObjectTypeID);
	DL_ASSERT(it != myEnemyTypes.end() && "EnemyType not found!");
	return std::make_unique<Enemy>(myEnemyTypes[aGameObjectTypeID]);
}

std::unique_ptr<GameObject> GameObjectFactory::CreateEnemy(const std::string_view aEnemyName)
{
	for (auto& enemyType : myEnemyTypes)
	{
		if (enemyType.second.GetName() == aEnemyName)
		{
			return std::move(CreateEnemy(enemyType.first));
		}
	}

	RESOURCE_LOG("Enemy &s does not exist!", aEnemyName.data());
	return nullptr;
}

void GameObjectFactory::LoadGameObjectTypes()
{
	std::ifstream file(std::string(gDataPath) + "data/json/gameObjects.json");
	DL_ASSERT(file.is_open() == true && "Can't open data/json/gameObjects.json!!");

	std::string text((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	rapidjson::Document gameObjectTypes;
	gameObjectTypes.Parse(text.c_str());
	DL_ASSERT(gameObjectTypes.HasParseError() == false && "Error while reading gameObjects.json!");

	for (auto it = gameObjectTypes.Begin(); it != gameObjectTypes.End(); it++)
	{
		GameObjectType newType;
		newType.LoadTypeJSON(it->GetObject());
		const int ID = it->GetObject().FindMember("ID")->value.GetInt();
		DL_ASSERT(myGameObjectTypes.find(ID) == myGameObjectTypes.end() && "Two GameObjectTypes has same ID!");
		myGameObjectTypes[ID] = newType;
	}
}

void GameObjectFactory::LoadEnemyTypes()
{
	std::ifstream file(std::string(gDataPath) + "data/json/enemies.json");
	DL_ASSERT(file.is_open() == true && "Can't open data/json/enemies.json!!");

	std::string text((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	rapidjson::Document enemyTypes;
	enemyTypes.Parse(text.c_str());
	DL_ASSERT(enemyTypes.HasParseError() == false && "Error while reading enemies.json!");

	for (auto it = enemyTypes.Begin(); it != enemyTypes.End(); it++)
	{
		EnemyType newType;
		newType.LoadTypeJSON(it->GetObject());
		const int ID = it->GetObject().FindMember("ID")->value.GetInt();
		DL_ASSERT(myEnemyTypes.find(ID) == myEnemyTypes.end() && "Two EnemyTypes has same ID!");
		myEnemyTypes[ID] = newType;
	}
}

void GameObjectFactory::InitTypeIDToEnums()
{
	for (const auto& gameObjectType : myGameObjectTypes)
	{
		if (gameObjectType.second.GetName() == "apple")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eApple;
			myEnumToGameObjectTypeID[eGameObjectTypes::eApple] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "bullet")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eBullet;
			myEnumToGameObjectTypeID[eGameObjectTypes::eBullet] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "boulder")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eBoulder;
			myEnumToGameObjectTypeID[eGameObjectTypes::eBoulder] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "enemy")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eEnemy;
			myEnumToGameObjectTypeID[eGameObjectTypes::eEnemy] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "rollerEnemy")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eRollerEnemy;
			myEnumToGameObjectTypeID[eGameObjectTypes::eRollerEnemy] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "bucket")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eBucket;
			myEnumToGameObjectTypeID[eGameObjectTypes::eBucket] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "fireFlower")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eFireFlower;
			myEnumToGameObjectTypeID[eGameObjectTypes::eFireFlower] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "hammer")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eHammer;
			myEnumToGameObjectTypeID[eGameObjectTypes::eHammer] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "player")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::ePlayer;
			myEnumToGameObjectTypeID[eGameObjectTypes::ePlayer] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "rainCloud")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eRainCloud;
			myEnumToGameObjectTypeID[eGameObjectTypes::eRainCloud] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "seed")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eSeed;
			myEnumToGameObjectTypeID[eGameObjectTypes::eSeed] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "tree")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eTree;
			myEnumToGameObjectTypeID[eGameObjectTypes::eTree] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "sink")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eSink;
			myEnumToGameObjectTypeID[eGameObjectTypes::eSink] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "enemySpawner")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eEnemySpawner;
			myEnumToGameObjectTypeID[eGameObjectTypes::eEnemySpawner] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "grenade")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eGrenade;
			myEnumToGameObjectTypeID[eGameObjectTypes::eGrenade] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "explosion")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eExplosion;
			myEnumToGameObjectTypeID[eGameObjectTypes::eExplosion] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "bloodPortal")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eBloodPortal;
			myEnumToGameObjectTypeID[eGameObjectTypes::eBloodPortal] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "disk")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eDisk;
			myEnumToGameObjectTypeID[eGameObjectTypes::eDisk] = gameObjectType.first;
		}
		else if (gameObjectType.second.GetName() == "playerSpawn")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::ePlayerSpawn;
			myEnumToGameObjectTypeID[eGameObjectTypes::ePlayerSpawn] = gameObjectType.first;
		}
		else
			DL_ASSERT(false && "game object name has no game object class");
	}
}
