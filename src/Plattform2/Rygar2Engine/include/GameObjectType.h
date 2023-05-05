#pragma once
#include "Variable.h"
#include "PhysicBody.h"
#include <Vector2.h>
#include <string>
#include <functional>
#include <map>
#include <..\external\rapidJSON\document.h>

class GameObject;
class Sprite;

class GameObjectType
{		
public:
								GameObjectType();
	virtual						~GameObjectType();
	GameObjectType&				operator=(GameObjectType& aObjectToCopy);

	virtual void				LoadTypeJSON(const rapidjson::GenericObject<false, rapidjson::Value>& aObject);
	void						InitGameObject(GameObject& aGameObject) const;
	Sprite&						GetSprite();
	const std::string&			GetName() const;

	const VariableContainer&	GetVariables() const;

private:
	std::string					myName;
	Sprite*						mySprite = nullptr;
	PhysicBodyData				myPhysicBodyData;
	bool						myDefaultRotate;
	VariableContainer			myVariables;
};

inline Sprite& GameObjectType::GetSprite()
{
	return *mySprite;
}

inline const std::string& GameObjectType::GetName() const
{
	return myName;
}

inline const VariableContainer& GameObjectType::GetVariables() const
{
	return myVariables;
}

