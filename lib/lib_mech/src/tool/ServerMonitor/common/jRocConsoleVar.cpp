/* file : jRocConsoleVar.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-01-27 23:06:48
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "jRocConsoleVar.h"
#if 1
using namespace nCONSOLE_VAR;

#ifdef for_each_CONSOLE_VAR
for_each_CONSOLE_VAR(rocDEFINE_CONSOLE_VAR);
#endif

namespace nCONSOLE_VAR
{

	void init_File_jRocConsoleVar(jRocConsoleVar& var)
	{
#ifdef DF_SERVER_TEAM
		if(var.m_option &eCVO_DONT_SAVE_SERVER) return; // 서버에서는  eCVO_DONT_SAVE_CLIENT이면 파일저장및 로딩안함.
#else
		if(var.m_option &eCVO_DONT_SAVE_CLIENT) return; // 클라에서는 eCVO_DONT_SAVE_SERVER이면 파일저장및 로딩안함.
#endif

		fname_t szFile;
		jt_sprintf(szFile,_T("%s.cfg"),var.m_name.c_str());
		FILE* fp = jt_fopen(szFile,_T("rt"));
		if(!fp) // 파일을 최초 생성.
		{
			fp = jt_fopen(szFile,_T("wt"));
			if(fp)
			{
				tname1024_t data;
				jt_fprintf(fp,_T("%s\n"),var.ToString(data));
				jt_fprintf(fp,_T("//%s = %s\n"),var.m_name.c_str(), var.m_help.c_str());
				fclose(fp);
			}
			return;
		}

		if(var.m_option&eCVO_NOT_USE_VAR)//사용하지않는 console var 파일은 삭제 표시.
		{
			fclose(fp);
			fname_t szDeleteFile;
			jt_sprintf(szDeleteFile,_T("%s.delete"),szFile);
			MoveFile(szFile,szDeleteFile);
			return;
		}

		// 기존 파일의 값 로딩.
		tstring sBuf;
		tname1024_t szBuf;
#if 1
		while(NULL != jt_fgets(szBuf, 1024, fp))
		{
			sBuf += szBuf;
		}
		fclose(fp);

		std::vector<tstring> out;
		nString::jSplit(sBuf,_T("\n\r"),out);
		if(!out.size()) return;
		var.FromString(out[0].c_str());
#else
		if(NULL == jt_fgets(szBuf, 1024, fp)) 
		{
			fclose(fp);
			return;
		}
		fclose(fp);
		var.FromString(szBuf);
#endif
	}

	jLIST_TYPEDEF_map(tstring,jRocConsoleVar*,g_mapjRocConsoleVar);
	jONCE_RUN(Init_CONSOLE_VAR)
	{
#if defined(DF_VER_DEV)
		pv_LastRecvPacket_WaitTime.Set_uint32(10000);
#elif defined(DF_VER_BP)
		pv_LastRecvPacket_WaitTime.Set_uint32(10000);
#elif defined(DF_VER_YD)
		pv_LastRecvPacket_WaitTime.Set_uint32(4000);
#elif defined(DF_VER_MARKET)
		pv_LastRecvPacket_WaitTime.Set_uint32(10000);
#else
		pv_LastRecvPacket_WaitTime.Set_uint32(10000);
#endif

		tfname_t buf;
		GetModuleFileName(0, buf, sizeof(buf));
		nFileSystem::jFileName fn(buf);
		fn.GetPath(buf);
		tfname_t cfg_dir;
		jt_sprintf(cfg_dir,_T("%sConsoleVar"),buf);
		tname1024_t szCurrDir;
		GetCurrentDirectory(256,szCurrDir);

#ifdef DF_SERVER_TEAM
		int ret = jt_mkdir(cfg_dir);
		jt_chdir(cfg_dir);
		#define Init_CONSOLE_VAR_CV_9845(TYPE, NAME , INIT_VALUE , HELP , OPTION) g_mapjRocConsoleVar[_T(#NAME)]=&NAME; init_File_jRocConsoleVar(NAME);
#else // DF_CLIENT_TEAM

	#ifdef SHIPPING
		#define Init_CONSOLE_VAR_CV_9845(TYPE, NAME , INIT_VALUE , HELP , OPTION) g_mapjRocConsoleVar[_T(#NAME)]=&NAME;
	#else
		int ret = jt_mkdir(cfg_dir);
		jt_chdir(cfg_dir);
		#define Init_CONSOLE_VAR_CV_9845(TYPE, NAME , INIT_VALUE , HELP , OPTION) g_mapjRocConsoleVar[_T(#NAME)]=&NAME; init_File_jRocConsoleVar(NAME);
	#endif

#endif
		for_each_CONSOLE_VAR(Init_CONSOLE_VAR_CV_9845);
		jt_chdir(szCurrDir);

	}

	bool SetConsoleVar(tcstr szName, tcstr szData)
	{
		if(!g_mapjRocConsoleVar.count(szName)) return false;
		g_mapjRocConsoleVar[szName]->FromString(szData);
		return true;
	}
	extern jRocConsoleVar* GetConsoleVar(tcstr szName)
	{
		if(!g_mapjRocConsoleVar.count(szName)) return 0;
		return g_mapjRocConsoleVar[szName];
	}

	tcstr jRocConsoleVar::ToString(tname1024_t buf)
	{
		switch(m_eType)
		{
		case eCV_wstring:
			jt_strcpy_s(buf, 1024, jT(m_wstring));
			break;
		case eCV_uint64:
			jt_sprintf(buf,_T("%I64u"),m_uint64);
			break;
		case eCV_int64:
			jt_sprintf(buf,_T("%I64d"),m_int64);
			break;
		default:
#define ToString_CV_9845(TYPE) if(m_eType==eCV_##TYPE) jt_sprintf(buf,_T("%d"),m_##TYPE);
			for_each_CONSOLE_VAR_TYPE_simple(ToString_CV_9845);
			break;
		}
		return buf;
	}
	void  jRocConsoleVar::FromString(tcstr buf)
	{
		switch(m_eType)
		{
		case eCV_wstring:
			m_wstring = jW(buf);
			break;
		case eCV_uint64:
		case eCV_int64:
			Set_int64(jt_atoi64(buf));
			break;
		default:
#define FromString_CV_9845(TYPE) if(m_eType==eCV_##TYPE) Set_##TYPE((TYPE)jt_atoi(buf));
			for_each_CONSOLE_VAR_TYPE_simple(FromString_CV_9845);
			break;
		}
	}

}
#endif