#include "AICharacterStates.h"
#include "TileMap.h"
#include "PickUps.h"
#include "Enemy.h"
#include "EnemyManager.h"

namespace
{
	bool IsBlocked(int column, int row)
	{
		int enemyPosX = Enemy::Get().GetPosition().x / TileMap::Get().GetTileWidth();
		int enemyPosY = Enemy::Get().GetPosition().y / TileMap::Get().GetTileHeight();

		int aiPosX = AICharacter::Get().GetPosition().x / TileMap::Get().GetTileWidth();
		int aiPosY = AICharacter::Get().GetPosition().y / TileMap::Get().GetTileHeight();
		
		if ((enemyPosX == column && enemyPosY == row) || (aiPosX == column && aiPosY == row))
			return true;

		// Improvement: To support multiple enmeies, use a EnemeyManager
		/*for (auto& enemy : EnemyManager::Get().GetAllEneimes())
		{
			int enemyPosX = enemy.GetPosition().x / TileMap::Get().GetTileWidth();
			int enemyPosY = enemy.GetPosition().y / TileMap::Get().GetTileHeight();
			if (enemyPosX == column && enemyPosY == row)
				return true;
		}*/

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

void MoveState::Enter(AICharacter& aiCharacter)
{

}

void MoveState::Update(AICharacter& aiCharacter, float deltaTime)
{
	graph.Initialize(TileMap::Get().GetColumns(), TileMap::Get().GetRows(), false);
	path.clear();
	closedList.clear();

	int startX = aiCharacter.GetPosition().x / TileMap::Get().GetTileWidth();
	int startY = aiCharacter.GetPosition().y / TileMap::Get().GetTileHeight();
	int endX = PickUps::Get().GetPosition().x / TileMap::Get().GetTileWidth();
	int endY = PickUps::Get().GetPosition().y / TileMap::Get().GetTileHeight();

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
	aiCharacter.mPath = path;

	for (auto it = path.begin(); it != path.end(); ++it)
	{
		auto node = *it;
		auto nodeParent = node->parent;
		if (nodeParent != nullptr)
		{
			X::Math::Vector2 position = GetPixelPosition(node->column, node->row);
			X::Math::Vector2 parentPosition = GetPixelPosition(nodeParent->column, nodeParent->row);
			X::DrawScreenLine(position, parentPosition, X::Colors::Black);
		}
	}

	time1 -= deltaTime;
	if (time1 <= 0)
	{
		time1 = time2;
		auto startNode = aiCharacter.mPath.front();
		aiCharacter.mPath.pop_front();
		if (!aiCharacter.mPath.empty())
		{
			auto nextNode = aiCharacter.mPath.front();
			if ((nextNode->row == startNode->row + 1) && (nextNode->column == startNode->column))
			{
				aiCharacter.SetTexture(X::LoadTexture("characterBackWard.png"));
			}
			if ((nextNode->row + 1 == startNode->row) && (nextNode->column == startNode->column))
			{
				aiCharacter.SetTexture(X::LoadTexture("characterForward.png"));
			}
			if ((nextNode->row == startNode->row) && (nextNode->column == startNode->column + 1))
			{
				aiCharacter.SetTexture(X::LoadTexture("characterRight.png"));
			}
			if ((nextNode->row == startNode->row) && (nextNode->column + 1 == startNode->column))
			{
				aiCharacter.SetTexture(X::LoadTexture("characterLeft.png"));
			}
			aiCharacter.SetPosition(GetPosition(aiCharacter.mPath.front()));

			if(X::Math::Distance(aiCharacter.GetPosition(), Enemy::Get().GetPosition()) <= 32.0f)
			{
				aiCharacter.SetLose(true);
			}

			// Improvement: To support multiple enmeies, use a EnemeyManager
			/*for (auto& enemy : EnemyManager::Get().GetAllEneimes())
			{
				if (X::Math::Distance(aiCharacter.GetPosition(), enemy.GetPosition()) <= 32.0f)
				{
					aiCharacter.SetLose(true);
				}
			}*/
		}
		else
		{
			aiCharacter.ChangeState("PickUpGems");
		}
	}
}

void MoveState::Exit(AICharacter& aiCharacter)
{

}

void PickUpGemsState::Enter(AICharacter& aiCharacter)
{

}

void PickUpGemsState::Update(AICharacter& aiCharacter, float deltaTime)
{
	PickUps::Get().PickUp();
	
	PickUps::Get().Load();
	PickUps::Get().Render();

	aiCharacter.ChangeState("Move");
}

void PickUpGemsState::Exit(AICharacter& aiCharacter)
{

}