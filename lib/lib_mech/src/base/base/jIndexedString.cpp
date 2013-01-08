/* file : jStringTable.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-25 16:57:47
comp.: pantavision
title : 
desc : 

*/

#include "stdafx.h"
#include "jIndexedString.h"
#include "header/jSington.h"
#include "header/kXmlIndex.h"
#include "base/jXmlDictionary.h"
#include "header/UFile.h"

namespace nMech
{
	using namespace nFileSystem;
	namespace nString
	{
		// base/jXmlDictionary.h에 정의된 enum예약어가 미리 RegistIDStatic를 통해 후출되었다면 
		// s_isStatic_xmlid_registed = true가 된다.
		static bool s_isStatic_xmlid_registed =false;

		//--------------------------------------------------------------------------
		class jStringTable : public jIStringTable
			//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIStringTable);
			~jStringTable(){ clear();}

		private:
			jSINGTON_INTERFACE_DECLEAR(JBASE_API , jStringTable, jIStringTable);

			kXmlIndex* m_kXmlIndex;
			void RegistIDStatic(tcstr szName,int id);
			void TestUnit_xmllid();
		};

		//--------------------------------------------------------------------------
		jSINGTON_INTERFACE_DEFINE(JBASE_API , jStringTable, jIStringTable)
			//--------------------------------------------------------------------------
		{
			assert(!s_isStatic_xmlid_registed);
			m_kXmlIndex = new kXmlIndex(nINDEX::EXmlID_END);
			assert(m_kXmlIndex);

#define jxDECL_ENUM(X)  RegistIDStatic(_T(#X) , nINDEX::x##X);

			jxDECL_ENUM(NULL) // -> xmlid == 0이다.

				jXML_STRING_ENUM()
				jXML_STRING_ENUM2()

				jxDECL_ENUM(NULL_END_REALY_END_NULL); // 이 이후로는 추가하지말것.
#undef jxDECL_ENUM
			s_isStatic_xmlid_registed  =true;
		}


		//--------------------------------------------------------------------------
		// jStringTable 인터페이스 정의
		//--------------------------------------------------------------------------


		kXmlIndex* jStringTable::GetTable(){ return m_kXmlIndex;}

		void jStringTable::clear()
		{
			SAFE_DELETE(m_kXmlIndex);
		}

		jstring_id jStringTable::GetIndex(tcstr  szName)
		{
			return m_kXmlIndex->GetIndex(szName);
		}

		tcstr jStringTable::GetName(jstring_cid idx)
		{
			assert(idx < m_kXmlIndex->m_vecName.size());
			return m_kXmlIndex->m_vecName[idx];	
		}

		void jStringTable::SaveToFile(FILE* fp1)
		{
			//assert(fp);
			nFileSystem::jFolder dm;
			dm.GotoStartDir();
			fname_t buf;
			jt_sprintf(buf,_T("xml_element_tag_%s.txt"),g_ExeEnv.m_szAppNic);
			nFileSystem::UFile fp(buf,_T("at"));

			jvector<tcstr>::iterator it = m_kXmlIndex->m_vecName.begin()
				, ie = m_kXmlIndex->m_vecName.end();

			int iStart = false;
			int i=0;
			for( ; it != ie ; ++it,++i)
			{
				tcstr sz = *it;
				if(!sz) continue;
				if(iStart)
					jt_fprintf(fp , _T("jxDEFINE(%s);\n"),*it);
				if(!jt_strcmp(*it , _T("NULL_END_REALY_END_NULL") ) )
					iStart=true;
			}
		}


		//--------------------------------------------------------------------------
		void jStringTable::RegistIDStatic(tcstr szName,int id)
			//--------------------------------------------------------------------------
		{
			m_kXmlIndex->Regist(szName,id);
#ifdef _DEBUG
			int id1 = GetIndex(szName);
			assert(id1 == id);
			tcstr szName1 = GetName(id);
			assert(!jt_strcmp(szName1,szName ));

#endif
		}

		// cpp모듈내부에서 정의한 jxDEFINE()들을 위한 함수.
		jLIST_TYPEDEF_map(jstring_id* , std::tstring, s_mapPostRegistID);
		static bool s_Inited_mapPostRegistID=false;

		/* jxDEFINE으로 세팅하는 전역 XML ID */ \
		jstring_cid jStringTable::RegistID(tcstr szName,jstring_id* pID)
		{
			if(!s_isStatic_xmlid_registed)
			{
				jMB(_T("ERROR jXml초기화 안됬음: jStringTable::RegistID()"),szName);
				throw;
			}
			if(!s_Inited_mapPostRegistID)
			{
				s_mapPostRegistID[pID]=szName;
				return 0;
			}

			*pID = GetIndex(szName);
#ifdef _DEBUG
			int id1 = GetIndex(szName);
			assert(id1 == *pID);
			tcstr szName1 = GetName(id1);
			assert(!jt_strcmp(szName1,szName ));
#endif

			return *pID;
		}

		void jStringTable::InitByXml()
		{
			s_mapPostRegistID_it it = s_mapPostRegistID.begin(), ie = s_mapPostRegistID.end();
			for( ; it!=ie ; ++it)
			{
				*(it->first) = GetIndex(it->second.c_str());
			}
			s_Inited_mapPostRegistID= true;
			s_mapPostRegistID.clear();

			//jTestUnit_xmllid();

		}

		void jStringTable::TestUnit_xmllid()
		{
#define JTEST_UNIT_XMLID

#ifdef JTEST_UNIT_XMLID
#if 0 // 버그인지 계속에러남
			{
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				nFileSystem::UFile fp(_T("jTest\\kXmlIndex_map2vec.txt"),_T("wt");
				kXmlIndex::map_it it = m_kXmlIndex.m_mapName.begin() , ie = m_kXmlIndex.m_mapName.end();
				int m_int=0;

				for( ; it!=ie ; ++it, ++m_int)
				{
					int id  = it->second;
					tcstr sz = GetName(id) ;
					int i2 = m_kXmlIndex.m_mapName[sz] ;
					assert( i2== id);
					tcstr sz1 = it->first;
					jt_fprintf(fp , _T("[%6d] %d , vec(%s)"),m_int,id, sz);
					//assert(!strcmp(sz1, sz) );
				}
				fp.fclose();
			}
#endif
			{
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				nFileSystem::UFile fp(_T("jTest\\kXmlIndex_vec2map.txt"),_T("wt"));
				size_t int_val = 0;
				size_t iSize = m_kXmlIndex->m_mapName.size();
				for( ; int_val < m_kXmlIndex->m_vecName.size() ; ++int_val)
				{
#pragma warning(disable : 4267)
					tcstr sz = GetName(int_val);
#pragma warning(default : 4267)
					if(!sz) continue;
					int id1 = m_kXmlIndex->m_mapName[sz];
					assert( id1 == int_val );
					jt_fprintf(fp , _T("%s = %d\n"),sz,int_val);
					//jTRACE("%s= %d\n", sz, m_int);
				}
				fp.fclose();
			}
#endif

		}
	}

}
