
//from(z:\src\tool\servermonitor\net\sequence\monitorprotocal\..\..\protocal\pt_monitorserver.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_MonitorServer_Enum.h"


#include "network/my_pt_aq_server.h"

#ifndef MonitorServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nMonitorServer;
DECLARE_INSTANCE_TYPE(S_M2A_SEND_FILE);
DECLARE_INSTANCE_TYPE(S_S_HELLO);
DECLARE_INSTANCE_TYPE(S_X2S_LOGIN);
DECLARE_INSTANCE_TYPE(S_S2X_LOGIN_OK);
DECLARE_INSTANCE_TYPE(S_S_ECHO);
DECLARE_INSTANCE_TYPE(S_X2S_THREAD_TEST1);
DECLARE_INSTANCE_TYPE(S_X2S_THREAD_TEST2);
DECLARE_INSTANCE_TYPE(S_M2A_CALL_CMD_RQ);
DECLARE_INSTANCE_TYPE(S_A2M_CALL_CMD_RS);
DECLARE_INSTANCE_TYPE(S_A2M_NOTIFY_SERVER_INFO);
DECLARE_INSTANCE_TYPE(S_A2M_SERVER_CONNECTED);
DECLARE_INSTANCE_TYPE(S_M2A_MYTHOLOGY_MENU_RQ);
DECLARE_INSTANCE_TYPE(S_A2M_MYTHOLOGY_MENU_RS);
DECLARE_INSTANCE_TYPE(S_A2M_PROCESS_STATUS_NOTIFY);
DECLARE_INSTANCE_TYPE(S_A2M_PROCESS_INFO_NOTIFY);
DECLARE_INSTANCE_TYPE(S_M2A_PROCESS_INFO_UPDATE);
DECLARE_INSTANCE_TYPE(S_A2M_SEND_ERROR_LOG);
DECLARE_INSTANCE_TYPE(S_M2A_RESET_ERROR_LOG_COUNT);
DECLARE_INSTANCE_TYPE(S_M2A_RUN_EXE);
#endif // MonitorServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nMonitorServer
{
	PT_MonitorServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef MonitorServer_jNOTUSE_SQ_CODE
	static void _S_M2A_SEND_FILE_WritePacket(S_M2A_SEND_FILE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_SEND_FILE(sendBuf,*pThis));
	}
	static void _S_M2A_SEND_FILE_WriteToPacket(S_M2A_SEND_FILE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_SEND_FILE(sendBuf,*pThis));
	}
	void call_sq_M2A_SEND_FILE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_SEND_FILE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_SEND_FILE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

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
	jSQ_gfn_DEF2(SquirrelObject, S_X2S_LOGIN , get_ip)(S_X2S_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_ip(buf));
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

	static void _S_M2A_CALL_CMD_RQ_WritePacket(S_M2A_CALL_CMD_RQ* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_CALL_CMD_RQ(sendBuf,*pThis));
	}
	static void _S_M2A_CALL_CMD_RQ_WriteToPacket(S_M2A_CALL_CMD_RQ* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_CALL_CMD_RQ(sendBuf,*pThis));
	}
	void call_sq_M2A_CALL_CMD_RQ(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_CALL_CMD_RQ param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_CALL_CMD_RQ"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_CALL_CMD_RS_WritePacket(S_A2M_CALL_CMD_RS* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_CALL_CMD_RS(sendBuf,*pThis));
	}
	static void _S_A2M_CALL_CMD_RS_WriteToPacket(S_A2M_CALL_CMD_RS* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_CALL_CMD_RS(sendBuf,*pThis));
	}
	void call_sq_A2M_CALL_CMD_RS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_CALL_CMD_RS param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_CALL_CMD_RS"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_NOTIFY_SERVER_INFO_WritePacket(S_A2M_NOTIFY_SERVER_INFO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_NOTIFY_SERVER_INFO(sendBuf,*pThis));
	}
	static void _S_A2M_NOTIFY_SERVER_INFO_WriteToPacket(S_A2M_NOTIFY_SERVER_INFO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_NOTIFY_SERVER_INFO(sendBuf,*pThis));
	}
	void call_sq_A2M_NOTIFY_SERVER_INFO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_NOTIFY_SERVER_INFO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_NOTIFY_SERVER_INFO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_SERVER_CONNECTED_WritePacket(S_A2M_SERVER_CONNECTED* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_SERVER_CONNECTED(sendBuf,*pThis));
	}
	static void _S_A2M_SERVER_CONNECTED_WriteToPacket(S_A2M_SERVER_CONNECTED* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_SERVER_CONNECTED(sendBuf,*pThis));
	}
	void call_sq_A2M_SERVER_CONNECTED(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_SERVER_CONNECTED param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_SERVER_CONNECTED"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_M2A_MYTHOLOGY_MENU_RQ_WritePacket(S_M2A_MYTHOLOGY_MENU_RQ* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_MYTHOLOGY_MENU_RQ(sendBuf,*pThis));
	}
	static void _S_M2A_MYTHOLOGY_MENU_RQ_WriteToPacket(S_M2A_MYTHOLOGY_MENU_RQ* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_MYTHOLOGY_MENU_RQ(sendBuf,*pThis));
	}
	void call_sq_M2A_MYTHOLOGY_MENU_RQ(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_MYTHOLOGY_MENU_RQ param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_MYTHOLOGY_MENU_RQ"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_MYTHOLOGY_MENU_RS_WritePacket(S_A2M_MYTHOLOGY_MENU_RS* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_MYTHOLOGY_MENU_RS(sendBuf,*pThis));
	}
	static void _S_A2M_MYTHOLOGY_MENU_RS_WriteToPacket(S_A2M_MYTHOLOGY_MENU_RS* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_MYTHOLOGY_MENU_RS(sendBuf,*pThis));
	}
	void call_sq_A2M_MYTHOLOGY_MENU_RS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_MYTHOLOGY_MENU_RS param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_MYTHOLOGY_MENU_RS"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_PROCESS_STATUS_NOTIFY_WritePacket(S_A2M_PROCESS_STATUS_NOTIFY* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_PROCESS_STATUS_NOTIFY(sendBuf,*pThis));
	}
	static void _S_A2M_PROCESS_STATUS_NOTIFY_WriteToPacket(S_A2M_PROCESS_STATUS_NOTIFY* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_PROCESS_STATUS_NOTIFY(sendBuf,*pThis));
	}
	void call_sq_A2M_PROCESS_STATUS_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_PROCESS_STATUS_NOTIFY param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_PROCESS_STATUS_NOTIFY"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_PROCESS_INFO_NOTIFY_WritePacket(S_A2M_PROCESS_INFO_NOTIFY* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_PROCESS_INFO_NOTIFY(sendBuf,*pThis));
	}
	static void _S_A2M_PROCESS_INFO_NOTIFY_WriteToPacket(S_A2M_PROCESS_INFO_NOTIFY* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_PROCESS_INFO_NOTIFY(sendBuf,*pThis));
	}
	void call_sq_A2M_PROCESS_INFO_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_PROCESS_INFO_NOTIFY param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_PROCESS_INFO_NOTIFY"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_A2M_PROCESS_INFO_NOTIFY , get_eServerType)(S_A2M_PROCESS_INFO_NOTIFY* pThis)
	{
		fname_t buf;return (pThis->get_eServerType(buf));
	}

	static void _S_M2A_PROCESS_INFO_UPDATE_WritePacket(S_M2A_PROCESS_INFO_UPDATE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_PROCESS_INFO_UPDATE(sendBuf,*pThis));
	}
	static void _S_M2A_PROCESS_INFO_UPDATE_WriteToPacket(S_M2A_PROCESS_INFO_UPDATE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_PROCESS_INFO_UPDATE(sendBuf,*pThis));
	}
	void call_sq_M2A_PROCESS_INFO_UPDATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_PROCESS_INFO_UPDATE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_PROCESS_INFO_UPDATE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_A2M_SEND_ERROR_LOG_WritePacket(S_A2M_SEND_ERROR_LOG* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_A2M_SEND_ERROR_LOG(sendBuf,*pThis));
	}
	static void _S_A2M_SEND_ERROR_LOG_WriteToPacket(S_A2M_SEND_ERROR_LOG* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_A2M_SEND_ERROR_LOG(sendBuf,*pThis));
	}
	void call_sq_A2M_SEND_ERROR_LOG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_A2M_SEND_ERROR_LOG param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_A2M_SEND_ERROR_LOG"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_A2M_SEND_ERROR_LOG , get_eServerType)(S_A2M_SEND_ERROR_LOG* pThis)
	{
		fname_t buf;return (pThis->get_eServerType(buf));
	}

	static void _S_M2A_RESET_ERROR_LOG_COUNT_WritePacket(S_M2A_RESET_ERROR_LOG_COUNT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_RESET_ERROR_LOG_COUNT(sendBuf,*pThis));
	}
	static void _S_M2A_RESET_ERROR_LOG_COUNT_WriteToPacket(S_M2A_RESET_ERROR_LOG_COUNT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_RESET_ERROR_LOG_COUNT(sendBuf,*pThis));
	}
	void call_sq_M2A_RESET_ERROR_LOG_COUNT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_RESET_ERROR_LOG_COUNT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_RESET_ERROR_LOG_COUNT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_M2A_RUN_EXE_WritePacket(S_M2A_RUN_EXE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_M2A_RUN_EXE(sendBuf,*pThis));
	}
	static void _S_M2A_RUN_EXE_WriteToPacket(S_M2A_RUN_EXE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_M2A_RUN_EXE(sendBuf,*pThis));
	}
	void call_sq_M2A_RUN_EXE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_M2A_RUN_EXE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_M2A_RUN_EXE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //MonitorServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__MonitorServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(M2A_SEND_FILE,jS(M2A_SEND_FILE),0);
		phtl.Insert(S_HELLO,jS(S_HELLO),0);
		phtl.Insert(X2S_LOGIN,jS(X2S_LOGIN),0);
		phtl.Insert(S2X_LOGIN_OK,jS(S2X_LOGIN_OK),0);
		phtl.Insert(S_ECHO,jS(S_ECHO),0);
		phtl.Insert(X2S_THREAD_TEST1,jS(X2S_THREAD_TEST1),jS(JOBTHREAD1));
		phtl.Insert(X2S_THREAD_TEST2,jS(X2S_THREAD_TEST2),jS(JOBTHREAD2));
		phtl.Insert(M2A_CALL_CMD_RQ,jS(M2A_CALL_CMD_RQ),0);
		phtl.Insert(A2M_CALL_CMD_RS,jS(A2M_CALL_CMD_RS),0);
		phtl.Insert(A2M_NOTIFY_SERVER_INFO,jS(A2M_NOTIFY_SERVER_INFO),0);
		phtl.Insert(A2M_SERVER_CONNECTED,jS(A2M_SERVER_CONNECTED),0);
		phtl.Insert(M2A_MYTHOLOGY_MENU_RQ,jS(M2A_MYTHOLOGY_MENU_RQ),0);
		phtl.Insert(A2M_MYTHOLOGY_MENU_RS,jS(A2M_MYTHOLOGY_MENU_RS),0);
		phtl.Insert(A2M_PROCESS_STATUS_NOTIFY,jS(A2M_PROCESS_STATUS_NOTIFY),0);
		phtl.Insert(A2M_PROCESS_INFO_NOTIFY,jS(A2M_PROCESS_INFO_NOTIFY),0);
		phtl.Insert(M2A_PROCESS_INFO_UPDATE,jS(M2A_PROCESS_INFO_UPDATE),0);
		phtl.Insert(A2M_SEND_ERROR_LOG,jS(A2M_SEND_ERROR_LOG),0);
		phtl.Insert(M2A_RESET_ERROR_LOG_COUNT,jS(M2A_RESET_ERROR_LOG_COUNT),0);
		phtl.Insert(M2A_RUN_EXE,jS(M2A_RUN_EXE),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("MonitorServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_M2A_SEND_FILE == M2A_SEND_FILE);
		jRAISE_PACKET(pk_S_HELLO == S_HELLO);
		jRAISE_PACKET(pk_X2S_LOGIN == X2S_LOGIN);
		jRAISE_PACKET(pk_S2X_LOGIN_OK == S2X_LOGIN_OK);
		jRAISE_PACKET(pk_S_ECHO == S_ECHO);
		jRAISE_PACKET(pk_X2S_THREAD_TEST1 == X2S_THREAD_TEST1);
		jRAISE_PACKET(pk_X2S_THREAD_TEST2 == X2S_THREAD_TEST2);
		jRAISE_PACKET(pk_M2A_CALL_CMD_RQ == M2A_CALL_CMD_RQ);
		jRAISE_PACKET(pk_A2M_CALL_CMD_RS == A2M_CALL_CMD_RS);
		jRAISE_PACKET(pk_A2M_NOTIFY_SERVER_INFO == A2M_NOTIFY_SERVER_INFO);
		jRAISE_PACKET(pk_A2M_SERVER_CONNECTED == A2M_SERVER_CONNECTED);
		jRAISE_PACKET(pk_M2A_MYTHOLOGY_MENU_RQ == M2A_MYTHOLOGY_MENU_RQ);
		jRAISE_PACKET(pk_A2M_MYTHOLOGY_MENU_RS == A2M_MYTHOLOGY_MENU_RS);
		jRAISE_PACKET(pk_A2M_PROCESS_STATUS_NOTIFY == A2M_PROCESS_STATUS_NOTIFY);
		jRAISE_PACKET(pk_A2M_PROCESS_INFO_NOTIFY == A2M_PROCESS_INFO_NOTIFY);
		jRAISE_PACKET(pk_M2A_PROCESS_INFO_UPDATE == M2A_PROCESS_INFO_UPDATE);
		jRAISE_PACKET(pk_A2M_SEND_ERROR_LOG == A2M_SEND_ERROR_LOG);
		jRAISE_PACKET(pk_M2A_RESET_ERROR_LOG_COUNT == M2A_RESET_ERROR_LOG_COUNT);
		jRAISE_PACKET(pk_M2A_RUN_EXE == M2A_RUN_EXE);

		#ifndef MonitorServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_M2A_SEND_FILE)
			jSQ_var(type,"int")
			jSQ_var(target_dir,"tstring")
			jSQ_gfn(S_M2A_SEND_FILE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_SEND_FILE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_S_HELLO)
			jSQ_gfn(S_S_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_S_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2S_LOGIN)
			jSQ_gfn(S_X2S_LOGIN,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_gfn(S_X2S_LOGIN,get_ip, "","return net_string")
			jSQ_fn(set_ip,"tcstr sz","")
			jSQ_fn(get_servers,"int i","return astring*")
			jSQ_fn(set_servers,"int i,astring* data","")
			jSQ_fn(insert_servers,"astring* data","")
			jSQ_fn(clear_servers,"","")
			jSQ_fn(size_servers,"","return size_t")
			jSQ_fn(get_states,"int i","return tstring*")
			jSQ_fn(set_states,"int i,tstring* data","")
			jSQ_fn(insert_states,"tstring* data","")
			jSQ_fn(clear_states,"","")
			jSQ_fn(size_states,"","return size_t")
			jSQ_gfn(S_X2S_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2S_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_S2X_LOGIN_OK)
			jSQ_var(did,"int32")
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

		jSQ_Class(S_M2A_CALL_CMD_RQ)
			jSQ_var(eServerType,"tstring")
			jSQ_var(cmd,"wstring")
			jSQ_gfn(S_M2A_CALL_CMD_RQ,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_CALL_CMD_RQ,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_CALL_CMD_RS)
			jSQ_var(eServerType,"tstring")
			jSQ_var(cmd,"wstring")
			jSQ_gfn(S_A2M_CALL_CMD_RS,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_CALL_CMD_RS,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_NOTIFY_SERVER_INFO)
			jSQ_var(eServerType,"tstring")
			jSQ_var(info,"wstring")
			jSQ_var(eState,"tstring")
			jSQ_gfn(S_A2M_NOTIFY_SERVER_INFO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_NOTIFY_SERVER_INFO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_SERVER_CONNECTED)
			jSQ_var(eServerType,"tstring")
			jSQ_var(eServerState,"tstring")
			jSQ_gfn(S_A2M_SERVER_CONNECTED,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_SERVER_CONNECTED,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M2A_MYTHOLOGY_MENU_RQ)
			jSQ_var(eServerType,"tstring")
			jSQ_var(cmd,"astring")
			jSQ_gfn(S_M2A_MYTHOLOGY_MENU_RQ,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_MYTHOLOGY_MENU_RQ,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_MYTHOLOGY_MENU_RS)
			jSQ_var(eServerType,"tstring")
			jSQ_var(cmd,"astring")
			jSQ_gfn(S_A2M_MYTHOLOGY_MENU_RS,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_MYTHOLOGY_MENU_RS,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_PROCESS_STATUS_NOTIFY)
			jSQ_var(eServerType,"astring")
			jSQ_var(eState,"astring")
			jSQ_gfn(S_A2M_PROCESS_STATUS_NOTIFY,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_PROCESS_STATUS_NOTIFY,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_PROCESS_INFO_NOTIFY)
			jSQ_gfn(S_A2M_PROCESS_INFO_NOTIFY,get_eServerType, "","return net_string")
			jSQ_fn(set_eServerType,"tcstr sz","")
			jSQ_var(name,"wstring")
			jSQ_var(value,"wstring")
			jSQ_gfn(S_A2M_PROCESS_INFO_NOTIFY,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_PROCESS_INFO_NOTIFY,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M2A_PROCESS_INFO_UPDATE)
			jSQ_var(eServerType,"tstring")
			jSQ_var(name,"wstring")
			jSQ_var(value,"wstring")
			jSQ_gfn(S_M2A_PROCESS_INFO_UPDATE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_PROCESS_INFO_UPDATE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_A2M_SEND_ERROR_LOG)
			jSQ_gfn(S_A2M_SEND_ERROR_LOG,get_eServerType, "","return net_string")
			jSQ_fn(set_eServerType,"tcstr sz","")
			jSQ_var(log,"wstring")
			jSQ_gfn(S_A2M_SEND_ERROR_LOG,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_A2M_SEND_ERROR_LOG,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M2A_RESET_ERROR_LOG_COUNT)
			jSQ_gfn(S_M2A_RESET_ERROR_LOG_COUNT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_RESET_ERROR_LOG_COUNT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_M2A_RUN_EXE)
			jSQ_var(type,"int")
			jSQ_var(option,"wstring")
			jSQ_var(cmd,"wstring")
			jSQ_gfn(S_M2A_RUN_EXE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_M2A_RUN_EXE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //MonitorServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__MonitorServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("MonitorServer"));
	}


}/* nMonitorServer */ }/*nNET*/ } //nMech


