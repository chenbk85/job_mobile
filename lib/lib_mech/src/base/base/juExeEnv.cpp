/* 
	filename:	juExeEnv.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-07-09오후 3:56:27
	title	:	
*/

#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <io.h>
#include "time.h"
#include "juExeEnv.h"
#include "base/jFolder.h"
#include "Interface/jIINI_File.h"
#include "header/jTCHAR_util.h"
#include "interface/xml/jIXml.h"
#include "base/jBase_Log.h"
#include <locale.h>
#include "jFileDebugger.h"
#include <winsock2.h>

//#define jLOG_DEBUG



//--------------------------------------------------------------------------
// jGlobal.ini 기본 생성내용.
//--------------------------------------------------------------------------
#define jDEFAULT_INI_TEXT(SECTION,CODE,NOTE)\
	\
	NOTE(주석 앞에 공백이 있으면 에러남)\
	\
	SECTION([exe])\
	\
	NOTE(default run env folder.)\
	CODE(start_dir , "..")\
	\
	NOTE(is run multi excute)\
	CODE(multi_run , 0)\
	\
	NOTE(default app_xml name. if not notified use app name.)\
	CODE(default_app_xml , "")\
	\
	NOTE(dont save file - app.xml  ini etc)\
	CODE(dont_save_file, 0)\
	\
	NOTE(is run TestUnit)\
	CODE(run_unit_test, 0)\
	\
	NOTE(is print string index)\
	CODE(MAKE_XMLID , 0)\
	\
	NOTE(run env languge locale)\
	CODE(locale , "kor")\
	\
	NOTE(log file save folder )\
	CODE(log_file_path, "c:\temp\log")\


