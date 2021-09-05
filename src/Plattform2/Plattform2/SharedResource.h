#pragma once
#include <Debugger/DL_Debug.h>

template<class T>
class SharedResource
{
public:
					SharedResource();
					~SharedResource();
					SharedResource(T* aResourceData);
					SharedResource(const SharedResource& aSharedResource);
	void			Init(T* aResourceData);
	SharedResource& operator=(const SharedResource& aSharedResource);
	const T*		GetResource() const;

private:
	T*		myResourceData;
	int*	myCounter;
};

template<class T>
inline SharedResource<T>::SharedResource()
{
	myCounter = nullptr;
	myResourceData = nullptr;
}

template<class T>
inline SharedResource<T>::~SharedResource()
{
	if (myCounter != nullptr)
	{
		(*myCounter)--;
	}
}

template<class T>
inline SharedResource<T>::SharedResource(T* aResourceData)
{
	Init(aResourceData);
}

template<class T>
inline SharedResource<T>::SharedResource(const SharedResource& aSharedResource)
{
	this->operator=(aSharedResource);
}

template<class T>
inline void SharedResource<T>::Init(T* aResourceData)
{
	DL_ASSERT(myCounter == nullptr && "Resourc already initiated!");
	DL_ASSERT(aResourceData != nullptr && "Can't init shared resource with nullptr!");
	myCounter = new int(0);
	myResourceData = aResourceData;
}

template<class T>
SharedResource<T>& SharedResource<T>::operator=(const SharedResource& aSharedResource)
{
	DL_ASSERT(aSharedResource.myResourceData != nullptr && "Tried to copy a dead resource!");
	if (myCounter != nullptr)
	{
		myCounter--;
	}

	myResourceData = aSharedResource.myResourceData;
	myCounter = aSharedResource.myCounter;
	(*myCounter)++;
	return *this;
}

template<class T>
inline const T* SharedResource<T>::GetResource() const
{
	DL_ASSERT(myResourceData != nullptr && "Can't get resource, resource is deleted!");
	return myResourceData;
}
