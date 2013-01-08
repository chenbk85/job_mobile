// ResourceImport.cpp: implementation of the CResourceImport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResourceImport.h"
#include "ResourceExport.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResourceImport::CResourceImport()
{
	m_pResources = NULL;
	m_bDelete = TRUE;
}

CResourceImport::~CResourceImport()
{
	if (m_bDelete)
	{
		SAFE_DELETE(m_pResources);
	}

}

#pragma pack(push, 1)

typedef struct
{
	WORD dlgVer;
	WORD signature;
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	WORD cDlgItems;
	short x;
	short y;
	short cx;
	short cy;
} DLGTEMPLATEEX;

typedef struct
{
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	short x;
	short y;
	short cx;
	short cy;
	DWORD id;
} DLGITEMTEMPLATEEX;

#pragma pack(pop)

AFX_INLINE int REPLACEW_S(LPWSTR strReplace, LPCWSTR lpszOld, LPCWSTR lpszNew)
{
	int nOldLength = (strReplace == NULL) ? 0 : (int)wcslen(strReplace);
	int nSourceLen = (lpszOld == NULL) ? 0 : (int)wcslen(lpszOld);

	if (nSourceLen == 0 || nOldLength == 0)
		return 0;

	int nReplacementLen = (lpszNew == NULL) ? 0 : (int)wcslen(lpszNew);

	// loop once to figure out the size of the result string
	int nCount = 0;
	LPWSTR lpszStart = strReplace;
	LPWSTR lpszTarget;

	while ((lpszTarget = wcsstr(lpszStart, lpszOld)) != NULL)
	{
		nCount++;
		lpszStart = lpszTarget + nSourceLen;
	}


	// if any changes were made, make them
	if (nCount > 0)
	{
		int nNewLength = nOldLength + (nReplacementLen-nSourceLen)*nCount;
		//ASSERT(nNewLength <= nOldLength); // not implemented

		lpszStart = strReplace;

		// loop again to actually do the work
		while ((lpszTarget = wcsstr(lpszStart, lpszOld)) != NULL)
		{
			int nBalance = nOldLength - int(lpszTarget - strReplace + nSourceLen);
			MEMMOVE_S(lpszTarget + nReplacementLen, lpszTarget + nSourceLen,
				nBalance * sizeof(WORD));
			MEMCPY_S(lpszTarget, lpszNew, nReplacementLen*sizeof(WORD));
			lpszStart = lpszTarget + nReplacementLen;
			lpszStart[nBalance] = '\0';
			nOldLength += (nReplacementLen - nSourceLen);
		}

		ASSERT(strReplace[nNewLength] == '\0');
	}

	return nCount;
}

void PreformatString(LPWSTR strValue)
{
	REPLACEW_S(strValue, L"\\", L"\\\\");
	REPLACEW_S(strValue, L"\n", L"\\n");
	REPLACEW_S(strValue, L"\r", L"\\r");
	REPLACEW_S(strValue, L"\t", L"\\t");
}



AFX_INLINE ULONG_PTR AlignDWord(ULONG_PTR uLong)  {  return ((uLong + 3) & ~3); }
		


void PX_StringW(CXTPPropExchange* pPX, LPCTSTR pszPropName, LPWSTR str, LPWSTR lpDefault = 0)
{
	if (!str || str[0] == 0)
		return;

	WORD dwLength = (WORD)wcslen(str);
		
	LPWSTR lpwString = new WCHAR[(dwLength + 1) * 2 * 2];
	
	memcpy(lpwString, str, (dwLength + 1) * 2);
	PreformatString(lpwString);

	BSTR bstrValue = (BSTR)lpwString;
	PX_Bstr(pPX, pszPropName, bstrValue, (BSTR)lpDefault);

	delete[] lpwString;
}


