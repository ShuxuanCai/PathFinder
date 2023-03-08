#include "PickUps.h"
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

PickUps& PickUps::Get()
{
	static PickUps instance;
	return instance;
}

void PickUps::Load()
{
	for (int i = 0; i < 1;)
	{
		int endX = X::Random(0, TileMap::Get().GetColumns() - 1);
		int endY = X::Random(0, TileMap::Get().GetRows() - 1);
		if (TileMap::Get().IsBlocked(endX, endY) == true)
		{
			continue;
		}
		else
		{
			mPosition = GetPixelPosition(endX, endY);
			++i;
		}
	}

	mActive = true;
	mTextureId = X::LoadTexture("blueGem.png");
}

void PickUps::Unload()
{
	mTextureId = 0;
}

void PickUps::Render()
{
	if(mActive == true)
		X::DrawSprite(mTextureId, mPosition);
}

void PickUps::PickUp()
{
	mActive = false;
	numberOfPickUps++;
}