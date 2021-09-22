#pragma once
#include "Tileset.h"
#include "ParallaxBackground.h"
#include "GameObjectFactory.h"
#include "State.h"
#include <PostMaster/Observer.h>

class PlayerCamera;
class Player;
class Map;

class GameState : public Observer, public State
{
public:
	using State::State;
	void							InitState() override;
	eStateStatus					Update(const float aDeltaTime) override;
	void							Render(const float aDeltaTime) override;
	void							RecieveMessage(const Message& aMessage) override;

private:
	void							InitKeybindings();
	void							LoadTilesets(const std::string_view aTilesetDatafile);

	ParallaxBackground				myParallaxBackground;
	GameObjectFactory				myGameObjectFactory;
	Player*							myPlayer = nullptr;
	PlayerCamera*					myPlayerCamera = nullptr;
	Map*							myMap = nullptr;
	std::map<std::string, Tileset>	myTilesets;
};
