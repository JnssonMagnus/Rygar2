#pragma once
#include "Camera.h"

class Player;

class PlayerCamera : public Camera
{
public:
						PlayerCamera(Player* aPlayer);
	void				Update() override;
private:
	Player*				myPlayer = nullptr;
	float				myTargetZoom = 1.f;
};