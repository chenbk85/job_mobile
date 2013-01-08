// PaneProperties.h : header file
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

#if !defined(AFX_PANEPROPERTIES_H__459C9EAA_E750_419F_BA3D_8AF424923076__INCLUDED_)
#define AFX_PANEPROPERTIES_H__459C9EAA_E750_419F_BA3D_8AF424923076__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct FINDCONTROLPARAM
{
	CXTPPropertyGridItem* pItem;
	BOOL bIncludeSelf;
	BOOL bRefresh;
};

/////////////////////////////////////////////////////////////////////////////
// CPaneProperties window

class CPaneProperties : public CPaneHolder
{
	typedef void (CPaneProperties::*ONCONTROLVALUECHANGEDINSTANCE)(CXTPControl* pControl, FINDCONTROLPARAM* pParam);


// Construction
public:
	CPaneProperties();

// Attributes
public:
	CXTPToolBar m_wndToolBar;

	CXTPPropertyGrid m_wndPropertyGrid;
	int m_nInstanceCount;

	CXTPCommandBars* m_pActiveCommandBars;
	
	CPaneHolder* m_pActivePane;
	CObject* m_pActiveObject;
	CXTPPropertyGridUpdateContext m_stateExpanding;


	void Refresh(CPaneHolder* pActivePane = NULL);
	void RefreshPaneProperties();

	void RefreshToolbarsPane();
	void RefreshControlProperties();
	void RefreshControlsPane();

	void OnPropertyChanged(CXTPControl* pControl);

	void FillConstraintsID(CXTPPropertyGridItem* pItem);
	void FillConstraintsToolbarsID(CXTPPropertyGridItem* pItem);
	void FillConstraintsActionsID(CXTPPropertyGridItem* pItem);
	void FillActionProperties(CXTPPropertyGridItem* pCategory, CXTPControlAction* pAction);

	void OnControlValueChanged(CXTPPropertyGridItem* pItem );
	void OnControlValueChangedInstance(CXTPControl* pControl, FINDCONTROLPARAM* pParam);

	void EnableActions();
	void CreateActionList(CXTPCommandBars* pCommandBars, CXTPControls* pControls);


	BOOL m_bApplyForGroup;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneProperties)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaneProperties();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPaneProperties)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPanePropertiesCategorized();
	afx_msg void OnUpdatePanePropertiesCategorized(CCmdUI* pCmdUI);
	afx_msg void OnPanePropertiesAlphabetic();
	afx_msg void OnUpdatePanePropertiesAlphabetic(CCmdUI* pCmdUI);
	afx_msg void OnPanePropertiesPages();
	afx_msg void OnUpdatePanePropertiesPages(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd*);

	//}}AFX_MSG

	afx_msg LRESULT OnGridNotify(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEPROPERTIES_H__459C9EAA_E750_419F_BA3D_8AF424923076__INCLUDED_)
