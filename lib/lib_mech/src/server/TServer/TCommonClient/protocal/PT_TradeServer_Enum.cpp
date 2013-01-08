
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_trade.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_TradeServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef TradeServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nTradeServer;
DECLARE_INSTANCE_TYPE(S_T_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2T_ONLINE);
DECLARE_INSTANCE_TYPE(S_T_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2T_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_T_ECHO);
DECLARE_INSTANCE_TYPE(S_T_ERROR);
#endif // TradeServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nTradeServer
{
	PT_TradeServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef TradeServer_jNOTUSE_SQ_CODE
	static void _S_T_HELLO_WritePacket(S_T_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_T_HELLO(sendBuf,*pThis));
	}
	static void _S_T_HELLO_WriteToPacket(S_T_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_T_HELLO(sendBuf,*pThis));
	}
	void call_sq_T_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_T_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_T_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2T_ONLINE_WritePacket(S_SS2T_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2T_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2T_ONLINE_WriteToPacket(S_SS2T_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2T_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2T_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2T_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2T_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_T_SERVERINFO_ACK_WritePacket(S_T_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_T_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_T_SERVERINFO_ACK_WriteToPacket(S_T_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_T_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_T_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_T_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_T_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2T_SERVERINFO_ACK_WritePacket(S_SS2T_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2T_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2T_SERVERINFO_ACK_WriteToPacket(S_SS2T_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2T_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2T_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2T_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2T_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_T_ECHO_WritePacket(S_T_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_T_ECHO(sendBuf,*pThis));
	}
	static void _S_T_ECHO_WriteToPacket(S_T_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_T_ECHO(sendBuf,*pThis));
	}
	void call_sq_T_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_T_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_T_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_T_ECHO , get_msg)(S_T_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_T_ERROR_WritePacket(S_T_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_T_ERROR(sendBuf,*pThis));
	}
	static void _S_T_ERROR_WriteToPacket(S_T_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_T_ERROR(sendBuf,*pThis));
	}
	void call_sq_T_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_T_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_T_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //TradeServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__TradeServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(T_HELLO,jS(T_HELLO),jS(Job_TradeServer));
		phtl.Insert(SS2T_ONLINE,jS(SS2T_ONLINE),0);
		phtl.Insert(T_SERVERINFO_ACK,jS(T_SERVERINFO_ACK),0);
		phtl.Insert(SS2T_SERVERINFO_ACK,jS(SS2T_SERVERINFO_ACK),0);
		phtl.Insert(T_ECHO,jS(T_ECHO),0);
		phtl.Insert(T_ERROR,jS(T_ERROR),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("TradeServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_T_HELLO == T_HELLO);
		jRAISE_PACKET(pk_SS2T_ONLINE == SS2T_ONLINE);
		jRAISE_PACKET(pk_T_SERVERINFO_ACK == T_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2T_SERVERINFO_ACK == SS2T_SERVERINFO_ACK);
		jRAISE_PACKET(pk_T_ECHO == T_ECHO);
		jRAISE_PACKET(pk_T_ERROR == T_ERROR);

		#ifndef TradeServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_T_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_T_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_T_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2T_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2T_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2T_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_T_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_T_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_T_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2T_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2T_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2T_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_T_ECHO)
			jSQ_gfn(S_T_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_T_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_T_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_T_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_T_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_T_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //TradeServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__TradeServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("TradeServer"));
	}


}/* nTradeServer */ }/*nNET*/ } //nMech


#ifndef TradeServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_TradeServer(TradeServer);
jxDEFINE_TradeServer(T_HELLO);
jxDEFINE_TradeServer(SS2T_ONLINE);
jxDEFINE_TradeServer(T_SERVERINFO_ACK);
jxDEFINE_TradeServer(SS2T_SERVERINFO_ACK);
jxDEFINE_TradeServer(T_ECHO);
jxDEFINE_TradeServer(T_ERROR);
#endif // TradeServer_jNOT_USE_PACKET_PLUGIN_HELP