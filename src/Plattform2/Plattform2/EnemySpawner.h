#pragma once
#include "GameObject.h"

class EnemySpawner : public GameObject
{
public:	
	void					Update(const float aDeltaTime) override;
	virtual void			Init(GameObjectType& aGameObjectType) override;

private:
	std::string				myEnemyName;
	float					mySpawnDelay = 0.45f;
	float					myTimeSinceLastSpawn = 0.f;
	int						myMaxSpawnCount = 1000;
	int						myCurrentSpawnCount = 0;
};

