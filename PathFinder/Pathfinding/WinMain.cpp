#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "TileMap.h"

//AI::GridBasedGraph myGraph;
AI::AIWorld aiWorld;
TileMap myTileMap;

float tileSize = 32.0f;

int startX = 5;
int startY = 5;
int endX = 0;
int endY = 0;

bool drawGraph = true;

std::list<AI::GridBasedGraph::Node*> path;
std::list<AI::GridBasedGraph::Node*> closedList;

bool IsBlocked(int column, int row)
{
	return myTileMap.IsBlocked(column, row);
}

float GetCost(int fromX, int fromY, int toX, int toY)
{
	const bool isDiagonal = (fromX != toX) && (fromY != toY);
	const float scale = isDiagonal ? 1.414f : 1.0f;
	return myTileMap.GetTraversalCost(toX, toY) * scale;
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
		(column + 0.5f) * myTileMap.GetTileWidth(),
		(row + 0.5f) * myTileMap.GetTileHeight()
	};
}

void ExtractPath()
{
	// Start from the end node
	auto node = aiWorld.GetGraph().GetNode(endX, endY);

	// Jump backwards until we hit a node with no parent
	path.clear();
	while (node != nullptr)
	{
		path.push_front(node);
		node = node->parent;
	}
}

void DrawGraph(AI::GridBasedGraph& myGraph)
{
	// X::DrawScreenLine({100,100},{500,200},X::Colors::Black);
	
	// TODO
	// - Get each node of the graph and draw lines from the node to each neighbor

	for (int y = 0; y < myGraph.GetRows(); ++y)
	{
		for (int x = 0; x < myGraph.GetColumns(); ++x)
		{
			auto node = myGraph.GetNode(x, y);
			for(auto neighbor : node->neighbors)
			{
				if (neighbor != nullptr)
				{
					X::Math::Vector2 ndoeCenter1(node->column * tileSize + 0.5f * tileSize, node->row * tileSize + 0.5f * tileSize);
					X::Math::Vector2 ndoeCenter2(neighbor->column * tileSize + 0.5f * tileSize, neighbor->row * tileSize + 0.5f * tileSize);
					X::DrawScreenLine(ndoeCenter1, ndoeCenter2, X::Colors::Red);
				}
			}
		}
	}
}

void DrawClosedList()
{
	// TODO
	// - To draw the closed list, for each node in the list, draw a line between the node and it's parent

	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		auto node = *it;
		auto nodeParent = node->parent;
		if (nodeParent != nullptr)
		{
			X::Math::Vector2 position = GetPixelPosition(node->column, node->row);
			X::Math::Vector2 parentPosition = GetPixelPosition(nodeParent->column, nodeParent->row);
			X::DrawScreenLine(position, parentPosition, X::Colors::White);
		}
	}
}

void DrawPath()
{
	// TODO
	// - To draw the path, for each node in the list, draw a line between the node and the parent

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
}

void DrawStartEnd()
{
	X::DrawScreenCircle(GetPixelPosition(startX, startY), 10.0f, X::Colors::Magenta);
	X::DrawScreenCircle(GetPixelPosition(endX, endY), 10.0f, X::Colors::Red);
}

void DrawUI()
{
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderInt("Start X", &startX, 0, myTileMap.GetColumns() - 1);
	ImGui::SliderInt("Start Y", &startY, 0, myTileMap.GetRows() - 1);
	ImGui::SliderInt("End X", &endX, 0, myTileMap.GetColumns() - 1);
	ImGui::SliderInt("End Y", &endY, 0, myTileMap.GetRows() - 1);
	
	if (ImGui::Button("Run BFS"))
	{
		AI::BFS bfs;
		if (bfs.Run(aiWorld.GetGraph(), startX, startY, endX, endY, IsBlocked))
		{
			closedList = bfs.GetClosedList();
			ExtractPath();
		}
	}

	if (ImGui::Button("Run DFS"))
	{
		AI::DFS dfs;
		if (dfs.Run(aiWorld.GetGraph(), startX, startY, endX, endY, IsBlocked))
		{
			closedList = dfs.GetClosedList();
			ExtractPath();
		}
	}

	if (ImGui::Button("Run Dijkstras"))
	{
		AI::Dijkstras dijkstras;
		if (dijkstras.Run(aiWorld.GetGraph(), startX, startY, endX, endY, IsBlocked, GetCost))
		{
			closedList = dijkstras.GetClosedList();
			ExtractPath();
		}
	}

	if (ImGui::Button("Run AStar"))
	{
		AI::AStar aStar;
		if (aStar.Run(aiWorld.GetGraph(), startX, startY, endX, endY, IsBlocked, GetCost, GetHeuristic))
		{
			closedList = aStar.GetClosedList();
			ExtractPath();
		}
	}

	ImGui::End();
}

void GameInit()
{
	myTileMap.LoadMap("level.txt", "map.txt");

	// Initialize graph to matching size as the map
	aiWorld.GetGraph().Initialize(myTileMap.GetColumns(), myTileMap.GetRows());
}

bool GameLoop(float deltaTime)
{
	myTileMap.Render();
	myTileMap.Update(deltaTime);
	/*if(drawGraph)
		DrawGraph(myGraph);*/
	DrawUI();
	DrawStartEnd();
	DrawClosedList();
	DrawPath();
	
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}