
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_login.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_LoginServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef LoginServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nLoginServer;
DECLARE_INSTANCE_TYPE(S_L_ERROR);
DECLARE_INSTANCE_TYPE(S_L_ECHO);
DECLARE_INSTANCE_TYPE(S_L_HELLO);
DECLARE_INSTANCE_TYPE(S_L2X_NOTICE);
DECLARE_INSTANCE_TYPE(S_X2L_LOGIN);
DECLARE_INSTANCE_TYPE(S_L2X_USER_LOGIN_OK);
DECLARE_INSTANCE_TYPE(S_X2L_GET_CHANNEL_LIST);
DECLARE_INSTANCE_TYPE(S_L2X_CHANNEL_LIST);
DECLARE_INSTANCE_TYPE(S_X2L_GET_WORLD_LIST);
DECLARE_INSTANCE_TYPE(S_L2X_WORLD_LIST);
DECLARE_INSTANCE_TYPE(S_X2L_USER_LOGIN);
DECLARE_INSTANCE_TYPE(S_X2L_USER_EXIT);
DECLARE_INSTANCE_TYPE(S_L2X_USER_EXIT);
DECLARE_INSTANCE_TYPE(S_X2L_CHANNEL_SELECT);
DECLARE_INSTANCE_TYPE(S_L2X_CHANNEL_SELECT_RESULT);
#endif // LoginServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nLoginServer
{
	PT_LoginServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef LoginServer_jNOTUSE_SQ_CODE
	static void _S_L_ERROR_WritePacket(S_L_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L_ERROR(sendBuf,*pThis));
	}
	static void _S_L_ERROR_WriteToPacket(S_L_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L_ERROR(sendBuf,*pThis));
	}
	void call_sq_L_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L_ECHO_WritePacket(S_L_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L_ECHO(sendBuf,*pThis));
	}
	static void _S_L_ECHO_WriteToPacket(S_L_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L_ECHO(sendBuf,*pThis));
	}
	void call_sq_L_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_L_ECHO , get_msg)(S_L_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_L_HELLO_WritePacket(S_L_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L_HELLO(sendBuf,*pThis));
	}
	static void _S_L_HELLO_WriteToPacket(S_L_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L_HELLO(sendBuf,*pThis));
	}
	void call_sq_L_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2X_NOTICE_WritePacket(S_L2X_NOTICE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_NOTICE(sendBuf,*pThis));
	}
	static void _S_L2X_NOTICE_WriteToPacket(S_L2X_NOTICE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_NOTICE(sendBuf,*pThis));
	}
	void call_sq_L2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_NOTICE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_NOTICE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_L2X_NOTICE , get_msg)(S_L2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_L2X_NOTICE , get_date)(S_L2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_date(buf));
	}

	static void _S_X2L_LOGIN_WritePacket(S_X2L_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_LOGIN(sendBuf,*pThis));
	}
	static void _S_X2L_LOGIN_WriteToPacket(S_X2L_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_LOGIN(sendBuf,*pThis));
	}
	void call_sq_X2L_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2X_USER_LOGIN_OK_WritePacket(S_L2X_USER_LOGIN_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_USER_LOGIN_OK(sendBuf,*pThis));
	}
	static void _S_L2X_USER_LOGIN_OK_WriteToPacket(S_L2X_USER_LOGIN_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_USER_LOGIN_OK(sendBuf,*pThis));
	}
	void call_sq_L2X_USER_LOGIN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_USER_LOGIN_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_USER_LOGIN_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2L_GET_CHANNEL_LIST_WritePacket(S_X2L_GET_CHANNEL_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_GET_CHANNEL_LIST(sendBuf,*pThis));
	}
	static void _S_X2L_GET_CHANNEL_LIST_WriteToPacket(S_X2L_GET_CHANNEL_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_GET_CHANNEL_LIST(sendBuf,*pThis));
	}
	void call_sq_X2L_GET_CHANNEL_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_GET_CHANNEL_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_GET_CHANNEL_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2L_GET_CHANNEL_LIST , get_world)(S_X2L_GET_CHANNEL_LIST* pThis)
	{
		fname_t buf;return (pThis->get_world(buf));
	}

	static void _S_L2X_CHANNEL_LIST_WritePacket(S_L2X_CHANNEL_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_CHANNEL_LIST(sendBuf,*pThis));
	}
	static void _S_L2X_CHANNEL_LIST_WriteToPacket(S_L2X_CHANNEL_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_CHANNEL_LIST(sendBuf,*pThis));
	}
	void call_sq_L2X_CHANNEL_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_CHANNEL_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_CHANNEL_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2L_GET_WORLD_LIST_WritePacket(S_X2L_GET_WORLD_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_GET_WORLD_LIST(sendBuf,*pThis));
	}
	static void _S_X2L_GET_WORLD_LIST_WriteToPacket(S_X2L_GET_WORLD_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_GET_WORLD_LIST(sendBuf,*pThis));
	}
	void call_sq_X2L_GET_WORLD_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_GET_WORLD_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_GET_WORLD_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2X_WORLD_LIST_WritePacket(S_L2X_WORLD_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_WORLD_LIST(sendBuf,*pThis));
	}
	static void _S_L2X_WORLD_LIST_WriteToPacket(S_L2X_WORLD_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_WORLD_LIST(sendBuf,*pThis));
	}
	void call_sq_L2X_WORLD_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_WORLD_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_WORLD_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2L_USER_LOGIN_WritePacket(S_X2L_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_USER_LOGIN(sendBuf,*pThis));
	}
	static void _S_X2L_USER_LOGIN_WriteToPacket(S_X2L_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_USER_LOGIN(sendBuf,*pThis));
	}
	void call_sq_X2L_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_USER_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_USER_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2L_USER_LOGIN , get_world)(S_X2L_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_world(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2L_USER_LOGIN , get_id)(S_X2L_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2L_USER_LOGIN , get_ver)(S_X2L_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_ver(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2L_USER_LOGIN , get_cpp_ver)(S_X2L_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_cpp_ver(buf));
	}

	static void _S_X2L_USER_EXIT_WritePacket(S_X2L_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_X2L_USER_EXIT_WriteToPacket(S_X2L_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_X2L_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2X_USER_EXIT_WritePacket(S_L2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_L2X_USER_EXIT_WriteToPacket(S_L2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_L2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2L_CHANNEL_SELECT_WritePacket(S_X2L_CHANNEL_SELECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_CHANNEL_SELECT(sendBuf,*pThis));
	}
	static void _S_X2L_CHANNEL_SELECT_WriteToPacket(S_X2L_CHANNEL_SELECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_CHANNEL_SELECT(sendBuf,*pThis));
	}
	void call_sq_X2L_CHANNEL_SELECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_CHANNEL_SELECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_CHANNEL_SELECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2X_CHANNEL_SELECT_RESULT_WritePacket(S_L2X_CHANNEL_SELECT_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2X_CHANNEL_SELECT_RESULT(sendBuf,*pThis));
	}
	static void _S_L2X_CHANNEL_SELECT_RESULT_WriteToPacket(S_L2X_CHANNEL_SELECT_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2X_CHANNEL_SELECT_RESULT(sendBuf,*pThis));
	}
	void call_sq_L2X_CHANNEL_SELECT_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2X_CHANNEL_SELECT_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2X_CHANNEL_SELECT_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_L2X_CHANNEL_SELECT_RESULT , get_ip)(S_L2X_CHANNEL_SELECT_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_ip(buf));
	}

	#endif //LoginServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__LoginServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(L_ERROR,jS(L_ERROR),0);
		phtl.Insert(L_ECHO,jS(L_ECHO),0);
		phtl.Insert(L_HELLO,jS(L_HELLO),0);
		phtl.Insert(L2X_NOTICE,jS(L2X_NOTICE),0);
		phtl.Insert(X2L_LOGIN,jS(X2L_LOGIN),0);
		phtl.Insert(L2X_USER_LOGIN_OK,jS(L2X_USER_LOGIN_OK),0);
		phtl.Insert(X2L_GET_CHANNEL_LIST,jS(X2L_GET_CHANNEL_LIST),0);
		phtl.Insert(L2X_CHANNEL_LIST,jS(L2X_CHANNEL_LIST),0);
		phtl.Insert(X2L_GET_WORLD_LIST,jS(X2L_GET_WORLD_LIST),0);
		phtl.Insert(L2X_WORLD_LIST,jS(L2X_WORLD_LIST),0);
		phtl.Insert(X2L_USER_LOGIN,jS(X2L_USER_LOGIN),0);
		phtl.Insert(X2L_USER_EXIT,jS(X2L_USER_EXIT),0);
		phtl.Insert(L2X_USER_EXIT,jS(L2X_USER_EXIT),0);
		phtl.Insert(X2L_CHANNEL_SELECT,jS(X2L_CHANNEL_SELECT),0);
		phtl.Insert(L2X_CHANNEL_SELECT_RESULT,jS(L2X_CHANNEL_SELECT_RESULT),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("LoginServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_L_ERROR == L_ERROR);
		jRAISE_PACKET(pk_L_ECHO == L_ECHO);
		jRAISE_PACKET(pk_L_HELLO == L_HELLO);
		jRAISE_PACKET(pk_L2X_NOTICE == L2X_NOTICE);
		jRAISE_PACKET(pk_X2L_LOGIN == X2L_LOGIN);
		jRAISE_PACKET(pk_L2X_USER_LOGIN_OK == L2X_USER_LOGIN_OK);
		jRAISE_PACKET(pk_X2L_GET_CHANNEL_LIST == X2L_GET_CHANNEL_LIST);
		jRAISE_PACKET(pk_L2X_CHANNEL_LIST == L2X_CHANNEL_LIST);
		jRAISE_PACKET(pk_X2L_GET_WORLD_LIST == X2L_GET_WORLD_LIST);
		jRAISE_PACKET(pk_L2X_WORLD_LIST == L2X_WORLD_LIST);
		jRAISE_PACKET(pk_X2L_USER_LOGIN == X2L_USER_LOGIN);
		jRAISE_PACKET(pk_X2L_USER_EXIT == X2L_USER_EXIT);
		jRAISE_PACKET(pk_L2X_USER_EXIT == L2X_USER_EXIT);
		jRAISE_PACKET(pk_X2L_CHANNEL_SELECT == X2L_CHANNEL_SELECT);
		jRAISE_PACKET(pk_L2X_CHANNEL_SELECT_RESULT == L2X_CHANNEL_SELECT_RESULT);

		#ifndef LoginServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_L_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_L_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L_ECHO)
			jSQ_gfn(S_L_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_L_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_L_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_NOTICE)
			jSQ_var(info,"jNoticeInfo")
			jSQ_gfn(S_L2X_NOTICE,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_L2X_NOTICE,get_date, "","return net_string")
			jSQ_fn(set_date,"tcstr sz","")
			jSQ_gfn(S_L2X_NOTICE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_NOTICE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_LOGIN)
			jSQ_gfn(S_X2L_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_USER_LOGIN_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_fn(get_channel,"int i","return serverid_t*")
			jSQ_fn(set_channel,"int i,serverid_t* data","")
			jSQ_fn(insert_channel,"serverid_t* data","")
			jSQ_fn(clear_channel,"","")
			jSQ_fn(size_channel,"","return size_t")
			jSQ_fn(get_channel_name,"int i","return astring*")
			jSQ_fn(set_channel_name,"int i,astring* data","")
			jSQ_fn(insert_channel_name,"astring* data","")
			jSQ_fn(clear_channel_name,"","")
			jSQ_fn(size_channel_name,"","return size_t")
			jSQ_fn(get_buzy_level,"int i","return uint8*")
			jSQ_fn(set_buzy_level,"int i,uint8* data","")
			jSQ_fn(insert_buzy_level,"uint8* data","")
			jSQ_fn(clear_buzy_level,"","")
			jSQ_fn(size_buzy_level,"","return size_t")
			jSQ_gfn(S_L2X_USER_LOGIN_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_USER_LOGIN_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_GET_CHANNEL_LIST)
			jSQ_gfn(S_X2L_GET_CHANNEL_LIST,get_world, "","return net_string")
			jSQ_fn(set_world,"tcstr sz","")
			jSQ_gfn(S_X2L_GET_CHANNEL_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_GET_CHANNEL_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_CHANNEL_LIST)
			jSQ_fn(get_channel,"int i","return serverid_t*")
			jSQ_fn(set_channel,"int i,serverid_t* data","")
			jSQ_fn(insert_channel,"serverid_t* data","")
			jSQ_fn(clear_channel,"","")
			jSQ_fn(size_channel,"","return size_t")
			jSQ_fn(get_channel_name,"int i","return astring*")
			jSQ_fn(set_channel_name,"int i,astring* data","")
			jSQ_fn(insert_channel_name,"astring* data","")
			jSQ_fn(clear_channel_name,"","")
			jSQ_fn(size_channel_name,"","return size_t")
			jSQ_fn(get_buzy_level,"int i","return uint8*")
			jSQ_fn(set_buzy_level,"int i,uint8* data","")
			jSQ_fn(insert_buzy_level,"uint8* data","")
			jSQ_fn(clear_buzy_level,"","")
			jSQ_fn(size_buzy_level,"","return size_t")
			jSQ_gfn(S_L2X_CHANNEL_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_CHANNEL_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_GET_WORLD_LIST)
			jSQ_gfn(S_X2L_GET_WORLD_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_GET_WORLD_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_WORLD_LIST)
			jSQ_fn(get_worlds,"int i","return jWorldServerInfo*")
			jSQ_fn(set_worlds,"int i,jWorldServerInfo* data","")
			jSQ_fn(insert_worlds,"jWorldServerInfo* data","")
			jSQ_fn(clear_worlds,"","")
			jSQ_fn(size_worlds,"","return size_t")
			jSQ_gfn(S_L2X_WORLD_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_WORLD_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_USER_LOGIN)
			jSQ_gfn(S_X2L_USER_LOGIN,get_world, "","return net_string")
			jSQ_fn(set_world,"tcstr sz","")
			jSQ_gfn(S_X2L_USER_LOGIN,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_fn(get_pwd,"int i","return uint8*")
			jSQ_fn(set_pwd,"int i,uint8* data","")
			jSQ_fn(insert_pwd,"uint8* data","")
			jSQ_fn(clear_pwd,"","")
			jSQ_fn(size_pwd,"","return size_t")
			jSQ_gfn(S_X2L_USER_LOGIN,get_ver, "","return net_string")
			jSQ_fn(set_ver,"tcstr sz","")
			jSQ_gfn(S_X2L_USER_LOGIN,get_cpp_ver, "","return net_string")
			jSQ_fn(set_cpp_ver,"tcstr sz","")
			jSQ_gfn(S_X2L_USER_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_USER_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_USER_EXIT)
			jSQ_gfn(S_X2L_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_USER_EXIT)
			jSQ_gfn(S_L2X_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_CHANNEL_SELECT)
			jSQ_var(sid,"serverid_t")
			jSQ_gfn(S_X2L_CHANNEL_SELECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_CHANNEL_SELECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2X_CHANNEL_SELECT_RESULT)
			jSQ_var(e,"jError")
			jSQ_gfn(S_L2X_CHANNEL_SELECT_RESULT,get_ip, "","return net_string")
			jSQ_fn(set_ip,"tcstr sz","")
			jSQ_var(port,"uint16")
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_L2X_CHANNEL_SELECT_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2X_CHANNEL_SELECT_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //LoginServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__LoginServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("LoginServer"));
	}


}/* nLoginServer */ }/*nNET*/ } //nMech


#ifndef LoginServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_LoginServer(LoginServer);
jxDEFINE_LoginServer(L_ERROR);
jxDEFINE_LoginServer(L_ECHO);
jxDEFINE_LoginServer(L_HELLO);
jxDEFINE_LoginServer(L2X_NOTICE);
jxDEFINE_LoginServer(X2L_LOGIN);
jxDEFINE_LoginServer(L2X_USER_LOGIN_OK);
jxDEFINE_LoginServer(X2L_GET_CHANNEL_LIST);
jxDEFINE_LoginServer(L2X_CHANNEL_LIST);
jxDEFINE_LoginServer(X2L_GET_WORLD_LIST);
jxDEFINE_LoginServer(L2X_WORLD_LIST);
jxDEFINE_LoginServer(X2L_USER_LOGIN);
jxDEFINE_LoginServer(X2L_USER_EXIT);
jxDEFINE_LoginServer(L2X_USER_EXIT);
jxDEFINE_LoginServer(X2L_CHANNEL_SELECT);
jxDEFINE_LoginServer(L2X_CHANNEL_SELECT_RESULT);
#endif // LoginServer_jNOT_USE_PACKET_PLUGIN_HELP