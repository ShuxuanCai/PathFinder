#include "MarioStates.h"
#include "Mushroom.h"

void IdleState::Enter(Mario& mario)
{
	mario.mSpeed = 0.0f;
	mario.mTextureId = X::LoadTexture("mario_idle_01.png");
}

void IdleState::Update(Mario& mario, float deltaTime)
{
	mario.SetPosition({640.0f, 360.0f});
}

void IdleState::Exit(Mario& mario)
{

}

void MoveState::Enter(Mario& mario)
{
	mario.mSpeed = 100.0f;
	mario.mTextureId = X::LoadTexture("mario_walk_02.png");
}

void MoveState::Update(Mario& mario, float deltaTime)
{
	auto marioPosition = mario.GetPosition();
	auto mushroomPosition = Mushroom::Get().GetPositions(mario.GetMushroom());

	if (X::Math::Distance(marioPosition, mushroomPosition) <= 5.0f)
		mario.ChangeState("Eat");

	else
	{
		auto unitDirection = X::Math::Normalize(mushroomPosition - marioPosition);

		if (unitDirection.x > 0)
			mario.isFacingLeft = false;

		else
			mario.isFacingLeft = true;

		auto marioNewPosition = unitDirection * mario.mSpeed * deltaTime;
		mario.SetPosition(mario.GetPosition() + marioNewPosition);
	}
}

void MoveState::Exit(Mario& mario)
{

}

void EatState::Enter(Mario& mario)
{
	
}

void EatState::Update(Mario& mario, float deltaTime)
{
	int index = mario.GetMushroom();
	int nextMushroom = index + 1;

	Mushroom::Get().MushroomEaten(index);
	mario.SetMushroom(nextMushroom);

	if (nextMushroom >= Mushroom::Get().mushroomCount)
	{
		mario.isGameOver = true;
	}

	if (!Mushroom::Get().IsMushroomActive(index))
	{
		mario.ChangeState("Move");
	}

	if (mario.isGameOver)
	{
		mario.ChangeState("Idle");
	}
}

void EatState::Exit(Mario& mario)
{

}