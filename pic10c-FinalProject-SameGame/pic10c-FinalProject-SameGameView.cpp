
// pic10c-FinalProject-SameGameView.cpp : implementation of the Cpic10cFinalProjectSameGameView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "pic10c-FinalProject-SameGame.h"
#endif

#include "pic10c-FinalProject-SameGameDoc.h"
#include "pic10c-FinalProject-SameGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpic10cFinalProjectSameGameView

IMPLEMENT_DYNCREATE(Cpic10cFinalProjectSameGameView, CView)

BEGIN_MESSAGE_MAP(Cpic10cFinalProjectSameGameView, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_LEVEL_3COLORS, &Cpic10cFinalProjectSameGameView::OnLevel3colors)
    ON_COMMAND(ID_LEVEL_4COLORS, &Cpic10cFinalProjectSameGameView::OnLevel4colors)
    ON_COMMAND(ID_LEVEL_5COLORS, &Cpic10cFinalProjectSameGameView::OnLevel5colors)
    ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS, &Cpic10cFinalProjectSameGameView::OnUpdateLevel3colors)
    ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS, &Cpic10cFinalProjectSameGameView::OnUpdateLevel4colors)
    ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS, &Cpic10cFinalProjectSameGameView::OnUpdateLevel5colors)
END_MESSAGE_MAP()

// Cpic10cFinalProjectSameGameView construction/destruction

Cpic10cFinalProjectSameGameView::Cpic10cFinalProjectSameGameView()
{
	// TODO: add construction code here

}

Cpic10cFinalProjectSameGameView::~Cpic10cFinalProjectSameGameView()
{
}

BOOL Cpic10cFinalProjectSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cpic10cFinalProjectSameGameView drawing

void Cpic10cFinalProjectSameGameView::OnDraw(CDC* pDC)
{
	Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
    int nDCSave = pDC->SaveDC(); //  Save the current state of the device context

    //  Get the client rectangle
    CRect rcClient;
    GetClientRect(&rcClient);

    COLORREF clr = pDoc->GetBoardSpace(-1, -1);     //  Get the background color of the board
    pDC->FillSolidRect(&rcClient, clr);     //	Draw the background first

    //  Create the brush for drawing
    CBrush br;
    br.CreateStockObject(HOLLOW_BRUSH);
    CBrush* pbrOld = pDC->SelectObject(&br);

    //	Draw the squares
    for (int row = 0; row < pDoc->GetRows(); row++)
    {
        for (int col = 0; col < pDoc->GetColumns(); col++)
        {
            clr = pDoc->GetBoardSpace(row, col);             //  Get the color for this board space

            //  Calculate the size and position of this space
            CRect rcBlock;
            rcBlock.top = row * pDoc->GetHeight();
            rcBlock.left = col * pDoc->GetWidth();
            rcBlock.right = rcBlock.left + pDoc->GetWidth();
            rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

            pDC->FillSolidRect(&rcBlock, clr);             //  Fill in the block with the correct color
            pDC->Rectangle(&rcBlock);             //  Draw the block outline
        }
    }
    //  Restore the device context settings
    pDC->RestoreDC(nDCSave);
    br.DeleteObject();
}



// Cpic10cFinalProjectSameGameView diagnostics

#ifdef _DEBUG
void Cpic10cFinalProjectSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void Cpic10cFinalProjectSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cpic10cFinalProjectSameGameDoc* Cpic10cFinalProjectSameGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cpic10cFinalProjectSameGameDoc)));
	return (Cpic10cFinalProjectSameGameDoc*)m_pDocument;
}
#endif //_DEBUG

void Cpic10cFinalProjectSameGameView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    //  Resize the window
    ResizeWindow();

}


void Cpic10cFinalProjectSameGameView::ResizeWindow()
{
    //  First get a pointer to the document
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    //  Get the size of the client area and the window
    CRect rcClient, rcWindow;
    GetClientRect(&rcClient);
    GetParentFrame()->GetWindowRect(&rcWindow);

    //  Calculate the difference
    int nWidthDiff = rcWindow.Width() - rcClient.Width();
    int nHeightDiff = rcWindow.Height() - rcClient.Height();

    //  Change the window size based on the size of the game board
    rcWindow.right = rcWindow.left +
        pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
    rcWindow.bottom = rcWindow.top +
        pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
    //  The MoveWindow function resizes the frame window
    GetParentFrame()->MoveWindow(&rcWindow);
}

// Cpic10cFinalProjectSameGameView message handlers
void Cpic10cFinalProjectSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
    //  First get a pointer to the document
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    //  Get the row and column of the block that was clicked on
    int row = point.y / pDoc->GetHeight();
    int col = point.x / pDoc->GetWidth();

    int count = pDoc->DeleteBlocks(row, col);     //  Delete the blocks from the document
    //  Check if there were any blocks deleted
    if (count > 0)
    {
        //  Force the view to redraw
        Invalidate();   //Signal to the view that the whole client area needs to be redrawn
        UpdateWindow(); //Redraw

        score += (count - 1) * (count - 1);
        //  Check if the game is over
        if (pDoc->IsGameOver())
        {
            //  Get the count remaining
            int remaining = pDoc->GetRemainingCount();
            CString message;
            if (remaining == 0) {
		if (score > 6000) {
	            message.Format(_T("You win!\nYour score: %d\nYou got more than 6000! Good job!!"), score);
	            score = 0;
		}
		else {
		    message.Format(_T("You win!\nYour score: %d"), score);
		    score = 0;
		}
            }
            else {
		if (score > 6000) {
		    message.Format(_T("No more moves left\nBlocks remaining: %d\nYour score: %d\nYou got more than 6000! Good job!!"), remaining, score);
		    score = 0;
		}
		else {
		    message.Format(_T("No more moves left\nBlocks remaining: %d\nYour score: %d"), remaining, score);
		    score = 0;
		}
            }
		
            MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION); //  Display the results to the user
        }
    }
    //  Default OnLButtonDown
    CView::OnLButtonDown(nFlags, point);
}

void Cpic10cFinalProjectSameGameView::OnLevel3colors() {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); //Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pDoc->SetNumColors(3); // Set the number of colors

    // Redraw the game board
    Invalidate();
    UpdateWindow();
}

void Cpic10cFinalProjectSameGameView::OnLevel4colors() {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); //Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pDoc->SetNumColors(4); // Set the number of colors

    // Redraw the game board
    Invalidate();
    UpdateWindow();
}

void Cpic10cFinalProjectSameGameView::OnLevel5colors() {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); //Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pDoc->SetNumColors(5); // Set the number of colors

    // Redraw the game board
    Invalidate();
    UpdateWindow();
}

void Cpic10cFinalProjectSameGameView::OnUpdateLevel3colors(CCmdUI* pCmdUI) {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); // Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pCmdUI->SetCheck(pDoc->GetNumColors() == 3); // Check if it is the right level
}

void Cpic10cFinalProjectSameGameView::OnUpdateLevel4colors(CCmdUI* pCmdUI) {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); // Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pCmdUI->SetCheck(pDoc->GetNumColors() == 4); // Check if it is the right level
}

void Cpic10cFinalProjectSameGameView::OnUpdateLevel5colors(CCmdUI* pCmdUI) {
    Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument(); // Get a pointer to the document
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    pCmdUI->SetCheck(pDoc->GetNumColors() == 5); // Check if it is the right level
}
