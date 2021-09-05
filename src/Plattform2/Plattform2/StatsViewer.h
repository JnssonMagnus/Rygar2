#pragma once
#include "Text.h"
#include "GUISprite.h"
#include <PostMaster/Observer.h>
#include <GrowingArray.h>

class Stats;
enum class eStats;

class StatGUI 
{
public:
	void				Init(const std::string& aText, const Vector2<int>& aPosition, const eStats aStatToDisplay);
	void				Draw();
	void				SetValue(const float aValue);

private:
	Text				myTypeText;
	GUISprite			myBarSprite;
	float				myValue;
	eStats				myStatToDisplay;
};

class StatsViewer : public Observer
{
public:
								StatsViewer();
	void						Init(Stats& aPlayerStats);
	void						Draw(const Vector2<int>& aPosition);
	void						RecieveMessage(const Message& aMessage) override;

private:
	CU::GrowingArray<StatGUI>	myStatGUIS;
	Stats*						myStats;
};
