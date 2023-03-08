#include "Gem.h"
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

Gem& Gem::Get()
{
	static Gem instance;
	return instance;
}

void Gem::Load()
{
	/*int index = 0;
	while (index == 1)
	{
		int positionX = X::Random(0, TileMap::Get().GetColumns() - 1);
		int positionY = X::Random(0, TileMap::Get().GetRows() - 1);
		if (!TileMap::Get().IsBlocked(positionX, positionY))
		{
			mPosition = GetPixelPosition(positionX, positionY);
			index = 1;
		}
	}*/
	int index = 0;
	do
	{
		mPosition.x = X::Random(0, TileMap::Get().GetColumns() - 1);
		mPosition.y = X::Random(0, TileMap::Get().GetRows() - 1);
		index = mPosition.x + (mPosition.y * TileMap::Get().GetColumns());
	} while (TileMap::Get().GetMap()[index] != 0);

	TileMap::Get().SetMap(index, 3);

	//mTextureId = X::LoadTexture("blueGem.png");
}

//void Gem::Render()
//{
//	X::DrawSprite(mTextureId, mPosition);
//}