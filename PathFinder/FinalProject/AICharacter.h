#pragma once

#include <AI.h>
#include <XEngine.h>

class AICharacter
{
public:
	static AICharacter& Get();

public:
	using Path = std::list<AI::GridBasedGraph::Node*>;

	void Load();
	void Update(float deltaTime);
	void Render();

	void ChangeState(const std::string& stateName);

	X::Math::Vector2 GetPosition() { return mPosition; }
	void SetPosition(X::Math::Vector2 position) { mPosition = position; }

	X::TextureId GetTexture() { return mTextureId; }
	void SetTexture(X::TextureId texture) { mTextureId = texture; }

	bool GetLose() { return lose; }
	void SetLose(bool isLose) { lose = isLose; }

	/*Path GetPath() { return mPath; }
	void SetPath(Path path) { mPath = path; }*/

	Path mPath;

private:
	std::unique_ptr<AI::StateMachine<AICharacter>> mStateMachine;
	
	X::Math::Vector2 mPosition;
	X::TextureId mTextureId;
	bool lose = false;
};