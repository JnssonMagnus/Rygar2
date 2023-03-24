#pragma once
#include "Actor.h"
#include "AIBehaviour.h"

class EnemyType;

class Enemy : public Actor
{
public:
						Enemy(EnemyType& enemyType);
	virtual void		Update(const float aDeltaTime) override;
	void				Init(EnemyType& aEnemyType);
	virtual void		Collide(GameObject* aGameObject) override;

private:
	float				myHasBeenDeadTimer = 0.f;
	AIBehaviour			myAIBehaviour;
	const EnemyType&	myEnemyType;
};
