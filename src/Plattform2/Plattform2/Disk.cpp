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
			Actor* actor = dynamic_cast<Actor*>(aGameObject);
			actor->Damage(1, myPhysicBody->GetPosition());
			myHitObjects.emplace(aGameObject);
		}

		const Vector2f& diskPosition = GetPhysicBody().GetPosition();
		const float pushDirection = (GetPhysicBody().GetOldPosition().myX - diskPosition.myX) < 0.f ? 1.f : -1.f;

		float positionXOutsideOfDisk = diskPosition.myX + GetPhysicBody().GetHalfSize().x * pushDirection;
		positionXOutsideOfDisk += pushDirection * aGameObject->GetPhysicBody().GetHalfSize().x + pushDirection;

		Vector2f translation = { positionXOutsideOfDisk - aGameObject->GetPhysicBody().GetPosition().x, 0 };
		aGameObject->GetPhysicBody().TranslatePosition(translation);
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
