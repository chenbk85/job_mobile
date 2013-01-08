// SmartLayoutDoc.h : interface of the CSmartLayoutDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTLAYOUTDOC_H__C3F65B55_1C52_4B57_A8E8_4CCACEA26725__INCLUDED_)
#define AFX_SMARTLAYOUTDOC_H__C3F65B55_1C52_4B57_A8E8_4CCACEA26725__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSmartLayoutDoc : public CRichEditDoc
{
protected: // create from serialization only
	CSmartLayoutDoc();
	DECLARE_DYNCREATE(CSmartLayoutDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartLayoutDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CSmartLayoutDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSmartLayoutDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTLAYOUTDOC_H__C3F65B55_1C52_4B57_A8E8_4CCACEA26725__INCLUDED_)
