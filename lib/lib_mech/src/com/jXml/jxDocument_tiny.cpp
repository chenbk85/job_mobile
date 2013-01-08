/* 
coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
compiler:	vc++ 6.0
date	:	2006-03-06오후 8:20:37
title	:	 
*/
#include "stdafx.h"
#include "tchar.h"
#include "jXmlUtil.h"
#include ".\jxdocument_tiny.h"
#include "tinyxml/tinyxml.h"
#include "base/jxVar.h"


#include "header\nUNI_StringA.h"
#include "header\nUNI_StringW.h"

namespace nMech
{
	namespace nXML
	{

		//****************************************************************
		void jxElement_tiny::LoadAtt(TiXmlElement*  node)
			//****************************************************************
		{
			if(!node) return;
			TiXmlAttribute* pA = node->FirstAttribute();
			tfname_t szTag;
			for(;pA ;pA = pA->Next() )
			{
				jt_strncpy(szTag, nUNI::scb1024_t(pA->Name()).getT() ,ARRAY_SIZE(szTag)-1);
				jIVar::EElementType eType = (jIVar::EElementType)jxVar::GetTypeByTagName(szTag);
				jxVar* pV = m_AttMap.Insert(szTag);
				nUNI::scb2048_t aaa(pA->Value());
				pV->InitValue(aaa.getT(), eType);
			}
		}

		//****************************************************************
		void jxElement_tiny::Load(TiXmlNode* node)
			//****************************************************************
		{
			tstring szTag = nUNI::scb1024_t(node->Value()).getT();
			jxVar::EElementType eTagType = (jxVar::EElementType)jxVar::GetTypeByTagName(&szTag[0]);	
			// m_szName 에는 eType을 뺀 이름이 다시 복사됨.

			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szTag.c_str());
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);
			LoadAtt(node->ToElement());

			if(node->Type() != TiXmlNode::TINYXML_ELEMENT)
				return;


#ifdef _DEBUG
			bool isAssert = false;
#endif
			acstr sz1 =node->ToElement()->GetText();
			if(sz1 && ja_strlen(sz1))
			{
				m_Data.InitValue(nUNI::scb2048_t(sz1).getT(), eTagType);
#ifdef _DEBUG
				isAssert =true;
#endif
			}
			jxElement_tiny* pE=0;
			TiXmlNode* nodeChild= node->FirstChild();
			for(; nodeChild; nodeChild = nodeChild->NextSibling())
			{
				switch (nodeChild->Type())
				{
				case TiXmlNode::TINYXML_ELEMENT:
					{
#ifdef _DEBUG
						assert(!isAssert);
#endif

						if(pE)	
							pE = (jxElement_tiny*)pE->NewR();
						else	
							pE = (jxElement_tiny*)NewCB();
						m_Data.m_eType = jxVar::ETelement;
						pE->Load(nodeChild);
						break;
					}
				case TiXmlNode::TINYXML_COMMENT:
					{
						nUNI::scb2048_t aaa(nodeChild->Value());

						tstring cmt = aaa.getT();
						jxD* pD = (jxD*)this->GetRoot();
						jxE* pEc = pE ? pE : (jxE*)this;
						pD->m_jCommentManager[pEc].push_back(cmt);
						break;
					}
				}
			}

			/*
			case MSXML2::NODE_COMMENT:
			//_tcscpy(buf, (LPCTSTR)nodePtr->Gettext() );
			tstring cmt;
			cmt= (LPCTSTR)nodePtr->Gettext();		
			jxD* pD = (jxD*)this->GetDoc();
			jxE* pEc = pE ? pE : (jxE*)this;
			pD->m_jCommentManager[pEc].push_back(cmt);
			break;
			*/

		}

		//****************************************************************
		void jxDocument_tiny::Load(cstr szURL)
			//****************************************************************
		{
			try 
			{
				if(!nFileSystem::jFolder::Is_Exist(szURL))		throw "file not found";

				TiXmlDocument doc( nUNI::scb1024_t(szURL).getA() );
				bool loadOkay = doc.LoadFile();
				if(!loadOkay) 
				{
					afname_t buf;
					ja_sprintf(buf, "Error - %s(row=%d, col=%d)", doc.ErrorDesc() , doc.ErrorRow(), doc.ErrorCol());
					throw nUNI::scb1024_t(buf).getT();
				}

				TiXmlNode* pE = doc.FirstChild();
				int iFirst = false;
				for( ; pE ; pE = pE->NextSibling())
				{
					int iType1 = pE->Type();
					switch(iType1)
					{
					case TiXmlNode::TINYXML_ELEMENT:
						{
							assert(!iFirst);
							jxElement_tiny::Load(pE);
							iFirst = true;
							break;
						}
					case TiXmlNode::TINYXML_COMMENT :
						{
							nUNI::scb2048_t aaa(pE->Value());
							cstr sz = aaa.getT();
							jxD* pD = (jxD*)this->GetDoc();
							jxE* pEc = (jxE*)this;
							pD->m_jCommentManager[pEc].push_back(sz);
							break;
						}
					default:
						{
							cstr sz = nUNI::scb1024_t(pE->Value()).getT();
							int i=0;
							++i;
						}
					}
				}
			}
			catch(cstr  sz )
			{
				fname_t buf;
				GetCurrentDirectory(_countof(buf),buf);
				jMB(szURL, sz);
				throw szURL;
			}
			catch(...)
			{
				jMB(szURL,TEXT("unknown error jxDocument_tiny"));
				throw szURL;
			}

		} // void XMLDOMElementSample()

		//****************************************************************
		void jxDocument_tiny::LoadFromBuffer(tcstr szBuffer)
			//****************************************************************
		{
			try 
			{
				TiXmlDocument doc;
				acstr szBuff;
#ifdef UNICODE
				astring aBuf = nUNI::wcs_to_mbs(szBuffer);
				szBuff = aBuf.c_str();
#else
				szBuff  = szBuffer;
#endif
				//nUNI::jStringA aBuf = nUNI::jStringT(szBuffer);
				doc.Parse( szBuff);
				if(doc.Error()) 
				{
					afname_t buf;
					ja_sprintf(buf, "Error - %s(row=%d, col=%d)", doc.ErrorDesc() , doc.ErrorRow(), doc.ErrorCol());
					throw nUNI::scb1024_t(buf).getT();
				}

				TiXmlNode* pE = doc.FirstChild();
				int iFirst = false;
				for( ; pE ; pE = pE->NextSibling())
				{
					switch(pE->Type())
					{
					case TiXmlNode::TINYXML_ELEMENT:
						{
							assert(!iFirst);
							jxElement_tiny::Load(pE);
							iFirst = true;
							break;
						}
					case TiXmlNode::TINYXML_TEXT :
						{

							break;
						}
					case TiXmlNode::TINYXML_COMMENT :
						{

							break;
						}
					}
				}
			}
			catch(cstr  sz )
			{
				fname_t buf;
				GetCurrentDirectory(_countof(buf),buf);
				jMB(szBuffer, sz);
				throw szBuffer;
			}
			catch(...)
			{
				jMB(szBuffer,TEXT("unknown error jxDocument_tiny"));
				throw szBuffer;
			}
		} // void XMLDOMElementSample()


	}
}
