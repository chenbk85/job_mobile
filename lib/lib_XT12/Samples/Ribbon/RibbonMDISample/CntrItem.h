// CntrItem.h : interface of the CRibbonMDISampleCntrItem class
//

#if !defined(AFX_CNTRITEM_H__07B72FD4_CFAE_4C1F_A28C_045DA9A8943D__INCLUDED_)
#define AFX_CNTRITEM_H__07B72FD4_CFAE_4C1F_A28C_045DA9A8943D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRibbonMDISampleDoc;
class CRibbonMDISampleView;

class CRibbonMDISampleCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CRibbonMDISampleCntrItem)

// Constructors
public:
	CRibbonMDISampleCntrItem(REOBJECT* preo = NULL, CRibbonMDISampleDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CRibbonMDISampleDoc* GetDocument()
		{ return (CRibbonMDISampleDoc*)CRichEditCntrItem::GetDocument(); }
	CRibbonMDISampleView* GetActiveView()
		{ return (CRibbonMDISampleView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonMDISampleCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CRibbonMDISampleCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__07B72FD4_CFAE_4C1F_A28C_045DA9A8943D__INCLUDED_)
