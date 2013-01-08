// XTPMarkupBorder.h: interface for the CXTPMarkupBorder class.
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

#if !defined(__XTPMARKUPCONTEXT_H__)
#define __XTPMARKUPCONTEXT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPMarkupObject;
class CXTPImageManager;
class CXTPMarkupUIElement;
class CXTPMarkupInputElement;
class CXTPMarkupContext;
class CXTPMarkupEventHandlerMap;
class CXTPMarkupRoutedEventArgs;
class CXTPMarkupRoutedEvent;
class CXTPMarkupDelegate;
class CXTPMarkupFont;
class CXTPMarkupType;
class CXTPMarkupKeyboardNavigation;
class CXTPToolTipContext;

class CXTPMarkupDelegateMap;

class _XTP_EXT_CLASS CXTPMarkupContext
{
	class CXTPMarkupFontArray;
protected:
	class CInputElementCollection;

public:
	CXTPMarkupContext();

protected:
	virtual ~CXTPMarkupContext();

public:
	LOGFONT* GetDefaultLogFont();
	COLORREF GetDefaultForeground();

	void SetDefaultTextColor(COLORREF clr);

	void SetDefaultFont(HFONT font);
	void SetDefaultFont(LOGFONT* pLogFont);

	CXTPMarkupUIElement* Parse(LPCSTR lpszBuffer);
	CXTPMarkupUIElement* Parse(LPCWSTR lpszBuffer);

	CXTPMarkupFont* GetFont(LOGFONT* pLogFont);

	static BOOL AFX_CDECL CompareFont(LOGFONT* pLogFont1, LOGFONT* pLogFont2);

	virtual BOOL OnWndMsg(CXTPMarkupUIElement* pUIElement, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	void RaiseEvent(CXTPMarkupObject* pSource, CXTPMarkupRoutedEventArgs* pEventArgs);
	void AddHandler(CXTPMarkupRoutedEvent* pEvent, CXTPMarkupDelegate* pDelegate);
	void SetDelegate(LPWSTR lpszDelegate, CXTPMarkupDelegate* pDelegate);

	CXTPMarkupDelegate* LookupDelegate(LPCWSTR lpszDelegate) const;

	void CaptureMouse(CXTPMarkupInputElement* pUIElement);
	void ReleaseMouseCapture(CXTPMarkupInputElement* pUIElement);

	CXTPMarkupKeyboardNavigation* GetKeyboardNavigation() const;

	void Release();
	INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pToolInfo);

private:
	void HandleMouseMove(CXTPMarkupUIElement* pUIElement, CPoint point);
	void HandleMouseEnter(CXTPMarkupInputElement* pUIElement, CPoint point);
	BOOL HandleSetCursor();
	BOOL HandleMouseWheel(int nDelta);
	BOOL HandleMouseUpDown(UINT message, WPARAM wParam, LPARAM lParam);

	void BuildInputList(CXTPMarkupObject* pUIElement, CInputElementCollection* list);
	BOOL IsVisualChild(CXTPMarkupObject* pParent, CXTPMarkupObject* pChild);

	CRect GetClientBoundingRect(CXTPMarkupInputElement* pUIElement);

public:
	virtual void OnInvalidateVisual(CXTPMarkupUIElement* pUIElement);
	virtual void OnInvalidateArrange(CXTPMarkupUIElement* pUIElement);

public:
	CXTPMarkupObject* CreateMarkupObject(CXTPMarkupType* pRuntimeClass);
	void FinalizeMarkupObject(CXTPMarkupInputElement* pInputElement);
	static void AFX_CDECL RegisterClasses();

public:
	CXTPImageManager* m_pImageManager;
	HWND m_hContextWnd;

protected:
	COLORREF m_clrForeground;
	LOGFONT m_logFont;

	CXTPMarkupInputElement* m_pMouseOver;
	CXTPMarkupInputElement* m_pMouseCapture;
	CXTPMarkupUIElement* m_pActiveElement;

	CXTPMarkupFontArray* m_pFonts;

	CXTPMarkupEventHandlerMap* m_pHandlers;
	CXTPMarkupDelegateMap* m_pDelegates;

	CXTPMarkupKeyboardNavigation* m_pKeyboardNavigation;

	CXTPToolTipContext* m_pTooltipContext;

	friend class CXTPMarkupFont;
	class CTooltipContext;
	long m_dwRef;

};


template<class TYPE>
class CXTPMarkupTypedSimpleStack
{
public:
	CXTPMarkupTypedSimpleStack()
	{
		m_pHead = NULL;
		m_pTail = NULL;
	}

	BOOL IsEmpty() const
	{
		return m_pHead == NULL;
	}

	void AddTail(TYPE* pPart)
	{
		if (m_pTail != NULL)
		{
			m_pTail->m_pNextChain = pPart;
		}
		else
		{
			m_pTail = m_pHead = pPart;
		}
		m_pTail = pPart;
	}

	TYPE* RemoveHead()
	{
		ASSERT(m_pHead);
		if (!m_pHead)
			return NULL;

		TYPE* pHead = m_pHead;

		if (m_pHead == m_pTail)
		{
			m_pHead = m_pTail = NULL;
		}
		else
		{
			m_pHead = pHead->m_pNextChain;
			ASSERT(m_pHead);
		}

		pHead->m_pNextChain = NULL;

		return pHead;
	}

	void RemoveAll()
	{
		m_pHead = m_pTail = NULL;
	}

	TYPE* GetHead() const
	{
		return m_pHead;
	}

	TYPE* GetTail() const
	{
		return m_pTail;
	}

	BOOL Remove(TYPE* p)
	{
		ASSERT(p != NULL);
		if (!p)
			return FALSE;

		if (m_pHead == m_pTail)
		{
			if (p != m_pHead)
				return FALSE;

			p->m_pNextChain = NULL;
			m_pHead = m_pTail = NULL;
			return TRUE;
		}

		if (m_pHead == p)
		{
			m_pHead = p->m_pNextChain;
			p->m_pNextChain = NULL;
			return TRUE;
		}

		TYPE* pTest = m_pHead;
		while (pTest != NULL && pTest->m_pNextChain != p)
			pTest = pTest->m_pNextChain;

		if (pTest != NULL)
		{
			if (m_pTail == p) m_pTail = pTest;
			pTest->m_pNextChain = p->m_pNextChain;
			p->m_pNextChain = NULL;
			return TRUE;
		}
		return FALSE;
	}

protected:
	TYPE* m_pHead;
	TYPE* m_pTail;
};

AFX_INLINE LOGFONT* CXTPMarkupContext::GetDefaultLogFont() {
	return &m_logFont;
}
AFX_INLINE COLORREF CXTPMarkupContext::GetDefaultForeground() {
	return m_clrForeground;
}
AFX_INLINE void CXTPMarkupContext::SetDefaultTextColor(COLORREF clr) {
	m_clrForeground = clr;
}
AFX_INLINE void CXTPMarkupContext::SetDefaultFont(HFONT font) {
	LOGFONT lf;
	GetObject(font, sizeof(LOGFONT), &lf);
	m_logFont = lf;
}
AFX_INLINE void CXTPMarkupContext::SetDefaultFont(LOGFONT* pLogFont) {
	m_logFont = *pLogFont;
}
AFX_INLINE CXTPMarkupKeyboardNavigation* CXTPMarkupContext::GetKeyboardNavigation() const {
	return m_pKeyboardNavigation;
}

#define MARKUP_CREATE(object_class, context) (object_class*)context->CreateMarkupObject(MARKUP_TYPE(object_class))

#endif // !defined(__XTPMARKUPCONTEXT_H__)
