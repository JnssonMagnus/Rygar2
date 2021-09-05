#include "stdafx.h"
#include "PhysicManager.h"
#include "PhysicBody.h"
#include "gameObject.h"
#include "Grid.h"
#include <ObjectPool.h>

PhysicManager* PhysicManager::ourInstance = nullptr;

PhysicManager::PhysicManager()
{
	myObjectPool = nullptr;
}

PhysicManager::~PhysicManager()
{
	SAFE_DELETE(myObjectPool);
}

void PhysicManager::Init()
{
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePhysicBodyAdded);
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePhysicBodyRemoved);
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePhysicBodyDisabled);
	PostMaster::GetInstance()->Register(this, eMessageTypes::eLevelLoaded);
	myObjectPool = new ObjectPool<PhysicBody, PHYSBODY_POOLSIZE>();
	SetGridSize({ 1, 1 }, { 1, 1 });

}

void PhysicManager::SetGridSize(const Vector2<int>& aNumberOfNodes, const Vector2<int>& aNodeSize)
{
	delete myGrid;
	myGrid = new Grid();
	myGrid->Init(aNumberOfNodes, aNodeSize);
}

void PhysicManager::UpdatePhysicBodies()
{
	// Update bodies
	for (int physicBodyIndex = 0; physicBodyIndex < myPhysicBodies.Size(); physicBodyIndex++)
	{
		assert(myPhysicBodies[physicBodyIndex]->IsEnabled() == true && "A disabled body is among active!");
		myPhysicBodies[physicBodyIndex]->Update();
	}	

	myGrid->Update();
}

void PhysicManager::AddAndRemovePhysicBodies()
{
	// Add new bodies
	for (int newBodyIndex = 0; newBodyIndex < myPhysicBodiesToAdd.Size(); newBodyIndex++)
	{
		assert(myPhysicBodies.Find(myPhysicBodiesToAdd[newBodyIndex]) == -1 && "Body already added!");
		myPhysicBodies.Add(myPhysicBodiesToAdd[newBodyIndex]);
		myGrid->AddBody(myPhysicBodiesToAdd[newBodyIndex]);
	}

	// remove disabled bodies
	for (int disableIndex = 0; disableIndex < myPhysicBodiesToDisable.Size(); disableIndex++)
	{
		myPhysicBodies.Remove(myPhysicBodiesToDisable[disableIndex]);
		myGrid->RemoveBody(myPhysicBodiesToDisable[disableIndex]);
	}

	// Remove bodies
	for (int removeIndex = 0; removeIndex < myPhysicBodiesToRemove.Size(); removeIndex++)
	{
		int index = myPhysicBodies.Find(myPhysicBodiesToRemove[removeIndex]);
		//	assert(index != -1 && "Body to remove not found!");
		if (index != -1)
		{
			myPhysicBodies.RemoveCyclicAtIndex(index);
		}
		myObjectPool->ReturnItem(myPhysicBodiesToRemove[removeIndex]);
		myGrid->RemoveBody(myPhysicBodiesToRemove[removeIndex]);
	}

	myPhysicBodiesToDisable.Clear();
	myPhysicBodiesToRemove.Clear();
	myPhysicBodiesToAdd.Clear();
}

