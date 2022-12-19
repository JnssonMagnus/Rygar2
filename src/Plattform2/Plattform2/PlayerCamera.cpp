#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"

PlayerCamera::PlayerCamera(Player* aPlayer)
{
	DL_ASSERT(aPlayer != nullptr && "Player is nullptr!");
	myPlayer = aPlayer;
}

void PlayerCamera::Update()
{
	Vector2f targetPosition = myPlayer->GetPhysicBody().GetPosition() + myPlayer->GetPhysicBody().GetVelocity() * 10 + 
		myPlayer->GetAimLocalPosition() / 10.f;
	myPosition = myPosition * 0.9f + targetPosition * 0.1f;
	float zoomFromWalkSpeed = (ABS(myPlayer->GetPhysicBody().GetVelocity().myX) / 16.f) * 0.9f;
	float zoomFromFalling = (ABS(myPlayer->GetPhysicBody().GetVelocity().myY) / 300.f) * 0.9f;
	myTargetZoom = 1.f - zoomFromWalkSpeed - zoomFromFalling;
	//myZoom = myZoom * 0.99f + myTargetZoom * 0.01f;
}