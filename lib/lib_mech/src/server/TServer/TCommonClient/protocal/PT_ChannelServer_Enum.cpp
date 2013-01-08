
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_channel.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_ChannelServer_Enum.h"


#include "../my_PT_TServer.h"

#ifndef ChannelServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nChannelServer;
DECLARE_INSTANCE_TYPE(S_CH_ECHO);
DECLARE_INSTANCE_TYPE(S_X2CH_CHAT);
DECLARE_INSTANCE_TYPE(S_CH2X_CHAT);
DECLARE_INSTANCE_TYPE(S_X2CH_USER_LOGIN_CHANNEL);
DECLARE_INSTANCE_TYPE(S_CH2X_NEW_TOWN_OK);
DECLARE_INSTANCE_TYPE(S_X2CH_NEW_TOWN);
DECLARE_INSTANCE_TYPE(S_CH2X_SELECT_CASTLE);
DECLARE_INSTANCE_TYPE(S_X2CH_TOWN_SELECT);
DECLARE_INSTANCE_TYPE(S_X2CH_TOWN_DELETE);
DECLARE_INSTANCE_TYPE(S_CH2X_TOWN_DELETE_OK);
DECLARE_INSTANCE_TYPE(S_CH2X_TOWN_SELECT_RESULT);
DECLARE_INSTANCE_TYPE(S_CH2X_CREATE_NEW_TOWN);
DECLARE_INSTANCE_TYPE(S_X2CH_USER_EXIT);
DECLARE_INSTANCE_TYPE(S_CH2X_USER_EXIT);
DECLARE_INSTANCE_TYPE(S_X2CH_GOTO_CASTLE_MAP);
DECLARE_INSTANCE_TYPE(S_CH2X_GOTO_CASTLE_MAP);
DECLARE_INSTANCE_TYPE(S_X2CH_GOTO_WORLD_MAP);
DECLARE_INSTANCE_TYPE(S_CH2X_GOTO_WORLD_MAP);
DECLARE_INSTANCE_TYPE(S_CH2X_UPDATE_CASTLE_MAP);
DECLARE_INSTANCE_TYPE(S_CH2X_UDPATE_WORLD_MAP);
DECLARE_INSTANCE_TYPE(S_X2CH_GOTO_TOWN_MAP);
DECLARE_INSTANCE_TYPE(S_CH2X_GOTO_TOWN_MAP);
DECLARE_INSTANCE_TYPE(S_X2CH_NEW_BUILD);
DECLARE_INSTANCE_TYPE(S_X2CH_BUILD_UPGRADE);
DECLARE_INSTANCE_TYPE(S_CH2X_BUILD_UPGRADE_RESULT);
DECLARE_INSTANCE_TYPE(S_X2CH_BUILD_UPGRADE_CANCLE);
DECLARE_INSTANCE_TYPE(S_X2CH_BUILD_UPGRADE_CANCLE_OK);
DECLARE_INSTANCE_TYPE(S_X2CH_BUILD_UPGRADE_CHECK);
DECLARE_INSTANCE_TYPE(S_X2CH_BUILD_UPGRADE_CHECK_RESULT);
DECLARE_INSTANCE_TYPE(S_CH_ERROR);
DECLARE_INSTANCE_TYPE(S_CH_HELLO);
DECLARE_INSTANCE_TYPE(S_T2X_NOTICE);
DECLARE_INSTANCE_TYPE(S_X2L_NOTICE_TEST);
DECLARE_INSTANCE_TYPE(S_CH2X_USER_LOGIN_CHANNEL_OK);
DECLARE_INSTANCE_TYPE(S_CH2X_USER_LOGIN_CHANNEL_OK2);
DECLARE_INSTANCE_TYPE(S_CH2X_USER_LOGIN_CHANNEL_OK3);
#endif // ChannelServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nChannelServer
{
	PT_ChannelServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef ChannelServer_jNOTUSE_SQ_CODE
	static void _S_CH_ECHO_WritePacket(S_CH_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH_ECHO(sendBuf,*pThis));
	}
	static void _S_CH_ECHO_WriteToPacket(S_CH_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH_ECHO(sendBuf,*pThis));
	}
	void call_sq_CH_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CH_ECHO , get_msg)(S_CH_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_X2CH_CHAT_WritePacket(S_X2CH_CHAT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_CHAT(sendBuf,*pThis));
	}
	static void _S_X2CH_CHAT_WriteToPacket(S_X2CH_CHAT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_CHAT(sendBuf,*pThis));
	}
	void call_sq_X2CH_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_CHAT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_CHAT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_CHAT , get_msg)(S_X2CH_CHAT* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_CH2X_CHAT_WritePacket(S_CH2X_CHAT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_CHAT(sendBuf,*pThis));
	}
	static void _S_CH2X_CHAT_WriteToPacket(S_CH2X_CHAT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_CHAT(sendBuf,*pThis));
	}
	void call_sq_CH2X_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_CHAT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_CHAT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CH2X_CHAT , get_msg)(S_CH2X_CHAT* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_X2CH_USER_LOGIN_CHANNEL_WritePacket(S_X2CH_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	static void _S_X2CH_USER_LOGIN_CHANNEL_WriteToPacket(S_X2CH_USER_LOGIN_CHANNEL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_USER_LOGIN_CHANNEL(sendBuf,*pThis));
	}
	void call_sq_X2CH_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_USER_LOGIN_CHANNEL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_USER_LOGIN_CHANNEL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_USER_LOGIN_CHANNEL , get_id)(S_X2CH_USER_LOGIN_CHANNEL* pThis)
	{
		fname_t buf;return (pThis->get_id(buf));
	}

	static void _S_CH2X_NEW_TOWN_OK_WritePacket(S_CH2X_NEW_TOWN_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_NEW_TOWN_OK(sendBuf,*pThis));
	}
	static void _S_CH2X_NEW_TOWN_OK_WriteToPacket(S_CH2X_NEW_TOWN_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_NEW_TOWN_OK(sendBuf,*pThis));
	}
	void call_sq_CH2X_NEW_TOWN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_NEW_TOWN_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_NEW_TOWN_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_NEW_TOWN_WritePacket(S_X2CH_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_NEW_TOWN(sendBuf,*pThis));
	}
	static void _S_X2CH_NEW_TOWN_WriteToPacket(S_X2CH_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_NEW_TOWN(sendBuf,*pThis));
	}
	void call_sq_X2CH_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_NEW_TOWN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_NEW_TOWN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_NEW_TOWN , get_name)(S_X2CH_NEW_TOWN* pThis)
	{
		fname_t buf;return (pThis->get_name(buf));
	}

	static void _S_CH2X_SELECT_CASTLE_WritePacket(S_CH2X_SELECT_CASTLE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_SELECT_CASTLE(sendBuf,*pThis));
	}
	static void _S_CH2X_SELECT_CASTLE_WriteToPacket(S_CH2X_SELECT_CASTLE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_SELECT_CASTLE(sendBuf,*pThis));
	}
	void call_sq_CH2X_SELECT_CASTLE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_SELECT_CASTLE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_SELECT_CASTLE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_TOWN_SELECT_WritePacket(S_X2CH_TOWN_SELECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_TOWN_SELECT(sendBuf,*pThis));
	}
	static void _S_X2CH_TOWN_SELECT_WriteToPacket(S_X2CH_TOWN_SELECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_TOWN_SELECT(sendBuf,*pThis));
	}
	void call_sq_X2CH_TOWN_SELECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_TOWN_SELECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_TOWN_SELECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_TOWN_DELETE_WritePacket(S_X2CH_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_TOWN_DELETE(sendBuf,*pThis));
	}
	static void _S_X2CH_TOWN_DELETE_WriteToPacket(S_X2CH_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_TOWN_DELETE(sendBuf,*pThis));
	}
	void call_sq_X2CH_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_TOWN_DELETE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_TOWN_DELETE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_TOWN_DELETE_OK_WritePacket(S_CH2X_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	static void _S_CH2X_TOWN_DELETE_OK_WriteToPacket(S_CH2X_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	void call_sq_CH2X_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_TOWN_DELETE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_TOWN_DELETE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_TOWN_SELECT_RESULT_WritePacket(S_CH2X_TOWN_SELECT_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_TOWN_SELECT_RESULT(sendBuf,*pThis));
	}
	static void _S_CH2X_TOWN_SELECT_RESULT_WriteToPacket(S_CH2X_TOWN_SELECT_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_TOWN_SELECT_RESULT(sendBuf,*pThis));
	}
	void call_sq_CH2X_TOWN_SELECT_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_TOWN_SELECT_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_TOWN_SELECT_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_CREATE_NEW_TOWN_WritePacket(S_CH2X_CREATE_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_CREATE_NEW_TOWN(sendBuf,*pThis));
	}
	static void _S_CH2X_CREATE_NEW_TOWN_WriteToPacket(S_CH2X_CREATE_NEW_TOWN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_CREATE_NEW_TOWN(sendBuf,*pThis));
	}
	void call_sq_CH2X_CREATE_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_CREATE_NEW_TOWN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_CREATE_NEW_TOWN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_USER_EXIT_WritePacket(S_X2CH_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_X2CH_USER_EXIT_WriteToPacket(S_X2CH_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_X2CH_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_USER_EXIT_WritePacket(S_CH2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_USER_EXIT(sendBuf,*pThis));
	}
	static void _S_CH2X_USER_EXIT_WriteToPacket(S_CH2X_USER_EXIT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_USER_EXIT(sendBuf,*pThis));
	}
	void call_sq_CH2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_USER_EXIT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_USER_EXIT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_GOTO_CASTLE_MAP_WritePacket(S_X2CH_GOTO_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_GOTO_CASTLE_MAP(sendBuf,*pThis));
	}
	static void _S_X2CH_GOTO_CASTLE_MAP_WriteToPacket(S_X2CH_GOTO_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_GOTO_CASTLE_MAP(sendBuf,*pThis));
	}
	void call_sq_X2CH_GOTO_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_GOTO_CASTLE_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_GOTO_CASTLE_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_GOTO_CASTLE_MAP_WritePacket(S_CH2X_GOTO_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_GOTO_CASTLE_MAP(sendBuf,*pThis));
	}
	static void _S_CH2X_GOTO_CASTLE_MAP_WriteToPacket(S_CH2X_GOTO_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_GOTO_CASTLE_MAP(sendBuf,*pThis));
	}
	void call_sq_CH2X_GOTO_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_GOTO_CASTLE_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_GOTO_CASTLE_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_GOTO_WORLD_MAP_WritePacket(S_X2CH_GOTO_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_GOTO_WORLD_MAP(sendBuf,*pThis));
	}
	static void _S_X2CH_GOTO_WORLD_MAP_WriteToPacket(S_X2CH_GOTO_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_GOTO_WORLD_MAP(sendBuf,*pThis));
	}
	void call_sq_X2CH_GOTO_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_GOTO_WORLD_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_GOTO_WORLD_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_GOTO_WORLD_MAP_WritePacket(S_CH2X_GOTO_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_GOTO_WORLD_MAP(sendBuf,*pThis));
	}
	static void _S_CH2X_GOTO_WORLD_MAP_WriteToPacket(S_CH2X_GOTO_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_GOTO_WORLD_MAP(sendBuf,*pThis));
	}
	void call_sq_CH2X_GOTO_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_GOTO_WORLD_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_GOTO_WORLD_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_UPDATE_CASTLE_MAP_WritePacket(S_CH2X_UPDATE_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_UPDATE_CASTLE_MAP(sendBuf,*pThis));
	}
	static void _S_CH2X_UPDATE_CASTLE_MAP_WriteToPacket(S_CH2X_UPDATE_CASTLE_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_UPDATE_CASTLE_MAP(sendBuf,*pThis));
	}
	void call_sq_CH2X_UPDATE_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_UPDATE_CASTLE_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_UPDATE_CASTLE_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_UDPATE_WORLD_MAP_WritePacket(S_CH2X_UDPATE_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_UDPATE_WORLD_MAP(sendBuf,*pThis));
	}
	static void _S_CH2X_UDPATE_WORLD_MAP_WriteToPacket(S_CH2X_UDPATE_WORLD_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_UDPATE_WORLD_MAP(sendBuf,*pThis));
	}
	void call_sq_CH2X_UDPATE_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_UDPATE_WORLD_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_UDPATE_WORLD_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_GOTO_TOWN_MAP_WritePacket(S_X2CH_GOTO_TOWN_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_GOTO_TOWN_MAP(sendBuf,*pThis));
	}
	static void _S_X2CH_GOTO_TOWN_MAP_WriteToPacket(S_X2CH_GOTO_TOWN_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_GOTO_TOWN_MAP(sendBuf,*pThis));
	}
	void call_sq_X2CH_GOTO_TOWN_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_GOTO_TOWN_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_GOTO_TOWN_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_GOTO_TOWN_MAP_WritePacket(S_CH2X_GOTO_TOWN_MAP* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_GOTO_TOWN_MAP(sendBuf,*pThis));
	}
	static void _S_CH2X_GOTO_TOWN_MAP_WriteToPacket(S_CH2X_GOTO_TOWN_MAP* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_GOTO_TOWN_MAP(sendBuf,*pThis));
	}
	void call_sq_CH2X_GOTO_TOWN_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_GOTO_TOWN_MAP param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_GOTO_TOWN_MAP"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_X2CH_NEW_BUILD_WritePacket(S_X2CH_NEW_BUILD* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_NEW_BUILD(sendBuf,*pThis));
	}
	static void _S_X2CH_NEW_BUILD_WriteToPacket(S_X2CH_NEW_BUILD* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_NEW_BUILD(sendBuf,*pThis));
	}
	void call_sq_X2CH_NEW_BUILD(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_NEW_BUILD param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_NEW_BUILD"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_NEW_BUILD , get_build_slot)(S_X2CH_NEW_BUILD* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_X2CH_BUILD_UPGRADE_WritePacket(S_X2CH_BUILD_UPGRADE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_BUILD_UPGRADE(sendBuf,*pThis));
	}
	static void _S_X2CH_BUILD_UPGRADE_WriteToPacket(S_X2CH_BUILD_UPGRADE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_BUILD_UPGRADE(sendBuf,*pThis));
	}
	void call_sq_X2CH_BUILD_UPGRADE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_BUILD_UPGRADE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_BUILD_UPGRADE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_BUILD_UPGRADE , get_build_slot)(S_X2CH_BUILD_UPGRADE* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_CH2X_BUILD_UPGRADE_RESULT_WritePacket(S_CH2X_BUILD_UPGRADE_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_BUILD_UPGRADE_RESULT(sendBuf,*pThis));
	}
	static void _S_CH2X_BUILD_UPGRADE_RESULT_WriteToPacket(S_CH2X_BUILD_UPGRADE_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_BUILD_UPGRADE_RESULT(sendBuf,*pThis));
	}
	void call_sq_CH2X_BUILD_UPGRADE_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_BUILD_UPGRADE_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_BUILD_UPGRADE_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_CH2X_BUILD_UPGRADE_RESULT , get_build_slot)(S_CH2X_BUILD_UPGRADE_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_X2CH_BUILD_UPGRADE_CANCLE_WritePacket(S_X2CH_BUILD_UPGRADE_CANCLE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_BUILD_UPGRADE_CANCLE(sendBuf,*pThis));
	}
	static void _S_X2CH_BUILD_UPGRADE_CANCLE_WriteToPacket(S_X2CH_BUILD_UPGRADE_CANCLE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_BUILD_UPGRADE_CANCLE(sendBuf,*pThis));
	}
	void call_sq_X2CH_BUILD_UPGRADE_CANCLE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_BUILD_UPGRADE_CANCLE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_BUILD_UPGRADE_CANCLE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_BUILD_UPGRADE_CANCLE , get_build_slot)(S_X2CH_BUILD_UPGRADE_CANCLE* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_X2CH_BUILD_UPGRADE_CANCLE_OK_WritePacket(S_X2CH_BUILD_UPGRADE_CANCLE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_BUILD_UPGRADE_CANCLE_OK(sendBuf,*pThis));
	}
	static void _S_X2CH_BUILD_UPGRADE_CANCLE_OK_WriteToPacket(S_X2CH_BUILD_UPGRADE_CANCLE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_BUILD_UPGRADE_CANCLE_OK(sendBuf,*pThis));
	}
	void call_sq_X2CH_BUILD_UPGRADE_CANCLE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_BUILD_UPGRADE_CANCLE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_BUILD_UPGRADE_CANCLE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_BUILD_UPGRADE_CANCLE_OK , get_build_slot)(S_X2CH_BUILD_UPGRADE_CANCLE_OK* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_X2CH_BUILD_UPGRADE_CHECK_WritePacket(S_X2CH_BUILD_UPGRADE_CHECK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_BUILD_UPGRADE_CHECK(sendBuf,*pThis));
	}
	static void _S_X2CH_BUILD_UPGRADE_CHECK_WriteToPacket(S_X2CH_BUILD_UPGRADE_CHECK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_BUILD_UPGRADE_CHECK(sendBuf,*pThis));
	}
	void call_sq_X2CH_BUILD_UPGRADE_CHECK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_BUILD_UPGRADE_CHECK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_BUILD_UPGRADE_CHECK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_BUILD_UPGRADE_CHECK , get_build_slot)(S_X2CH_BUILD_UPGRADE_CHECK* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_X2CH_BUILD_UPGRADE_CHECK_RESULT_WritePacket(S_X2CH_BUILD_UPGRADE_CHECK_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2CH_BUILD_UPGRADE_CHECK_RESULT(sendBuf,*pThis));
	}
	static void _S_X2CH_BUILD_UPGRADE_CHECK_RESULT_WriteToPacket(S_X2CH_BUILD_UPGRADE_CHECK_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2CH_BUILD_UPGRADE_CHECK_RESULT(sendBuf,*pThis));
	}
	void call_sq_X2CH_BUILD_UPGRADE_CHECK_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2CH_BUILD_UPGRADE_CHECK_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2CH_BUILD_UPGRADE_CHECK_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_X2CH_BUILD_UPGRADE_CHECK_RESULT , get_build_slot)(S_X2CH_BUILD_UPGRADE_CHECK_RESULT* pThis)
	{
		fname_t buf;return (pThis->get_build_slot(buf));
	}

	static void _S_CH_ERROR_WritePacket(S_CH_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH_ERROR(sendBuf,*pThis));
	}
	static void _S_CH_ERROR_WriteToPacket(S_CH_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH_ERROR(sendBuf,*pThis));
	}
	void call_sq_CH_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH_HELLO_WritePacket(S_CH_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH_HELLO(sendBuf,*pThis));
	}
	static void _S_CH_HELLO_WriteToPacket(S_CH_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH_HELLO(sendBuf,*pThis));
	}
	void call_sq_CH_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_T2X_NOTICE_WritePacket(S_T2X_NOTICE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_T2X_NOTICE(sendBuf,*pThis));
	}
	static void _S_T2X_NOTICE_WriteToPacket(S_T2X_NOTICE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_T2X_NOTICE(sendBuf,*pThis));
	}
	void call_sq_T2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_T2X_NOTICE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_T2X_NOTICE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_T2X_NOTICE , get_msg)(S_T2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_T2X_NOTICE , get_date)(S_T2X_NOTICE* pThis)
	{
		fname_t buf;return (pThis->get_date(buf));
	}

	static void _S_X2L_NOTICE_TEST_WritePacket(S_X2L_NOTICE_TEST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_X2L_NOTICE_TEST(sendBuf,*pThis));
	}
	static void _S_X2L_NOTICE_TEST_WriteToPacket(S_X2L_NOTICE_TEST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_X2L_NOTICE_TEST(sendBuf,*pThis));
	}
	void call_sq_X2L_NOTICE_TEST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_X2L_NOTICE_TEST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_X2L_NOTICE_TEST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_USER_LOGIN_CHANNEL_OK_WritePacket(S_CH2X_USER_LOGIN_CHANNEL_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_USER_LOGIN_CHANNEL_OK(sendBuf,*pThis));
	}
	static void _S_CH2X_USER_LOGIN_CHANNEL_OK_WriteToPacket(S_CH2X_USER_LOGIN_CHANNEL_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_USER_LOGIN_CHANNEL_OK(sendBuf,*pThis));
	}
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_USER_LOGIN_CHANNEL_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_USER_LOGIN_CHANNEL_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_USER_LOGIN_CHANNEL_OK2_WritePacket(S_CH2X_USER_LOGIN_CHANNEL_OK2* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_USER_LOGIN_CHANNEL_OK2(sendBuf,*pThis));
	}
	static void _S_CH2X_USER_LOGIN_CHANNEL_OK2_WriteToPacket(S_CH2X_USER_LOGIN_CHANNEL_OK2* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_USER_LOGIN_CHANNEL_OK2(sendBuf,*pThis));
	}
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_USER_LOGIN_CHANNEL_OK2 param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_USER_LOGIN_CHANNEL_OK2"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_CH2X_USER_LOGIN_CHANNEL_OK3_WritePacket(S_CH2X_USER_LOGIN_CHANNEL_OK3* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_CH2X_USER_LOGIN_CHANNEL_OK3(sendBuf,*pThis));
	}
	static void _S_CH2X_USER_LOGIN_CHANNEL_OK3_WriteToPacket(S_CH2X_USER_LOGIN_CHANNEL_OK3* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_CH2X_USER_LOGIN_CHANNEL_OK3(sendBuf,*pThis));
	}
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK3(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_CH2X_USER_LOGIN_CHANNEL_OK3 param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_CH2X_USER_LOGIN_CHANNEL_OK3"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //ChannelServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__ChannelServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(CH_ECHO,jS(CH_ECHO),0);
		phtl.Insert(X2CH_CHAT,jS(X2CH_CHAT),0);
		phtl.Insert(CH2X_CHAT,jS(CH2X_CHAT),0);
		phtl.Insert(X2CH_USER_LOGIN_CHANNEL,jS(X2CH_USER_LOGIN_CHANNEL),0);
		phtl.Insert(CH2X_NEW_TOWN_OK,jS(CH2X_NEW_TOWN_OK),0);
		phtl.Insert(X2CH_NEW_TOWN,jS(X2CH_NEW_TOWN),0);
		phtl.Insert(CH2X_SELECT_CASTLE,jS(CH2X_SELECT_CASTLE),0);
		phtl.Insert(X2CH_TOWN_SELECT,jS(X2CH_TOWN_SELECT),0);
		phtl.Insert(X2CH_TOWN_DELETE,jS(X2CH_TOWN_DELETE),0);
		phtl.Insert(CH2X_TOWN_DELETE_OK,jS(CH2X_TOWN_DELETE_OK),0);
		phtl.Insert(CH2X_TOWN_SELECT_RESULT,jS(CH2X_TOWN_SELECT_RESULT),0);
		phtl.Insert(CH2X_CREATE_NEW_TOWN,jS(CH2X_CREATE_NEW_TOWN),0);
		phtl.Insert(X2CH_USER_EXIT,jS(X2CH_USER_EXIT),0);
		phtl.Insert(CH2X_USER_EXIT,jS(CH2X_USER_EXIT),0);
		phtl.Insert(X2CH_GOTO_CASTLE_MAP,jS(X2CH_GOTO_CASTLE_MAP),0);
		phtl.Insert(CH2X_GOTO_CASTLE_MAP,jS(CH2X_GOTO_CASTLE_MAP),0);
		phtl.Insert(X2CH_GOTO_WORLD_MAP,jS(X2CH_GOTO_WORLD_MAP),0);
		phtl.Insert(CH2X_GOTO_WORLD_MAP,jS(CH2X_GOTO_WORLD_MAP),0);
		phtl.Insert(CH2X_UPDATE_CASTLE_MAP,jS(CH2X_UPDATE_CASTLE_MAP),0);
		phtl.Insert(CH2X_UDPATE_WORLD_MAP,jS(CH2X_UDPATE_WORLD_MAP),0);
		phtl.Insert(X2CH_GOTO_TOWN_MAP,jS(X2CH_GOTO_TOWN_MAP),0);
		phtl.Insert(CH2X_GOTO_TOWN_MAP,jS(CH2X_GOTO_TOWN_MAP),0);
		phtl.Insert(X2CH_NEW_BUILD,jS(X2CH_NEW_BUILD),0);
		phtl.Insert(X2CH_BUILD_UPGRADE,jS(X2CH_BUILD_UPGRADE),0);
		phtl.Insert(CH2X_BUILD_UPGRADE_RESULT,jS(CH2X_BUILD_UPGRADE_RESULT),0);
		phtl.Insert(X2CH_BUILD_UPGRADE_CANCLE,jS(X2CH_BUILD_UPGRADE_CANCLE),0);
		phtl.Insert(X2CH_BUILD_UPGRADE_CANCLE_OK,jS(X2CH_BUILD_UPGRADE_CANCLE_OK),0);
		phtl.Insert(X2CH_BUILD_UPGRADE_CHECK,jS(X2CH_BUILD_UPGRADE_CHECK),0);
		phtl.Insert(X2CH_BUILD_UPGRADE_CHECK_RESULT,jS(X2CH_BUILD_UPGRADE_CHECK_RESULT),0);
		phtl.Insert(CH_ERROR,jS(CH_ERROR),0);
		phtl.Insert(CH_HELLO,jS(CH_HELLO),0);
		phtl.Insert(T2X_NOTICE,jS(T2X_NOTICE),0);
		phtl.Insert(X2L_NOTICE_TEST,jS(X2L_NOTICE_TEST),0);
		phtl.Insert(CH2X_USER_LOGIN_CHANNEL_OK,jS(CH2X_USER_LOGIN_CHANNEL_OK),0);
		phtl.Insert(CH2X_USER_LOGIN_CHANNEL_OK2,jS(CH2X_USER_LOGIN_CHANNEL_OK2),0);
		phtl.Insert(CH2X_USER_LOGIN_CHANNEL_OK3,jS(CH2X_USER_LOGIN_CHANNEL_OK3),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("ChannelServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_CH_ECHO == CH_ECHO);
		jRAISE_PACKET(pk_X2CH_CHAT == X2CH_CHAT);
		jRAISE_PACKET(pk_CH2X_CHAT == CH2X_CHAT);
		jRAISE_PACKET(pk_X2CH_USER_LOGIN_CHANNEL == X2CH_USER_LOGIN_CHANNEL);
		jRAISE_PACKET(pk_CH2X_NEW_TOWN_OK == CH2X_NEW_TOWN_OK);
		jRAISE_PACKET(pk_X2CH_NEW_TOWN == X2CH_NEW_TOWN);
		jRAISE_PACKET(pk_CH2X_SELECT_CASTLE == CH2X_SELECT_CASTLE);
		jRAISE_PACKET(pk_X2CH_TOWN_SELECT == X2CH_TOWN_SELECT);
		jRAISE_PACKET(pk_X2CH_TOWN_DELETE == X2CH_TOWN_DELETE);
		jRAISE_PACKET(pk_CH2X_TOWN_DELETE_OK == CH2X_TOWN_DELETE_OK);
		jRAISE_PACKET(pk_CH2X_TOWN_SELECT_RESULT == CH2X_TOWN_SELECT_RESULT);
		jRAISE_PACKET(pk_CH2X_CREATE_NEW_TOWN == CH2X_CREATE_NEW_TOWN);
		jRAISE_PACKET(pk_X2CH_USER_EXIT == X2CH_USER_EXIT);
		jRAISE_PACKET(pk_CH2X_USER_EXIT == CH2X_USER_EXIT);
		jRAISE_PACKET(pk_X2CH_GOTO_CASTLE_MAP == X2CH_GOTO_CASTLE_MAP);
		jRAISE_PACKET(pk_CH2X_GOTO_CASTLE_MAP == CH2X_GOTO_CASTLE_MAP);
		jRAISE_PACKET(pk_X2CH_GOTO_WORLD_MAP == X2CH_GOTO_WORLD_MAP);
		jRAISE_PACKET(pk_CH2X_GOTO_WORLD_MAP == CH2X_GOTO_WORLD_MAP);
		jRAISE_PACKET(pk_CH2X_UPDATE_CASTLE_MAP == CH2X_UPDATE_CASTLE_MAP);
		jRAISE_PACKET(pk_CH2X_UDPATE_WORLD_MAP == CH2X_UDPATE_WORLD_MAP);
		jRAISE_PACKET(pk_X2CH_GOTO_TOWN_MAP == X2CH_GOTO_TOWN_MAP);
		jRAISE_PACKET(pk_CH2X_GOTO_TOWN_MAP == CH2X_GOTO_TOWN_MAP);
		jRAISE_PACKET(pk_X2CH_NEW_BUILD == X2CH_NEW_BUILD);
		jRAISE_PACKET(pk_X2CH_BUILD_UPGRADE == X2CH_BUILD_UPGRADE);
		jRAISE_PACKET(pk_CH2X_BUILD_UPGRADE_RESULT == CH2X_BUILD_UPGRADE_RESULT);
		jRAISE_PACKET(pk_X2CH_BUILD_UPGRADE_CANCLE == X2CH_BUILD_UPGRADE_CANCLE);
		jRAISE_PACKET(pk_X2CH_BUILD_UPGRADE_CANCLE_OK == X2CH_BUILD_UPGRADE_CANCLE_OK);
		jRAISE_PACKET(pk_X2CH_BUILD_UPGRADE_CHECK == X2CH_BUILD_UPGRADE_CHECK);
		jRAISE_PACKET(pk_X2CH_BUILD_UPGRADE_CHECK_RESULT == X2CH_BUILD_UPGRADE_CHECK_RESULT);
		jRAISE_PACKET(pk_CH_ERROR == CH_ERROR);
		jRAISE_PACKET(pk_CH_HELLO == CH_HELLO);
		jRAISE_PACKET(pk_T2X_NOTICE == T2X_NOTICE);
		jRAISE_PACKET(pk_X2L_NOTICE_TEST == X2L_NOTICE_TEST);
		jRAISE_PACKET(pk_CH2X_USER_LOGIN_CHANNEL_OK == CH2X_USER_LOGIN_CHANNEL_OK);
		jRAISE_PACKET(pk_CH2X_USER_LOGIN_CHANNEL_OK2 == CH2X_USER_LOGIN_CHANNEL_OK2);
		jRAISE_PACKET(pk_CH2X_USER_LOGIN_CHANNEL_OK3 == CH2X_USER_LOGIN_CHANNEL_OK3);

		#ifndef ChannelServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_CH_ECHO)
			jSQ_gfn(S_CH_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_gfn(S_CH_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_CHAT)
			jSQ_gfn(S_X2CH_CHAT,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_fn(get_id,"int i","return wstring*")
			jSQ_fn(set_id,"int i,wstring* data","")
			jSQ_fn(insert_id,"wstring* data","")
			jSQ_fn(clear_id,"","")
			jSQ_fn(size_id,"","return size_t")
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_gfn(S_X2CH_CHAT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_CHAT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_CHAT)
			jSQ_gfn(S_CH2X_CHAT,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_var(type,"uint8")
			jSQ_gfn(S_CH2X_CHAT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_CHAT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_USER_LOGIN_CHANNEL)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_X2CH_USER_LOGIN_CHANNEL,get_id, "","return net_string")
			jSQ_fn(set_id,"tcstr sz","")
			jSQ_gfn(S_X2CH_USER_LOGIN_CHANNEL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_USER_LOGIN_CHANNEL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_NEW_TOWN_OK)
			jSQ_var(index,"channelid_t")
			jSQ_var(town,"Use_Town")
			jSQ_gfn(S_CH2X_NEW_TOWN_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_NEW_TOWN_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_NEW_TOWN)
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tpsid,"Sys_TownPos_id_t")
			jSQ_gfn(S_X2CH_NEW_TOWN,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_gfn(S_X2CH_NEW_TOWN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_NEW_TOWN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_SELECT_CASTLE)
			jSQ_gfn(S_CH2X_SELECT_CASTLE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_SELECT_CASTLE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_TOWN_SELECT)
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_X2CH_TOWN_SELECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_TOWN_SELECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_TOWN_DELETE)
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_X2CH_TOWN_DELETE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_TOWN_DELETE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_TOWN_DELETE_OK)
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_CH2X_TOWN_DELETE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_TOWN_DELETE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_TOWN_SELECT_RESULT)
			jSQ_var(channelNo,"channelid_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_CH2X_TOWN_SELECT_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_TOWN_SELECT_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_CREATE_NEW_TOWN)
			jSQ_gfn(S_CH2X_CREATE_NEW_TOWN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_CREATE_NEW_TOWN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_USER_EXIT)
			jSQ_gfn(S_X2CH_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_USER_EXIT)
			jSQ_gfn(S_CH2X_USER_EXIT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_USER_EXIT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_GOTO_CASTLE_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_gfn(S_X2CH_GOTO_CASTLE_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_GOTO_CASTLE_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_GOTO_CASTLE_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_var(castle_map_info,"jIE*")
			jSQ_gfn(S_CH2X_GOTO_CASTLE_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_GOTO_CASTLE_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_GOTO_WORLD_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_gfn(S_X2CH_GOTO_WORLD_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_GOTO_WORLD_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_GOTO_WORLD_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_var(world_map_info,"jIE*")
			jSQ_gfn(S_CH2X_GOTO_WORLD_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_GOTO_WORLD_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_UPDATE_CASTLE_MAP)
			jSQ_var(castle_map_info,"jIE*")
			jSQ_gfn(S_CH2X_UPDATE_CASTLE_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_UPDATE_CASTLE_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_UDPATE_WORLD_MAP)
			jSQ_var(world_map_info,"jIE*")
			jSQ_gfn(S_CH2X_UDPATE_WORLD_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_UDPATE_WORLD_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_GOTO_TOWN_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_gfn(S_X2CH_GOTO_TOWN_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_GOTO_TOWN_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_GOTO_TOWN_MAP)
			jSQ_var(channelNo,"uint8")
			jSQ_gfn(S_CH2X_GOTO_TOWN_MAP,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_GOTO_TOWN_MAP,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_NEW_BUILD)
			jSQ_gfn(S_X2CH_NEW_BUILD,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_var(_EBuildType,"uint8")
			jSQ_var(hero_id,"uint8")
			jSQ_gfn(S_X2CH_NEW_BUILD,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_NEW_BUILD,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_BUILD_UPGRADE)
			jSQ_gfn(S_X2CH_BUILD_UPGRADE,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_var(hero_id,"uint8")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_BUILD_UPGRADE_RESULT)
			jSQ_gfn(S_CH2X_BUILD_UPGRADE_RESULT,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_var(_EBuildType,"uint8")
			jSQ_var(level,"uint8")
			jSQ_var(e,"jError")
			jSQ_var(curr_server_time,"j_time_t")
			jSQ_var(upgrade_sec,"int32")
			jSQ_var(hero_id,"uint8")
			jSQ_gfn(S_CH2X_BUILD_UPGRADE_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_BUILD_UPGRADE_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_BUILD_UPGRADE_CANCLE)
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_BUILD_UPGRADE_CANCLE_OK)
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE_OK,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CANCLE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_BUILD_UPGRADE_CHECK)
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2CH_BUILD_UPGRADE_CHECK_RESULT)
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK_RESULT,get_build_slot, "","return net_string")
			jSQ_fn(set_build_slot,"tcstr sz","")
			jSQ_var(e,"jError")
			jSQ_var(left_sec,"int32")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2CH_BUILD_UPGRADE_CHECK_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_CH_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH_HELLO)
			jSQ_var(si,"jServerInfo")
			jSQ_gfn(S_CH_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_T2X_NOTICE)
			jSQ_var(info,"jNoticeInfo")
			jSQ_gfn(S_T2X_NOTICE,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_T2X_NOTICE,get_date, "","return net_string")
			jSQ_fn(set_date,"tcstr sz","")
			jSQ_gfn(S_T2X_NOTICE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_T2X_NOTICE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_X2L_NOTICE_TEST)
			jSQ_gfn(S_X2L_NOTICE_TEST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_X2L_NOTICE_TEST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_USER_LOGIN_CHANNEL_OK)
			jSQ_var(user,"nAQ::Use_User")
			jSQ_fn(get_town,"int i","return nAQ::Use_Town*")
			jSQ_fn(set_town,"int i,nAQ::Use_Town* data","")
			jSQ_fn(insert_town,"nAQ::Use_Town* data","")
			jSQ_fn(clear_town,"","")
			jSQ_fn(size_town,"","return size_t")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_USER_LOGIN_CHANNEL_OK2)
			jSQ_fn(get_hero,"int i","return nAQ::Use_Hero*")
			jSQ_fn(set_hero,"int i,nAQ::Use_Hero* data","")
			jSQ_fn(insert_hero,"nAQ::Use_Hero* data","")
			jSQ_fn(clear_hero,"","")
			jSQ_fn(size_hero,"","return size_t")
			jSQ_fn(get_force,"int i","return nAQ::Use_Force*")
			jSQ_fn(set_force,"int i,nAQ::Use_Force* data","")
			jSQ_fn(insert_force,"nAQ::Use_Force* data","")
			jSQ_fn(clear_force,"","")
			jSQ_fn(size_force,"","return size_t")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK2,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK2,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_CH2X_USER_LOGIN_CHANNEL_OK3)
			jSQ_var(town_xml,"jIE*")
			jSQ_var(server_time,"j_time_t")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK3,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_CH2X_USER_LOGIN_CHANNEL_OK3,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //ChannelServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__ChannelServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("ChannelServer"));
	}


}/* nChannelServer */ }/*nNET*/ } //nMech


