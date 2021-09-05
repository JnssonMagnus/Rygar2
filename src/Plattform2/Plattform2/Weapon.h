#pragma once

class Weapon
{
public:
	virtual			~Weapon();
	virtual	void	Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition = { 0.f, 0.f }) = 0;
	virtual	void	Update(const float aDeltaTime);
	float			GetPercentageAmmoLeft() const;

protected:
	float			myReloadTime = 0.01f;
	float			myTimeSinceShot = 0.f;
	int				myAmmo = 1000;
	int				myMaxAmmo = 1000;
};
