
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dbcache.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_DBCacheServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef DBCacheServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nDBCacheServer;
DECLARE_INSTANCE_TYPE(S_DC2CH_NEW_TOWN_OK);
DECLARE_INSTANCE_TYPE(S_CH2DC_TOWN_DELETE);
DECLARE_INSTANCE_TYPE(S_DC2CH_TOWN_DELETE_OK);
DECLARE_INSTANCE_TYPE(S_DC_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2DC_ONLINE);
DECLARE_INSTANCE_TYPE(S_DC_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2DC_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_DC_ECHO);
DECLARE_INSTANCE_TYPE(S_DC_ERROR);
DECLARE_INSTANCE_TYPE(S_DC2CH_USER_LOGIN_CHANNEL_OK);
DECLARE_INSTANCE_TYPE(S_DC2CH_USER_LOGIN_CHANNEL_OK2);
#endif // DBCacheServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nDBCacheServer
{
	PT_DBCacheServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef DBCacheServer_jNOTUSE_SQ_CODE
	static void _S_DC2CH_NEW_TOWN_OK_WritePacket(S_DC2CH_NEW_TOWN_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2CH_NEW_TOWN_OK(sendBuf,*pThis));
	}
	static void _S_DC2CH_NEW_TOWN_OK_WriteToPacket(S_DC2CH_NEW_TOWN_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2CH_NEW_TOWN_OK(sendBuf,*pThis));
	}
	void call_sq_DC2CH_NEW_TOWN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2CH_NEW_TOWN_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2CH_NEW_TOWN_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2DC_TOWN_DELETE_WritePacket(S_CH2DC_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2DC_TOWN_DELETE(sendBuf,*pThis));
	}
	static void _S_CH2DC_TOWN_DELETE_WriteToPacket(S_CH2DC_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2DC_TOWN_DELETE(sendBuf,*pThis));
	}
	void call_sq_CH2DC_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2DC_TOWN_DELETE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2DC_TOWN_DELETE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2CH_TOWN_DELETE_OK_WritePacket(S_DC2CH_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2CH_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	static void _S_DC2CH_TOWN_DELETE_OK_WriteToPacket(S_DC2CH_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2CH_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	void call_sq_DC2CH_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2CH_TOWN_DELETE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2CH_TOWN_DELETE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC_HELLO_WritePacket(S_DC_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC_HELLO(sendBuf,*pThis));
	}
	static void _S_DC_HELLO_WriteToPacket(S_DC_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC_HELLO(sendBuf,*pThis));
	}
	void call_sq_DC_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2DC_ONLINE_WritePacket(S_SS2DC_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2DC_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2DC_ONLINE_WriteToPacket(S_SS2DC_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2DC_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2DC_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2DC_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2DC_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC_SERVERINFO_ACK_WritePacket(S_DC_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_DC_SERVERINFO_ACK_WriteToPacket(S_DC_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_DC_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2DC_SERVERINFO_ACK_WritePacket(S_SS2DC_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2DC_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2DC_SERVERINFO_ACK_WriteToPacket(S_SS2DC_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2DC_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2DC_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2DC_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2DC_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC_ECHO_WritePacket(S_DC_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC_ECHO(sendBuf,*pThis));
	}
	static void _S_DC_ECHO_WriteToPacket(S_DC_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC_ECHO(sendBuf,*pThis));
	}
	void call_sq_DC_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC_ECHO , get_msg)(S_DC_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_DC_ERROR_WritePacket(S_DC_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC_ERROR(sendBuf,*pThis));
	}
	static void _S_DC_ERROR_WriteToPacket(S_DC_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC_ERROR(sendBuf,*pThis));
	}
	void call_sq_DC_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2CH_USER_LOGIN_CHANNEL_OK_WritePacket(S_DC2CH_USER_LOGIN_CHANNEL_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2CH_USER_LOGIN_CHANNEL_OK(sendBuf,*pThis));
	}
	static void _S_DC2CH_USER_LOGIN_CHANNEL_OK_WriteToPacket(S_DC2CH_USER_LOGIN_CHANNEL_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2CH_USER_LOGIN_CHANNEL_OK(sendBuf,*pThis));
	}
	void call_sq_DC2CH_USER_LOGIN_CHANNEL_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2CH_USER_LOGIN_CHANNEL_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2CH_USER_LOGIN_CHANNEL_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2CH_USER_LOGIN_CHANNEL_OK2_WritePacket(S_DC2CH_USER_LOGIN_CHANNEL_OK2* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2CH_USER_LOGIN_CHANNEL_OK2(sendBuf,*pThis));
	}
	static void _S_DC2CH_USER_LOGIN_CHANNEL_OK2_WriteToPacket(S_DC2CH_USER_LOGIN_CHANNEL_OK2* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2CH_USER_LOGIN_CHANNEL_OK2(sendBuf,*pThis));
	}
	void call_sq_DC2CH_USER_LOGIN_CHANNEL_OK2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2CH_USER_LOGIN_CHANNEL_OK2 param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2CH_USER_LOGIN_CHANNEL_OK2"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //DBCacheServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__DBCacheServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(DC2CH_NEW_TOWN_OK,jS(DC2CH_NEW_TOWN_OK),0);
		phtl.Insert(CH2DC_TOWN_DELETE,jS(CH2DC_TOWN_DELETE),0);
		phtl.Insert(DC2CH_TOWN_DELETE_OK,jS(DC2CH_TOWN_DELETE_OK),0);
		phtl.Insert(DC_HELLO,jS(DC_HELLO),jS(Job_DBCacheServer));
		phtl.Insert(SS2DC_ONLINE,jS(SS2DC_ONLINE),0);
		phtl.Insert(DC_SERVERINFO_ACK,jS(DC_SERVERINFO_ACK),0);
		phtl.Insert(SS2DC_SERVERINFO_ACK,jS(SS2DC_SERVERINFO_ACK),0);
		phtl.Insert(DC_ECHO,jS(DC_ECHO),0);
		phtl.Insert(DC_ERROR,jS(DC_ERROR),0);
		phtl.Insert(DC2CH_USER_LOGIN_CHANNEL_OK,jS(DC2CH_USER_LOGIN_CHANNEL_OK),0);
		phtl.Insert(DC2CH_USER_LOGIN_CHANNEL_OK2,jS(DC2CH_USER_LOGIN_CHANNEL_OK2),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("DBCacheServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_DC2CH_NEW_TOWN_OK == DC2CH_NEW_TOWN_OK);
		jRAISE_PACKET(pk_CH2DC_TOWN_DELETE == CH2DC_TOWN_DELETE);
		jRAISE_PACKET(pk_DC2CH_TOWN_DELETE_OK == DC2CH_TOWN_DELETE_OK);
		jRAISE_PACKET(pk_DC_HELLO == DC_HELLO);
		jRAISE_PACKET(pk_SS2DC_ONLINE == SS2DC_ONLINE);
		jRAISE_PACKET(pk_DC_SERVERINFO_ACK == DC_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2DC_SERVERINFO_ACK == SS2DC_SERVERINFO_ACK);
		jRAISE_PACKET(pk_DC_ECHO == DC_ECHO);
		jRAISE_PACKET(pk_DC_ERROR == DC_ERROR);
		jRAISE_PACKET(pk_DC2CH_USER_LOGIN_CHANNEL_OK == DC2CH_USER_LOGIN_CHANNEL_OK);
		jRAISE_PACKET(pk_DC2CH_USER_LOGIN_CHANNEL_OK2 == DC2CH_USER_LOGIN_CHANNEL_OK2);

		#ifndef DBCacheServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_DC2CH_NEW_TOWN_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_var(index,"channelid_t")
			jSQ_var(town,"Use_Town")
			jSQ_var(isCapital,"bool")
			jSQ_gfn(S_DC2CH_NEW_TOWN_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2CH_NEW_TOWN_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2DC_TOWN_DELETE)
			jSQ_var(pid,"player_id_t")
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_CH2DC_TOWN_DELETE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2DC_TOWN_DELETE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2CH_TOWN_DELETE_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_DC2CH_TOWN_DELETE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2CH_TOWN_DELETE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_DC_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2DC_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2DC_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2DC_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_DC_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2DC_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2DC_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2DC_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC_ECHO)
			jSQ_gfn(S_DC_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_DC_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_DC_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2CH_USER_LOGIN_CHANNEL_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_var(user,"nAQ::Use_User")
			jSQ_fn(get_town,"int i","return nAQ::Use_Town*")
			jSQ_fn(set_town,"int i,nAQ::Use_Town* data","")
			jSQ_fn(insert_town,"nAQ::Use_Town* data","")
			jSQ_fn(clear_town,"","")
			jSQ_fn(size_town,"","return size_t")
			jSQ_gfn(S_DC2CH_USER_LOGIN_CHANNEL_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2CH_USER_LOGIN_CHANNEL_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2CH_USER_LOGIN_CHANNEL_OK2)
			jSQ_var(pid,"player_id_t")
			jSQ_fn(get_hero,"int i","return nAQ::Use_Hero*")
			jSQ_fn(set_hero,"int i,nAQ::Use_Hero* data","")
			jSQ_fn(insert_hero,"nAQ::Use_Hero* data","")
			jSQ_fn(clear_hero,"","")
			jSQ_fn(size_hero,"","return size_t")
			jSQ_fn(get_force,"int i","return nAQ::Use_Force*")
			jSQ_fn(set_force,"int i,nAQ::Use_Force* data","")
			jSQ_fn(insert_force,"nAQ::Use_Force* data","")
			jSQ_fn(clear_force,"","")
			jSQ_fn(size_force,"","return size_t")
			jSQ_gfn(S_DC2CH_USER_LOGIN_CHANNEL_OK2,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2CH_USER_LOGIN_CHANNEL_OK2,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //DBCacheServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__DBCacheServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("DBCacheServer"));
	}


}/* nDBCacheServer */ }/*nNET*/ } //nMech


#ifndef DBCacheServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_DBCacheServer(DBCacheServer);
jxDEFINE_DBCacheServer(DC2CH_NEW_TOWN_OK);
jxDEFINE_DBCacheServer(CH2DC_TOWN_DELETE);
jxDEFINE_DBCacheServer(DC2CH_TOWN_DELETE_OK);
jxDEFINE_DBCacheServer(DC_HELLO);
jxDEFINE_DBCacheServer(SS2DC_ONLINE);
jxDEFINE_DBCacheServer(DC_SERVERINFO_ACK);
jxDEFINE_DBCacheServer(SS2DC_SERVERINFO_ACK);
jxDEFINE_DBCacheServer(DC_ECHO);
jxDEFINE_DBCacheServer(DC_ERROR);
jxDEFINE_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK);
jxDEFINE_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK2);
#endif // DBCacheServer_jNOT_USE_PACKET_PLUGIN_HELP