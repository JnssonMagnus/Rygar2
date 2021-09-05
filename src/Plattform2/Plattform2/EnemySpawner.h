#pragma once
#include "GameObject.h"

class EnemySpawner : public GameObject
{
public:
	void					Update(const float aDeltaTime) override;

private:
	int						mySpawnType = 9; // Enemy
	float					mySpawnDelay = 0.45f;
	float					myTimeSinceLastSpawn = 0.f;
	int						myMaxSpawnCount = 1000;
	int						myCurrentSpawnCount = 0;
};

