#pragma once
#include "gameObjectTypes.h"
#include "GameObjectType.h"
#include <unordered_map>
#include <memory>

class GameObject;
class TreeType;
class GameObjectFactory
{
public:
								GameObjectFactory();
	void						Init();
	std::unique_ptr<GameObject>	CreateObject(const eGameObjectTypes aGameObjectType);
	std::unique_ptr<GameObject>	CreateObject(const int aGameObjectTypeID);
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
