/*
	filename:	kXmlIndex.h
	coder	:	(psy123@empal.com)(icq:128176816) 
	compiler:	vc++ 6.0
	date	:	2001-08-29오후3:55:25
	title	:	
*/

#ifndef __kXmlIndex_h__
#define __kXmlIndex_h__
#if _MSC_VER > 1000
//#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <map>
//#include <assert.h>
#include "header\\nPatriciaTrie.h"
#pragma warning(disable : 4251)
#include "header\\jMemoryChunk.h"
#include "Interface\jILog.h"

namespace nMech
{
	typedef StringID jstring_id;
	typedef StringID jstring_cid;
	namespace nUtil
	{
		struct jMemoryChunk;
	}

	namespace nString
	{
#pragma warning(disable: 4251)
#pragma warning(disable: 4267)

		//----------------------------------------------------------------
		class kXmlIndex
			//----------------------------------------------------------------
		{
		public:
			jLIST_TYPEDEF_vector(cstr, m_vecName);
			typedef nDataStruct::nPatriciaTrie<jstring_id> map_t;
			typedef map_t::iterator map_it;	
			map_t m_mapName;	 

			jstring_id Insert(cstr szName)
			{
				map_it it = m_mapName.find(szName);
				if(it != m_mapName.end() )
					return it->second;
				jstring_id index = (jstring_id)m_vecName.size();
				it = m_mapName.insert(szName , index );
				m_vecName.push_back(it->first );
				return index;
			}
		public:
			kXmlIndex(int iTot)
			{
				//m_mapName.clear();
				m_vecName.resize(iTot);
				std::fill(m_vecName.begin(), m_vecName.end(), (cstr)0);
				assert(!m_vecName[m_vecName.size()-1] );
				assert(!m_vecName[iTot/2] );
				assert(!m_vecName[0] );
			}

			void Regist(cstr szName,size_t  id)
			{
#if _DEBUG
				size_t iTot = m_vecName.size();
				assert(id < iTot);
				cstr szTest = m_vecName[id];
				if( iTot <= id || szTest)
#else
				if(m_vecName.size() <= id || m_vecName[id])
#endif
				{
					jERROR(_T("kXmlIndex id 등록 실패 %s"),szName);
				}
				map_it it = m_mapName.find(szName);
				if(it != m_mapName.end() )
				{
					jMB(_T("kXmlIndex중복"),szName);
					throw szName;
				}
				it = m_mapName.insert(szName , id);
				m_vecName[id]= it->first;
#if _DEBUG
				assert(m_mapName[szName] == id );
				cstr szName1 = m_vecName[id];
				assert(!jt_strcmp(szName1,szName) );
#endif
			}

			void clear()
			{ 
				m_vecName.clear(); 
				m_mapName.clear();
			}

			jstring_id GetIndex(cstr szName)
			{		
				return Insert(szName);
			};

			cstr GetName(jstring_id idx)
			{			
				return m_vecName[idx];		
			};

			//void kXmlIndex::readChunk(jMemoryChunk& mc);
			//void kXmlIndex::writeChunk(jMemoryChunk& mc);
			//---------------------------------------------------------------	
			void kXmlIndex::writeChunk(nUtil::jMemoryChunk& mc)
				//----------------------------------------------------------------
			{	
				size_t vecSize	= m_vecName.size();
				const float version = 1;

				mc.writeChunk(version);
				mc.writeChunk(vecSize);
				for(size_t  i =0 ; i < vecSize ; i++)
				{
					mc.writeChunk(const_cast<TCHAR*>(m_vecName[i]));
				}		
			}

			//---------------------------------------------------------------	
			void kXmlIndex::readChunk(nUtil::jMemoryChunk& mc)
				//----------------------------------------------------------------
			{
				int vecSize;		
				float version;

				mc.readChunk(version);
				mc.readChunk(vecSize);
				for(int i = 0; i < vecSize; i++)
				{
					TCHAR* sz;
					mc.readChunk(&sz);
					GetIndex(sz);			
				}
			}

		};

	}//nString

}

#pragma warning(default: 4251)
#pragma warning(default: 4267)

#endif //__kXmlIndex_h__
