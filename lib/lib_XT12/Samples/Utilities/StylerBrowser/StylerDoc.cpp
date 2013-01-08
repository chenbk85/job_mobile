// StylerDoc.cpp : implementation of the CStylerDoc class
//

#include "stdafx.h"
#include "Styler.h"

#include "StylerDoc.h"
#include "StylerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStylerDoc

IMPLEMENT_DYNCREATE(CStylerDoc, CDocument)

BEGIN_MESSAGE_MAP(CStylerDoc, CDocument)
END_MESSAGE_MAP()


// CStylerDoc construction/destruction

CStylerDoc::CStylerDoc()
{
	m_strUrl = "";

}

CStylerDoc::~CStylerDoc()
{
}

BOOL CStylerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_strUrl = "";

	return TRUE;
}




// CStylerDoc serialization

void CStylerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CStylerDoc diagnostics

#ifdef _DEBUG
void CStylerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStylerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStylerDoc commands

BOOL CStylerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();
	CStylerView* pView = (CStylerView*)GetNextView(pos);
	if (pView)
	{
		CString strUrl = CString(_T("file://")) + lpszPathName;
		pView->Navigate2(strUrl);
		
		// Internet Explorer bug 
		if (strUrl.Right(4).CompareNoCase(_T(".mht")) == 0 && strUrl.Find(_T("#")) != -1)
		{		
			pView->Refresh();
			pView->Navigate2(strUrl);
		}

		m_strUrl = strUrl;
	}

	// TODO:  Add your specialized creation code here

	return TRUE;
}
