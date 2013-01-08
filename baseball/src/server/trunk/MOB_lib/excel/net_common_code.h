/* file : net_common_code.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-10-08 17:26:10
comp.: actoz.com
title : 
desc : 

*/

#ifndef __net_common_code_header__
#define __net_common_code_header__
#pragma once


namespace nMech
{
	typedef int undefined_t;

	struct jEnumString
	{
		int m_id;
		tcstr m_szName;
		tcstr m_szNicName;
		static jEnumString* Get(jEnumString* pList, int iIndex)
		{
			if( iIndex==0) return 0;
			int tot = pList[0].m_id;
			for(int i=1; i<=tot;++i )
			{
				if(pList[i].m_id == iIndex) 
					return &pList[i];
			}
			return 0;
		}
		static jEnumString* Get(jEnumString* pList, tcstr szName)
		{
			int tot = pList[0].m_id;
			for(int i=1; i<=tot;++i )
			{
				if(!jt_strcmp(pList[i].m_szName , szName) )
					return &pList[i];
			}
			return 0;
		}

		static void DebugPrint(jEnumString* pList)
		{
			int tot = pList[0].m_id;
			for(int i=1; i<=tot;++i )
			{
				jLOG(_T("%d : %s : %s"), pList[i].m_id , pList[i].m_szName, pList[i].m_szNicName);
			}
		}
	};
	#define Get_jENUM(ns,X,INDEX) jEnumString::Get(ns::g_ES_##X, INDEX);
	#define DebugPrint_jENUM(ns,X) jLOG_T(_T(#ns "::" #X " (%d)" ) , ns::g_ES_##X[0].m_id); jEnumString::DebugPrint(ns::g_ES_##X);

	#define jENUM_s(pEnum ,ns,X,INDEX) jEnumString * pEnum = jEnumString::Get(ns::g_ES_##X, INDEX);\
	if(!pEnum)\
	{\
		DebugPrint_jENUM(ns,X);\
		jWARN_T(_T( #X "- %s not found"), jS(INDEX) );\
	}

	#define jENUM_i(pEnum ,ns,X,INDEX) jEnumString * pEnum = jEnumString::Get(ns::g_ES_##X, INDEX);\
	if(!pEnum)\
	{\
		DebugPrint_jENUM(ns,X);\
		jWARN_T(_T( #X "- %d not found"), INDEX);\
	}


}//nMech


#define net_StringID_enum_gen(id,name,help) e##name=id,
#define net_stringID_gen_EnumStringTable(id,name,help) ,{id,jS(name),_T(help) }


#endif // __net_common_code_header__
