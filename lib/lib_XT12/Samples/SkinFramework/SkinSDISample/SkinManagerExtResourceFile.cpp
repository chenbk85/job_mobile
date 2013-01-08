// SkinManagerExtResourceFile.cpp: implementation of the CSkinManagerExtResourceFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinSDISample.h"
#include "SkinManagerExtResourceFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinManagerExtResourceFile::CSkinManagerExtResourceFile()
{
	m_pIniFile = NULL;
}

CSkinManagerExtResourceFile::~CSkinManagerExtResourceFile()
{
	Close();
}

BOOL CSkinManagerExtResourceFile::Open(LPCTSTR lpszResourcePath, LPCTSTR lpszIniFileName)
{
	Close();

	m_strResourcePath = lpszResourcePath;
	m_strIniFileName = lpszIniFileName;

	CString strFileName = m_strResourcePath + _T('\\') + m_strIniFileName;
	m_pIniFile = new CStdioFile;
	
	if (!m_pIniFile->Open(strFileName, CFile::modeRead))
	{
		SAFE_DELETE(m_pIniFile);
		return FALSE;
	}

	return TRUE;
}

BOOL CSkinManagerExtResourceFile::ReadString(CString& str)
{
	if (!m_pIniFile)
		return FALSE;

	if (!m_pIniFile->ReadString(str))
	{
		SAFE_DELETE(m_pIniFile);
		return FALSE;
	}

	return TRUE;
}

void CSkinManagerExtResourceFile::Close()
{
	SAFE_DELETE(m_pIniFile);
}

CXTPSkinImage* CSkinManagerExtResourceFile::LoadImage(CString strImageFile)
{
	USES_CONVERSION;

	strImageFile = m_strResourcePath + _T('\\') + strImageFile;

	if (!FILEEXISTS_S(strImageFile))
		return NULL;

	BOOL bAlpha;
	HBITMAP hBitmap = NULL;

	hBitmap = CXTPImageManagerIcon::LoadBitmapFromFile(strImageFile, &bAlpha);
	
	if (!hBitmap)
		return NULL;
	
	CXTPSkinImage* pImage = new CXTPSkinImage;
	
	if (bAlpha)
	{
		HBITMAP hBitmapAlpha = CXTPImageManagerIcon::PreMultiplyAlphaBitmap(hBitmap);
		
		pImage->SetBitmap(hBitmapAlpha, TRUE);
		
		DeleteObject(hBitmap);
	}
	else 
	{
		pImage->SetBitmap(hBitmap);
	}
	
	return pImage;
}
