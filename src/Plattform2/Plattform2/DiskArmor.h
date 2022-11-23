#pragma once
#include "Weapon.h"
#include "Chain.h"

class GameObject;
class Disk;

class DiskArmor : public Weapon
{
public:
	void Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition = { 0.f, 0.f }) override;
	void Update(const float aDeltaTime, const Vector2f& aParentPosition, const float aParentDirX) override;
	void Draw() override;
	void Init() override;

private:
	Chain						myChain;
	Disk*						myDisk = nullptr;
};

