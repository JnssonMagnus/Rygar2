#pragma once
#include "Actor.h"
#include "AIBehaviour.h"

class Enemy : public Actor
{
public:
	virtual void		Update(const float aDeltaTime) override;
	virtual void		Init(GameObjectType& aGameObjectType) override;
	virtual void		Collide(GameObject* aGameObject) override;

private:
	float				myHasBeenDeadTimer = 0.f;
	AIBehaviour			myAIBehaviour;
};
