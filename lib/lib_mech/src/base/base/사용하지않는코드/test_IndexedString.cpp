/* file : test_IndexedString.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-21 11:09:23
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "IndexedString.h"
#include "IndexedStringDB.h"
#include "jTestUnit.h"
#include "base/jFolder.h"

using namespace nMech;
using namespace nMech::nString;

jxDEFINE(test_string_asdf);
namespace nMech
{
	StringID test_StringID = jx(test_string_asdf); // 해당 DLL ,EXE 모듈마다 정의해두어야함.
}

namespace 
{
		jTEST_SUITE_BEGIN(string_test)
		jTEST(jIStringTable_)
		{
			jCHECK(jx(NULL) == jStringID::make_StringID(0) );
			jCHECK(std::tstring(Get_jIStringTable()->GetName(jx(NULL))) == std::tstring(_T("NULL")) );

			jStringID idLOG_OFF = Get_jIStringTable()->GetIndex(_T("LOG_OFF"));
			jCHECK(jx(LOG_OFF) == idLOG_OFF);
			jEQUAL(sizeof(StringID),sizeof(jStringID_vt) );
			jEQUAL(sizeof(StringID),4);


			StringID id1 =test_StringID;
			jCHECK(test_StringID == jx(test_string_asdf));
			StringID id_jNet_OGS = Get_jIStringTable()->GetIndex(_T("test_string_asdf"));
			jCHECK(test_StringID == id_jNet_OGS);
			tstring s_jNet_OGS = Get_jIStringTable()->GetName(id_jNet_OGS);
			jCHECK(s_jNet_OGS==_T("test_string_asdf"));


#define JTEST_UNIT_XMLID

#ifdef JTEST_UNIT_XMLID
#if 0 // 버그인지 계속에러남
			{
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				nFileSystem::UFile fp(_T("jTest\\IndexedStringDB_map2vec.txt"),_T("wt");
				IndexedStringDB::map_it it = Get_jIStringTable()->GetTable().m_mapName.begin() , ie = Get_jIStringTable()->GetTable().m_mapName.end();
				int m_int=0;

				for( ; it!=ie ; ++it, ++m_int)
				{
					int id.id  = it->second;
					tcstr sz = GetName(id.id) ;
					int i2 = Get_jIStringTable()->GetTable().m_mapName[sz] ;
					assert( i2== id.id);
					tcstr sz1 = it->first;
					jt_fprintf(fp , _T("[%6d] %d , vec(%s)"),m_int,id.id, sz);
					//assert(!strcmp(sz1, sz) );
				}
				fp.fclose();
			}
#endif
			{
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				dm.CreateDir(_T("test"));
				nFileSystem::UFile fp(_T("test\\IndexedStringDB_vec2map.txt"),_T("wt"));
				jStringID_vt m_int = 0;
				size_t iSize = Get_jIStringTable()->GetTable()->m_mapName.size();
				for( ; m_int < Get_jIStringTable()->GetTable()->m_vecName.size() ; ++m_int)
				{
#pragma warning(disable : 4267)
					tcstr sz = Get_jIStringTable()->GetName(nString::jStringID::make_StringID(m_int));
#pragma warning(default : 4267)
					if(!sz) continue;
					jStringID_vt id1 = Get_jIStringTable()->GetTable()->m_mapName[sz];
					assert( id1 == m_int );
					jt_fprintf(fp , _T("%s = %d\n"),sz,m_int);
				}
				fp.fclose();
			}
#endif

		}

		jTEST_SUITE_END(string_test)

}

