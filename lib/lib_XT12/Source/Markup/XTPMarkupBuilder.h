// XTPMarkupBuilder.h: interface for the CXTPMarkupBuilder class.
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

#if !defined(__XTPMARKUPBUILDER_H__)
#define __XTPMARKUPBUILDER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPMarkupUIElement;
class CXTPMarkupObject;
class CXTPMarkupDependencyProperty;
class CXTPMarkupContext;
class CXTPMarkupParser;
class CXTPMarkupClassList;
class CXTPMarkupType;


class CXTPMarkupBuilderException : public CSimpleException
{
	DECLARE_DYNAMIC(CXTPMarkupBuilderException)

public:
	CXTPMarkupBuilderException(LPCTSTR lpszError);

public:
	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
		PUINT pnHelpContext = NULL);

protected:
	TCHAR m_szMessage[256];
};

class _XTP_EXT_CLASS CXTPMarkupBuilder
{
	class CStaticExtension;
	class CStringBuilder;
	class CStaticResourceExtension;

public:
	CXTPMarkupBuilder(CXTPMarkupContext* pContext);
	virtual ~CXTPMarkupBuilder();

public:

	CXTPMarkupObject* CreateObject(LPCWSTR lpszTag);
	CXTPMarkupDependencyProperty* FindProperty(LPCWSTR lpszTag, LPCWSTR lpszAttribute);
	CXTPMarkupDependencyProperty* FindProperty(CXTPMarkupType* pRuntimeClass, LPCWSTR lpszAttribute);

	CString GetLastError() const;

public:
	CXTPMarkupUIElement* Parse(CXTPMarkupParser* pParser);

	void ThrowBuilderException(LPCTSTR lpszError);

	CXTPMarkupContext* GetMarkupContext() const;

public:
	static BOOL AFX_CDECL ColorStringToKnownColor(LPCWSTR lpszValue, COLORREF& clr);
	static CXTPMarkupObject* AFX_CDECL ConvertTextDecorations(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertFontWeight(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertFontStyle(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertVerticalAlignment(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertHorizontalAlignment(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertTextWrapping(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertTextTrimming(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertTextAlignment(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertOrientation(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertBaselineAlignment(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertCursor(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertVisibility(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertFontQuality(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertContent(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertScrollBarVisibility(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);
	static CXTPMarkupObject* AFX_CDECL ConvertStretch(CXTPMarkupContext* pContext, CXTPMarkupObject* pObject);

public:
	static CString AFX_CDECL FormatString(LPCTSTR lpszFormat, LPCTSTR lpszParameter);
	static CString AFX_CDECL FormatString(LPCTSTR lpszFormat, LPCTSTR lpszParameter1, LPCTSTR lpszParameter2);
	static CString AFX_CDECL FormatString(LPCTSTR lpszFormat, LPCTSTR lpszParameter1, LPCTSTR lpszParameter2, LPCTSTR lpszParameter3);

	CXTPMarkupObject* ConvertValue(CXTPMarkupDependencyProperty* pProperty, CXTPMarkupObject* pValue);


private:
	CXTPMarkupObject* ResolveMarkupExtension(LPCWSTR lpszValue);
	CStaticExtension* GetStaticExtension();
	CStaticResourceExtension* GetStaticResourceExtension();
	CXTPMarkupObject* CreateTypeKey(LPCWSTR lpszType);


protected:
	CString m_strLastError;
	CXTPMarkupContext* m_pMarkupContext;
	CStaticExtension* m_pStaticExtension;
	CStaticResourceExtension* m_pStaticResourceExtension;
	CList<CXTPMarkupObject*, CXTPMarkupObject*> m_arrObjects;

	friend class CStaticResourceExtension;

};

AFX_INLINE void CXTPMarkupBuilder::ThrowBuilderException(LPCTSTR lpszError) {
	THROW(new CXTPMarkupBuilderException(lpszError));
}
AFX_INLINE CString CXTPMarkupBuilder::GetLastError() const {
	return m_strLastError;
}
AFX_INLINE CXTPMarkupContext* CXTPMarkupBuilder::GetMarkupContext() const {
	return m_pMarkupContext;
}

#endif // !defined(__XTPMARKUPBUILDER_H__)
