#include "stdafx.h"
#include "TimerManager.h"
#include <assert.h>
#include <iostream>

namespace Timer
{
	TimerManager* TimerManager::ourInstance = nullptr;

	void TimerManager::Create()
	{
		assert(ourInstance == nullptr && "TimerManager instance already created!");
		ourInstance = new TimerManager();
	}

	void TimerManager::Destroy()
	{
		assert(ourInstance != nullptr && "TimerManager is not initiated or already destroyed");
		SAFE_DELETE(ourInstance);
	}

	TimerManager* TimerManager::GetInstance()
	{
		assert(ourInstance != nullptr && "TimerManager hasn't been created!");
		return ourInstance;
	}
	TimerManager::TimerManager(void)
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);

		myFrequence = static_cast<double>(freq.QuadPart) / 1000000000.0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		myLastTime = time;

		CreateMasterTimer();		
	}

	TimerManager::~TimerManager(void)
	{
	}

	void TimerManager::CreateMasterTimer()
	{
		CreateTimer();
	}

	void TimerManager::UpdateTimers()
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].AddTime((time.QuadPart - myLastTime.QuadPart) / myFrequence);
		}

		myLastTime = time;
	}

	void TimerManager::Start()
	{
		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].Start();
		}
	}

	void TimerManager::Stop()
	{
		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].Stop();
		}
	}

	const Timer& TimerManager::GetTimer(TimerHandle aHandle) const
	{
		assert(aHandle < myTimers.size() && "GetTimer out of bounds!");
		return myTimers[aHandle];
	}

	TimerHandle	TimerManager::CreateTimer()
	{
		myTimers.push_back(Timer(myLastTime.QuadPart / myFrequence));
		return static_cast<TimerHandle>(myTimers.size() - 1);
	}

	void TimerManager::PrintTimers() const
	{
		//system("cls");
		//for (unsigned int i = 0; i < myTimers.size(); ++i)
		//{
		//	TimeUnit time = myTimers[i].GetTime();
		//	std::cout << "Timer " << i << std::endl;
		//	std::cout << "Hours: " << time.GetHours() << std::endl;
		//	std::cout << "Minutes: " << time.GetMinutes() << std::endl;
		//	std::cout << "Seconds: " << time.GetSeconds() << std::endl;
		//	std::cout << "Milliseconds: " << time.GetMilliseconds() << std::endl;
		//	std::cout << "Microseconds: " << time.GetMicroseconds() << std::endl;
		//	std::cout << "FPS:" << time.GetFPS() << std::endl;
		//	std::cout << "FrameTime:" << time.GetFrameTime() << std::endl;
		//}

	}

	void TimerManager::StartAndResetStopWatch()
	{
		QueryPerformanceCounter(&myInternalStopWatchHandle);
	}

	TimeUnit TimerManager::StopStopWatch()
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return static_cast<TimeUnit>((time.QuadPart - myInternalStopWatchHandle.QuadPart) / myFrequence);
	}
}