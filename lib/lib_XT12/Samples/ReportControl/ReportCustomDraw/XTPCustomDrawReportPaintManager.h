// XTPCustomDrawReportPaintManager.h: interface for the CXTPCustomDrawReportPaintManager class.
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

#if !defined(AFX_XTPCUSTOMDRAWREPORTPAINTMANAGER_H__3D7A3DA9_B37E_4863_9B2F_D2F5191AB35B__INCLUDED_)
#define AFX_XTPCUSTOMDRAWREPORTPAINTMANAGER_H__3D7A3DA9_B37E_4863_9B2F_D2F5191AB35B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomDrawReportDlg;

class CXTPCustomDrawReportPaintManager : public CXTPReportPaintManager
{
public:
	CXTPCustomDrawReportPaintManager(CCustomDrawReportDlg* pParent);
	virtual ~CXTPCustomDrawReportPaintManager();

	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);
	virtual int GetRowHeight(CDC* pDC, CXTPReportRow* pRow);

protected:
	CCustomDrawReportDlg* m_pParent;
};

#endif // !defined(AFX_XTPCUSTOMDRAWREPORTPAINTMANAGER_H__3D7A3DA9_B37E_4863_9B2F_D2F5191AB35B__INCLUDED_)
