#include "Gems.h"
#include "TileMap.h"

namespace
{
	X::Math::Vector2 GetPixelPosition(int column, int row)
	{
		return {
			(column + 0.5f) * TileMap::Get().GetTileWidth(),
			(row + 0.5f) * TileMap::Get().GetTileHeight()
		};
	}
}

Gems& Gems::Get()
{
	static Gems instance;
	return instance;
}

void Gems::Load()
{
	for (int i = 0; i < 2; ++i)
	{
		Gem::Get().Load();
		Gem g;
		mGems.push_back(g);
	}
}

X::Math::Vector2 Gems::FindNearestPickUpPos(X::Math::Vector2 pos)
{
	float distance = FLT_MAX;
	X::Math::Vector2 nearest;
	for (size_t i = 0; i < mGems.size(); i++)
	{
		if (X::Math::Distance(pos, mGems[i].GetPosition() * TileMap::Get().GetTileWidth()) < distance)
		{
			distance = X::Math::Distance(pos, mGems[i].GetPosition() * TileMap::Get().GetTileWidth());
			nearest = mGems[i].GetPosition();
		}
	}
	return nearest;
}