// jLog.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#ifdef _WIN32
#include <time.h>
#endif

#include <stdarg.h> 
#include "jBase_Log.h"
#include "linux/nOS_filesystem.h"

using namespace nMech;
namespace nMech
{
	namespace nInterface
	{ 
		nLOG::jBase_Log g_jBase_Log;
		JBASE_API nLOG::jILog* g_pjILog =  &g_jBase_Log;
	}

	namespace nLOG
	{
		void _jConsolePrinterFunc( tcstr szString,bool bAdd )
		{
			if(bAdd)
			{
				cout << szString;
				//printf("%s",szString);
			}
			else
			{
				cout << endl << szString;
				//printf("\n%s",szString);
			}
		}

		//////////////////////////////////////////////////////////////////////
		jBase_Log::jBase_Log()
			:m_pLogPrinter(_jConsolePrinterFunc)
		{
			memset(m_szFilename,0,MAX_FILENAME_SIZE);
			//--------------------------------------------------------------------------
			// 로깅 파일 세팅
			//--------------------------------------------------------------------------
			
			SYSTEMTIME st;
			getLocalTime(&st);
			fname_t szDATE;
			jt_sprintf(szDATE,_T("[%d-%d-%d]"),st.wYear,st.wMonth,st.wDay);
			fs::path log_path = fs::current_path();
			log_path /="log";
			//log_path /=szDATE;
			log_path /="logfile.log";
			
			SetFileName(log_path.string().c_str());
			printf("jBase_Log() ok\n");
		}
		int			jBase_Log::GetWarningCount() 
		{
			return m_iWarningCount;
		}
		int			jBase_Log::GetErrorCount()
		{
			return m_iErrorCount;
		}
		void		jBase_Log::ResetWaringErrorCount()
		{
			m_iWarningCount = m_iErrorCount=0;
			return ;
		}

		//set the file used to log to disk
		//////////////////////////////////////////////////////////////////////
		void jBase_Log::SetFileName(tcstr command)
		{
			printf("%s>log file : %s\n",jFUNC,command);
			jt_strcpy(m_szFilename,command);

			if(jt_strlen(m_szFilename) && fs::exists(m_szFilename))
			{
				SYSTEMTIME st;
				getLocalTime(&st);
				fname_t szDATE;
				jt_sprintf(szDATE,_T("[%d-%d-%d]"),st.wYear,st.wMonth,st.wDay);
				fs::path log_path = fs::current_path();
				log_path /="log";
				log_path /=szDATE;
				fs::create_directories(log_path);
				fname_t backupFile;
				jt_sprintf(backupFile,"%s_%d-%d-%d.%d.%d",m_szFilename,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
				fs::tpath orgLog = fs::path(m_szFilename) ;
				try
				{
					if(fs::exists(backupFile))
					{
						fs::remove(backupFile);
					}
					fs::copy_file( orgLog, backupFile);
				}
				catch (...)
				{
					jWARN("error backup file : %s",backupFile);
				}
				//fs::copy_file(backupFile, log_path);
				//fs::remove(backupFile);
				//fs::remove(orgLog);
			}

			fs::path p = m_szFilename;
			fs::create_directories(p.parent_path());
			FILE *fp=jt_fopen(m_szFilename,_T("wt"));
			if (fp)
				fclose(fp);
		}


		//////////////////////////////////////////////////////////////////////////
		tcstr  jBase_Log::GetFileName()
		{
			return m_szFilename;
		}



#define jLogV_PROCESS(LogLevel,LogType,type) \
	TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE];\
	memset(_szTemp234,0,sizeof(_szTemp234));\
	va_list args;\
	va_start(args,szFormat);\
	cstr msg = LogV( LogLevel,LogType,_szTemp234,type,szFormat,args );\
	va_end(args);

