
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_user.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_UserServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef UserServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nUserServer;
DECLARE_INSTANCE_TYPE(S_U4_USER_CONNECTION_NOTIFY);
DECLARE_INSTANCE_TYPE(S_U_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2U_ONLINE);
DECLARE_INSTANCE_TYPE(S_W2U_ONLINE_USERS);
DECLARE_INSTANCE_TYPE(S_L2U_ONLINE_USERS);
DECLARE_INSTANCE_TYPE(S_U_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2U_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_U2SS_ONLINE_OK);
DECLARE_INSTANCE_TYPE(S_U_ECHO);
DECLARE_INSTANCE_TYPE(S_U_ERROR);
DECLARE_INSTANCE_TYPE(S_L2U_USER_LOGIN);
DECLARE_INSTANCE_TYPE(S_U2L_USER_LOGIN_RESULT);
DECLARE_INSTANCE_TYPE(S_U2W_USER_LOGIN);
DECLARE_INSTANCE_TYPE(S_W2U_USER_LOGIN_RESULT);
DECLARE_INSTANCE_TYPE(S_U2W_USER_LOGIN_DUPLICATE);
DECLARE_INSTANCE_TYPE(S_W2U_USER_LOGIN_DUPLICATE_OK);
DECLARE_INSTANCE_TYPE(S_U2W_USER_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_U2L_DO_USER_DISCONNECT);
#endif // UserServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nUserServer
{
	PT_UserServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef UserServer_jNOTUSE_SQ_CODE
	static void _S_U4_USER_CONNECTION_NOTIFY_WritePacket(S_U4_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U4_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	static void _S_U4_USER_CONNECTION_NOTIFY_WriteToPacket(S_U4_USER_CONNECTION_NOTIFY* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U4_USER_CONNECTION_NOTIFY(sendBuf,*pThis));
	}
	void call_sq_U4_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U4_USER_CONNECTION_NOTIFY param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U4_USER_CONNECTION_NOTIFY"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_U_HELLO_WritePacket(S_U_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U_HELLO(sendBuf,*pThis));
	}
	static void _S_U_HELLO_WriteToPacket(S_U_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U_HELLO(sendBuf,*pThis));
	}
	void call_sq_U_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2U_ONLINE_WritePacket(S_SS2U_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2U_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2U_ONLINE_WriteToPacket(S_SS2U_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2U_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2U_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2U_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2U_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W2U_ONLINE_USERS_WritePacket(S_W2U_ONLINE_USERS* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2U_ONLINE_USERS(sendBuf,*pThis));
	}
	static void _S_W2U_ONLINE_USERS_WriteToPacket(S_W2U_ONLINE_USERS* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2U_ONLINE_USERS(sendBuf,*pThis));
	}
	void call_sq_W2U_ONLINE_USERS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2U_ONLINE_USERS param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2U_ONLINE_USERS"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2U_ONLINE_USERS_WritePacket(S_L2U_ONLINE_USERS* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2U_ONLINE_USERS(sendBuf,*pThis));
	}
	static void _S_L2U_ONLINE_USERS_WriteToPacket(S_L2U_ONLINE_USERS* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2U_ONLINE_USERS(sendBuf,*pThis));
	}
	void call_sq_L2U_ONLINE_USERS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2U_ONLINE_USERS param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2U_ONLINE_USERS"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_U_SERVERINFO_ACK_WritePacket(S_U_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_U_SERVERINFO_ACK_WriteToPacket(S_U_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_U_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2U_SERVERINFO_ACK_WritePacket(S_SS2U_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2U_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2U_SERVERINFO_ACK_WriteToPacket(S_SS2U_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2U_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2U_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2U_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2U_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_U2SS_ONLINE_OK_WritePacket(S_U2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2SS_ONLINE_OK(sendBuf,*pThis));
	}
	static void _S_U2SS_ONLINE_OK_WriteToPacket(S_U2SS_ONLINE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2SS_ONLINE_OK(sendBuf,*pThis));
	}
	void call_sq_U2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2SS_ONLINE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2SS_ONLINE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_U_ECHO_WritePacket(S_U_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U_ECHO(sendBuf,*pThis));
	}
	static void _S_U_ECHO_WriteToPacket(S_U_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U_ECHO(sendBuf,*pThis));
	}
	void call_sq_U_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_U_ECHO , get_msg)(S_U_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_U_ERROR_WritePacket(S_U_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U_ERROR(sendBuf,*pThis));
	}
	static void _S_U_ERROR_WriteToPacket(S_U_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U_ERROR(sendBuf,*pThis));
	}
	void call_sq_U_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_L2U_USER_LOGIN_WritePacket(S_L2U_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_L2U_USER_LOGIN(sendBuf,*pThis));
	}
	static void _S_L2U_USER_LOGIN_WriteToPacket(S_L2U_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_L2U_USER_LOGIN(sendBuf,*pThis));
	}
	void call_sq_L2U_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_L2U_USER_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_L2U_USER_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_L2U_USER_LOGIN , get_id)(S_L2U_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_U2L_USER_LOGIN_RESULT_WritePacket(S_U2L_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2L_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	static void _S_U2L_USER_LOGIN_RESULT_WriteToPacket(S_U2L_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2L_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	void call_sq_U2L_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2L_USER_LOGIN_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2L_USER_LOGIN_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_U2L_USER_LOGIN_RESULT , get_id)(S_U2L_USER_LOGIN_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_U2W_USER_LOGIN_WritePacket(S_U2W_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2W_USER_LOGIN(sendBuf,*pThis));
	}
	static void _S_U2W_USER_LOGIN_WriteToPacket(S_U2W_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2W_USER_LOGIN(sendBuf,*pThis));
	}
	void call_sq_U2W_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2W_USER_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2W_USER_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_U2W_USER_LOGIN , get_id)(S_U2W_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_W2U_USER_LOGIN_RESULT_WritePacket(S_W2U_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2U_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	static void _S_W2U_USER_LOGIN_RESULT_WriteToPacket(S_W2U_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2U_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	void call_sq_W2U_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2U_USER_LOGIN_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2U_USER_LOGIN_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2U_USER_LOGIN_RESULT , get_id)(S_W2U_USER_LOGIN_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_U2W_USER_LOGIN_DUPLICATE_WritePacket(S_U2W_USER_LOGIN_DUPLICATE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2W_USER_LOGIN_DUPLICATE(sendBuf,*pThis));
	}
	static void _S_U2W_USER_LOGIN_DUPLICATE_WriteToPacket(S_U2W_USER_LOGIN_DUPLICATE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2W_USER_LOGIN_DUPLICATE(sendBuf,*pThis));
	}
	void call_sq_U2W_USER_LOGIN_DUPLICATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2W_USER_LOGIN_DUPLICATE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2W_USER_LOGIN_DUPLICATE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_U2W_USER_LOGIN_DUPLICATE , get_id)(S_U2W_USER_LOGIN_DUPLICATE* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_W2U_USER_LOGIN_DUPLICATE_OK_WritePacket(S_W2U_USER_LOGIN_DUPLICATE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2U_USER_LOGIN_DUPLICATE_OK(sendBuf,*pThis));
	}
	static void _S_W2U_USER_LOGIN_DUPLICATE_OK_WriteToPacket(S_W2U_USER_LOGIN_DUPLICATE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2U_USER_LOGIN_DUPLICATE_OK(sendBuf,*pThis));
	}
	void call_sq_W2U_USER_LOGIN_DUPLICATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2U_USER_LOGIN_DUPLICATE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2U_USER_LOGIN_DUPLICATE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2U_USER_LOGIN_DUPLICATE_OK , get_id)(S_W2U_USER_LOGIN_DUPLICATE_OK* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_U2W_USER_DISCONNECT_WritePacket(S_U2W_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2W_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_U2W_USER_DISCONNECT_WriteToPacket(S_U2W_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2W_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_U2W_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2W_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2W_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_U2L_DO_USER_DISCONNECT_WritePacket(S_U2L_DO_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_U2L_DO_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_U2L_DO_USER_DISCONNECT_WriteToPacket(S_U2L_DO_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_U2L_DO_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_U2L_DO_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_U2L_DO_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_U2L_DO_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //UserServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__UserServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(U4_USER_CONNECTION_NOTIFY,jS(U4_USER_CONNECTION_NOTIFY),0);
		phtl.Insert(U_HELLO,jS(U_HELLO),jS(Job_UserServer));
		phtl.Insert(SS2U_ONLINE,jS(SS2U_ONLINE),0);
		phtl.Insert(W2U_ONLINE_USERS,jS(W2U_ONLINE_USERS),0);
		phtl.Insert(L2U_ONLINE_USERS,jS(L2U_ONLINE_USERS),0);
		phtl.Insert(U_SERVERINFO_ACK,jS(U_SERVERINFO_ACK),0);
		phtl.Insert(SS2U_SERVERINFO_ACK,jS(SS2U_SERVERINFO_ACK),0);
		phtl.Insert(U2SS_ONLINE_OK,jS(U2SS_ONLINE_OK),0);
		phtl.Insert(U_ECHO,jS(U_ECHO),0);
		phtl.Insert(U_ERROR,jS(U_ERROR),0);
		phtl.Insert(L2U_USER_LOGIN,jS(L2U_USER_LOGIN),0);
		phtl.Insert(U2L_USER_LOGIN_RESULT,jS(U2L_USER_LOGIN_RESULT),0);
		phtl.Insert(U2W_USER_LOGIN,jS(U2W_USER_LOGIN),0);
		phtl.Insert(W2U_USER_LOGIN_RESULT,jS(W2U_USER_LOGIN_RESULT),0);
		phtl.Insert(U2W_USER_LOGIN_DUPLICATE,jS(U2W_USER_LOGIN_DUPLICATE),0);
		phtl.Insert(W2U_USER_LOGIN_DUPLICATE_OK,jS(W2U_USER_LOGIN_DUPLICATE_OK),0);
		phtl.Insert(U2W_USER_DISCONNECT,jS(U2W_USER_DISCONNECT),0);
		phtl.Insert(U2L_DO_USER_DISCONNECT,jS(U2L_DO_USER_DISCONNECT),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("UserServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_U4_USER_CONNECTION_NOTIFY == U4_USER_CONNECTION_NOTIFY);
		jRAISE_PACKET(pk_U_HELLO == U_HELLO);
		jRAISE_PACKET(pk_SS2U_ONLINE == SS2U_ONLINE);
		jRAISE_PACKET(pk_W2U_ONLINE_USERS == W2U_ONLINE_USERS);
		jRAISE_PACKET(pk_L2U_ONLINE_USERS == L2U_ONLINE_USERS);
		jRAISE_PACKET(pk_U_SERVERINFO_ACK == U_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2U_SERVERINFO_ACK == SS2U_SERVERINFO_ACK);
		jRAISE_PACKET(pk_U2SS_ONLINE_OK == U2SS_ONLINE_OK);
		jRAISE_PACKET(pk_U_ECHO == U_ECHO);
		jRAISE_PACKET(pk_U_ERROR == U_ERROR);
		jRAISE_PACKET(pk_L2U_USER_LOGIN == L2U_USER_LOGIN);
		jRAISE_PACKET(pk_U2L_USER_LOGIN_RESULT == U2L_USER_LOGIN_RESULT);
		jRAISE_PACKET(pk_U2W_USER_LOGIN == U2W_USER_LOGIN);
		jRAISE_PACKET(pk_W2U_USER_LOGIN_RESULT == W2U_USER_LOGIN_RESULT);
		jRAISE_PACKET(pk_U2W_USER_LOGIN_DUPLICATE == U2W_USER_LOGIN_DUPLICATE);
		jRAISE_PACKET(pk_W2U_USER_LOGIN_DUPLICATE_OK == W2U_USER_LOGIN_DUPLICATE_OK);
		jRAISE_PACKET(pk_U2W_USER_DISCONNECT == U2W_USER_DISCONNECT);
		jRAISE_PACKET(pk_U2L_DO_USER_DISCONNECT == U2L_DO_USER_DISCONNECT);

		#ifndef UserServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_U4_USER_CONNECTION_NOTIFY)
			jSQ_fn(get_id_connect,"int i","return wstring*")
			jSQ_fn(set_id_connect,"int i,wstring* data","")
			jSQ_fn(insert_id_connect,"wstring* data","")
			jSQ_fn(clear_id_connect,"","")
			jSQ_fn(size_id_connect,"","return size_t")
			jSQ_fn(get_id_disconnect,"int i","return wstring*")
			jSQ_fn(set_id_disconnect,"int i,wstring* data","")
			jSQ_fn(insert_id_disconnect,"wstring* data","")
			jSQ_fn(clear_id_disconnect,"","")
			jSQ_fn(size_id_disconnect,"","return size_t")
			jSQ_gfn(S_U4_USER_CONNECTION_NOTIFY,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U4_USER_CONNECTION_NOTIFY,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_U_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2U_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2U_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2U_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2U_ONLINE_USERS)
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_fn(get_town,"int i","return serverid_t*")
			jSQ_fn(set_town,"int i,serverid_t* data","")
			jSQ_fn(insert_town,"serverid_t* data","")
			jSQ_fn(clear_town,"","")
			jSQ_fn(size_town,"","return size_t")
			jSQ_gfn(S_W2U_ONLINE_USERS,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2U_ONLINE_USERS,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2U_ONLINE_USERS)
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_gfn(S_L2U_ONLINE_USERS,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2U_ONLINE_USERS,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_U_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2U_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2U_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2U_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2SS_ONLINE_OK)
			jSQ_var(your_sid,"serverid_t")
			jSQ_gfn(S_U2SS_ONLINE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2SS_ONLINE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U_ECHO)
			jSQ_gfn(S_U_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_U_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_U_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_L2U_USER_LOGIN)
			jSQ_var(world,"serverid_t")
			jSQ_gfn(S_L2U_USER_LOGIN,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_L2U_USER_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_L2U_USER_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2L_USER_LOGIN_RESULT)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_U2L_USER_LOGIN_RESULT,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_var(e,"jError")
			jSQ_gfn(S_U2L_USER_LOGIN_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2L_USER_LOGIN_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2W_USER_LOGIN)
			jSQ_gfn(S_U2W_USER_LOGIN,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_U2W_USER_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2W_USER_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2U_USER_LOGIN_RESULT)
			jSQ_var(pid,"player_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_W2U_USER_LOGIN_RESULT,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_W2U_USER_LOGIN_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2U_USER_LOGIN_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2W_USER_LOGIN_DUPLICATE)
			jSQ_gfn(S_U2W_USER_LOGIN_DUPLICATE,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_U2W_USER_LOGIN_DUPLICATE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2W_USER_LOGIN_DUPLICATE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2U_USER_LOGIN_DUPLICATE_OK)
			jSQ_gfn(S_W2U_USER_LOGIN_DUPLICATE_OK,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_W2U_USER_LOGIN_DUPLICATE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2U_USER_LOGIN_DUPLICATE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2W_USER_DISCONNECT)
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_gfn(S_U2W_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2W_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_U2L_DO_USER_DISCONNECT)
			jSQ_fn(get_uids,"int i","return player_id_t*")
			jSQ_fn(set_uids,"int i,player_id_t* data","")
			jSQ_fn(insert_uids,"player_id_t* data","")
			jSQ_fn(clear_uids,"","")
			jSQ_fn(size_uids,"","return size_t")
			jSQ_gfn(S_U2L_DO_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_U2L_DO_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //UserServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__UserServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("UserServer"));
	}


}/* nUserServer */ }/*nNET*/ } //nMech


#ifndef UserServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_UserServer(UserServer);
jxDEFINE_UserServer(U4_USER_CONNECTION_NOTIFY);
jxDEFINE_UserServer(U_HELLO);
jxDEFINE_UserServer(SS2U_ONLINE);
jxDEFINE_UserServer(W2U_ONLINE_USERS);
jxDEFINE_UserServer(L2U_ONLINE_USERS);
jxDEFINE_UserServer(U_SERVERINFO_ACK);
jxDEFINE_UserServer(SS2U_SERVERINFO_ACK);
jxDEFINE_UserServer(U2SS_ONLINE_OK);
jxDEFINE_UserServer(U_ECHO);
jxDEFINE_UserServer(U_ERROR);
jxDEFINE_UserServer(L2U_USER_LOGIN);
jxDEFINE_UserServer(U2L_USER_LOGIN_RESULT);
jxDEFINE_UserServer(U2W_USER_LOGIN);
jxDEFINE_UserServer(W2U_USER_LOGIN_RESULT);
jxDEFINE_UserServer(U2W_USER_LOGIN_DUPLICATE);
jxDEFINE_UserServer(W2U_USER_LOGIN_DUPLICATE_OK);
jxDEFINE_UserServer(U2W_USER_DISCONNECT);
jxDEFINE_UserServer(U2L_DO_USER_DISCONNECT);
#endif // UserServer_jNOT_USE_PACKET_PLUGIN_HELP