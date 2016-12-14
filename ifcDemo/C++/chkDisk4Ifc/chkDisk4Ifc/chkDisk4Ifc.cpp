////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@rdf.bg
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "chkDisk4Ifc.h"
#include "chkDisk4IfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


extern	char	* ifcSchemaName_IFC2x3, * ifcSchemaName_IFC4, * ifcResultDir;

// CchkDisk4IfcApp

BEGIN_MESSAGE_MAP(CchkDisk4IfcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CchkDisk4IfcApp construction

CchkDisk4IfcApp::CchkDisk4IfcApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CchkDisk4IfcApp object

CchkDisk4IfcApp theApp;


// CchkDisk4IfcApp initialization

BOOL CchkDisk4IfcApp::InitInstance()
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

	CchkDisk4IfcDlg dlg;
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

BOOL CchkDisk4IfcApp::InitApplication() 
{
	int	i = (int)strlen(this->m_pszHelpFilePath) - (int)strlen(this->m_pszExeName) - 4;

	ASSERT(ifcSchemaName_IFC2x3 == 0  &&  ifcSchemaName_IFC4 == 0  &&  i > 0);

	ifcSchemaName_IFC2x3 = new char[i+strlen("IFC2X3_TC1.exp")+1];
	memcpy(&ifcSchemaName_IFC2x3[0], this->m_pszHelpFilePath, i);
	memcpy(&ifcSchemaName_IFC2x3[i], "IFC2X3_TC1.exp", strlen("IFC2X3_TC1.exp")+1);

	ifcSchemaName_IFC4 = new char[i+strlen("IFC4.exp")+1];
	memcpy(&ifcSchemaName_IFC4[0], this->m_pszHelpFilePath, i);
	memcpy(&ifcSchemaName_IFC4[i], "IFC4.exp", strlen("IFC4.exp")+1);
	
    char    date[256];

    time_t  t;
    struct tm   tInfo;

    time ( &t );
	localtime_s( &tInfo, &t );

    _itoa_s(1900 + tInfo.tm_year, &date[0], 10, 10);
    _itoa_s(100 + 1 + tInfo.tm_mon, &date[4], 10, 10);
    _itoa_s(100 + tInfo.tm_mday, &date[7], 10, 10);
    date[4] = '-';
    date[7] = '-';
    date[10] = '\\';
    date[11] = '*';
    date[12] = 0;

	ifcResultDir = new char[i+13];
	memcpy(&ifcResultDir[0], this->m_pszHelpFilePath, i);
	memcpy(&ifcResultDir[i], date, 13);

	return CWinApp::InitApplication();
}

#undef int 
