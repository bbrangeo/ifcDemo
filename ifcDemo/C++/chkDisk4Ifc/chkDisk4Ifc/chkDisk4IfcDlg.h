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

#pragma once

//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


// CchkDisk4IfcDlg dialog
class CchkDisk4IfcDlg : public CDialogEx
{
// Construction
public:
	CchkDisk4IfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHKDISK4IFC_DIALOG };
	CEdit	m_Skip;
	CStatic	m_WarningShow;
	CStatic	m_Warning;
	CButton	m_Ok;
	CButton	m_Cancel;
	CButton	m_CheckSubDirs;
	CEdit	m_ResultDir;
	CEdit	m_BaseDir;
	CStatic	m_TotalTriangles;
	CStatic	m_TotalObjects;
	CStatic	m_TotalFiles;
	CStatic	m_Status;
	CStatic	m_FilePath;
	CStatic	m_FileName;
	//}}AFX_DATA

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void findIfcFiles(char * dir, int * k);
    afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
};

#undef int 
