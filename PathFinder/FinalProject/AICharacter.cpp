#include "AICharacter.h"
#include "AICharacterStates.h"

AICharacter& AICharacter::Get()
{
	static AICharacter instance;
	return instance;
}

void AICharacter::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<AICharacter>>(*this);

	mStateMachine->AddState<MoveState>("Move");
	mStateMachine->AddState<PickUpGemsState>("PickUpGems");

	mTextureId = X::LoadTexture("characterBackward.png");
	mPosition = { 304.0f, 48.0f };
}

void AICharacter::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void AICharacter::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

void AICharacter::ChangeState(const std::string& stateName)
{
	mStateMachine->ChangeState(stateName);
}
