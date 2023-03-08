#pragma once

#include "Mario.h"
#include <AI.h>

class IdleState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};

class MoveState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};

class EatState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};