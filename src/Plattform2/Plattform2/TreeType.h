#pragma once
#include <GrowingArray.h>
#include "Sprite.h"

struct BranchRotation
{

	float myMinRad = 0.f;
	float myMaxRad = 0.f;
};

struct BranchPlacement
{
	float myMin = 0.f;
	float myMax = 1.f;
};

struct BranchLevelData
{
	Sprite			mySprite;
	BranchRotation	myBranchRotation;
	BranchPlacement myBranchPlacement;
	float			myMaxGrowth = 1.f;
};

class TreeType
{
public:
				
										TreeType();
	int									GetLeafLevel() const;
	void								SetLeafLevel(const int aLeafLevel);

	void								SetRootSprite(const char* aSpriteFilename);
	void								SetLeafSprite(const char* aSpriteFilename);

	void								SetDefaultSprite(const char* aSpriteFilename);
	void								SetDefaultRotation(const float aMinRad, const float aMaxRad);
	void								SetDefaultPlacement(const float aMin, const float aMax);

	void								SetSpriteAtLevel(const int aLevelIndex, const char* aSpriteFilename);
	void								SetMaxGrowthAtLevel(const int aLevelIndex, const float aMaxGrowth);
	void								SetRotationAtLevel(const int aLevelIndex, const float aMaxRad, const float aMinRad);

	Sprite&								GetSpriteAtLevel(const int aLevel);
	BranchLevelData&					GetBranchData(const int aLevel);
	float								GetRandomAngleFromLevel(const int aLevel) const;
	float								GetRandomPlacementFromLevel(const int aLevel) const;

private:
	int									myLeafLevel;
	CU::GrowingArray<BranchLevelData>	myBranchLevelData;
};
