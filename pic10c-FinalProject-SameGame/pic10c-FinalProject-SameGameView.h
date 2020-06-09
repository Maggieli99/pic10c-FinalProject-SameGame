
// pic10c-FinalProject-SameGameView.h : interface of the Cpic10cFinalProjectSameGameView class
//

#pragma once


class Cpic10cFinalProjectSameGameView : public CView
{
protected: // create from serialization only
	Cpic10cFinalProjectSameGameView();
	virtual ~Cpic10cFinalProjectSameGameView();
	DECLARE_DYNCREATE(Cpic10cFinalProjectSameGameView)

// Attributes
public:
	Cpic10cFinalProjectSameGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in pic10c-FinalProject-SameGameView.cpp
inline Cpic10cFinalProjectSameGameDoc* Cpic10cFinalProjectSameGameView::GetDocument() const
   { return reinterpret_cast<Cpic10cFinalProjectSameGameDoc*>(m_pDocument); }
#endif

