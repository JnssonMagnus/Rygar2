#include "stdafx.h"
#include "Disk.h"
#include "PhysicBody.h"
#include "Actor.h"

void Disk::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::eEnemy) == true)
	{
		if (HasAlreadyHitObject(aGameObject) == false)
		{
			myHitObjects.emplace(aGameObject);
			const float pushDirection = (GetPhysicBody().GetOldPosition().myX - GetPhysicBody().GetPosition().myX) < 0.f ? 1.f : -1.f;
			aGameObject->GetPhysicBody().AddForce({ 100.f * pushDirection, 0 });
			Actor* actor = dynamic_cast<Actor*>(aGameObject);
			actor->Damage(1, myPhysicBody->GetPosition());
		}
	}
}

void Disk::ResetHitObjects()
{
	myHitObjects.clear();
}

bool Disk::HasAlreadyHitObject(GameObject* aGameObject) const
{
	return myHitObjects.find(aGameObject) != myHitObjects.end();
}
