// MDITextEditorView.h : interface of the CMDITextEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDITEXTEDITORVIEW_H__8755594F_0001_4908_9353_5187AEEF9610__INCLUDED_)
#define AFX_MDITEXTEDITORVIEW_H__8755594F_0001_4908_9353_5187AEEF9610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define CViewBase	CView
#define CViewBase	CXTPSyntaxEditView

class CMDITextEditorView : public CViewBase
{
protected: // create from serialization only
	CMDITextEditorView();
	DECLARE_DYNCREATE(CMDITextEditorView)

// Attributes
public:
	CMDITextEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITextEditorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
	virtual BOOL OnRowColChanged(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnParseEvent(NMHDR* pNMHDR, LRESULT* pResult);
	void OnPrintHeader(CDC* pDC, CPrintInfo* pInfo);
	void OnPrintFooter(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMDITextEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDITextEditorView)
	afx_msg void OnToolsBookmark();
	afx_msg void OnToolsBreakpoint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditFindSilent();
	afx_msg void OnToolsNextBookmark();
	afx_msg void OnUpdateToolsNextBookmark(CCmdUI* pCmdUI);
	afx_msg void OnToolsPrevBookmark();
	afx_msg void OnUpdateToolsPrevBookmark(CCmdUI* pCmdUI);
	afx_msg void OnEditTabify();
	afx_msg void OnEditUnTabify();
	afx_msg void OnEditUppercase();
	afx_msg void OnEditLowercase();
	afx_msg void OnEditWhiteSpace();
	afx_msg void OnEditCollapseAll();
	afx_msg void OnEditExpandAll();
	afx_msg void OnUpdateEditWhiteSpace(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions();
	afx_msg void OnFileGoTo();
	afx_msg void OnReadOnly();
	afx_msg void OnUpdateReadOnly(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	RECT  m_rcMargin;
	DWORD m_dwLastUpdate;
	DWORD m_dwParserStart;
	CXTPSyntaxEditGoToLineDlg m_dlgGoTo;
};

#ifndef _DEBUG  // debug version in MDITextEditorView.cpp
inline CMDITextEditorDoc* CMDITextEditorView::GetDocument()
   { return (CMDITextEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDITEXTEDITORVIEW_H__8755594F_0001_4908_9353_5187AEEF9610__INCLUDED_)
