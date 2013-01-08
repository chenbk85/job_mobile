// CntrItem.h : interface of the CGallerySampleCntrItem class
//

#if !defined(AFX_CNTRITEM_H__3F2338AE_6846_4BD1_A37D_875060BE171D__INCLUDED_)
#define AFX_CNTRITEM_H__3F2338AE_6846_4BD1_A37D_875060BE171D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGallerySampleDoc;
class CGallerySampleView;

class CGallerySampleCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CGallerySampleCntrItem)

// Constructors
public:
	CGallerySampleCntrItem(REOBJECT* preo = NULL, CGallerySampleDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CGallerySampleDoc* GetDocument()
		{ return (CGallerySampleDoc*)CRichEditCntrItem::GetDocument(); }
	CGallerySampleView* GetActiveView()
		{ return (CGallerySampleView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGallerySampleCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CGallerySampleCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__3F2338AE_6846_4BD1_A37D_875060BE171D__INCLUDED_)
