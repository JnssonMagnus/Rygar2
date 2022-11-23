#pragma once

class CollisionBoxDrawerVisitor;
class PlayerCamera;

class IngameDebugDraw
{
public:
	IngameDebugDraw();
	~IngameDebugDraw();
	void DebugDraw();
	void Init(PlayerCamera* aPlayerCamera);


private:
	CollisionBoxDrawerVisitor* myCollisionBoxDrawerVisitor = nullptr;
	PlayerCamera* myPlayerCamera = nullptr;
};

