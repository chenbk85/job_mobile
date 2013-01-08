// XTPOffice2007Image.h: interface for the CXTPOffice2007Image class.
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

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPOFFICE2007IMAGE_H__)
#define __XTPOFFICE2007IMAGE_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//{{AFX_CODEJOCK_PRIVATE

#include "Common/XTPSystemHelpers.h"

// Private image wrappers:

#define XTP_DI_COMPOSITE 1

class CXTPOffice2007Images;
class CXTPOffice2007ImageList;
class CXTPNotifyConnection;

class _XTP_EXT_CLASS CXTPOffice2007Image : public CXTPCmdTarget
{
public:
	CXTPOffice2007Image(CXTPOffice2007Images* pImages);
	virtual ~CXTPOffice2007Image();

public:
	BOOL LoadFile(HMODULE hModule, LPCTSTR lpszBitmapFileName);
	void SetBitmap(HBITMAP hBitmap, BOOL bAlpha = FALSE);

	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc, const CRect& rcSizingMargins, COLORREF clrTransparent, DWORD dwFlags);
	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc, const CRect& rcSizingMargins, COLORREF clrTransparent);
	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc, CRect rcSizingMargins);
	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc);

	int GetHeight() const;
	int GetWidth() const;
	CSize GetExtent() const;

	BOOL IsAlphaImage() const;

	void PreserveOrientation() {
		m_bImageOrientaionPreserved = TRUE;
	}

	CRect GetSource(int nState = 0, int nCount = 1) const;

	BOOL GetBitmapPixel(CPoint pt, COLORREF& clrPixel);

	void Premultiply();


protected:
	BOOL DrawImagePart(CDC* pDCDest, CRect rcDest,
		CDC* pDCSrc, CRect rcSrc) const;

	BOOL DrawImageTile(CDC* pDCDest, const CRect& rcDest,
		CDC* pDCSrc, const CRect& rcSrc, BOOL bTile) const;

	void InvertBitmap();
	BOOL ConvertToBits(HBITMAP hBitmap);

protected:
	LPVOID m_pBits;
	BOOL m_bAlpha;
	BOOL m_bMultiply;
	BOOL m_bImageOrientaionPreserved;
	BOOL m_bInvert;
	CSize m_szExtent;

	CXTPOffice2007Images* m_pImages;

	friend class CXTPOffice2007Images;
	friend class CXTPOffice2007ImageList;
};

class _XTP_EXT_CLASS CXTPOffice2007Images : public CXTPCmdTarget
{
private:
	class CBitmapDC : public CDC
	{
	public:
		CBitmapDC()
		{
			m_hOldBitmap = 0;
		}
		~CBitmapDC()
		{
			if (m_hOldBitmap)
			{
				::SelectObject(GetSafeHdc(), m_hOldBitmap);
			}
		}
		void SetBitmap(HBITMAP hBitmap)
		{
			if (hBitmap)
			{
				m_hOldBitmap = (HBITMAP)::SelectObject(GetSafeHdc(), hBitmap);
			}
			else if (m_hOldBitmap)
			{
				::SelectObject(GetSafeHdc(), m_hOldBitmap);
				m_hOldBitmap = NULL;
			}

		}
		HBITMAP m_hOldBitmap;
	};
public:
	CXTPOffice2007Images();
	~CXTPOffice2007Images();
public:
	void RemoveAll();

	CXTPOffice2007Image* LoadFile(LPCTSTR lpszImageFile);

	BOOL SetHandle(HMODULE hResource, LPCTSTR lpszIniFileName = NULL, BOOL bFreeOnRelease = FALSE);
	BOOL SetHandle(LPCTSTR lpszFile, LPCTSTR lpszIniFileName = NULL);
	BOOL InitResourceHandle(LPCTSTR lpszTestImageFile, LPCTSTR lpResType = RT_BITMAP);

	COLORREF GetImageColor(CString strSectionName, CString strKeyName);
	CString GetImageString(CString strSectionName, CString strKeyName);
	CString GetImageValue(CString strSectionName, CString strKeyName);
	BOOL IsValid() const;

	CXTPNotifyConnection* GetConnection();

	CString m_strHandle;

protected:
	CXTPOffice2007Image* LoadImage(CString strImageFile);
	CString _ImageNameToResourceName(CString strImageFile);

private:
	void RefreshSettings();
	BOOL ReadString(CString& str, LPSTR& lpTextFile);

	static BOOL CALLBACK EnumResNameProc(HMODULE hModule,
		LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam);
	HRSRC FindResourceIniFile(HMODULE hResource);


protected:
	HMODULE m_hResource;
	LPSTR m_lpTextFile;
	LPSTR m_lpTextFileEnd;
	BOOL m_bFreeOnRelease;
	CRITICAL_SECTION m_cs;

	CBitmapDC m_dc;
	HBITMAP m_hbmLayer;
	LPDWORD m_pLayerBits;

	CXTPNotifyConnection* m_pConnection;	

protected:
	CMapStringToPtr m_mapImages;

	friend class CXTPOffice2007Image;

};

class _XTP_EXT_CLASS CXTPOffice2007ImageList : public CXTPOffice2007Images
{
	DECLARE_DYNCREATE(CXTPOffice2007ImageList)
	friend class CXTPOffice2007Image;
public:
	CXTPOffice2007ImageList();
	virtual ~CXTPOffice2007ImageList();

	CXTPOffice2007Image* GetBitmap(UINT nID);

	CXTPOffice2007Image* SetBitmap(HBITMAP hBitmap, UINT nID, BOOL bAlptha, BOOL bCopyBitmap = TRUE);

	BOOL SetBitmap(CXTPOffice2007Image* pImage, UINT nID, BOOL bCallAddRef);

	BOOL LoadBitmap(LPCTSTR lpcszPath, UINT nID);

	BOOL Remove(UINT nID);
	void RemoveAll();

protected:
	CMap<UINT, UINT, CXTPOffice2007Image*, CXTPOffice2007Image*> m_mapID2Image;

protected:
};

_XTP_EXT_CLASS CXTPOffice2007Images* AFX_CDECL XTPOffice2007Images();

//}}AFX_CODEJOCK_PRIVATE

#endif // !defined(__XTPOFFICE2007IMAGE_H__)
