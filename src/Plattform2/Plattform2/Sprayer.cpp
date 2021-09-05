#include "stdafx.h"
#include "Sprayer.h"

void Sprayer::Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition)
{
	myShotLastFrame = true;
	if (myTimeSinceShot >= myReloadTime && myAmmo > 0)
	{
		PostMaster::GetInstance()->SendSoundEvent("minigunFire");

		myShotLastFrame = true;

		myAmmo--;
		myTimeSinceShot = 0.f;
		
		const float angle = atan2f(aDirection.myY, aDirection.myX);
		const float maxRandomRad = (2 / 360.f) * PI * 2.f;
		static float v = 0.f;
		v += 0.5f;
		float randomAngle = angle + cos(v)/18.f + CU::RandomF(-maxRandomRad, maxRandomRad);

		Message message;
		message.myMessageType = eMessageTypes::eCreateObject;
		message.myIntData = 10; // Bullet
		message.myDirection = Vector2f(cos(randomAngle), sin(randomAngle)) * 20.f;
		message.myPosition = aPosition;

		PostMaster::GetInstance()->SendMessage(message);
	}

	if (myAmmo <= 0)
	{
		PostMaster::GetInstance()->SendSoundEvent("minigunStop");
	}
}

void Sprayer::Update(const float aDeltaTime) 
{
	if (myShotLastFrame == false)
	{
		PostMaster::GetInstance()->SendSoundEvent("minigunStop");
	}
	Weapon::Update(aDeltaTime);
	myShotLastFrame = false;
}