void PutDialogTemplate(CXTPPropExchange* pPX, DLGTEMPLATE* pTemplate)
{
	DLGTEMPLATEEX* pTemplateEx = (DLGTEMPLATEEX*)pTemplate;
	BOOL bTemplateEx = pTemplateEx->signature == 0xFFFF;
	int style, styleex, x, y, cx, cy, id;
	LPWORD pItems;
	
	if (bTemplateEx)
	{
		style = pTemplateEx->style;
		styleex = pTemplateEx->exStyle;
		
		x = pTemplateEx->x;
		y = pTemplateEx->y;
		cx = pTemplateEx->cx;
		cy = pTemplateEx->cy;

		pItems = (LPWORD)((LPBYTE)pTemplate + sizeof(DLGTEMPLATEEX));
	}
	else
	{
		style = pTemplate->style;
		styleex = pTemplate->dwExtendedStyle;
		
		x = pTemplate->x;
		y = pTemplate->y;
		cx = pTemplate->cx;
		cy = pTemplate->cy;		
		
		pItems = (LPWORD)((LPBYTE)pTemplate + sizeof(DLGTEMPLATE));
	}
		
	ASSERT(*pItems == 0);
	ASSERT(*(pItems + 1) == 0);
		
	pItems += 2;
	if (pItems)
	{
		PX_StringW(pPX, _T("caption"), (LPWSTR)pItems);
		pItems += wcslen((LPWSTR)pItems);
	}
	pItems += 1;
		
	if (style & DS_SETFONT)
	{
		int nHeight = *pItems;
		PX_Int(pPX, _T("fontsize"), nHeight, 8);

		pItems += bTemplateEx? 3: 1;

		PX_StringW(pPX, _T("fontface"), (LPWSTR)pItems, L"MS Sans Serif");
		
		pItems += wcslen((LPWSTR)pItems) + 1;			
	}
	

	CString strPos;
	strPos.Format(_T("%i, %i, %i, %i"), x, y, cx, cy);

	PX_Int(pPX, _T("style"), style);
	PX_Int(pPX, _T("styleex"), styleex, 0);
	PX_String(pPX, _T("position"), strPos);

	pItems = LPWORD((LPBYTE)pTemplate + AlignDWord((LPBYTE)pItems - (LPBYTE)pTemplate));

	CXTPPropExchangeEnumeratorPtr secControl(pPX->GetEnumerator(_T("control")));
	POSITION pos = secControl->GetPosition(32000);

	int nCount = bTemplateEx? pTemplateEx->cDlgItems:  pTemplate->cdit;

	for (int i = 0; i < nCount; i++)
	{
		DLGITEMTEMPLATE* pItemTemplate = (DLGITEMTEMPLATE*)pItems;
		DLGITEMTEMPLATEEX* pItemTemplateEx = (DLGITEMTEMPLATEEX*)pItems;

		CXTPPropExchangeSection sec(secControl->GetNext(pos));	

		if (bTemplateEx)
		{
			style = pItemTemplateEx->style;
			styleex = pItemTemplateEx->exStyle;
			
			x = pItemTemplateEx->x;
			y = pItemTemplateEx->y;
			cx = pItemTemplateEx->cx;
			cy = pItemTemplateEx->cy;
			id = pItemTemplateEx->id;

			pItems = LPWORD((LPBYTE)pItemTemplate + sizeof(DLGITEMTEMPLATEEX));
		}
		else
		{			
			style = pItemTemplate->style;
			styleex = pItemTemplate->dwExtendedStyle;
			
			x = pItemTemplate->x;
			y = pItemTemplate->y;
			cx = pItemTemplate->cx;
			cy = pItemTemplate->cy;
			id = pItemTemplate->id;

			pItems = LPWORD((LPBYTE)pItemTemplate + sizeof(DLGITEMTEMPLATE));
		}

		CString strPos;
		strPos.Format(_T("%i, %i, %i, %i"), x, y, cx, cy);

		if (id == 65535 || id == -1) id = 0;
		
		PX_Int(&sec, _T("id"), id, 0);
		
		CString strClass;

		if (*pItems == 0xFFFF)
		{
			switch (*(pItems + 1))
			{
			case 0x0080: strClass = _T("BUTTON"); break;
			case 0x0081: strClass = _T("EDIT"); break;
			case 0x0082: strClass = _T("STATIC"); break;
			case 0x0083: strClass = _T("LISTBOX"); break;
			case 0x0084: strClass = _T("SCROLLBAR"); break;
			case 0x0085: strClass = _T("COMBOBOX"); break;
			}

			pItems += 2;
		}
		else
		{
			strClass  = (LPWSTR)pItems;
			pItems += strClass.GetLength() + 1;
		}
		PX_String(&sec, _T("class"), strClass, _T("STATIC"));

		if (*pItems == 0xFFFF)
		{
			int nResource = *(pItems + 1);
			PX_Int(&sec, _T("resource"), nResource);
			
			pItems += 2;
		}
		else
		{
			PX_StringW(&sec, _T("caption"), (LPWSTR)pItems);
			pItems += wcslen((LPWSTR)pItems) + 1;
		}
		

		PX_Int(&sec, _T("style"), style, WS_CHILD | WS_VISIBLE | WS_GROUP);
		PX_Int(&sec, _T("styleex"), styleex, 0);
		PX_String(&sec, _T("position"), strPos);

		ASSERT(*pItems == 0);
		pItems += 1;

		pItems = LPWORD((LPBYTE)pItemTemplate + AlignDWord((LPBYTE)pItems - (LPBYTE)pItemTemplate));
	}

}


