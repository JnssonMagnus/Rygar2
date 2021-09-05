#include "stdafx.h"
#include "Explosion.h"
#include "PhysicBody.h"
#include "Actor.h"

Explosion::Explosion()
{

}

void Explosion::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::eEnemy))
	{
		Actor* enemy = dynamic_cast<Actor*>(aGameObject);
		Vector2f pushDirection = aGameObject->GetPhysicBody().GetPosition() - myPhysicBody->GetPosition();
		pushDirection.Normalize();
		enemy->GetPhysicBody().AddForce(pushDirection * 50);
		enemy->Damage(1, (myPhysicBody->GetPosition() + aGameObject->GetPhysicBody().GetPosition()) / 2.f);
	}
	else if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::ePickable))
	{
		Vector2f pushDirection = aGameObject->GetPhysicBody().GetPosition() - myPhysicBody->GetPosition();
		pushDirection.Normalize();
		aGameObject->GetPhysicBody().AddForce(pushDirection * 50);
	}
}

void Explosion::Update(const float aDeltaTime)
{
	myAge += aDeltaTime;
	if (myAge >= 0.2f)
		Delete();
}
