#pragma once

#include <AI.h>

class Enemy
{
public:
	using Path = std::list<AI::GridBasedGraph::Node*>;
	
public:
	static Enemy& Get();

	void Load();
	void Update(float deltaTime);
	void Render();

	void ChangeState(const std::string& stateName);

	X::Math::Vector2 GetPosition() { return mPosition; }
	void SetPosition(X::Math::Vector2 position) { mPosition = position; }

	void SetIsFacingLeft(bool facingLeft) { isFacingLeft = facingLeft; }

	/*Path GetPath() { return mPath; }
	void SetPath(Path path) { path = mPath; }*/

	Path mPath;

private:
	std::unique_ptr<AI::StateMachine<Enemy>> mStateMachine;
	
	X::Math::Vector2 mPosition;
	X::TextureId mTextureId;
	bool isFacingLeft = false;
};