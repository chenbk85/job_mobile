#if !defined(AFX_PAGESEARCH_H__FAC79060_211E_41F2_8F6E_1C04932B42BC__INCLUDED_)
#define AFX_PAGESEARCH_H__FAC79060_211E_41F2_8F6E_1C04932B42BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pagesearch.h : header file
//

#include "OptionsPage.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CPageSearch dialog

class CSearchDialog;
class CComboBoxSearch;


class CPageSearch : public COptionsPage
{
	DECLARE_DYNCREATE(CPageSearch)
	

// Construction
public:
	static void UpdateComboBox(CComboBoxSearch* pCombo);
	void RefreshList();
	static void Save();
	static void Load();
	CPageSearch();
	~CPageSearch();

	struct ENGINE
	{
		CString strTitle, strKeyword, strSearch;
	};
	typedef CArray<ENGINE, ENGINE&> CEngineArray;

// Atributes
	static CEngineArray m_arrEngines;

// Dialog Data
	//{{AFX_DATA(CPageSearch)
	enum { IDD = IDD_PAGE_SEARCH };
	CListCtrl	m_wndSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageSearch)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonRemove();
	afx_msg void OnDblclkListSearch(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog

class CSearchDialog : public CDialog
{
// Construction
public:
	CSearchDialog(CPageSearch::ENGINE& engine, CWnd* pParent = NULL);   // standard constructor

	CPageSearch::ENGINE m_engine;

// Dialog Data
	//{{AFX_DATA(CSearchDialog)
	enum { IDD = IDD_DIALOG_SEARCH };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual void OnOK();

// Implementation
protected:
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESEARCH_H__FAC79060_211E_41F2_8F6E_1C04932B42BC__INCLUDED_)
