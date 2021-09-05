#include "stdafx.h"
#include "Bullet.h"
#include "Actor.h"
#include "physicBody.h"

void Bullet::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::eEnemy))
	{
		Actor* enemy = dynamic_cast<Actor*>(aGameObject);
		enemy->GetPhysicBody().AddForce({ myPhysicBody->GetVelocity().myX, 0.f });
		enemy->Damage(1, myPhysicBody->GetPosition());
		Delete();
	}
	else if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::ePickable))
	{
		aGameObject->GetPhysicBody().AddForce(myPhysicBody->GetVelocity());
		Delete();
	}
}

void Bullet::CollideWithTile(eCollisionPoint collisionPoint)
{
	Message particleMsg(eMessageTypes::eCreateParticleSystem);
	particleMsg.myPosition = myPhysicBody->GetPosition();
	particleMsg.myIntData = 0;
	Vector2f dir;
	switch (collisionPoint)
	{
	case eCollisionPoint::eBottom:
			dir.y = -1; break;
	case eCollisionPoint::eTop:
		dir.y = 1; break;
	case eCollisionPoint::eRight:
		dir.x = -1; break;
	case eCollisionPoint::eLeft:
		dir.x = 1; break;
	}


	//particleMsg.myDirection = myPhysicBody->GetDirection() * -1.f;
	particleMsg.myDirection = dir;
	PostMaster::GetInstance()->SendDelayedMessage(particleMsg);

	Delete();
}
