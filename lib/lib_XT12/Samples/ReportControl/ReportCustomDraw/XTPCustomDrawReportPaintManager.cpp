// XTPCustomDrawReportPaintManager.cpp: implementation of the CXTPCustomDrawReportPaintManager class.
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
#include "XTPCustomDrawReportPaintManager.h"
#include "CustomDrawReportDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPCustomDrawReportPaintManager::CXTPCustomDrawReportPaintManager(CCustomDrawReportDlg* pParent) 
	: m_pParent(pParent)
{
}

CXTPCustomDrawReportPaintManager::~CXTPCustomDrawReportPaintManager()
{
}

int CXTPCustomDrawReportPaintManager::GetRowHeight(CDC* pDC, CXTPReportRow* pRow)
{
	if(m_pParent)
		return m_pParent->GetRowHeight(pDC, pRow);

	return CXTPReportPaintManager::GetRowHeight(pDC, pRow);
}

void CXTPCustomDrawReportPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	if(m_pParent && m_pParent->DrawItem(pDrawArgs, pMetrics))
		return;

	CXTPReportPaintManager::DrawItemCaption(pDrawArgs, pMetrics);
}