void PhysicManager::ResolveCollisions()
{
	auto& nodes = myGrid->GetSpatialListsWithBodies();

	std::unordered_map<long long, std::pair<PhysicBody*, PhysicBody*>> collisionsToTest;

	// Find unique collisions
	for (const auto& gridCell : nodes)
	{
		for (int physicBodyToTest = 0; physicBodyToTest < gridCell.Size(); physicBodyToTest++)
		{
			for (int physicBodyToTestAgainst = physicBodyToTest + 1; physicBodyToTestAgainst < gridCell.Size(); physicBodyToTestAgainst++)
			{
				PhysicBody* toTest = gridCell[physicBodyToTest];
				PhysicBody* toTestAgainst = gridCell[physicBodyToTestAgainst];

				long long hashKey = reinterpret_cast<long long>(toTest) * reinterpret_cast<long long>(toTestAgainst);
				collisionsToTest[hashKey] = std::make_pair(toTest, toTestAgainst);
			}
		}
	}

	// Resolve found unique collision
	for (auto& collisionPair : collisionsToTest)
	{
		PhysicBody* toTest = collisionPair.second.first;
		PhysicBody* toTestAgainst = collisionPair.second.second;

		const float totalWeight = toTest->GetMass()* toTest->GetMass() + toTestAgainst->GetMass()* toTestAgainst->GetMass();
		if (toTest->Collides(*toTestAgainst))
		{
			if (toTest->GetParent() != nullptr && toTestAgainst->GetParent() != nullptr)
			{
				toTest->GetParent()->Collide(toTestAgainst->GetParent());
				toTestAgainst->GetParent()->Collide(toTest->GetParent());
			}

			if (toTest->GetOption(ePhysicBodyOptions::eKinetic) == false && toTestAgainst->GetOption(ePhysicBodyOptions::eKinetic) == false)
			{
				Vector2f force;

				if (toTest->GetPosition().myX < toTestAgainst->GetPosition().myX)
				{
					force.x = (toTestAgainst->GetPosition().myX - toTestAgainst->GetHalfSize().myX) - (toTest->GetPosition().myX + toTest->GetHalfSize().myX);
				}
				else
				{
					force.x = (toTestAgainst->GetPosition().myX + toTestAgainst->GetHalfSize().myX) - (toTest->GetPosition().myX - toTest->GetHalfSize().myX);
				}

				if (toTest->GetPosition().myY < toTestAgainst->GetPosition().myY)
				{
					force.y = (toTestAgainst->GetPosition().myY - toTestAgainst->GetHalfSize().myY) - (toTest->GetPosition().myY + toTest->GetHalfSize().myY);
				}
				else
				{
					force.y = (toTestAgainst->GetPosition().myY + toTestAgainst->GetHalfSize().myY) - (toTest->GetPosition().myY - toTest->GetHalfSize().myY);
				}

				if (abs(force.y) < 0.1f) force.y = 0;
				if (abs(force.x) < 0.1f) force.x = 0;
				force *= ((force.Length()) / 600.f); // was 600
				toTest->AddForce(force * ((toTestAgainst->GetMass() * toTestAgainst->GetMass()) / totalWeight) * toTest->GetMass());
				toTestAgainst->AddForce((force * -1.f) * ((toTest->GetMass() * toTest->GetMass()) / totalWeight) * toTestAgainst->GetMass());
			}
		}
	}
}

void PhysicManager::RecieveMessage(const Message& aMessage)
{
	switch (aMessage.myMessageType)
	{
	case eMessageTypes::ePhysicBodyAdded:
		myPhysicBodiesToAdd.Add(static_cast<PhysicBody*>(aMessage.myVoidPointer));
		break;
	case eMessageTypes::ePhysicBodyRemoved:
		myPhysicBodiesToRemove.Add(static_cast<PhysicBody*>(aMessage.myVoidPointer));
		break;
	case eMessageTypes::ePhysicBodyDisabled:
		myPhysicBodiesToDisable.Add(static_cast<PhysicBody*>(aMessage.myVoidPointer));
		break;
	case eMessageTypes::eLevelLoaded:
		SetGridSize({ aMessage.myIntData / 50, aMessage.mySecondIntData / 50 }, { 50, 50 });
		break;
	}
}

PhysicBody* PhysicManager::CreateNewPhysicBody()
{
	return myObjectPool->GetItem();
}

PhysicManager* PhysicManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr && "PhysicManager not created!");
	return ourInstance;
}

void PhysicManager::Create()
{
	DL_ASSERT(ourInstance == nullptr && "PhysicManager already created!");
	ourInstance = new PhysicManager();
}

void PhysicManager::Destroy()
{
	DL_ASSERT(ourInstance != nullptr && "Tried to destroy Physic manager, there is none!");
	SAFE_DELETE(ourInstance);
}
