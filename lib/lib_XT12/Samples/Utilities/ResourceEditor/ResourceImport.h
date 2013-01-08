// ResourceImport.h: interface for the CResourceImport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEIMPORT_H__9089E5BD_7F26_4649_AD8C_0007D8A6AECE__INCLUDED_)
#define AFX_RESOURCEIMPORT_H__9089E5BD_7F26_4649_AD8C_0007D8A6AECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResourceImport  
{
public:
	CResourceImport();
	virtual ~CResourceImport();

	BOOL Import(LPCTSTR lpszInput);

public:
	CXTPPropExchangeXMLNode* m_pResources;
	BOOL m_bDelete;
};

#endif // !defined(AFX_RESOURCEIMPORT_H__9089E5BD_7F26_4649_AD8C_0007D8A6AECE__INCLUDED_)