		void jBase_Log::Warning(uint32 threadID,tcstr szFormat,...)
		{
			++m_iWarningCount;
			jLogV_PROCESS(0,0,eWarning);
            msg=0;
		}
		void jBase_Log::Error(uint32 threadID,tcstr szFormat,...)
		{
			++m_iErrorCount;
			jLogV_PROCESS(0,0,eERROR);
			_errorCheck(msg);
		}
		void jBase_Log::_errorCheck(cstr msg)
		{
			if(msg==0) return;
			// get system error message before any attempt to write into log
			//tcstr  szSysErrorMessage = nUtil::nWIN::GetLastSystemErrorMessage();
#ifdef DEF_WINDOWS
			::MessageBox( NULL,msg,_T("Error"),MB_OK|MB_ICONERROR|MB_SYSTEMMODAL );
#else
			throw msg;
#endif
		}
		void		jBase_Log::LogToConsole(uint32 threadID,tcstr szFormat, ...)
		{
			jLogV_PROCESS(0,0,eLogToConsole);
            msg=0;

		}
		void jBase_Log::Warning(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType, tcstr szFormat,...)
		{
			++m_iWarningCount;
			jLogV_PROCESS(0,0,eWarning);
            msg=0;
		}
		void jBase_Log::Error(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			++m_iErrorCount;
			jLogV_PROCESS(0,0,eERROR);
            msg=0;
		}
		void jBase_Log::Log(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLog);
            msg=0;
		}
		void jBase_Log::LogPlus(const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLogPlus);
            msg=0;
		}

		void jBase_Log::Log(uint32 threadID,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLog);
            msg=0;
		}
		void jBase_Log::LogPlus(tcstr szFormat,...) 
		{
			jLogV_PROCESS(0,0,eLogPlus);
            msg=0;
		}
		void jBase_Log::LogTime(uint32 threadID,tcstr szFormat,...) 
		{
			jLogV_PROCESS(0,0,eLogTime);
            msg=0;
		}

		void jBase_Log::LogTimeTag(uint32 threadID,bool withFile)
		{
		}
		void jBase_Log::Release()
		{
		}
		//will log the text both to file and console
		//////////////////////////////////////////////////////////////////////
		cstr jBase_Log::LogV(tcstr ,tcstr , TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE],ELogType type , tcstr  szFormat, va_list args )
		{
			const size_t TEMP_LEN = MAX_TEMP_LENGTH_SIZE;
			if (!szFormat) return _T("");
			TCHAR *szString = _szTemp234;

			//--------------------------------------------------------------------------
			// 로깅 레벨 스트링 출력
			//--------------------------------------------------------------------------
			size_t skipLen = 0;
			size_t len=0;
			bool logPlus =false;
			switch(type)
			{
			case eWarning:
				{
					jt_sprintf( szString,_T("[WARNING]"));
					len = jt_strlen(szString);
					szString += len;
					skipLen +=  len;
				}
				break;
			case eERROR:
				{
					jt_sprintf( szString,_T("[ERROR]"));
					len = jt_strlen(szString);
					szString += len;
					skipLen +=len;
				}
				break;
			case eLogPlus: // LogPlus
				logPlus=true;
				break;
			case eLogTime:
				{
					szString += len;
					skipLen +=len;
					break;
				}
			default:
				{

				}
			}

			jt_vsnprintf( szString, TEMP_LEN-skipLen-32, szFormat, args );
			_szTemp234[TEMP_LEN-1]=0;

			_logToFile( _szTemp234 ,logPlus);
			m_pLogPrinter(_szTemp234,logPlus);
			return _szTemp234;
		}

		//////////////////////////////////////////////////////////////////////
		void jBase_Log::_logToFile(tcstr szString,bool bAdd)
		{
			tcstr szFile = m_szFilename;

			if(!jt_strlen(szFile)) return;
			if (!szString || !szString[0])
				return;

			tofstream of(jA(m_szFilename), ios_base::app);
			if(of.bad()) return;
			//of.imbue(locale(jA(pv_file_locale->Get_cstr())));
			if(!bAdd) of << endl;
			of << szString;

		}
		bool jBase_Log::TestLogLevel(const StringID logLevel , const StringID logType , tcstr*szLevel, tcstr*szType)
		{
			return true;
		}

		void jBase_Log::UpdateLogLevel(const StringID logLevel,ELogLevelType isLogOn)
		{
		}

		bool jBase_Log::UpdateLogType(const StringID logLevel,const StringID logType, bool isLogOn)
		{
			return true;
		}
		int			jBase_Log::PushIndent(int iWantedIndentCount)
		{
			return 0;
		}
		int			jBase_Log::PopIndent(int iWantedIndentCount)
		{
			return 0;
		}
		void		jBase_Log::LogOff(bool is)
		{
		}
		void		jBase_Log::ProcessMessage(cstr szMsg,void* v)
		{

		}
	}
}
