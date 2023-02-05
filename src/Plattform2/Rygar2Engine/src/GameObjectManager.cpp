#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "PhysicBody.h"
#include "Camera.h"
#include "Visitor.h"

GameObjectManager* GameObjectManager::ourInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	PostMaster::GetInstance()->Register(this, eMessageTypes::eEntityCreated);
	PostMaster::GetInstance()->Register(this, eMessageTypes::eEntityDestroyed);
}

void GameObjectManager::AddGameObject(GameObject* aGameObject)
{
	DL_ASSERT(aGameObject != nullptr && "Tried to add nullptr gameobject!");
	DL_ASSERT(myGameObjects.Find(aGameObject) == -1 && "Game object aldready added!");
	myGameObjectsToAdd.Add(aGameObject);
}

void GameObjectManager::DeleteGameObject(GameObject* aGameObject)
{
	DL_ASSERT(aGameObject != nullptr && "Tried to remove nullptr!");
	DL_ASSERT(myGameObjects.Find(aGameObject) != -1 || myGameObjectsToAdd.Find(aGameObject) != -1 && "GameObject not found!");
	const auto index = myGameObjects.Find(aGameObject);

	if(myGameObjectsToDelete.Find(aGameObject) == -1)
		myGameObjectsToDelete.Add(aGameObject);
}

GameObject* GameObjectManager::GetFirstWithName(const std::string& aGameObject)
{
	for (int gameObjectIndex = 0; gameObjectIndex < myGameObjects.Size(); gameObjectIndex++)
	{
		if (myGameObjects[gameObjectIndex]->GetTypeName() == aGameObject)
		{
			return myGameObjects[gameObjectIndex];
		}
	}

	return nullptr;
}

void GameObjectManager::DrawGameObjects(const Camera& aCamera)
{
	PhysicBody cameraBody;
	cameraBody.SetPosition(aCamera.GetPosition());
	cameraBody.SetHalfSize({ (SCREEN_WIDTH / 2.f) / aCamera.GetZoom(), (SCREEN_HEIGHT / 2.f) / aCamera.GetZoom() });

	for (int gameObjectIndex = 0; gameObjectIndex < myGameObjects.Size(); gameObjectIndex++)
	{
		if (myGameObjects[gameObjectIndex]->GetPhysicBody().Collides(cameraBody))
		{
			myGameObjects[gameObjectIndex]->Draw();
		}
	}

	cameraBody.Release();
}

void GameObjectManager::UpdateGameObjects(const float aDeltaTime)
{
	for (int gameObjectIndex = 0; gameObjectIndex < myGameObjects.Size(); ++gameObjectIndex)
	{
		myGameObjects[gameObjectIndex]->Update(aDeltaTime);
	}
}

void GameObjectManager::AddAndRemoveObjects()
{
	myGameObjects.Add(myGameObjectsToAdd);
	myGameObjectsToAdd.Clear();
	for (int i = 0; i < myGameObjectsToDelete.Size(); ++i)
	{
		myGameObjects.RemoveCyclic(myGameObjectsToDelete[i]);
		SAFE_DELETE(myGameObjectsToDelete[i]);
	}
	myGameObjectsToDelete.Clear();
}

void GameObjectManager::RecieveMessage(const Message& aMessage)
{
	switch (aMessage.myMessageType)
	{
	case eMessageTypes::eEntityDestroyed:
		DeleteGameObject(static_cast<GameObject*>(aMessage.myVoidPointer));			
		break;
	case eMessageTypes::eCreateObject:
		break;
	default:
		DL_ASSERT(false && "Tried to create unknown gameobject type!");
	}
}

void GameObjectManager::RemoveAllGameObjects()
{
	//AddAndRemoveObjects();
	for (GameObject* gameObjectToDelete : myGameObjects)
	{
		if (gameObjectToDelete->HasProperty(PropertyKey::eKeepOnLevelReset) == false)
		{
			DeleteGameObject(gameObjectToDelete);
		}
	}
	//AddAndRemoveObjects();
}

const CU::GrowingArray<GameObject*>& GameObjectManager::GetGameObjects() const
{
	return myGameObjects;
}

GameObject* GameObjectManager::GetClosest(const Vector2f& aPosition, GameObject* aGameObjecToExclude) const
{
	float closest = 9999999.f;
	GameObject* bestMatch = nullptr;
	for (int i = 0; i < myGameObjects.Size(); i++)
	{
		if (myGameObjects[i] != aGameObjecToExclude && myGameObjects[i]->GetPhysicBody().IsEnabled() == true)
		{
			float distance = aPosition.SqrdDistanceTo(myGameObjects[i]->GetPhysicBody().GetPosition());
			if (distance < closest)
			{
				closest = distance;
				bestMatch = myGameObjects[i];
			}
		}
	}
	return bestMatch;
}

void GameObjectManager::Create()
{
	DL_ASSERT(ourInstance == nullptr && "Instance already created!");
	ourInstance = new GameObjectManager();
}

void GameObjectManager::Delete()
{
	DL_ASSERT(ourInstance != nullptr && "Already deleted or not created!");
	SAFE_DELETE(ourInstance);
}

GameObjectManager* GameObjectManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr && "GameObjectManager not created yet!");
	return ourInstance;
}