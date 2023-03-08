#include "TileMap.h"

void TileMap::LoadMap(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName)
{
	// Homework:
	// Add code here so we can read values from a txt file
	// to load the textures and map tiles.

	// fopen/fclose/fscanf - C way
	// fstream - C++ way

	Load(mapName);
	LoadTexture(tilesetName);
}

void TileMap::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ONE))
	{
		//Grass
		selectedTileIndex = 0;
	}

	else if (X::IsKeyPressed(X::Keys::TWO))
	{
		//Flower
		selectedTileIndex = 1;
	}

	else if (X::IsKeyPressed(X::Keys::THREE))
	{
		//Stone
		selectedTileIndex = 2;
	}

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const int mouseX = X::GetMouseScreenX();
		const int mouseY = X::GetMouseScreenY();

		const int columnSelected = mouseX / tileSize;
		const int rowSelected = mouseY / tileSize;

		if (columnSelected >= 0 && columnSelected < mColumns
			&& rowSelected >= 0 && rowSelected < mRows)
		{
			const int mapIndex = GetIndex(columnSelected, rowSelected);
			mMap[mapIndex] = selectedTileIndex;
		}
	}
}

void TileMap::Render() const
{
	// Homework:
	// Add code to draw the tile map.
	// for (y from 0 to mRows)
	//   for (x from 0 to mColumns)
	// 	   Compute pixel positions from the tile index
	//	   DrawSprite(textureId, {pixelX, pixelY}, X::Pivot::TopLeft)
	// 
	// 	Note that this will not work as we need pixel positions!
	//		DrawSprite(textureId, {x, y} ... )

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

	if (tileType == 0 || tileType == 1)
		return false;
	return true;
}

float TileMap::GetTraversalCost(int column, int row) const
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