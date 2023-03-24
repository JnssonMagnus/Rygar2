#include "stdafx.h"
#include "GameObjectType.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "PhysicBody.h"
#include "sprite.h"

GameObjectType::GameObjectType()
{
	myPhysicBodyData.myAirFriction = { 1.0f, 1.0f };
	myPhysicBodyData.myGroundFriction = { 1.0f, 1.0f };
	myPhysicBodyData.myBounciness = 0.8f;
	myPhysicBodyData.myWeight = 1.f;
	myPhysicBodyData.myDefaultPhysics = true;
	myPhysicBodyData.myDefaultGravity = true;
	myPhysicBodyData.myDefaultKinetic = false;
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
	myPhysicBodyData = aObjectToCopy.myPhysicBodyData;
	myDefaultRotate = aObjectToCopy.myDefaultRotate;
		
	aObjectToCopy.mySprite = nullptr;

	return *this;
}

void GameObjectType::LoadTypeJSON(const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
{
	myName = aObject.FindMember("name")->value.GetString();
	std::string imagePath = aObject.FindMember("image")->value.GetString();
	mySprite = new Sprite();
	mySprite->Init(imagePath.c_str());
	mySprite->CenterPivot();

	auto physicBodyNode = aObject.FindMember("physicBody")->value.GetObject();
	myPhysicBodyData.Init(physicBodyNode);
	myDefaultRotate = aObject.FindMember("rotateObject")->value.GetBool();
}

void GameObjectType::InitGameObject(GameObject& aGameObject)
{
	PhysicBody& body = aGameObject.GetPhysicBody();
	body.SetBounciness(myPhysicBodyData.myBounciness);
	body.SetMass(myPhysicBodyData.myWeight);
	body.SetEnabled(myPhysicBodyData.myDefaultPhysics);
	body.SetGravity(myPhysicBodyData.myDefaultGravity);
	body.SetIsKinetic(myPhysicBodyData.myDefaultKinetic);
	body.SetFriction(myPhysicBodyData.myAirFriction, myPhysicBodyData.myGroundFriction);
	body.SetCollisionTags(myPhysicBodyData.myCollisionTags);
	body.SetRotation(myDefaultRotate);
}
