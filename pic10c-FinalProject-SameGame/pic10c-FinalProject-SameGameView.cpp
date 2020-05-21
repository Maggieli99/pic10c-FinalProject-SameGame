
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
END_MESSAGE_MAP()

// Cpic10cFinalProjectSameGameView construction/destruction

Cpic10cFinalProjectSameGameView::Cpic10cFinalProjectSameGameView() noexcept
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

void Cpic10cFinalProjectSameGameView::OnDraw(CDC* /*pDC*/)
{
	Cpic10cFinalProjectSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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


// Cpic10cFinalProjectSameGameView message handlers
