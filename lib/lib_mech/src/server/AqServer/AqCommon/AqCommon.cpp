// AqCommon.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "AqCommon.h"
#include "base/jFileDebugger.h"
#include "net_StringID.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

AQ_SERVER_LIB_API jAqCommon g_jAqCommon;
#if 0
tcstr ToString(userid_t &uid,fname_t buf)
{
	jt_sprintf(buf, _T("[%d:%d]"), uid.m_dc_sid,uid.m_dc_handle);
	return buf;
}
#endif

bool jAqCommon::output_string_to_file_or_con( tcstr outType, tcstr file_name, tcstr file_tag, vector<tstring> &servers )
{
	if(tstring(outType)==jS(file))
	{
		fname_t szFileName;
		fname_t szOutFile;
		if(file_tag)
			jt_sprintf(szOutFile, _T("%s_%s"), file_name,file_tag);
		else
			jt_strcpy(szOutFile, file_name);

		FILE* fp = g_jAqCommon.open_file_for_console_cmd_logging(szOutFile,szFileName);
		if(!fp) return false;
		try{
			jt_fprintf(fp , _T("size = %d\n"),servers.size());
			jFOR_EACH(servers, vector_string_to_file(fp));
		}
		catch(...){}
		if(fp)
			fclose(fp);

		g_jAqCommon.file_open_by_notepad(szFileName, !(file_tag&&jt_strlen(file_tag)) );
		return true;
	}
	if(tstring(outType)==jS(con))
	{
		//GetjILog()->Log(_T("Get_PacketUsage : %I64d") , g_jAqCommon.Get_PacketUsage() );
		jFOR_EACH(servers, vector_string_to_console());
		GetjILog()->Log(_T("size = %d"),servers.size());
		return true;
	}
	return false;
}

bool jAqCommon::output_console_data(const tstring &outType, vector<tstring>& lists, tcstr szFileTag,bool isFileOpen)
{
	if(outType==jS(file))
	{
		fname_t szFileName;
		fname_t szOutFile;
		jt_strcpy(szOutFile, szFileTag);

		FILE* fp = g_jAqCommon.open_file_for_console_cmd_logging(szOutFile,szFileName);
		if(!fp) return false;

		jFOR_EACH(lists, vector_string_to_file(fp));
		fclose(fp);
		g_jAqCommon.file_open_by_notepad(szFileName, isFileOpen );
		return true;
	}
	else if(outType==jS(con))
	{
		jFOR_EACH(lists, vector_string_to_console());
		return true;
	}
	return false;
}

nMech::nDebug::jFileDebugger g_PacketDebugger(tstring(tstring(nInterface::g_pjILog->GetFileName()) + tstring(_T("_PacketInfo"))).c_str() );
void jAqCommon::OnPacketSize_UsageInfo(tcstr szName , uint64 packet_size)
{
	if(_OnPacketSize_UsageInfo_count>pv_Packet_mean_reset_count->Get_int())
	{
		_OnPacketSize_UsageInfo_count=0;
		_OnPacketSize_UsageInfo_tot=0;
	}
	++_OnPacketSize_UsageInfo_count;
	_OnPacketSize_UsageInfo_tot+=packet_size;
	g_PacketDebugger.WriteWithTime(_T("%I64d ,mean= %I64d"),packet_size, Get_PacketUsage() );


}

uint64 jAqCommon::Get_PacketUsage()
{
	if(!_OnPacketSize_UsageInfo_count) return 0;
	static jIVar* pv_OnPacketSize_UsageInfo_TIME = nCONSOLE::Get_jIConsoleVar()->GetVar(jS(jINet_OGS) , jS(OnPacketSize_UsageInfo_TIME));
	return (_OnPacketSize_UsageInfo_tot / _OnPacketSize_UsageInfo_count / pv_OnPacketSize_UsageInfo_TIME->Get_int());
}

AQ_SERVER_LIB_API void init_common_AQ()
{
	static int iFirstRun=false;
	if(iFirstRun==true) return;
	iFirstRun = true;
	fname_t szBuf;
	jt_sprintf(szBuf , _T("%sserver\\xml\\AqGameSetting.xml"),pv_SERVER_RESOUCE->Get_cstr());
	g_jAqCommon.m_pDoc= GetjIXml()->Load(szBuf);
	if(!g_jAqCommon.m_pDoc)
	{
		GetjILog()->Error(_T("load xml fail : %s"),szBuf);
	}
	jIVar* pv_OnPacketSize_UsageInfo_TIME = jGV(jINet_OGS,OnPacketSize_UsageInfo_TIME);
	g_PacketDebugger.Write(_T("OnPacketSize_UsageInfo_TIME(sec)= %f"), pv_OnPacketSize_UsageInfo_TIME->Get_float());
	g_PacketDebugger.Write(_T("Packet_mean_reset_count = %d\n"), pv_Packet_mean_reset_count->Get_int());
}

namespace nMech
{
#ifndef jError_USING_DEV_MODE
	jError::server_tcstr jError::ToStringS()
	{
		jEnumString* pErr = StringID_ServerResult::Get(iServer);
		if(pErr)
			return pErr->m_szName;

		return _T("");
	}

	jError::client_tcstr jError::ToStringC()
	{
		jEnumString* pErr = StringID_ClientResult::Get(iClient);
		if(pErr)
			return pErr->m_szName;

		return _T("");
	}

