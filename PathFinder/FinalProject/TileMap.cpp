#include "TileMap.h"
#include "Enemy.h"

TileMap& TileMap::Get()
{
	static TileMap instance;
	return instance;
}

void TileMap::LoadMap(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName)
{
	Load(mapName);
	LoadTexture(tilesetName);
}

void TileMap::Update(float deltaTime)
{
	
}

void TileMap::Render() const
{
	for (int y = 0; y < GetRows(); ++y)
	{
		for (int x = 0; x < GetColumns(); ++x)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];

			const X::TextureId textureId = mTextures.at(tileIndex);
			const X::Math::Vector2 position = { x * tileSize, y * tileSize };

			X::DrawSprite(textureId, position, X::Pivot::TopLeft);
		}
	}
}

bool TileMap::IsBlocked(int column, int row) const
{
	const int index = GetIndex(column, row);
	const int tileType = mMap[index];

	if (tileType == 0)
		return false;
	return true;
}

float TileMap::GetTraversalCost(int fromX, int fromY, int endX, int endY)
{
	const int index = GetIndex(endX, endY);
	const int tileType = mMap[index];

	if (tileType == 0)
		return 1.0f;
	return 5.0f;
}

float TileMap::GetTraversalCost(int column, int row)
{
	const int index = GetIndex(column, row);
	const int tileType = mMap[index];

	if (tileType == 0)
		return 1.0f;
	return 5.0f;
}

void TileMap::Load(const std::filesystem::path& fileName)
{
	if (mMap.size() != 0)
	{
		mMap.clear();
	}

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);

	mMap = std::vector<int>(static_cast<int>(GetColumns()) * static_cast<int>(GetRows()));

	for (int y = 0; y < GetRows(); ++y)
	{
		for (int x = 0; x < GetColumns(); ++x)
		{
			const int index = GetIndex(x, y);
			mMap[index] = fgetc(file) - '0';
		}

		fgetc(file);
	}

	fclose(file);
}

void TileMap::LoadTexture(const std::filesystem::path& fileName)
{
	mTextures.clear();

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	int count = 0;
	fscanf_s(file, "Tiles: %d\n", &count);

	for (int i = 0; i < count; ++i)
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

		mTextures.push_back(X::LoadTexture(buffer));
	}

	fclose(file);

	mTileWidth = X::GetSpriteWidth(mTextures.front());
	mTileHeight = X::GetSpriteHeight(mTextures.front());
}

int TileMap::GetIndex(int column, int row) const
{
	return column + (row * GetColumns());
}