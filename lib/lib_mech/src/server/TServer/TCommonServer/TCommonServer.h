/* file : TCommonServer.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-07 12:55:43
comp.: wiki.aqrius.com
title : 
desc : 



// 모든 server.dll에 공통적인 모듈들.
기찬더라도 모든 .cpp에 해더를 추가하자. + stdafx.h

*/

#ifndef __A34qC5o5mm46on56_h67e6ad6er__
#define __A34qC5o5mm46on56_h67e6ad6er__
#pragma once

#include "TCommonServer_header.h"

#include "Interface/jIConsoleDLL.h"
#include "interface/jIConsoleCmd.h"
#include "base/jMsgManager.h"
#include "../TCommonBase/jNetGridHelper.h"



#include "jGridNode_Server.h"
#include "jServerGrid.h"

#include "../TProtocal_back/TProtocal_back.h"
#include "../TProtocal_front/TProtocal_front.h"


class T_SERVER_LIB_API TCommonServer
{
public:
	int32 _OnPacketSize_UsageInfo_count;
	uint64 _OnPacketSize_UsageInfo_tot;
	TCommonServer()
		:_OnPacketSize_UsageInfo_count(0)
		,_OnPacketSize_UsageInfo_tot(0)
	{

	}
	void OnPacketSize_UsageInfo(tcstr szName , uint64 packet_size);
	uint64 Get_PacketUsage();

	FILE* open_file_for_console_cmd_logging(tcstr szTag,fname_t szFileName);
	void file_open_by_notepad(tcstr szFileOutFile, bool isFileOpen);
	acstr jConvertToHostIP(aname32_t szIP);
	bool Make_FileDBPath_By_Channel_DBID( IN cstr szID,IN Use_User_id_t user_db_id,OUT fname_t szFullPath);
	bool output_console_data(const tstring &outType, vector<tstring>& lists, tcstr szFileTag,bool isFileOpen);
	bool output_string_to_file_or_con( tcstr outType, tcstr file_name, tcstr file_tag, vector<tstring> &servers );
	jID* m_pDoc;// release/server/xml/TGameSetting.xml


	jIE* TCommonServer::FindChannel_by_TUID(nXML::jE eUserFileDB,Use_Town_id_t tuid);
};



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
	var_func(jSERVER_NAME,CSV_PATH, _T("\\\\50.10.250.36\\tserver_resource$\\client\\server_data\\csv\\"), 0,"CSV FILE PATH")\
	var_func(jSERVER_NAME,SERVER_RESOUCE, _T("\\\\50.10.250.36\\tserver_resource$\\"), 0,"SEVER RESOURCE FOLDER")\
	var_func(jSERVER_NAME,FILE_DB_PATH, _T("\\\\50.10.250.36\\tserver_resource$\\file_db\\"), 0,"file db path. must add  / backend string")\
	var_func(jSERVER_NAME,Packet_mean_reset_count , 360, 0 , "packet size mean reset time")\
	var_func(jSERVER_NAME,XmlSaveScheduleTime, 300.f, 0 , "xml db file saving term [ sec ]")\

var_enum_ServerCommon(jCV_DECLARE);



#define jSET_CON_FLAG(category,var,value)\
	jIVar* pv_##var= nCONSOLE::Get_jIConsoleVar()->GetVar(jS(category),jS(var));\
	if(pv_##var) pv_##var->Set_bool(value);


#define for_each_User_table(X) X(Town) X(Hero) X(Force)
#define for_each_EBuildType_Impl(X) X(Sys_T_HQ) X(Sys_T_Bar) X(Sys_T_House) X(Sys_T_Farm) X(Sys_T_Barrack) X(Sys_T_Camp) X(Sys_T_Depot)


extern T_SERVER_LIB_API jIPlugIn_Net *g_pCurrPlugIn_CmdParser;



#include "../TCommonClient/define_code_TCommonClient.h"

extern T_SERVER_LIB_API void jSocketDebugger(jIPacketSocket_IOCP* pS);
extern T_SERVER_LIB_API TCommonServer g_TCommon;
extern T_SERVER_LIB_API void _OnPacketSize_UsageInfo(tcstr szPlugIn,uint64 packet_size,tname1024_t info);
extern int Get_CURR_USER();
extern int Get_MAX_USER();
extern void jMsg_C4_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*);

extern T_SERVER_LIB_API void Init_T_SERVER_LIB_API();
extern T_SERVER_LIB_API void UnLoad_Common_CSV12();
#endif // __A34qC5o5mm46on56_h67e6ad6er__
