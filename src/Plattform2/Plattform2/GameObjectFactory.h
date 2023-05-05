#pragma once
#include "gameObjectTypes.h"
#include "GameObjectType.h"
#include "EnemyType.h"
#include <unordered_map>
#include <memory>

class GameObject;
class GameObjectFactory
{
public:
								GameObjectFactory();
	void						Init();
	std::unique_ptr<GameObject>	CreateObject(const eGameObjectTypes aGameObjectType);
	std::unique_ptr<GameObject>	CreateObject(const int aGameObjectTypeID);
	std::unique_ptr<GameObject> CreateEnemy(const int aGameObjectTypeID);
	std::unique_ptr<GameObject> CreateEnemy(const std::string_view aEnemyName);
private:
	GameObjectType&			GetGameObjectType(const eGameObjectTypes aGameObjectType);		

	void					LoadGameObjectTypes();
	void					LoadEnemyTypes();
	void					InitTypeIDToEnums();

	std::unordered_map<int, eGameObjectTypes>
							myGameObjectTypeIDToEnum;
	std::unordered_map<eGameObjectTypes, int>
							myEnumToGameObjectTypeID;

	std::unordered_map<int, GameObjectType>
							myGameObjectTypes;

	std::unordered_map<int, EnemyType>
							myEnemyTypes;
};
