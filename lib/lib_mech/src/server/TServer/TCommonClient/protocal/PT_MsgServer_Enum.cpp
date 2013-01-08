
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_msg.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_MsgServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef MsgServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nMsgServer;
DECLARE_INSTANCE_TYPE(S_MG_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2MG_ONLINE);
DECLARE_INSTANCE_TYPE(S_MG_ECHO);
DECLARE_INSTANCE_TYPE(S_MG_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2MG_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_MG_ERROR);
#endif // MsgServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nMsgServer
{
	PT_MsgServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef MsgServer_jNOTUSE_SQ_CODE
	static void _S_MG_HELLO_WritePacket(S_MG_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_MG_HELLO(sendBuf,*pThis));
	}
	static void _S_MG_HELLO_WriteToPacket(S_MG_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_MG_HELLO(sendBuf,*pThis));
	}
	void call_sq_MG_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_MG_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_MG_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2MG_ONLINE_WritePacket(S_SS2MG_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2MG_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2MG_ONLINE_WriteToPacket(S_SS2MG_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2MG_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2MG_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2MG_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2MG_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_MG_ECHO_WritePacket(S_MG_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_MG_ECHO(sendBuf,*pThis));
	}
	static void _S_MG_ECHO_WriteToPacket(S_MG_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_MG_ECHO(sendBuf,*pThis));
	}
	void call_sq_MG_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_MG_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_MG_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_MG_ECHO , get_msg)(S_MG_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_MG_SERVERINFO_ACK_WritePacket(S_MG_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_MG_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_MG_SERVERINFO_ACK_WriteToPacket(S_MG_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_MG_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_MG_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_MG_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_MG_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2MG_SERVERINFO_ACK_WritePacket(S_SS2MG_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2MG_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2MG_SERVERINFO_ACK_WriteToPacket(S_SS2MG_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2MG_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2MG_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2MG_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2MG_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_MG_ERROR_WritePacket(S_MG_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_MG_ERROR(sendBuf,*pThis));
	}
	static void _S_MG_ERROR_WriteToPacket(S_MG_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_MG_ERROR(sendBuf,*pThis));
	}
	void call_sq_MG_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_MG_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_MG_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //MsgServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__MsgServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(MG_HELLO,jS(MG_HELLO),jS(Job_MsgServer));
		phtl.Insert(SS2MG_ONLINE,jS(SS2MG_ONLINE),0);
		phtl.Insert(MG_ECHO,jS(MG_ECHO),0);
		phtl.Insert(MG_SERVERINFO_ACK,jS(MG_SERVERINFO_ACK),0);
		phtl.Insert(SS2MG_SERVERINFO_ACK,jS(SS2MG_SERVERINFO_ACK),0);
		phtl.Insert(MG_ERROR,jS(MG_ERROR),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("MsgServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_MG_HELLO == MG_HELLO);
		jRAISE_PACKET(pk_SS2MG_ONLINE == SS2MG_ONLINE);
		jRAISE_PACKET(pk_MG_ECHO == MG_ECHO);
		jRAISE_PACKET(pk_MG_SERVERINFO_ACK == MG_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2MG_SERVERINFO_ACK == SS2MG_SERVERINFO_ACK);
		jRAISE_PACKET(pk_MG_ERROR == MG_ERROR);

		#ifndef MsgServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_MG_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_MG_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_MG_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2MG_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2MG_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2MG_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_MG_ECHO)
			jSQ_gfn(S_MG_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_MG_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_MG_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_MG_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_MG_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_MG_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2MG_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2MG_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2MG_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_MG_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_MG_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_MG_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //MsgServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__MsgServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("MsgServer"));
	}


}/* nMsgServer */ }/*nNET*/ } //nMech


#ifndef MsgServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_MsgServer(MsgServer);
jxDEFINE_MsgServer(MG_HELLO);
jxDEFINE_MsgServer(SS2MG_ONLINE);
jxDEFINE_MsgServer(MG_ECHO);
jxDEFINE_MsgServer(MG_SERVERINFO_ACK);
jxDEFINE_MsgServer(SS2MG_SERVERINFO_ACK);
jxDEFINE_MsgServer(MG_ERROR);
#endif // MsgServer_jNOT_USE_PACKET_PLUGIN_HELP