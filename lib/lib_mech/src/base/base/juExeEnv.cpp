/* 
	filename:	juExeEnv.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-07-09���� 3:56:27
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
// jGlobal.ini �⺻ ��������.
//--------------------------------------------------------------------------
#define jDEFAULT_INI_TEXT(SECTION,CODE,NOTE)\
	\
	NOTE(�ּ� �տ� ������ ������ ������)\
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


/* �� �ڵ��� ��� ������ ������ ����.

; �ּ� �տ� ������ ������ ������


[exe]

; �⺻ �����������������. ".."�� ��������.
start_dir = ".."

; ���������� ������ ���డ��
multi_run = 0

; �⺻������ �ε��ϴ� app_xml�̸�. �����ȵǾ� ������ �������ϸ�.xml�� �δ��Ѵ�.
default_app_xml = ""

; TestUnit ���࿩��
run_test_unit = 0

; string index�� �������
MAKE_XMLID = 0

; ���� ��� ������
locale = "kor"

; �⺻������ �����Ǵ� ���ϵ��� �������� ����. app.xml , ini , user.xml
dont_save_file = 0

*/


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace nMech
{
	/*
	�缳IP�� �Ҵ�Ǿ��ִ�

	10.0.0.0 - 10.255.255.255
	172.16.0.0 - 172.31.255.255
	192.168.0.0 - 192.168.255.255

	�뿪 �̿��� IP�� ����IP��� �Ѵ�. 
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
		�缳IP�� �Ҵ�Ǿ��ִ�

		10.0.0.0 - 10.255.255.255
		172.16.0.0 - 172.31.255.255
		192.168.0.0 - 192.168.255.255

		�뿪 �̿��� IP�� ����IP��� �Ѵ�. 
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
		WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 ������ �ε��մϴ�.

		jt_strcpy(m_szDefaultLocale,_T("kor"));
		m_pDocLanguge=0;


		//--------------------------------------------------------------------------
		// ������ ���� , ��ǻ���̸� & ����� �̸�����
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
		// arg �Ľ�
		//--------------------------------------------------------------------------
		/* *_* by icandoit : 2006-10-26 10:31:27
		-ini:test.ini					test.ini�� ���.
		-start_dir:"c:\asdf"		c:\asdf�� ���������� ���.
		-default_app_xml:"..\a.xml"   app.xml�� ../a.xml�� ���.
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
				jMB(arg.c_str() , _T("arg ����"));
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
		// ���������̸� ����
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
		// ini ���� �ε�
		//--------------------------------------------------------------------------
		jt_chdir(m_szModuleDir);
		GetCurrentDirectory(_countof(m_szStartDir), m_szStartDir);
		tfname_t buf1;
		tcstr szIni = GetArg(_T("-ini"));
		if(szIni)
		{
			jt_strcpy(buf1 , szIni);
			if(! (jt_access(buf1, 0) != -1) )//������ ������
				szIni =0;
		}

		if(!szIni)
		{
			jt_sprintf(buf1, _T("%s.ini"), fname);
			if(! (jt_access(buf1, 0) != -1) )//������ ������
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
		if( (jt_access(szIni, 0) != -1) )//������ ������
		{
			m_pINI_File = nScript::Get_jIINI_Manager()->Load(szIni);
			if(m_pINI_File)
			{
				//--------------------------------------------------------------------------
				// arg ����Ʈ���� ���� ini�� [exe]������ ���� ������Ʈ��
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
				// �������� ���� ���� ���� 1
				//--------------------------------------------------------------------------
				jxVar* pV =  m_pINI_File->GetData(_T("exe"),_T("start_dir"));
				if(pV)
				{
					szStartDir = pV->Get_cstr();
				}
			}
		}

		//--------------------------------------------------------------------------
		// App Nic name ���� 
		//					: ���ڿ� "app_nic_name:asdf" �� ������ ���������̸��� ����Ѵ�.
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
		// �������� ���� ���� ���� 2
		//--------------------------------------------------------------------------

		jt_chdir(szStartDir);
		GetCurrentDirectory(_countof(m_szStartDir), m_szStartDir);
		jt_strlwr(m_szStartDir);
		if(m_szStartDir[jt_strlen(m_szStartDir)-1]!=_T('\\') )
			jt_strcat(m_szStartDir,_T("\\"));


		//--------------------------------------------------------------------------
		// �޸� DLL ����
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
		// �ֺܼ��� ��Űȭ
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
		printf("�ϸ�� jExeEnv() call\n");
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

