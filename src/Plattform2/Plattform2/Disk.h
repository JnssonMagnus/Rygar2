#pragma once
#include "GameObject.h"
#include <set>


class Disk : public GameObject
{
public:
							Disk() = default;
							~Disk() = default;

	enum eStates {
		eThrowing,
		eReturning,
		eIdle
	};

	void					Collide(GameObject* aGameObject) override;
	void					ResetHitObjects();
	void					SetState(const eStates aState);


private:
	bool					HasAlreadyHitObject(GameObject* aGameObject) const;
	void					PushEnemy(GameObject& aEnemy) const;

	std::set<GameObject*>	myHitObjects;
	Disk::eStates			myState;
};

