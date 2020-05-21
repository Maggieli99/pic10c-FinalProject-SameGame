
// pic10c-FinalProject-SameGame.h : main header file for the pic10c-FinalProject-SameGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cpic10cFinalProjectSameGameApp:
// See pic10c-FinalProject-SameGame.cpp for the implementation of this class
//

class Cpic10cFinalProjectSameGameApp : public CWinApp
{
public:
	Cpic10cFinalProjectSameGameApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cpic10cFinalProjectSameGameApp theApp;
