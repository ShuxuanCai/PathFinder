#include "Precompiled.h"
#include "AIWorld.h"

using namespace AI;

void AIWorld::RegisterEntity(Entity* entity)
{
	mEntities.push_back(entity);
}

void AIWorld::UnregisterEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}

Entity* AIWorld::GetEntityById(uint64_t entityId)
{
	auto CompareId = [entityId](Entity* entity)
	{
		return entity->id == entityId;
	};

	auto iter = std::find_if(mEntities.begin(), mEntities.end(), CompareId);
		
	if (iter != mEntities.end())
	{
		return *iter;
	}

	return nullptr;
}

void AIWorld::AddObstacle(const X::Math::Circle& obstacle)
{
	mObstacles.push_back(obstacle);
	X::DrawScreenCircle(obstacle, X::Colors::White);
}

void AIWorld::AddWall(const X::Math::LineSegment& wall)
{
	mWalls.push_back(wall);
}

void AIWorld::Clear()
{
	mObstacles.clear();
	mWalls.clear();
}

uint32_t AIWorld::GetNextId(uint32_t typeId)
{
	uint64_t id = typeId;
	id <<= 32;
	id |= mNextId++;
	return id;
}