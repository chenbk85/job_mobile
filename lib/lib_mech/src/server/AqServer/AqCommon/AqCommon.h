/* file : AqCommon.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-07 12:55:43
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqCommon_header__
#define __AqCommon_header__
#pragma once

#ifdef AQCOMMON_EXPORTS
#define AQ_SERVER_LIB_API __declspec(dllexport)
#else
#define AQ_SERVER_LIB_API __declspec(dllimport)
#pragma comment(lib, "AqCommon.lib")
#endif

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <process.h> 

#include "common/jCommon.h"
using namespace std;
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet.h"
#include "interface/net/jINet_Util.h"
#include "interface/net/excel_code_util.h"
#include "Interface/jIConsoleDLL.h"
#include "interface/jIConsoleCmd.h"
#include "base/jMsgManager.h"

using namespace nMech;
using namespace nMech::nNET;


#define jNET_COMMON_LIB_API AQ_SERVER_LIB_API
#define TR_SERVER_SIDE_CODE
#define aqSERVER_SIDE_LOGIG

#include "interface/net/net_common_code.h"

//--------------------------------------------------------------------------
// 서버 클라이언트 공유 시작 해더
//--------------------------------------------------------------------------
#include "../../../share/network/AqServerClient_CommonHeader.h"


#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"
#include "interface/net/jSQ_bind_jINet.h"

// 서버 클라이언트 공유 마지막 해더
//#include "AqCilentPure_End.h"



//--------------------------------------------------------------------------
// 서버간 공유 시작 해더
//--------------------------------------------------------------------------
//#include "AqServerPure_Begin.h"

#define PT_CentralServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_CentralServer jxDECL_NET
#define jxDEFINE_CentralServer jxDEFINE_NET

#define PT_UserServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_UserServer jxDECL_NET
#define jxDEFINE_UserServer jxDEFINE_NET

#define PT_WorldServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_WorldServer jxDECL_NET
#define jxDEFINE_WorldServer jxDEFINE_NET

#define PT_DBCacheServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_DBCacheServer jxDECL_NET
#define jxDEFINE_DBCacheServer jxDEFINE_NET

#define PT_TestServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_TestServer jxDECL_NET
#define jxDEFINE_TestServer jxDEFINE_NET

#define PT_LoginServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_LoginServer jxDECL_NET
#define jxDEFINE_LoginServer jxDEFINE_NET

#define PT_DBQueryServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_DBQueryServer jxDECL_NET
#define jxDEFINE_DBQueryServer jxDEFINE_NET


#ifndef jxDEFINE_NET
#define jxDEFINE_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{ \
	jNET_COMMON_LIB_API StringID x_##X= Get_jIStringTable()->RegistID(_T(#X),&x_##X);} } }
#endif

#ifndef jxDECL_NET
#define jxDECL_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{extern jNET_COMMON_LIB_API StringID x_##X;}}}
#endif

#include "jServerInfo.h"

//--------------------------------------------------------------------------
// 엑셀 csv로딩
//--------------------------------------------------------------------------
#include "db_type.h"
#include "csv_loader.h"
using namespace nTR_net;
namespace nTR_excel
{

}
using namespace nTR_excel;


// 서버 클라이언트간 공유 마지막 해더
#include "network/AqServerClient_CommonHeader_End.h"



//--------------------------------------------------------------------------
// 서버공용 자료구조들을 위한 기반 코드 지원 해더
//--------------------------------------------------------------------------
#include "network/Aq_Stream.h"

// 액셀용 사용자자료구조 지원 코드
#include "network/net_Setter.h"

// ../common_AQ/net_Struct.h에서 정의된 자료구조에 대한 디버깅 & 스커럴 선언
#include "server_ToString.h"
#include "network/net_SQ_client.h"
#include "net_SQ_Server.h"


#define jBE() PlugIn_ToBackEnd*pBE = PlugIn_ToBackEnd::Get(); if(!pBE) return;
#define jFE() PlugIn_ToFrontEnd*pFE = PlugIn_ToFrontEnd::Get(); if(!pFE) return;

#define jBE_ret(ret) PlugIn_ToBackEnd*pBE = PlugIn_ToBackEnd::Get(); if(!pBE) return ret;
#define jFE_ret(ret) PlugIn_ToFrontEnd*pFE = PlugIn_ToFrontEnd::Get(); if(!pFE) return ret;

#define jBE_A() PlugIn_ToBackEnd*pBE = PlugIn_ToBackEnd::Get(); if(!pBE) jAssert0(0 && "PlugIn_ToBackEnd* pPC = PlugIn_ToBackEnd::Get() null");
#define jFE_A() PlugIn_ToFrontEnd*pFE = PlugIn_ToFrontEnd::Get(); if(!pFE) jAssert0(0 && "PlugIn_ToFrontEnd* pPC = PlugIn_ToFrontEnd::Get() null");

#define be_READ_PACKET_P2P_P(PACKET) PlugIn_ToBackEnd*pBE = (PlugIn_ToBackEnd*)pPlugIn; READ_PACKET(PACKET);
#define be_READ_PACKET_P2P_P_Data(PACKET,Data) PlugIn_ToBackEnd*pBE = (PlugIn_ToBackEnd*)pPlugIn; READ_PACKET_Data(PACKET,Data);
#define be_READ_PACKET_P2P_PB(PACKET) nswb1024_t buf; be_READ_PACKET_P2P_P(PACKET);
#define be_READ_PACKET_P2P_PB_Data(PACKET,Data) nswb1024_t buf; be_READ_PACKET_P2P_P_Data(PACKET,Data);

#define be_READ_PACKET_P2P_PB_xml(PACKET,xml) S_##PACKET Data;Data.xml=GetjIXml()->CreateElement(); be_READ_PACKET_P2P_PB_Data(PACKET,Data)

#define jPT_MEMBER(NS,X) NS::S_##X m_##X;

#define jPLUGIN_header_code(NAME)\
	jDECLARE_RTTIOBJ(NAME);\
	JNET_PLUGIN_SINGTONE_DECL(NAME);\
	virtual void Start();\
	virtual void Stop();\
	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP);\
	virtual VOID OnIoWrote(jIPacketSocket_IOCP*pObject);\
	virtual VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);\
	virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*);\
	virtual bool ParseCmd(tcstr szCommand);\
	NAME();\
	nEVENT::jIMsgManager* m_pMM;\


#define jPLUGIN_BACK_END_header_code(NAME)\
	jPLUGIN_header_code(NAME)\
	virtual int Get_CURR_USER(){return ::Get_CURR_USER();};\


#define jPLUGIN_cpp_code_Start(NAME)\
jDEFINE_RTTIOBJ_BY_SCOPE(NAME,jNet, 1,1);\
JNET_PLUGIN_SINGTONE_DEFINE(NAME);\
VOID NAME::OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)\
{\
	jNamedEventNode* pHN = pHT->GetByNum(pk->num);\
	GetjILog()->Warning(jFUNC1 _T("%d:%s"),pk->num,pHN?pHN->m_szName:jS(NULL));\
}\
VOID NAME::OnIoWrote(jIPacketSocket_IOCP* pSocket){}\
void NAME::Start()\
{\
	NAME::Set(this);\
	GetjILog()->Log(jFUNC1 );\


#define jPLUGIN_BACK_END_cpp_code_Start(NAME)\
	jPLUGIN_cpp_code_Start(NAME);\
	m_eServers = GetjIXml()->CreateMemoryDoc(jsSERVER_NAME);\
	g_pCurrPlugInBE = this;\
	g_pjPlugIn_BE_Helper=this;\
	clear_DBCache();


#define jPLUGIN_FRONT_END_cpp_code_Start(NAME,CONNECT_TYPE)\
	int Get_CURR_USER(){jFE_ret(0);return pFE->size();}\
	int Get_MAX_USER(){	jFE_ret(0);return pFE->m_pE->GetAttrVar(jS(MaxTcpUser))->Get_int();}\
	jPLUGIN_cpp_code_Start(NAME);\
	m_pMM = nEVENT::jIMsgManager::Get(jS(NAME), true);\
	jServerUsers<CONNECT_TYPE,CONNECT_TYPE::KEY_TYPE_id_t>::start();\


#define jPLUGIN_cpp_code_Stop(NAME)\
}\
void NAME::Stop()\
{\


#define jPLUGIN_BACK_END_cpp_code_End(NAME)\
	NAME::Set(0);\
	GetjILog()->Log(jFUNC1 );\
	if(g_pCurrPlugInBE==this)g_pCurrPlugInBE=0;\
	GetjIXml()->UnLoad(m_eServers->GetDoc());\
	g_pjPlugIn_BE_Helper=0;\
}\


#define jPLUGIN_FRONT_END_cpp_code_End(NAME,CONNECT_TYPE)\
	jServerUsers<CONNECT_TYPE,CONNECT_TYPE::KEY_TYPE_id_t>::start();\
	if(m_pMM){m_pMM->clear();m_pMM=0;}\
	NAME::Set(0);\
	GetjILog()->Log(jFUNC1 );\
}\


/* 사용 코드 예.


jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqTestClientNode)
{//PlugIn_ToFrontEnd::Start
}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{//PlugIn_ToFrontEnd::Stop
}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqTestClientNode);



jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{
}
jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd)
{
}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);

*/

