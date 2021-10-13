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

void Weapon::Update(const float aDeltaTime, const Vector2f& aParentPosition, const float aOwnerXDir)
{
	myTimeSinceShot += aDeltaTime;
	myPosition = aParentPosition + Vector2f(myOffsetPosition.myX * aOwnerXDir, myOffsetPosition.myY);
}

void Weapon::Draw()
{
}

void Weapon::Init()
{
}

float Weapon::GetPercentageAmmoLeft() const
{
	return static_cast<float>(myAmmo) / myMaxAmmo;
}

void Weapon::SetOffsetPosition(const Vector2f& aOffset)
{
	myOffsetPosition = aOffset;
}

const Vector2f& Weapon::GetOffsetPosition() const
{
	return myOffsetPosition;
}

eWeaponStatus Weapon::GetWeaponStatus() const
{
	return myWeaponStatus;
}
