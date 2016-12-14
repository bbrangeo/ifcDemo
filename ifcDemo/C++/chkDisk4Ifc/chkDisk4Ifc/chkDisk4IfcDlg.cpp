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
#include "IFCEngineInteract.h"

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


extern  char    * ifcResultDir;
int     checkSubDirs;
char    resultDir[1024];
int     resultDirLength,
        skipCnt;
CFont   * pFontB, * pFontN;

// CchkDisk4IfcDlg dialog




CchkDisk4IfcDlg::CchkDisk4IfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CchkDisk4IfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchkDisk4IfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChkDisk4IfcDlg)
	DDX_Control(pDX, IDC_EDIT_SKIP, m_Skip);
	DDX_Control(pDX, IDC_STATIC_WARNING_SHOW, m_WarningShow);
	DDX_Control(pDX, IDC_STATIC_WARNING, m_Warning);
	DDX_Control(pDX, IDC_START, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_CHECK_SUBDIRS, m_CheckSubDirs);
	DDX_Control(pDX, IDC_EDIT_DIR, m_ResultDir);
	DDX_Control(pDX, IDC_EDIT_RESULTS, m_BaseDir);
	DDX_Control(pDX, IDC_STATIC_TOTALTRIANGLES, m_TotalTriangles);
	DDX_Control(pDX, IDC_STATIC_TOTALOBJECTS, m_TotalObjects);
	DDX_Control(pDX, IDC_STATIC_TOTALFILES, m_TotalFiles);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_Status);
	DDX_Control(pDX, IDC_STATIC_FILEPATH, m_FilePath);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_FileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CchkDisk4IfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CchkDisk4IfcDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CchkDisk4IfcDlg message handlers

BOOL CchkDisk4IfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    m_BaseDir.SetWindowText("C:\\*");
    m_ResultDir.SetWindowText(ifcResultDir);
    m_CheckSubDirs.SetCheck(true);
    m_Skip.SetWindowText("0");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CchkDisk4IfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int	x = (rect.Width() - cxIcon + 1) / 2,
			y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon((__int32) x, (__int32) y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CchkDisk4IfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CchkDisk4IfcDlg::findIfcFiles(char * dir, int * k)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE          hFind;
    char            * filename;


    hFind = FindFirstFile(dir, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE) 
    {
        FindNextFile(hFind, &FindFileData);
        while  (FindNextFile(hFind, &FindFileData)) {
            char    name[1024];
            int i = 0;
            memcpy(&name[i], dir, length(dir));
            i += length(dir) - 1;
            memcpy(&name[i], FindFileData.cFileName, length(FindFileData.cFileName));
            i += length(FindFileData.cFileName);
            name[i++] = 0;
        
            if  (i < 256) {
				if  (_chdir(name)) {
					if  ( ( (i > 4)  &&
							(name[i-5] == '.')  &&
							(name[i-4] == 'i'  ||  name[i-4] == 'I')  &&
							(name[i-3] == 'f'  ||  name[i-3] == 'F')  &&
							(name[i-2] == 'c'  ||  name[i-2] == 'C'  ||  name[i-2] == 'x'  ||  name[i-2] == 'X') )  ||
							( (i > 7)  &&
							(name[i-8] == '.')  &&
							(name[i-7] == 'i'  ||  name[i-7] == 'I')  &&
							(name[i-6] == 'f'  ||  name[i-6] == 'F')  &&
							(name[i-5] == 'c'  ||  name[i-5] == 'C')  &&
							(name[i-4] == 'x'  ||  name[i-4] == 'X')  &&
							(name[i-3] == 'm'  ||  name[i-3] == 'M')  &&
							(name[i-2] == 'k'  ||  name[i-2] == 'L') ) ) {
                        filename = new char[i];
                        memcpy(filename, &name[0], i);

                        m_FileName.SetFont(pFontB, true);
                        m_FilePath.SetFont(pFontB, true);
                        m_Status.SetFont(pFontB, true);
                 
                        m_FileName.SetWindowText(FindFileData.cFileName);
                        m_FilePath.SetWindowText(dir);
                        (*k)++;

                        StartLoadingIfcFile(filename, FindFileData.cFileName, &m_Status, &m_TotalFiles, &m_TotalObjects, &m_TotalTriangles);                    
                    } else {
                        m_FileName.SetFont(pFontN, true);
                        m_FilePath.SetFont(pFontN, true);
                        m_Status.SetFont(pFontN, true);

                        m_FileName.SetWindowText(FindFileData.cFileName);
                        m_FilePath.SetWindowText(dir);

                        m_Status.SetWindowText("-");
                    }
                } else {
                    if  (checkSubDirs) {
                        name[i-1] = '\\';
                        name[i] = '*';
                        name[i+1] = 0;
                        findIfcFiles(name, k);
                    }
                }
            } else {
                m_WarningShow.EnableWindow(true);
                m_Warning.SetFont(pFontB, true);
                m_Warning.SetWindowText("Some of your path + filename increases the windows max (256, actual max is 260)/nImplement FindFirstFileExA/FindFirstFileExW if you want to access these files also.");
            }
        }
        FindClose(hFind);
    }
}

void    repairDir(char * dir)
{
    int i = length(dir);

    if  (dir[i-1] == '*') {
        ////ASSERT(dir[i-2] == '\\');
    } else {
        if  (dir[i-1] == '\\') {
            dir[i+0] = '*';
            dir[i+1] = 0;
        } else {
            dir[i+0] = '\\';
            dir[i+1] = '*';
            dir[i+2] = 0;
        }
    }
}

void CchkDisk4IfcDlg::OnOK() 
{
	CDialog::OnOK();
}

void CchkDisk4IfcDlg::OnBnClickedStart()
{
    char baseDir[1024], buffer[512];
    int  k = 0;

    m_Skip.GetWindowText(buffer, 512);
    skipCnt = atoi(buffer);

    LOGFONT lf;
    HFONT   m_hFont;
    m_FileName.GetFont()->GetLogFont(&lf);

    lf.lfWeight = FW_BOLD;
    m_hFont = ::CreateFontIndirect(&lf);
    pFontB = CFont::FromHandle(m_hFont);

    lf.lfWeight = FW_NORMAL;
    m_hFont = ::CreateFontIndirect(&lf);
    pFontN = CFont::FromHandle(m_hFont);

    m_Ok.EnableWindow(false);
    m_Cancel.EnableWindow(false);
    m_BaseDir.EnableWindow(false);
    m_ResultDir.EnableWindow(false);
    m_CheckSubDirs.EnableWindow(false);

    m_BaseDir.GetWindowText(baseDir, 1024);
    m_ResultDir.GetWindowText(resultDir, 1024);
    checkSubDirs = m_CheckSubDirs.GetCheck();

    repairDir(baseDir);
    repairDir(resultDir);

    resultDirLength = length(resultDir);

    resultDir[resultDirLength-2] = 0;

    if  (_chdir(resultDir)) {
        _mkdir(resultDir);
    }

    resultDir[resultDirLength-2] = '\\';
    findIfcFiles(baseDir, &k);

    m_Ok.EnableWindow(true);
    m_Cancel.EnableWindow(true);
    m_BaseDir.EnableWindow(true);
    m_ResultDir.EnableWindow(true);
    m_CheckSubDirs.EnableWindow(true);
}

#undef int 
