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
	
	void DeleteBoard(void); //Function to delete the board and free memory

private:
	void CreateBoard(); // Function to create the board and allocate memory
	int** m_arrBoard; // 2D array pointer
	COLORREF m_arrColors[4]; // List of colors, 0 is background and 1-3 are piece colors
	
	// Board size information
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};