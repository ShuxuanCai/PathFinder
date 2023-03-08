#pragma once

#include <XEngine.h>

class Mushroom
{
public:
	static Mushroom& Get();

public:
	void Load();
	void Unload();
	void Render();

	const X::Math::Vector2& GetPositions(int index) const { return mPosition[index]; }
	void MushroomEaten(int index) { isEaten[index] = false; }
	bool IsMushroomActive(int index) const { return isEaten[index]; }
	
	int mushroomCount = 5;

private:
	X::TextureId mTextureId;
	std::vector<X::Math::Vector2> mPosition;
	std::vector<bool> isEaten;
};