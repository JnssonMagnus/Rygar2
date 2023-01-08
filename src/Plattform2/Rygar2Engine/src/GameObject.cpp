#include "stdafx.h"
#include "GameObject.h"
#include "physicbody.h"
#include "PhysicManager.h"
#include "GameObjectType.h"
#include "Visitor.h"

GameObject::GameObject(const GameObject& aGameObject)
{
	myGameObjectType = nullptr;
	myPhysicBody = nullptr;
	*this = aGameObject;
}

GameObject::GameObject()
{
	myGameObjectType = nullptr;
	myPhysicBody = nullptr;
}

GameObject& GameObject::operator=(const GameObject& aGameObject)
{
	myGameObjectType = aGameObject.myGameObjectType;
	if (myPhysicBody == nullptr)
	{
		myPhysicBody = PhysicManager::GetInstance()->CreateNewPhysicBody();
		myPhysicBody->SetParent(this);
	}
	*myPhysicBody = *aGameObject.myPhysicBody;
	myPhysicBody->SetEnabled(aGameObject.myPhysicBody->IsEnabled());
	return *this;
}

GameObject& GameObject::operator=(GameObject&& aGameObject)
{
	myGameObjectType = aGameObject.myGameObjectType;
	if (myPhysicBody == nullptr)
	{
		myPhysicBody = aGameObject.myPhysicBody;
		myPhysicBody->SetParent(this);
		aGameObject.myPhysicBody = nullptr;
	}
	else
	{
		std::swap(myPhysicBody, aGameObject.myPhysicBody);
	}
	return *this;
}

GameObject::~GameObject()
{
	myGameObjectType = nullptr;
	if (myPhysicBody != nullptr)
	{
		myPhysicBody->Release();
		myPhysicBody = nullptr;
	}
}

void GameObject::Update(const float aDeltaTime)
{
	(aDeltaTime);
}
	
void GameObject::Init(GameObjectType& aGameObjectType)
{		
	assert(myGameObjectType == nullptr && "GameObject is already initated!");
	myGameObjectType = &aGameObjectType;
	myPhysicBody = PhysicManager::GetInstance()->CreateNewPhysicBody();
	myPhysicBody->SetParent(this);
	aGameObjectType.InitGameObject(*this);

	const Sprite& sprite = aGameObjectType.GetSprite();
	myPhysicBody->SetHalfSize({ sprite.GetSize().myX / 2.f, sprite.GetSize().myY / 2.f });
}

void GameObject::Draw()
{
	myGameObjectType->GetSprite().Draw(myPhysicBody->GetPosition(), myPhysicBody->GetRotation());
}

bool GameObject::Use(Player& aPlayer)
{
	return false;
}

void GameObject::Collide(GameObject* aGameObject)
{
}

void GameObject::CollidedWithMap(const MapCollisionData& aMapCollisionData)
{
}

void GameObject::Delete()
{
	Message deleteMessage(eMessageTypes::eEntityDestroyed);
	deleteMessage.myVoidPointer = this;
	PostMaster::GetInstance()->SendMessage(deleteMessage);
}

void GameObject::SetPosition(const Vector2f& aPosition)
{
	myPhysicBody->SetPosition(aPosition);
}

void GameObject::SetStartPosition(const Vector2f& aPosition)
{
	myPhysicBody->SetStartPosition(aPosition);
}

const bool GameObject::HasProperty(const PropertyKey aPropertyKey) const
{
	return myProperties.HasValue(aPropertyKey);
}

const std::string& GameObject::GetTypeName() const
{
	return myGameObjectType->GetName();
}

PhysicBody& GameObject::GetPhysicBody()
{
	return *myPhysicBody;
}

const PhysicBody& GameObject::GetPhysicBody() const
{
	return *myPhysicBody;
}
