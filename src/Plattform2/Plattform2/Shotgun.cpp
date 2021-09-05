#include "stdafx.h"
#include "Shotgun.h"

Shotgun::Shotgun() 
{
	myReloadTime = 0.5f;
}

void Shotgun::Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition)
{
	if (myTimeSinceShot >= myReloadTime && myAmmo > 0)
	{
		PostMaster::GetInstance()->SendSoundEvent("shotgunFire");
		const float angle = atan2f(aDirection.myY, aDirection.myX);
		const int bullets = 25;
		myAmmo--;
		for (int i = 0; i < bullets; i++)
		{
			myTimeSinceShot = 0.f;

			Message message;
			message.myMessageType = eMessageTypes::eCreateObject;
			message.myIntData = 10; // Bullet
			const float maxRandomRad = (6 / 360.f) * PI * 2.f;
			float randomAngle = angle + CU::RandomF(-maxRandomRad, maxRandomRad);
			message.myDirection = Vector2f(cos(randomAngle), sin(randomAngle)) * (10.f + CU::RandomF(4.f, 10.f));
			message.myPosition = aPosition;

			PostMaster::GetInstance()->SendMessage(message);
		}
	}
}
