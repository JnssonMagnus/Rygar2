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
#include <istream>

GameObjectFactory::GameObjectFactory()
{
	myTreeType = nullptr;
}

void GameObjectFactory::Init()
{
	LoadGameObjectTypes();
	InitTypeIDToEnums();

	myTreeType = new TreeType();
	myTreeType->SetLeafLevel(4);
	myTreeType->SetDefaultRotation(0.f, 0.f);
	myTreeType->SetDefaultPlacement(0.5f, 1.f);
	myTreeType->SetRotationAtLevel(0, -PI / 2.1f, -PI / 1.9f);
	myTreeType->SetRotationAtLevel(1, PI / 1.9f, PI / 2.1f);
	myTreeType->SetRotationAtLevel(2, -PI / 2.1f, -PI / 1.9f);
	myTreeType->SetRotationAtLevel(3, PI / 1.9f, PI / 2.1f);
	myTreeType->SetRotationAtLevel(4, -PI / 2.1f, -PI / 1.9f);
		
	myTreeType->SetMaxGrowthAtLevel(1, 0.3f);
	myTreeType->SetMaxGrowthAtLevel(2, 0.5f);
	myTreeType->SetMaxGrowthAtLevel(3, 0.3f);
	myTreeType->SetMaxGrowthAtLevel(4, 0.2f);

	myTreeType->SetDefaultSprite("data/gfx/gameObjects/twig.png");
	myTreeType->SetRootSprite("data/gfx/gameObjects/TreeTrunk.png");
	//myTreeType->SetSpriteAtLevel(2, "data/gfx/gameObjects/TreeLeaves.png");
	//myTreeType->SetLeafSprite("data/gfx/gameObjects/apple.png");
}

GameObject* GameObjectFactory::CreateObject(const eGameObjectTypes aGameObjectType)
{
	GameObject* newGameObject = nullptr;
	switch (aGameObjectType)
	{
	case eGameObjectTypes::eApple:
		newGameObject = new Apple(); break;
	case eGameObjectTypes::eBoulder:
		newGameObject = new Boulder(); break;
	case eGameObjectTypes::eSeed:
		newGameObject = new Seed(); break;
	case eGameObjectTypes::eEnemy:
		newGameObject = new Enemy(); break;
	case eGameObjectTypes::eBigEnemy:
		newGameObject = new BigEnemy(); break;
	case eGameObjectTypes::eBullet:
		newGameObject = new Bullet(); break;
	case eGameObjectTypes::eTree:
	{
		newGameObject = new Tree();
		dynamic_cast<Tree*>(newGameObject)->SetTreeType(myTreeType);
		break;
	}
	case eGameObjectTypes::eHammer:
		newGameObject = new Hammer(); break;
	case eGameObjectTypes::eRainCloud:
		newGameObject = new RainCloud(); break;
	case eGameObjectTypes::eBucket:
		newGameObject = new Bucket(); break;
	case eGameObjectTypes::eFireFlower:
		newGameObject = new FireFlower(); break;
	case eGameObjectTypes::ePlayer:
		newGameObject = new Player(); break;
	case eGameObjectTypes::eSink:
		newGameObject = new Sink(); break;
	case eGameObjectTypes::eEnemySpawner:
		newGameObject = new EnemySpawner(); break;
	case eGameObjectTypes::eGrenade:
		newGameObject = new Grenade(); break;
	case eGameObjectTypes::eExplosion:
		newGameObject = new Explosion(); break;
	case eGameObjectTypes::eBloodPortal:
		newGameObject = new BloodPortal(); break;
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
	case eGameObjectTypes::eBigEnemy:
		nameToFind = "bigEnemy"; break;
	case eGameObjectTypes::eEnemySpawner:
		nameToFind = "enemySpawner"; break;
	case eGameObjectTypes::eGrenade:
		nameToFind = "grenade"; break;
	case eGameObjectTypes::eExplosion:
		nameToFind = "explosion"; break;
	case eGameObjectTypes::eBloodPortal:
		nameToFind = "bloodPortal"; break;
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

GameObject* GameObjectFactory::CreateObject(const int aGameObjectTypeID)
{
	GameObject* newGameObject = nullptr;
	const auto& it = myGameObjectTypes.find(aGameObjectTypeID);
	DL_ASSERT(it != myGameObjectTypes.end() && "ObjectType not found!");
		
	eGameObjectTypes gameObjectTypeEnum = myGameObjectTypeIDToEnum[it->first];		
	return CreateObject(gameObjectTypeEnum);
}

void GameObjectFactory::LoadGameObjectTypes()
{
	std::ifstream file("data/json/gameObjects.json");
	DL_ASSERT(file.is_open() == true && "Can't open data/json/gameObjects.json!!");

	//std::string text;
	//std::getline(file, text);
	std::string text((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	rapidjson::Document gameObjectTypes;
	gameObjectTypes.Parse(text.c_str());
	DL_ASSERT(gameObjectTypes.HasParseError() == false && "Error while reading gameObjects.json!");

	for (auto it = gameObjectTypes.Begin(); it != gameObjectTypes.End(); it++)
	{
		GameObjectType newType;
		newType.Init(it->GetObject());
		const int ID = it->GetObject().FindMember("ID")->value.GetInt();
		DL_ASSERT(myGameObjectTypes.find(ID) == myGameObjectTypes.end() && "Two GameObjectTypes has same ID!");
		myGameObjectTypes[ID] = newType;
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
		else if (gameObjectType.second.GetName() == "bigEnemy")
		{
			myGameObjectTypeIDToEnum[gameObjectType.first] = eGameObjectTypes::eBigEnemy;
			myEnumToGameObjectTypeID[eGameObjectTypes::eBigEnemy] = gameObjectType.first;
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
		else
			DL_ASSERT(false && "game object name has no game object class");
	}
}
