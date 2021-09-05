#pragma once
#include "GameObject.h"

class Bucket : public GameObject
{
public:
				Bucket();
	bool		Use(Player& aPlayer) override;

private:
	void		EmptyBucket();
	int			myWaterAmount;
	int			myWaterCapacity;

};
