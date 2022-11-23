#pragma once

enum class eWeaponStatus
{
	eReloading,
	eFireing,
	eIdle
};

class Weapon
{
public:
	virtual			~Weapon();
	virtual	void	Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition = { 0.f, 0.f }) = 0;
	virtual	void	Update(const float aDeltaTime, const Vector2f& aParentPosition, const float aOwnerXDir);
	virtual void	Draw();
	virtual void	Init();
	float			GetPercentageAmmoLeft() const;
	void			SetOffsetPosition(const Vector2f& aOffset);
	const Vector2f& GetPosition() const;
	eWeaponStatus	GetWeaponStatus() const;

protected:
	float			myReloadTime = 0.01f;
	float			myTimeSinceShot = 0.f;
	int				myAmmo = 1000;
	int				myMaxAmmo = 1000;
	Vector2f		myPosition;
	Vector2f		myOffsetPosition;
	eWeaponStatus	myWeaponStatus = eWeaponStatus::eIdle;
};
