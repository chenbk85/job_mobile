
//from(z:\src\com\jorb\sequence\..\protocal\pt_orb.xml)

#include "stdafx.h"
#include "interface/net/jPlugInHelpTable.h"
#include "PT_OrbHost_Enum.h"


#include "network/my_PT_Orb.h"

#ifndef OrbHost_jNOTUSE_SQ_CODE
using namespace nMech::nNET::nOrbHost;
DECLARE_INSTANCE_TYPE(S_H_ECHO);
DECLARE_INSTANCE_TYPE(S_H_SEND_MSG);
DECLARE_INSTANCE_TYPE(S_H_SEND_LOG);
DECLARE_INSTANCE_TYPE(S_H_HELLO);
DECLARE_INSTANCE_TYPE(S_H_HELLO_OK);
DECLARE_INSTANCE_TYPE(S_ORB_IS_ALIVE);
DECLARE_INSTANCE_TYPE(S_ORB_ALIVE);
DECLARE_INSTANCE_TYPE(S_H_DISCONNECT);
DECLARE_INSTANCE_TYPE(S_H_NOTIFY_HWND);
DECLARE_INSTANCE_TYPE(S_H_NOTIFY_HWND_OK);
DECLARE_INSTANCE_TYPE(S_ORB_SEND_XML);
DECLARE_INSTANCE_TYPE(S_ORB_SEND_DATA);
DECLARE_INSTANCE_TYPE(S_H_SAVE_DOC);
DECLARE_INSTANCE_TYPE(S_H_GET_XML);
DECLARE_INSTANCE_TYPE(S_H_COPY_XML_ELEMENT);
DECLARE_INSTANCE_TYPE(S_H_DEL_XML_ELEMENT);
DECLARE_INSTANCE_TYPE(S_H_CHANGE_XML_NODE);
DECLARE_INSTANCE_TYPE(S_H_GET_UPDATE_XML_NODE);
DECLARE_INSTANCE_TYPE(S_H_PUT_XML);
#endif // OrbHost_jNOTUSE_SQ_CODE

namespace nMech{ namespace nNET	{ namespace nOrbHost
{
	PT_OrbHost_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;

