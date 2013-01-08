/* 
filename:	jxDocument_Expat.cpp
coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
compiler:	vc++ 6.0
date	:	2006-03-06오후 8:20:37
title	:	 
*/
#include "stdafx.h"
#include "tchar.h"
#include "jXmlUtil.h"
#include "jxDocument_Expat.h"

namespace nMech
{
	namespace nXML
	{

		//****************************************************************
		void jxElement_Expat::LoadAtt(jXmlNodeRef&  node)
			//****************************************************************
		{
			cstr key = 0;
			cstr val = 0;
			int len = node->getNumAttributes();
			for(int i=0; i < len ; i++)
			{
				node->getAttributeByIndex(i, &key,&val);
				fname_t szTag;
				strncpy(szTag, key,sizeof(szTag));
				jIVar::EElementType eType = (jIVar::EElementType)jxVar::GetTypeByTagName(szTag);
				jxVar* pV = m_AttMap.Insert(szTag);
				pV->InitValue(val , eType);
			}
		}

		//****************************************************************
		void jxElement_Expat::Load(jXmlNodeRef& node)
			//****************************************************************
		{
			fname_t szTag;
			strncpy(szTag , node->getTag() , sizeof(szTag));
			jxVar::EElementType eTagType = (jxVar::EElementType)jxVar::GetTypeByTagName(szTag);	// m_szName 에는 eType을 뺀 이름이 다시 복사됨.
			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szTag);
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);
			LoadAtt(node);

			int iChild = node->getChildCount();
			if (!iChild) return;	
			jxElement_Expat* pE=0;
			for(int i= 0; i < iChild ; i++)
			{
				jXmlNodeRef& nodeChild = node->getChild(i);
				cstr sz = nodeChild->getContent();
				if(nodeChild->getChildCount() || !strlen(sz) )
				{
					if(pE)	pE = (jxElement_Expat*)pE->NewR();
					else	pE = (jxElement_Expat*)NewCB();
					m_Data.eType = jxVar::ETelement;
					pE->Load(nodeChild);
				}
				else
				{
					m_Data.InitValue(sz , eTagType);
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
			}//for(i= 0; i < iChild ; i++)

		}


		using namespace jUtil_xml;
		//****************************************************************
		void jxDocument_Expat::Load(cstr szURL)
			//****************************************************************
		{
			XmlParser parser;
			try 
			{
				if(!nFileSystem::jFolder::Is_Exist(szURL))		throw "file not found";

				jXmlNodeRef root =	parser.parse(szURL);
				if(!root)	throw parser.getErrorString();
				jxDocument* pD = (jxDocument*)this;			
				jxElement_Expat::Load(root);
			}
			catch(cstr  sz )
			{
				fname_t buf;
				GetCurrentDirectory(sizeof(buf),buf);
				jMB(szURL, sz);
				throw szURL;
			}
			catch(...)
			{
				jMB(szURL,TEXT("unknown error jxDocument_Expat"));
				throw szURL;
			}

		} // void XMLDOMElementSample()

		//****************************************************************
		void jxDocument_Expat::LoadFromBuffer(char* szBuffer)
			//****************************************************************
		{
			XmlParser parser;
			try 
			{
				jXmlNodeRef root =	parser.parseBuffer(szBuffer);
				if(!root)	throw parser.getErrorString();
				jxDocument* pD = (jxDocument*)this;			
				jxElement_Expat::Load(root);
			}
			catch(cstr  sz )
			{
				char buf[1024];
				GetCurrentDirectory(sizeof(buf),buf);
				jMB(szBuffer, sz);
				throw szBuffer;
			}
			catch(...)
			{
				jMB(szBuffer,TEXT("unknown error jxDocument_Expat"));
				throw szBuffer;
			}
		} // void XMLDOMElementSample()



	}
}
