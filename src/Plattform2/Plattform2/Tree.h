#pragma once
#include "GameObject.h"
#include <vector>
#include <VectorOnStack.h>

class TreeType;

class Tree : public GameObject
{
public:
							Tree();
	void					Update(const float aDeltaTime) override;
	void					Draw() override;
	void					SetTreeType(TreeType* aTreeType);
private:

	struct Branch
	{
		Vector2f					myWorldPosition;
		Vector2f					myLocalPosition;
		float						myRotation;
		float						myGrowth;
		int							myLevel;
		CU::VectorOnStack<int, 3>	myChildrenIndex;
		bool						myMirrored = false;
	};

	void					Grow(const int aBranchIndex, const float aGrowth);
	void					Update(const int aBranchIndex, const Vector2f& aParentPosition, const float aParentRotation, const float aParentGrowth);
	void					Draw(const int aBranchIndex, const float aParentRotation, const float aParentGrowth);
	std::vector<Branch>		myChildren;
	TreeType*				myTreeType;
};
