#pragma once

#include <AI.h>
#include <XEngine.h>

class Gem
{
public:
	static Gem& Get();

public:
	void Load();
	//void Render();

	const X::Math::Vector2 GetPosition() const { return mPosition; }

private:
	X::Math::Vector2 mPosition;
	//X::TextureId mTextureId;
};