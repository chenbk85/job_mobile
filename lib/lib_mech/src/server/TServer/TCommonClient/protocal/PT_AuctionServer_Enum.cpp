
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_auction.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_AuctionServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef AuctionServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nAuctionServer;
DECLARE_INSTANCE_TYPE(S_A_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2A_ONLINE);
DECLARE_INSTANCE_TYPE(S_A_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2A_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_A_ECHO);
DECLARE_INSTANCE_TYPE(S_A_ERROR);
#endif // AuctionServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nAuctionServer
{
	PT_AuctionServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef AuctionServer_jNOTUSE_SQ_CODE
	static void _S_A_HELLO_WritePacket(S_A_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A_HELLO(sendBuf,*pThis));
	}
	static void _S_A_HELLO_WriteToPacket(S_A_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A_HELLO(sendBuf,*pThis));
	}
	void call_sq_A_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2A_ONLINE_WritePacket(S_SS2A_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2A_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2A_ONLINE_WriteToPacket(S_SS2A_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2A_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2A_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2A_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2A_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A_SERVERINFO_ACK_WritePacket(S_A_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_A_SERVERINFO_ACK_WriteToPacket(S_A_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_A_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2A_SERVERINFO_ACK_WritePacket(S_SS2A_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2A_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2A_SERVERINFO_ACK_WriteToPacket(S_SS2A_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2A_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2A_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2A_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2A_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A_ECHO_WritePacket(S_A_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A_ECHO(sendBuf,*pThis));
	}
	static void _S_A_ECHO_WriteToPacket(S_A_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A_ECHO(sendBuf,*pThis));
	}
	void call_sq_A_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_A_ECHO , get_msg)(S_A_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_A_ERROR_WritePacket(S_A_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A_ERROR(sendBuf,*pThis));
	}
	static void _S_A_ERROR_WriteToPacket(S_A_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A_ERROR(sendBuf,*pThis));
	}
	void call_sq_A_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //AuctionServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__AuctionServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(A_HELLO,jS(A_HELLO),jS(Job_AuctionServer));
		phtl.Insert(SS2A_ONLINE,jS(SS2A_ONLINE),0);
		phtl.Insert(A_SERVERINFO_ACK,jS(A_SERVERINFO_ACK),0);
		phtl.Insert(SS2A_SERVERINFO_ACK,jS(SS2A_SERVERINFO_ACK),0);
		phtl.Insert(A_ECHO,jS(A_ECHO),0);
		phtl.Insert(A_ERROR,jS(A_ERROR),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("AuctionServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_A_HELLO == A_HELLO);
		jRAISE_PACKET(pk_SS2A_ONLINE == SS2A_ONLINE);
		jRAISE_PACKET(pk_A_SERVERINFO_ACK == A_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2A_SERVERINFO_ACK == SS2A_SERVERINFO_ACK);
		jRAISE_PACKET(pk_A_ECHO == A_ECHO);
		jRAISE_PACKET(pk_A_ERROR == A_ERROR);

		#ifndef AuctionServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_A_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_A_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2A_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2A_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2A_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_A_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2A_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2A_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2A_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A_ECHO)
			jSQ_gfn(S_A_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_A_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_A_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //AuctionServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__AuctionServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("AuctionServer"));
	}


}/* nAuctionServer */ }/*nNET*/ } //nMech


#ifndef AuctionServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_AuctionServer(AuctionServer);
jxDEFINE_AuctionServer(A_HELLO);
jxDEFINE_AuctionServer(SS2A_ONLINE);
jxDEFINE_AuctionServer(A_SERVERINFO_ACK);
jxDEFINE_AuctionServer(SS2A_SERVERINFO_ACK);
jxDEFINE_AuctionServer(A_ECHO);
jxDEFINE_AuctionServer(A_ERROR);
#endif // AuctionServer_jNOT_USE_PACKET_PLUGIN_HELP