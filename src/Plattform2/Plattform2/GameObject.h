#pragma once
#include "sprite.h"
#include "CollisionPoint.h"
#include <OpaqueDictionary.h>

class PhysicBody;
class GameObjectType;
class Player;

enum class ePropertyValues
{
	eLife,
	eAlive,
	eFacingRight
};

typedef ePropertyValues PropertyKey;

class GameObject
{
public:
							GameObject(const GameObject& aGameObject);
							GameObject();
	GameObject&				operator=(const GameObject& aGameObject);
	GameObject&				operator=(GameObject&& aGameObject);
	virtual					~GameObject();
	virtual void			Update(const float aDeltaTime);
	virtual void			Init(GameObjectType& aGameObjectType);
	virtual void			Draw();
	virtual bool			Use(Player& aPlayer);
	virtual void			Collide(GameObject* aGameObject);
	virtual void			CollideWithTile(eCollisionPoint collisionPoint = eCollisionPoint::eNoCollision);
	void					Delete();

	template<class T>
	const T&				GetProperty(const PropertyKey) const;

	template<class T>
	T&						ChangeProperty(const PropertyKey aPropertyKey);

	const std::string&		GetTypeName() const;

	PhysicBody&				GetPhysicBody();
	const PhysicBody&		GetPhysicBody() const;

protected:
	PhysicBody*				myPhysicBody;
	GameObjectType*			myGameObjectType;

	CU::OpaqueDictionary<PropertyKey>
							myProperties;
};

template<class T>
inline const T& GameObject::GetProperty(const PropertyKey aPropertyKey) const
{
	return myProperties.GetValue<T>(aPropertyKey);
}

template<class T>
inline T& GameObject::ChangeProperty(const PropertyKey aPropertyKey)
{
	return myProperties.ChangeValue<T>(aPropertyKey);
}
