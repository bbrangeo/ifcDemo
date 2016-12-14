
// ifceditorView.h : interface of the CifceditorView class
//

#pragma once


class CifceditorView : public CView
{
protected: // create from serialization only
	CifceditorView();
	DECLARE_DYNCREATE(CifceditorView)

// Attributes
public:
	CifceditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CifceditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ifceditorView.cpp
inline CifceditorDoc* CifceditorView::GetDocument() const
   { return reinterpret_cast<CifceditorDoc*>(m_pDocument); }
#endif

