// XTPControlProgress.h : interface for the CXTPControlProgress class.
//
// This file is a part of the XTREME COMMANDBARS MFC class library.
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
#if !defined(__XTPCONTOLPROGRESS_H__)
#define __XTPCONTOLPROGRESS_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTPControl.h"
#include "Common/XTPWinThemeWrapper.h"

class CXTPProgressPaintManager;

//===========================================================================
// Summary:
//     CXTPControlProgressBase is base class for all progress objects
//===========================================================================
class _XTP_EXT_CLASS CXTPProgressBase
{
public:
	CXTPProgressBase();
	virtual ~CXTPProgressBase();

public:
	void SetRange(int nLower, int nUpper);
	void GetRange(int& nLower, int& nUpper) const;
	int GetPos() const;
	void SetPos(int nPos);

public:
	//----------------------------------------------------------------------
	// Summary:
	//     This method is called to get bounding rectangle of progressbar
	//----------------------------------------------------------------------
	virtual CRect GetProgressRect() = 0;

protected:
	//----------------------------------------------------------------------
	// Summary:
	//     This method is called to redraw progress bar
	//----------------------------------------------------------------------
	virtual void RedrawProgress() = 0;

	//----------------------------------------------------------------------
	// Summary:
	//     This method is called to retrieve pointer to CXTPProgressPaintManager
	//----------------------------------------------------------------------
	virtual CXTPProgressPaintManager* GetProgressPaintManager() const = 0;

protected:
	int m_nMin;     // Minimum
	int m_nMax;     // Maximum
	int m_nPos;     // Current position

};


//===========================================================================
// Summary:
//     CXTPControlProgress is a CXTPControl derived class.
//     It represents an progress control.
//===========================================================================
class _XTP_EXT_CLASS CXTPControlProgress : public CXTPControl, public CXTPProgressBase
{
	DECLARE_XTP_CONTROL(CXTPControlProgress)
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPControlProgress object
	//-----------------------------------------------------------------------
	CXTPControlProgress();

protected:
	//----------------------------------------------------------------------
	// Summary:
	//     This method is called to determine the size of the control.
	// Parameters:
	//     pDC - Pointer to a valid device context
	// Returns:
	//     Size of the control.
	//----------------------------------------------------------------------
	virtual CSize GetSize(CDC* pDC);

	//----------------------------------------------------------------------
	// Summary:
	//     This method is called to draw the control.
	// Parameters:
	//     pDC - Pointer to a valid device context.
	//----------------------------------------------------------------------
	virtual void Draw(CDC* pDC);

protected:
	virtual void RedrawProgress();

	virtual CXTPProgressPaintManager* GetProgressPaintManager() const;

	virtual CRect GetProgressRect();

protected:
	void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);
	void DoPropExchange(CXTPPropExchange* pPX);

};


class _XTP_EXT_CLASS CXTPProgressPaintManager
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPProgressPaintManager object
	// Parameters:
	//     pPaintManager - PaintManager of commandbars
	//-----------------------------------------------------------------------
	CXTPProgressPaintManager(CXTPPaintManager* pPaintManager);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPProgressPaintManager object, handles cleanup and deallocation
	//-----------------------------------------------------------------------
	virtual ~CXTPProgressPaintManager();

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     This method is called to draw progress
	// Parameters:
	//     pDC - Pointer to device context
	//     pProgressBar - Progress to draw
	//-----------------------------------------------------------------------
	virtual void DrawProgress(CDC* pDC, CXTPProgressBase* pProgressBar);

	//-------------------------------------------------------------------------
	// Summary:
	//     Recalculates metrics
	//-------------------------------------------------------------------------
	virtual void RefreshMetrics();

	//-----------------------------------------------------------------------
	// Summary:
	//     Returns parent paintmanager object
	//-----------------------------------------------------------------------
	CXTPPaintManager* GetPaintManager() const;

protected:
	CXTPWinThemeWrapper m_themeProgress;
	CXTPPaintManager* m_pPaintManager;

public:
	int m_cyProgress;
};

AFX_INLINE  int CXTPProgressBase::GetPos() const {
	return m_nPos;
}
AFX_INLINE CXTPPaintManager* CXTPProgressPaintManager::GetPaintManager() const {
	return m_pPaintManager;
}


#endif //#if !defined(__XTPCONTOLPROGRESS_H__)
