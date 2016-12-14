
// simpleOpenIFCFile.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CsimpleOpenIFCFileApp:
// See simpleOpenIFCFile.cpp for the implementation of this class
//

class CsimpleOpenIFCFileApp : public CWinApp
{
public:
	CsimpleOpenIFCFileApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CsimpleOpenIFCFileApp theApp;