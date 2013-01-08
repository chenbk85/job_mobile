// test_template.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <direct.h>


// X(CMD,ARG_MIN,ARG_MAX,HELP)
#define for_each_Cmd(X)\
	X(restart,2,4,"<exe_name> <delay_time_sec> [kill_process] [job_dir]")\
	X(kill,1,2,"<exe_name | exe_pid> [delay_time_sec]")\
	X(grep,5,5,"<target_folder> <file_pattern> <out_file> <action> <find_str>")\
	X(grep_ini,1,1,"<ini file name>")


struct jFind_dir
{
	tstring target_folder;
	tstring file_pattern;
	tstring out_file;
	tstring action;
	tstring find_str;
	std::list<tstring> outList;

};

void for_each_folder_function(tcstr szFile,void* v)
{
	jFind_dir &fd  = *((jFind_dir*)v);
	fd.outList.push_back(szFile);
}

void trim_begin_end(tstring& str)
{
	if(str[0]=='\"')
	{
		str.erase(str.begin());
	}
	if(str[str.size()-1]=='\"')
	{
		str[str.size()-1]=0;
	}
}

int  _tmain_grep(int argc, _TCHAR* argv[])
{
	jFind_dir fd;
	fd.target_folder=argv[0];
	fd.file_pattern=argv[1];
	fd.out_file=argv[2];
	fd.action=argv[3];
	fd.find_str=argv[4];
	trim_begin_end(fd.target_folder);
	trim_begin_end(fd.file_pattern);
	trim_begin_end(fd.out_file);
	trim_begin_end(fd.action);
	trim_begin_end(fd.find_str);

	for_each_folder( fd.target_folder.c_str(),for_each_folder_function ,&fd);

	return 0;
}
int  _tmain_grep_ini(int argc, _TCHAR* argv[])
{
	return 0;
}

int  _tmain_kill(int argc, _TCHAR* argv[])
{
	cstr kill_process=argv[0];
	cstr delay_time_sec=0;if(argc>=2) delay_time_sec= argv[1];
	if(delay_time_sec)
	{
		DWORD iDelay = jt_atoi(delay_time_sec);
		if(iDelay>0)
			Sleep(iDelay*1000);
	}
	fname_t szBuf;
	tstring proc= kill_process;
	if( isdigit(proc[0]) )
	{
		kill_Process_byID(jt_atoi(proc.c_str()));
		jt_sprintf(szBuf,_T("kill.exe %u"),jt_atoi(proc.c_str()));
	}
	else
	{
		kill_Process_byName(proc.c_str(),0);
		jt_sprintf(szBuf,_T("kill.exe %s"),proc.c_str() );
	}
	return 0;
}
int  _tmain_restart(int argc, _TCHAR* argv[])
{
	cstr exe_name=argv[0];
	cstr delay_time_sec=argv[1];
	cstr kill_process=0; if(argc>=3) kill_process= argv[2];
	cstr job_dir=0; if(argc>=4)	job_dir=argv[3];

	fname_t szDir;
	GetCurrentDirectory(255,szDir);

	int iT = jt_atoi(delay_time_sec);
	Sleep( iT*1000 );
	if(kill_process)
	{
		fname_t szBuf;
		tstring proc= kill_process;
		if( isdigit(proc[0]) )
		{
			kill_Process_byID(jt_atoi(proc.c_str()));
			jt_sprintf(szBuf,_T("kill.exe %u"),jt_atoi(proc.c_str()));
		}
		else
		{
			kill_Process_byName(proc.c_str(),0);
			jt_sprintf(szBuf,_T("kill.exe %s"),proc.c_str() );
		}
	}
	if(job_dir)
	{
		jt_chdir(job_dir);
		GetCurrentDirectory(255,szDir);
		jt_printf(_T("\nchange dir=%s, curr dir=%s\n"),job_dir,szDir);
	}
//	jt_printf(_T("\nWinExec(%s),SW_SHOW);\n"),argv[1]);
// 	if(!Is_Exist(argv[1]))
// 	{
// 		GetCurrentDirectory(255,szDir);
// 		jt_printf(_T("\nWinExec(%s) is not found. currdir=%s\n"),argv[1],szDir);
// 		Sleep(3000);
// 	}
	UINT ret =WinExec(jA(exe_name),SW_SHOW);
	if(ret <= 31)
	{
		jt_printf(_T("\n[ERROR]tool_restarter.exe restart %s %s > WinExec ret= %d\n"),exe_name,delay_time_sec,ret);
		Sleep(3000);
		exit(999);
		return 999;
	}
	jt_printf(_T("\ntool_restarter.exe %s %s <OK>\n"),exe_name,delay_time_sec);
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
#define print_help_cmd342(CMD,ARG_MIN,ARG_MAX,HELP) jt_printf(_T("\ntool_command.exe ") jS(CMD) _T(" ") _T(HELP));

	if(argc==0 || argc==1 )
	{
		//jt_printf(_T("%s /?\n"),argv[1]);
		for_each_Cmd(print_help_cmd342);
		return 0;
	}

	cstr szCmd=0;
	if(argc>=2)
	{

		szCmd=argv[1];
		if( jt_strstr(szCmd,_T("?")) || jt_strstr(szCmd,_T("-help")) )
		{
			jt_printf(_T("%s /?\n"),argv[1]);
			for_each_Cmd(print_help_cmd342);
			return 0;
		}
	}

	#define call_Cmd432(CMD,ARG_MIN,ARG_MAX,HELP) \
	if(jt_strcmp(szCmd,jS(CMD))==0)\
	{\
		if(argc<(ARG_MIN+2) || argc>(ARG_MAX+2) )\
		{\
			jt_printf(_T("\n[ERROR]%s ") jS(CMD) _T(" ") _T(HELP) ,argv[0]);\
			return 0;\
		}\
		int _tmain_##CMD(int argc, _TCHAR* argv[]); \
		return _tmain_##CMD(argc-2,argv+2); \
	}\

	for_each_Cmd(call_Cmd432)
	else
	{
		jMB(_T("tool_command.exe /?"),_T("error"));
		return 0;
	}

	return 0;
}

