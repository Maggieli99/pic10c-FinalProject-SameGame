#pragma once
#include <wtypes.h>

class CSameGameBoard
{
public:
	CSameGameBoard(); //Default Constructor
	~CSameGameBoard(); //Destructor
	void SetupBoard(); //Funtion to randomly setup the board
	COLORREF GetBoardSpace(int row, int col); //Get the color at a particualr location

	// Accessor functions to get board size information
	int GetWidth() const { return m_nWidth; }
	int GetHeight() const { return m_nHeight; }
	int GetColumns() const { return m_nColumns; }
	int GetRows() const { return m_nRows; }

	void DeleteBoard(); //Function to delete the board and free memory
	bool IsGameOver() const; // Check if the game is over
	int GetRemainingCount() const { return m_nRemaining; } //Get the number of blocks remaining
	int DeleteBlocks(int row, int col); // Delete all adjacent blocks

	int GetNumColors() { return m_nColors; } 
	void SetNumColors(int nColors) { m_nColors = nColors; }

private:
	void CreateBoard(); // Function to create the board and allocate memory
	enum Direction { DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT }; // Direction enumertion for deleting blocks
	int DeleteNeighborBlocks(int row, int col, int color, Direction direction); // Recursive helper function for deleting blocks
	void CompactBoard(); // Function to compact the board after blocks are eliminated
	int** m_arrBoard; // 2D array pointer
	static COLORREF m_arrColors[6]; // List of colors, 0 is background and 1-5 are piece colors

	// Board size information
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	int m_nRemaining; // Number of blocks remaining
	int m_nColors; // Number of colors of blocks of the game
};