#include "stdafx.h"
#include "Stats.h"

Stats::Stats()
{
	for (int statIndex = 0; statIndex < static_cast<int>(eStats::eCount); statIndex++)
	{
		myStats[statIndex] = 50.f;
	}
}

float Stats::GetStat(const eStats aStat) const		  
{
	return myStats[static_cast<int>(aStat)];
}

void Stats::UpdateStats()
{

}

void Stats::SetStat(const eStats aStat, const float aValue)
{
	myStats[static_cast<int>(aStat)] = aValue;

	Message statChangeMessage(eMessageTypes::eStatChanged);
	statChangeMessage.myFloatData = myStats[static_cast<int>(aStat)];
	statChangeMessage.mySecondIntData = static_cast<int>(aStat);
	PostMaster::GetInstance()->SendMessage(statChangeMessage);
}

void Stats::ChangeStat(const eStats aStat, const float aChange)
{
	myStats[static_cast<int>(aStat)] += aChange;
	myStats[static_cast<int>(aStat)] = RANGE(myStats[static_cast<int>(aStat)], 0.f, 100.f);

	Message statChangeMessage(eMessageTypes::eStatChanged);
	statChangeMessage.myFloatData = myStats[static_cast<int>(aStat)];
	statChangeMessage.mySecondIntData = static_cast<int>(aStat);
	PostMaster::GetInstance()->SendMessage(statChangeMessage);
}
