#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	// TODO
	// - save the columns and rows
	// - resize mNodes and add nodes and neighbors
	//
	//e.g.
	//  for(...)
	//     for(...)
	//         set node column/row and add 8 neighbors
	//         node, neighbors[East] = GetNode(x + 1, y);
	//         node, neighbors[SouthEast] = GetNode(x + 1, y + 1);

	mColumns = columns;
	mRows = rows;
	mNodes.clear();
	mNodes.resize(static_cast<size_t>(mColumns) * static_cast<size_t>(mRows));

	for (int y = 0; y < GetRows(); ++y)
	{
		for (int x = 0; x < GetColumns(); ++x)
		{
			Node* node = GetNode(x, y);

			node->column = x;
			node->row = y;

			node->neighbors[North] = GetNode(x, y - 1);
			node->neighbors[South] = GetNode(x, y + 1);
			node->neighbors[East] = GetNode(x + 1, y);
			node->neighbors[West] = GetNode(x - 1, y);
			node->neighbors[NorthEast] = GetNode(x + 1, y - 1);
			node->neighbors[NorthWest] = GetNode(x - 1, y - 1);
			node->neighbors[SouthEast] = GetNode(x + 1, y + 1);
			node->neighbors[SouthWest] = GetNode(x - 1, y + 1);
		}
	}
}

void GridBasedGraph::Initialize(int columns, int rows, bool isDiagonal)
{
	// TODO
	// - save the columns and rows
	// - resize mNodes and add nodes and neighbors
	//
	//e.g.
	//  for(...)
	//     for(...)
	//         set node column/row and add 8 neighbors
	//         node, neighbors[East] = GetNode(x + 1, y);
	//         node, neighbors[SouthEast] = GetNode(x + 1, y + 1);

	mColumns = columns;
	mRows = rows;
	mNodes.clear();
	mNodes.resize(static_cast<size_t>(mColumns) * static_cast<size_t>(mRows));

	if (isDiagonal == false)
	{
		for (int y = 0; y < GetRows(); ++y)
		{
			for (int x = 0; x < GetColumns(); ++x)
			{
				Node* node = GetNode(x, y);

				node->column = x;
				node->row = y;

				node->neighbors[North] = GetNode(x, y - 1);
				node->neighbors[South] = GetNode(x, y + 1);
				node->neighbors[East] = GetNode(x + 1, y);
				node->neighbors[West] = GetNode(x - 1, y);
			}
		}
	}
}

void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.opened = false;
		node.closed = false;
		node.g = 0.0f;
		node.h = 0.0f;
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	// TODO - Check bound, if good, return node, else return nullptr
	if (x < 0 || x >= GetColumns() || y < 0 || y >= GetRows())
	{
		return nullptr;
	}

	int index = GetIndex(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x >= GetColumns() || y < 0 || y >= GetRows())
	{
		return nullptr;
	}

	int index = x + (y * GetColumns());
	return &mNodes[index];
}

int GridBasedGraph::GetIndex(int x, int y)
{
	// TODO - x, y must be within (0, 0) and (columns, rows)
	return x + (y * GetColumns());
}