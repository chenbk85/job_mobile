
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_command.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_CommandServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef CommandServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nCommandServer;
DECLARE_INSTANCE_TYPE(S_CD_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2CD_ONLINE);
DECLARE_INSTANCE_TYPE(S_CD2SS_ONLINE_OK);
DECLARE_INSTANCE_TYPE(S_CD_ECHO);
DECLARE_INSTANCE_TYPE(S_CD_SERVER_ONLINE);
DECLARE_INSTANCE_TYPE(S_CD_SERVER_OFFLINE);
DECLARE_INSTANCE_TYPE(S_CD_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2CD_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_CD_ERROR);
DECLARE_INSTANCE_TYPE(S_CD2_CENTRAL_RESTART);
#endif // CommandServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nCommandServer
{
	PT_CommandServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef CommandServer_jNOTUSE_SQ_CODE
	static void _S_CD_HELLO_WritePacket(S_CD_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_HELLO(sendBuf,*pThis));
	}
	static void _S_CD_HELLO_WriteToPacket(S_CD_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_HELLO(sendBuf,*pThis));
	}
	void call_sq_CD_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2CD_ONLINE_WritePacket(S_SS2CD_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2CD_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2CD_ONLINE_WriteToPacket(S_SS2CD_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2CD_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2CD_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2CD_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2CD_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD2SS_ONLINE_OK_WritePacket(S_CD2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD2SS_ONLINE_OK(sendBuf,*pThis));
	}
	static void _S_CD2SS_ONLINE_OK_WriteToPacket(S_CD2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD2SS_ONLINE_OK(sendBuf,*pThis));
	}
	void call_sq_CD2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD2SS_ONLINE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD2SS_ONLINE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD_ECHO_WritePacket(S_CD_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_ECHO(sendBuf,*pThis));
	}
	static void _S_CD_ECHO_WriteToPacket(S_CD_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_ECHO(sendBuf,*pThis));
	}
	void call_sq_CD_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CD_ECHO , get_msg)(S_CD_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_CD_SERVER_ONLINE_WritePacket(S_CD_SERVER_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_SERVER_ONLINE(sendBuf,*pThis));
	}
	static void _S_CD_SERVER_ONLINE_WriteToPacket(S_CD_SERVER_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_SERVER_ONLINE(sendBuf,*pThis));
	}
	void call_sq_CD_SERVER_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_SERVER_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_SERVER_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD_SERVER_OFFLINE_WritePacket(S_CD_SERVER_OFFLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_SERVER_OFFLINE(sendBuf,*pThis));
	}
	static void _S_CD_SERVER_OFFLINE_WriteToPacket(S_CD_SERVER_OFFLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_SERVER_OFFLINE(sendBuf,*pThis));
	}
	void call_sq_CD_SERVER_OFFLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_SERVER_OFFLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_SERVER_OFFLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD_SERVERINFO_ACK_WritePacket(S_CD_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_CD_SERVERINFO_ACK_WriteToPacket(S_CD_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_CD_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2CD_SERVERINFO_ACK_WritePacket(S_SS2CD_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2CD_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2CD_SERVERINFO_ACK_WriteToPacket(S_SS2CD_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2CD_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2CD_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2CD_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2CD_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD_ERROR_WritePacket(S_CD_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD_ERROR(sendBuf,*pThis));
	}
	static void _S_CD_ERROR_WriteToPacket(S_CD_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD_ERROR(sendBuf,*pThis));
	}
	void call_sq_CD_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD2_CENTRAL_RESTART_WritePacket(S_CD2_CENTRAL_RESTART* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD2_CENTRAL_RESTART(sendBuf,*pThis));
	}
	static void _S_CD2_CENTRAL_RESTART_WriteToPacket(S_CD2_CENTRAL_RESTART* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD2_CENTRAL_RESTART(sendBuf,*pThis));
	}
	void call_sq_CD2_CENTRAL_RESTART(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD2_CENTRAL_RESTART param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD2_CENTRAL_RESTART"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //CommandServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__CommandServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(CD_HELLO,jS(CD_HELLO),jS(Job_CommandServer));
		phtl.Insert(SS2CD_ONLINE,jS(SS2CD_ONLINE),0);
		phtl.Insert(CD2SS_ONLINE_OK,jS(CD2SS_ONLINE_OK),0);
		phtl.Insert(CD_ECHO,jS(CD_ECHO),0);
		phtl.Insert(CD_SERVER_ONLINE,jS(CD_SERVER_ONLINE),0);
		phtl.Insert(CD_SERVER_OFFLINE,jS(CD_SERVER_OFFLINE),0);
		phtl.Insert(CD_SERVERINFO_ACK,jS(CD_SERVERINFO_ACK),0);
		phtl.Insert(SS2CD_SERVERINFO_ACK,jS(SS2CD_SERVERINFO_ACK),0);
		phtl.Insert(CD_ERROR,jS(CD_ERROR),0);
		phtl.Insert(CD2_CENTRAL_RESTART,jS(CD2_CENTRAL_RESTART),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("CommandServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_CD_HELLO == CD_HELLO);
		jRAISE_PACKET(pk_SS2CD_ONLINE == SS2CD_ONLINE);
		jRAISE_PACKET(pk_CD2SS_ONLINE_OK == CD2SS_ONLINE_OK);
		jRAISE_PACKET(pk_CD_ECHO == CD_ECHO);
		jRAISE_PACKET(pk_CD_SERVER_ONLINE == CD_SERVER_ONLINE);
		jRAISE_PACKET(pk_CD_SERVER_OFFLINE == CD_SERVER_OFFLINE);
		jRAISE_PACKET(pk_CD_SERVERINFO_ACK == CD_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2CD_SERVERINFO_ACK == SS2CD_SERVERINFO_ACK);
		jRAISE_PACKET(pk_CD_ERROR == CD_ERROR);
		jRAISE_PACKET(pk_CD2_CENTRAL_RESTART == CD2_CENTRAL_RESTART);

		#ifndef CommandServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_CD_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_CD_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2CD_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2CD_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2CD_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD2SS_ONLINE_OK)
			jSQ_var(you,"jServerInfo")
			jSQ_fn(get_s,"int i","return jServerInfo*")
			jSQ_fn(set_s,"int i,jServerInfo* data","")
			jSQ_fn(insert_s,"jServerInfo* data","")
			jSQ_fn(clear_s,"","")
			jSQ_fn(size_s,"","return size_t")
			jSQ_gfn(S_CD2SS_ONLINE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD2SS_ONLINE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD_ECHO)
			jSQ_gfn(S_CD_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_CD_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD_SERVER_ONLINE)
			jSQ_var(s,"jServerInfo")
			jSQ_gfn(S_CD_SERVER_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_SERVER_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD_SERVER_OFFLINE)
			jSQ_var(sid,"serverid_t")
			jSQ_gfn(S_CD_SERVER_OFFLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_SERVER_OFFLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_CD_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2CD_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2CD_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2CD_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_CD_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD2_CENTRAL_RESTART)
			jSQ_gfn(S_CD2_CENTRAL_RESTART,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD2_CENTRAL_RESTART,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //CommandServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__CommandServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("CommandServer"));
	}


}/* nCommandServer */ }/*nNET*/ } //nMech


#ifndef CommandServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_CommandServer(CommandServer);
jxDEFINE_CommandServer(CD_HELLO);
jxDEFINE_CommandServer(SS2CD_ONLINE);
jxDEFINE_CommandServer(CD2SS_ONLINE_OK);
jxDEFINE_CommandServer(CD_ECHO);
jxDEFINE_CommandServer(CD_SERVER_ONLINE);
jxDEFINE_CommandServer(CD_SERVER_OFFLINE);
jxDEFINE_CommandServer(CD_SERVERINFO_ACK);
jxDEFINE_CommandServer(SS2CD_SERVERINFO_ACK);
jxDEFINE_CommandServer(CD_ERROR);
jxDEFINE_CommandServer(CD2_CENTRAL_RESTART);
#endif // CommandServer_jNOT_USE_PACKET_PLUGIN_HELP