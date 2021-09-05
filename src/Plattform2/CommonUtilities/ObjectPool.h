#pragma once
#include "StaticArray.h"
#include <queue>
#include <assert.h>
#include <PostMaster/Observer.h>
//#include <new>

template<typename T, int SIZE=100>
class ObjectPool : public Observer
{
public:
								ObjectPool();
								~ObjectPool();
	template<typename ... args>
	T*							GetItem(args...);
	void						ReturnItem(T* aItem);
	void						RecieveMessage(const Message& aMessage) override;
	void						RemoveDeadObjects();
	bool						IsFull() const;


private:
	CU::StaticArray<char, SIZE * sizeof(T)>
								myPool;
	std::queue<T*>				myFreeItems;
	std::queue<T*>				myObjectsToRemove;
};



template<typename T, int SIZE>
void ObjectPool<T, SIZE>::RecieveMessage(const Message& aMessage)
{
	myObjectsToRemove.push(reinterpret_cast<T*>(aMessage.myVoidPointer));
}

template<typename T, int SIZE>
void ObjectPool<T, SIZE>::RemoveDeadObjects()
{
	while (myObjectsToRemove.empty() == false)
	{
		ReturnItem(myObjectsToRemove.front());
		myObjectsToRemove.pop();
	}
}

template<typename T, int SIZE>
inline bool ObjectPool<T, SIZE>::IsFull() const
{
	return (myFreeItems.size() == SIZE);
}

template<typename T, int SIZE>
ObjectPool<T, SIZE>::ObjectPool()
{
	for (int i = 0; i < SIZE; ++i)
	{
		myFreeItems.push(reinterpret_cast<T*>(&myPool[i * sizeof(T)]));
	}
}

template<typename T, int SIZE>
ObjectPool<T, SIZE>::~ObjectPool()
{
}

template<typename T, int SIZE>
template<typename  ...args>
T* ObjectPool<T, SIZE>::GetItem(args... someArgs)
{
	assert(myFreeItems.empty() == false && "Pool is empty!");
	T* freeAdress = myFreeItems.front();
	myFreeItems.pop();
	T* newItem = new (freeAdress) T(someArgs...);
	//newItem->AttachObserver(eMessageTypes::eEntityDestroyed, this);
	return newItem;
}

template<typename T, int SIZE>
void ObjectPool<T, SIZE>::ReturnItem(T* aItem)
{
	assert(aItem != nullptr && "Can't return nullptr!");
	//aItem->DetachObserver(eMessageTypes::eEntityDestroyed, this);
	aItem->~T();
	myFreeItems.push(aItem);
}