#ifndef MonitorServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_MonitorServer(MonitorServer);
jxDEFINE_MonitorServer(M2A_SEND_FILE);
jxDEFINE_MonitorServer(S_HELLO);
jxDEFINE_MonitorServer(X2S_LOGIN);
jxDEFINE_MonitorServer(S2X_LOGIN_OK);
jxDEFINE_MonitorServer(S_ECHO);
jxDEFINE_MonitorServer(X2S_THREAD_TEST1);
jxDEFINE_MonitorServer(X2S_THREAD_TEST2);
jxDEFINE_MonitorServer(M2A_CALL_CMD_RQ);
jxDEFINE_MonitorServer(A2M_CALL_CMD_RS);
jxDEFINE_MonitorServer(A2M_NOTIFY_SERVER_INFO);
jxDEFINE_MonitorServer(A2M_SERVER_CONNECTED);
jxDEFINE_MonitorServer(M2A_MYTHOLOGY_MENU_RQ);
jxDEFINE_MonitorServer(A2M_MYTHOLOGY_MENU_RS);
jxDEFINE_MonitorServer(A2M_PROCESS_STATUS_NOTIFY);
jxDEFINE_MonitorServer(A2M_PROCESS_INFO_NOTIFY);
jxDEFINE_MonitorServer(M2A_PROCESS_INFO_UPDATE);
jxDEFINE_MonitorServer(A2M_SEND_ERROR_LOG);
jxDEFINE_MonitorServer(M2A_RESET_ERROR_LOG_COUNT);
jxDEFINE_MonitorServer(M2A_RUN_EXE);
#endif // MonitorServer_jNOT_USE_PACKET_PLUGIN_HELP