#include "Enemy.h"
#include "EnemyStates.h"

Enemy& Enemy::Get()
{
	static Enemy instance;
	return instance;
}

void Enemy::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Enemy>>(*this);

	mStateMachine->AddState<WaitState>("Wait");
	mStateMachine->AddState<ChaseState>("Chase");

	mTextureId = X::LoadTexture("enemy.png");
	mPosition = { 336.0f, 272.0f };
}

void Enemy::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Enemy::Render()
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

	for (int i = 0; i < 3; ++i)
	{
		X::DrawSprite(mTextureId, mPosition, X::Pivot::Center, flipType);
	}
}

void Enemy::ChangeState(const std::string& stateName)
{
	mStateMachine->ChangeState(stateName);
}