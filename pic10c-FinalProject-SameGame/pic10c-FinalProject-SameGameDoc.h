
// pic10c-FinalProject-SameGameDoc.h : interface of the Cpic10cFinalProjectSameGameDoc class
//


#pragma once
#include "CSameGameBoard.h"


class Cpic10cFinalProjectSameGameDoc : public CDocument
{
protected: // create from serialization only
	Cpic10cFinalProjectSameGameDoc() noexcept;
	virtual ~Cpic10cFinalProjectSameGameDoc();
	DECLARE_DYNCREATE(Cpic10cFinalProjectSameGameDoc)

// Attributes
public:

// Operations
public:
	// Functions for accessing the game board
	COLORREF GetBoardSpace(int row, int col) {
		return m_board.GetBoardSpace(row, col);
	}
	void SetUpBoard() { m_board.SetupBoard(); }
	int GetWidth() { return m_board.GetWidth(); }
	int GetHeight() { return m_board.GetHeight(); }
	int GetColumns() { return m_board.GetColumns(); }
	int GetRows() { return m_board.GetRows(); }
	void DeleteBoard() { m_board.DeleteBoard(); }


// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cpic10cFinalProjectSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSameGameBoard m_board; // Create the game board object

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
