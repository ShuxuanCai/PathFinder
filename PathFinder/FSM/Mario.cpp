#pragma once

#include "Mario.h"
#include "MarioStates.h"

void Mario::Initialize()
{
	// Create a state machine that controls this mario
	mStateMachine = std::make_unique<AI::StateMachine<Mario>>(*this);

	// Add states
	mStateMachine->AddState<IdleState>("Idle");
	mStateMachine->AddState<MoveState>("Move");
	mStateMachine->AddState<EatState>("Eat");
	ChangeState("Move");

	mPosition = { 100.0f, 100.0f };
}

void Mario::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Mario::Render()
{
	X::Flip flipType;

	if (isFacingLeft)
	{
		flipType = X::Flip::Horizontal;
	}
	else
	{
		flipType = X::Flip::None;
	}

	X::DrawSprite(mTextureId, GetPosition(), X::Pivot::Bottom, flipType);
	X::DrawScreenText(mStateMachine->GetStateName(), GetPosition().x + 10.0f, GetPosition().y - 20.0f, 12.0f, X::Colors::White);
}

void Mario::ChangeState(const std::string& stateName)
{
	mStateMachine->ChangeState(stateName);
}
