#include "stdafx.h"
#include "GameObjectType.h"
#include "gameObject.h"
#include "resourceManager.h"
#include "PhysicBody.h"
#include "sprite.h"

GameObjectType::GameObjectType()
{
	myAirFriction = { 1.0f, 1.0f };
	myGroundFriction = { 1.0f, 1.0f };
	myBounciness = 0.8f;
	myWeight = 1.f;
	myDefaultPhysics = true;
	myDefaultGravity = true;
	myDefaultKinetic = false;
	myDefaultRotate = false;
}

GameObjectType::~GameObjectType()
{
	SAFE_DELETE(mySprite);
}

GameObjectType& GameObjectType::operator=(GameObjectType& aObjectToCopy)
{
	myName = aObjectToCopy.myName;
	mySprite = aObjectToCopy.mySprite;
	myAirFriction = aObjectToCopy.myAirFriction;
	myGroundFriction = aObjectToCopy.myGroundFriction;
	myBounciness = aObjectToCopy.myBounciness;
	myWeight = aObjectToCopy.myWeight;
	myDefaultPhysics = aObjectToCopy.myDefaultPhysics;
	myDefaultGravity = aObjectToCopy.myDefaultGravity;
	myDefaultKinetic = aObjectToCopy.myDefaultKinetic;
	myDefaultRotate = aObjectToCopy.myDefaultRotate;
	myCollisionTags = aObjectToCopy.myCollisionTags;
		
	aObjectToCopy.mySprite = nullptr;

	return *this;
}

void GameObjectType::Init(const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
{
	myName = aObject.FindMember("name")->value.GetString();
	std::string imagePath = aObject.FindMember("image")->value.GetString();
	mySprite = new Sprite();
	mySprite->Init(imagePath.c_str());
	mySprite->CenterPivot();

	auto airFrictionObject = aObject.FindMember("airFriction")->value.GetObject();
	myAirFriction = { airFrictionObject.FindMember("x")->value.GetFloat(),
		airFrictionObject.FindMember("y")->value.GetFloat() };

	auto groundFrictionObject = aObject.FindMember("groundFriction")->value.GetObject();
	myGroundFriction = { groundFrictionObject.FindMember("x")->value.GetFloat(),
		groundFrictionObject.FindMember("y")->value.GetFloat() };

	myBounciness = aObject.FindMember("bounciness")->value.GetFloat();
	myWeight = aObject.FindMember("weight")->value.GetFloat();
	myDefaultPhysics = aObject.FindMember("physicsEnabled")->value.GetBool();
	myDefaultGravity = aObject.FindMember("gravity")->value.GetBool();
	myDefaultKinetic = aObject.FindMember("kinetic")->value.GetBool();
	myDefaultRotate = aObject.FindMember("rotateObject")->value.GetBool();

	myCollisionTags = static_cast<char>(aObject.FindMember("collisionTags")->value.GetInt());
}

void GameObjectType::InitGameObject(GameObject& aGameObject)
{
	PhysicBody& body = aGameObject.GetPhysicBody();
	body.SetBounciness(myBounciness);
	body.SetMass(myWeight);
	body.SetEnabled(myDefaultPhysics);
	body.SetGravity(myDefaultGravity);
	body.SetRotation(myDefaultRotate);
	body.SetIsKinetic(myDefaultKinetic);
	body.SetFriction(myAirFriction, myGroundFriction);
	body.SetCollisionTags(myCollisionTags);
}
