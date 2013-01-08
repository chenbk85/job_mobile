// ControlFavorites.cpp: implementation of the CControlFavorites class.
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
#include "resource.h"
#include "ControlFavorites.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_XTP_CONTROL(CControlFavorites, CXTPControlButton)


CControlFavorites::CControlFavorites(LPCTSTR strRootDir)
{
	m_strRootDir = strRootDir;
}

void CControlFavorites::Copy(CXTPControl* pControl, BOOL bRecursive)
{
	ASSERT(DYNAMIC_DOWNCAST(CControlFavorites, pControl));
	CXTPControlButton::Copy(pControl, bRecursive);

	m_strRootDir = ((CControlFavorites*)pControl)->m_strRootDir;
}

void CControlFavorites::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPControlButton::DoPropExchange(pPX);

	PX_String(pPX, _T("RootDir"), m_strRootDir);
}

void CControlFavorites::OnCalcDynamicSize(DWORD /*dwMode*/)
{
	if (GetParent()->GetType() !=xtpBarTypePopup)
		return;

	ASSERT(m_pControls->GetAt(m_nIndex) == this);
	while (m_nIndex + 1 < m_pControls->GetCount())
	{
		CXTPControl* pControl = m_pControls->GetAt(m_nIndex + 1);
		if (
			pControl->GetID() == ID_FAVORITE_LINK ||
			pControl->GetID() == ID_FAVORITE_FOLDER)
		{
			m_pControls->Remove(pControl);
		}
		else break;
	}

	if (m_pParent->IsCustomizeMode())
	{
		m_dwHideFlags = 0;
		return;
	}

	m_dwHideFlags |= xtpHideGeneric;

	//CString         strPath2;
	CString         str;
	WIN32_FIND_DATA wfd;
	HANDLE          h;
	int             nPos = 0;
	int             nEndPos = 0;

	#define INTERNET_MAX_PATH_LENGTH 2048

	TCHAR           buf[INTERNET_MAX_PATH_LENGTH];
	CStringArray    astrFavorites;
	CStringArray    astrFavoritesUrl;
	CStringArray    astrDirs;

	// make sure there's a trailing backslash
	if(m_strRootDir[m_strRootDir.GetLength() - 1] != _T('\\'))
		m_strRootDir += _T('\\');

	int nStartPos = m_nIndex + 1;

	// now scan the directory, first for .URL files and then for subdirectories
	// that may also contain .URL files
	h = FindFirstFile(m_strRootDir + _T("*.*"), &wfd);
	if(h != INVALID_HANDLE_VALUE)
	{
		nEndPos = nStartPos;
		do
		{
			if((wfd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0)
			{
				str = wfd.cFileName;
				if(str.Right(4).CompareNoCase(_T(".url")) == 0)
				{
					// an .URL file is formatted just like an .INI file, so we can
					// use GetPrivateProfileString() to get the information we want
					::GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),
						_T(""), buf, INTERNET_MAX_PATH_LENGTH,
						m_strRootDir + str);
					str = str.Left(str.GetLength() - 4);

					// scan through the array and perform an insertion sort
					// to make sure the menu ends up in alphabetic order
					for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
					{
						if(str.CompareNoCase(astrFavorites[nPos]) < 0)
							break;
					}
					astrFavorites.InsertAt(nPos, str);
					astrFavoritesUrl.InsertAt(nPos, buf);
					++nEndPos;
				}
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);

		BOOL bBeginGroup  = GetBeginGroup();

		// Now add these items to the menu
		for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
		{
			CXTPControlButton* pControl = (CXTPControlButton*)m_pControls->Add(xtpControlButton, ID_FAVORITE_LINK, astrFavoritesUrl[nPos], nPos, TRUE);
			pControl->SetCaption(astrFavorites[nPos]);
			pControl->SetTooltip(astrFavoritesUrl[nPos]);
			pControl->SetDescription(astrFavoritesUrl[nPos]);
			pControl->SetFlags(xtpFlagManualUpdate);
			pControl->SetStyle(xtpButtonIconAndCaption);
		}


		// now that we've got all the .URL files, check the subdirectories for more
		int nLastDir = 0;
		h = FindFirstFile(m_strRootDir + _T("*.*"), &wfd);
		ASSERT(h != INVALID_HANDLE_VALUE);
		do
		{
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// ignore the current and parent directory entries
				if(lstrcmp(wfd.cFileName, _T(".")) == 0 || lstrcmp(wfd.cFileName, _T("..")) == 0)
					continue;

				for(nPos = 0 ; nPos < nLastDir ; ++nPos)
				{
					if(astrDirs[nPos].CompareNoCase(wfd.cFileName) > 0)
						break;
				}

				CXTPControlPopup* pControl = (CXTPControlPopup*)m_pControls->Add(xtpControlButtonPopup, ID_FAVORITE_FOLDER, _T(""), nStartPos + nPos, TRUE);
				CXTPControls* pChildControls = pControl->GetCommandBar()->GetControls();

				pChildControls->Add(new CControlFavorites(m_strRootDir + wfd.cFileName), 0);
				pControl->SetCaption(wfd.cFileName);
				pControl->SetFlags(xtpFlagManualUpdate);

				astrDirs.InsertAt(nPos, wfd.cFileName);
				++nLastDir;
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);
		
		if (nEndPos != nStartPos || nLastDir != 0)
		{
			CXTPControl* pControlFirst = m_pControls->GetAt(m_nIndex + 1);
			if (pControlFirst) pControlFirst->SetBeginGroup(bBeginGroup);
		}
	}

}

BOOL CControlFavorites::IsCustomizeDragOverAvail(CXTPCommandBar* pCommandBar, CPoint /*point*/, DROPEFFECT& dropEffect)
{
	if (pCommandBar->GetType() != xtpBarTypePopup)
	{
		dropEffect = DROPEFFECT_NONE;
		return FALSE;
	}
	return TRUE;
}
