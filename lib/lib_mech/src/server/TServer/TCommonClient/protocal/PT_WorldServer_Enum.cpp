
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_world.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_WorldServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef WorldServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nWorldServer;
DECLARE_INSTANCE_TYPE(S_CH2W_NEW_TOWN);
DECLARE_INSTANCE_TYPE(S_W_ERROR);
DECLARE_INSTANCE_TYPE(S_W2DC_NEW_TOWN);
DECLARE_INSTANCE_TYPE(S_DC2W_NEW_TOWN_ERROR);
DECLARE_INSTANCE_TYPE(S_DC2W_TOWN_DELETE_OK);
DECLARE_INSTANCE_TYPE(S_W4_USER_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_W2DC_USER_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_W2_USER_LOGIN_DUPLICATE);
DECLARE_INSTANCE_TYPE(S_W_HELLO);
DECLARE_INSTANCE_TYPE(S_SS2W_ONLINE);
DECLARE_INSTANCE_TYPE(S_W_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_SS2W_SERVERINFO_ACK);
DECLARE_INSTANCE_TYPE(S_W_ECHO);
DECLARE_INSTANCE_TYPE(S_W2DC_USER_LOGIN);
DECLARE_INSTANCE_TYPE(S_DC2W_USER_LOGIN_RESULT);
DECLARE_INSTANCE_TYPE(S_W2DC_USER_LOGIN_CHANNEL);
DECLARE_INSTANCE_TYPE(S_DC2W_USER_LOGIN_CHANNEL_FAIL);
DECLARE_INSTANCE_TYPE(S_DC2W_USER_LOGIN_DUPLICATE_OK);
DECLARE_INSTANCE_TYPE(S_W2_USER_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_CH2W_USER_LOGIN_CHANNEL);
#endif // WorldServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nWorldServer
{
	PT_WorldServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef WorldServer_jNOTUSE_SQ_CODE
	static void _S_CH2W_NEW_TOWN_WritePacket(S_CH2W_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2W_NEW_TOWN(sendBuf,*pThis));
	}
	static void _S_CH2W_NEW_TOWN_WriteToPacket(S_CH2W_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2W_NEW_TOWN(sendBuf,*pThis));
	}
	void call_sq_CH2W_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2W_NEW_TOWN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2W_NEW_TOWN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CH2W_NEW_TOWN , get_town_name)(S_CH2W_NEW_TOWN* pThis)
	{
		fname_t buf;return (pThis->get_town_name(buf));
	}

	static void _S_W_ERROR_WritePacket(S_W_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W_ERROR(sendBuf,*pThis));
	}
	static void _S_W_ERROR_WriteToPacket(S_W_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W_ERROR(sendBuf,*pThis));
	}
	void call_sq_W_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W2DC_NEW_TOWN_WritePacket(S_W2DC_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2DC_NEW_TOWN(sendBuf,*pThis));
	}
	static void _S_W2DC_NEW_TOWN_WriteToPacket(S_W2DC_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2DC_NEW_TOWN(sendBuf,*pThis));
	}
	void call_sq_W2DC_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2DC_NEW_TOWN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2DC_NEW_TOWN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2DC_NEW_TOWN , get_name)(S_W2DC_NEW_TOWN* pThis)
	{
		fname_t buf;return (pThis->get_name(buf));
	}

	static void _S_DC2W_NEW_TOWN_ERROR_WritePacket(S_DC2W_NEW_TOWN_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2W_NEW_TOWN_ERROR(sendBuf,*pThis));
	}
	static void _S_DC2W_NEW_TOWN_ERROR_WriteToPacket(S_DC2W_NEW_TOWN_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2W_NEW_TOWN_ERROR(sendBuf,*pThis));
	}
	void call_sq_DC2W_NEW_TOWN_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2W_NEW_TOWN_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2W_NEW_TOWN_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2W_TOWN_DELETE_OK_WritePacket(S_DC2W_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2W_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	static void _S_DC2W_TOWN_DELETE_OK_WriteToPacket(S_DC2W_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2W_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	void call_sq_DC2W_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2W_TOWN_DELETE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2W_TOWN_DELETE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2W_TOWN_DELETE_OK , get_user)(S_DC2W_TOWN_DELETE_OK* pThis)
	{
		fname_t buf;return (pThis->get_user(buf));
	}

	static void _S_W4_USER_DISCONNECT_WritePacket(S_W4_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W4_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_W4_USER_DISCONNECT_WriteToPacket(S_W4_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W4_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_W4_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W4_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W4_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W2DC_USER_DISCONNECT_WritePacket(S_W2DC_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2DC_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_W2DC_USER_DISCONNECT_WriteToPacket(S_W2DC_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2DC_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_W2DC_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2DC_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2DC_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W2_USER_LOGIN_DUPLICATE_WritePacket(S_W2_USER_LOGIN_DUPLICATE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2_USER_LOGIN_DUPLICATE(sendBuf,*pThis));
	}
	static void _S_W2_USER_LOGIN_DUPLICATE_WriteToPacket(S_W2_USER_LOGIN_DUPLICATE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2_USER_LOGIN_DUPLICATE(sendBuf,*pThis));
	}
	void call_sq_W2_USER_LOGIN_DUPLICATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2_USER_LOGIN_DUPLICATE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2_USER_LOGIN_DUPLICATE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2_USER_LOGIN_DUPLICATE , get_id)(S_W2_USER_LOGIN_DUPLICATE* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_W_HELLO_WritePacket(S_W_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W_HELLO(sendBuf,*pThis));
	}
	static void _S_W_HELLO_WriteToPacket(S_W_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W_HELLO(sendBuf,*pThis));
	}
	void call_sq_W_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2W_ONLINE_WritePacket(S_SS2W_ONLINE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2W_ONLINE(sendBuf,*pThis));
	}
	static void _S_SS2W_ONLINE_WriteToPacket(S_SS2W_ONLINE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2W_ONLINE(sendBuf,*pThis));
	}
	void call_sq_SS2W_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2W_ONLINE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2W_ONLINE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W_SERVERINFO_ACK_WritePacket(S_W_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_W_SERVERINFO_ACK_WriteToPacket(S_W_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_W_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_SS2W_SERVERINFO_ACK_WritePacket(S_SS2W_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_SS2W_SERVERINFO_ACK(sendBuf,*pThis));
	}
	static void _S_SS2W_SERVERINFO_ACK_WriteToPacket(S_SS2W_SERVERINFO_ACK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_SS2W_SERVERINFO_ACK(sendBuf,*pThis));
	}
	void call_sq_SS2W_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_SS2W_SERVERINFO_ACK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_SS2W_SERVERINFO_ACK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_W_ECHO_WritePacket(S_W_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W_ECHO(sendBuf,*pThis));
	}
	static void _S_W_ECHO_WriteToPacket(S_W_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W_ECHO(sendBuf,*pThis));
	}
	void call_sq_W_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W_ECHO , get_msg)(S_W_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_W2DC_USER_LOGIN_WritePacket(S_W2DC_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2DC_USER_LOGIN(sendBuf,*pThis));
	}
	static void _S_W2DC_USER_LOGIN_WriteToPacket(S_W2DC_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2DC_USER_LOGIN(sendBuf,*pThis));
	}
	void call_sq_W2DC_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2DC_USER_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2DC_USER_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2DC_USER_LOGIN , get_id)(S_W2DC_USER_LOGIN* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_DC2W_USER_LOGIN_RESULT_WritePacket(S_DC2W_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2W_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	static void _S_DC2W_USER_LOGIN_RESULT_WriteToPacket(S_DC2W_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2W_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	void call_sq_DC2W_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2W_USER_LOGIN_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2W_USER_LOGIN_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2W_USER_LOGIN_RESULT , get_id)(S_DC2W_USER_LOGIN_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_W2DC_USER_LOGIN_CHANNEL_WritePacket(S_W2DC_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2DC_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	static void _S_W2DC_USER_LOGIN_CHANNEL_WriteToPacket(S_W2DC_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2DC_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	void call_sq_W2DC_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2DC_USER_LOGIN_CHANNEL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2DC_USER_LOGIN_CHANNEL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_W2DC_USER_LOGIN_CHANNEL , get_id)(S_W2DC_USER_LOGIN_CHANNEL* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_DC2W_USER_LOGIN_CHANNEL_FAIL_WritePacket(S_DC2W_USER_LOGIN_CHANNEL_FAIL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(sendBuf,*pThis));
	}
	static void _S_DC2W_USER_LOGIN_CHANNEL_FAIL_WriteToPacket(S_DC2W_USER_LOGIN_CHANNEL_FAIL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(sendBuf,*pThis));
	}
	void call_sq_DC2W_USER_LOGIN_CHANNEL_FAIL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2W_USER_LOGIN_CHANNEL_FAIL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2W_USER_LOGIN_CHANNEL_FAIL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2W_USER_LOGIN_DUPLICATE_OK_WritePacket(S_DC2W_USER_LOGIN_DUPLICATE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(sendBuf,*pThis));
	}
	static void _S_DC2W_USER_LOGIN_DUPLICATE_OK_WriteToPacket(S_DC2W_USER_LOGIN_DUPLICATE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(sendBuf,*pThis));
	}
	void call_sq_DC2W_USER_LOGIN_DUPLICATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2W_USER_LOGIN_DUPLICATE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2W_USER_LOGIN_DUPLICATE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2W_USER_LOGIN_DUPLICATE_OK , get_id)(S_DC2W_USER_LOGIN_DUPLICATE_OK* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_W2_USER_DISCONNECT_WritePacket(S_W2_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_W2_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_W2_USER_DISCONNECT_WriteToPacket(S_W2_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_W2_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_W2_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_W2_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_W2_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2W_USER_LOGIN_CHANNEL_WritePacket(S_CH2W_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2W_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	static void _S_CH2W_USER_LOGIN_CHANNEL_WriteToPacket(S_CH2W_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2W_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	void call_sq_CH2W_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2W_USER_LOGIN_CHANNEL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2W_USER_LOGIN_CHANNEL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CH2W_USER_LOGIN_CHANNEL , get_id)(S_CH2W_USER_LOGIN_CHANNEL* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	#endif //WorldServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__WorldServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(CH2W_NEW_TOWN,jS(CH2W_NEW_TOWN),0);
		phtl.Insert(W_ERROR,jS(W_ERROR),0);
		phtl.Insert(W2DC_NEW_TOWN,jS(W2DC_NEW_TOWN),0);
		phtl.Insert(DC2W_NEW_TOWN_ERROR,jS(DC2W_NEW_TOWN_ERROR),0);
		phtl.Insert(DC2W_TOWN_DELETE_OK,jS(DC2W_TOWN_DELETE_OK),0);
		phtl.Insert(W4_USER_DISCONNECT,jS(W4_USER_DISCONNECT),0);
		phtl.Insert(W2DC_USER_DISCONNECT,jS(W2DC_USER_DISCONNECT),0);
		phtl.Insert(W2_USER_LOGIN_DUPLICATE,jS(W2_USER_LOGIN_DUPLICATE),0);
		phtl.Insert(W_HELLO,jS(W_HELLO),jS(Job_WorldServer));
		phtl.Insert(SS2W_ONLINE,jS(SS2W_ONLINE),0);
		phtl.Insert(W_SERVERINFO_ACK,jS(W_SERVERINFO_ACK),0);
		phtl.Insert(SS2W_SERVERINFO_ACK,jS(SS2W_SERVERINFO_ACK),0);
		phtl.Insert(W_ECHO,jS(W_ECHO),0);
		phtl.Insert(W2DC_USER_LOGIN,jS(W2DC_USER_LOGIN),0);
		phtl.Insert(DC2W_USER_LOGIN_RESULT,jS(DC2W_USER_LOGIN_RESULT),0);
		phtl.Insert(W2DC_USER_LOGIN_CHANNEL,jS(W2DC_USER_LOGIN_CHANNEL),0);
		phtl.Insert(DC2W_USER_LOGIN_CHANNEL_FAIL,jS(DC2W_USER_LOGIN_CHANNEL_FAIL),0);
		phtl.Insert(DC2W_USER_LOGIN_DUPLICATE_OK,jS(DC2W_USER_LOGIN_DUPLICATE_OK),0);
		phtl.Insert(W2_USER_DISCONNECT,jS(W2_USER_DISCONNECT),0);
		phtl.Insert(CH2W_USER_LOGIN_CHANNEL,jS(CH2W_USER_LOGIN_CHANNEL),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("WorldServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_CH2W_NEW_TOWN == CH2W_NEW_TOWN);
		jRAISE_PACKET(pk_W_ERROR == W_ERROR);
		jRAISE_PACKET(pk_W2DC_NEW_TOWN == W2DC_NEW_TOWN);
		jRAISE_PACKET(pk_DC2W_NEW_TOWN_ERROR == DC2W_NEW_TOWN_ERROR);
		jRAISE_PACKET(pk_DC2W_TOWN_DELETE_OK == DC2W_TOWN_DELETE_OK);
		jRAISE_PACKET(pk_W4_USER_DISCONNECT == W4_USER_DISCONNECT);
		jRAISE_PACKET(pk_W2DC_USER_DISCONNECT == W2DC_USER_DISCONNECT);
		jRAISE_PACKET(pk_W2_USER_LOGIN_DUPLICATE == W2_USER_LOGIN_DUPLICATE);
		jRAISE_PACKET(pk_W_HELLO == W_HELLO);
		jRAISE_PACKET(pk_SS2W_ONLINE == SS2W_ONLINE);
		jRAISE_PACKET(pk_W_SERVERINFO_ACK == W_SERVERINFO_ACK);
		jRAISE_PACKET(pk_SS2W_SERVERINFO_ACK == SS2W_SERVERINFO_ACK);
		jRAISE_PACKET(pk_W_ECHO == W_ECHO);
		jRAISE_PACKET(pk_W2DC_USER_LOGIN == W2DC_USER_LOGIN);
		jRAISE_PACKET(pk_DC2W_USER_LOGIN_RESULT == DC2W_USER_LOGIN_RESULT);
		jRAISE_PACKET(pk_W2DC_USER_LOGIN_CHANNEL == W2DC_USER_LOGIN_CHANNEL);
		jRAISE_PACKET(pk_DC2W_USER_LOGIN_CHANNEL_FAIL == DC2W_USER_LOGIN_CHANNEL_FAIL);
		jRAISE_PACKET(pk_DC2W_USER_LOGIN_DUPLICATE_OK == DC2W_USER_LOGIN_DUPLICATE_OK);
		jRAISE_PACKET(pk_W2_USER_DISCONNECT == W2_USER_DISCONNECT);
		jRAISE_PACKET(pk_CH2W_USER_LOGIN_CHANNEL == CH2W_USER_LOGIN_CHANNEL);

		#ifndef WorldServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_CH2W_NEW_TOWN)
			jSQ_var(pid,"player_id_t")
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tpsid,"Sys_TownPos_id_t")
			jSQ_gfn(S_CH2W_NEW_TOWN,get_town_name, "","return net_string")
			jSQ_fn(set_town_name,"tcstr sz","")
			jSQ_gfn(S_CH2W_NEW_TOWN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2W_NEW_TOWN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_W_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2DC_NEW_TOWN)
			jSQ_var(pid,"player_id_t")
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tpsid,"Sys_TownPos_id_t")
			jSQ_gfn(S_W2DC_NEW_TOWN,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_gfn(S_W2DC_NEW_TOWN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2DC_NEW_TOWN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2W_NEW_TOWN_ERROR)
			jSQ_var(pid,"player_id_t")
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tpsid,"Sys_TownPos_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_DC2W_NEW_TOWN_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2W_NEW_TOWN_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2W_TOWN_DELETE_OK)
			jSQ_gfn(S_DC2W_TOWN_DELETE_OK,get_user, "","return net_string")
			jSQ_fn(set_user,"tcstr sz","")
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tp,"Sys_TownPos_id_t")
			jSQ_gfn(S_DC2W_TOWN_DELETE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2W_TOWN_DELETE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W4_USER_DISCONNECT)
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_gfn(S_W4_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W4_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2DC_USER_DISCONNECT)
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_gfn(S_W2DC_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2DC_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2_USER_LOGIN_DUPLICATE)
			jSQ_gfn(S_W2_USER_LOGIN_DUPLICATE,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_W2_USER_LOGIN_DUPLICATE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2_USER_LOGIN_DUPLICATE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_W_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2W_ONLINE)
			jSQ_var(your_sid,"serverid_t")
			jSQ_var(my,"jServerInfo")
			jSQ_gfn(S_SS2W_ONLINE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2W_ONLINE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_W_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_SS2W_SERVERINFO_ACK)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_SS2W_SERVERINFO_ACK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_SS2W_SERVERINFO_ACK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W_ECHO)
			jSQ_gfn(S_W_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"int8")
			jSQ_gfn(S_W_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2DC_USER_LOGIN)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_W2DC_USER_LOGIN,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_W2DC_USER_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2DC_USER_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2W_USER_LOGIN_RESULT)
			jSQ_var(e,"jError")
			jSQ_gfn(S_DC2W_USER_LOGIN_RESULT,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_DC2W_USER_LOGIN_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2W_USER_LOGIN_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2DC_USER_LOGIN_CHANNEL)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_W2DC_USER_LOGIN_CHANNEL,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_var(town,"serverid_t")
			jSQ_gfn(S_W2DC_USER_LOGIN_CHANNEL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2DC_USER_LOGIN_CHANNEL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2W_USER_LOGIN_CHANNEL_FAIL)
			jSQ_var(pid,"player_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_DC2W_USER_LOGIN_CHANNEL_FAIL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2W_USER_LOGIN_CHANNEL_FAIL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2W_USER_LOGIN_DUPLICATE_OK)
			jSQ_gfn(S_DC2W_USER_LOGIN_DUPLICATE_OK,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_DC2W_USER_LOGIN_DUPLICATE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2W_USER_LOGIN_DUPLICATE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_W2_USER_DISCONNECT)
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_gfn(S_W2_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_W2_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2W_USER_LOGIN_CHANNEL)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_CH2W_USER_LOGIN_CHANNEL,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_CH2W_USER_LOGIN_CHANNEL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2W_USER_LOGIN_CHANNEL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //WorldServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__WorldServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("WorldServer"));
	}


}/* nWorldServer */ }/*nNET*/ } //nMech


