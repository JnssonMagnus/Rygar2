#include "stdafx.h"
#include "EnemyType.h"
#include "ResourceManager.h"
#include <..\external\rapidJSON\document.h>

void EnemyType::LoadTypeJSON(const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
{
	if (aObject.HasMember("animationSet"))
	{
		auto animationSetNode = aObject.FindMember("animationSet");
		myAnimationSet.LoadAnimationSet(animationSetNode->value.GetObject());
	}

	myMaxLife = aObject.FindMember("life")->value.GetInt();
	myStaggeredTime = aObject.FindMember("staggeredTime")->value.GetFloat();
	myTouchDamage = aObject.FindMember("touchDamage")->value.GetInt();
	myXP = aObject.FindMember("exp")->value.GetInt();

	GameObjectType::LoadTypeJSON(aObject);
}

int EnemyType::GetMaxLife() const
{
	return myMaxLife;
}

int EnemyType::GetTouchDamage() const
{
	return myTouchDamage;
}

int EnemyType::GetXP() const
{
	return myXP;
}

float EnemyType::GetStaggeredTime() const
{
	return myStaggeredTime;
}

const AnimationSet2& EnemyType::GetAnimationSet() const
{
	return myAnimationSet;
}
