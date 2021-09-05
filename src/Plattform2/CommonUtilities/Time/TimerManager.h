#pragma once
#include "Timer.h"
#include <vector>
#include <Windows.h>

//#ifndef NDEBUG
#define START_STOP_WATCH Timer::TimerManager::GetInstance()->StartAndResetStopWatch();
#define STOP_STOP_WATCH Timer::TimerManager::GetInstance()->StopStopWatch()
//#else
//#define START_STOP_WATCH
//#define STOP_STOP_WATCH
//#endif

namespace Timer
{
	typedef unsigned int TimerHandle;
	const TimerHandle MasterTimer = 0;

#define DELTA_TIME Timer::TimerManager::GetInstance()->GetTimer(Timer::MasterTimer).GetFrameTime()

	class TimerManager
	{
	public:
		TimerHandle				CreateTimer();
		const Timer&			GetTimer(TimerHandle aHandle) const;
		void					UpdateTimers();
		void					Start();
		void					Stop();
		void					PrintTimers() const;
		void					StartAndResetStopWatch();
		TimeUnit				StopStopWatch();
		static void				Create();
		static void				Destroy();
		static TimerManager*	GetInstance();

	private:
		TimerManager(void);
		~TimerManager(void);

		void					CreateMasterTimer();

		static TimerManager		*ourInstance;

		std::vector<Timer>		myTimers;
		std::vector<LARGE_INTEGER>
			myStopWatches;
		LARGE_INTEGER			myLastTime;
		double					myFrequence;
		LARGE_INTEGER			myInternalStopWatchHandle;

	};
}
