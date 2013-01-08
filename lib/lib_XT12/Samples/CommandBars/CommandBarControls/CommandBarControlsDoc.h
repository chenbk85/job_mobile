// CommandBarControlsDoc.h : interface of the CCommandBarControlsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDBARCONTROLSDOC_H__BC7BBCAD_8270_4D3C_82DA_B8879E594FB0__INCLUDED_)
#define AFX_COMMANDBARCONTROLSDOC_H__BC7BBCAD_8270_4D3C_82DA_B8879E594FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommandBarControlsDoc : public CDocument
{
protected: // create from serialization only
	CCommandBarControlsDoc();
	DECLARE_DYNCREATE(CCommandBarControlsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandBarControlsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommandBarControlsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommandBarControlsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDBARCONTROLSDOC_H__BC7BBCAD_8270_4D3C_82DA_B8879E594FB0__INCLUDED_)