void PutMenuItems(CXTPPropExchange* pPX, MENUITEMTEMPLATE*& pItem)
{
	CXTPPropExchangeEnumeratorPtr secMenuItem(pPX->GetEnumerator(_T("menuitem")));
	POSITION posMenuItem = secMenuItem->GetPosition(32000);
	
	
	while (TRUE)
	{
		CXTPPropExchangeSection sec(secMenuItem->GetNext(posMenuItem));
		
		BOOL bPopup = (pItem->mtOption & MF_POPUP) != 0;
		BOOL bEnd = (pItem->mtOption & MF_END) != 0;
		
		int nID = !bPopup? (int)pItem->mtID: 0;
		PX_Int(&sec, _T("id"), nID, 0);
		
		
		int nCaptionSize = (int)wcslen(bPopup? pItem->mtString - 1: pItem->mtString);
		
		WCHAR* pCaption = !bPopup? pItem->mtString: (WCHAR*)&pItem->mtID;
		
		if (pCaption)
		{
			PX_StringW(&sec, _T("caption"), pCaption);
		}
		
		pItem = (MENUITEMTEMPLATE*)((LPBYTE)pItem + (pItem->mtOption & MF_POPUP? sizeof(WORD) * 2: sizeof(WORD) * 3) + (nCaptionSize) * 2);

		if (bPopup)
		{
			PutMenuItems(&sec, pItem);

		}
		
		if (bEnd) break;
	}
}

struct PROPEXCHANGEENUM
{
	CXTPPropExchangeEnumerator* pEnumerator;
	POSITION pos;
}; 

BOOL CALLBACK EnumResStringProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam)
{
	PROPEXCHANGEENUM* pxEnum = (PROPEXCHANGEENUM*)lParam;
	ASSERT(pxEnum);
	if (!pxEnum)
		return FALSE;

	HRSRC hRsrc = FindResource(hModule, lpszName, lpszType);
	if (!hRsrc)
		return FALSE;
	
	HGLOBAL hRsrcData = LoadResource(hModule, hRsrc);
	LPWSTR lpszData = (LPWSTR)LockResource(hRsrcData);

	for (int i = 0; i < 16; i++)
	{
		if (*lpszData)
		{
			CXTPPropExchangeSection sec(pxEnum->pEnumerator->GetNext(pxEnum->pos));

			WORD dwLength = *lpszData;
		
			LPWSTR lpwString = new WCHAR[(dwLength + 1) * 2 * 2];
			memcpy(lpwString, lpszData + 1, dwLength * 2);
			lpwString[dwLength] = 0;
			PreformatString(lpwString);


			BSTR bstrString = (BSTR)lpwString;
			int nResource = (((UINT)(UINT_PTR)lpszName - 1) * 16 + i);
		
			PX_Int(&sec, _T("id"), nResource);	
			PX_Bstr(&sec, _T("value"), bstrString, 0);	

			delete[] lpwString;

			lpszData = lpszData + dwLength + 1;
		}
		else
		{
			lpszData += 1;
		}
	}

	return TRUE;
}

void ConvertStrings(HMODULE hModule, CXTPPropExchange* pPX)
{
	PROPEXCHANGEENUM pxenum;
	pxenum.pEnumerator = pPX->GetEnumerator(_T("string"));
	pxenum.pos = pxenum.pEnumerator->GetPosition(32000);

	::EnumResourceNames(hModule, RT_STRING, &EnumResStringProc, (LONG_PTR)&pxenum);

	delete pxenum.pEnumerator;
}

