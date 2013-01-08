
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_mail.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_MailServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef MailServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nMailServer;
DECLARE_INSTANCE_TYPE(S_M_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2M_ONLINE);
DECLARE_INSTANCE_TYPE(S_M_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2M_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_M_ECHO);
DECLARE_INSTANCE_TYPE(S_M_ERROR);
#endif // MailServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nMailServer
{
	PT_MailServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef MailServer_jNOTUSE_SQ_CODE
	static void _S_M_HELLO_WritePacket(S_M_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M_HELLO(sendBuf,*pThis));
	}
	static void _S_M_HELLO_WriteToPacket(S_M_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M_HELLO(sendBuf,*pThis));
	}
	void call_sq_M_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2M_ONLINE_WritePacket(S_SS2M_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2M_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2M_ONLINE_WriteToPacket(S_SS2M_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2M_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2M_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2M_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2M_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_M_SERVERINFO_ACK_WritePacket(S_M_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_M_SERVERINFO_ACK_WriteToPacket(S_M_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_M_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2M_SERVERINFO_ACK_WritePacket(S_SS2M_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2M_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2M_SERVERINFO_ACK_WriteToPacket(S_SS2M_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2M_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2M_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2M_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2M_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_M_ECHO_WritePacket(S_M_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M_ECHO(sendBuf,*pThis));
	}
	static void _S_M_ECHO_WriteToPacket(S_M_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M_ECHO(sendBuf,*pThis));
	}
	void call_sq_M_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_M_ECHO , get_msg)(S_M_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_M_ERROR_WritePacket(S_M_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M_ERROR(sendBuf,*pThis));
	}
	static void _S_M_ERROR_WriteToPacket(S_M_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M_ERROR(sendBuf,*pThis));
	}
	void call_sq_M_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //MailServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__MailServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(M_HELLO,jS(M_HELLO),jS(Job_MailServer));
		phtl.Insert(SS2M_ONLINE,jS(SS2M_ONLINE),0);
		phtl.Insert(M_SERVERINFO_ACK,jS(M_SERVERINFO_ACK),0);
		phtl.Insert(SS2M_SERVERINFO_ACK,jS(SS2M_SERVERINFO_ACK),0);
		phtl.Insert(M_ECHO,jS(M_ECHO),0);
		phtl.Insert(M_ERROR,jS(M_ERROR),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("MailServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_M_HELLO == M_HELLO);
		jRAISE_PACKET(pk_SS2M_ONLINE == SS2M_ONLINE);
		jRAISE_PACKET(pk_M_SERVERINFO_ACK == M_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2M_SERVERINFO_ACK == SS2M_SERVERINFO_ACK);
		jRAISE_PACKET(pk_M_ECHO == M_ECHO);
		jRAISE_PACKET(pk_M_ERROR == M_ERROR);

		#ifndef MailServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_M_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_M_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2M_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2M_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2M_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_M_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2M_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2M_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2M_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M_ECHO)
			jSQ_gfn(S_M_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_M_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_M_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //MailServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__MailServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("MailServer"));
	}


}/* nMailServer */ }/*nNET*/ } //nMech


#ifndef MailServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_MailServer(MailServer);
jxDEFINE_MailServer(M_HELLO);
jxDEFINE_MailServer(SS2M_ONLINE);
jxDEFINE_MailServer(M_SERVERINFO_ACK);
jxDEFINE_MailServer(SS2M_SERVERINFO_ACK);
jxDEFINE_MailServer(M_ECHO);
jxDEFINE_MailServer(M_ERROR);
#endif // MailServer_jNOT_USE_PACKET_PLUGIN_HELP