
// ifceditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ifceditor.h"
#include "MainFrm.h"

#include "ifceditorDoc.h"
#include "ifceditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CifceditorApp

BEGIN_MESSAGE_MAP(CifceditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CifceditorApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


wchar_t	* ifcSchemaName_IFC2x3 = 0, * ifcSchemaName_IFC4 = 0;


// CifceditorApp construction

CifceditorApp::CifceditorApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ifceditor.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CifceditorApp object

CifceditorApp theApp;


// CifceditorApp initialization

BOOL CifceditorApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CifceditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CifceditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

// CifceditorApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CifceditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CifceditorApp message handlers





BOOL CifceditorApp::InitApplication()
{
	int	i = (int) wcslen(this->m_pszHelpFilePath) - (int) wcslen(this->m_pszExeName) - 4;

	ASSERT(ifcSchemaName_IFC2x3 == 0  &&  ifcSchemaName_IFC4 == 0  &&  i > 0);

	ifcSchemaName_IFC2x3 = new wchar_t[i+wcslen(L"IFC2X3_TC1.exp")+1];
	memcpy(&ifcSchemaName_IFC2x3[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcSchemaName_IFC2x3[i], L"IFC2X3_TC1.exp", (wcslen(L"IFC2X3_TC1.exp")+1) * sizeof(wchar_t));

	ifcSchemaName_IFC4 = new wchar_t[i+wcslen(L"IFC4.exp")+1];
	memcpy(&ifcSchemaName_IFC4[0], this->m_pszHelpFilePath, i * sizeof(wchar_t));
	memcpy(&ifcSchemaName_IFC4[i], L"IFC4.exp", (wcslen(L"IFC4.exp")+1) * sizeof(wchar_t));

	return CWinApp::InitApplication();
}
