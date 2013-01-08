#if !defined(AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_)
#define AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog

class CPropertiesDlg : public CDialog
{
public:
	CPropertiesDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CPropertiesDlg)
	enum { IDD = IDD_ITEM_PROPERTIES };
	CButton	m_btnApply;
	CXTFlatComboBox m_comboSize;
	CXTColorPicker  m_cpText;
	CXTColorPicker  m_cpBack;
	CXTFontCombo    m_comboFont;
	int     m_nIndex;
	BOOL    m_bBoldCheck;
	CString m_strFontSize;
	//}}AFX_DATA

	COLORREF		m_crText;
	COLORREF		m_crBack;
	CXTLogFont		m_LogFont;
	CXTTreeCtrl*	m_pTreeCtrl;

	void UpdateItem(HTREEITEM hItem);
	int DoModalEx(CXTTreeCtrl* pTreeCtrl);

	//{{AFX_VIRTUAL(CPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPropertiesDlg)
	afx_msg void OnBoldCheck();
	afx_msg void OnSelendokSizeCombo();
	afx_msg void OnSelendokFontCombo();
	afx_msg void OnSelEndOkColorText();
	afx_msg void OnSelEndOkColorBack();
	afx_msg void OnEditchangeSizeCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESDLG_H__31B41A07_5CBC_4C5F_8C9D_474D9D55BE65__INCLUDED_)