	#ifndef OrbHost_jNOTUSE_SQ_CODE
	static void _S_H_ECHO_WritePacket(S_H_ECHO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_ECHO(sendBuf,*pThis));
	}
	static void _S_H_ECHO_WriteToPacket(S_H_ECHO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_ECHO(sendBuf,*pThis));
	}
	void call_sq_H_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_ECHO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_ECHO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_ECHO , get_msg)(S_H_ECHO* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_H_SEND_MSG_WritePacket(S_H_SEND_MSG* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_SEND_MSG(sendBuf,*pThis));
	}
	static void _S_H_SEND_MSG_WriteToPacket(S_H_SEND_MSG* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_SEND_MSG(sendBuf,*pThis));
	}
	void call_sq_H_SEND_MSG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_SEND_MSG param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_SEND_MSG"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_SEND_MSG , get_msg)(S_H_SEND_MSG* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_H_SEND_LOG_WritePacket(S_H_SEND_LOG* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_SEND_LOG(sendBuf,*pThis));
	}
	static void _S_H_SEND_LOG_WriteToPacket(S_H_SEND_LOG* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_SEND_LOG(sendBuf,*pThis));
	}
	void call_sq_H_SEND_LOG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_SEND_LOG param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_SEND_LOG"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_SEND_LOG , get_msg)(S_H_SEND_LOG* pThis)
	{
		fname_t buf;return (pThis->get_msg(buf));
	}

	static void _S_H_HELLO_WritePacket(S_H_HELLO* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_HELLO(sendBuf,*pThis));
	}
	static void _S_H_HELLO_WriteToPacket(S_H_HELLO* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_HELLO(sendBuf,*pThis));
	}
	void call_sq_H_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_HELLO param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_HELLO"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_HELLO , get_orbServiceName)(S_H_HELLO* pThis)
	{
		fname_t buf;return (pThis->get_orbServiceName(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_HELLO , get_myName)(S_H_HELLO* pThis)
	{
		fname_t buf;return (pThis->get_myName(buf));
	}

	static void _S_H_HELLO_OK_WritePacket(S_H_HELLO_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_HELLO_OK(sendBuf,*pThis));
	}
	static void _S_H_HELLO_OK_WriteToPacket(S_H_HELLO_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_HELLO_OK(sendBuf,*pThis));
	}
	void call_sq_H_HELLO_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_HELLO_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_HELLO_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_HELLO_OK , get_orbServiceName)(S_H_HELLO_OK* pThis)
	{
		fname_t buf;return (pThis->get_orbServiceName(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_HELLO_OK , get_myName)(S_H_HELLO_OK* pThis)
	{
		fname_t buf;return (pThis->get_myName(buf));
	}

	static void _S_ORB_IS_ALIVE_WritePacket(S_ORB_IS_ALIVE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_ORB_IS_ALIVE(sendBuf,*pThis));
	}
	static void _S_ORB_IS_ALIVE_WriteToPacket(S_ORB_IS_ALIVE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_ORB_IS_ALIVE(sendBuf,*pThis));
	}
	void call_sq_ORB_IS_ALIVE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_ORB_IS_ALIVE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_ORB_IS_ALIVE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_ORB_ALIVE_WritePacket(S_ORB_ALIVE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_ORB_ALIVE(sendBuf,*pThis));
	}
	static void _S_ORB_ALIVE_WriteToPacket(S_ORB_ALIVE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_ORB_ALIVE(sendBuf,*pThis));
	}
	void call_sq_ORB_ALIVE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_ORB_ALIVE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_ORB_ALIVE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_H_DISCONNECT_WritePacket(S_H_DISCONNECT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_DISCONNECT(sendBuf,*pThis));
	}
	static void _S_H_DISCONNECT_WriteToPacket(S_H_DISCONNECT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_DISCONNECT(sendBuf,*pThis));
	}
	void call_sq_H_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_DISCONNECT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_DISCONNECT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_H_NOTIFY_HWND_WritePacket(S_H_NOTIFY_HWND* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_NOTIFY_HWND(sendBuf,*pThis));
	}
	static void _S_H_NOTIFY_HWND_WriteToPacket(S_H_NOTIFY_HWND* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_NOTIFY_HWND(sendBuf,*pThis));
	}
	void call_sq_H_NOTIFY_HWND(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_NOTIFY_HWND param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_NOTIFY_HWND"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_H_NOTIFY_HWND_OK_WritePacket(S_H_NOTIFY_HWND_OK* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_NOTIFY_HWND_OK(sendBuf,*pThis));
	}
	static void _S_H_NOTIFY_HWND_OK_WriteToPacket(S_H_NOTIFY_HWND_OK* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_NOTIFY_HWND_OK(sendBuf,*pThis));
	}
	void call_sq_H_NOTIFY_HWND_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_NOTIFY_HWND_OK param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_NOTIFY_HWND_OK"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_ORB_SEND_XML_WritePacket(S_ORB_SEND_XML* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_ORB_SEND_XML(sendBuf,*pThis));
	}
	static void _S_ORB_SEND_XML_WriteToPacket(S_ORB_SEND_XML* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_ORB_SEND_XML(sendBuf,*pThis));
	}
	void call_sq_ORB_SEND_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_ORB_SEND_XML param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_ORB_SEND_XML"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}

	static void _S_ORB_SEND_DATA_WritePacket(S_ORB_SEND_DATA* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_ORB_SEND_DATA(sendBuf,*pThis));
	}
	static void _S_ORB_SEND_DATA_WriteToPacket(S_ORB_SEND_DATA* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_ORB_SEND_DATA(sendBuf,*pThis));
	}
	void call_sq_ORB_SEND_DATA(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_ORB_SEND_DATA param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_ORB_SEND_DATA"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_ORB_SEND_DATA , get_name)(S_ORB_SEND_DATA* pThis)
	{
		fname_t buf;return (pThis->get_name(buf));
	}

	static void _S_H_SAVE_DOC_WritePacket(S_H_SAVE_DOC* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_SAVE_DOC(sendBuf,*pThis));
	}
	static void _S_H_SAVE_DOC_WriteToPacket(S_H_SAVE_DOC* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_SAVE_DOC(sendBuf,*pThis));
	}
	void call_sq_H_SAVE_DOC(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_SAVE_DOC param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_SAVE_DOC"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_SAVE_DOC , get_doc)(S_H_SAVE_DOC* pThis)
	{
		fname_t buf;return (pThis->get_doc(buf));
	}

	static void _S_H_GET_XML_WritePacket(S_H_GET_XML* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_GET_XML(sendBuf,*pThis));
	}
	static void _S_H_GET_XML_WriteToPacket(S_H_GET_XML* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_GET_XML(sendBuf,*pThis));
	}
	void call_sq_H_GET_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_GET_XML param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_GET_XML"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_GET_XML , get_szXml)(S_H_GET_XML* pThis)
	{
		fname_t buf;return (pThis->get_szXml(buf));
	}

	static void _S_H_COPY_XML_ELEMENT_WritePacket(S_H_COPY_XML_ELEMENT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_COPY_XML_ELEMENT(sendBuf,*pThis));
	}
	static void _S_H_COPY_XML_ELEMENT_WriteToPacket(S_H_COPY_XML_ELEMENT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_COPY_XML_ELEMENT(sendBuf,*pThis));
	}
	void call_sq_H_COPY_XML_ELEMENT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_COPY_XML_ELEMENT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_COPY_XML_ELEMENT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_COPY_XML_ELEMENT , get_szDoc)(S_H_COPY_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szDoc(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_COPY_XML_ELEMENT , get_szXPath)(S_H_COPY_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szXPath(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_COPY_XML_ELEMENT , get_szOrbFunc)(S_H_COPY_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szOrbFunc(buf));
	}

	static void _S_H_DEL_XML_ELEMENT_WritePacket(S_H_DEL_XML_ELEMENT* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_DEL_XML_ELEMENT(sendBuf,*pThis));
	}
	static void _S_H_DEL_XML_ELEMENT_WriteToPacket(S_H_DEL_XML_ELEMENT* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_DEL_XML_ELEMENT(sendBuf,*pThis));
	}
	void call_sq_H_DEL_XML_ELEMENT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_DEL_XML_ELEMENT param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_DEL_XML_ELEMENT"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_DEL_XML_ELEMENT , get_szDoc)(S_H_DEL_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szDoc(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_DEL_XML_ELEMENT , get_szXPath)(S_H_DEL_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szXPath(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_DEL_XML_ELEMENT , get_szOrbFunc)(S_H_DEL_XML_ELEMENT* pThis)
	{
		fname_t buf;return (pThis->get_szOrbFunc(buf));
	}

	static void _S_H_CHANGE_XML_NODE_WritePacket(S_H_CHANGE_XML_NODE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_CHANGE_XML_NODE(sendBuf,*pThis));
	}
	static void _S_H_CHANGE_XML_NODE_WriteToPacket(S_H_CHANGE_XML_NODE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_CHANGE_XML_NODE(sendBuf,*pThis));
	}
	void call_sq_H_CHANGE_XML_NODE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_CHANGE_XML_NODE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_CHANGE_XML_NODE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_CHANGE_XML_NODE , get_szDoc)(S_H_CHANGE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szDoc(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_CHANGE_XML_NODE , get_szXPath)(S_H_CHANGE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szXPath(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_CHANGE_XML_NODE , get_szTag)(S_H_CHANGE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szTag(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_CHANGE_XML_NODE , get_szData)(S_H_CHANGE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szData(buf));
	}

	static void _S_H_GET_UPDATE_XML_NODE_WritePacket(S_H_GET_UPDATE_XML_NODE* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_GET_UPDATE_XML_NODE(sendBuf,*pThis));
	}
	static void _S_H_GET_UPDATE_XML_NODE_WriteToPacket(S_H_GET_UPDATE_XML_NODE* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_GET_UPDATE_XML_NODE(sendBuf,*pThis));
	}
	void call_sq_H_GET_UPDATE_XML_NODE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_GET_UPDATE_XML_NODE param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_GET_UPDATE_XML_NODE"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_GET_UPDATE_XML_NODE , get_szDoc)(S_H_GET_UPDATE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szDoc(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_GET_UPDATE_XML_NODE , get_szXPath)(S_H_GET_UPDATE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szXPath(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_GET_UPDATE_XML_NODE , get_szTag)(S_H_GET_UPDATE_XML_NODE* pThis)
	{
		fname_t buf;return (pThis->get_szTag(buf));
	}

	static void _S_H_PUT_XML_WritePacket(S_H_PUT_XML* pThis, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t sendBuf; pS->WritePacket(&WRITE_H_PUT_XML(sendBuf,*pThis));
	}
	static void _S_H_PUT_XML_WriteToPacket(S_H_PUT_XML* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)
	{
		nswb1024_t sendBuf; pS->WriteToPacket(pIP,&WRITE_H_PUT_XML(sendBuf,*pThis));
	}
	void call_sq_H_PUT_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)
	{
		SquirrelObject* pO = (SquirrelObject*)v;
		S_H_PUT_XML param;
		SquirrelFunction<void> func(*pO,_T("jNET_EVENT_H_PUT_XML"));
		if(!func.func.IsNull()) func(pS,pk,pIP,&param);
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_PUT_XML , get_szTempFile)(S_H_PUT_XML* pThis)
	{
		fname_t buf;return (pThis->get_szTempFile(buf));
	}
	jSQ_gfn_DEF2(SquirrelObject, S_H_PUT_XML , get_szXml)(S_H_PUT_XML* pThis)
	{
		fname_t buf;return (pThis->get_szXml(buf));
	}

	#endif //OrbHost_jNOTUSE_SQ_CODE

	jONCE_RUN_CTOR(__OrbHost__)
	{
		static jNamedEventTable_impl phtl;
		phtl.Insert(H_ECHO,jS(H_ECHO),0);
		phtl.Insert(H_SEND_MSG,jS(H_SEND_MSG),0);
		phtl.Insert(H_SEND_LOG,jS(H_SEND_LOG),0);
		phtl.Insert(H_HELLO,jS(H_HELLO),0);
		phtl.Insert(H_HELLO_OK,jS(H_HELLO_OK),0);
		phtl.Insert(ORB_IS_ALIVE,jS(ORB_IS_ALIVE),0);
		phtl.Insert(ORB_ALIVE,jS(ORB_ALIVE),0);
		phtl.Insert(H_DISCONNECT,jS(H_DISCONNECT),0);
		phtl.Insert(H_NOTIFY_HWND,jS(H_NOTIFY_HWND),0);
		phtl.Insert(H_NOTIFY_HWND_OK,jS(H_NOTIFY_HWND_OK),0);
		phtl.Insert(ORB_SEND_XML,jS(ORB_SEND_XML),0);
		phtl.Insert(ORB_SEND_DATA,jS(ORB_SEND_DATA),0);
		phtl.Insert(H_SAVE_DOC,jS(H_SAVE_DOC),0);
		phtl.Insert(H_GET_XML,jS(H_GET_XML),0);
		phtl.Insert(H_COPY_XML_ELEMENT,jS(H_COPY_XML_ELEMENT),0);
		phtl.Insert(H_DEL_XML_ELEMENT,jS(H_DEL_XML_ELEMENT),0);
		phtl.Insert(H_CHANGE_XML_NODE,jS(H_CHANGE_XML_NODE),0);
		phtl.Insert(H_GET_UPDATE_XML_NODE,jS(H_GET_UPDATE_XML_NODE),0);
		phtl.Insert(H_PUT_XML,jS(H_PUT_XML),0);

		g_pPlugInHelpTableList = &phtl;
		nMech::jBase::RegistNamedPointer(_T("nNET"),_T("OrbHost"),g_pPlugInHelpTableList);
		jRAISE_PACKET(pk_H_ECHO == H_ECHO);
		jRAISE_PACKET(pk_H_SEND_MSG == H_SEND_MSG);
		jRAISE_PACKET(pk_H_SEND_LOG == H_SEND_LOG);
		jRAISE_PACKET(pk_H_HELLO == H_HELLO);
		jRAISE_PACKET(pk_H_HELLO_OK == H_HELLO_OK);
		jRAISE_PACKET(pk_ORB_IS_ALIVE == ORB_IS_ALIVE);
		jRAISE_PACKET(pk_ORB_ALIVE == ORB_ALIVE);
		jRAISE_PACKET(pk_H_DISCONNECT == H_DISCONNECT);
		jRAISE_PACKET(pk_H_NOTIFY_HWND == H_NOTIFY_HWND);
		jRAISE_PACKET(pk_H_NOTIFY_HWND_OK == H_NOTIFY_HWND_OK);
		jRAISE_PACKET(pk_ORB_SEND_XML == ORB_SEND_XML);
		jRAISE_PACKET(pk_ORB_SEND_DATA == ORB_SEND_DATA);
		jRAISE_PACKET(pk_H_SAVE_DOC == H_SAVE_DOC);
		jRAISE_PACKET(pk_H_GET_XML == H_GET_XML);
		jRAISE_PACKET(pk_H_COPY_XML_ELEMENT == H_COPY_XML_ELEMENT);
		jRAISE_PACKET(pk_H_DEL_XML_ELEMENT == H_DEL_XML_ELEMENT);
		jRAISE_PACKET(pk_H_CHANGE_XML_NODE == H_CHANGE_XML_NODE);
		jRAISE_PACKET(pk_H_GET_UPDATE_XML_NODE == H_GET_UPDATE_XML_NODE);
		jRAISE_PACKET(pk_H_PUT_XML == H_PUT_XML);

		#ifndef OrbHost_jNOTUSE_SQ_CODE
		jSQ_Class(S_H_ECHO)
			jSQ_var(type,"uint8")
			jSQ_gfn(S_H_ECHO,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_H_ECHO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_ECHO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_SEND_MSG)
			jSQ_var(type,"uint8")
			jSQ_gfn(S_H_SEND_MSG,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_H_SEND_MSG,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_SEND_MSG,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_SEND_LOG)
			jSQ_var(type,"uint8")
			jSQ_gfn(S_H_SEND_LOG,get_msg, "","return net_string")
			jSQ_fn(set_msg,"tcstr sz","")
			jSQ_gfn(S_H_SEND_LOG,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_SEND_LOG,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_HELLO)
			jSQ_gfn(S_H_HELLO,get_orbServiceName, "","return net_string")
			jSQ_fn(set_orbServiceName,"tcstr sz","")
			jSQ_gfn(S_H_HELLO,get_myName, "","return net_string")
			jSQ_fn(set_myName,"tcstr sz","")
			jSQ_var(isServerMode,"bool")
			jSQ_gfn(S_H_HELLO,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_HELLO,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_HELLO_OK)
			jSQ_gfn(S_H_HELLO_OK,get_orbServiceName, "","return net_string")
			jSQ_fn(set_orbServiceName,"tcstr sz","")
			jSQ_gfn(S_H_HELLO_OK,get_myName, "","return net_string")
			jSQ_fn(set_myName,"tcstr sz","")
			jSQ_var(isServerMode,"bool")
			jSQ_gfn(S_H_HELLO_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_HELLO_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_ORB_IS_ALIVE)
			jSQ_gfn(S_ORB_IS_ALIVE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_ORB_IS_ALIVE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_ORB_ALIVE)
			jSQ_gfn(S_ORB_ALIVE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_ORB_ALIVE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_DISCONNECT)
			jSQ_gfn(S_H_DISCONNECT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_DISCONNECT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_NOTIFY_HWND)
			jSQ_var(hWnd,"uint32")
			jSQ_gfn(S_H_NOTIFY_HWND,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_NOTIFY_HWND,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_NOTIFY_HWND_OK)
			jSQ_var(hWnd,"uint32")
			jSQ_gfn(S_H_NOTIFY_HWND_OK,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_NOTIFY_HWND_OK,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_ORB_SEND_XML)
			jSQ_var(xml,"jIE*")
			jSQ_gfn(S_ORB_SEND_XML,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_ORB_SEND_XML,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_ORB_SEND_DATA)
			jSQ_gfn(S_ORB_SEND_DATA,get_name, "","return net_string")
			jSQ_fn(set_name,"tcstr sz","")
			jSQ_fn(get_data,"int i","return BYTE*")
			jSQ_fn(set_data,"int i,BYTE* data","")
			jSQ_fn(insert_data,"BYTE* data","")
			jSQ_fn(clear_data,"","")
			jSQ_fn(size_data,"","return size_t")
			jSQ_gfn(S_ORB_SEND_DATA,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_ORB_SEND_DATA,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_SAVE_DOC)
			jSQ_gfn(S_H_SAVE_DOC,get_doc, "","return net_string")
			jSQ_fn(set_doc,"tcstr sz","")
			jSQ_gfn(S_H_SAVE_DOC,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_SAVE_DOC,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_GET_XML)
			jSQ_gfn(S_H_GET_XML,get_szXml, "","return net_string")
			jSQ_fn(set_szXml,"tcstr sz","")
			jSQ_gfn(S_H_GET_XML,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_GET_XML,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_COPY_XML_ELEMENT)
			jSQ_var(isInsertMode,"bool")
			jSQ_gfn(S_H_COPY_XML_ELEMENT,get_szDoc, "","return net_string")
			jSQ_fn(set_szDoc,"tcstr sz","")
			jSQ_gfn(S_H_COPY_XML_ELEMENT,get_szXPath, "","return net_string")
			jSQ_fn(set_szXPath,"tcstr sz","")
			jSQ_var(idx,"int8")
			jSQ_gfn(S_H_COPY_XML_ELEMENT,get_szOrbFunc, "","return net_string")
			jSQ_fn(set_szOrbFunc,"tcstr sz","")
			jSQ_var(xml,"jIE*")
			jSQ_gfn(S_H_COPY_XML_ELEMENT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_COPY_XML_ELEMENT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_DEL_XML_ELEMENT)
			jSQ_gfn(S_H_DEL_XML_ELEMENT,get_szDoc, "","return net_string")
			jSQ_fn(set_szDoc,"tcstr sz","")
			jSQ_gfn(S_H_DEL_XML_ELEMENT,get_szXPath, "","return net_string")
			jSQ_fn(set_szXPath,"tcstr sz","")
			jSQ_gfn(S_H_DEL_XML_ELEMENT,get_szOrbFunc, "","return net_string")
			jSQ_fn(set_szOrbFunc,"tcstr sz","")
			jSQ_gfn(S_H_DEL_XML_ELEMENT,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_DEL_XML_ELEMENT,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_CHANGE_XML_NODE)
			jSQ_gfn(S_H_CHANGE_XML_NODE,get_szDoc, "","return net_string")
			jSQ_fn(set_szDoc,"tcstr sz","")
			jSQ_gfn(S_H_CHANGE_XML_NODE,get_szXPath, "","return net_string")
			jSQ_fn(set_szXPath,"tcstr sz","")
			jSQ_var(idx,"int8")
			jSQ_var(isAttr,"bool")
			jSQ_gfn(S_H_CHANGE_XML_NODE,get_szTag, "","return net_string")
			jSQ_fn(set_szTag,"tcstr sz","")
			jSQ_var(iType,"int32")
			jSQ_gfn(S_H_CHANGE_XML_NODE,get_szData, "","return net_string")
			jSQ_fn(set_szData,"tcstr sz","")
			jSQ_gfn(S_H_CHANGE_XML_NODE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_CHANGE_XML_NODE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_GET_UPDATE_XML_NODE)
			jSQ_gfn(S_H_GET_UPDATE_XML_NODE,get_szDoc, "","return net_string")
			jSQ_fn(set_szDoc,"tcstr sz","")
			jSQ_gfn(S_H_GET_UPDATE_XML_NODE,get_szXPath, "","return net_string")
			jSQ_fn(set_szXPath,"tcstr sz","")
			jSQ_var(idx,"int8")
			jSQ_var(isAttr,"bool")
			jSQ_gfn(S_H_GET_UPDATE_XML_NODE,get_szTag, "","return net_string")
			jSQ_fn(set_szTag,"tcstr sz","")
			jSQ_gfn(S_H_GET_UPDATE_XML_NODE,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_GET_UPDATE_XML_NODE,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		jSQ_Class(S_H_PUT_XML)
			jSQ_gfn(S_H_PUT_XML,get_szTempFile, "","return net_string")
			jSQ_fn(set_szTempFile,"tcstr sz","")
			jSQ_gfn(S_H_PUT_XML,get_szXml, "","return net_string")
			jSQ_fn(set_szXml,"tcstr sz","")
			jSQ_gfn(S_H_PUT_XML,WritePacket,"jIPacketSocket_IOCP* pS","")
			jSQ_gfn(S_H_PUT_XML,WriteToPacket,"jIPacketSocket_IOCP* pS,jIP_Address *pIP","")
			jSQ_fn(ReadPacket,"jIPacketSocket_IOCP* pS,jPacket_Base* pk","")
			jSQ_fn(DebugPrint,"bool isPrintAll","")
		jSQ_end();

		#endif //OrbHost_jNOTUSE_SQ_CODE

	}
	jONCE_RUN_DTOR(__OrbHost__)
	{
	nMech::jBase::UnRegistNamedPointer(_T("nNET"),_T("OrbHost"));
	}


}/* nOrbHost */ }/*nNET*/ } //nMech


