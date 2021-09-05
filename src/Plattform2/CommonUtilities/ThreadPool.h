#pragma once
#include "GrowingArray.h"
#include "TemplatedWork.h"
#include "Worker.h"
#include <mutex>

class ThreadPool
{
public:
	template<class T>
	void										AddWork(const T& aFunctor);
	template<class T>
	void										AddSubTask(const T& aFunctor);

	void										DoAllWork();
	void										DoAllSubTasks();
	static void									Create();
	static ThreadPool*							GetInstance();

private:
	ThreadPool();
	~ThreadPool();

	void										WaitUntilWorkIsDone(CU::GrowingArray<Work*>& aWorkAssigned);
	volatile bool								myIsDoingAllWork;
	volatile bool								myIsDoingAllSubTasks;
	CU::GrowingArray<Worker>					myWorkers;
	CU::GrowingArray<Work*>						myWork;
	CU::GrowingArray<Work*>						mySubTasks;
	void										WorkOnTaskList(CU::GrowingArray<Work*>& aWorkList);
	std::mutex									myMutex;
	static ThreadPool							*myInstance;
};

template<class T>
void ThreadPool::AddWork(const T& aFunctor)
{
	myMutex.lock();
	myWork.Add(new TemplatedWork<T>(aFunctor));
	myMutex.unlock();
}

template<class T>
void ThreadPool::AddSubTask(const T& aFunctor)
{
	myMutex.lock();
	mySubTasks.Add(new TemplatedWork<T>(aFunctor));
	myMutex.unlock();
}

