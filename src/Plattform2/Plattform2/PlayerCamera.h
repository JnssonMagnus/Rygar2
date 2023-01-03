#pragma once
#include "Camera.h"
#include <memory>

class Player;

class PlayerCamera : public Camera
{
public:
								PlayerCamera(std::weak_ptr<Player> aPlayer);
	void						Update() override;
private:
	std::weak_ptr<Player>		myPlayer;
	float						myTargetZoom = 1.f;
};