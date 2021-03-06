#pragma once
#include "Sprite.h"
#include "PhysicBody.h"
#include "Stats.h"
#include "StatsViewer.h"
#include "Actor.h"
#include "Hook.h"
#include "Aim.h"
#include <PostMaster/Subject.h>
#include <InputObserver.h>
#include <Vector2.h>
#include <growingArray.h>

class Weapon;

class Player : public Input::InputObserver, public Actor
{
public:
								Player();
								Player(const Player&) = delete;
								~Player();
	const Player&				operator=(const Player&) = delete;
	void						Update(const float aDeltaTime) override;
	void						Draw() override;
	void						Init(GameObjectType& aGameObjectType) override;
	void						RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue) override;
	void						CollideWithTile(eCollisionPoint collisionPoint) override;
	void						ChangeStat(const eStats aStat, const float aChange);
	bool						PickUp(GameObject* aGameObject);
	void						DropItem();

	const Vector2f				GetAimLocalPosition() const;

	const Stats&				GetStats() const;

private:
	void						CycleWeapons(int aCycleValue);
	void						AddWeapons();

	Aim							myAim;
	Stats						myStats;
	StatsViewer					myStatsViewer;
	bool						myHasDoubleJumped = false;
	GameObject*					myPickedUpObject;
	Hook						myHook;
	
	CU::GrowingArray<Weapon*>	myWeapons;
	int							myCurrentWeapon = 0;

	float						myJumpStrength;
	float						myDashStrength;
	int							myDashReloadTimer;
	int							myDashTime;
};
