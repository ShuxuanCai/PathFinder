#pragma once

namespace AI
{
	class GridBasedGraph
	{
	public:
		enum Direction
		{
			North,
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		struct Node
		{
			// Graph structure - set in Initialize
			std::array<Node*, 8> neighbors;
			int column = 0;
			int row = 0;

			// Search parameters
			Node* parent = nullptr;
			bool opened = false;
			bool closed = false;
			float g = 0.0f; // Accumulated distance
			float h = 0.0f;
		};

		void Initialize(int columns, int rows);
		void Initialize(int columns, int rows, bool isDiagonal);
		void ResetSearchParams(); // TODO - Loop through all nodes and reset the search parameters to their default

		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y) const; // TODO - This is needed for when graph is passed by const&, can just copy GetNode's body

		int GetColumns() const { return mColumns; }
		int GetRows() const { return mRows; }

	private:
		int GetIndex(int x, int y);

		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};
}