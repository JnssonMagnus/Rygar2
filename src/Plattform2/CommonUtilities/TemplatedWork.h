#pragma once
#include "Work.h"

template<class T>
class TemplatedWork : public Work
{
public:
	TemplatedWork(const T& aFunctor);
	~TemplatedWork() = default;

	void DoWork() override;

private:
	T myWork;
};

template<class T>
void TemplatedWork<T>::DoWork()
{
	myWork();
	myDone = true;
}

template<class T>
TemplatedWork<T>::TemplatedWork(const T& aFunctor) : myWork(aFunctor)
{
}