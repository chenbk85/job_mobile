// SkinSDISampleDoc.h : interface of the CSkinSDISampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINSDISAMPLEDOC_H__65FFE4F9_8D66_47F3_B960_0169C41F2AE4__INCLUDED_)
#define AFX_SKINSDISAMPLEDOC_H__65FFE4F9_8D66_47F3_B960_0169C41F2AE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkinSDISampleDoc : public CRichEditDoc
{
protected: // create from serialization only
	CSkinSDISampleDoc();
	DECLARE_DYNCREATE(CSkinSDISampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSDISampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CSkinSDISampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinSDISampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDISAMPLEDOC_H__65FFE4F9_8D66_47F3_B960_0169C41F2AE4__INCLUDED_)