#define _jCONSOLE_VAL_tstring(VAL,TYPE,DEFAULT) tstring VAL= arg.size()<=e_##VAL ? (DEFAULT==0?_T(""):_T(DEFAULT)) : arg[e_##VAL];
#define _jCONSOLE_VAL_astring(VAL,TYPE,DEFAULT) astring VAL= arg.size()<=e_##VAL ? (DEFAULT==0? "":jA(DEFAULT) : jA(arg[e_##VAL]);
#define _jCONSOLE_VAL_wstring(VAL,TYPE,DEFAULT) tstring VAL= arg.size()<=e_##VAL ? (DEFAULT==0? L"":jW(DEFAULT) : jW(arg[e_##VAL]);


#define jLAMDA_vector_string_to_file(X,Z) Z(FILE*,fp)
jLAMDA_for_each(vector_string_to_file, tstring&)	{jt_fprintf(fp, _T("%s\n") , it.c_str());} jLAMDA_end();
jLAMDA_for_each0(vector_string_to_console, tstring&)	{GetjILog()->Log(_T("%s"), it.c_str());}jLAMDA_end();
jLAMDA_for_each0(vector_wstring_to_console, wstring&)	{GetjILog()->Log(_T("%s"), nUNI::scb256_t(it.c_str()).getT());}jLAMDA_end();

