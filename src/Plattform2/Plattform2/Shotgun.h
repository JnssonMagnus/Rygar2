#pragma once
#include "Weapon.h"

class Shotgun : public Weapon
{
public:
            Shotgun();
    void    Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition = { 0.f, 0.f }) override;
};

