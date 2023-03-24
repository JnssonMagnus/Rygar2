#pragma once
#include <GameObjectType.h>
#include "Animation.h"


class EnemyType : public GameObjectType
{
public:
	void LoadTypeJSON(const rapidjson::GenericObject<false, rapidjson::Value>& aObject) override;

	int GetMaxLife() const;
	int GetTouchDamage() const;
	int GetXP() const;
	float GetStaggeredTime() const;

	const AnimationSet2& GetAnimationSet() const;

private:
	AnimationSet2 myAnimationSet;

	float myStaggeredTime = 0.f;
	int myMaxLife = 0;
	int myTouchDamage = 0;
	int myXP = 0;
};