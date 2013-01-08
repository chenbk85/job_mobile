// notepadreView.h : interface of the CNotepadreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEPADREVIEW_H__5FF0A242_98D0_4BC7_A857_B51B535412A0__INCLUDED_)
#define AFX_NOTEPADREVIEW_H__5FF0A242_98D0_4BC7_A857_B51B535412A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNotepadreView : public CEditView
{
	enum e_Alignment {eLeft, eCentre, eRight};

protected: // create from serialization only
	CNotepadreView ();
	DECLARE_DYNCREATE (CNotepadreView)

// Attributes
public:
	CNotepadreDoc *GetDocument ();
	void StartTimer (LPCTSTR lpszPathName);
	void StopTimer ();
	bool IsWordWrapEnabled () const;
	bool IsReadOnlyEnabled () const;
	void InsertTimeDate (const bool bCRLF);
	void DisplayErrorMsg (const CString &str);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadreView)
	public:
	virtual void OnDraw (CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter (COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver (COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop (COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint (CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotepadreView ();
	void ToggleWordWrap ();
	void ToggleReadOnly ();
	void ReCreateWindow (const bool bWordWrap, const bool bReadOnly);
#ifdef _DEBUG
	virtual void AssertValid () const;
	virtual void Dump (CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnPreparePrinting (CPrintInfo *pInfo);
	void PrintHeaderFooter (const CString &str, const bool bHeader,
		const int iWidth, CDC *pDC, CPrintInfo *pInfo);
	void FormatHeaderFooter (CString &strHeaderFooter, const int iPage,
		e_Alignment &eAlignment);

// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadreView)
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy ();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnFilePageSetup();
	afx_msg void OnEditFind ();
	afx_msg void OnEditRepeat ();
	afx_msg void OnEditReplace ();
	afx_msg void OnEditGoto ();
	afx_msg void OnEditTimedate ();
	afx_msg void OnUpdateEditPaste (CCmdUI* pCmdUI);
	afx_msg void OnUpdateNeedFind (CCmdUI* pCmdUI);
	afx_msg void OnUpdateNotReadOnly (CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsScrollToEnd(CCmdUI* pCmdUI);
	afx_msg void OnOptionsScrollToEnd();
	afx_msg void OnUpdateOptionsFileChangeNotify(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFileChangeNotify();
	afx_msg void OnUpdateFormatWordWrap (CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatReadOnly(CCmdUI* pCmdUI);
	afx_msg void OnFormatWordWrap ();
	afx_msg void OnFormatReadOnly();
	afx_msg void OnFormatFont ();
	afx_msg LRESULT OnNotifyFileChange (WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateOptionsAutoReload(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAutoReload();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	COleDropTarget m_DropTarget;
	bool m_bCanDrop;

	int m_iPointSize;
	LOGFONT m_lfDefFont;
	CFont m_font;

	unsigned int m_uiTimer;
	WIN32_FILE_ATTRIBUTE_DATA m_FileAttributeData;
	bool m_bFileChange;

	bool m_bMetric;
	CRect m_rectMargin;
	CString m_strHeader;
	CString m_strFooter;
};

#ifndef _DEBUG  // debug version in notepadreView.cpp
inline CNotepadreDoc* CNotepadreView::GetDocument ()
   { return (CNotepadreDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADREVIEW_H__5FF0A242_98D0_4BC7_A857_B51B535412A0__INCLUDED_)
