#pragma once
#include <GrowingArray.h>

class GameObject;
class Camera;

class GameObjectManager : public Observer
{
public:
		
											GameObjectManager();
	void									AddGameObject(GameObject* aGameObject);
	void									DeleteGameObject(GameObject* aGameObject);
	GameObject*								GetFirstWithName(const std::string& aGameObject);
	void									DrawGameObjects(const Camera& aCamera);
	void									UpdateGameObjects(const float aDeltaTime);
	void									AddAndRemoveObjects();
	void									RecieveMessage(const Message& aMessage) override;
	void									RemoveAllGameObjects();
	const CU::GrowingArray<GameObject*>&	GetGameObjects() const;

	GameObject*								GetClosest(const Vector2f& aPosition, GameObject* aGameObjecToExclude) const;

	static void								Create();
	static void								Delete();
	static GameObjectManager*				GetInstance();

private:
	CU::GrowingArray<GameObject*>			myGameObjects;
	CU::GrowingArray<GameObject*>			myGameObjectsToAdd;
	CU::GrowingArray<GameObject*>			myGameObjectsToDelete;
	static GameObjectManager*				ourInstance;
};

