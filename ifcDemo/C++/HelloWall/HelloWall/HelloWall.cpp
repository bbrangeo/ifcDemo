////////////////////////////////////////////////////////////////////////
//	Author:		Peter Bonsma
//	Date:		20 February 2015
//	Project:	IFC Engine Series (example using DLL)
//
//	This code may be used and edited freely,
//	also for commercial projects in open and closed source software
//
//	In case of use of the DLL:
//	be aware of license fee for use of this DLL when used commercially
//	more info for commercial use:	contact@rdf.bg
//
//	more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "HelloWall.h"
#include "HelloWallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef UNICODE
wchar_t	* ifcFileName, * ifcSchemaNameIFC2x3, * ifcSchemaNameIFC4;
#else
char	* ifcFileName, * ifcSchemaNameIFC2x3, * ifcSchemaNameIFC4;
#endif


// CHelloWallApp

BEGIN_MESSAGE_MAP(CHelloWallApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHelloWallApp construction

CHelloWallApp::CHelloWallApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CHelloWallApp object

CHelloWallApp theApp;


// CHelloWallApp initialization

BOOL CHelloWallApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CHelloWallDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CHelloWallApp::InitApplication()
{
#ifdef UNICODE
	size_t	i = wcslen(this->m_pszHelpFilePath) - wcslen(this->m_pszExeName) - 4;
#else
	size_t	i = strlen(this->m_pszHelpFilePath) - strlen(this->m_pszExeName) - 4;
#endif

	ASSERT(ifcFileName == 0  &&  i > 0);
	ASSERT(ifcSchemaNameIFC2x3 == 0  &&  i > 0);
	ASSERT(ifcSchemaNameIFC4 == 0  &&  i > 0);

#ifdef UNICODE
	ifcFileName = new wchar_t[i + wcslen(L"example.ifc")+1];
	memcpy(&ifcFileName[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcFileName[i], L"example.ifc", (wcslen(L"example.ifc") + 1) * sizeof(wchar_t));
#else
	ifcFileName = new char[i + strlen("example.ifc")+1];
	memcpy(&ifcFileName[0], this->m_pszHelpFilePath, i * sizeof(char));
	memcpy(&ifcFileName[i], "example.ifc", (strlen("example.ifc") + 1) * sizeof(char));
#endif

#ifdef UNICODE
	ifcSchemaNameIFC2x3 = new wchar_t[i + wcslen(L"IFC2X3_TC1.exp")+1];
	memcpy(&ifcSchemaNameIFC2x3[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcSchemaNameIFC2x3[i], L"IFC2X3_TC1.exp", (wcslen(L"IFC2X3_TC1.exp") + 1) * sizeof(wchar_t));
#else
	ifcSchemaNameIFC2x3 = new char[i + strlen("IFC2X3_TC1.exp")+1];
	memcpy(&ifcSchemaNameIFC2x3[0], this->m_pszHelpFilePath, i * sizeof(char));
	memcpy(&ifcSchemaNameIFC2x3[i], "IFC2X3_TC1.exp", (strlen("IFC2X3_TC1.exp") + 1) * sizeof(char));
#endif

#ifdef UNICODE
	ifcSchemaNameIFC4 = new wchar_t[i + wcslen(L"IFC4.exp")+1];
	memcpy(&ifcSchemaNameIFC4[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcSchemaNameIFC4[i], L"IFC4.exp", (wcslen(L"IFC4.exp") + 1) * sizeof(wchar_t));
#else
	ifcSchemaNameIFC4 = new char[i + strlen("IFC4.exp")+1];
	memcpy(&ifcSchemaNameIFC4[0], this->m_pszHelpFilePath, i * sizeof(char));
	memcpy(&ifcSchemaNameIFC4[i], "IFC4.exp", (strlen("IFC4.exp") + 1) * sizeof(char));
#endif

	return CWinApp::InitApplication();
}
