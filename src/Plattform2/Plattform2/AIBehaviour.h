#pragma once

class PhysicBody;

class AIBehaviour
{
public:
	~AIBehaviour() = default;
	void Update(PhysicBody& aPhysicBody);

private:
	void TurnAtCliff(PhysicBody& aPhysicBody);
	void TurnAtWall(PhysicBody& aPhysicBody);
	void GoForward(PhysicBody& aPhysicBody);
};

