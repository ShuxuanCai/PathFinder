#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	class Dijkstras
	{
	public:
		// Define IsBlocked function, that takes two integers and return a boolean
		using IsBlocked = std::function<bool(int, int)>;
		using GetCost = std::function<float(int, int, int, int)>;

		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, IsBlocked isBlocked, GetCost getCost);

		const std::list<GridBasedGraph::Node*>& GetClosedList() const { return mClosedList; }

	private:
		std::list<GridBasedGraph::Node*> mOpenList;
		std::list<GridBasedGraph::Node*> mClosedList;
	};
}