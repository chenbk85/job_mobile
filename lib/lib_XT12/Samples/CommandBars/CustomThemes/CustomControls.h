// CustomControls.h
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

#if !defined(AFX_CUSTOMCONTROLS_H__)
#define AFX_CUSTOMCONTROLS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MainFrm.h"

class CControlButtonLine : public CXTPControlButton
{
	DECLARE_XTP_CONTROL(CControlButtonLine)
public:
	CControlButtonLine(double dWidth = 0);
protected:
	virtual CSize GetSize(CDC* pDC);
	virtual void Draw(CDC* pDC);
	virtual void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);
	virtual void DoPropExchange(CXTPPropExchange* pPX);

private:
	double m_dWidth;
};

class CControlButtonStyle : public CXTPControlButton
{
	DECLARE_XTP_CONTROL(CControlButtonStyle)
public:
	CControlButtonStyle(int nStyle = 0);
protected:
	virtual CSize GetSize(CDC* pDC);
	virtual void Draw(CDC* pDC);
	virtual void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);
	virtual void DoPropExchange(CXTPPropExchange* pPX);

private:
	int m_nStyle;
};


class CControlButtonArrow : public CXTPControlButton
{
	DECLARE_XTP_CONTROL(CControlButtonArrow)
public:
	CControlButtonArrow(int nStyle = 0);
protected:
	virtual CSize GetSize(CDC* pDC);
	virtual void Draw(CDC* pDC);
	virtual void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);
	virtual void DoPropExchange(CXTPPropExchange* pPX);

private:
	int m_nStyle;
};

class CControlComboBoxEditEx : public CXTMaskEditT<CXTPControlComboBoxEditCtrl>
{
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

class CControlComboBoxEx: public CXTPControlComboBox
{
	DECLARE_XTP_CONTROL(CControlComboBoxEx)
public:
	CXTPControlComboBoxEditCtrl* CreateEditControl()
	{
		return new CControlComboBoxEditEx();
	}
};


class CControlComboBoxPopup: public CXTPControlComboBox
{
	DECLARE_XTP_CONTROL(CControlComboBoxPopup)
public:
	CString GetListBoxText() const;
};


class CControlComboBoxCustomDraw: public CXTPControlFontComboBox
{
	DECLARE_XTP_CONTROL(CControlComboBoxCustomDraw)
public:

	CControlComboBoxCustomDraw(CXTPCommandBars* pCommandBars = NULL)
	{
		GetCommandBar()->SetCommandBars(pCommandBars); // Require to find Site.
		ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		((CXTPControlFontComboBoxList*)GetCommandBar())->EnumFontFamiliesEx(1);
	}

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

class CControlComboBoxDatePicker : public CXTPControlComboBox
{
	DECLARE_XTP_CONTROL(CControlComboBoxDatePicker);

public:
	CControlComboBoxDatePicker();
	~CControlComboBoxDatePicker();

public:
	void OnKillFocus();

	BOOL OnHookKeyDown(UINT nChar, LPARAM lParam);

	void SetDate(COleDateTime& dt);
	const COleDateTime& GetDate() const;

protected:
	COleDateTime m_dt;
};

#endif //AFX_CUSTOMCONTROLS_H__
