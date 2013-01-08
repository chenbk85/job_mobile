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

#define jError_USING_DEV_MODE
#ifdef jError_USING_DEV_MODE

	struct jClientResult
	{
		acstr str;
		jClientResult(acstr s) : str(s){}
	};
	struct jServerResult
	{
		acstr str;
		jServerResult(acstr s) : str(s){}
	};

#define CR_t(X) (#X)
#define SR_t(X) (#X)

	typedef acstr jError_Creator_arg_t;

	struct /*jNET_COMMON_LIB_API */ jError
	{
		astring iClient;
		astring iServer;
		jError(){}
		jError(jError_Creator_arg_t s, jError_Creator_arg_t c): iServer(s ? s :("")),iClient(c ? c:("")){ }
		jError(const jServerResult& s, const jClientResult &c): iServer(s.str ? s.str :""),iClient(c.str ? c.str :""){ }

		bool isOk()
		{
			return !isError();
		}
		bool isError()
		{ 
			size_t i = ja_strlen(iClient.c_str());
			size_t j = ja_strlen(iServer.c_str());
			size_t k = i || j;
			return  k;
		}
		acstr jError::ToStringS(){ return iClient.c_str();}
		acstr jError::ToStringC(){ return iServer.c_str();}
		std::pair<acstr ,acstr> ToString(name1024_t buf)
		{
			jt_sprintf(buf, _T("%s:%s"), jT(iClient.c_str()), jT(iServer.c_str()) );
			return std::pair<acstr,acstr>(iClient.c_str(),iServer.c_str());
		}
	};

	inline bool operator ==(jError & e, jClientResult id)
	{
		return (e.iServer == id.str);
	}
	inline bool operator ==(jError & e, jServerResult id)
	{
		return (e.iClient== id.str);
	}

#else
	typedef uint16 jError_Creator_arg_t;

	struct jNET_COMMON_LIB_API jError
	{
		typedef tcstr client_tcstr;
		typedef tcstr server_tcstr;
		union
		{
			struct 
			{
				uint16 iServer;
				uint16 iClient;
			};
			int	iError;
		};
		jError(): iError(0){}
		jError(jError_Creator_arg_t iS, jError_Creator_arg_t iC): iServer(iS),iClient(iC){ }

		bool isOk(){return !iError;}
		bool isError(){ return iError;}
		jError::server_tcstr jError::ToStringS();// 주의 클라이언트 코드에서는 사용안함
		jError::client_tcstr jError::ToStringC();
		std::pair<server_tcstr ,client_tcstr> ToString(name1024_t buf);// 주의 클라이언트 코드에서는 사용안함
	};

#endif

}//nMech


#define net_StringID_enum_gen(id,name,help) e##name=id,
#define net_stringID_gen_EnumStringTable(id,name,help) ,{id,jS(name),_T(help) }


#endif // __net_common_code_header__
