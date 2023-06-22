#include "stdafx.h"
#include "ThreadPool.h"
#include <thread>

ThreadPool* ThreadPool::myInstance = nullptr;

ThreadPool::ThreadPool()
{
	constexpr int WORKERS = 4;
	myIsDoingAllWork = false;
	myIsDoingAllSubTasks = false;
	myWorkers.Reserve(WORKERS);
	for (unsigned int i = 0; i < WORKERS; ++i)
	{
		myWorkers.Add(Worker());
		myWorkers[i].Init();
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::Create()
{
	assert(myInstance == nullptr && "ThreadPool already created!");
	myInstance = new ThreadPool();
}

ThreadPool*	ThreadPool::GetInstance()
{
	assert(myInstance != nullptr && "ThreadPool not created!");
	return myInstance;
}

void ThreadPool::DoAllWork()
{
	assert(myIsDoingAllWork == false && "Is already doing all work! Don't call this function recusivly!");
	myIsDoingAllWork = true;
	WorkOnTaskList(myWork);
	myIsDoingAllWork = false;
}

void ThreadPool::DoAllSubTasks()
{
	assert(myIsDoingAllSubTasks == false && "Is already doing all subtasks! Don't call this function recusivly!");
	myIsDoingAllSubTasks = true;
	WorkOnTaskList(mySubTasks);
	myIsDoingAllSubTasks = false;
}

void ThreadPool::WorkOnTaskList(CU::GrowingArray<Work*>& aWorkList)
{
	CU::GrowingArray<Work*> assignedWork;
	while (aWorkList.Size() > 0)
	{
		for (int i = 0; i < myWorkers.Size(); ++i)
		{
			if (aWorkList.Size() < 1)
			{
				break;
			}

			myMutex.lock();
			if (myWorkers[i].IsWorking() == false)
			{
				assignedWork.Add(aWorkList[0]);
				myWorkers[i].AssignWork(aWorkList[0]);
				aWorkList.RemoveCyclicAtIndex(0);
			}
			myMutex.unlock();
		}
	}	

	WaitUntilWorkIsDone(assignedWork);
}

void ThreadPool::WaitUntilWorkIsDone(CU::GrowingArray<Work*>& aWorkAssigned)
{
	for (int i = 0; i < aWorkAssigned.Size(); ++i)
	{
		if (aWorkAssigned[i]->IsDone() == false)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			--i;
		}
	}

	aWorkAssigned.DeleteAll();
}