//	GetjILog()->Log(_T("%s : %s") , szName, nUNI::scb256_t(msg).getT());


#define 	jSORT(X) std::sort(X.begin() , X.end() );


class AQ_SERVER_LIB_API jAqCommon
{
public:
	uint32 _OnPacketSize_UsageInfo_count;
	uint64 _OnPacketSize_UsageInfo_tot;
	jAqCommon()
		:_OnPacketSize_UsageInfo_count(0)
		,_OnPacketSize_UsageInfo_tot(0)
	{

	}
	void OnPacketSize_UsageInfo(tcstr szName , uint64 packet_size);
	uint64 Get_PacketUsage();

	FILE* open_file_for_console_cmd_logging(tcstr szTag,fname_t szFileName);
	void file_open_by_notepad(tcstr szFileOutFile, bool isFileOpen);
	acstr jConvertToHostIP(aname32_t szIP);
	bool Make_FileDBPath_By_Town_DBID( IN cstr szID,IN Use_User_id_t user_db_id,OUT fname_t szFullPath);
	bool output_console_data(const tstring &outType, vector<tstring>& lists, tcstr szFileTag,bool isFileOpen);
	bool output_string_to_file_or_con( tcstr outType, tcstr file_name, tcstr file_tag, vector<tstring> &servers );
	jID* m_pDoc;// release/server/xml/AqGameSetting.xml


	jIE* jAqCommon::FindTownBYTUID(nXML::jE eUserFileDB,Use_Town_id_t tuid);
};


extern AQ_SERVER_LIB_API jAqCommon g_jAqCommon;
extern AQ_SERVER_LIB_API void init_common_AQ();
extern void _OnPacketSize_UsageInfo(tcstr szPlugIn,uint64 packet_size,tname1024_t info);
extern int Get_CURR_USER();
extern int Get_MAX_USER();
extern void jMsg_C4_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*);

inline  bool jReadLineFromFile(CHAR* buf, int buf_size, FILE* pF)
{
	if( ja_fgets( buf, buf_size-1, pF ) == NULL)
	{
		buf=NULL; return false;
	}
	size_t len = ja_strlen(buf);
	buf[len-1] = NULL; // 여기까지 file로 부터 한라인 읽어서 마지막 의 개행문자를 제거.
	return true;
}

#define var_enum_ServerCommon(var_func)\
	var_func(ServerCommon,CSV_PATH, _T("R:\\client\\server_data\\csv\\"), 0,"CSV FILE PATH")\
	var_func(ServerCommon,SERVER_RESOUCE, _T("R:\\"), 0,"SEVER RESOURCE FOLDER")\
	var_func(ServerCommon,FILE_DB_PATH, _T("R:\\file_db\\"), 0,"file db path. must add  / backend string")\
	var_func(ServerCommon,Packet_mean_reset_count , 360, 0 , "packet size mean reset time")\
	var_func(ServerCommon,XmlSaveScheduleTime, 300.f, 0 , "xml db file saving term [ sec ]")\

var_enum_ServerCommon(jCV_DECLARE);

#define jSET_CON_FLAG(category,var,value)\
	jIVar* pv_##var= nCONSOLE::Get_jIConsoleVar()->GetVar(jS(category),jS(var));\
	if(pv_##var) pv_##var->Set_bool(value);



#define for_each_User_table(X) X(Town) X(Hero) X(Force)
#define for_each_EBuildType_Impl(X) X(Sys_T_HQ) X(Sys_T_Bar) X(Sys_T_House) X(Sys_T_Farm) X(Sys_T_Barrack) X(Sys_T_Camp) X(Sys_T_Depot)



#endif // __AqCommon_header__
