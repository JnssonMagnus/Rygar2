#pragma once
#include <Vector2.h>
#include <string>
#include <functional>
#include <..\external\rapidJSON\document.h>

class GameObject;
class Sprite;

class GameObjectType
{		
public:
							GameObjectType();
							~GameObjectType();
	GameObjectType&			operator=(GameObjectType& aObjectToCopy);

	void					Init(const rapidjson::GenericObject<false, rapidjson::Value>& aObject);
	void					InitGameObject(GameObject& aGameObject);
	Sprite&					GetSprite();
	const std::string&		GetName() const;

private:
	std::string				myName;
	Sprite*					mySprite = nullptr;
	Vector2f				myAirFriction;
	Vector2f				myGroundFriction;
	float					myBounciness;
	float					myWeight;
	bool					myDefaultPhysics;
	bool					myDefaultGravity;
	bool					myDefaultKinetic;
	bool					myDefaultRotate;
	char					myCollisionTags = 0;
};

inline Sprite& GameObjectType::GetSprite()
{
	return *mySprite;
}

inline const std::string& GameObjectType::GetName() const
{
	return myName;
}

