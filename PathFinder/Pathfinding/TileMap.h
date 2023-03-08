#pragma once

#include <XEngine.h>

class TileMap
{
public:
	void LoadMap(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName);
	void Update(float deltaTime);
	void Render() const;

	bool IsBlocked(int column, int row) const;
	float GetTraversalCost(int column, int row) const;

	int GetColumns() const { return mColumns; }
	int GetRows() const { return mRows; }
	int GetTileWidth() const { return mTileWidth; }
	int GetTileHeight() const { return mTileHeight; }

private:
	void Load(const std::filesystem::path& fileName);
	void LoadTexture(const std::filesystem::path& fileName);
	int GetIndex(int column, int row) const;

	std::vector<int> mMap;
	std::vector<X::TextureId> mTextures;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileHeight = 0;

	const float tileSize = 32.0f;
	int selectedTileIndex = 0;
};

// This is how you use a 2D array, however, we want to be able to dynamically change size:
// int map[100][100];
// 
// 
// // Bad way
// int** map = new int*[100];
// for (...)
// 	map[i] = new int[100];
// 
// 
// // Easy/Good way
// int* map = new int[100 * 100];
// ????
// delete[] map;


// int** map = [*][*][*][*][*][*][*][*][*][*][*]
//              |  |  |  |  |  |  |  |  |  |  | 
//              v  v  v  v  v  v  v  v  v  v  v 
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ] 0
//             [ ][ ][ ][ ][*][ ][ ][ ][ ][ ][ ] 1         <---- [y][x] == [1][4] == 4 + (1 * 10) = 14
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ] 2
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ] 3
//             [ ][ ][ ][ ][ ][ ][X][ ][ ][ ][ ] 4         <---- [y][x] == [4][6]
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ] ...
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
//              0  1  2  3  4  5  ...
//     

// int* map =  [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
//             [ ][ ][ ][ ][*][ ][ ][ ][ ][ ][ ]
//             [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
// index = x + (y * columns)

// In hardware:
// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]