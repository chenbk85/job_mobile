// MessageRecord.h: interface for the CMessageRecord class.
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

#if !defined(AFX_MESSAGERECORD_H__86DCA43B_6A9C_40CD_B814_A625E68850CA__INCLUDED_)
#define AFX_MESSAGERECORD_H__86DCA43B_6A9C_40CD_B814_A625E68850CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPReportRecordItemProgress.h"

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying group of checkboxes.
class CMessageRecordItemCheckGroup : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemCheckGroup)
public:
	// Default constructor.
	CMessageRecordItemCheckGroup();

	// Constructs record item with the initial value.
	CMessageRecordItemCheckGroup(unsigned int unCheckboxes, ULONG ulValue = 0);

	// Provides custom group captions depending on the item value.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on item value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Provides custom records comparison by this item based on item value, 
	// instead of based on captions.
	int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Gets radio buttons number.
	unsigned int GetControlsNumber()
	{
		return m_unCheckboxes;
	}

	// Sets new radio buttons number.
	void SetControlsNumber(unsigned int unCheckboxes)
	{
		m_unCheckboxes = unCheckboxes;
	}

	// Gets item value.
	ULONG GetValue()
	{
		return m_ulValue;
	}

	// Sets new item value.
	void SetValue(ULONG ulValue)
	{
		m_ulValue = ulValue;
	}

	// Sets a bit by the specified bit number.
	void SetBit(unsigned int unBitNumber)
	{
		m_ulValue |= (1 << unBitNumber);
	}

	// Clears a bit by the specified bit number.
	void ClearBit(unsigned int unBitNumber)
	{
		m_ulValue &= ~(1 << unBitNumber);
	}

	// Toggles a bit by the specified bit number.
	void ToggleBit(unsigned int unBitNumber)
	{
		if(m_ulValue & (1 << unBitNumber))
			m_ulValue &= ~(1 << unBitNumber);
		else
			m_ulValue |= (1 << unBitNumber);
	}

	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	unsigned int m_unCheckboxes; // number of checkboxes
	ULONG m_ulValue; // checkboxes value
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying group of radio buttons.
class CMessageRecordItemRadioGroup : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemRadioGroup)
public:
	// Default constructor.
	CMessageRecordItemRadioGroup();

	// Constructs record item with the initial value.
	CMessageRecordItemRadioGroup(unsigned int unRadioButtons, ULONG ulValue = 0);

	// Provides custom group captions depending on the item value.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on item value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Provides custom records comparison by this item based on item value, 
	// instead of based on captions.
	int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Gets radio buttons number.
	unsigned int GetControlsNumber()
	{
		return m_unRadioButtons;
	}

	// Sets new radio buttons number.
	void SetControlsNumber(unsigned int unRadioButtons)
	{
		m_unRadioButtons = unRadioButtons;
	}

	// Gets item value.
	ULONG GetValue()
	{
		return m_ulValue;
	}

	// Sets new item value.
	void SetValue(ULONG ulValue)
	{
		m_ulValue = ulValue;
	}

	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	unsigned int m_unRadioButtons; // number of radio buttons
	ULONG m_ulValue; // radio buttons selection value
};

//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class CMessageRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(CMessageRecord)
public:
	
	// Construct record object using empty values on each field
	CMessageRecord();
	
	// Construct record object from detailed values on each field
	CMessageRecord(CString strName, unsigned int unCheckboxes, unsigned int unCheckValue,
		unsigned int unRadioButtons, unsigned int unRadioValue,
		CString strProgressText, COLORREF clrProgress, int nProgressWidth, int nProgressLower, int nProgressUpper, int nProgressStep, int nProgressPos);

	// Clean up internal objects
	virtual ~CMessageRecord();

	// Create record fields using empty values
	virtual void CreateItems();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

	virtual void DoPropExchange(CXTPPropExchange* pPX);

	CMessageRecordItemCheckGroup* m_pItemAttr1;	// Contains message attribute 1.
	CMessageRecordItemRadioGroup* m_pItemAttr2;	// Contains message attribute 2.
	CXTPReportRecordItemProgress* m_pItemAttr3;	// Contains message attribute 3.
};

#endif // !defined(AFX_MESSAGERECORD_H__86DCA43B_6A9C_40CD_B814_A625E68850CA__INCLUDED_)
