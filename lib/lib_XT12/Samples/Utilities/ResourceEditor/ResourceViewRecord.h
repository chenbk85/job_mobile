// ResourceViewRecord.h: interface for the CResourceViewRecord class.
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

#if !defined(AFX_RESOURCEVIEWRECORD_H__3E6EE55C_19BE_4DAA_9441_B6D4FF6966E5__INCLUDED_)
#define AFX_RESOURCEVIEWRECORD_H__3E6EE55C_19BE_4DAA_9441_B6D4FF6966E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

CString GetResourceName(DWORD dwId, DWORD dwParent = 0);

enum ResourceType
{
	resString,
	resDialog,
	resMenu,
};

class CResourceViewRecord : public CXTPReportRecord
{
public:
	CResourceViewRecord(CString strResource, ResourceType resType, DWORD dwId, CString strValue);
	~CResourceViewRecord();

public:

	DWORD GetId();

public:
	CXTPPropExchangeXMLNode* m_pSection;
	ResourceType m_resType;

	CResourceViewRecord* m_pBaseRecord;
	
};


#endif // !defined(AFX_RESOURCEVIEWRECORD_H__3E6EE55C_19BE_4DAA_9441_B6D4FF6966E5__INCLUDED_)
