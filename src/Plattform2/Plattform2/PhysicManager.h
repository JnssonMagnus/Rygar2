#pragma once
#include <PostMaster/Observer.h>
#include <growingArray.h>

class PhysicBody;
class Grid;
class PhysicBodyVisitor;

template<class T, int SIZE>
class ObjectPool;

constexpr int PHYSBODY_POOLSIZE = 1500;

class PhysicManager : public Observer
{
public:
	void							Init();
	void							UpdatePhysicBodies();
	void							AddAndRemovePhysicBodies();
	void							ResolveCollisions();
	void							RecieveMessage(const Message& aMessage) override;
	void							Visit(PhysicBodyVisitor& aPhysicBodyVisitor);
	PhysicBody*						CreateNewPhysicBody();
	static PhysicManager*			GetInstance();
	static void						Create();
	static void						Destroy();

private:
									PhysicManager();
									~PhysicManager();
	void							SetGridSize(const Vector2<int>& aNumberOfNodes, const Vector2<int>& aNodeSize);
	CU::GrowingArray<PhysicBody*>	myPhysicBodies;
	CU::GrowingArray<PhysicBody*>	myPhysicBodiesToAdd;
	CU::GrowingArray<PhysicBody*>	myPhysicBodiesToRemove;
	CU::GrowingArray<PhysicBody*>	myPhysicBodiesToDisable;
	ObjectPool<PhysicBody, PHYSBODY_POOLSIZE>*	myObjectPool;
	static PhysicManager*			ourInstance;
	Grid*							myGrid = nullptr;
};

