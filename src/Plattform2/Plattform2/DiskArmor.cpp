#include "stdafx.h"
#include "DiskArmor.h"
#include "Megaton.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "PhysicBody.h"
#include "Disk.h"

void DiskArmor::Shoot(const Vector2f& aPosition, const Vector2f& aDirection, const Vector2f& aAimPosition)
{
	if (myChain.GetState() == Chain::eState::eUnreleased)
	{
		myDisk->GetPhysicBody().SetEnabled(true);
		myWeaponStatus = eWeaponStatus::eFireing;
		myDisk->SetState(Disk::eStates::eThrowing);
	}
	myChain.Fire(aDirection);
}

void DiskArmor::Update(const float aDeltaTime, const Vector2f& aParentPosition, const float aParentDirX)
{
	Weapon::Update(aDeltaTime, aParentPosition, aParentDirX);
	myChain.Update(aDeltaTime, myPosition, Vector2f(0.f, 0.f));

	if (myChain.GetState() == Chain::eState::eReturning)
	{
		myDisk->SetState(Disk::eStates::eReturning);
	}

	if (myChain.GetState() == Chain::eState::eUnreleased)
	{
		myWeaponStatus = eWeaponStatus::eIdle;
		myDisk->ResetHitObjects();
		myDisk->SetState(Disk::eStates::eIdle);
		myDisk->GetPhysicBody().SetEnabled(false);
	}
}

void DiskArmor::Draw()
{
	myChain.Draw();
}

void DiskArmor::Init()
{
	constexpr float maxLength = 105.f;
	constexpr float initSpeed = 5.f;
	constexpr int returnSpeed = 2;
	myDisk = dynamic_cast<Disk*>(Megaton::GetInstance().GetGameObjectFactory().CreateObject(eGameObjectTypes::eDisk));
	myChain.Init("data/gfx/discArmor_link.png", "data/gfx/discArmor.png", maxLength, initSpeed, returnSpeed, myDisk, false);
	myChain.SetLaunchSoundEvent("rygarAttack");
	myChain.SetHitWallSoundEvent("rygarAttackHitWall");
}
