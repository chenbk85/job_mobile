// ControlFavorites.h
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

#if !defined(_CONTROLFAVORITES_H__)
#define _CONTROLFAVORITES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CControlFavorites : public CXTPControlButton
{
public:
	CControlFavorites(LPCTSTR strRootDir = 0);
protected:
	virtual void OnCalcDynamicSize(DWORD dwMode);
	virtual BOOL IsCustomizeDragOverAvail(CXTPCommandBar* pCommandBar, CPoint point, DROPEFFECT& dropEffect);


	virtual void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);
	void DoPropExchange(CXTPPropExchange* pPX);


	DECLARE_XTP_CONTROL(CControlFavorites)

private:
	CString m_strRootDir;
};

#endif
