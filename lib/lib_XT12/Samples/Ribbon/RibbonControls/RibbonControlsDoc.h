// RibbonControlsDoc.h : interface of the CRibbonControlsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONCONTROLSDOC_H__E42DBF73_86E4_496F_B2E8_A56D64F6958B__INCLUDED_)
#define AFX_RIBBONCONTROLSDOC_H__E42DBF73_86E4_496F_B2E8_A56D64F6958B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRibbonControlsDoc : public CDocument
{
protected: // create from serialization only
	CRibbonControlsDoc();
	DECLARE_DYNCREATE(CRibbonControlsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonControlsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRibbonControlsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonControlsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONCONTROLSDOC_H__E42DBF73_86E4_496F_B2E8_A56D64F6958B__INCLUDED_)
