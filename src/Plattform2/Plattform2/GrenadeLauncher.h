#pragma once
#include "Weapon.h"
class GrenadeLauncher : public Weapon
{
public:
			GrenadeLauncher();
	void    Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition = { 0.f, 0.f }) override;
};

