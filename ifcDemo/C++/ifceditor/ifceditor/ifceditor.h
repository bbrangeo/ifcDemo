
// ifceditor.h : main header file for the ifceditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CifceditorApp:
// See ifceditor.cpp for the implementation of this class
//

class CifceditorApp : public CWinApp
{
public:
	CifceditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL InitApplication();
};

extern CifceditorApp theApp;
