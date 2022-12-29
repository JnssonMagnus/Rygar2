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

		if (myState == eStates::eThrowing)
		{
			PushEnemy(*aGameObject);
		}
	}
}

void Disk::ResetHitObjects()
{
	myHitObjects.clear();
}

void Disk::SetState(const eStates aState)
{
	myState = aState;
}

bool Disk::HasAlreadyHitObject(GameObject* aGameObject) const
{
	return myHitObjects.find(aGameObject) != myHitObjects.end();
}

void Disk::PushEnemy(GameObject& aEnemy) const
{
	const Vector2f& diskPosition = GetPhysicBody().GetPosition();
	const float pushDirection = (GetPhysicBody().GetOldPosition().myX - diskPosition.myX) < 0.f ? 1.f : -1.f;

	float positionXOutsideOfDisk = diskPosition.myX + GetPhysicBody().GetHalfSize().x * pushDirection;
	positionXOutsideOfDisk += pushDirection * aEnemy.GetPhysicBody().GetHalfSize().x + pushDirection;

	Vector2f translation = { positionXOutsideOfDisk - aEnemy.GetPhysicBody().GetPosition().x, 0 };
	aEnemy.GetPhysicBody().TranslatePosition(translation);

}
