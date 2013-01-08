
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dbquery.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_DBQueryServer_Enum.h"



#ifndef DBQueryServer_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nDBQueryServer;
DECLARE_INSTANCE_TYPE(S_DC2DQ_USER_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_DQ_ECHO);
DECLARE_INSTANCE_TYPE(S_DQ_ERROR);
DECLARE_INSTANCE_TYPE(S_DC2DQ_TOWN_CREATE);
DECLARE_INSTANCE_TYPE(S_DQ2DC_TOWN_CREATE_OK);
DECLARE_INSTANCE_TYPE(S_DC2DQ_TOWN_DELETE);
DECLARE_INSTANCE_TYPE(S_DQ2DC_TOWN_DELETE_OK);
DECLARE_INSTANCE_TYPE(S_DC2DQ_INSERT_ITEM_AND_SKILL);
DECLARE_INSTANCE_TYPE(S_DQ2DC_TOWN_CREATE_ERROR);
DECLARE_INSTANCE_TYPE(S_DC2DQ_CONNECT);
DECLARE_INSTANCE_TYPE(S_DQ2DC_CONNECT);
DECLARE_INSTANCE_TYPE(S_DQ2DC_CONNECT_OK);
DECLARE_INSTANCE_TYPE(S_DC2DQ_CONNECT_OK);
DECLARE_INSTANCE_TYPE(S_DC2DQ_USER_LOGIN);
DECLARE_INSTANCE_TYPE(S_DQ2DC_USER_LOGIN_RESULT);
DECLARE_INSTANCE_TYPE(S_DC2DQ_GET_TOWN_LIST);
DECLARE_INSTANCE_TYPE(S_DQ2DC_SEND_TOWN_LIST);
#endif // DBQueryServer_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nDBQueryServer
{
	PT_DBQueryServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef DBQueryServer_jNOTUSE_SQ_CODE
	static void _S_DC2DQ_USER_DISCONNECT_WritePacket(S_DC2DQ_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_USER_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_DC2DQ_USER_DISCONNECT_WriteToPacket(S_DC2DQ_USER_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_USER_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_USER_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_USER_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DQ_ECHO_WritePacket(S_DQ_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ_ECHO(sendBuf,*pThis));
	}
	static void _S_DQ_ECHO_WriteToPacket(S_DQ_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ_ECHO(sendBuf,*pThis));
	}
	void call_sq_DQ_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ_ECHO , get_msg)(S_DQ_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_DQ_ERROR_WritePacket(S_DQ_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ_ERROR(sendBuf,*pThis));
	}
	static void _S_DQ_ERROR_WriteToPacket(S_DQ_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ_ERROR(sendBuf,*pThis));
	}
	void call_sq_DQ_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_TOWN_CREATE_WritePacket(S_DC2DQ_TOWN_CREATE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_TOWN_CREATE(sendBuf,*pThis));
	}
	static void _S_DC2DQ_TOWN_CREATE_WriteToPacket(S_DC2DQ_TOWN_CREATE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_TOWN_CREATE(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_TOWN_CREATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_TOWN_CREATE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_TOWN_CREATE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2DQ_TOWN_CREATE , get_name)(S_DC2DQ_TOWN_CREATE* pThis)
	{
		fname_t buf;return (pThis->get_name(buf));
	}

	static void _S_DQ2DC_TOWN_CREATE_OK_WritePacket(S_DQ2DC_TOWN_CREATE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_TOWN_CREATE_OK(sendBuf,*pThis));
	}
	static void _S_DQ2DC_TOWN_CREATE_OK_WriteToPacket(S_DQ2DC_TOWN_CREATE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_TOWN_CREATE_OK(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_TOWN_CREATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_TOWN_CREATE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_TOWN_CREATE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_TOWN_DELETE_WritePacket(S_DC2DQ_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_TOWN_DELETE(sendBuf,*pThis));
	}
	static void _S_DC2DQ_TOWN_DELETE_WriteToPacket(S_DC2DQ_TOWN_DELETE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_TOWN_DELETE(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_TOWN_DELETE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_TOWN_DELETE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DQ2DC_TOWN_DELETE_OK_WritePacket(S_DQ2DC_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	static void _S_DQ2DC_TOWN_DELETE_OK_WriteToPacket(S_DQ2DC_TOWN_DELETE_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_TOWN_DELETE_OK(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_TOWN_DELETE_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_TOWN_DELETE_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_INSERT_ITEM_AND_SKILL_WritePacket(S_DC2DQ_INSERT_ITEM_AND_SKILL* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_INSERT_ITEM_AND_SKILL(sendBuf,*pThis));
	}
	static void _S_DC2DQ_INSERT_ITEM_AND_SKILL_WriteToPacket(S_DC2DQ_INSERT_ITEM_AND_SKILL* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_INSERT_ITEM_AND_SKILL(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_INSERT_ITEM_AND_SKILL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_INSERT_ITEM_AND_SKILL param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_INSERT_ITEM_AND_SKILL"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DQ2DC_TOWN_CREATE_ERROR_WritePacket(S_DQ2DC_TOWN_CREATE_ERROR* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_TOWN_CREATE_ERROR(sendBuf,*pThis));
	}
	static void _S_DQ2DC_TOWN_CREATE_ERROR_WriteToPacket(S_DQ2DC_TOWN_CREATE_ERROR* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_TOWN_CREATE_ERROR(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_TOWN_CREATE_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_TOWN_CREATE_ERROR param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_TOWN_CREATE_ERROR"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_CONNECT_WritePacket(S_DC2DQ_CONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_CONNECT(sendBuf,*pThis));
	}
	static void _S_DC2DQ_CONNECT_WriteToPacket(S_DC2DQ_CONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_CONNECT(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_CONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_CONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_CONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2DQ_CONNECT , get_WORLD_NAME)(S_DC2DQ_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_WORLD_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2DQ_CONNECT , get_SM_QUERY2CACHE_NAME)(S_DC2DQ_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_QUERY2CACHE_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2DQ_CONNECT , get_SM_CACHE2QUERY_NAME)(S_DC2DQ_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_CACHE2QUERY_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DC2DQ_CONNECT , get_SM_USER_INFO_NAME)(S_DC2DQ_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_USER_INFO_NAME(buf));
	}

	static void _S_DQ2DC_CONNECT_WritePacket(S_DQ2DC_CONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_CONNECT(sendBuf,*pThis));
	}
	static void _S_DQ2DC_CONNECT_WriteToPacket(S_DQ2DC_CONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_CONNECT(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_CONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_CONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_CONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ2DC_CONNECT , get_WORLD_NAME)(S_DQ2DC_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_WORLD_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ2DC_CONNECT , get_SM_QUERY2CACHE_NAME)(S_DQ2DC_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_QUERY2CACHE_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ2DC_CONNECT , get_SM_CACHE2QUERY_NAME)(S_DQ2DC_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_CACHE2QUERY_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ2DC_CONNECT , get_SM_USER_INFO_NAME)(S_DQ2DC_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_SM_USER_INFO_NAME(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_DQ2DC_CONNECT , get_GAMEDB_NAME)(S_DQ2DC_CONNECT* pThis)
	{
		fname_t buf;return (pThis->get_GAMEDB_NAME(buf));
	}

	static void _S_DQ2DC_CONNECT_OK_WritePacket(S_DQ2DC_CONNECT_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_CONNECT_OK(sendBuf,*pThis));
	}
	static void _S_DQ2DC_CONNECT_OK_WriteToPacket(S_DQ2DC_CONNECT_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_CONNECT_OK(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_CONNECT_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_CONNECT_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_CONNECT_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_CONNECT_OK_WritePacket(S_DC2DQ_CONNECT_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_CONNECT_OK(sendBuf,*pThis));
	}
	static void _S_DC2DQ_CONNECT_OK_WriteToPacket(S_DC2DQ_CONNECT_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_CONNECT_OK(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_CONNECT_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_CONNECT_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_CONNECT_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_USER_LOGIN_WritePacket(S_DC2DQ_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_USER_LOGIN(sendBuf,*pThis));
	}
	static void _S_DC2DQ_USER_LOGIN_WriteToPacket(S_DC2DQ_USER_LOGIN* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_USER_LOGIN(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_USER_LOGIN param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_USER_LOGIN"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DQ2DC_USER_LOGIN_RESULT_WritePacket(S_DQ2DC_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	static void _S_DQ2DC_USER_LOGIN_RESULT_WriteToPacket(S_DQ2DC_USER_LOGIN_RESULT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_USER_LOGIN_RESULT(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_USER_LOGIN_RESULT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_USER_LOGIN_RESULT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DC2DQ_GET_TOWN_LIST_WritePacket(S_DC2DQ_GET_TOWN_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DC2DQ_GET_TOWN_LIST(sendBuf,*pThis));
	}
	static void _S_DC2DQ_GET_TOWN_LIST_WriteToPacket(S_DC2DQ_GET_TOWN_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DC2DQ_GET_TOWN_LIST(sendBuf,*pThis));
	}
	void call_sq_DC2DQ_GET_TOWN_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DC2DQ_GET_TOWN_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DC2DQ_GET_TOWN_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_DQ2DC_SEND_TOWN_LIST_WritePacket(S_DQ2DC_SEND_TOWN_LIST* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_DQ2DC_SEND_TOWN_LIST(sendBuf,*pThis));
	}
	static void _S_DQ2DC_SEND_TOWN_LIST_WriteToPacket(S_DQ2DC_SEND_TOWN_LIST* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_DQ2DC_SEND_TOWN_LIST(sendBuf,*pThis));
	}
	void call_sq_DQ2DC_SEND_TOWN_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_DQ2DC_SEND_TOWN_LIST param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_DQ2DC_SEND_TOWN_LIST"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	#endif //DBQueryServer_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__DBQueryServer__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(DC2DQ_USER_DISCONNECT,jS(DC2DQ_USER_DISCONNECT),0);
		phtl.Insert(DQ_ECHO,jS(DQ_ECHO),0);
		phtl.Insert(DQ_ERROR,jS(DQ_ERROR),0);
		phtl.Insert(DC2DQ_TOWN_CREATE,jS(DC2DQ_TOWN_CREATE),0);
		phtl.Insert(DQ2DC_TOWN_CREATE_OK,jS(DQ2DC_TOWN_CREATE_OK),0);
		phtl.Insert(DC2DQ_TOWN_DELETE,jS(DC2DQ_TOWN_DELETE),0);
		phtl.Insert(DQ2DC_TOWN_DELETE_OK,jS(DQ2DC_TOWN_DELETE_OK),0);
		phtl.Insert(DC2DQ_INSERT_ITEM_AND_SKILL,jS(DC2DQ_INSERT_ITEM_AND_SKILL),0);
		phtl.Insert(DQ2DC_TOWN_CREATE_ERROR,jS(DQ2DC_TOWN_CREATE_ERROR),0);
		phtl.Insert(DC2DQ_CONNECT,jS(DC2DQ_CONNECT),0);
		phtl.Insert(DQ2DC_CONNECT,jS(DQ2DC_CONNECT),0);
		phtl.Insert(DQ2DC_CONNECT_OK,jS(DQ2DC_CONNECT_OK),0);
		phtl.Insert(DC2DQ_CONNECT_OK,jS(DC2DQ_CONNECT_OK),0);
		phtl.Insert(DC2DQ_USER_LOGIN,jS(DC2DQ_USER_LOGIN),0);
		phtl.Insert(DQ2DC_USER_LOGIN_RESULT,jS(DQ2DC_USER_LOGIN_RESULT),0);
		phtl.Insert(DC2DQ_GET_TOWN_LIST,jS(DC2DQ_GET_TOWN_LIST),0);
		phtl.Insert(DQ2DC_SEND_TOWN_LIST,jS(DQ2DC_SEND_TOWN_LIST),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("DBQueryServer"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_DC2DQ_USER_DISCONNECT == DC2DQ_USER_DISCONNECT);
		jRAISE_PACKET(pk_DQ_ECHO == DQ_ECHO);
		jRAISE_PACKET(pk_DQ_ERROR == DQ_ERROR);
		jRAISE_PACKET(pk_DC2DQ_TOWN_CREATE == DC2DQ_TOWN_CREATE);
		jRAISE_PACKET(pk_DQ2DC_TOWN_CREATE_OK == DQ2DC_TOWN_CREATE_OK);
		jRAISE_PACKET(pk_DC2DQ_TOWN_DELETE == DC2DQ_TOWN_DELETE);
		jRAISE_PACKET(pk_DQ2DC_TOWN_DELETE_OK == DQ2DC_TOWN_DELETE_OK);
		jRAISE_PACKET(pk_DC2DQ_INSERT_ITEM_AND_SKILL == DC2DQ_INSERT_ITEM_AND_SKILL);
		jRAISE_PACKET(pk_DQ2DC_TOWN_CREATE_ERROR == DQ2DC_TOWN_CREATE_ERROR);
		jRAISE_PACKET(pk_DC2DQ_CONNECT == DC2DQ_CONNECT);
		jRAISE_PACKET(pk_DQ2DC_CONNECT == DQ2DC_CONNECT);
		jRAISE_PACKET(pk_DQ2DC_CONNECT_OK == DQ2DC_CONNECT_OK);
		jRAISE_PACKET(pk_DC2DQ_CONNECT_OK == DC2DQ_CONNECT_OK);
		jRAISE_PACKET(pk_DC2DQ_USER_LOGIN == DC2DQ_USER_LOGIN);
		jRAISE_PACKET(pk_DQ2DC_USER_LOGIN_RESULT == DQ2DC_USER_LOGIN_RESULT);
		jRAISE_PACKET(pk_DC2DQ_GET_TOWN_LIST == DC2DQ_GET_TOWN_LIST);
		jRAISE_PACKET(pk_DQ2DC_SEND_TOWN_LIST == DQ2DC_SEND_TOWN_LIST);

		#ifndef DBQueryServer_jNOTUSE_SQ_CODE
		jSQ_Class(S_DC2DQ_USER_DISCONNECT)
			jSQ_fn(get_pid,"int i","return player_id_t*")
			jSQ_fn(set_pid,"int i,player_id_t* data","")
			jSQ_fn(insert_pid,"player_id_t* data","")
			jSQ_fn(clear_pid,"","")
			jSQ_fn(size_pid,"","return size_t")
			jSQ_gfn(S_DC2DQ_USER_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_USER_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ_ECHO)
			jSQ_var(type,"uint8")
			jSQ_gfn(S_DQ_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_DQ_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ_ERROR)
			jSQ_var(ei,"jErrorInfo")
			jSQ_gfn(S_DQ_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_TOWN_CREATE)
			jSQ_var(pid,"player_id_t")
			jSQ_var(csid,"Sys_Castle_id_t")
			jSQ_var(tpsid,"Sys_TownPos_id_t")
			jSQ_gfn(S_DC2DQ_TOWN_CREATE,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_gfn(S_DC2DQ_TOWN_CREATE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_TOWN_CREATE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_TOWN_CREATE_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_var(channelNo,"channelid_t")
			jSQ_gfn(S_DQ2DC_TOWN_CREATE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_TOWN_CREATE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_TOWN_DELETE)
			jSQ_var(pid,"player_id_t")
			jSQ_var(index,"channelid_t")
			jSQ_gfn(S_DC2DQ_TOWN_DELETE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_TOWN_DELETE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_TOWN_DELETE_OK)
			jSQ_var(pid,"player_id_t")
			jSQ_var(channel_index,"uint8")
			jSQ_gfn(S_DQ2DC_TOWN_DELETE_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_TOWN_DELETE_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_INSERT_ITEM_AND_SKILL)
			jSQ_var(pid,"player_id_t")
			jSQ_var(channel_index,"uint8")
			jSQ_gfn(S_DC2DQ_INSERT_ITEM_AND_SKILL,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_INSERT_ITEM_AND_SKILL,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_TOWN_CREATE_ERROR)
			jSQ_var(pid,"player_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_DQ2DC_TOWN_CREATE_ERROR,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_TOWN_CREATE_ERROR,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_CONNECT)
			jSQ_gfn(S_DC2DQ_CONNECT,get_WORLD_NAME, "","return net_string")
			jSQ_fn(set_WORLD_NAME,"tcstr sz","")
			jSQ_gfn(S_DC2DQ_CONNECT,get_SM_QUERY2CACHE_NAME, "","return net_string")
			jSQ_fn(set_SM_QUERY2CACHE_NAME,"tcstr sz","")
			jSQ_gfn(S_DC2DQ_CONNECT,get_SM_CACHE2QUERY_NAME, "","return net_string")
			jSQ_fn(set_SM_CACHE2QUERY_NAME,"tcstr sz","")
			jSQ_gfn(S_DC2DQ_CONNECT,get_SM_USER_INFO_NAME, "","return net_string")
			jSQ_fn(set_SM_USER_INFO_NAME,"tcstr sz","")
			jSQ_var(processid,"uint32")
			jSQ_gfn(S_DC2DQ_CONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_CONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_CONNECT)
			jSQ_gfn(S_DQ2DC_CONNECT,get_WORLD_NAME, "","return net_string")
			jSQ_fn(set_WORLD_NAME,"tcstr sz","")
			jSQ_gfn(S_DQ2DC_CONNECT,get_SM_QUERY2CACHE_NAME, "","return net_string")
			jSQ_fn(set_SM_QUERY2CACHE_NAME,"tcstr sz","")
			jSQ_gfn(S_DQ2DC_CONNECT,get_SM_CACHE2QUERY_NAME, "","return net_string")
			jSQ_fn(set_SM_CACHE2QUERY_NAME,"tcstr sz","")
			jSQ_gfn(S_DQ2DC_CONNECT,get_SM_USER_INFO_NAME, "","return net_string")
			jSQ_fn(set_SM_USER_INFO_NAME,"tcstr sz","")
			jSQ_gfn(S_DQ2DC_CONNECT,get_GAMEDB_NAME, "","return net_string")
			jSQ_fn(set_GAMEDB_NAME,"tcstr sz","")
			jSQ_var(processid,"uint32")
			jSQ_gfn(S_DQ2DC_CONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_CONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_CONNECT_OK)
			jSQ_var(e,"jError")
			jSQ_var(processid,"uint32")
			jSQ_gfn(S_DQ2DC_CONNECT_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_CONNECT_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_CONNECT_OK)
			jSQ_var(e,"jError")
			jSQ_var(processid,"uint32")
			jSQ_gfn(S_DC2DQ_CONNECT_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_CONNECT_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_USER_LOGIN)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_DC2DQ_USER_LOGIN,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_USER_LOGIN,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_USER_LOGIN_RESULT)
			jSQ_var(pid,"player_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_DQ2DC_USER_LOGIN_RESULT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_USER_LOGIN_RESULT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DC2DQ_GET_TOWN_LIST)
			jSQ_var(pid,"player_id_t")
			jSQ_gfn(S_DC2DQ_GET_TOWN_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DC2DQ_GET_TOWN_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_DQ2DC_SEND_TOWN_LIST)
			jSQ_var(pid,"player_id_t")
			jSQ_var(e,"jError")
			jSQ_gfn(S_DQ2DC_SEND_TOWN_LIST,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_DQ2DC_SEND_TOWN_LIST,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //DBQueryServer_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__DBQueryServer__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("DBQueryServer"));
	}


}/* nDBQueryServer */ }/*nNET*/ } //nMech


#ifndef DBQueryServer_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_DBQueryServer(DBQueryServer);
jxDEFINE_DBQueryServer(DC2DQ_USER_DISCONNECT);
jxDEFINE_DBQueryServer(DQ_ECHO);
jxDEFINE_DBQueryServer(DQ_ERROR);
jxDEFINE_DBQueryServer(DC2DQ_TOWN_CREATE);
jxDEFINE_DBQueryServer(DQ2DC_TOWN_CREATE_OK);
jxDEFINE_DBQueryServer(DC2DQ_TOWN_DELETE);
jxDEFINE_DBQueryServer(DQ2DC_TOWN_DELETE_OK);
jxDEFINE_DBQueryServer(DC2DQ_INSERT_ITEM_AND_SKILL);
jxDEFINE_DBQueryServer(DQ2DC_TOWN_CREATE_ERROR);
jxDEFINE_DBQueryServer(DC2DQ_CONNECT);
jxDEFINE_DBQueryServer(DQ2DC_CONNECT);
jxDEFINE_DBQueryServer(DQ2DC_CONNECT_OK);
jxDEFINE_DBQueryServer(DC2DQ_CONNECT_OK);
jxDEFINE_DBQueryServer(DC2DQ_USER_LOGIN);
jxDEFINE_DBQueryServer(DQ2DC_USER_LOGIN_RESULT);
jxDEFINE_DBQueryServer(DC2DQ_GET_TOWN_LIST);
jxDEFINE_DBQueryServer(DQ2DC_SEND_TOWN_LIST);
#endif // DBQueryServer_jNOT_USE_PACKET_PLUGIN_HELP