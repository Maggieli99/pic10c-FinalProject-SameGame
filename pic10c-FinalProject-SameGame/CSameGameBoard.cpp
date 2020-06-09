#include "pch.h"
#include "framework.h" // Not sure
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard() :m_arrBoard(NULL), m_nColumns(15), m_nRows(15), m_nHeight(35), m_nWidth(35), m_nRemaining(0) { 
    m_arrColors[0] = RGB(0, 0, 0);
    m_arrColors[1] = RGB(255, 0, 0);
    m_arrColors[2] = RGB(255, 255, 64);
    m_arrColors[3] = RGB(0, 0, 255);
    SetupBoard(); // Create and setup the board
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
    m_nRemaining = m_nRows * m_nColumns; // Set the number of spaces remaining
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col) { 
    // Check the bounds of the array
    if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) { 
        return m_arrColors[0];
    }
    return m_arrColors[m_arrBoard[row][col]];
}

void CSameGameBoard::DeleteBoard() {
    // Delete a board if it's not NULL
    if (m_arrBoard != NULL) {
        for (int row = 0; row < m_nRows; row++) {
            if (m_arrBoard[row] != NULL) {
                delete[] m_arrBoard[row]; // Delete each row first 
                m_arrBoard[row] = NULL;
            }
        }
        delete[] m_arrBoard; // Finally delete the array of rows
        m_arrBoard = NULL;
    }
}

void CSameGameBoard::CreateBoard() {
    // Delete the board if it is not NULL
    if (m_arrBoard != NULL) {
        DeleteBoard();
    }
    m_arrBoard = new int* [m_nRows]; // Create the array of rows
    // Create each row
    for (int row = 0; row < m_nRows; row++) {
        m_arrBoard[row] = new int[m_nColumns];
        // Set each square to be empty
        for (int col = 0; col < m_nColumns; col++) {
            m_arrBoard[row][col] = 0; 
        }
    }

}

int CSameGameBoard::DeleteBlocks(int row, int col) {
    // validations
    if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
        return -1;
    }
    int nColor = m_arrBoard[row][col];
    if (nColor == 0) {
        return -1;
    }
    int nCount = -1;

    // Find adjacent sidess with the same color and call recursive function to eliminate the adjacent blocks with the same color
    if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) || (row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
        (col - 1 >= 0 && m_arrBoard[row + 1][col - 1] == nColor) || (col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor)) {
        m_arrBoard[row][col] = 0;
        nCount = 1;
        nCount += DeleteNeighborBlocks(row - 1, col, nColor, DIRECTION_DOWN);
        nCount += DeleteNeighborBlocks(row + 1, col, nColor, DIRECTION_UP);
        nCount += DeleteNeighborBlocks(row, col - 1, nColor, DIRECTION_RIGHT);
        nCount += DeleteNeighborBlocks(row, col + 1, nColor, DIRECTION_LEFT);
        CompactBoard();
        m_nRemaining -= nCount;
    }
    return nCount;
}

int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color, Direction direction) {
    // Validations
    if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
        return 0;
    }
    if (m_arrBoard[row][col] != color) {
        return 0;
    }
    int nCount = 1;
    m_arrBoard[row][col] = 0;

    // Do not check the block that we came from; make the algorithm more efficient
    if (direction != DIRECTION_UP) {
        nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
    }
    if (direction != DIRECTION_DOWN) {
        nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_UP);
    }
    if (direction != DIRECTION_LEFT) {
        nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_RIGHT);
    }
    if (direction != DIRECTION_RIGHT) {
        nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_LEFT);
    }
    return nCount;
}

void CSameGameBoard::CompactBoard(void) {
    // Move everything down
    for (int col = 0; col < m_nColumns; col++) {
        int nNextEmptyRow = m_nRows - 1;
        int nNextOccupiedRow = nNextEmptyRow;
        while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0) {
            while (nNextEmptyRow >= 0 && m_arrBoard[nNextEmptyRow][col] != 0) {
                nNextEmptyRow--;
            }
            if (nNextEmptyRow >= 0) {
                nNextOccupiedRow = nNextEmptyRow - 1;
                while (nNextOccupiedRow >= 0 && m_arrBoard[nNextOccupiedRow][col] == 0) {
                    nNextOccupiedRow--;
                }
                if (nNextOccupiedRow >= 0) {
                    m_arrBoard[nNextEmptyRow][col] = m_arrBoard[nNextOccupiedRow][col];
                    m_arrBoard[nNextOccupiedRow][col] = 0;
                }
            }
        }
    }
    // Move everything to the left
    int nNextEmptyCol = 0;
    int nNextOccupiedCol = nNextEmptyCol;
    while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns) {
        while (nNextEmptyCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0) {
            nNextEmptyCol++;
        }
        if (nNextEmptyCol < m_nColumns) {
            nNextOccupiedCol = nNextEmptyCol + 1;
            while (nNextOccupiedCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0) {
                nNextOccupiedCol++;
            }
            if (nNextOccupiedCol < m_nColumns) {
                for (int row = 0; row < m_nRows; row++) {
                    m_arrBoard[row][nNextEmptyCol] = m_arrBoard[row][nNextOccupiedCol];
                    m_arrBoard[row][nNextOccupiedCol] = 0;
                }
            }
        }
    }
}

bool CSameGameBoard::IsGameOver() const {
    for (int col = 0; col < m_nColumns; col++) {
        for (int row = m_nRows - 1; row >= 0; row--) {
            int nColor = m_arrBoard[row][col];
            if (nColor == 0) {
                break;
            }
            else {
                if (row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) {
                    return false;
                }
                else if (col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor) {
                    return false;
                }
            }
        }
    }
    return true;
}