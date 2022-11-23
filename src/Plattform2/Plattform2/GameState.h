#pragma once
#include "Tileset.h"
#include "ParallaxBackground.h"
#include "GameObjectFactory.h"
#include "State.h"
#include "IngameDebugDraw.h"
#include <PostMaster/Observer.h>

class PlayerCamera;
class Player;
class MapChunk;
class World;

class GameState : public Observer, public State
{
public:
	using State::State;
	void							InitState() override;
	eStateStatus					Update(const float aDeltaTime) override;
	void							Render(const float aDeltaTime) override;
	void							DebugRender();
	void							RecieveMessage(const Message& aMessage) override;

private:
	void							InitKeybindings();
	void							LoadTilesets(const std::string_view aTilesetDatafile);
	void							InitPlayerStartPosition();

	ParallaxBackground				myParallaxBackground;
	GameObjectFactory				myGameObjectFactory;
	IngameDebugDraw					myIngameDebugDraw;
	Player*							myPlayer = nullptr;
	PlayerCamera*					myPlayerCamera = nullptr;
	World*							myWorld = nullptr;
	std::map<std::string, Tileset>	myTilesets;
};
