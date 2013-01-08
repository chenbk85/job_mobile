
//from(d:\svn\lib\lib_mech\src\server\testserver\sequence\testserver\..\..\protocal\pt_testserver.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_TestServer_Enum.h"


#include "network/my_pt_aq_server.h"

#ifndef TestServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nTestServer;
DECLARE_INSTANCE_TYPE(S_S_HELLO);
DECLARE_INSTANCE_TYPE(S_X2S_LOGIN);
DECLARE_INSTANCE_TYPE(S_S2X_LOGIN_OK);
DECLARE_INSTANCE_TYPE(S_S_ECHO);
DECLARE_INSTANCE_TYPE(S_S2X_ECHO);
DECLARE_INSTANCE_TYPE(S_X2S_THREAD_TEST1);
DECLARE_INSTANCE_TYPE(S_X2S_THREAD_TEST2);
DECLARE_INSTANCE_TYPE(S_X2S_TEST_PACKET);
#endif // TestServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nTestServer
{
	PT_TestServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef TestServer_jNOTUSE_SQ_CODE
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

	static void _S_X2S_LOGIN_WritePacket(S_X2S_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2S_LOGIN(sendBuf,*pThis));
	}
	static void _S_X2S_LOGIN_WriteToPacket(S_X2S_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2S_LOGIN(sendBuf,*pThis));
	}
	void call_sq_X2S_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2S_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2S_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2S_LOGIN , get_name)(S_X2S_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_name(buf));
	}

	static void _S_S2X_LOGIN_OK_WritePacket(S_S2X_LOGIN_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_S2X_LOGIN_OK(sendBuf,*pThis));
	}
	static void _S_S2X_LOGIN_OK_WriteToPacket(S_S2X_LOGIN_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_S2X_LOGIN_OK(sendBuf,*pThis));
	}
	void call_sq_S2X_LOGIN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_S2X_LOGIN_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_S2X_LOGIN_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_S2X_LOGIN_OK , get_server_name)(S_S2X_LOGIN_OK* pThis)
	{
		fname_t buf;return (pThis->get_server_name(buf));
	}

	static void _S_S_ECHO_WritePacket(S_S_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_S_ECHO(sendBuf,*pThis));
	}
	static void _S_S_ECHO_WriteToPacket(S_S_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_S_ECHO(sendBuf,*pThis));
	}
	void call_sq_S_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_S_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_S_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_S2X_ECHO_WritePacket(S_S2X_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_S2X_ECHO(sendBuf,*pThis));
	}
	static void _S_S2X_ECHO_WriteToPacket(S_S2X_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_S2X_ECHO(sendBuf,*pThis));
	}
	void call_sq_S2X_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_S2X_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_S2X_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2S_THREAD_TEST1_WritePacket(S_X2S_THREAD_TEST1* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2S_THREAD_TEST1(sendBuf,*pThis));
	}
	static void _S_X2S_THREAD_TEST1_WriteToPacket(S_X2S_THREAD_TEST1* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2S_THREAD_TEST1(sendBuf,*pThis));
	}
	void call_sq_X2S_THREAD_TEST1(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2S_THREAD_TEST1 param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2S_THREAD_TEST1"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2S_THREAD_TEST2_WritePacket(S_X2S_THREAD_TEST2* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2S_THREAD_TEST2(sendBuf,*pThis));
	}
	static void _S_X2S_THREAD_TEST2_WriteToPacket(S_X2S_THREAD_TEST2* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2S_THREAD_TEST2(sendBuf,*pThis));
	}
	void call_sq_X2S_THREAD_TEST2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2S_THREAD_TEST2 param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2S_THREAD_TEST2"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2S_TEST_PACKET_WritePacket(S_X2S_TEST_PACKET* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2S_TEST_PACKET(sendBuf,*pThis));
	}
	static void _S_X2S_TEST_PACKET_WriteToPacket(S_X2S_TEST_PACKET* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2S_TEST_PACKET(sendBuf,*pThis));
	}
	void call_sq_X2S_TEST_PACKET(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2S_TEST_PACKET param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2S_TEST_PACKET"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //TestServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__TestServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(S_HELLO,jS(S_HELLO),0);
		phtl.Insert(X2S_LOGIN,jS(X2S_LOGIN),0);
		phtl.Insert(S2X_LOGIN_OK,jS(S2X_LOGIN_OK),0);
		phtl.Insert(S_ECHO,jS(S_ECHO),0);
		phtl.Insert(S2X_ECHO,jS(S2X_ECHO),0);
		phtl.Insert(X2S_THREAD_TEST1,jS(X2S_THREAD_TEST1),jS(JOBTHREAD1));
		phtl.Insert(X2S_THREAD_TEST2,jS(X2S_THREAD_TEST2),jS(JOBTHREAD2));
		phtl.Insert(X2S_TEST_PACKET,jS(X2S_TEST_PACKET),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("TestServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_S_HELLO == S_HELLO);
		jRAISE_PACKET(pk_X2S_LOGIN == X2S_LOGIN);
		jRAISE_PACKET(pk_S2X_LOGIN_OK == S2X_LOGIN_OK);
		jRAISE_PACKET(pk_S_ECHO == S_ECHO);
		jRAISE_PACKET(pk_S2X_ECHO == S2X_ECHO);
		jRAISE_PACKET(pk_X2S_THREAD_TEST1 == X2S_THREAD_TEST1);
		jRAISE_PACKET(pk_X2S_THREAD_TEST2 == X2S_THREAD_TEST2);
		jRAISE_PACKET(pk_X2S_TEST_PACKET == X2S_TEST_PACKET);

		#ifndef TestServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_S_HELLO)
			jSQ_gfn(S_S_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2S_LOGIN)
			jSQ_gfn(S_X2S_LOGIN,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_gfn(S_X2S_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2S_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_S2X_LOGIN_OK)
			jSQ_gfn(S_S2X_LOGIN_OK,get_server_name, "","return net_string")
			jSQ_fn(set_server_name,"tcstr sz","")
			jSQ_gfn(S_S2X_LOGIN_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S2X_LOGIN_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_S_ECHO)
			jSQ_var(type,"uint8")
			jSQ_var(msg,"wstring")
			jSQ_gfn(S_S_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_S2X_ECHO)
			jSQ_var(type,"uint8")
			jSQ_var(msg,"wstring")
			jSQ_gfn(S_S2X_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S2X_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2S_THREAD_TEST1)
			jSQ_var(type,"uint8")
			jSQ_var(msg,"wstring")
			jSQ_gfn(S_X2S_THREAD_TEST1,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2S_THREAD_TEST1,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2S_THREAD_TEST2)
			jSQ_var(type,"uint8")
			jSQ_var(msg,"wstring")
			jSQ_gfn(S_X2S_THREAD_TEST2,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2S_THREAD_TEST2,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2S_TEST_PACKET)
			jSQ_var(val,"int32")
			jSQ_var(msg,"string")
			jSQ_gfn(S_X2S_TEST_PACKET,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2S_TEST_PACKET,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //TestServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__TestServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("TestServer"));
	}


}/* nTestServer */ }/*nNET*/ } //nMech


#ifndef TestServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_TestServer(TestServer);
jxDEFINE_TestServer(S_HELLO);
jxDEFINE_TestServer(X2S_LOGIN);
jxDEFINE_TestServer(S2X_LOGIN_OK);
jxDEFINE_TestServer(S_ECHO);
jxDEFINE_TestServer(S2X_ECHO);
jxDEFINE_TestServer(X2S_THREAD_TEST1);
jxDEFINE_TestServer(X2S_THREAD_TEST2);
jxDEFINE_TestServer(X2S_TEST_PACKET);
#endif // TestServer_jNOT_USE_PACKET_PLUGIN_HELP