#ifndef ChannelServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_ChannelServer(ChannelServer);
jxDEFINE_ChannelServer(CH_ECHO);
jxDEFINE_ChannelServer(X2CH_CHAT);
jxDEFINE_ChannelServer(CH2X_CHAT);
jxDEFINE_ChannelServer(X2CH_USER_LOGIN_CHANNEL);
jxDEFINE_ChannelServer(CH2X_NEW_TOWN_OK);
jxDEFINE_ChannelServer(X2CH_NEW_TOWN);
jxDEFINE_ChannelServer(CH2X_SELECT_CASTLE);
jxDEFINE_ChannelServer(X2CH_TOWN_SELECT);
jxDEFINE_ChannelServer(X2CH_TOWN_DELETE);
jxDEFINE_ChannelServer(CH2X_TOWN_DELETE_OK);
jxDEFINE_ChannelServer(CH2X_TOWN_SELECT_RESULT);
jxDEFINE_ChannelServer(CH2X_CREATE_NEW_TOWN);
jxDEFINE_ChannelServer(X2CH_USER_EXIT);
jxDEFINE_ChannelServer(CH2X_USER_EXIT);
jxDEFINE_ChannelServer(X2CH_GOTO_CASTLE_MAP);
jxDEFINE_ChannelServer(CH2X_GOTO_CASTLE_MAP);
jxDEFINE_ChannelServer(X2CH_GOTO_WORLD_MAP);
jxDEFINE_ChannelServer(CH2X_GOTO_WORLD_MAP);
jxDEFINE_ChannelServer(CH2X_UPDATE_CASTLE_MAP);
jxDEFINE_ChannelServer(CH2X_UDPATE_WORLD_MAP);
jxDEFINE_ChannelServer(X2CH_GOTO_TOWN_MAP);
jxDEFINE_ChannelServer(CH2X_GOTO_TOWN_MAP);
jxDEFINE_ChannelServer(X2CH_NEW_BUILD);
jxDEFINE_ChannelServer(X2CH_BUILD_UPGRADE);
jxDEFINE_ChannelServer(CH2X_BUILD_UPGRADE_RESULT);
jxDEFINE_ChannelServer(X2CH_BUILD_UPGRADE_CANCLE);
jxDEFINE_ChannelServer(X2CH_BUILD_UPGRADE_CANCLE_OK);
jxDEFINE_ChannelServer(X2CH_BUILD_UPGRADE_CHECK);
jxDEFINE_ChannelServer(X2CH_BUILD_UPGRADE_CHECK_RESULT);
jxDEFINE_ChannelServer(CH_ERROR);
jxDEFINE_ChannelServer(CH_HELLO);
jxDEFINE_ChannelServer(T2X_NOTICE);
jxDEFINE_ChannelServer(X2L_NOTICE_TEST);
jxDEFINE_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK);
jxDEFINE_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK2);
jxDEFINE_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK3);
#endif // ChannelServer_jNOT_USE_PACKET_PLUGIN_HELP