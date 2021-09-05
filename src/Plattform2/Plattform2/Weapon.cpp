#include "stdafx.h"
#include "Weapon.h"
#include "GameObjectTypes.h"

Weapon::~Weapon()
{
	myAmmo = -1;
	myMaxAmmo = -1;
	myReloadTime = -1.f;
	myTimeSinceShot = -1.f;
}

void Weapon::Update(const float aDeltaTime)
{
	myTimeSinceShot += aDeltaTime;
}

float Weapon::GetPercentageAmmoLeft() const
{
	return static_cast<float>(myAmmo) / myMaxAmmo;
}
