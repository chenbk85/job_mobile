// ReportCustomHeapView.h : interface of the CReportCustomHeapView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCUSTOMHEAPVIEW_H__66197631_84DB_475D_BDBC_D43A20168066__INCLUDED_)
#define AFX_REPORTCUSTOMHEAPVIEW_H__66197631_84DB_475D_BDBC_D43A20168066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReportCustomHeapView : public CXTPReportView
{
protected: // create from serialization only
	CReportCustomHeapView();
	DECLARE_DYNCREATE(CReportCustomHeapView)

// Attributes
public:
	CReportCustomHeapDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCustomHeapView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCustomHeapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	void AddRecords(int nCountToAdd) ;
	void AddRecord(int nState, LPCTSTR pcszText, double dNumber, const COleDateTime& dtDate, 
				   const COleVariant& varVariant);
	void UpdateTitle(DWORD dwAddTime, DWORD dwPopulateTime);

	void BatchAddRecords(int nCountToAdd);

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCustomHeapView)
	afx_msg void OnAdd10kRecords();
	afx_msg void OnAdd20kRecords();
	afx_msg void OnBatchAdd10kRecords();
	afx_msg void OnBatchAdd20kRecords();
	afx_msg void OnRemoveAllRecords();
	afx_msg void OnViewPreviewMode();
	afx_msg void OnUpdateViewPreviewMode(CCmdUI* pCmdUI);
	afx_msg void OnRemoveHalfRecords();
	afx_msg void OnFreeExtraBatchData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ReportCustomHeapView.cpp
inline CReportCustomHeapDoc* CReportCustomHeapView::GetDocument()
   { return (CReportCustomHeapDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCUSTOMHEAPVIEW_H__66197631_84DB_475D_BDBC_D43A20168066__INCLUDED_)
