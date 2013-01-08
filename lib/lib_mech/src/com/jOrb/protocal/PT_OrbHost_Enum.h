
//from(z:\src\com\jorb\sequence\..\protocal\pt_orb.xml)
#pragma once

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);

jxDECL_OrbHost(H_ECHO);
jxDECL_OrbHost(H_SEND_MSG);
jxDECL_OrbHost(H_SEND_LOG);
jxDECL_OrbHost(H_HELLO);
jxDECL_OrbHost(H_HELLO_OK);
jxDECL_OrbHost(ORB_IS_ALIVE);
jxDECL_OrbHost(ORB_ALIVE);
jxDECL_OrbHost(H_DISCONNECT);
jxDECL_OrbHost(H_NOTIFY_HWND);
jxDECL_OrbHost(H_NOTIFY_HWND_OK);
jxDECL_OrbHost(ORB_SEND_XML);
jxDECL_OrbHost(ORB_SEND_DATA);
jxDECL_OrbHost(H_SAVE_DOC);
jxDECL_OrbHost(H_GET_XML);
jxDECL_OrbHost(H_COPY_XML_ELEMENT);
jxDECL_OrbHost(H_DEL_XML_ELEMENT);
jxDECL_OrbHost(H_CHANGE_XML_NODE);
jxDECL_OrbHost(H_GET_UPDATE_XML_NODE);
jxDECL_OrbHost(H_PUT_XML);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nOrbHost
{
	enum EOrbHost
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000,
		H_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+1,
		/* uint8 type;*/
		/* tname256_t msg;*/
		
		H_SEND_MSG=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+2,
		/* uint8 type;*/
		/* tname256_t msg;*/
		
		H_SEND_LOG=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+3,
		/* uint8 type;*/
		/* tname256_t msg;*/
		
		H_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+4,
		/* tname32_t orbServiceName;*/
		/* tname32_t myName;*/
		/* bool isServerMode;*/
		
		H_HELLO_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+5,
		/* tname32_t orbServiceName;*/
		/* tname32_t myName;*/
		/* bool isServerMode;*/
		
		ORB_IS_ALIVE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6,
		
		ORB_ALIVE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+7,
		
		H_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+8,
		
		H_NOTIFY_HWND=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+9,
		/* uint32 hWnd;*/
		
		H_NOTIFY_HWND_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+10,
		/* uint32 hWnd;*/
		
		ORB_SEND_XML=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+11,
		/* jIE* xml;*/
		
		ORB_SEND_DATA=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+12,
		/* tname32_t name;*/
		/* BYTE data[-1];*/
		
		H_SAVE_DOC=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+13,
		/* tname256_t doc;*/
		
		H_GET_XML=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+14,
		/*[[ 해당 XML을 요청하는 메세지 ]]*/
		/* tname256_t szXml;*/
		
		H_COPY_XML_ELEMENT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+15,
		/* bool isInsertMode;*/
		/* tname256_t szDoc;*/
		/* tname1024_t szXPath;*/
		/* int8 idx;*/
		/* aname32_t szOrbFunc;*/
		/* jIE* xml;*/
		
		H_DEL_XML_ELEMENT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16,
		/* tname256_t szDoc;*/
		/* tname1024_t szXPath;*/
		/* aname32_t szOrbFunc;*/
		
		H_CHANGE_XML_NODE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+17,
		/*[[ pE의 tagname 이나 컨텐츠또는 		
pA의 컨텐츠 수정사항만 적용함 		
(자식의 내용은 적용안함) ]]*/
		/* tname256_t szDoc;*/
		/* tname1024_t szXPath;*/
		/* int8 idx;*/
		/* bool isAttr;*/
		/* tname32_t szTag;*/
		/* int32 iType;*/
		/* tname256_t szData;*/
		
		H_GET_UPDATE_XML_NODE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+18,
		/*[[ 원격지의 해당 XML노드의 값으로 새로 업데이트를 요청. 자식포함 ]]*/
		/* tname256_t szDoc;*/
		/* tname1024_t szXPath;*/
		/* int8 idx;*/
		/* bool isAttr;*/
		/* tname32_t szTag;*/
		
		H_PUT_XML=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+19,
		/* tname256_t szTempFile;*/
		/* tname256_t szXml;*/
		
		PT_OrbHost_END
	};//enum EOrbHost

	void call_sq_H_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_SEND_MSG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_SEND_LOG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_HELLO_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_ORB_IS_ALIVE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_ORB_ALIVE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_NOTIFY_HWND(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_NOTIFY_HWND_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_ORB_SEND_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_ORB_SEND_DATA(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_SAVE_DOC(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_GET_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_COPY_XML_ELEMENT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_DEL_XML_ELEMENT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_CHANGE_XML_NODE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_GET_UPDATE_XML_NODE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_H_PUT_XML(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef OrbHost_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_OrbHost_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // OrbHost_jNOT_USE_PACKET_PLUGIN_HELP


}//nOrbHost
}/* nNET*/ } //nMech

#ifndef OrbHost_jNOTUSE_PACKET_HPP_INCLUDE
#include "OrbHost/H_ECHO.hpp"
#include "OrbHost/H_SEND_MSG.hpp"
#include "OrbHost/H_SEND_LOG.hpp"
#include "OrbHost/H_HELLO.hpp"
#include "OrbHost/H_HELLO_OK.hpp"
#include "OrbHost/ORB_IS_ALIVE.hpp"
#include "OrbHost/ORB_ALIVE.hpp"
#include "OrbHost/H_DISCONNECT.hpp"
#include "OrbHost/H_NOTIFY_HWND.hpp"
#include "OrbHost/H_NOTIFY_HWND_OK.hpp"
#include "OrbHost/ORB_SEND_XML.hpp"
#include "OrbHost/ORB_SEND_DATA.hpp"
#include "OrbHost/H_SAVE_DOC.hpp"
#include "OrbHost/H_GET_XML.hpp"
#include "OrbHost/H_COPY_XML_ELEMENT.hpp"
#include "OrbHost/H_DEL_XML_ELEMENT.hpp"
#include "OrbHost/H_CHANGE_XML_NODE.hpp"
#include "OrbHost/H_GET_UPDATE_XML_NODE.hpp"
#include "OrbHost/H_PUT_XML.hpp"
#endif // OrbHost_jNOTUSE_PACKET_HPP_INCLUDE