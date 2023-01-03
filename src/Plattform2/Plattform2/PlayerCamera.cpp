#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"

PlayerCamera::PlayerCamera(std::weak_ptr<Player> aPlayer)
{
	myPlayer = aPlayer;
}

void PlayerCamera::Update()
{
	if (Player* player = myPlayer.lock().get())
	{
		Vector2f targetPosition = player->GetPhysicBody().GetPosition() + player->GetPhysicBody().GetVelocity() * 10 +
			player->GetAimLocalPosition() / 10.f;
		myPosition = myPosition * 0.9f + targetPosition * 0.1f;
		float zoomFromWalkSpeed = (ABS(player->GetPhysicBody().GetVelocity().myX) / 16.f) * 0.9f;
		float zoomFromFalling = (ABS(player->GetPhysicBody().GetVelocity().myY) / 300.f) * 0.9f;
		myTargetZoom = 1.f - zoomFromWalkSpeed - zoomFromFalling;
		//myZoom = myZoom * 0.99f + myTargetZoom * 0.01f;
	}
}