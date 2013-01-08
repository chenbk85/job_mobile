/* 
	filename:	jxAttributeList.cpp
	coder	:	Cho Wook Rea (chowookrea@hotmail) 
	comp.	:	-DIGICELL-
	compiler:	vc++ 6.0
	date	:	2004-07-20오전 1:14:21
	title	:	
*/
#include "stdafx.h"
#include "jxmlUtil.h"
#include "jxAttribute.h"
#include "jxDocument.h"
#include "header\\jMemoryChunk.h"
//#include "base/XFile.h"

namespace nMech
{
	namespace nXML
	{
		jDEFINE_YVECTOR_MANAGER(jxAttribute, 200,5);

		void jxAttribute::ChangeTagName(cstr sz)
		{
			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(sz );
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);
		}

		//---------------------------------------------------------------
		jxVar* jxAttributeList::Insert(cstr szKey) 	
			//----------------------------------------------------------------
		{
			jxVar* pV = FindVar(szKey);
			if(pV) return pV;
			iterator it = m_aObj.push_back();
			it->m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szKey);
			it->m_pTagName = nString::Get_jIStringTable()->GetName(it->m_iTagIndex);
			return &it->m_Data;
		}

		//****************************************************************
		void jxAttributeList::SaveXML(jXmlFile* fp)
			//****************************************************************
		{
			iterator it = m_aObj.begin() , ie = m_aObj.end();
			for( ; it != ie ; ++it )
			{
				fname_t name;
				it->m_Data.GetTagNameByType(it->m_pTagName, name);

				/*{by icandoit4337-11-08 오후 2:17:50
				if(it->GetVar()->GetType()== jxVar::EDcstr)
				{
				if(!_tcscmp(it->GetVar()->Get_cstr() , g_XmlNULL ) )				return ;
				}
				}by icandoit 4337-11-08 오후 2:17:52*/

				if(fp->fp)
				{
					jt_fprintf(fp->fp, TEXT(" %s='") , name);

					fname_t buf;
					cstr sz = it->m_Data.ToString(buf);
					jt_fprintf(fp->fp, TEXT("%s"),sz);

					//it->m_Data.SaveXML(fp);
					jt_fprintf(fp->fp, TEXT("%s"), TEXT("'"));
				}
				else
				{
#ifdef UNICODE
					TCHAR bufX[1024];
					jt_sprintf(bufX, TEXT(" %s='") , name);
					//fp->xfp->Write(bufX, jt_strlen(bufX));
					fp->str +=bufX;

					fname_t buf;
					cstr sz = it->m_Data.ToString(buf);
					jt_sprintf(bufX, TEXT("%s"),sz);
					//fp->xfp->Write(bufX, jt_strlen(bufX));
					fp->str +=bufX;

					//it->m_Data.SaveXML(fp);
					jt_sprintf(bufX, TEXT("%s"), TEXT("'"));
					//fp->xfp->Write(bufX, jt_strlen(bufX));
					fp->str +=bufX;
#endif
				}


			}
		}

		//****************************************************************
		void jxAttributeList::DebugPrint(bool isInsert_CR)
			//****************************************************************
		{
			iterator it = m_aObj.begin() , ie = m_aObj.end();

			for( ; it != ie ; it++ )
			{
				GetjILog()->LogPlus(  TEXT(" %s='") , it->m_pTagName );
				it->m_Data.DebugPrint(isInsert_CR);
				GetjILog()->LogPlus( TEXT("' "));
			}
			//SAFE_REL(attPtr);
		}

		//---------------------------------------------------------------
		void jxAttributeList::writeChunk(nUtil::jMemoryChunk& mc)
			//----------------------------------------------------------------
		{
#pragma warning(disable : 4267)
			uint16 tot = m_aObj.size();
#pragma warning(default : 4267)
			mc.writeChunk(tot);
			iterator  it = m_aObj.begin();
			for(uint16 i =0 ; i < tot; i++ , it++ )
			{
				if(!jt_strncmp(it->GetTagName(),_T("___"),jt_strlen(_T("___"))))
				{
					continue;
				}
				mc.writeChunk(const_cast<TCHAR*>(it->m_pTagName));
				it->m_Data.writeChunk(mc);
			}
		}

		//---------------------------------------------------------------
		void jxAttributeList::readChunk(nUtil::jMemoryChunk& mc)
		//----------------------------------------------------------------
		{

			uint16 tot;
			mc.readChunk(tot);
			for(uint16 i =tot ; i ; --i )
			{
				TCHAR *sz;
				mc.readChunk(&sz);
				jxVar* pV = Insert(sz);
				pV->readChunk(mc);
			}
		}

		//---------------------------------------------------------------
		void jxAttributeList::writePacket(nUtil::jMemoryChunk& mc)
		//----------------------------------------------------------------
		{
			iterator  it = m_aObj.begin(), ie = m_aObj.end();
			for(; it!=ie ; ++it )
			{				
				if(!jt_strncmp(it->GetTagName(),_T("___"),jt_strlen(_T("___") )))
				{
					continue;
				}
				it->m_Data.writePacket(mc);
			}
		}


		//---------------------------------------------------------------
		void jxAttributeList::readPacket(nUtil::jMemoryChunk& mc)
			//----------------------------------------------------------------
		{
			iterator it = m_aObj.begin() , ie = m_aObj.end();
			for( ; it != ie ; ++it)
			{
				it->m_Data.readPacket(mc);
			}
		}

	}
}


