#pragma once

#include "AICharacter.h"
#include <AI.h>

class MoveState : public AI::State<AICharacter>
{
public:
	void Enter(AICharacter& aiCharacter) override;
	void Update(AICharacter& aiCharacter, float deltaTime) override;
	void Exit(AICharacter& aiCharacter) override;

private:
	float time1 = 0.0f;
	float time2 = 0.3f;

	AI::GridBasedGraph graph;
	AI::AStar aStar;
	std::list<AI::GridBasedGraph::Node*> path;
	std::list<AI::GridBasedGraph::Node*> closedList;
};

class PickUpGemsState : public AI::State<AICharacter>
{
public:
	void Enter(AICharacter& aiCharacter) override;
	void Update(AICharacter& aiCharacter, float deltaTime) override;
	void Exit(AICharacter& aiCharacter) override;
};