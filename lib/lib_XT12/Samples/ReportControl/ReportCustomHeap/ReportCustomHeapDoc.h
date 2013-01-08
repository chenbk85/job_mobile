// ReportCustomHeapDoc.h : interface of the CReportCustomHeapDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCUSTOMHEAPDOC_H__2B26CF40_D199_40E6_B1DB_71BF1AE09071__INCLUDED_)
#define AFX_REPORTCUSTOMHEAPDOC_H__2B26CF40_D199_40E6_B1DB_71BF1AE09071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReportCustomHeapDoc : public CDocument
{
protected: // create from serialization only
	CReportCustomHeapDoc();
	DECLARE_DYNCREATE(CReportCustomHeapDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCustomHeapDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCustomHeapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCustomHeapDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCUSTOMHEAPDOC_H__2B26CF40_D199_40E6_B1DB_71BF1AE09071__INCLUDED_)
