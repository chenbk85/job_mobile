#if !defined(AFX_OPTIONSLIST_H__C0BF7FDD_5914_4D12_B5AB_F412381C095A__INCLUDED_)
#define AFX_OPTIONSLIST_H__C0BF7FDD_5914_4D12_B5AB_F412381C095A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsList window

class COptionsList : public CTreeCtrl
{
// Construction
public:
	COptionsList();

// Attributes
public:
	CImageList m_imgList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSLIST_H__C0BF7FDD_5914_4D12_B5AB_F412381C095A__INCLUDED_)
