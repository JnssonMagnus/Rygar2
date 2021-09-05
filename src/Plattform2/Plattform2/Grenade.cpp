#include "stdafx.h"
#include "Grenade.h"
#include "PhysicBody.h"

Grenade::Grenade()
{
	myMaxAge = CU::RandomF(0.f, 0.5f) + 0.5f;
}

void Grenade::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::eEnemy))
	{
		aGameObject->GetPhysicBody().AddForce(myPhysicBody->GetVelocity() / 20.f);
	}
}

void Grenade::CollideWithTile(eCollisionPoint collisionPoint)
{
	PostMaster::GetInstance()->SendSoundEvent("grenadeBounce");
}

void Grenade::Update(const float aDeltaTime)
{
	myAnimation.Update(aDeltaTime);
	myLivedTime += aDeltaTime;

	if (myLivedTime >= myMaxAge)
	{
		PostMaster::GetInstance()->SendSoundEvent("grenadeExplode");
		Message message;
		message.myMessageType = eMessageTypes::eCreateObject;
		message.myIntData = 13; // Explosion
		message.myDirection = Vector2f(0, 0);
		message.myPosition = GetPhysicBody().GetPosition();
		PostMaster::GetInstance()->SendMessage(message);
		Delete();
	}
}

void Grenade::Init(GameObjectType& aGameObjectType)
{
	GameObject::Init(aGameObjectType);
	myAnimation.Init("data/gfx/gameObjects/grenade.png");
	myAnimation.AddAnimation(eAnimationID::eDefault, 2, { 15, 11 }, 7);
	myAnimation.CenterPivot();
}

void Grenade::Draw()
{
	myAnimation.Draw(myPhysicBody->GetPosition(), myPhysicBody->GetRotation());
}
