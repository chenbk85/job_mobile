
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_game.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_GameServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef GameServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nGameServer;
DECLARE_INSTANCE_TYPE(S_G_ECHO);
DECLARE_INSTANCE_TYPE(S_G_ERROR);
DECLARE_INSTANCE_TYPE(S_G_HELLO);
DECLARE_INSTANCE_TYPE(S_D2X_NOTICE);
DECLARE_INSTANCE_TYPE(S_X2D_NOTICE_TEST);
DECLARE_INSTANCE_TYPE(S_D_ECHO);
DECLARE_INSTANCE_TYPE(S_X2G_CHAT);
DECLARE_INSTANCE_TYPE(S_G2X_CHAT);
DECLARE_INSTANCE_TYPE(S_X2G_USER_EXIT);
DECLARE_INSTANCE_TYPE(S_G2X_USER_EXIT);
#endif // GameServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nGameServer
{
	PT_GameServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef GameServer_jNOTUSE_SQ_CODE
	static void _S_G_ECHO_WritePacket(S_G_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_G_ECHO(sendBuf,*pThis));
	}
	static void _S_G_ECHO_WriteToPacket(S_G_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_G_ECHO(sendBuf,*pThis));
	}
	void call_sq_G_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_G_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_G_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_G_ECHO , get_msg)(S_G_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_G_ERROR_WritePacket(S_G_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_G_ERROR(sendBuf,*pThis));
	}
	static void _S_G_ERROR_WriteToPacket(S_G_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_G_ERROR(sendBuf,*pThis));
	}
	void call_sq_G_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_G_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_G_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_G_HELLO_WritePacket(S_G_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_G_HELLO(sendBuf,*pThis));
	}
	static void _S_G_HELLO_WriteToPacket(S_G_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_G_HELLO(sendBuf,*pThis));
	}
	void call_sq_G_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_G_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_G_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_D2X_NOTICE_WritePacket(S_D2X_NOTICE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_D2X_NOTICE(sendBuf,*pThis));
	}
	static void _S_D2X_NOTICE_WriteToPacket(S_D2X_NOTICE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_D2X_NOTICE(sendBuf,*pThis));
	}
	void call_sq_D2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_D2X_NOTICE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_D2X_NOTICE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_D2X_NOTICE , get_msg)(S_D2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_D2X_NOTICE , get_date)(S_D2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_date(buf));
	}

	static void _S_X2D_NOTICE_TEST_WritePacket(S_X2D_NOTICE_TEST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2D_NOTICE_TEST(sendBuf,*pThis));
	}
	static void _S_X2D_NOTICE_TEST_WriteToPacket(S_X2D_NOTICE_TEST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2D_NOTICE_TEST(sendBuf,*pThis));
	}
	void call_sq_X2D_NOTICE_TEST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2D_NOTICE_TEST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2D_NOTICE_TEST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2D_NOTICE_TEST , get_msg)(S_X2D_NOTICE_TEST* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2D_NOTICE_TEST , get_date)(S_X2D_NOTICE_TEST* pThis)
	{
		fname_t buf;return (pThis->get_date(buf));
	}

	static void _S_D_ECHO_WritePacket(S_D_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_D_ECHO(sendBuf,*pThis));
	}
	static void _S_D_ECHO_WriteToPacket(S_D_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_D_ECHO(sendBuf,*pThis));
	}
	void call_sq_D_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_D_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_D_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2G_CHAT_WritePacket(S_X2G_CHAT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2G_CHAT(sendBuf,*pThis));
	}
	static void _S_X2G_CHAT_WriteToPacket(S_X2G_CHAT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2G_CHAT(sendBuf,*pThis));
	}
	void call_sq_X2G_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2G_CHAT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2G_CHAT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2G_CHAT , get_msg)(S_X2G_CHAT* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_G2X_CHAT_WritePacket(S_G2X_CHAT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_G2X_CHAT(sendBuf,*pThis));
	}
	static void _S_G2X_CHAT_WriteToPacket(S_G2X_CHAT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_G2X_CHAT(sendBuf,*pThis));
	}
	void call_sq_G2X_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_G2X_CHAT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_G2X_CHAT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_G2X_CHAT , get_msg)(S_G2X_CHAT* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_X2G_USER_EXIT_WritePacket(S_X2G_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2G_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_X2G_USER_EXIT_WriteToPacket(S_X2G_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2G_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_X2G_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2G_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2G_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_G2X_USER_EXIT_WritePacket(S_G2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_G2X_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_G2X_USER_EXIT_WriteToPacket(S_G2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_G2X_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_G2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_G2X_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_G2X_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //GameServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__GameServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(G_ECHO,jS(G_ECHO),0);
		phtl.Insert(G_ERROR,jS(G_ERROR),0);
		phtl.Insert(G_HELLO,jS(G_HELLO),0);
		phtl.Insert(D2X_NOTICE,jS(D2X_NOTICE),0);
		phtl.Insert(X2D_NOTICE_TEST,jS(X2D_NOTICE_TEST),0);
		phtl.Insert(D_ECHO,jS(D_ECHO),0);
		phtl.Insert(X2G_CHAT,jS(X2G_CHAT),0);
		phtl.Insert(G2X_CHAT,jS(G2X_CHAT),0);
		phtl.Insert(X2G_USER_EXIT,jS(X2G_USER_EXIT),0);
		phtl.Insert(G2X_USER_EXIT,jS(G2X_USER_EXIT),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("GameServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_G_ECHO == G_ECHO);
		jRAISE_PACKET(pk_G_ERROR == G_ERROR);
		jRAISE_PACKET(pk_G_HELLO == G_HELLO);
		jRAISE_PACKET(pk_D2X_NOTICE == D2X_NOTICE);
		jRAISE_PACKET(pk_X2D_NOTICE_TEST == X2D_NOTICE_TEST);
		jRAISE_PACKET(pk_D_ECHO == D_ECHO);
		jRAISE_PACKET(pk_X2G_CHAT == X2G_CHAT);
		jRAISE_PACKET(pk_G2X_CHAT == G2X_CHAT);
		jRAISE_PACKET(pk_X2G_USER_EXIT == X2G_USER_EXIT);
		jRAISE_PACKET(pk_G2X_USER_EXIT == G2X_USER_EXIT);

		#ifndef GameServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_G_ECHO)
			jSQ_gfn(S_G_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_gfn(S_G_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_G_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_G_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_G_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_G_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_G_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_G_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_G_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_D2X_NOTICE)
			jSQ_var(info,"jNoticeInfo")
			jSQ_gfn(S_D2X_NOTICE,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_D2X_NOTICE,get_date, "","return net_string")
			jSQ_fn(set_date,"tcstr sz","")
			jSQ_gfn(S_D2X_NOTICE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_D2X_NOTICE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2D_NOTICE_TEST)
			jSQ_var(info,"jNoticeInfo")
			jSQ_gfn(S_X2D_NOTICE_TEST,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_X2D_NOTICE_TEST,get_date, "","return net_string")
			jSQ_fn(set_date,"tcstr sz","")
			jSQ_gfn(S_X2D_NOTICE_TEST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2D_NOTICE_TEST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_D_ECHO)
			jSQ_gfn(S_D_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_D_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2G_CHAT)
			jSQ_gfn(S_X2G_CHAT,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_gfn(S_X2G_CHAT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2G_CHAT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_G2X_CHAT)
			jSQ_gfn(S_G2X_CHAT,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_gfn(S_G2X_CHAT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_G2X_CHAT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2G_USER_EXIT)
			jSQ_gfn(S_X2G_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2G_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_G2X_USER_EXIT)
			jSQ_gfn(S_G2X_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_G2X_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //GameServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__GameServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("GameServer"));
	}


}/* nGameServer */ }/*nNET*/ } //nMech


#ifndef GameServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_GameServer(GameServer);
jxDEFINE_GameServer(G_ECHO);
jxDEFINE_GameServer(G_ERROR);
jxDEFINE_GameServer(G_HELLO);
jxDEFINE_GameServer(D2X_NOTICE);
jxDEFINE_GameServer(X2D_NOTICE_TEST);
jxDEFINE_GameServer(D_ECHO);
jxDEFINE_GameServer(X2G_CHAT);
jxDEFINE_GameServer(G2X_CHAT);
jxDEFINE_GameServer(X2G_USER_EXIT);
jxDEFINE_GameServer(G2X_USER_EXIT);
#endif // GameServer_jNOT_USE_PACKET_PLUGIN_HELP