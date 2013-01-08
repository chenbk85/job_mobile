// TabbedToolbarDoc.h : interface of the CTabbedToolbarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABBEDTOOLBARDOC_H__3BF6A229_13AD_40A9_90EF_2385E9314B91__INCLUDED_)
#define AFX_TABBEDTOOLBARDOC_H__3BF6A229_13AD_40A9_90EF_2385E9314B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabbedToolbarDoc : public CDocument
{
protected: // create from serialization only
	CTabbedToolbarDoc();
	DECLARE_DYNCREATE(CTabbedToolbarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabbedToolbarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabbedToolbarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabbedToolbarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABBEDTOOLBARDOC_H__3BF6A229_13AD_40A9_90EF_2385E9314B91__INCLUDED_)
