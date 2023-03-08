#pragma once

#include "Entity.h"
#include "GridBasedGraph.h"

namespace AI
{
	class AIWorld
	{
	public:
		using Obstacles = std::vector<X::Math::Circle>;
		using Walls = std::vector<X::Math::LineSegment>;

		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		Entity* GetEntityById(uint64_t entityId);

		void AddObstacle(const X::Math::Circle& obstacle);
		void AddWall(const X::Math::LineSegment& wall);
		void Clear();

		uint32_t GetNextId(uint32_t typeId);

		const Obstacles& GetObstacles() const { return mObstacles; }
		const Walls& GetWalls() const { return mWalls; }

		const GridBasedGraph& GetGraph() const { return mGraph; }
		GridBasedGraph& GetGraph() { return mGraph; }

	private:
		GridBasedGraph mGraph;

		Entities mEntities;
		uint32_t mNextId = 0;

		Obstacles mObstacles;
		Walls mWalls;
	};
}