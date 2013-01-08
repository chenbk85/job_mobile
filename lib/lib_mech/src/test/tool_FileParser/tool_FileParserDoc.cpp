// tool_FileParserDoc.cpp : implementation of the Ctool_FileParserDoc class
//

#include "stdafx.h"
#include "tool_FileParser.h"

#include "tool_FileParserDoc.h"

#include "util/juFileEnum.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctool_FileParserDoc

IMPLEMENT_DYNCREATE(Ctool_FileParserDoc, CDocument)

BEGIN_MESSAGE_MAP(Ctool_FileParserDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &Ctool_FileParserDoc::OnFileOpen)
END_MESSAGE_MAP()


// Ctool_FileParserDoc construction/destruction

Ctool_FileParserDoc::Ctool_FileParserDoc()
{
	// TODO: add one-time construction code here

}

Ctool_FileParserDoc::~Ctool_FileParserDoc()
{
}

BOOL Ctool_FileParserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Ctool_FileParserDoc serialization

void Ctool_FileParserDoc::Serialize(CArchive& ar)
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


// Ctool_FileParserDoc diagnostics

#ifdef _DEBUG
void Ctool_FileParserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ctool_FileParserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ctool_FileParserDoc commands

struct jUnicodeConvetingInfo
{
	cstr findStrB;
	cstr findStrE;
	cstr changeStrB;
	cstr changeStrE;
};

void change_to_unitext(tcstr szFile,void* v)
{
	jUnicodeConvetingInfo* a  = (jUnicodeConvetingInfo *)v;
	nFileSystem::UFileName fn;
	fn.Init(szFile);
	bool is =!jt_strcmp(fn.ext,_T(".cpp") );
	bool ish = !jt_strcmp(fn.ext,_T(".h") );
	if( is  || ish)
	{
		GetjILog()->LogPlus(_T("."),szFile);

		tstring sFile;
		nFileSystem::read_file(szFile,sFile);
		TCHAR* szB = &sFile[0];
		tstring newFile;
		for(;szB;)
		{
			TCHAR*szE = jt_strstr(szB,a->findStrB);
			if(!szE) 
			{
				if(!newFile.size()) 
					return;
				newFile +=szB;
				assert(newFile.size() > sFile.size());
				break;
			}

			*szE=0;
			newFile += szB;
			newFile += a->changeStrB;
			szB = szE + jt_strlen(a->findStrB);

			szE = jt_strstr(szB,a->findStrE);
			if(!szE)
			{
				GetjILog()->Error(_T(" %s에대한 짝 %s를 못찾음 : %s"), a->findStrB,a->findStrE ,szFile);
				return;
			}
			*szE=0;
			newFile += szB;
			newFile +=a->changeStrE;
			szB = szE + jt_strlen(a->findStrE);
		}
		GetjILog()->Log(_T("\ngo : %s"),szFile);
		tofstream of(szFile);
		of << newFile;
	}
}

void Ctool_FileParserDoc::OnFileOpen()
{
	jUnicodeConvetingInfo a = {_T("_jL\""),_T("\""),_T("TEXT(\""),_T("\")") }; 

#if 0
	{
		jUnicodeConvetingInfo c5 = {_T("GetCustomProperty(\""),_T("\""),_T("GetCustomProperty(TEXT(\""),_T("\")") };
		for_each_folder(_T("Z:\\src\\com\\jGui") , change_to_unitext,&c5);
	}
	jUnicodeConvetingInfo c5 = {_T(".Attr(\""),_T("\""),_T(".Attr(TEXT(\""),_T("\")") };
	for_each_folder(_T("Z:\\src") , change_to_unitext,&c5);

#endif

	jIE* pE = nGLOBAL::g_pDocApp->Find(jS(jUnicodeConvetingInfo));
	jIE* it = pE->begin();
	jrFOR(it)
	{
		if(!it->GetAttrVar(jS(ENABLE))->Get_bool()) continue;
		it->DebugPrint(false);
		jUnicodeConvetingInfo c5 = {it->GetAttr(jS(findS)),it->GetAttr(jS(findE)) , it->GetAttr(jS(changeS)) , it->GetAttr(jS(changeE)) };
		nFileSystem::for_each_folder(it->Get_cstr() , change_to_unitext,&c5);
	}

	GetjILog()->Log(_T("finish"));
	
}
