
//from(d:\svn\common\server\tool\umlpad\baseballtestclient\code\pt_baseballserver.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_BaseballServer_Enum.h"


#include "network/my_pt_aq_server.h"

#ifndef BaseballServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nBaseballServer;
DECLARE_INSTANCE_TYPE(S_S_HELLO);
#endif // BaseballServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nBaseballServer
{
	PT_BaseballServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef BaseballServer_jNOTUSE_SQ_CODE
	static void _S_S_HELLO_WritePacket(S_S_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_S_HELLO(sendBuf,*pThis));
	}
	static void _S_S_HELLO_WriteToPacket(S_S_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_S_HELLO(sendBuf,*pThis));
	}
	void call_sq_S_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_S_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_S_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //BaseballServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__BaseballServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(S_HELLO,jS(S_HELLO),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("BaseballServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_S_HELLO == S_HELLO);

		#ifndef BaseballServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_S_HELLO)
			jSQ_var(type,"int")
			jSQ_var(msg,"astring")
			jSQ_gfn(S_S_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //BaseballServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__BaseballServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("BaseballServer"));
	}


}/* nBaseballServer */ }/*nNET*/ } //nMech


#ifndef BaseballServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_BaseballServer(BaseballServer);
jxDEFINE_BaseballServer(S_HELLO);
#endif // BaseballServer_jNOT_USE_PACKET_PLUGIN_HELP