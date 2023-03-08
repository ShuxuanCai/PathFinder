#pragma once

#include "Enemy.h"
#include <AI.h>

class WaitState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;

private:
	float time = 3.0f;
};

class ChaseState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;

private:
	AI::GridBasedGraph graph;
	AI::AStar aStar;
	std::list<AI::GridBasedGraph::Node*> path;
	std::list<AI::GridBasedGraph::Node*> closedList;

	float time1 = 0.0f;
	float time2 = 0.5f;
};