BOOL CALLBACK EnumResMenuProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam)
{
	PROPEXCHANGEENUM* pxEnum = (PROPEXCHANGEENUM*)lParam;
	ASSERT(pxEnum);
	if (!pxEnum)
		return FALSE;

	HRSRC hRsrc = FindResource(hModule, lpszName, lpszType);
	if (!hRsrc)
		return FALSE;
	
	HGLOBAL hRsrcData = LoadResource(hModule, hRsrc);
	LPBYTE lpszData = (LPBYTE)LockResource(hRsrcData);

	CXTPPropExchangeSection sec(pxEnum->pEnumerator->GetNext(pxEnum->pos));

	int nResource = (UINT)(UINT_PTR)lpszName;
	PX_Int(&sec, _T("id"), nResource);	

	lpszData += 4;
	MENUITEMTEMPLATE* pItem = (MENUITEMTEMPLATE*)lpszData;

	PutMenuItems(&sec, pItem);				

	return TRUE;
}

void ConvertMenus(HMODULE hModule, CXTPPropExchange* pPX)
{
	PROPEXCHANGEENUM pxenum;
	pxenum.pEnumerator = pPX->GetEnumerator(_T("menu"));
	pxenum.pos = pxenum.pEnumerator->GetPosition(32000);

	::EnumResourceNames(hModule, RT_MENU, &EnumResMenuProc, (LONG_PTR)&pxenum);

	delete pxenum.pEnumerator;
}

BOOL CALLBACK EnumResDialogProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam)
{
	PROPEXCHANGEENUM* pxEnum = (PROPEXCHANGEENUM*)lParam;
	ASSERT(pxEnum);
	if (!pxEnum)
		return FALSE;

	HRSRC hRsrc = FindResource(hModule, lpszName, lpszType);
	if (!hRsrc)
		return FALSE;
	
	HGLOBAL hRsrcData = LoadResource(hModule, hRsrc);
	LPBYTE lpszData = (LPBYTE)LockResource(hRsrcData);

	CXTPPropExchangeSection sec(pxEnum->pEnumerator->GetNext(pxEnum->pos));

	int nResource = (UINT)(UINT_PTR)lpszName;
	PX_Int(&sec, _T("id"), nResource);	

	DLGTEMPLATE* pItem = (DLGTEMPLATE*)lpszData;
	PutDialogTemplate(&sec, pItem);

	return TRUE;
}

void ConvertDialogs(HMODULE hModule, CXTPPropExchange* pPX)
{
	PROPEXCHANGEENUM pxenum;
	pxenum.pEnumerator = pPX->GetEnumerator(_T("dialog"));
	pxenum.pos = pxenum.pEnumerator->GetPosition(32000);

	::EnumResourceNames(hModule, RT_DIALOG, &EnumResDialogProc, (LONG_PTR)&pxenum);

	delete pxenum.pEnumerator;
}



BOOL CResourceImport::Import(LPCTSTR lpszFileName)
{
	HMODULE hModule =  LoadLibrary(lpszFileName);
	if (!hModule)
		return FALSE;

	m_pResources = new CXTPPropExchangeXMLNode(FALSE, 0, _T("resource"));
	if (!m_pResources->OnBeforeExchange())
		return FALSE;

	long wLanguage = CXTPResourceManager::GetResourceLanguage(hModule);
	if (wLanguage == 0)
		return FALSE;

	XTP_RESOURCEMANAGER_LANGINFO* lan = CXTPResourceManager::GetLanguageInfo(wLanguage);
	if (!lan)
		return FALSE;

	m_pResources->SetEncoding(lan->lpszEncoding);

	CString strCaption(lan->lpszCaption);
	PX_String(m_pResources, _T("Language"), strCaption);		
	PX_Long(m_pResources, _T("LANGID"), wLanguage);

		
	ConvertStrings(hModule, m_pResources);
	ConvertMenus(hModule, m_pResources);
	ConvertDialogs(hModule, m_pResources);

	FreeLibrary(hModule);
	
	return TRUE;
}
