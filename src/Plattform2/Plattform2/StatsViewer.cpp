#include "stdafx.h"
#include "StatsViewer.h"
#include "Stats.h"

StatsViewer::StatsViewer()
{
	myStats = nullptr;
}

void StatsViewer::Init(Stats& aPlayerStats)
{
	const int x = 10;
	const int y = 10;
	const int space = 18;

	myStats = &aPlayerStats;

	StatGUI health;
	StatGUI ammo;

	health.Init("Health",	{ x, y + space * 0 }, eStats::eHealth);
	ammo.Init("Ammo",		{ x, y + space * 1 }, eStats::eAmmo);
	myStatGUIS.Resize(2);
	myStatGUIS[static_cast<int>(eStats::eHealth)] = health;
	myStatGUIS[static_cast<int>(eStats::eAmmo)] = ammo;
	PostMaster::GetInstance()->Register(this, eMessageTypes::eStatChanged);
}

void StatsViewer::Draw(const Vector2<int>& aPosition)
{
	for (int statIndex = 0; statIndex < myStatGUIS.Size(); statIndex++)
	{
		myStatGUIS[statIndex].Draw();
	}
}

void StatsViewer::RecieveMessage(const Message& aMessage)
{
	myStatGUIS[aMessage.mySecondIntData].SetValue(aMessage.myFloatData);
}

void StatGUI::Init(const std::string& aText, const Vector2<int>& aPosition, const eStats aStatToDisplay)
{
	myTypeText.Init("data/fonts/corbel.ttf");
	myTypeText.SetText(aText);
	myTypeText.SetPosition(aPosition);
	myBarSprite.Init("data/gfx/statsbar.png");
	myStatToDisplay = aStatToDisplay;
}

void StatGUI::Draw()
{
	static const Color red(255_uc, 0_uc, 0_uc);
	static const Color green(100_uc, 255_uc, 0_uc);
	static const Color yellow(255_uc, 255_uc, 0_uc);

	myTypeText.Draw();	
	const Color color{ static_cast <unsigned char>(255.f * ((100.f-myValue) / 100.f)), static_cast < unsigned char>(255 * (myValue / 100.f)), 0 };
	myBarSprite.Draw({ myTypeText.GetPosition().myX + 70.f, static_cast<float>(myTypeText.GetPosition().myY) }, Vector2<int>(myValue, 16), color, 128_uc);
}

void StatGUI::SetValue(const float aValue)
{
	myValue = aValue;
}
