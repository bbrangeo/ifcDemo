
// chkDisk4Ifc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


// CchkDisk4IfcApp:
// See chkDisk4Ifc.cpp for the implementation of this class
//

class CchkDisk4IfcApp : public CWinApp
{
public:
	CchkDisk4IfcApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CchkDisk4IfcApp theApp;

#undef int 
