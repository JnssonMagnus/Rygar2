#include "stdafx.h"
#include "Worker.h"
#include "NameThread.h"
#include <thread>
#include <assert.h>

Worker::Worker()
{
	myState = eWorkerState::eIdle;
	myWork = nullptr;
	myHasQuit = false;
	myThread = nullptr;
}

void Worker::Init()
{
	assert(myThread == nullptr && "Thread already initiated!");
	myThread = new std::thread(&Worker::WorkThread, this);
}

Worker::~Worker()
{
	myHasQuit = true;
	if (myThread != nullptr)
	{
		myThread->join();
		delete myThread;
		myThread = nullptr;
	}

}

bool Worker::IsWorking() const
{
	return (myState == eWorkerState::eWorking || myState == eWorkerState::eNewWork);
}

void Worker::WorkThread()
{
	SetThreadName("OneFPS: Worker Thread");
	while (myHasQuit == false)
	{
		if (myState == eWorkerState::eNewWork)
		{
			assert(myWork != nullptr && "myWork is nullptr!");
			myState = eWorkerState::eWorking;
			myWork->DoWork();
			myWork = nullptr;
			myState = eWorkerState::eIdle;
		}
		else if (myState == eWorkerState::eIdle)
		{
			std::this_thread::yield();
		}
	}
}

void Worker::AssignWork(Work *someWork)
{
	assert(IsWorking() == false && "Worker is already working!");
	assert(someWork != nullptr && "Assigned work is nullptr!");
	myWork = someWork;
	myState = eWorkerState::eNewWork;
}