#include "stdafx.h"
#include "grid.h"
#include "PhysicBody.h"

Grid::~Grid()
{
	myBodiesInGrid.Clear();
	myNodes.Clear();
	myGridSize = { -1, -1 };
	myNodeSize = { -1, -1 };
}

void Grid::Init(const Vector2<int>& aGridSize, const Vector2<int>& aNodeSize)
{
	myNodeSize = aNodeSize;
	myGridSize = aGridSize;
	myNodes.Resize(aGridSize.myX * aGridSize.myY);
}

void Grid::AddBody(PhysicBody* aPhysicBody)
{
	DL_ASSERT(myBodiesInGrid.Find(aPhysicBody) == -1 && "Body already added to grid!");
	myBodiesInGrid.Add(aPhysicBody);
}

void Grid::RemoveBody(PhysicBody* aPhysicBody)
{
	DL_ASSERT(myBodiesInGrid.Find(aPhysicBody) != -1 && "Body already removed from grid!");
	myBodiesInGrid.RemoveCyclic(aPhysicBody);
}

void Grid::Update()
{
	for (auto nodeIndex : myActiveNodes)
		myNodes[nodeIndex].Clear();

	myActiveNodes.clear();

	for (auto dweller : myBodiesInGrid)
	{
		const Vector2f topLeft = dweller->GetLeftTop();
		const Vector2f bottomRight = dweller->GetRightBottom();

		for (int y = topLeft.myY; y < bottomRight.myY; y += myNodeSize.myY)
		{
			for (int x = topLeft.myX; x < bottomRight.myX; x += myNodeSize.myX)
			{
				int nodeIndex = (x / myNodeSize.myX) + (y / myNodeSize.myY) * myGridSize.myX;
				if (nodeIndex >= 0 && nodeIndex < myNodes.Size())
				{
					myNodes[nodeIndex].Add(dweller);
					myActiveNodes.emplace(nodeIndex);
				}
			}
		}
	}
}

const CU::GrowingArray<CU::GrowingArray<PhysicBody*>> Grid::GetSpatialListsWithBodies() const
{
	CU::GrowingArray<CU::GrowingArray<PhysicBody*>> nodesWithBodies;

	for (auto nodeIndex : myActiveNodes)
	{
		nodesWithBodies.Add(myNodes[nodeIndex]);
	}
	return nodesWithBodies;
}
