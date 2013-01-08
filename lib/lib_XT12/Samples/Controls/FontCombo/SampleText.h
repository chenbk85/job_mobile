#if !defined(AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_)
#define AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleText.h : header file
//

class CFontComboDlg;

/////////////////////////////////////////////////////////////////////////////
// CSampleText window

class CSampleText : public CStatic
{
public:
	CSampleText();
	virtual ~CSampleText();

	void UpdateFont(const CXTLogFont& lf, const COLORREF& cr);

	//{{AFX_VIRTUAL(CSampleText)
	//}}AFX_VIRTUAL

protected:
	COLORREF m_cr;
	CXTLogFont m_lf;

	//{{AFX_MSG(CSampleText)
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_)
