#include "stdafx.h"
#include "GameState.h"
#include "PlayerCamera.h"
#include "GameObjectManager.h"
#include "Megaton.h"
#include "GameOverState.h"
#include "StateStackProxy.h"
#include "player.h"
#include "CollisionBoxDrawerVisitor.h"
#include "World.h"
#include "MapChunk.h"
#include <InputMapper.h>

void GameState::InitState()
{
	DL_ASSERT(myPlayer == nullptr && "Player is already initiated!");

	PostMaster::GetInstance()->Register(this, eMessageTypes::eCreateObject);
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePlayerDied);

	myParallaxBackground.AddLayer("data/gfx/background.png", { 0.f, 0.f });
	myParallaxBackground.AddLayer("data/gfx/background2.png", { 0.1f, 0.0f });

	LoadTilesets(std::string(gDataPath) + "data/tilesets/tilesets.dat");

	GameObjectManager::Create();
	myGameObjectFactory.Init();

	Megaton::GetInstance().SetGameObjectFactory(myGameObjectFactory);

	myWorld = new World();
		
	Megaton::GetInstance().SetWorld(myWorld);

	InitKeybindings();

	myPlayer = std::shared_ptr<Player>(dynamic_cast<Player*>(myGameObjectFactory.CreateObject(eGameObjectTypes::ePlayer).release()));
	myPlayerCamera = new PlayerCamera(myPlayer);
	GameObjectManager::GetInstance()->AddGameObject(myPlayer.get());
	GameObjectManager::GetInstance()->AddAndRemoveObjects();
	myPlayer->SetStartPosition({ 100, 100 });

	myIngameDebugDraw.Init(myPlayerCamera);

	InitPlayerStartPosition();

	Message pushCameraMessage(eMessageTypes::ePushCamera);
	pushCameraMessage.myVoidPointer = myPlayerCamera;		
	PostMaster::GetInstance()->SendMessage(pushCameraMessage);			   

	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eFireGun1, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eMoveLeft, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eMoveRight, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eJump, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDodge, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::ePickUp, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eUseItem, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eUseHook, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDown, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eDash, myPlayer.get());
	Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eCycleWeapons, myPlayer.get());
}

eStateStatus GameState::Update(const float aDeltaTime)
{	
	// Map collisions
	auto mapChunksWithPlayer = myWorld->GetMapChunks(myPlayer->GetPhysicBody().GetPosition(), myPlayer->GetPhysicBody().GetHalfSize());
	for (auto mapChunk : mapChunksWithPlayer)
	{
		mapChunk->Collided(myPlayer->GetPhysicBody());
	//	mapChunk->UpdatePlayerVsWaterCollisions(*myPlayer);
	}

	auto mapChunksOnScreen = myWorld->GetMapChunks(myPlayerCamera->GetPosition(), Vector2<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	for (auto mapChunk : mapChunksOnScreen)
	{
		mapChunk->UpdateWaterMovement();
	}

	const auto& gameObjects = GameObjectManager::GetInstance()->GetGameObjects();
	for (int gameObjectIndex = 0; gameObjectIndex < gameObjects.Size(); gameObjectIndex++)
	{
		auto mapChunks = myWorld->GetMapChunks(gameObjects[gameObjectIndex]->GetPhysicBody().GetPosition(), gameObjects[gameObjectIndex]->GetPhysicBody().GetHalfSize());
		for (auto mapChunk : mapChunks)
		{
			eCollisionPoint collisionPoint = eCollisionPoint::eNoCollision;
			collisionPoint = mapChunk->Collided(gameObjects[gameObjectIndex]->GetPhysicBody());
			if (collisionPoint != eCollisionPoint::eNoCollision)
			{
				gameObjects[gameObjectIndex]->CollideWithTile(collisionPoint);
			}
		}
	}

	if (myPlayer->GetStats().GetStat(eStats::eHealth) <= 0.f)
	{
		myStateStackProxy.PushState(new GameOverState(myStateStackProxy, true));
	}

	return eStateStatus::eKeepState;
}

void GameState::Render(const float aDeltaTime)
{
//	DebugRender();
	// Render stuff
	myParallaxBackground.Render(myPlayerCamera->GetPosition());
	auto mapChunks = myWorld->GetMapChunks(myPlayerCamera->GetPosition(), Vector2<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	for (auto mapChunk : mapChunks) {
		mapChunk->Draw(myPlayerCamera->GetPosition(), myPlayerCamera->GetZoom());
		mapChunk->DrawWater(myPlayerCamera->GetPosition());
		mapChunk->DebugDraw(myPlayerCamera->GetPosition());
	}
	GameObjectManager::GetInstance()->DrawGameObjects(*myPlayerCamera);
}

void GameState::DebugRender()
{
	myIngameDebugDraw.DebugDraw();	
}

void GameState::RecieveMessage(const Message& aMessage)
{
	switch (aMessage.myMessageType)
	{
	case eMessageTypes::eCreateObject:
	{
		GameObject* newObject = myGameObjectFactory.CreateObject(aMessage.myIntData).release();
		newObject->GetPhysicBody().SetStartPosition(aMessage.myPosition);
		newObject->GetPhysicBody().SetVelocity(aMessage.myDirection);
		GameObjectManager::GetInstance()->AddGameObject(newObject);
		break;
	}
	case eMessageTypes::ePlayerDied:
		GameObjectManager::GetInstance()->RemoveAllGameObjects();
		myWorld->UnloadWorld();
		break;
	}
}

void GameState::InitKeybindings()
{
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eKeySPACE, Input::eInputEvent::eFireGun1);
	Input::InputMapper::GetInstance()->MapEvent(Input::eInputAction::eMouse_LeftButtonDown, Input::eInputEvent::eFireGun1);
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

void GameState::InitPlayerStartPosition()
{
	auto playerSpawn = GameObjectManager::GetInstance()->GetFirstWithName("playerSpawn");
	if (playerSpawn != nullptr)
		myPlayer->SetPosition(playerSpawn->GetPhysicBody().GetPosition());
}

