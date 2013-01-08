// XTPReportRecordItemProgress.h: interface for the CXTPReportRecordItemProgress class.
//
// This file is a part of the XTREME REPORTCONTROL MFC class library.
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

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPREPORTRECORDITEMPROGRESS_H__)
#define __XTPREPORTRECORDITEMPROGRESS_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\Source\ReportControl\XTPReportRecordItemText.h"

//===========================================================================
// Summary:
//     This Class represents a progress bar cell and inherits basic functionality
//     from CXTPReportRecordItemText class.
//     You create a progress record item by calling a constructor with one
//     parameter - text string. You create progress bars by subsequent calls to
//     AddProgress method.
// See Also: CXTPReportRecordItem, AddProgress
//===========================================================================
class CXTPReportRecordItemProgress : public CXTPReportRecordItemText
{
	DECLARE_SERIAL(CXTPReportRecordItemProgress)
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Creates a record progress item.
	// Parameters:
	//     szText - A text value for the item.
	//-----------------------------------------------------------------------
	CXTPReportRecordItemProgress(LPCTSTR szText = _T(""));

	//-----------------------------------------------------------------------
	// Summary:
	//     Creates a record progress item.
	// Parameters:
	//     szText - A text value for the item.
	//-----------------------------------------------------------------------
	CXTPReportRecordItemProgress(LPCTSTR szText, COLORREF clrProgress, int nWidth, int nLower, int nUpper, int nStep, int nPos);

	//-----------------------------------------------------------------------
	// Summary:
	//     Sets progress color.
	// Parameters:
	//     clrProgress - progress color.
	//-----------------------------------------------------------------------
	void SetProgressColor(COLORREF clrProgress);

	//-----------------------------------------------------------------------
	// Summary:
	//     Gets progress color.
	// Returns:
	//     The progress color.
	//-----------------------------------------------------------------------
	COLORREF GetProgressColor();

	//-----------------------------------------------------------------------
	// Summary:
	//     Sets progress width.
	// Parameters:
	//     nWidth - progress width.
	//-----------------------------------------------------------------------
	void SetProgressWidth(int nWidth);

	//-----------------------------------------------------------------------
	// Summary:
	//     Gets progress width.
	// Returns:
	//     The progress width.
	//-----------------------------------------------------------------------
	int GetProgressWidth();

	//-----------------------------------------------------------------------
	// Summary:
	//     Sets progress range.
	// Parameters:
	//     nLower - progress lower limit.
	//     nUpper - progress upper limit.
	//-----------------------------------------------------------------------
	void SetProgressRange(int nLower, int nUpper);

	//-----------------------------------------------------------------------
	// Summary:
	//     Gets progress range.
	// Parameters:
	//     nLower - progress lower limit.
	//     nUpper - progress upper limit.
	//-----------------------------------------------------------------------
	void GetProgressRange(int& nLower, int& nUpper);

	//-----------------------------------------------------------------------
	// Summary:
	//     Sets progress step.
	// Parameters:
	//     nStep - progress step.
	//-----------------------------------------------------------------------
	void SetProgressStep(int nWidth);

	//-----------------------------------------------------------------------
	// Summary:
	//     Gets progress step.
	// Returns:
	//     The progress step.
	//-----------------------------------------------------------------------
	int GetProgressStep();

	//-----------------------------------------------------------------------
	// Summary:
	//     Sets the progress position.
	// Parameters:
	//     nPos - progress position.
	// Returns:
	//     The previous position of the progress.
	//-----------------------------------------------------------------------
	int SetProgressPos(int nPos);

	//-----------------------------------------------------------------------
	// Summary:
	//     Returns the progress position.
	// Returns:
	//     Progress position.
	//-----------------------------------------------------------------------
	int GetProgressPos();

	//-----------------------------------------------------------------------
	// Summary:
	//     Returns the progress position in percents.
	// Returns:
	//     Progress position in percents.
	//-----------------------------------------------------------------------
	int GetProgressPosPercent();

	//-----------------------------------------------------------------------
	// Summary:
	//     Advances the progress position by the specified increment.
	// Parameters:
	//     nOffset - amount to advance the position.
	// Returns:
	//     The previous position of the progress.
	//-----------------------------------------------------------------------
	int OffsetProgressPos(int nOffset);

	//-----------------------------------------------------------------------
	// Summary:
	//     Advances the progress position by the step increment.
	// Returns:
	//     The previous position of the progress.
	//-----------------------------------------------------------------------
	int StepProgressPos();

	//-----------------------------------------------------------------------
	// Summary:
	//     Should be overridden by descendants for drawing itself.
	// Parameters:
	//     pDrawArgs - structure which contain drawing arguments.
	//     pMetrics - structure which contain metrics of the item.
	//-----------------------------------------------------------------------
	virtual void OnDrawCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to Store/Load a report record item
	//     using the specified data object.
	// Parameters:
	//     pPX - Source or destination CXTPPropExchange data object reference.
	//-----------------------------------------------------------------------
//	virtual void DoPropExchange(CXTPPropExchange* pPX);


protected:
	COLORREF m_clrProgress; // progress color.
	int m_nProgressWidth;   // progress width.
	int m_nProgressLower;   // progress lower limit.
	int m_nProgressUpper;   // progress upper limit.
	int m_nProgressStep;    // progress step increment.
	int m_nProgressPos;     // current progress position.
};

#endif //#if !defined(__XTPREPORTRECORDITEMPROGRESS_H__)
