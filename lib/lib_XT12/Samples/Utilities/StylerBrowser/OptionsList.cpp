// OptionsList.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsList.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsList

COptionsList::COptionsList()
{
	m_imgList.Create(IDB_OPTIONS, 12, 2, RGB(0, 0xFF, 0));

}

COptionsList::~COptionsList()
{
}


BEGIN_MESSAGE_MAP(COptionsList, CTreeCtrl)
	//{{AFX_MSG_MAP(COptionsList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsList message handlers

void COptionsList::PreSubclassWindow()
{
	ModifyStyle(TVS_SHOWSELALWAYS, TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS);
	SetImageList(&m_imgList, TVSIL_NORMAL);

	CTreeCtrl::PreSubclassWindow();
}
