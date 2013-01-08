// TabClientPage.h
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

#if !defined(AFX_ALPHAICONSPAGE_H__)
#define AFX_ALPHAICONSPAGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlphaIconsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabManagerPage dialog

class CTabManagerPage : public CXTPPropertyPage
{
// Construction
public:
	CTabManagerPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabManagerPage)
	enum { IDD = IDD_TABCTRL_DIALOG };
	CComboBox   m_comboAppearance;
	CComboBox   m_comboPosition;
	CComboBox   m_comboColor;
	int     m_nAppearance;
	int     m_nColor;
	int     m_nLayout;
	int     m_nPosition;
	BOOL    m_bBoldSelected;
	BOOL    m_bLunaColors;
	BOOL    m_bOneNoteColors;
	BOOL    m_bHotTracking;
	BOOL    m_bShowIcons;
	int     m_nArrows;
	int     m_nClose;
	BOOL    m_bShowStaticFrame;
	int     m_nClientFrame;
	BOOL    m_bAllowReorder;
	BOOL    m_bLargeIcons;
	BOOL	m_bMultiRowFixedSelection;
	BOOL	m_bMultiRowJustified;
	//}}AFX_DATA

	virtual void UpdateControls();

	virtual void OnCancel();

	virtual void Update();

	virtual CXTPTabPaintManager* GetPaintManager()
	{
		return GetManager()->GetPaintManager();
	}

	virtual CXTPTabManager* GetManager()
	{
		return NULL;
	}

	virtual void Reposition()
	{
		GetParentFrame()->RecalcLayout();
	}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabManagerPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabManagerPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboColor();
	afx_msg void virtual OnSelchangeComboPosition();
	afx_msg void OnSelchangeComboAppearance();
	afx_msg void OnCheckBoldSelected();
	afx_msg void OnCheckLunaColors();
	afx_msg void OnCheckOnenoteColors();
	afx_msg void OnCheckHottracking();
	afx_msg virtual void OnCheckIcons();
	afx_msg virtual void OnSelchangeComboLayout();
	afx_msg void OnSelchangeComboArrows();
	afx_msg void OnSelchangeComboClose();
	afx_msg void OnCheckStaticFrame();
	afx_msg void OnSelchangeComboClientFrame();
	afx_msg virtual void OnCheckLargeIcons();
	afx_msg void OnCheckFixedSelection();
	afx_msg void OnCheckJustified();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnCheckAllowReorder();
};


class CTabClientPage : public CTabManagerPage
{
// Construction
public:
	CTabClientPage();   // standard constructor

	virtual CXTPTabManager* GetManager();
	CXTPTabPaintManager* GetPaintManager();

	void Reposition();

	void OnCheckAllowReorder();
	void UpdateControls();
};

class CTabControlPage : public CTabManagerPage
{
// Construction
public:
	CTabControlPage();   // standard constructor

	virtual CXTPTabManager* GetManager();

	virtual void Reposition()
	{
		GetManager()->Reposition();
		((CXTPPropertySheet*)GetParent())->RecalcLayout(NULL, FALSE);
		GetParent()->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
};

class CTabDockingPanePage : public CTabManagerPage
{
// Construction
public:
	CTabDockingPanePage();   // standard constructor

	CXTPTabPaintManager* GetPaintManager();

	virtual void Reposition();
	virtual void UpdateControls();
};

class CTabPanelPage : public CTabManagerPage
{
// Construction
public:
	CTabPanelPage();   // standard constructor

	CXTPTabPaintManager* GetPaintManager();

	virtual void Reposition();
	virtual void UpdateControls();
	BOOL OnInitDialog();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALPHAICONSPAGE_H__)
