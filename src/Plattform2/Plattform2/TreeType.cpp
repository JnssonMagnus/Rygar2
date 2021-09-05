#include "stdafx.h"
#include "TreeType.h"

TreeType::TreeType()
{
	myLeafLevel = 0;
}

int TreeType::GetLeafLevel() const
{
	return myLeafLevel;
}

void TreeType::SetLeafLevel(const int aLeafLevel)
{
	assert(aLeafLevel >= 0 && "Out of bounds!");
	myLeafLevel = aLeafLevel;
	myBranchLevelData.Resize(myLeafLevel + 1);
}

void TreeType::SetRootSprite(const char* aSpriteFilename)
{
	SetSpriteAtLevel(0, aSpriteFilename);
}

void TreeType::SetLeafSprite(const char* aSpriteFilename)
{
	SetSpriteAtLevel(myLeafLevel, aSpriteFilename);
}

void TreeType::SetDefaultSprite(const char* aSpriteFilename)
{
	for (size_t i = 0; i < myBranchLevelData.Size(); i++)
	{
		SetSpriteAtLevel(i, aSpriteFilename);
	}
}

void TreeType::SetDefaultRotation(const float aMinRad, const float aMaxRad)
{
	for (size_t i = 0; i < myBranchLevelData.Size(); i++)
	{
		myBranchLevelData[i].myBranchRotation.myMinRad = aMinRad;
		myBranchLevelData[i].myBranchRotation.myMaxRad = aMaxRad;
	}
}

void TreeType::SetDefaultPlacement(const float aMin, const float aMax)
{
	for (size_t i = 0; i < myBranchLevelData.Size(); i++)
	{
		myBranchLevelData[i].myBranchPlacement.myMin = aMin;
		myBranchLevelData[i].myBranchPlacement.myMax = aMax;
	}
}

Sprite& TreeType::GetSpriteAtLevel(const int aLevel)
{
	assert(aLevel >= 0 && myBranchLevelData.Size() && "out of bounds!");
	return myBranchLevelData[aLevel].mySprite;
}

BranchLevelData& TreeType::GetBranchData(const int aLevel)
{
	assert(aLevel >= 0 && aLevel < myBranchLevelData.Size() && "out of bounds!");
	return myBranchLevelData[aLevel];
}

float TreeType::GetRandomAngleFromLevel(const int aLevel) const
{
	const float min = myBranchLevelData[aLevel].myBranchRotation.myMinRad;
	const float max = myBranchLevelData[aLevel].myBranchRotation.myMaxRad;
	return CU::RandomF(min, max);
}

float TreeType::GetRandomPlacementFromLevel(const int aLevel) const
{
	return CU::RandomF(myBranchLevelData[aLevel].myBranchPlacement.myMin, myBranchLevelData[aLevel].myBranchPlacement.myMax);
}
	
void TreeType::SetSpriteAtLevel(const int aLevelIndex, const char* aSpriteFilename)
{
	assert(aLevelIndex >= 0 && aLevelIndex < myBranchLevelData.Size() && "out of bounds!");
	myBranchLevelData[aLevelIndex].mySprite.Init(aSpriteFilename);
}

void TreeType::SetMaxGrowthAtLevel(const int aLevelIndex, const float aMaxGrowth)
{
	assert(aLevelIndex >= 0 && aLevelIndex < myBranchLevelData.Size() && "out of bounds!");
	myBranchLevelData[aLevelIndex].myMaxGrowth = aMaxGrowth;
}

void TreeType::SetRotationAtLevel(const int aLevelIndex, const float aMaxRad, const float aMinRad)
{
	assert(aLevelIndex >= 0 && aLevelIndex < myBranchLevelData.Size() && "out of bounds!");
	myBranchLevelData[aLevelIndex].myBranchRotation.myMaxRad = aMaxRad;
	myBranchLevelData[aLevelIndex].myBranchRotation.myMinRad = aMinRad;
}
