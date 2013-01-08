  /* 
	filename:	jxDocumentEx.cpp
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-06오후 8:20:37
	title	:	 xml문서를 jxml로  export 하는 클래스. 게임엔진에서는 필요없는 모듈이다.
*/

// jxDocumentEx.cpp: implementation of the jxDocumentEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tchar.h"
#include "jXmlUtil.h"
#include "jxDocumentEx.h"

#ifdef jMSXML_USE


#	ifdef _DEBUG
#	undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#	define new DEBUG_NEW
#	endif
#	ifndef _STLP_NEW_PLATFORM_SDK
using namespace MSXML2;
#	endif
inline void TESTHR( HRESULT _hr )    { if FAILED(_hr) throw(_hr); }


//#define JLOAD_TEST_DEBUG
namespace nMech
{
	namespace nXML
	{

		//****************************************************************
		void jxElementEx::LoadAtt(MSXML2::IXMLDOMNamedNodeMapPtr& attMap)
			//****************************************************************
		{
			//jxBStr bs2,bs3;
			TCHAR* bs2; TCHAR* bs3;
			MSXML2::IXMLDOMAttributePtr attPtr=0;
			int len;
			len = attMap->Getlength() ;
			for(int i=0; i < len ; i++)
			{
				attPtr = attMap->Getitem(i);
				//bs2.Set(attPtr->GetbaseName());
				_bstr_t  sz4 = attPtr->GetbaseName();
				bs3 = sz4;
				TCHAR szAttName[1024];
				_tcscpy( szAttName , bs3 );
				int  eType = jxVar::GetTypeByTagName(szAttName);
				//bs3.Set( attPtr->Gettext());
				_bstr_t  sz5 = attPtr->Gettext();
				bs2 = sz5 ;
				jxVar* pV = m_AttMap.Insert(szAttName );
				pV->InitValue(bs2,(jxVar::EElementType)eType);
#ifdef JLOAD_TEST_DEBUG
				fname_t buf123;
				jt_printf(_T("\t\t attr=%s"),szAttName, pV->ToString(buf123));
#endif

			}
			//SAFE_REL(attPtr);
		}

