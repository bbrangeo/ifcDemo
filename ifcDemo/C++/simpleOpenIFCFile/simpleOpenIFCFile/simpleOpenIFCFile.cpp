
// simpleOpenIFCFile.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "simpleOpenIFCFile.h"
#include "simpleOpenIFCFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



wchar_t		* ifcFileName = 0, * ifcSchemaName_IFC2x3 = 0;



BEGIN_MESSAGE_MAP(CsimpleOpenIFCFileApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CsimpleOpenIFCFileApp construction

CsimpleOpenIFCFileApp::CsimpleOpenIFCFileApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CsimpleOpenIFCFileApp object

CsimpleOpenIFCFileApp theApp;


// CsimpleOpenIFCFileApp initialization

BOOL CsimpleOpenIFCFileApp::InitInstance()
{
	CWinApp::InitInstance();


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

	CsimpleOpenIFCFileDlg dlg;
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

BOOL CsimpleOpenIFCFileApp::InitApplication()
{
	int	i = (int) wcslen(this->m_pszHelpFilePath) - (int) wcslen(this->m_pszExeName) - 4;

	ifcFileName = new wchar_t[i + wcslen(L"input.ifc") + 1];
	memcpy(&ifcFileName[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcFileName[i], L"input.ifc", (wcslen(L"input.ifc") + 1) * sizeof(wchar_t));

	ifcSchemaName_IFC2x3 = new wchar_t[i + wcslen(L"IFC2X3_TC1.exp") + 1];
	memcpy(&ifcSchemaName_IFC2x3[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcSchemaName_IFC2x3[i], L"IFC2X3_TC1.exp", (wcslen(L"IFC2X3_TC1.exp") + 1) * sizeof(wchar_t));

	return CWinApp::InitApplication();
}
