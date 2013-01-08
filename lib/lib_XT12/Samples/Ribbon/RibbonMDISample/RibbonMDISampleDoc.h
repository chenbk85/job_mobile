// RibbonMDISampleDoc.h : interface of the CRibbonMDISampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONMDISAMPLEDOC_H__8ADF142E_6D76_4FDC_A901_AB4F3A5D5E61__INCLUDED_)
#define AFX_RIBBONMDISAMPLEDOC_H__8ADF142E_6D76_4FDC_A901_AB4F3A5D5E61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRibbonMDISampleDoc : public CRichEditDoc
{
protected: // create from serialization only
	CRibbonMDISampleDoc();
	DECLARE_DYNCREATE(CRibbonMDISampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonMDISampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CRibbonMDISampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonMDISampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONMDISAMPLEDOC_H__8ADF142E_6D76_4FDC_A901_AB4F3A5D5E61__INCLUDED_)
