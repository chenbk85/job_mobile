// RibbonSampleView.h : interface of the CRibbonSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONSAMPLEVIEW_H__935101D2_496C_43ED_BA40_2A8C1D5ED981__INCLUDED_)
#define AFX_RIBBONSAMPLEVIEW_H__935101D2_496C_43ED_BA40_2A8C1D5ED981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRibbonSampleCntrItem;
class CRibbonSampleDoc;

#include "ScrollRichEditView.h"

class CRibbonSampleView : public CScrollRichEditView
{
protected: // create from serialization only
	CRibbonSampleView();
	DECLARE_DYNCREATE(CRibbonSampleView)


// Attributes
public:
	CRibbonSampleDoc* GetDocument();

	void OnGroupFont();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonSampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	void OnEditGoto();

// Implementation
public:
	virtual ~CRibbonSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnFilePrintPreview();

	void OnUpdateRibbonTab(CCmdUI* pCmd);

	void OnParaJustify();
	void OnUpdateParaJustify(CCmdUI* pCmdUI);

	void OnGroupParagraph();
	void OnGroupClipboad();

	CPoint m_ptLastSel;

// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonSampleView)
	afx_msg void OnDestroy();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnEmptyCommand(UINT);
	void OnInsertSomeObject(UINT);


	void OnUpdateSelectorText(CCmdUI* pCmd);
	void OnButtonText();
	void OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateText(CCmdUI* pCmd);
	void OnTextAuto();
	void OnUpdateTextAuto(CCmdUI* pCmd);
	COLORREF m_clr;
	COLORREF m_clrBack;


	void OnEditSize(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateComboSize(CCmdUI* pCmd);
	void OnEditFont(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateComboFont(CCmdUI* pCmd);
	void OnUpdateGalleryFontSize(CCmdUI* pCmdUI);
	void OnUpdateGalleryFontFace(CCmdUI* pCmdUI);

	void OnUpdateBack(CCmdUI* pCmdUI);
	void OnButtonBack();
	void OnUpdateGalleryFontBackColor(CCmdUI* pCmdUI);
	void OnGalleryFontBackColor(NMHDR* pNMHDR, LRESULT* pResult);

	void OnUpdateIndentLeft(CCmdUI* pCmdUI);
	void OnIndentLeft(NMHDR* pNMHDR, LRESULT* pResult);
	void OnIndentLeftSpin(NMHDR* pNMHDR, LRESULT* pResult);
	void SetIndentLeft(long nIndentLeft);
	long GetIndentLeft();

	void OnUpdateIndentRight(CCmdUI* pCmdUI);
	void OnIndentRight(NMHDR* pNMHDR, LRESULT* pResult);
	void OnIndentRightSpin(NMHDR* pNMHDR, LRESULT* pResult);
	void SetIndentRight(long nIndentRight);
	long GetIndentRight();

	void OnUpdateSpaceBefore(CCmdUI* pCmdUI);
	void OnSpaceBefore(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSpaceBeforeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	void SetSpaceBefore(long nSpaceBefore);
	long GetSpaceBefore();

	void OnUpdateSpaceAfter(CCmdUI* pCmdUI);
	void OnSpaceAfter(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSpaceAfterSpin(NMHDR* pNMHDR, LRESULT* pResult);
	void SetSpaceAfter(long nSpaceAfter);
	long GetSpaceAfter();

	void OnUpdateEditUndo(CCmdUI* pCmd);
	void OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult);
	void OnLButtonDown(UINT nFlags, CPoint point) ;
	void OnButtonBackNoColor();
	void OnUpdateBackNoColor(CCmdUI* pCmdUI);

	void OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult);
	void OnZoomIndicator();

	int m_nZoom;

};

#ifndef _DEBUG  // debug version in RibbonSampleView.cpp
inline CRibbonSampleDoc* CRibbonSampleView::GetDocument()
   { return (CRibbonSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONSAMPLEVIEW_H__935101D2_496C_43ED_BA40_2A8C1D5ED981__INCLUDED_)
