#pragma once
#include "gameObjectTypes.h"
#include "GameObjectType.h"
#include <unordered_map>

class GameObject;
class TreeType;
class GameObjectFactory
{
public:
							GameObjectFactory();
	void					Init();
	GameObject*				CreateObject(const eGameObjectTypes aGameObjectType);
	GameObject*				CreateObject(const int aGameObjectTypeID);
private:
	GameObjectType&			GetGameObjectType(const eGameObjectTypes aGameObjectType);		

	void					LoadGameObjectTypes();
	void					InitTypeIDToEnums();

	TreeType*				myTreeType;
	std::unordered_map<int, eGameObjectTypes>
							myGameObjectTypeIDToEnum;
	std::unordered_map<eGameObjectTypes, int>
							myEnumToGameObjectTypeID;

	std::unordered_map<int, GameObjectType>
							myGameObjectTypes;
};