		//****************************************************************
		void jxElementEx::Load(MSXML2::IXMLDOMElementPtr& pElmt)
			//****************************************************************
		{
			TCHAR szName[256];	
			_stprintf(szName , (LPCTSTR)(pElmt->GettagName()) , sizeof(pElmt->GettagName()));

			jxVar::EElementType eTagType = jxVar::GetTypeByTagName(szName);	// m_szName 에는 eType을 뺀 이름이 다시 복사됨.
			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szName);
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);

#ifdef JLOAD_TEST_DEBUG
			for(int iTab=0; iTab< this->GetDepth(); ++iTab)printf("\t");
			jt_printf(_T("<%s\n"),szName);
#endif
			try 
			{	 

				try
				{
					LoadAtt(pElmt->Getattributes());
				}
				catch(...)
				{
					jERROR(TEXT("%s : %s Attribute error "), GetParent()->GetTagName() , m_pTagName );
				}

				MSXML2::IXMLDOMNodeListPtr pNodeList  = pElmt->GetchildNodes();

				int iChild = pNodeList->Getlength();
				if (iChild ==0) return;	

				jxElementEx* pE=0;
				for(int i= 0; i < iChild ; i++)
				{
					MSXML2::IXMLDOMNodePtr nodePtr = pNodeList->Getitem(i);
					MSXML2::DOMNodeType eXmlType = nodePtr->GetnodeType();
					switch(eXmlType)
					{
					case MSXML2::NODE_ELEMENT :
						try
						{
							if(pE)	
								pE = (jxElementEx*)pE->NewR();
							else	
								pE = (jxElementEx*)NewCB();
							m_Data.SetType(jxVar::ETelement);
							MSXML2::IXMLDOMElementPtr elmtPtr = nodePtr;
							//jxElementEx* pE = (jxElementEx*)it;
							pE->Load(elmtPtr );

						}
						catch(...)
						{
							jAssertArg(0 ,TEXT("%s : %s MSXML2::NODE_ELEMENT error "), GetParent()->GetTagName() , m_pTagName );
						}
						break;
					case MSXML2::NODE_TEXT:
						try
						{
							m_Data.InitValue((LPCTSTR)nodePtr->Gettext(), eTagType);
#ifdef JLOAD_TEST_DEBUG
							jt_printf(_T("\ntype = %s"),m_Data.GetTypeString());
							for(int iTab=0; iTab< this->GetDepth(); ++iTab)printf("\t");
							jt_printf(_T("=text = %s\n"),(LPCTSTR)nodePtr->Gettext());
#endif

						}
						catch(...)
						{
							jAssertArg(0 ,TEXT("%s : %s MSXML2::NODE_TEXT error "), GetParent()->GetTagName() , m_pTagName );
						}
						break;
					case MSXML2::NODE_COMMENT:
						try{
							//_tcscpy(buf, (LPCTSTR)nodePtr->Gettext() );
							jxD* pD = (jxD*)this->GetDoc();
							jxE* pEc = pE ? pE : (jxE*)this;
							pD->m_jCommentManager[pEc].push_back((LPCTSTR)nodePtr->Gettext());
						}
						catch(cstr sz )		
						{
							jAssertArg(0 ,TEXT("%s : %s MSXML2::NODE_COMMENT error %s "), GetParent()->GetTagName() , m_pTagName ,sz);
						}
						break;
					default:
						MessageBox(0,(LPCTSTR)(nodePtr->xml) , TEXT("알수 없는 엘리먼트 타입입니다 : void jxElementEx::Load()"),MB_OK);
						jLOG(_T("\n\n\n  알수 없는 엘리먼트 타입입니다. \n\n\n"));
						break;
					}
				}//for(i= 0; i < iChild ; i++)
			}
			catch(cstr sz)
			{
				jERROR(TEXT("%s : %s MSXML2::NODE_COMMENT error : %s "), GetParent()->GetTagName() , m_pTagName ,sz);
			}
			catch(...)
			{
				jERROR(TEXT("%s : %s MSXML2::NODE_COMMENT error "), GetParent()->GetTagName() , m_pTagName );
			}

		} // void jxElementEx::Load(IXMLDOMElementPtr& pElmt, jxElementEx* pParent)
		char buf_save1[1024];



		//****************************************************************
		void jxDocumentEx::Load(cstr szURL)
			//****************************************************************
		{
			::CoInitialize(NULL);
			//::CoInitializeEx(NULL, COINIT_MULTITHREADED);
			try 
			{

				static int iDepth =0;
				MSXML2::IXMLDOMDocumentPtr docPtr =0;
				//init
				//TESTHR(CoInitialize(NULL)); 
				TESTHR(docPtr.CreateInstance(TEXT("Msxml2.DOMDocument.6.0")));

				// load a document
				_variant_t varXml(szURL); //"O:\\XMLTEST\\book.xml");
				_variant_t varOut((bool)TRUE);
				if(!nFileSystem::jFolder::Is_Exist(szURL))
					throw szURL;
				varOut = docPtr->load(varXml);
				if ((bool)varOut == FALSE)
					throw szURL;
				MSXML2::IXMLDOMElementPtr ElementPtr = docPtr->documentElement;
				jxDocument* pD = (jxDocument*)this;			

				jxElementEx::Load(ElementPtr);

				CoUninitialize();
			}
			catch(cstr  )
			{
				CoUninitialize();
				fname_t buf;
				GetCurrentDirectory(_countof(buf),buf);
				if(nInterface::g_pjILog)
				{
					jERROR(_T("jxD::Load Error(%s), - currpath=%s"), szURL, buf);
				}
				else 
					jMB(szURL, _T("xml load fail") );
			}
			catch(...)
			{
				CoUninitialize();
				if(nInterface::g_pjILog)
				{
					jERROR(TEXT("error jxDocEx : %s"),szURL);
				}
				else 
					jMB(szURL, _T("xml load fail") );
			}

		} // void XMLDOMElementSample()

		//****************************************************************
		void jxDocumentEx::LoadFromBuffer(tcstr szBuffer)
			//****************************************************************
		{
			try 
			{
				static int iDepth =0;
				MSXML2::IXMLDOMDocumentPtr docPtr =0;
				//init
				TESTHR(CoInitialize(NULL)); 
				//::CoInitializeEx(NULL, COINIT_MULTITHREADED);
				TESTHR(docPtr.CreateInstance(TEXT("Msxml2.DOMDocument.6.0")));

				// load a document
				_variant_t varOut((bool)TRUE);
				varOut = docPtr->loadXML(szBuffer);
				if ((bool)varOut == FALSE)
					throw szBuffer;
				MSXML2::IXMLDOMElementPtr ElementPtr = docPtr->documentElement;
				jxDocument* pD = (jxDocument*)this;			

				jxElementEx::Load(ElementPtr);
			}
			catch(cstr  )
			{
				fname_t buf;
				GetCurrentDirectory(_countof(buf),buf);
				jERROR(_T("void jxDocumentEx::LoadFromBuffer(char* szBuffer)"), buf);
			}
			catch(...)
			{
				jERROR(_T("void jxDocumentEx::LoadFromBuffer(char* szBuffer)"),TEXT("error jxDocEx"));
			}

			CoUninitialize();
		} // void XMLDOMElementSample()


		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////

		jxDocumentEx::jxDocumentEx()
		{

		}

		//****************************************************************
		jxDocumentEx::~jxDocumentEx()
			//****************************************************************
		{

		}

	}
}
#endif //#ifdef jMSXML_USE