	std::pair<jError::server_tcstr ,jError::client_tcstr> jError::ToString(fname_t buf)
	{
		tcstr s=_T("?"),c=_T("?");
		jEnumString* pErr = StringID_ServerResult::Get(iServer);
		if(pErr)
			s=pErr->m_szName;

		pErr = StringID_ClientResult::Get(iClient);
		if(pErr)
			c=pErr->m_szName;

		if(buf)
		{
			const int tot = sizeof(fname_t)/sizeof(TCHAR)-1;
			jt_snprintf(buf, tot, _T("%s : %s"),s,c);
			buf[tot] =0;
		}
		return std::make_pair(s,c);
	}
#endif

}

acstr jAqCommon::jConvertToHostIP(aname32_t szIP)
{
	if(!ja_strcmp(szIP , "PRIVATE_IP") )
		return g_pjINet_OGS->GetUtil()->GetPrivateIP(szIP);
	else if(ja_strcmp(szIP,"PUBLIC_IP") )
		return g_pjINet_OGS->GetUtil()->GetPublicIP(szIP);
	return szIP;
}

FILE* jAqCommon::open_file_for_console_cmd_logging(tcstr szTag,fname_t szFileName)
{
	SYSTEMTIME	SystemTime;
	GetLocalTime(&SystemTime);
	fname_t szRunStartTime;
	_sntprintf(szRunStartTime, 32, _T("[%d-%d-%d]%d_%d_%d"),
		SystemTime.wYear, 
		SystemTime.wMonth, 
		SystemTime.wDay,
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond);

	nFileSystem::jFolder dir;
	jt_sprintf(szFileName,_T("%stemp\\%s_%s.txt"),g_ExeEnv.m_szStartDir, szTag, szRunStartTime );
	//jt_sprintf(szFileName,_T("c:\\user_list_%s.txt"),g_ExeEnv.m_szStartDir, szRunStartTime );
	FILE* fp = jt_fopen(szFileName,_T("wt"));
	if(!fp) 
	{
		GetjILog()->Warning(_T("%s : create file failed  : %s"),__FUNCTION__ , szFileName);
		return 0;
	}
	jt_fprintf(fp,_T("%s\n"),szRunStartTime);
	return fp;
}

void jAqCommon::file_open_by_notepad(tcstr szFileOutFile, bool isFileOpen)
{
	if(!isFileOpen) return;
	afname_t exeBuf;
	ja_sprintf( exeBuf , "notepad %s", jA(szFileOutFile));
	WinExec(exeBuf, SW_SHOW);
}



// db_id sample :3) 565 007 511 192 029
//				 2) 56 50 07 51 11 92 02 9

bool jAqCommon::Make_FileDBPath_By_Town_DBID( IN cstr szID,IN Use_User_id_t user_db_id,OUT fname_t szFullPath)
{
	memset(szFullPath,0,sizeof(szFullPath));

	PathAppend( szFullPath, pv_FILE_DB_PATH->Get_cstr() );
	PathAppend( szFullPath, _T("users"));
	tname32_t szUID;
	jt_sprintf( szUID, _T("%I64d"), user_db_id.m_db_id );
	int len = jt_strlen(szUID);

	TCHAR* ch = szFullPath + jt_strlen(szFullPath);
	for( int i=1; i <= len  ; ++i ,++ch)
	{
		if(i%3 ==0)
		{
			*ch= '\\';
			++ch;
		}
		if((len-i) <=3) // 마지막 3자리는 안만든다. 대신 szID라는 파일명으로 구분될것이다.
			break;

		*ch = szUID[i-1];
	}
	len = jt_strlen(szFullPath);
	if( szFullPath[len-1] !='\\' )
	{
		jt_strcat(szFullPath,_T("\\"));
	}
	jt_strcat( szFullPath , szID);
	jt_strcat( szFullPath , _T("\\"));
	jt_strcat( szFullPath , szID);
	jt_strcat( szFullPath, jS(_file_db));
	jt_strcat( szFullPath , _T(".xml"));
	if(!nFileSystem::jFolder::Is_Exist(szFullPath)) 
	{
		bool is = nFileSystem::jFolder::CreateDirForce(szFullPath);
		if(!is) return false;
		fname_t szTownXml;
		jt_sprintf(szTownXml, _T("%sclient\\server_data\\xml\\town_file_db.xml") ,pv_SERVER_RESOUCE->Get_cstr() );
		CopyFile(szTownXml , szFullPath , false);
		return true;
	}
	return false;
}
inline void Test_UID(tcstr szUID,db_uid_type uid)
{
	jAssert0(jt_strlen(szUID));
	int64 uid1;
	jt_sscanf(szUID,_T("%I64d"),&uid1);
	jAssert0(uid.m_db_id==uid1);
}


jIE* jAqCommon::FindTownBYTUID(nXML::jE eUserFileDB,Use_Town_id_t tuid)
{
	if(eUserFileDB.empty()) return 0;
	fname_t szTUID;
	ToString(tuid, szTUID);
	Test_UID(szTUID,tuid);
	jIE* pe = eUserFileDB[jS(Town_List)]->FindByFirstAttr(jS(TUID) , jIVar::EDcstr , szTUID,1);
	return pe;
}


