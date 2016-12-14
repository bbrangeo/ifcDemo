
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ifceditor.h"

#include "MainFrm.h"

#include "LeftPane.h"
#include "RightPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return	false;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return	true;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if	(!m_wndSplitter.CreateStatic(this, 1, 2)) {
		return	false;
	}

	if	( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftPane), CSize(200, 200), pContext)  ||
		  !m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightPane), CSize(10, 10), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return	false;
	}

	return	true;
}
