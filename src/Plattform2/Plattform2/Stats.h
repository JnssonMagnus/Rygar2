#pragma once
#include <StaticArray.h>

enum class eStats
{
	eHealth,
	eAmmo,
	eCount
};

class Stats
{
public:
				Stats();
	float		GetStat(const eStats aStat) const;
	void		ChangeStat(const eStats aStat, const float aChange);
	void		SetStat(const eStats aStat, const float aValue);
	void		UpdateStats();

private:
	CU::StaticArray<float, static_cast<int>(eStats::eCount)>	
				myStats;
};
