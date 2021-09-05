#pragma once

#include "TimeUnit.h"
namespace Timer
{
	class Timer
	{
	public:
		Timer(double aStartTime);
		~Timer(void);

		void				AddTime(double aTime);
		void				Start();
		void				Stop();
		const TimeUnit&		GetFrameTime() const;
		TimeUnit			GetPassedTime() const;

	private:
		double				myLifeTime;
		bool				myOn;
		TimeUnit			myFrameTime;
	};

	inline void Timer::Start()
	{
		myOn = false;
	}

	inline void Timer::Stop()
	{
		myOn = true;
	}

	inline const TimeUnit& Timer::GetFrameTime() const
	{
		return myFrameTime;
	}

	inline TimeUnit Timer::GetPassedTime() const
	{
		return TimeUnit(static_cast<TimeType>(myLifeTime));
	}
}
