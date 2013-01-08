
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_central.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_CentralServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef CentralServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nCentralServer;
DECLARE_INSTANCE_TYPE(S_C_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2C_ONLINE);
DECLARE_INSTANCE_TYPE(S_C_SERVER_ONLINE);
DECLARE_INSTANCE_TYPE(S_C2SS_ONLINE_OK);
DECLARE_INSTANCE_TYPE(S_C_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2C_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_C_SERVER_OFFLINE);
DECLARE_INSTANCE_TYPE(S_C_ECHO);
DECLARE_INSTANCE_TYPE(S_C2_LOG_FILE_DAY_CHANGE);
DECLARE_INSTANCE_TYPE(S_C_ERROR);
DECLARE_INSTANCE_TYPE(S_CD2C_WELCOME);
DECLARE_INSTANCE_TYPE(S_C4_USER_CONNECTION_NOTIFY);
DECLARE_INSTANCE_TYPE(S_C2_USER_CONNECTION_NOTIFY);
DECLARE_INSTANCE_TYPE(S_C2_NOTICE);
DECLARE_INSTANCE_TYPE(S_C2_SERVER_LOG_LEVEL);
DECLARE_INSTANCE_TYPE(S_C2L_DO_USER_DISSCONNECT);
#endif // CentralServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nCentralServer
{
	PT_CentralServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef CentralServer_jNOTUSE_SQ_CODE
	static void _S_C_HELLO_WritePacket(S_C_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_HELLO(sendBuf,*pThis));
	}
	static void _S_C_HELLO_WriteToPacket(S_C_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_HELLO(sendBuf,*pThis));
	}
	void call_sq_C_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2C_ONLINE_WritePacket(S_SS2C_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2C_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2C_ONLINE_WriteToPacket(S_SS2C_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2C_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2C_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2C_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2C_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C_SERVER_ONLINE_WritePacket(S_C_SERVER_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_SERVER_ONLINE(sendBuf,*pThis));
	}
	static void _S_C_SERVER_ONLINE_WriteToPacket(S_C_SERVER_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_SERVER_ONLINE(sendBuf,*pThis));
	}
	void call_sq_C_SERVER_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_SERVER_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_SERVER_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C2SS_ONLINE_OK_WritePacket(S_C2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2SS_ONLINE_OK(sendBuf,*pThis));
	}
	static void _S_C2SS_ONLINE_OK_WriteToPacket(S_C2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2SS_ONLINE_OK(sendBuf,*pThis));
	}
	void call_sq_C2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2SS_ONLINE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2SS_ONLINE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C_SERVERINFO_ACK_WritePacket(S_C_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_C_SERVERINFO_ACK_WriteToPacket(S_C_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_C_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2C_SERVERINFO_ACK_WritePacket(S_SS2C_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2C_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2C_SERVERINFO_ACK_WriteToPacket(S_SS2C_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2C_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2C_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2C_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2C_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C_SERVER_OFFLINE_WritePacket(S_C_SERVER_OFFLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_SERVER_OFFLINE(sendBuf,*pThis));
	}
	static void _S_C_SERVER_OFFLINE_WriteToPacket(S_C_SERVER_OFFLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_SERVER_OFFLINE(sendBuf,*pThis));
	}
	void call_sq_C_SERVER_OFFLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_SERVER_OFFLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_SERVER_OFFLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C_ECHO_WritePacket(S_C_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_ECHO(sendBuf,*pThis));
	}
	static void _S_C_ECHO_WriteToPacket(S_C_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_ECHO(sendBuf,*pThis));
	}
	void call_sq_C_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_C_ECHO , get_msg)(S_C_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_C2_LOG_FILE_DAY_CHANGE_WritePacket(S_C2_LOG_FILE_DAY_CHANGE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2_LOG_FILE_DAY_CHANGE(sendBuf,*pThis));
	}
	static void _S_C2_LOG_FILE_DAY_CHANGE_WriteToPacket(S_C2_LOG_FILE_DAY_CHANGE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2_LOG_FILE_DAY_CHANGE(sendBuf,*pThis));
	}
	void call_sq_C2_LOG_FILE_DAY_CHANGE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2_LOG_FILE_DAY_CHANGE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2_LOG_FILE_DAY_CHANGE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C_ERROR_WritePacket(S_C_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C_ERROR(sendBuf,*pThis));
	}
	static void _S_C_ERROR_WriteToPacket(S_C_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C_ERROR(sendBuf,*pThis));
	}
	void call_sq_C_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CD2C_WELCOME_WritePacket(S_CD2C_WELCOME* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CD2C_WELCOME(sendBuf,*pThis));
	}
	static void _S_CD2C_WELCOME_WriteToPacket(S_CD2C_WELCOME* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CD2C_WELCOME(sendBuf,*pThis));
	}
	void call_sq_CD2C_WELCOME(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CD2C_WELCOME param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CD2C_WELCOME"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C4_USER_CONNECTION_NOTIFY_WritePacket(S_C4_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C4_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	static void _S_C4_USER_CONNECTION_NOTIFY_WriteToPacket(S_C4_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C4_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	void call_sq_C4_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C4_USER_CONNECTION_NOTIFY param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C4_USER_CONNECTION_NOTIFY"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C2_USER_CONNECTION_NOTIFY_WritePacket(S_C2_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	static void _S_C2_USER_CONNECTION_NOTIFY_WriteToPacket(S_C2_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	void call_sq_C2_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2_USER_CONNECTION_NOTIFY param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2_USER_CONNECTION_NOTIFY"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_C2_NOTICE_WritePacket(S_C2_NOTICE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2_NOTICE(sendBuf,*pThis));
	}
	static void _S_C2_NOTICE_WriteToPacket(S_C2_NOTICE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2_NOTICE(sendBuf,*pThis));
	}
	void call_sq_C2_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2_NOTICE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2_NOTICE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_C2_NOTICE , get_msg)(S_C2_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_C2_NOTICE , get_date)(S_C2_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_date(buf));
	}

	static void _S_C2_SERVER_LOG_LEVEL_WritePacket(S_C2_SERVER_LOG_LEVEL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2_SERVER_LOG_LEVEL(sendBuf,*pThis));
	}
	static void _S_C2_SERVER_LOG_LEVEL_WriteToPacket(S_C2_SERVER_LOG_LEVEL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2_SERVER_LOG_LEVEL(sendBuf,*pThis));
	}
	void call_sq_C2_SERVER_LOG_LEVEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2_SERVER_LOG_LEVEL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2_SERVER_LOG_LEVEL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_C2_SERVER_LOG_LEVEL , get_type)(S_C2_SERVER_LOG_LEVEL* pThis)
	{
		fname_t buf;return (pThis->get_type(buf));
	}

	static void _S_C2L_DO_USER_DISSCONNECT_WritePacket(S_C2L_DO_USER_DISSCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_C2L_DO_USER_DISSCONNECT(sendBuf,*pThis));
	}
	static void _S_C2L_DO_USER_DISSCONNECT_WriteToPacket(S_C2L_DO_USER_DISSCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_C2L_DO_USER_DISSCONNECT(sendBuf,*pThis));
	}
	void call_sq_C2L_DO_USER_DISSCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_C2L_DO_USER_DISSCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_C2L_DO_USER_DISSCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //CentralServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__CentralServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(C_HELLO,jS(C_HELLO),0);
		phtl.Insert(SS2C_ONLINE,jS(SS2C_ONLINE),0);
		phtl.Insert(C_SERVER_ONLINE,jS(C_SERVER_ONLINE),0);
		phtl.Insert(C2SS_ONLINE_OK,jS(C2SS_ONLINE_OK),0);
		phtl.Insert(C_SERVERINFO_ACK,jS(C_SERVERINFO_ACK),0);
		phtl.Insert(SS2C_SERVERINFO_ACK,jS(SS2C_SERVERINFO_ACK),0);
		phtl.Insert(C_SERVER_OFFLINE,jS(C_SERVER_OFFLINE),0);
		phtl.Insert(C_ECHO,jS(C_ECHO),0);
		phtl.Insert(C2_LOG_FILE_DAY_CHANGE,jS(C2_LOG_FILE_DAY_CHANGE),0);
		phtl.Insert(C_ERROR,jS(C_ERROR),0);
		phtl.Insert(CD2C_WELCOME,jS(CD2C_WELCOME),0);
		phtl.Insert(C4_USER_CONNECTION_NOTIFY,jS(C4_USER_CONNECTION_NOTIFY),0);
		phtl.Insert(C2_USER_CONNECTION_NOTIFY,jS(C2_USER_CONNECTION_NOTIFY),0);
		phtl.Insert(C2_NOTICE,jS(C2_NOTICE),0);
		phtl.Insert(C2_SERVER_LOG_LEVEL,jS(C2_SERVER_LOG_LEVEL),0);
		phtl.Insert(C2L_DO_USER_DISSCONNECT,jS(C2L_DO_USER_DISSCONNECT),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("CentralServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_C_HELLO == C_HELLO);
		jRAISE_PACKET(pk_SS2C_ONLINE == SS2C_ONLINE);
		jRAISE_PACKET(pk_C_SERVER_ONLINE == C_SERVER_ONLINE);
		jRAISE_PACKET(pk_C2SS_ONLINE_OK == C2SS_ONLINE_OK);
		jRAISE_PACKET(pk_C_SERVERINFO_ACK == C_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2C_SERVERINFO_ACK == SS2C_SERVERINFO_ACK);
		jRAISE_PACKET(pk_C_SERVER_OFFLINE == C_SERVER_OFFLINE);
		jRAISE_PACKET(pk_C_ECHO == C_ECHO);
		jRAISE_PACKET(pk_C2_LOG_FILE_DAY_CHANGE == C2_LOG_FILE_DAY_CHANGE);
		jRAISE_PACKET(pk_C_ERROR == C_ERROR);
		jRAISE_PACKET(pk_CD2C_WELCOME == CD2C_WELCOME);
		jRAISE_PACKET(pk_C4_USER_CONNECTION_NOTIFY == C4_USER_CONNECTION_NOTIFY);
		jRAISE_PACKET(pk_C2_USER_CONNECTION_NOTIFY == C2_USER_CONNECTION_NOTIFY);
		jRAISE_PACKET(pk_C2_NOTICE == C2_NOTICE);
		jRAISE_PACKET(pk_C2_SERVER_LOG_LEVEL == C2_SERVER_LOG_LEVEL);
		jRAISE_PACKET(pk_C2L_DO_USER_DISSCONNECT == C2L_DO_USER_DISSCONNECT);

		#ifndef CentralServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_C_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_C_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2C_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2C_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2C_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C_SERVER_ONLINE)
			jSQ_var(s,"jServerInfo")
			jSQ_gfn(S_C_SERVER_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_SERVER_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2SS_ONLINE_OK)
			jSQ_var(you,"jServerInfo")
			jSQ_fn(get_s,"int i","return jServerInfo*")
			jSQ_fn(set_s,"int i,jServerInfo* data","")
			jSQ_fn(insert_s,"jServerInfo* data","")
			jSQ_fn(clear_s,"","")
			jSQ_fn(size_s,"","return size_t")
			jSQ_gfn(S_C2SS_ONLINE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2SS_ONLINE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_C_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2C_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2C_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2C_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C_SERVER_OFFLINE)
			jSQ_var(sid,"serverid_t")
			jSQ_gfn(S_C_SERVER_OFFLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_SERVER_OFFLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C_ECHO)
			jSQ_gfn(S_C_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_C_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2_LOG_FILE_DAY_CHANGE)
			jSQ_gfn(S_C2_LOG_FILE_DAY_CHANGE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2_LOG_FILE_DAY_CHANGE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_C_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CD2C_WELCOME)
			jSQ_var(my,"jServerInfo")
			jSQ_fn(get_s,"int i","return jServerInfo*")
			jSQ_fn(set_s,"int i,jServerInfo* data","")
			jSQ_fn(insert_s,"jServerInfo* data","")
			jSQ_fn(clear_s,"","")
			jSQ_fn(size_s,"","return size_t")
			jSQ_gfn(S_CD2C_WELCOME,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CD2C_WELCOME,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C4_USER_CONNECTION_NOTIFY)
			jSQ_var(userCnt,"uint16")
			jSQ_gfn(S_C4_USER_CONNECTION_NOTIFY,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C4_USER_CONNECTION_NOTIFY,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2_USER_CONNECTION_NOTIFY)
			jSQ_fn(get_sid,"int i","return serverid_t*")
			jSQ_fn(set_sid,"int i,serverid_t* data","")
			jSQ_fn(insert_sid,"serverid_t* data","")
			jSQ_fn(clear_sid,"","")
			jSQ_fn(size_sid,"","return size_t")
			jSQ_fn(get_userCnt,"int i","return uint16*")
			jSQ_fn(set_userCnt,"int i,uint16* data","")
			jSQ_fn(insert_userCnt,"uint16* data","")
			jSQ_fn(clear_userCnt,"","")
			jSQ_fn(size_userCnt,"","return size_t")
			jSQ_gfn(S_C2_USER_CONNECTION_NOTIFY,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2_USER_CONNECTION_NOTIFY,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2_NOTICE)
			jSQ_var(info,"jNoticeInfo")
			jSQ_gfn(S_C2_NOTICE,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_C2_NOTICE,get_date, "","return net_string")
			jSQ_fn(set_date,"tcstr sz","")
			jSQ_gfn(S_C2_NOTICE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2_NOTICE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2_SERVER_LOG_LEVEL)
			jSQ_gfn(S_C2_SERVER_LOG_LEVEL,get_type, "","return net_string")
			jSQ_fn(set_type,"tcstr sz","")
			jSQ_var(enable,"bool")
			jSQ_gfn(S_C2_SERVER_LOG_LEVEL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2_SERVER_LOG_LEVEL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_C2L_DO_USER_DISSCONNECT)
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_gfn(S_C2L_DO_USER_DISSCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_C2L_DO_USER_DISSCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //CentralServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__CentralServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("CentralServer"));
	}


}/* nCentralServer */ }/*nNET*/ } //nMech


