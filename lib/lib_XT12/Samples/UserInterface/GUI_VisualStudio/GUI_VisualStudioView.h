// GUI_VisualStudioView.h : interface of the CGUI_VisualStudioView class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_VISUALSTUDIOVIEW_H__954BEB65_A878_40A1_A864_57F5C30DC303__INCLUDED_)
#define AFX_GUI_VISUALSTUDIOVIEW_H__954BEB65_A878_40A1_A864_57F5C30DC303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _XTP_INCLUDE_SYNTAXEDIT
#define CXTPSyntaxEditView CEditView
#endif

class CGUI_VisualStudioView : public CXTPSyntaxEditView
{
protected: // create from serialization only
	CGUI_VisualStudioView();
	DECLARE_DYNCREATE(CGUI_VisualStudioView)

// Attributes
public:
	CGUI_VisualStudioDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_VisualStudioView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGUI_VisualStudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGUI_VisualStudioView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnUpdateEditFind(CCmdUI* pCmd);
	void OnEditFind(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in GUI_VisualStudioView.cpp
inline CGUI_VisualStudioDoc* CGUI_VisualStudioView::GetDocument()
	{ return (CGUI_VisualStudioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_VISUALSTUDIOVIEW_H__954BEB65_A878_40A1_A864_57F5C30DC303__INCLUDED_)
