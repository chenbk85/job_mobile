
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dummy.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_DummyServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef DummyServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nDummyServer;
DECLARE_INSTANCE_TYPE(S_DT_ECHO);
DECLARE_INSTANCE_TYPE(S_DT_ERROR);
DECLARE_INSTANCE_TYPE(S_DT_HELLO);
DECLARE_INSTANCE_TYPE(S_X2DT_HELLO);
DECLARE_INSTANCE_TYPE(S_DT_ONLINE);
DECLARE_INSTANCE_TYPE(S_DT_TEST_LOGIN_START);
DECLARE_INSTANCE_TYPE(S_DT_TEST_LOG_OUT);
DECLARE_INSTANCE_TYPE(S_DT_LOGIN_START_OK);
DECLARE_INSTANCE_TYPE(S_DT2_UPDATE_XPATH_VALUE);
DECLARE_INSTANCE_TYPE(S_DT4_UPDATE_XPATH_VALUE_OK);
DECLARE_INSTANCE_TYPE(S_DT_RUN_CONSOLE_CMD);
DECLARE_INSTANCE_TYPE(S_DT2X_SET_TEST_ENV);
DECLARE_INSTANCE_TYPE(S_DT_RUN_DUMMY_SCRIPT);
#endif // DummyServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nDummyServer
{
	PT_DummyServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef DummyServer_jNOTUSE_SQ_CODE
	static void _S_DT_ECHO_WritePacket(S_DT_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_ECHO(sendBuf,*pThis));
	}
	static void _S_DT_ECHO_WriteToPacket(S_DT_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_ECHO(sendBuf,*pThis));
	}
	void call_sq_DT_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DT_ERROR_WritePacket(S_DT_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_ERROR(sendBuf,*pThis));
	}
	static void _S_DT_ERROR_WriteToPacket(S_DT_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_ERROR(sendBuf,*pThis));
	}
	void call_sq_DT_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DT_HELLO_WritePacket(S_DT_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_HELLO(sendBuf,*pThis));
	}
	static void _S_DT_HELLO_WriteToPacket(S_DT_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_HELLO(sendBuf,*pThis));
	}
	void call_sq_DT_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2DT_HELLO_WritePacket(S_X2DT_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2DT_HELLO(sendBuf,*pThis));
	}
	static void _S_X2DT_HELLO_WriteToPacket(S_X2DT_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2DT_HELLO(sendBuf,*pThis));
	}
	void call_sq_X2DT_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2DT_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2DT_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DT_ONLINE_WritePacket(S_DT_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_ONLINE(sendBuf,*pThis));
	}
	static void _S_DT_ONLINE_WriteToPacket(S_DT_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_ONLINE(sendBuf,*pThis));
	}
	void call_sq_DT_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_ONLINE , get_test_id)(S_DT_ONLINE* pThis)
	{
		fname_t buf;return (pThis->get_test_id(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_ONLINE , get_szLoginIP)(S_DT_ONLINE* pThis)
	{
		fname_t buf;return (pThis->get_szLoginIP(buf));
	}

	static void _S_DT_TEST_LOGIN_START_WritePacket(S_DT_TEST_LOGIN_START* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_TEST_LOGIN_START(sendBuf,*pThis));
	}
	static void _S_DT_TEST_LOGIN_START_WriteToPacket(S_DT_TEST_LOGIN_START* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_TEST_LOGIN_START(sendBuf,*pThis));
	}
	void call_sq_DT_TEST_LOGIN_START(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_TEST_LOGIN_START param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_TEST_LOGIN_START"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_TEST_LOGIN_START , get_testClientName)(S_DT_TEST_LOGIN_START* pThis)
	{
		fname_t buf;return (pThis->get_testClientName(buf));
	}

	static void _S_DT_TEST_LOG_OUT_WritePacket(S_DT_TEST_LOG_OUT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_TEST_LOG_OUT(sendBuf,*pThis));
	}
	static void _S_DT_TEST_LOG_OUT_WriteToPacket(S_DT_TEST_LOG_OUT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_TEST_LOG_OUT(sendBuf,*pThis));
	}
	void call_sq_DT_TEST_LOG_OUT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_TEST_LOG_OUT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_TEST_LOG_OUT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_TEST_LOG_OUT , get_testClientName)(S_DT_TEST_LOG_OUT* pThis)
	{
		fname_t buf;return (pThis->get_testClientName(buf));
	}

	static void _S_DT_LOGIN_START_OK_WritePacket(S_DT_LOGIN_START_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_LOGIN_START_OK(sendBuf,*pThis));
	}
	static void _S_DT_LOGIN_START_OK_WriteToPacket(S_DT_LOGIN_START_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_LOGIN_START_OK(sendBuf,*pThis));
	}
	void call_sq_DT_LOGIN_START_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_LOGIN_START_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_LOGIN_START_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_LOGIN_START_OK , get_user_id)(S_DT_LOGIN_START_OK* pThis)
	{
		fname_t buf;return (pThis->get_user_id(buf));
	}

	static void _S_DT2_UPDATE_XPATH_VALUE_WritePacket(S_DT2_UPDATE_XPATH_VALUE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT2_UPDATE_XPATH_VALUE(sendBuf,*pThis));
	}
	static void _S_DT2_UPDATE_XPATH_VALUE_WriteToPacket(S_DT2_UPDATE_XPATH_VALUE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT2_UPDATE_XPATH_VALUE(sendBuf,*pThis));
	}
	void call_sq_DT2_UPDATE_XPATH_VALUE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT2_UPDATE_XPATH_VALUE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT2_UPDATE_XPATH_VALUE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DT4_UPDATE_XPATH_VALUE_OK_WritePacket(S_DT4_UPDATE_XPATH_VALUE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT4_UPDATE_XPATH_VALUE_OK(sendBuf,*pThis));
	}
	static void _S_DT4_UPDATE_XPATH_VALUE_OK_WriteToPacket(S_DT4_UPDATE_XPATH_VALUE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT4_UPDATE_XPATH_VALUE_OK(sendBuf,*pThis));
	}
	void call_sq_DT4_UPDATE_XPATH_VALUE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT4_UPDATE_XPATH_VALUE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT4_UPDATE_XPATH_VALUE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT4_UPDATE_XPATH_VALUE_OK , get_target_name)(S_DT4_UPDATE_XPATH_VALUE_OK* pThis)
	{
		fname_t buf;return (pThis->get_target_name(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT4_UPDATE_XPATH_VALUE_OK , get_doc)(S_DT4_UPDATE_XPATH_VALUE_OK* pThis)
	{
		fname_t buf;return (pThis->get_doc(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT4_UPDATE_XPATH_VALUE_OK , get_xpath)(S_DT4_UPDATE_XPATH_VALUE_OK* pThis)
	{
		fname_t buf;return (pThis->get_xpath(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT4_UPDATE_XPATH_VALUE_OK , get_value)(S_DT4_UPDATE_XPATH_VALUE_OK* pThis)
	{
		fname_t buf;return (pThis->get_value(buf));
	}

	static void _S_DT_RUN_CONSOLE_CMD_WritePacket(S_DT_RUN_CONSOLE_CMD* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_RUN_CONSOLE_CMD(sendBuf,*pThis));
	}
	static void _S_DT_RUN_CONSOLE_CMD_WriteToPacket(S_DT_RUN_CONSOLE_CMD* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_RUN_CONSOLE_CMD(sendBuf,*pThis));
	}
	void call_sq_DT_RUN_CONSOLE_CMD(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_RUN_CONSOLE_CMD param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_RUN_CONSOLE_CMD"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_RUN_CONSOLE_CMD , get_category)(S_DT_RUN_CONSOLE_CMD* pThis)
	{
		fname_t buf;return (pThis->get_category(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DT_RUN_CONSOLE_CMD , get_cmd)(S_DT_RUN_CONSOLE_CMD* pThis)
	{
		fname_t buf;return (pThis->get_cmd(buf));
	}

	static void _S_DT2X_SET_TEST_ENV_WritePacket(S_DT2X_SET_TEST_ENV* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT2X_SET_TEST_ENV(sendBuf,*pThis));
	}
	static void _S_DT2X_SET_TEST_ENV_WriteToPacket(S_DT2X_SET_TEST_ENV* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT2X_SET_TEST_ENV(sendBuf,*pThis));
	}
	void call_sq_DT2X_SET_TEST_ENV(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT2X_SET_TEST_ENV param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT2X_SET_TEST_ENV"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DT_RUN_DUMMY_SCRIPT_WritePacket(S_DT_RUN_DUMMY_SCRIPT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DT_RUN_DUMMY_SCRIPT(sendBuf,*pThis));
	}
	static void _S_DT_RUN_DUMMY_SCRIPT_WriteToPacket(S_DT_RUN_DUMMY_SCRIPT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DT_RUN_DUMMY_SCRIPT(sendBuf,*pThis));
	}
	void call_sq_DT_RUN_DUMMY_SCRIPT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DT_RUN_DUMMY_SCRIPT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DT_RUN_DUMMY_SCRIPT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //DummyServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__DummyServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(DT_ECHO,jS(DT_ECHO),0);
		phtl.Insert(DT_ERROR,jS(DT_ERROR),0);
		phtl.Insert(DT_HELLO,jS(DT_HELLO),0);
		phtl.Insert(X2DT_HELLO,jS(X2DT_HELLO),0);
		phtl.Insert(DT_ONLINE,jS(DT_ONLINE),0);
		phtl.Insert(DT_TEST_LOGIN_START,jS(DT_TEST_LOGIN_START),0);
		phtl.Insert(DT_TEST_LOG_OUT,jS(DT_TEST_LOG_OUT),0);
		phtl.Insert(DT_LOGIN_START_OK,jS(DT_LOGIN_START_OK),0);
		phtl.Insert(DT2_UPDATE_XPATH_VALUE,jS(DT2_UPDATE_XPATH_VALUE),0);
		phtl.Insert(DT4_UPDATE_XPATH_VALUE_OK,jS(DT4_UPDATE_XPATH_VALUE_OK),0);
		phtl.Insert(DT_RUN_CONSOLE_CMD,jS(DT_RUN_CONSOLE_CMD),0);
		phtl.Insert(DT2X_SET_TEST_ENV,jS(DT2X_SET_TEST_ENV),0);
		phtl.Insert(DT_RUN_DUMMY_SCRIPT,jS(DT_RUN_DUMMY_SCRIPT),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("DummyServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_DT_ECHO == DT_ECHO);
		jRAISE_PACKET(pk_DT_ERROR == DT_ERROR);
		jRAISE_PACKET(pk_DT_HELLO == DT_HELLO);
		jRAISE_PACKET(pk_X2DT_HELLO == X2DT_HELLO);
		jRAISE_PACKET(pk_DT_ONLINE == DT_ONLINE);
		jRAISE_PACKET(pk_DT_TEST_LOGIN_START == DT_TEST_LOGIN_START);
		jRAISE_PACKET(pk_DT_TEST_LOG_OUT == DT_TEST_LOG_OUT);
		jRAISE_PACKET(pk_DT_LOGIN_START_OK == DT_LOGIN_START_OK);
		jRAISE_PACKET(pk_DT2_UPDATE_XPATH_VALUE == DT2_UPDATE_XPATH_VALUE);
		jRAISE_PACKET(pk_DT4_UPDATE_XPATH_VALUE_OK == DT4_UPDATE_XPATH_VALUE_OK);
		jRAISE_PACKET(pk_DT_RUN_CONSOLE_CMD == DT_RUN_CONSOLE_CMD);
		jRAISE_PACKET(pk_DT2X_SET_TEST_ENV == DT2X_SET_TEST_ENV);
		jRAISE_PACKET(pk_DT_RUN_DUMMY_SCRIPT == DT_RUN_DUMMY_SCRIPT);

		#ifndef DummyServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_DT_ECHO)
			jSQ_fn(get_msg,"","tcstr")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_gfn(S_DT_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_DT_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_DT_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2DT_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_X2DT_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2DT_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_ONLINE)
			jSQ_gfn(S_DT_ONLINE,get_test_id, "","return net_string")
			jSQ_fn(set_test_id,"tcstr sz","")
			jSQ_var(TEST_ID_START_NUM,"int")
			jSQ_var(iDummyCount,"uint16")
			jSQ_gfn(S_DT_ONLINE,get_szLoginIP, "","return net_string")
			jSQ_fn(set_szLoginIP,"tcstr sz","")
			jSQ_var(iLoginPort,"uint16")
			jSQ_gfn(S_DT_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_TEST_LOGIN_START)
			jSQ_var(per_user,"int16")
			jSQ_var(delay,"uint32")
			jSQ_gfn(S_DT_TEST_LOGIN_START,get_testClientName, "","return net_string")
			jSQ_fn(set_testClientName,"tcstr sz","")
			jSQ_gfn(S_DT_TEST_LOGIN_START,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_TEST_LOGIN_START,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_TEST_LOG_OUT)
			jSQ_var(per_user,"int16")
			jSQ_var(delay,"uint32")
			jSQ_gfn(S_DT_TEST_LOG_OUT,get_testClientName, "","return net_string")
			jSQ_fn(set_testClientName,"tcstr sz","")
			jSQ_gfn(S_DT_TEST_LOG_OUT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_TEST_LOG_OUT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_LOGIN_START_OK)
			jSQ_var(process_msec,"uint32")
			jSQ_gfn(S_DT_LOGIN_START_OK,get_user_id, "","return net_string")
			jSQ_fn(set_user_id,"tcstr sz","")
			jSQ_fn(get_lobby_ip,"","tcstr")
			jSQ_fn(set_lobby_ip,"tcstr sz","")
			jSQ_gfn(S_DT_LOGIN_START_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_LOGIN_START_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT2_UPDATE_XPATH_VALUE)
			jSQ_gfn(S_DT2_UPDATE_XPATH_VALUE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT2_UPDATE_XPATH_VALUE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT4_UPDATE_XPATH_VALUE_OK)
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,get_target_name, "","return net_string")
			jSQ_fn(set_target_name,"tcstr sz","")
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,get_doc, "","return net_string")
			jSQ_fn(set_doc,"tcstr sz","")
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,get_xpath, "","return net_string")
			jSQ_fn(set_xpath,"tcstr sz","")
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,get_value, "","return net_string")
			jSQ_fn(set_value,"tcstr sz","")
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT4_UPDATE_XPATH_VALUE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_RUN_CONSOLE_CMD)
			jSQ_var(dummy_id,"dummy_id_t")
			jSQ_gfn(S_DT_RUN_CONSOLE_CMD,get_category, "","return net_string")
			jSQ_fn(set_category,"tcstr sz","")
			jSQ_gfn(S_DT_RUN_CONSOLE_CMD,get_cmd, "","return net_string")
			jSQ_fn(set_cmd,"tcstr sz","")
			jSQ_fn(get_arg,"int i","return tstring*")
			jSQ_fn(set_arg,"int i,tstring* data","")
			jSQ_fn(insert_arg,"tstring* data","")
			jSQ_fn(clear_arg,"","")
			jSQ_fn(size_arg,"","return size_t")
			jSQ_gfn(S_DT_RUN_CONSOLE_CMD,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_RUN_CONSOLE_CMD,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT2X_SET_TEST_ENV)
			jSQ_gfn(S_DT2X_SET_TEST_ENV,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT2X_SET_TEST_ENV,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DT_RUN_DUMMY_SCRIPT)
			jSQ_fn(get_code,"","tcstr")
			jSQ_fn(set_code,"tcstr sz","")
			jSQ_gfn(S_DT_RUN_DUMMY_SCRIPT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DT_RUN_DUMMY_SCRIPT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //DummyServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__DummyServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("DummyServer"));
	}


}/* nDummyServer */ }/*nNET*/ } //nMech


#ifndef DummyServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_DummyServer(DummyServer);
jxDEFINE_DummyServer(DT_ECHO);
jxDEFINE_DummyServer(DT_ERROR);
jxDEFINE_DummyServer(DT_HELLO);
jxDEFINE_DummyServer(X2DT_HELLO);
jxDEFINE_DummyServer(DT_ONLINE);
jxDEFINE_DummyServer(DT_TEST_LOGIN_START);
jxDEFINE_DummyServer(DT_TEST_LOG_OUT);
jxDEFINE_DummyServer(DT_LOGIN_START_OK);
jxDEFINE_DummyServer(DT2_UPDATE_XPATH_VALUE);
jxDEFINE_DummyServer(DT4_UPDATE_XPATH_VALUE_OK);
jxDEFINE_DummyServer(DT_RUN_CONSOLE_CMD);
jxDEFINE_DummyServer(DT2X_SET_TEST_ENV);
jxDEFINE_DummyServer(DT_RUN_DUMMY_SCRIPT);
#endif // DummyServer_jNOT_USE_PACKET_PLUGIN_HELP