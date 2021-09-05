#include "stdafx.h"
#include "Tree.h"
#include "Apple.h"
#include "PhysicBody.h"
#include "GameObjectManager.h"
#include "Megaton.h"
#include "map.h"
#include "TreeType.h"

static constexpr int ROOT = 0;
static constexpr int MAX_BRANCHES = 200;

Tree::Tree()
{
	myTreeType = nullptr;

	Branch root;
	root.myGrowth = 0.f;
	root.myLevel = 0;
	root.myLocalPosition = { 0.f, 0.f };
	root.myRotation = 0.f;
	myChildren.push_back(root);
	myChildren.reserve(MAX_BRANCHES);
}

void Tree::Update(const float aDeltaTime)
{
	assert(myTreeType != nullptr && "Tree not initiated!");

	Grow(0, 0.f);
	Update(0, myPhysicBody->GetPosition(), 0.f, 1.f);
}

void Tree::Draw()
{
	Draw(0, 0.f, 1.f);
}
	
void Tree::SetTreeType(TreeType* aTreeType)
{
	DL_ASSERT(aTreeType != nullptr && "TreeType is nullptr!");
	myTreeType = aTreeType;
}

void Tree::Draw(const int aBranchIndex, const float aParentRotation, const float aParentGrowth)
{
	assert(myTreeType != nullptr && "Tree not initiated!");

	Vector2<int> size;
	const Branch& currentBranch = myChildren[aBranchIndex];
	size.myY = static_cast<int>(myTreeType->GetSpriteAtLevel(currentBranch.myLevel).GetSize().myY * currentBranch.myGrowth);
	size.myX = static_cast<int>(myTreeType->GetSpriteAtLevel(currentBranch.myLevel).GetSize().myX * currentBranch.myGrowth);
		
	myTreeType->GetSpriteAtLevel(currentBranch.myLevel).SetPivot({ size.myX / 2, size.myY });
	myTreeType->GetSpriteAtLevel(currentBranch.myLevel).Draw(currentBranch.myWorldPosition, { static_cast<int>(size.myX), static_cast<int>(size.myY) }, currentBranch.myRotation);

	for (int childIndex = 0; childIndex < currentBranch.myChildrenIndex.Size(); childIndex++)
	{
		Draw(currentBranch.myChildrenIndex[childIndex], currentBranch.myRotation, currentBranch.myGrowth);
	}
}
	
void Tree::Grow(const int aBranchIndex, const float aGrowth)
{
	Branch& currentBranch = myChildren[aBranchIndex];
	float growth = aGrowth;
	if (currentBranch.myLevel == ROOT)
	{
		if (Megaton::GetInstance().GetMap().TryTakeWater(1, currentBranch.myWorldPosition + Vector2f(0, -2)) == true)
		{
			growth += 0.001f;
		}
	}

	if (currentBranch.myGrowth < myTreeType->GetBranchData(currentBranch.myLevel).myMaxGrowth)
	{
		currentBranch.myGrowth += growth;
	}
	else
	{
		currentBranch.myGrowth = myTreeType->GetBranchData(currentBranch.myLevel).myMaxGrowth;
	}

	for (int childIndex = 0; childIndex < currentBranch.myChildrenIndex.Size(); childIndex++)
	{
		Grow(currentBranch.myChildrenIndex[childIndex], growth);
	}
}

void Tree::Update(const int aBranchIndex, const Vector2f& aParentPosition, const float aParentRotation, const float aParentGrowth)
{
	DL_ASSERT(myChildren.size() < MAX_BRANCHES - 2 && "Almost out of branches! Increase cap!");
	Branch& currentBranch = myChildren[aBranchIndex];
	const float totalGrowth = currentBranch.myGrowth;
		
	if (currentBranch.myLevel < myTreeType->GetLeafLevel())
	{
		if (currentBranch.myGrowth > 0.3f && currentBranch.myChildrenIndex.Size() == 0)
		{
			Branch branch = { { 0.f, 0.f }, { 0.f, 0.f }, 0.f, 0.f, currentBranch.myLevel + 1 };
			branch.myMirrored = currentBranch.myMirrored;
			branch.myGrowth = 0.f;

			// First branch
			float placement = myTreeType->GetRandomPlacementFromLevel(currentBranch.myLevel);
			float randRot = myTreeType->GetRandomAngleFromLevel(currentBranch.myLevel) * branch.myMirrored ? -1 : 1;
			branch.myRotation = currentBranch.myRotation + randRot;
			branch.myLocalPosition = {
				0,
				-static_cast<float>(myTreeType->GetSpriteAtLevel(currentBranch.myLevel).GetSize().myY * placement)
				};

			myChildren.push_back(branch);
			currentBranch.myChildrenIndex.Add(myChildren.size() - 1);

			// second branch
			if (currentBranch.myLevel == ROOT)
				branch.myMirrored = true;
			placement = myTreeType->GetRandomPlacementFromLevel(currentBranch.myLevel);
			branch.myLocalPosition = {
				0,
				-static_cast<float>(myTreeType->GetSpriteAtLevel(currentBranch.myLevel).GetSize().myY * placement)
				};
			randRot = myTreeType->GetRandomAngleFromLevel(currentBranch.myLevel) * branch.myMirrored ? -1 : 1;
			branch.myRotation = currentBranch.myRotation - randRot;
			myChildren.push_back(branch);
			currentBranch.myChildrenIndex.Add(myChildren.size() - 1);

			// one extra top branch for root level (trunk)
			//if (currentBranch.myLevel == ROOT)
			//{
			//	randRot = (rand() % 20) / 120.f - (rand() % 20) / 120.f;
			//	branch.myRotation = currentBranch.myRotation + randRot;
			//	branch.myGrowth = 0.1f;
			//	myChildren.push_back(branch);
			//	currentBranch.myChildrenIndex.Add(myChildren.size() - 1);
			//}
		}
	}

	Vector2f rotatedLocalPosition(
		cos(aParentRotation) * currentBranch.myLocalPosition.myX +
		-sin(aParentRotation) * currentBranch.myLocalPosition.myY,
		sin(aParentRotation) * currentBranch.myLocalPosition.myX +
		cos(aParentRotation) * currentBranch.myLocalPosition.myY );

	currentBranch.myWorldPosition = (aParentPosition + rotatedLocalPosition * aParentGrowth);

	for (int childIndex = 0; childIndex < currentBranch.myChildrenIndex.Size(); childIndex++)
	{
		Update(currentBranch.myChildrenIndex[childIndex], currentBranch.myWorldPosition, currentBranch.myRotation, currentBranch.myGrowth);
	}
}
