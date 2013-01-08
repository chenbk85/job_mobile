// GallerySampleDoc.h : interface of the CGallerySampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GALLERYSAMPLEDOC_H__96B2A54A_C90C_4F10_BE02_BC8D727B6B2F__INCLUDED_)
#define AFX_GALLERYSAMPLEDOC_H__96B2A54A_C90C_4F10_BE02_BC8D727B6B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGallerySampleDoc : public CRichEditDoc
{
protected: // create from serialization only
	CGallerySampleDoc();
	DECLARE_DYNCREATE(CGallerySampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGallerySampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CGallerySampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGallerySampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GALLERYSAMPLEDOC_H__96B2A54A_C90C_4F10_BE02_BC8D727B6B2F__INCLUDED_)
