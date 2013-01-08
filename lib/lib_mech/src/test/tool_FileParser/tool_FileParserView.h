// tool_FileParserView.h : interface of the Ctool_FileParserView class
//


#pragma once


class Ctool_FileParserView : public CView
{
protected: // create from serialization only
	Ctool_FileParserView();
	DECLARE_DYNCREATE(Ctool_FileParserView)

// Attributes
public:
	Ctool_FileParserDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Ctool_FileParserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tool_FileParserView.cpp
inline Ctool_FileParserDoc* Ctool_FileParserView::GetDocument() const
   { return reinterpret_cast<Ctool_FileParserDoc*>(m_pDocument); }
#endif
