// ResourceEditorDoc.cpp : implementation of the CResourceEditorDoc class
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

#include "ResourceEditorDoc.h"
#include "ResourceExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorDoc

IMPLEMENT_DYNCREATE(CResourceEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CResourceEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CResourceEditorDoc)
	ON_COMMAND(ID_FILE_EXPOR_DLL, OnFileExportDll)
	ON_COMMAND(ID_FILE_EXPOR_RC, OnFileExportRc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorDoc construction/destruction

CResourceEditorDoc::CResourceEditorDoc()
{
	m_pResources = NULL;
	m_pLanguageInfo = NULL;
}

CResourceEditorDoc::~CResourceEditorDoc()
{
	CMDTARGET_RELEASE(m_pResources);
}

BOOL CResourceEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


BOOL CResourceEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	SAFE_DELETE(m_pResources);
	
	m_pResources = new CXTPPropExchangeXMLNode(TRUE, 0, _T("resource"));

	SetModifiedFlag(FALSE);
	
	if (!m_pResources->LoadFromFile(lpszPathName))
		return FALSE;

	DWORD nLangId = 0;
	PX_DWord(m_pResources, _T("LANGID"), nLangId);

	m_pLanguageInfo = CXTPResourceManager::GetLanguageInfo(nLangId);
	if (!m_pLanguageInfo)
		return FALSE;
	

	return TRUE;
}

BOOL CResourceEditorDoc::AssignResource(CXTPPropExchangeXMLNode* pResources)
{
	ASSERT(m_pResources == NULL);
	
	pResources->SetLoading(TRUE);
	
	DWORD nLangId = 0;
	PX_DWord(pResources, _T("LANGID"), nLangId);

	m_pLanguageInfo = CXTPResourceManager::GetLanguageInfo(nLangId);

	if (m_pLanguageInfo == NULL)
		return FALSE;

	SetModifiedFlag(TRUE);
	m_pResources = pResources;
	return TRUE;
}

BOOL CResourceEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_pResources->SaveToFile(lpszPathName);



	SetModifiedFlag(FALSE);     // back to unmodified
	return TRUE;        // success
}

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorDoc diagnostics

#ifdef _DEBUG
void CResourceEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResourceEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorDoc commands

void CResourceEditorDoc::OnFileExportDll() 
{
	if (!m_pResources)
		return;

	CString strFilter = _T("32-bit Dynamic Library (*.dll)|*.dll|All files (*.*)|*.*||");
	
	CString strTitle = GetPathName();
	REPLACE_S(strTitle, _T(".xml"), _T(".dll"));

	CFileDialog fd(FALSE, _T("dll"), strTitle, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() != IDOK)
		return;

	CResourceExport re;
	re.ExportDll(m_pResources, fd.GetPathName());
}

void CResourceEditorDoc::OnFileExportRc() 
{
	if (!m_pResources)
		return;
	
	CString strFilter = _T("Resource Script (*.rc)|*.rc|All files (*.*)|*.*||");

	CString strTitle = GetPathName();
	REPLACE_S(strTitle, _T(".xml"), _T(".rc"));

	CFileDialog fd(FALSE, _T("rc"), strTitle, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() != IDOK)
		return;


	CResourceExport re;
	re.ExportRc(m_pResources, fd.GetPathName());
}
