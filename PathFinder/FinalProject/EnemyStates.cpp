#include "EnemyStates.h"
#include "TileMap.h"
#include "AICharacter.h"

namespace
{
	bool IsBlocked(int column, int row)
	{
		return TileMap::Get().IsBlocked(column, row);
	}

	float GetCost(int fromX, int fromY, int toX, int toY)
	{
		const bool isDiagonal = (fromX != toX) && (fromY != toY);
		const float scale = isDiagonal ? 1.414f : 1.0f;
		return TileMap::Get().GetTraversalCost(toX, toY) * scale;
	}

	float GetHeuristic(int fromX, int fromY, int toX, int toY)
	{
		X::Math::Vector2 fromPos(fromX, fromY);
		X::Math::Vector2 toPos(toX, toY);
		return X::Math::Distance(fromPos, toPos);
	}

	X::Math::Vector2 GetPixelPosition(int column, int row)
	{
		return {
			(column + 0.5f) * TileMap::Get().GetTileWidth(),
			(row + 0.5f) * TileMap::Get().GetTileHeight()
		};
	}

	X::Math::Vector2 GetPosition(AI::GridBasedGraph::Node* node)
	{
		return GetPixelPosition(node->column, node->row);
	}
}

void WaitState::Enter(Enemy& enemy)
{

}

void WaitState::Update(Enemy& enemy, float deltaTime)
{
	time -= deltaTime;
	if (time < 0.0f)
	{
		enemy.ChangeState("Chase");
	}
}

void WaitState::Exit(Enemy& enemy)
{

}

void ChaseState::Enter(Enemy& enemy)
{

}

void ChaseState::Update(Enemy& enemy, float deltaTime)
{
	graph.Initialize(TileMap::Get().GetColumns(), TileMap::Get().GetRows(), false);
	path.clear();
	closedList.clear();

	int startX = enemy.GetPosition().x / TileMap::Get().GetTileWidth();
	int startY = enemy.GetPosition().y / TileMap::Get().GetTileHeight();
	int endX = AICharacter::Get().GetPosition().x / TileMap::Get().GetTileWidth();
	int endY = AICharacter::Get().GetPosition().y / TileMap::Get().GetTileHeight();

	if (aStar.Run(graph, startX, startY, endX, endY, IsBlocked, GetCost, GetHeuristic))
	{
		closedList = aStar.GetClosedList();
	}

	auto node = graph.GetNode(endX, endY);
	while (node != nullptr)
	{
		path.push_back(node);
		node = node->parent;
	}

	std::reverse(path.begin(), path.end());
	enemy.mPath = path;

	for (auto it = path.begin(); it != path.end(); ++it)
	{
		auto node = *it;
		auto nodeParent = node->parent;
		if (nodeParent != nullptr)
		{
			X::Math::Vector2 position = GetPixelPosition(node->column, node->row);
			X::Math::Vector2 parentPosition = GetPixelPosition(nodeParent->column, nodeParent->row);
			X::DrawScreenLine(position, parentPosition, X::Colors::Red);
		}
	}

	time1 -= deltaTime;
	if (time1 <= 0)
	{
		time1 = time2;
		auto startNode = enemy.mPath.front();
		enemy.mPath.pop_front();
		if (!enemy.mPath.empty())
		{
			auto nextNode = enemy.mPath.front();
			if ((nextNode->row == startNode->row) && (nextNode->column == startNode->column + 1))
			{
				enemy.SetIsFacingLeft(true);
			}
			if ((nextNode->row == startNode->row) && (nextNode->column + 1 == startNode->column))
			{
				enemy.SetIsFacingLeft(false);
			}
			enemy.SetPosition(GetPosition(enemy.mPath.front()));
		}
	}
}

void ChaseState::Exit(Enemy& enemy)
{

}