/* 위 코드의 출력 샘플은 다음과 같다.

; 주석 앞에 공백이 있으면 에러남


[exe]

; 기본 실행시작폴더지정시. ".."는 상위폴더.
start_dir = ".."

; 실행파일이 여러개 실행가능
multi_run = 0

; 기본적으로 로딩하는 app_xml이름. 지정안되어 있으면 실행파일명.xml을 로당한다.
default_app_xml = ""

; TestUnit 실행여부
run_test_unit = 0

; string index를 출력할지
MAKE_XMLID = 0

; 실행 언어 로케일
locale = "kor"

; 기본적으로 생성되는 파일들을 저장하지 않음. app.xml , ini , user.xml
dont_save_file = 0

*/


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace nMech
{
	/*
	사설IP로 할당되어있는

	10.0.0.0 - 10.255.255.255
	172.16.0.0 - 172.31.255.255
	192.168.0.0 - 192.168.255.255

	대역 이외의 IP를 공인IP라고 한다. 
	*/
	static bool isPrivateIP(acstr strIp)
	{
		vector<astring> out;
		nString::jSplitA(strIp, ". ",out);
		if( out.size()!=4) return false;
		int num = ja_atoi(out[0].c_str());
		int num2 = ja_atoi(out[1].c_str());

		if(num==10) 
		{
			//jLOG(_T("%s is private"), jT(strIp));
			return true;
		}
		if(num==172)
		{
			if(num2>=16 && num2 <=31) 
			{
				//jLOG(_T("%s is private"), jT(strIp));
				return true;
			}
			//jLOG(_T("%s is public"), jT(strIp));
			return false;

		}
		else if(num==192 && num2==168) 
		{
			//jLOG(_T("%s is private"), jT(strIp));
			return true;
		}

		//jLOG(_T("%s is public"), jT(strIp));
		return false;
	}
	static acstr GetPrivateIP(aname32_t szBuf)
	{
		char localHostName[256];
		//IN_ADDR in_addr;
		HOSTENT *pHost;

		memset(localHostName, 0x00, 256);
		gethostname( localHostName, 256 );
		pHost = gethostbyname( localHostName );
		for(int i = 0; pHost->h_addr_list[i]; ++i)
		{
			ja_strcpy(szBuf, inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i] ) );
			if(isPrivateIP(szBuf)) 
			{
				//jLOG(_T("private ip returned : %s"), jT(szBuf));
				return szBuf;
			}
		}
		ja_strcpy(szBuf , "127.0.0.1");
		return szBuf;
	}
	static acstr GetPublicIP(aname32_t szBuf)
	{
		char localHostName[256];
		//IN_ADDR in_addr;
		HOSTENT *pHost;
		/*
		사설IP로 할당되어있는

		10.0.0.0 - 10.255.255.255
		172.16.0.0 - 172.31.255.255
		192.168.0.0 - 192.168.255.255

		대역 이외의 IP를 공인IP라고 한다. 
		*/

		memset(localHostName, 0x00, 256);
		gethostname( localHostName, 256 );
		DWORD iError =WSAGetLastError();
		pHost = gethostbyname( localHostName );
		for(int i = 0; pHost->h_addr_list[i]; ++i)
		{
			ja_strcpy(szBuf, inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]) );
			jLOG(_T("gethostbyname ip = %s") , jT(szBuf) );
			if(isPrivateIP(szBuf )) 
				continue;

			//jLOG(_T("GetPublicIP() :  public ip returned : %s"), jT(szBuf));
			return	szBuf;
		}
		//jLOG(_T("GetPublicIP() :  private ip returned : %s"), jT(szBuf));
		return	GetPrivateIP(szBuf);
	}

	void make_App_Default_xml(tcstr fileName)
	{
		nFileSystem::jFolder dir;
		tofstream of(fileName);
		of << _T(
"<?xml version='1.0' encoding='euc-kr'?>\n\
<jGame DOC_TYPE='APP'>\n\
	<jIConsoleVar Original_FILE='xml\\jConsoleVar_default.xml'>\n\
		<exe>\n\
			<UserInfo     FLAG='' HELP=''>xml\\user\\UserInfo.xml</UserInfo>\n\
		</exe>\n\
	</jIConsoleVar>\n\
	<DLL>\n\
		<Com_Util b_ENABLE='1'>Com_Util.dll</Com_Util>\n\
		<jILog b_ENABLE='1'>jLog.dll</jILog>\n\
		<jINet b_ENABLE='1'>jNet.dll</jINet>\n\
		<jIOrb b_ENABLE='0' SERVICE_REQUEST_LIST='NULL;NULL' SERVICE_PROVIDE='NULL'>jOrb.dll</jIOrb>\n\
	</DLL>\n\
</jGame>\n");

	}


	juExeEnv g_ExeEnv;
	extern HANDLE g_hModule;
	
	void juExeEnv::__init()
	{
		WSADATA WsaData;
		WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

		jt_strcpy(m_szDefaultLocale,_T("kor"));
		m_pDocLanguge=0;


		//--------------------------------------------------------------------------
		// 컴파일 버젼 , 컴퓨터이름 & 사용자 이름세팅
		//--------------------------------------------------------------------------

		jt_sprintf(m_szVersion ,_T("%s(%s)"),_T(__DATE__), _T(__TIME__));
		DWORD iSizze = sizeof(m_szUserName);
		memset(m_szUserName, 0, iSizze);
		::GetUserName(m_szUserName, &iSizze);

		iSizze = sizeof(m_szComputerName );
		GetComputerName( m_szComputerName , &iSizze);

		SYSTEMTIME	SystemTime;
		GetLocalTime(&SystemTime);
		_sntprintf(m_szRunStartTime, 32, _T("[%03d-%02d-%02d]%02d.%02d.%02d"),
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay,
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);

		//--------------------------------------------------------------------------
		// arg 파싱
		//--------------------------------------------------------------------------
		/* *_* by icandoit : 2006-10-26 10:31:27
		-ini:test.ini					test.ini를 사용.
		-start_dir:"c:\asdf"		c:\asdf를 시작폴더로 사용.
		-default_app_xml:"..\a.xml"   app.xml로 ../a.xml을 사용.
		-dont_save_file:0
		*/ //*_* by icandoit : 2006-10-26 10:31:29

		char* asdf = __argv[0];
		for(int i=1 ; i < __argc ; ++i)
		{
			assert(__argv);
			tstring arg = nUNI::scb1024_t(__argv[i]).getT();
			std::vector<std::tstring> out;
			nString::jSplit(arg, _T(":") , out);
			if(!out.size()) continue;
			if(out.size()>2)
			{
				jMB(arg.c_str() , _T("arg 에러"));
				exit(0);
			}
			tcstr szName = out[0].c_str();
			if(szName[0]=='-')
			{
				++szName;
			}
			if(out.size() ==2 )
			{
				m_ArgList[szName] = out[1];
#ifdef jLOG_DEBUG
				jt_printf(_T("%s=%s\n") , szName , out[1].c_str());
#endif
			}
			else
			{
				//m_ArgList[szName] = tstring(_T("NULL"));
#ifdef jLOG_DEBUG
				jt_printf(_T("%s=<<NULL>>\n") , szName);
#endif
			}
		}


		//--------------------------------------------------------------------------
		// 실행파일이름 세팅
		//--------------------------------------------------------------------------
		tfname_t buf;
		GetModuleFileName(0, buf, sizeof(buf));
		jt_strncpy(m_szExeName,buf,ARRAY_SIZE(m_szExeName) );
		m_szExeName[sizeof(m_szExeName)-1]=0;

		GetModuleFileName(GetModuleHandle(_T("jBase.dll")), buf, sizeof(buf));
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		_tcslwr(buf);
		_tsplitpath( buf, drive, dir, fname, ext );
		_stprintf(m_szModuleDir, TEXT("%s%s"),drive,dir);

		_tsplitpath( m_szExeName, drive, dir, fname, ext );


		//--------------------------------------------------------------------------
		// ini 파일 로딩
		//--------------------------------------------------------------------------
		jt_chdir(m_szModuleDir);
		GetCurrentDirectory(_countof(m_szStartDir), m_szStartDir);
		tfname_t buf1;
		tcstr szIni = GetArg(_T("-ini"));
		if(szIni)
		{
			jt_strcpy(buf1 , szIni);
			if(! (jt_access(buf1, 0) != -1) )//파일이 없으면
				szIni =0;
		}

		if(!szIni)
		{
			jt_sprintf(buf1, _T("%s.ini"), fname);
			if(! (jt_access(buf1, 0) != -1) )//파일이 없으면
				szIni =0;
			else
				szIni = buf1;
		}
		if(!szIni)
		{
			//jt_sprintf(buf1, _T("jGlobal_%s.ini"), m_szVersion);
			jt_sprintf(buf1, _T("jGlobal.ini"));

			szIni = buf1;
		}

		cstr dont_save_file = GetArg(jS(dont_save_file));
		m_is_dont_save_file = dont_save_file && dont_save_file[0]=='1';
		if( !(jt_access(szIni, 0) != -1) && !m_is_dont_save_file)
		{
			//http://www.gosu.net/GosuWeb/Article-detail.aspx?ArticleCode=345
			std::locale::global( std::locale( "kor" ) ); 
			tofstream of(szIni/*,std::ios_base::binary*/);

#define _section(X) of << endl << endl << _T(#X) << endl <<endl;
#define _code(VAR, INIT) of << _T(#VAR) << _T(" = ") << _T(#INIT) << endl << endl;
#define _note(X) of << _T("; ") << _T(#X) << endl;

			jDEFAULT_INI_TEXT(_section, _code, _note);

			of.close();
		}

		tcstr szStartDir  =_T(".");
		if( (jt_access(szIni, 0) != -1) )//파일이 있으면
		{
			m_pINI_File = nScript::Get_jIINI_Manager()->Load(szIni);
			if(m_pINI_File)
			{
				//--------------------------------------------------------------------------
				// arg 리스트들의 값을 ini의 [exe]섹션의 값에 업데이트함
				//--------------------------------------------------------------------------
				m_ArgList_it it = m_ArgList.begin(), ie = m_ArgList.end();
				for(;it!=ie;++it)
				{
					nScript::jINI_Data_t var = m_pINI_File->GetData(_T("exe"),it->first.c_str());
					if(!var) continue;
					if(var->GetType()==jIVar::ETelement)
						var->SetType(jIVar::EDcstr);
					var->FromString(it->second.c_str() ) ;
				}

				//--------------------------------------------------------------------------
				// 실행파일 시작 폴더 세팅 1
				//--------------------------------------------------------------------------
				jxVar* pV =  m_pINI_File->GetData(_T("exe"),_T("start_dir"));
				if(pV)
				{
					szStartDir = pV->Get_cstr();
				}
			}
		}

		//--------------------------------------------------------------------------
		// App Nic name 세팅 
		//					: 인자에 "app_nic_name:asdf" 가 없으면 실행파일이름을 사용한다.
		//--------------------------------------------------------------------------
		tcstr szAppNic = GetArg(_T("app_nic_name"));
		if(szAppNic && jt_strlen(szAppNic))
		{
			jt_strcpy(m_szAppNic , szAppNic);
		}
		else
		{
			jt_sprintf(m_szAppNic,_T("App_%s") ,fname);
		}

		//--------------------------------------------------------------------------
		// 실행파일 시작 폴더 세팅 2
		//--------------------------------------------------------------------------

		jt_chdir(szStartDir);
		GetCurrentDirectory(_countof(m_szStartDir), m_szStartDir);
		jt_strlwr(m_szStartDir);
		if(m_szStartDir[jt_strlen(m_szStartDir)-1]!=_T('\\') )
			jt_strcat(m_szStartDir,_T("\\"));


		//--------------------------------------------------------------------------
		// 메모리 DLL 세팅
		//--------------------------------------------------------------------------
#if 0
		m_jIMemoryDLL=0;
		static jMemoryDLL s_jIMemoryDLL;
		m_jIMemoryDLL = &s_jIMemoryDLL;
#endif


		nFileSystem::jFolder::CreateDirForce( GetUserFilePath() );
		assert(nFileSystem::jFolder::Is_Exist(GetUserFilePath()) );


		//--------------------------------------------------------------------------
		// app doc load
		//--------------------------------------------------------------------------
		if(m_is_dont_save_file)
		{
			fname_t szTemp;
			GetTempPath(sizeof(szTemp), szTemp);
			jt_sprintf(buf, _T("%s%s.xml"), szTemp, m_szAppNic);
			DeleteFile(buf);
		}
		else
		{
			aname256_t szIP;
			GetPublicIP(szIP);
			jt_sprintf(buf, _T("xml\\%s_%s.xml"), m_szAppNic,jT(szIP));
			if(!nFileSystem::jFolder::Is_Exist(buf))
			{
				jt_sprintf(buf, _T("xml\\%s.xml"), m_szAppNic);
			}
		}
		jt_printf(_T("load app doc = %s"), buf);
		nGLOBAL::g_pDocApp = GetjIXml()->Load(buf);
		if(!nGLOBAL::g_pDocApp)
		{
			make_App_Default_xml(buf);
			//CopyFile(_T("xml\\App_Default.xml") ,buf , false);
			nGLOBAL::g_pDocApp = GetjIXml()->Load(buf);
			if(!nGLOBAL::g_pDocApp)
			{
				jMB(_T("not found xml/app's xml"), m_szAppNic);
				throw false;
			}
		}

		//--------------------------------------------------------------------------
		// 콘솔변수 초키화
		//--------------------------------------------------------------------------
		nCONSOLE::Get_jIConsoleVar()->Init(nGLOBAL::g_pDocApp);

		static nLOG::jBase_Log g_jBase_Log;
		nInterface::g_pjILog = &g_jBase_Log;
	}

	int filter_juExeEnv(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
	{
		nDebug::MakeDumpFile("juExeEnv", ep);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	juExeEnv::juExeEnv()
	{
		//std::locale::global( std::locale( "kor" ) ); 
		printf("하면되 jExeEnv() call\n");
		__init();
		printf("jExeEnv() ok\n");
	}

	tcstr juExeEnv::GetArg(tcstr sz)
	{
		m_ArgList_it it = m_ArgList.find(sz);
		if(it==m_ArgList.end()) return 0;
		return it->second.c_str();
	}

	cstr juExeEnv::GetUserFilePath()
	{
		return _T("xml\\user\\");
	}
	cstr juExeEnv::GetUserXmlFileName(fname_t buf)
	{
		jt_sprintf(buf, _T("%s%s_%s.xml"),GetUserFilePath(),m_szAppNic, m_szUserName);
		return buf;
	}


}//namespace nMech

using namespace nMech;

