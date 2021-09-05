#pragma once
#include "TemplatedWork.h"

class Work;

namespace std
{
	class thread;
}

enum class eWorkerState
{
	eIdle,
	eNewWork,
	eWorking,
};

class Worker
{
public:
								Worker();
								~Worker();
	void						Init();
	void						AssignWork(Work *someWork);
	bool						IsWorking() const;

private:
	void						WorkThread();
	volatile eWorkerState		myState;
	volatile bool				myHasQuit;
	std::thread*				myThread;
	Work *volatile				myWork;
};


