#include "Precompiled.h"
#include "Dijkstras.h"

using namespace AI;

namespace
{
	bool sortByG(const AI::GridBasedGraph::Node* node1, const AI::GridBasedGraph::Node* node2)
	{
		if (node1->g < node2->g)
			return true;
		return false;
	}
}

bool Dijkstras::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, IsBlocked isBlocked, GetCost getCost)
{
	// Reset everything
	graph.ResetSearchParams();
	mOpenList.clear();
	mClosedList.clear();

	// Add start node to open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;
	//	while end node not reached && open list isn’t empty:
	//		select node N from open list
	//		if node N is end
	//			found = true
	//		else expand node N:
	//			if expanded node isn’t in open or closed lists:
	//				add expanded node to open list, set parent to node N
	//		Add node N to closed list


	while (!found && !mOpenList.empty())
	{
		auto findNode = mOpenList.front();
		mOpenList.pop_front();
		auto endNode = graph.GetNode(endX, endY);
		if (findNode == endNode)
		{
			found = true;
		}

		else
		{
			for (auto neighbor : findNode->neighbors)
			{
				if (neighbor == nullptr || neighbor->opened || isBlocked(neighbor->column, neighbor->row))
				{
					continue;
				}

				if (!neighbor->opened)
				{
					mOpenList.push_back(neighbor);
					neighbor->opened = true;
					neighbor->parent = findNode;
					neighbor->g = findNode->g + getCost(findNode->column, findNode->row, neighbor->column, neighbor->row);
					// sort openList by g
					mOpenList.sort(sortByG);
				}
			}
		}

		mClosedList.push_back(findNode);
		findNode->closed = true;
	}

	return found;
}