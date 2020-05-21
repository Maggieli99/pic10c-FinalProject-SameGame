#include "pch.h"
#include "framework.h" // Not sure
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard() :m_arrBoard(NULL), m_nColumns(15), m_nRows(15), m_nHeight(35), m_nWidth(35) { 
    m_arrColors[0] = RGB(0, 0, 0);
    m_arrColors[1] = RGB(255, 0, 0);
    m_arrColors[2] = RGB(255, 255, 64);
    m_arrColors[3] = RGB(0, 0, 255);
}

CSameGameBoard::~CSameGameBoard() {
    DeleteBoard(); // Delete the board
}

void CSameGameBoard::SetupBoard() {
    //Create the board when starting running the game
    if (m_arrBoard == NULL) {
        CreateBoard();
    }

    // Set each square to a color randomly
    for (int row = 0; row < m_nRows; row++) {
        for (int col = 0; col < m_nColumns; col++) {
            m_arrBoard[row][col] = (rand() % 3) + 1; // I want a random game board every time I play it. I may want to improve this part later.
        }
    }
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col) { 
    // Check the bounds of the array
    if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) { 
        return m_arrColors[0];
    }
    return m_arrColors[m_arrBoard[row][col]];
}