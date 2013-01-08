// GallerySampleView.h : interface of the CGallerySampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GALLERYSAMPLEVIEW_H__A8624FF3_1A17_4566_9D54_FCF41A54EB31__INCLUDED_)
#define AFX_GALLERYSAMPLEVIEW_H__A8624FF3_1A17_4566_9D54_FCF41A54EB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGallerySampleCntrItem;

class CGallerySampleView : public CRichEditView
{
protected: // create from serialization only
	CGallerySampleView();
	DECLARE_DYNCREATE(CGallerySampleView)

// Attributes
public:
	CGallerySampleDoc* GetDocument();

	COLORREF m_clrText;
	COLORREF m_clrBack;
	void OnButtonText();
	void OnButtonBack();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGallerySampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGallerySampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGallerySampleView)
	afx_msg void OnDestroy();
	afx_msg void OnFormatFontcolorAutomatic();
	afx_msg void OnUpdateFormatFontcolorAutomatic(CCmdUI* pCmdUI);
	afx_msg void OnFormatFontcolorMorecolors();
	afx_msg void OnFormatFontcolorNoHighlight();
	//}}AFX_MSG
	void OnUpdateGalleryFontBackColor(CCmdUI* pCmdUI);
	void OnGalleryFontBackColor(NMHDR* pNMHDR, LRESULT* pResult);

	void OnUpdateGalleryFontTextColor(CCmdUI* pCmdUI);
	void OnGalleryFontTextColor(NMHDR* pNMHDR, LRESULT* pResult);

	void OnUpdateGalleryFontFace(CCmdUI* pCmdUI);
	void OnUpdateGalleryFontSize(CCmdUI* pCmdUI);
	
	void OnUpdateBack(CCmdUI* pCmdUI);
	void OnUpdateButtonText(CCmdUI* pCmd);
	DECLARE_MESSAGE_MAP()

	void OnEditFont(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateComboFont(CCmdUI* pCmd);

	void OnUpdateComboSize(CCmdUI* pCmd);
	void OnEditSize(NMHDR* pNMHDR, LRESULT* pResult);
	void OnEmptyCommand();

	void OnUpdateEditUndo(CCmdUI* pCmd);
	void OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in GallerySampleView.cpp
inline CGallerySampleDoc* CGallerySampleView::GetDocument()
   { return (CGallerySampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GALLERYSAMPLEVIEW_H__A8624FF3_1A17_4566_9D54_FCF41A54EB31__INCLUDED_)
