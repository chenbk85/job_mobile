#if !defined(AFX_STATICMENUGRABBER_H__1F8B08E0_B524_4560_8613_E67776B1F694__INCLUDED_)
#define AFX_STATICMENUGRABBER_H__1F8B08E0_B524_4560_8613_E67776B1F694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticMenuGrabber.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticMenuGrabber window

class CStaticMenuGrabber : public CStatic
{
// Construction
public:
	CStaticMenuGrabber();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticMenuGrabber)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticMenuGrabber();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticMenuGrabber)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	HCURSOR m_hCursor;

	void HighlightWindow(HWND hwnd, BOOL fDraw);
	BOOL m_bGrabbing;
	void ConvertMenu(HWND hWnd);

public:
	CXTPToolBar* m_pMenuBar;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICMENUGRABBER_H__1F8B08E0_B524_4560_8613_E67776B1F694__INCLUDED_)
