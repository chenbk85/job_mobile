// SmartLayoutView.h : interface of the CSmartLayoutView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTLAYOUTVIEW_H__A3FB2520_E873_4AF6_A57C_F349CDF8E3CE__INCLUDED_)
#define AFX_SMARTLAYOUTVIEW_H__A3FB2520_E873_4AF6_A57C_F349CDF8E3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSmartLayoutCntrItem;

class CSmartLayoutView : public CRichEditView
{
protected: // create from serialization only
	CSmartLayoutView();
	DECLARE_DYNCREATE(CSmartLayoutView)

// Attributes
public:
	CSmartLayoutDoc* GetDocument();

	COLORREF m_clr;
	DWORD m_dwBorders;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartLayoutView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSmartLayoutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSmartLayoutView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnGetCharFormat(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnSetCharFormat(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnUpdateComboFont(CCmdUI* pCmd);
	afx_msg void OnUpdateComboSize(CCmdUI* pCmd);


	afx_msg void OnUpdateSelectorText(CCmdUI* pCmd);
	afx_msg void OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateText(CCmdUI* pCmd);
	afx_msg void OnButtonText();

	afx_msg void OnTextAuto();
	afx_msg void OnUpdateTextAuto(CCmdUI* pCmd);

	afx_msg void OnTextMore();


	CXTPControlStatic* FindInfoControl(CXTPControl* pControl);

	afx_msg void OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListBoxControlSelChange(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnListBoxControlPoup(NMHDR* pNMHDR, LRESULT* pRes);

		afx_msg void OnColumnsSelChange(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnTableSelChange(NMHDR* pNMHDR, LRESULT* pRes);

	afx_msg void OnInsertTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertColumns(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void SwitchBorders(DWORD dwState);
	afx_msg void OnBorders(UINT nID);
	afx_msg void OnUpdateBorders(CCmdUI* pCmdUI);
	afx_msg void OnEnableCommand(CCmdUI* pCmdUI);

};

#ifndef _DEBUG  // debug version in SmartLayoutView.cpp
inline CSmartLayoutDoc* CSmartLayoutView::GetDocument()
	{ return (CSmartLayoutDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTLAYOUTVIEW_H__A3FB2520_E873_4AF6_A57C_F349CDF8E3CE__INCLUDED_)
