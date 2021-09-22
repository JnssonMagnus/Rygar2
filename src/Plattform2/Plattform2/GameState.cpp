#include "stdafx.h"
#include "GameState.h"
#include "PlayerCamera.h"
#include "Map.h"
#include "Tileset.h"
#include "GameObjectManager.h"
#include "Megaton.h"
#include "GameOverState.h"
#include "StateStackProxy.h"
#include "player.h"
#include <InputMapper.h>

void GameState::InitState()
{
	DL_ASSERT(myPlayer == nullptr && "Player is already initiated!");

	PostMaster::GetInstance()->Register(this, eMessageTypes::eCreateObject);

	myParallaxBackground.AddLayer("data/gfx/background.png", { 0.f, 0.f });
	myParallaxBackground.AddLayer("data/gfx/background2.png", { 0.1f, 0.0f });

	LoadTilesets(std::string(gDataPath) + "data/tilesets/tilesets.dat");

	GameObjectManager::Create();
	myGameObjectFactory.Init();

	myMap = new Map();
	myMap->LoadFromFile(std::string(gDataPath) + "data/testLevel.lvl");
	myMap->Init(myTilesets);
		
	Megaton::GetInstance().SetMap(myMap);

	InitKeybindings();

	myPlayer = dynamic_cast<Player*>(myGameObjectFactory.CreateObject(eGameObjectTypes::ePlayer));
	myPlayerCamera = new PlayerCamera(myPlayer);
	GameObjectManager::GetInstance()->AddGameObject(myPlayer);

	Message pushCameraMessage(eMessageTypes::ePushCamera);
	pushCameraMessage.myVoidPointer = myPlayerCamera;		
	PostMaster::GetInstance()->SendMessage(pushCameraMessage);			   

	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eFireGun1, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eMoveLeft, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eMoveRight, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eJump, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDodge, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::ePickUp, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eUseItem, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eUseHook, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDown, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDash, myPlayer);
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eCycleWeapons, myPlayer);
}

eStateStatus GameState::Update(const float aDeltaTime)
{	
	// Map collisions
	myMap->Collided(myPlayer->GetPhysicBody());		
	const auto& gameObjects = GameObjectManager::GetInstance()->GetGameObjects();
	for (int gameObjectIndex = 0; gameObjectIndex < gameObjects.Size(); gameObjectIndex++)
	{
		eCollisionPoint collisionPoint = eCollisionPoint::eNoCollision;
		collisionPoint = myMap->Collided(gameObjects[gameObjectIndex]->GetPhysicBody());
		if (collisionPoint != eCollisionPoint::eNoCollision)	
		{
			gameObjects[gameObjectIndex]->CollideWithTile(collisionPoint);
		}
	}
	myMap->Update(*myPlayer);

	if (myPlayer->GetStats().GetStat(eStats::eHealth) <= 0.f)
	{
		myStateStackProxy.PushState(new GameOverState(myStateStackProxy, true));
	}

	return eStateStatus::eKeepState;
}

void GameState::Render(const float aDeltaTime)
{
	// Render stuff
	myParallaxBackground.Render(myPlayerCamera->GetPosition());
	GameObjectManager::GetInstance()->DrawGameObjects(*myPlayerCamera);
	myMap->Draw(myPlayerCamera->GetPosition(), myPlayerCamera->GetZoom());
	myMap->DrawWater(myPlayerCamera->GetPosition());
	myMap->DebugDraw(myPlayerCamera->GetPosition());
}

void GameState::RecieveMessage(const Message& aMessage)
{
	switch (aMessage.myMessageType)
	{
	case eMessageTypes::eCreateObject:
		GameObject* newObject = myGameObjectFactory.CreateObject(aMessage.myIntData);
		newObject->GetPhysicBody().SetPosition(aMessage.myPosition);
		newObject->GetPhysicBody().SetVelocity(aMessage.myDirection);
		GameObjectManager::GetInstance()->AddGameObject(newObject);
		break;
	}
}

void GameState::InitKeybindings()
{
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeySPACE, Input::eInputEvent::eFireGun1);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_LeftButtonPressed, Input::eInputEvent::eFireGun1);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_Scroll, Input::eInputEvent::eCycleWeapons);

	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyLEFT, Input::eInputEvent::eMoveLeft);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyRIGHT, Input::eInputEvent::eMoveRight);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyUP, Input::eInputEvent::eJump);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyDOWN, Input::eInputEvent::eDown);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyA, Input::eInputEvent::eMoveLeft);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyD, Input::eInputEvent::eMoveRight);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyW, Input::eInputEvent::eJump);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyS, Input::eInputEvent::eDown);

	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_MovedX, Input::eInputEvent::eAimX);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_MovedY, Input::eInputEvent::eAimY);


	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyE, Input::eInputEvent::ePickUp);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyLSHIFT, Input::eInputEvent::eUseHook);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_RightButtonDown, Input::eInputEvent::eUseHook);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeyLCONTROL, Input::eInputEvent::eDash);
		
}

void GameState::LoadTilesets(const std::string_view aTilesetDatafile)
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
