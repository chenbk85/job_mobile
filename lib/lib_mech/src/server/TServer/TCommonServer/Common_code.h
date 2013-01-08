/* file : Common_code.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-15 22:31:14
comp.: t3.co.kr
title : 
desc : 

*/



#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;

#include "../TCommonClient/protocal/PT_UserServer_Enum.h"
using namespace nNET::nUserServer;

#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nNET::nWorldServer;

#include "../TCommonClient/protocal/PT_MsgServer_Enum.h"
using namespace nNET::nMsgServer;

#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nNET::nDBCacheServer;




#if 0
jCONSOLE_CMD_AUTO(jSERVER_NAME , servers,0,"print server info","<file | con> [file_tag]")
{
#define jCONSOLE_PARAM_servers(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(servers);

	jPC_ret(false);
	vector<tstring> servers;
	servers.push_back(jT(g_SG.m_eServers->Find(pv_DOMAIN_NAME->Get_cstr())->ToString()));
	g_SG.m_eServers->ToString_Free();

	if(tstring(outType)==jS(file))
	{
		fname_t szFileName;
		fname_t szOutFile;
		if(file_tag)
			js_sprintf(szOutFile, _T("world_servers_%s"), file_tag);
		else
			jt_strcpy_s(szOutFile, _T("world_servers"));

		FILE* fp = g_TCommon.open_file_for_console_cmd_logging(szOutFile,szFileName);
		if(!fp) return false;

		jFOR_EACH(servers, vector_string_to_file(fp));
		fclose(fp);

		g_TCommon.file_open_by_notepad(szFileName, !(file_tag&&jt_strlen(file_tag)) );
		return true;
	}

	if(tstring(outType)==jS(con))
	{
		jFOR_EACH(servers, vector_string_to_console());
		return true;
	}
	return false;

}
#endif

void jMsg_C4_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*)
{
	nswb16000_t buf;
	if(g_SG.m_Central.size())
	{
		static uint16 oldCnt=0;
		uint16 currCnt = ::Get_CURR_USER();
		if(oldCnt!=currCnt)
		{
			oldCnt=currCnt;
#ifdef jTSERVER_PREPARE
			g_SG.m_Central.WritePacket(WRITE_C4_USER_CONNECTION_NOTIFY(buf, currCnt));
#endif
		}
	}
	if(g_SG.m_User.size())
	{
		vector<wstring> uid_connect,uid_disconnect;
		if( g_SG.Make_U4_USER_CONNECTION_NOTIFY(uid_connect,uid_disconnect) )
		{
#ifdef jTSERVER_PREPARE
			g_SG.m_User.WritePacket(&WRITE_U4_USER_CONNECTION_NOTIFY(buf, uid_connect, uid_disconnect));
			if(g_SG.m_MyInfo.m_eType==eChannel 
				|| g_SG.m_MyInfo.m_eType==eGame)
			{
				if(uid_disconnect.size() && g_SG.m_World.size())
					g_SG.m_World.WritePacket(&nWorldServer::WRITE_W4_USER_DISCONNECT(buf, uid_disconnect));
			}
#endif

		}
	}
}
