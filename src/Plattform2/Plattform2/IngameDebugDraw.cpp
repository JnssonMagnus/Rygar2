#include "stdafx.h"
#include "IngameDebugDraw.h"
#include "CollisionBoxDrawerVisitor.h"
#include "megaton.h"
#include "PhysicManager.h"
#include "MapChunk.h"
#include "PlayerCamera.h"
#include "DebugDrawer.h"

IngameDebugDraw::IngameDebugDraw()
{
	myCollisionBoxDrawerVisitor = new CollisionBoxDrawerVisitor();
}

IngameDebugDraw::~IngameDebugDraw()
{
	SAFE_DELETE(myCollisionBoxDrawerVisitor);
}

void IngameDebugDraw::DebugDraw()
{
	DL_ASSERT(myPlayerCamera && "DebugDraw not initiated with player camera!");
	PhysicManager::GetInstance()->Visit(*myCollisionBoxDrawerVisitor);

	const int halfScreenWidth = static_cast<int>((SCREEN_WIDTH / 2.f) / myPlayerCamera->GetZoom() + 0.5f);
	const int halfScreenHeight = static_cast<int>((SCREEN_HEIGHT / 2.f) / myPlayerCamera->GetZoom() + 0.5f);
	auto mapChunks = Megaton::GetInstance().GetMapChunks(myPlayerCamera->GetPosition(), Vector2<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	for (auto mapChunk : mapChunks) {
		const Vector2f mapWidth(mapChunk->GetTileSize().x * mapChunk->GetMapWidth(), 0.f);
		const Vector2f mapHeight(0.f, mapChunk->GetTileSize().y * mapChunk->GetMapHeight());
		DebugDrawer::DrawLine(mapChunk->GetWorldPosition() , mapChunk->GetWorldPosition() + mapWidth);
		DebugDrawer::DrawLine(mapChunk->GetWorldPosition() + mapWidth, mapChunk->GetWorldPosition() + mapWidth + mapHeight);
		DebugDrawer::DrawLine(mapChunk->GetWorldPosition() + mapWidth + mapHeight, mapChunk->GetWorldPosition() + mapHeight);
		DebugDrawer::DrawLine(mapChunk->GetWorldPosition() + mapHeight, mapChunk->GetWorldPosition());
	}
}

void IngameDebugDraw::Init(PlayerCamera* aPlayerCamera)
{
	DL_ASSERT(aPlayerCamera && "Player camera is nullptr!");
	myPlayerCamera = aPlayerCamera;
}
