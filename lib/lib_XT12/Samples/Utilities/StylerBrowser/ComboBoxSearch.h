// ComboBoxSearch.h: interface for the CComboBoxSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_)
#define AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ID_LINK_STARTDRAG 1002

class CComboBoxURL : public CXTPControlComboBox  
{
	DECLARE_XTP_CONTROL(CComboBoxURL);
public:
	CComboBoxURL(CXTPCommandBars* pCommandBars = 0);

	void UpdateComboBox();
	void SaveTypedURL();

	void OnClick(BOOL bKeyboard = FALSE, CPoint pt = CPoint(0, 0));
	void OnMouseMove(CPoint point);

	void DoPropExchange(CXTPPropExchange* pPX);
};






class CComboBoxSearch : public CXTPControlComboBox  
{
	DECLARE_XTP_CONTROL(CComboBoxSearch);
public:
	CComboBoxSearch(CXTPCommandBars* pCommandBars = 0);
	virtual ~CComboBoxSearch();

	virtual BOOL OnSetPopup(BOOL bPopup);
	virtual void OnSelChanged();
	virtual void OnEditChanged();

public:
	int m_nCurrentEngine;
	CBrush m_brWindow;
};

#endif // !defined(AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_)
