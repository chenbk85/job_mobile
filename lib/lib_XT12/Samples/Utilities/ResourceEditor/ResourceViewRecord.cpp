// ResourceViewRecord.cpp: implementation of the CResourceViewRecord class.
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
#include "ResourceEditor.h"
#include "ResourceViewRecord.h"

#include <XTPResource.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DECLARE_CODEJOCK_RESOURCE(Module, nIDResource) _T(Module), _T(#nIDResource), nIDResource, 0,
#define DECLARE_CODEJOCK_RESOURCE_CHILD(Module, nIDResourceParent, nIDResource) _T(Module), _T(#nIDResource), nIDResource, nIDResourceParent,

const struct 
{
	LPCTSTR lpszModule;
	LPCTSTR lpszResourceName;
	DWORD dwResource;
	DWORD dwResourceParent;
} 
Resources[] = 
{
	#include "ResourceViewRecord.inl" 
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CString GetResourceName(DWORD dwId, DWORD dwParent)
{
	if ((dwId > 1000) || (dwParent != 0))
	{
		for (int i = 0; i < _countof(Resources); i++)
		{
			if ((Resources[i].dwResource == dwId) && 
				(dwParent == 0 || dwId > 1000 || dwParent == Resources[i].dwResourceParent))
			{
				return Resources[i].lpszResourceName;
			}
			
		}
	}
	
	CString str;
	str.Format(_T("%i"), dwId);

	return str;	
}

CString GetResourceModule(DWORD dwId)
{
	for (int i = 0; i < _countof(Resources); i++)
	{
		ASSERT(Resources[i].dwResource > 1000 || Resources[i].dwResourceParent != 0);

		if (Resources[i].dwResource == dwId && Resources[i].dwResourceParent == 0)
		{
			return Resources[i].lpszModule;
		}

	}

	return _T("");	
}
 

CResourceViewRecord::CResourceViewRecord(CString strResource, ResourceType resType, DWORD dwId, CString strValue)
{
	AddItem(new CXTPReportRecordItemText(GetResourceModule(dwId)));
	CXTPReportRecordItem* pItem = AddItem(new CXTPReportRecordItemNumber(dwId));
	
	if (dwId != 0)
	{
		pItem->SetTooltip(GetResourceName(dwId));
	}
	
	CString strOriginal;
	if (resType == resString) XTPResourceManager()->LoadString(&strOriginal, dwId);
	CXTPPropExchangeXMLNode::PreformatString(strOriginal, FALSE);
	
	AddItem(new CXTPReportRecordItemText(strOriginal));
	AddItem(new CXTPReportRecordItemText(strValue));
	
	pItem = AddItem(new CXTPReportRecordItemText(strResource));
	pItem->SetIconIndex(resType == resString ? 6: resType == resMenu? 5: resType == resDialog? 3: -1);

	m_pSection = NULL;	
	m_resType = resType;
	m_pBaseRecord = NULL;
}

CResourceViewRecord::~CResourceViewRecord()
{
	CMDTARGET_RELEASE(m_pSection); 
	
}

DWORD CResourceViewRecord::GetId()
{
	return (DWORD)((CXTPReportRecordItemNumber*)GetItem(1))->GetValue();
}
