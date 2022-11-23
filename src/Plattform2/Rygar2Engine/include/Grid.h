#pragma once
#include <unordered_set>
class PhysicBody;


class GridNode
{

};

class Grid
{
public:
									Grid() = default;
									~Grid();
									Grid(const Grid&) = delete;
	Grid&							operator=(const Grid&) = delete;
	void							Init(const Vector2<int>& aGridSize, const Vector2<int>& aNodeSize);
	void							AddBody(PhysicBody* aPhysicBody);
	void							RemoveBody(PhysicBody* aPhysicBody);
	void							Update();
	const CU::GrowingArray<CU::GrowingArray<PhysicBody*>>
									GetSpatialListsWithBodies() const;

private:
	CU::GrowingArray<PhysicBody*>	myBodiesInGrid;

	CU::GrowingArray<CU::GrowingArray<PhysicBody*>> 
									myNodes;
	Vector2<int>					myNodeSize;
	Vector2<int>					myGridSize;
	std::unordered_set<int>			myActiveNodes;
};

