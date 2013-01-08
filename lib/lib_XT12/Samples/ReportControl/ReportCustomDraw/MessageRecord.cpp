// MessageRecord.cpp: implementation of the CMessageRecord class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomDrawReport.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CMessageRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

IMPLEMENT_SERIAL(CMessageRecordItemCheckGroup, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(CMessageRecordItemRadioGroup, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

//////////////////////////////////////////////////////////////////////////
// CMessageRecordItemCheckGroup

CMessageRecordItemCheckGroup::CMessageRecordItemCheckGroup()
	: m_unCheckboxes(0), m_ulValue(0)
{
}

CMessageRecordItemCheckGroup::CMessageRecordItemCheckGroup(unsigned int unCheckboxes, ULONG ulValue)
	: m_unCheckboxes(unCheckboxes), m_ulValue(ulValue)
{
}

int CMessageRecordItemCheckGroup::Compare(CXTPReportColumn* /*pColumn*/, CXTPReportRecordItem* pItem)
{
	return int(m_ulValue) - int(((CMessageRecordItemCheckGroup*)pItem)->m_ulValue);
}

CString CMessageRecordItemCheckGroup::GetGroupCaption(CXTPReportColumn* /*pColumn*/)
{
	CString strGroupCaption;

	strGroupCaption.Format(_T("%d"), m_ulValue);
	return strGroupCaption;
}

int CMessageRecordItemCheckGroup::CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem)
{
	return GetGroupCaption(pColumn).Compare(pItem->GetGroupCaption(pColumn));
}

void CMessageRecordItemCheckGroup::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_ULong(pPX, _T("Attr1"), m_ulValue);
}


//////////////////////////////////////////////////////////////////////////
// CMessageRecordItemRadioGroup

CMessageRecordItemRadioGroup::CMessageRecordItemRadioGroup()
	: m_unRadioButtons(0), m_ulValue(0)
{
}

CMessageRecordItemRadioGroup::CMessageRecordItemRadioGroup(unsigned int unRadioButtons, ULONG ulValue)
	: m_unRadioButtons(unRadioButtons), m_ulValue(ulValue)
{
}

int CMessageRecordItemRadioGroup::Compare(CXTPReportColumn* /*pColumn*/, CXTPReportRecordItem* pItem)
{
	return int(m_ulValue) - int(((CMessageRecordItemRadioGroup*)pItem)->m_ulValue);
}

CString CMessageRecordItemRadioGroup::GetGroupCaption(CXTPReportColumn* /*pColumn*/)
{
	CString strGroupCaption;

	strGroupCaption.Format(_T("%d"), m_ulValue);
	return strGroupCaption;
}

int CMessageRecordItemRadioGroup::CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem)
{
	return GetGroupCaption(pColumn).Compare(pItem->GetGroupCaption(pColumn));
}

void CMessageRecordItemRadioGroup::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_ULong(pPX, _T("Attr2"), m_ulValue);
}



//////////////////////////////////////////////////////////////////////
// CMessageRecord class

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageRecord::CMessageRecord()
{
	m_pItemAttr1 = NULL;
	m_pItemAttr2 = NULL;

	CreateItems();
}

CMessageRecord::CMessageRecord(CString strName, unsigned int unCheckboxes, unsigned int unCheckValue,
					unsigned int unRadioButtons, unsigned int unRadioValue,
					CString strProgressText, COLORREF clrProgress, int nProgressWidth, int nProgressLower, int nProgressUpper, int nProgressStep, int nProgressPos)
{
	AddItem(new CXTPReportRecordItemText(strName));
	m_pItemAttr1 = (CMessageRecordItemCheckGroup*)AddItem(new CMessageRecordItemCheckGroup(unCheckboxes, unCheckValue));
	m_pItemAttr2 = (CMessageRecordItemRadioGroup*)AddItem(new CMessageRecordItemRadioGroup(unRadioButtons, unRadioValue));
	m_pItemAttr3 = (CXTPReportRecordItemProgress*)AddItem(new CXTPReportRecordItemProgress(strProgressText, clrProgress, nProgressWidth, nProgressLower, nProgressUpper, nProgressStep, nProgressPos));

//	SetPreviewItem(new CXTPReportRecordItemPreview(strPreview));
}

void CMessageRecord::CreateItems()
{
	// Initialize record items with empty values
	
	// 0 
	AddItem(new CXTPReportRecordItemText(_T("")));

	// 1 ***
	m_pItemAttr1 = (CMessageRecordItemCheckGroup*)AddItem(new CMessageRecordItemCheckGroup(1, 0));
	
	// 2 ***
	m_pItemAttr2 = (CMessageRecordItemRadioGroup*)AddItem(new CMessageRecordItemRadioGroup(1, 0));
	
	// 3 ***
	m_pItemAttr3 = (CXTPReportRecordItemProgress*)AddItem(new CXTPReportRecordItemProgress(_T("Test string"), RGB(0, 0, 150), 15, 5, 105, 15, 25));

	SetPreviewItem(new CXTPReportRecordItemPreview(_T("")));
}

CMessageRecord::~CMessageRecord()
{

}

void CMessageRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPReportRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}

void CMessageRecord::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecord::DoPropExchange(pPX);

	if (pPX->IsLoading())
	{
		// 1 - m_pItemAttr1 = (CMessageRecordItemCheckGroup*)AddItem(new CMessageRecordItemCheckGroup(1, 0));
		ASSERT_KINDOF(CMessageRecordItemCheckGroup, GetItem(1));
		m_pItemAttr1 = DYNAMIC_DOWNCAST(CMessageRecordItemCheckGroup, GetItem(1));
		ASSERT(m_pItemAttr1);
		
		// 2 - m_pItemAttr2 = (CMessageRecordItemRadioGroup*)AddItem(new CMessageRecordItemRadioGroup(1, 0));
		ASSERT_KINDOF(CMessageRecordItemRadioGroup, GetItem(2));
		m_pItemAttr2 = DYNAMIC_DOWNCAST(CMessageRecordItemRadioGroup, GetItem(2));
		ASSERT(m_pItemAttr2);
	}
}
