#pragma once

#include <AI.h>
#include <XEngine.h>

class Mario
{
public:
	void Initialize();

	void Update(float deltaTime);
	void Render();

	void ChangeState(const std::string& stateName);

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }

	void SetMushroom(int index) { mCurrentMushroom = index; }
	int GetMushroom() const { return mCurrentMushroom; }

	X::TextureId mTextureId;
	float mSpeed = 0.0f;
	bool isFacingLeft = false;
	bool isGameOver = false;

private:
	std::unique_ptr<AI::StateMachine<Mario>> mStateMachine;
	X::Math::Vector2 mPosition;
	int mCurrentMushroom = 0;
};