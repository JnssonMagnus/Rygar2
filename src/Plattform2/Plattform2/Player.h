#pragma once
#include "Sprite.h"
#include "PhysicBody.h"
#include "PLayerUI.h"
#include "Actor.h"
#include "Chain.h"
#include "Aim.h"
#include "Disk.h"
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
	bool						PickUp(GameObject* aGameObject);
	void						DropItem();

	void						Collide(GameObject* aGameObject) override;
	void						Damage(const int aDamage, const Vector2f& aContactPoint) override;

	const Vector2f				GetAimLocalPosition() const;

	bool						IsAboveEnemy(const GameObject* const aGameObject) const;

	void						Respawn();
	void						SetRespawnPosition(const Vector2f& aWorldPosition);
	bool						IsDead() const;

private:
	void						CollidedWithMap(const MapCollisionData& aMapCollisionData) override;
	void						UpdateHook(const float aDeltaTime);
	void						UpdatePickedUpObject();
	void						PlayLandOnGroundSound();
	void						UpdateWeapon(const float aDeltaTime);
	void						UpdateSoundListenerPosition();

	void						CycleWeapons(int aCycleValue);
	void						AddWeapons();

	bool						IsHinderedFromMoving() const;
	bool						IsAttacking() const;

	Aim							myAim;
	PlayerUI					myPlayerUI;
	bool						myHasDoubleJumped = false;
	GameObject*					myPickedUpObject;
	Chain						myHook;

	Disk						myDisk;
	
	CU::GrowingArray<Weapon*>	myWeapons;
	int							myCurrentWeapon = 0;

	Vector2f					myRespawnPosition;

	float						myJumpStrength;
	float						myDashStrength;
	float						myWalkSpeed;
	float						myInvinsibleTime = 0.f;
	int							myDashReloadTimer;
	int							myDashTime;
};
