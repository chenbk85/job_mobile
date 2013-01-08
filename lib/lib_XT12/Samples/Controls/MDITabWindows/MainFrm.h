// MainFrm.h : interface of the CMainFrame class
//
// This file is a part of the XTREME TOOLKIT MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_)
#define AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMDIWndTab : public CXTMDIWndTab
{
protected:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#define CMainFrameBase CXTPMDIFrameWnd

class CMainFrame : public CMainFrameBase
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
    
    CMDIWndTab& GetMDITabWindow() {
        return m_wndMDITabWindow;
    }

    void ToggleMDITabs();
    void HideMDITabs();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void SetTheme(int iTheme);

	CXTPStatusBar   m_wndStatusBar;
	CMDIWndTab m_wndMDITabWindow;
	BOOL         m_bAlignment[4];
	BOOL         m_bMDIActive;
	CXTRegistryManager m_regMgr;
	int            m_iTheme;

	enum ALIGNMENT { left, top, right, bottom };

	void SetMDITabStyle();
	void SetAlignment(ALIGNMENT eAlign);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate();
	afx_msg void OnClosedocument();
	afx_msg void OnHidetabs();
	afx_msg void OnAligntableft();
	afx_msg void OnAligntabtop();
	afx_msg void OnAligntabright();
	afx_msg void OnAligntabbottom();
	afx_msg void OnUpdateAligntableft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabtop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabright(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAligntabbottom(CCmdUI* pCmdUI);
	afx_msg void OnShowMditabs();
	afx_msg void OnUpdateShowMditabs(CCmdUI* pCmdUI);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowCascade(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowTileHorz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowArrange(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnClose() ;
	afx_msg void OnCustomize();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CBFD0AD7_BE56_477B_B837_281F1370F9EE__INCLUDED_)