#ifndef OrbHost_jNOT_USE_PACKET_PLUGIN_HELP
jxDEFINE_OrbHost(OrbHost);
jxDEFINE_OrbHost(H_ECHO);
jxDEFINE_OrbHost(H_SEND_MSG);
jxDEFINE_OrbHost(H_SEND_LOG);
jxDEFINE_OrbHost(H_HELLO);
jxDEFINE_OrbHost(H_HELLO_OK);
jxDEFINE_OrbHost(ORB_IS_ALIVE);
jxDEFINE_OrbHost(ORB_ALIVE);
jxDEFINE_OrbHost(H_DISCONNECT);
jxDEFINE_OrbHost(H_NOTIFY_HWND);
jxDEFINE_OrbHost(H_NOTIFY_HWND_OK);
jxDEFINE_OrbHost(ORB_SEND_XML);
jxDEFINE_OrbHost(ORB_SEND_DATA);
jxDEFINE_OrbHost(H_SAVE_DOC);
jxDEFINE_OrbHost(H_GET_XML);
jxDEFINE_OrbHost(H_COPY_XML_ELEMENT);
jxDEFINE_OrbHost(H_DEL_XML_ELEMENT);
jxDEFINE_OrbHost(H_CHANGE_XML_NODE);
jxDEFINE_OrbHost(H_GET_UPDATE_XML_NODE);
jxDEFINE_OrbHost(H_PUT_XML);
#endif // OrbHost_jNOT_USE_PACKET_PLUGIN_HELP