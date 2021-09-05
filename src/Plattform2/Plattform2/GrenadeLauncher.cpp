#include "stdafx.h"
#include "GrenadeLauncher.h"

GrenadeLauncher::GrenadeLauncher()
{
	myReloadTime = 0.8f;
}

void GrenadeLauncher::Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition)
{
	if (myTimeSinceShot >= myReloadTime && myAmmo > 0)
	{
		PostMaster::GetInstance()->SendSoundEvent("grenadeFire");
		myTimeSinceShot = 0.f;
		constexpr float maxSpeed = 13.f;
		const float angle = atan2f(aDirection.myY, aDirection.myX);
		const Vector2f distancePercent(abs(aPosition.myX - aAimPosition.myX) / (SCREEN_WIDTH / 2.f),
			abs(aPosition.myY - aAimPosition.myY) / (SCREEN_HEIGHT / 2.f));
		const float totaltDistancePercent = (distancePercent.myX + distancePercent.myY) / 2.f;
		const float fixedSpeed = MAX(4.f, totaltDistancePercent * maxSpeed);

		for (size_t i = 0; i < 4; i++)
		{
			Message message;
			message.myMessageType = eMessageTypes::eCreateObject;
			message.myIntData = 12; // Grenade				
			const float maxRandomRad = (15 / 360.f) * PI * 2.f;
			float randomAngle = angle + CU::RandomF(-maxRandomRad, maxRandomRad);
			constexpr float heightBoost = 1.4f;
			message.myDirection = Vector2f(cos(randomAngle), sin(randomAngle) * heightBoost) * (fixedSpeed + CU::RandomF(-1.f, 3.f));
			message.myPosition = aPosition;

			PostMaster::GetInstance()->SendMessage(message);
		}
	}
}
