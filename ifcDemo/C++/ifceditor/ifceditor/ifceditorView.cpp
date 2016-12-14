
// ifceditorView.cpp : implementation of the CifceditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ifceditor.h"
#endif

#include "ifceditorDoc.h"
#include "ifceditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CifceditorView

IMPLEMENT_DYNCREATE(CifceditorView, CView)

BEGIN_MESSAGE_MAP(CifceditorView, CView)
END_MESSAGE_MAP()

// CifceditorView construction/destruction

CifceditorView::CifceditorView()
{
	// TODO: add construction code here

}

CifceditorView::~CifceditorView()
{
}

BOOL CifceditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CifceditorView drawing

void CifceditorView::OnDraw(CDC* /*pDC*/)
{
	CifceditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CifceditorView diagnostics

#ifdef _DEBUG
void CifceditorView::AssertValid() const
{
	CView::AssertValid();
}

void CifceditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CifceditorDoc* CifceditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CifceditorDoc)));
	return (CifceditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CifceditorView message handlers
