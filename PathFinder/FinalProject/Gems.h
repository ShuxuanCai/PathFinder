#pragma once

#include "Gem.h"

class Gems
{
public:
	static Gems& Get();

public:
	void Load();

	X::Math::Vector2 FindNearestPickUpPos(X::Math::Vector2 pos);

	const std::vector<Gem> GetPositions() { return mGems; }

private:
	std::vector<Gem> mGems;
};