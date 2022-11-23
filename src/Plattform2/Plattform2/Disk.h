#pragma once
#include "GameObject.h"
#include <set>


class Disk : public GameObject
{
public:
	void					Collide(GameObject* aGameObject) override;
	void					ResetHitObjects();

private:
	std::set<GameObject*>	myHitObjects;
	bool					HasAlreadyHitObject(GameObject* aGameObject) const;
};

