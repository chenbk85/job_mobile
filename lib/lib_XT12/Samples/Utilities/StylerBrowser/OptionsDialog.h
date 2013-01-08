
#pragma once

#include <AfxTempl.h>
#include "OptionsList.h"
#include "resource.h"


#include "PageGeneral.h"
#include "PageKeyboard.h"
#include "PageMouse.h"
#include "PageSearch.h"



class COptionsDialog: public CDialog
{
public:
	COptionsDialog(CWnd* pParent = NULL);

	enum { IDD = IDD_OPTIONS };

private:
	COptionsList m_wndList;
	CRect m_rcWorkspace;
	CArray<COptionsPage*,COptionsPage*> m_arrPages;
	int m_nActive;

public:
	void AddPage(COptionsPage *pPage);
	void SetActivePage(int nPage);


public:	
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();

public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP();

};
