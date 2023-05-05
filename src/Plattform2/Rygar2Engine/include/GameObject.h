#pragma once
#include "sprite.h"
#include "CollisionPoint.h"
#include "Variable.h"
#include "GameObjectType.h"
#include <OpaqueDictionary.h>
#include <set>

struct MapCollisionData;
class PhysicBody;
class GameObjectType;
class Player;

enum class ePropertyValues
{
	eLife,
	eMaxLife,
	eAlive,
	eFacingRight,
	eIsAttacking,
	eDucking,
	eKeepOnLevelReset
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
	virtual void			CollidedWithMap(const MapCollisionData& aMapCollisionData);
	void					Delete();
	void					SetPosition(const Vector2f& aPosition);
	
	// Also moves the "old position" so it appears as if the character got teleported
	void					SetStartPosition(const Vector2f& aPosition);

	template<class T>
	const T&				GetProperty(const PropertyKey aPropertyKey) const;

	const bool				HasProperty(const PropertyKey aPropertyKey) const;

	template<class T>
	T						GetGameObjectTypeVariable(const std::string& key) const;

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
	VariableContainer		myOverrideTypeValues;
};

template<class T>
inline const T& GameObject::GetProperty(const PropertyKey aPropertyKey) const
{
	return myProperties.GetValue<T>(aPropertyKey);
}

template<class T>
inline T GameObject::GetGameObjectTypeVariable(const std::string& key) const
{
	T value;
	if (myOverrideTypeValues.GetValue<T>(key, value)) {
		return value;
	}
	else {
		return myGameObjectType->GetVariables().GetValue<T>(key);
	}
}

template<class T>
inline T& GameObject::ChangeProperty(const PropertyKey aPropertyKey)
{
	return myProperties.ChangeValue<T>(aPropertyKey);
}