#ifndef CentralServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_CentralServer(CentralServer);
jxDEFINE_CentralServer(C_HELLO);
jxDEFINE_CentralServer(SS2C_ONLINE);
jxDEFINE_CentralServer(C_SERVER_ONLINE);
jxDEFINE_CentralServer(C2SS_ONLINE_OK);
jxDEFINE_CentralServer(C_SERVERINFO_ACK);
jxDEFINE_CentralServer(SS2C_SERVERINFO_ACK);
jxDEFINE_CentralServer(C_SERVER_OFFLINE);
jxDEFINE_CentralServer(C_ECHO);
jxDEFINE_CentralServer(C2_LOG_FILE_DAY_CHANGE);
jxDEFINE_CentralServer(C_ERROR);
jxDEFINE_CentralServer(CD2C_WELCOME);
jxDEFINE_CentralServer(C4_USER_CONNECTION_NOTIFY);
jxDEFINE_CentralServer(C2_USER_CONNECTION_NOTIFY);
jxDEFINE_CentralServer(C2_NOTICE);
jxDEFINE_CentralServer(C2_SERVER_LOG_LEVEL);
jxDEFINE_CentralServer(C2L_DO_USER_DISSCONNECT);
#endif // CentralServer_jNOT_USE_PACKET_PLUGIN_HELP