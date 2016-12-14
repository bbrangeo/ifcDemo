
// simpleOpenIFCFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "simpleOpenIFCFile.h"
#include "simpleOpenIFCFileDlg.h"
#include "afxdialogex.h"

#include "ifcengine\include\engine.h"
#include "ifcengine\include\ifcengine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



extern	wchar_t		* ifcFileName, * ifcSchemaName_IFC2x3;



CsimpleOpenIFCFileDlg::CsimpleOpenIFCFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsimpleOpenIFCFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsimpleOpenIFCFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsimpleOpenIFCFileDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_IFC_FILE, &CsimpleOpenIFCFileDlg::OnBnClickedButtonOpenIfcFile)
END_MESSAGE_MAP()


// CsimpleOpenIFCFileDlg message handlers

BOOL CsimpleOpenIFCFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsimpleOpenIFCFileDlg::OnPaint()
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
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsimpleOpenIFCFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsimpleOpenIFCFileDlg::OnBnClickedButtonOpenIfcFile()
{
#ifndef	WIN64
	__int32 ifcModel = sdaiOpenModelBNUnicode(0, ifcFileName, ifcSchemaName_IFC2x3);
#else
	__int64 ifcModel = sdaiOpenModelBNUnicode(0, ifcFileName, ifcSchemaName_IFC2x3);
#endif

	if	(ifcModel) {
		sdaiCloseModel(ifcModel);

		MessageBoxW(L"IFC file opened and closed correctly.");
	} else {
		//
		//	something went wrong, could not open IFC file
		//
		ASSERT(false);
	}
}
