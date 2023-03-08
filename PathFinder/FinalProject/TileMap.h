#pragma once

#include <XEngine.h>

class TileMap
{
public:
	static TileMap& Get();

public:
	void LoadMap(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName);
	void Update(float deltaTime);
	void Render() const;

	bool IsBlocked(int column, int row) const;
	float GetTraversalCost(int fromX, int fromY, int endX, int endY);
	float GetTraversalCost(int column, int row);

	int GetColumns() const { return mColumns; }
	int GetRows() const { return mRows; }
	int GetTileWidth() const { return mTileWidth; }
	int GetTileHeight() const { return mTileHeight; }

	int GetIndex(int column, int row) const;
	std::vector<int> mMap;

private:
	void Load(const std::filesystem::path& fileName);
	void LoadTexture(const std::filesystem::path& fileName);

	std::vector<X::TextureId> mTextures;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileHeight = 0;

	const float tileSize = 32.0f;
};