#ifndef WorldServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_WorldServer(WorldServer);
jxDEFINE_WorldServer(CH2W_NEW_TOWN);
jxDEFINE_WorldServer(W_ERROR);
jxDEFINE_WorldServer(W2DC_NEW_TOWN);
jxDEFINE_WorldServer(DC2W_NEW_TOWN_ERROR);
jxDEFINE_WorldServer(DC2W_TOWN_DELETE_OK);
jxDEFINE_WorldServer(W4_USER_DISCONNECT);
jxDEFINE_WorldServer(W2DC_USER_DISCONNECT);
jxDEFINE_WorldServer(W2_USER_LOGIN_DUPLICATE);
jxDEFINE_WorldServer(W_HELLO);
jxDEFINE_WorldServer(SS2W_ONLINE);
jxDEFINE_WorldServer(W_SERVERINFO_ACK);
jxDEFINE_WorldServer(SS2W_SERVERINFO_ACK);
jxDEFINE_WorldServer(W_ECHO);
jxDEFINE_WorldServer(W2DC_USER_LOGIN);
jxDEFINE_WorldServer(DC2W_USER_LOGIN_RESULT);
jxDEFINE_WorldServer(W2DC_USER_LOGIN_CHANNEL);
jxDEFINE_WorldServer(DC2W_USER_LOGIN_CHANNEL_FAIL);
jxDEFINE_WorldServer(DC2W_USER_LOGIN_DUPLICATE_OK);
jxDEFINE_WorldServer(W2_USER_DISCONNECT);
jxDEFINE_WorldServer(CH2W_USER_LOGIN_CHANNEL);
#endif // WorldServer_jNOT_USE_PACKET_PLUGIN_HELP