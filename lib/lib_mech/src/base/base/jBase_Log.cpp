// jLog.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#ifdef _WIN32
#include <time.h>
#endif

#include "jBase_Log.h"
#include "interface/jIINI_File.h"
#include "base/jWindow_Util.h"
using namespace nMech;
namespace nMech
{
	namespace nLOG
	{
		void _jConsolePrinterFunc( tcstr szString,bool bAdd )
		{
#ifdef DEF_WINDOWS
			DWORD writtenCount;

			if(bAdd)
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, (DWORD)jt_strlen(szString), &writtenCount, NULL);
			else
			{
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, (DWORD)jt_strlen(szString), &writtenCount, NULL);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
			}
#endif
		}

		//////////////////////////////////////////////////////////////////////
		jBase_Log::jBase_Log()
			:m_pLogPrinter(_jConsolePrinterFunc)
		{
			memset(m_szFilename,0,MAX_FILENAME_SIZE);
			//--------------------------------------------------------------------------
			// 로깅 파일 세팅
			//--------------------------------------------------------------------------
			nScript::jINI_Data_t pv_log_file_path = g_ExeEnv.Get_INI()->GetData(jS(exe) , jS(log_file_path));
			
			fname_t szBufFileTag;
			jt_sprintf(szBufFileTag,_T("%s"),g_ExeEnv.m_szAppNic);
			jIVar* pv_LogFileTag= jCV(jILog,LogFileTag,szBufFileTag,0,"log file path");
			jASSERT0(pv_log_file_path && pv_LogFileTag);
			SYSTEMTIME st;
			GetLocalTime(&st);
			fname_t szDATE;
			jt_sprintf(szDATE,_T("[%3d-%2d-%2d]"),st.wYear,st.wMonth,st.wDay);
			jt_sprintf(szBufFileTag, _T("%s\\%s\\%s"),pv_log_file_path->Get_cstr() , szDATE , pv_LogFileTag->Get_cstr());
			SetFileName(szBufFileTag);
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
			if (!command)// 값이 NULL이면 파일이름 뒤에 1부터 해서 숫자를 붙인다.
			{
				static int si = 0;

				fname_t buf; 
				jt_strcpy(buf, m_szFilename );
				if(si==0)
				{
					TCHAR* ch = jt_strstr(buf,_T(".log"));
					if(!ch) 
						return;

					jt_sprintf(ch , _T("((%d)).log"), ++si);
				}
				else
				{
					TCHAR* ch = jt_strstr(buf,_T("(("));
					if(!ch) 
						return;
					jt_sprintf(ch , _T("((%d)).log"), ++si);
				}
				jt_strcpy(m_szFilename, buf);
				return;
			}
			std::tstring prevFile = m_szFilename;

			if(jt_strstr(command,_T(":\\")))
			{
				jt_sprintf(m_szFilename, _T("%s_%s.log"),command, g_ExeEnv.m_szRunStartTime);
			}
			else
			{
				tcstr szC = command;
				if(command[0]=='\\')
				{
					szC = command+1;
				}

				jt_sprintf(m_szFilename, _T("%s%s_%s.log"),g_ExeEnv.m_szStartDir, szC,g_ExeEnv.m_szRunStartTime);

			}
			nFileSystem::jFolder::CreateDirForce(m_szFilename);
			if(prevFile.size() && nFileSystem::jFolder::Is_Exist(prevFile.c_str()))
			{
				MoveFile(prevFile.c_str() , m_szFilename);
			}
			else
			{
				FILE *fp=jt_fopen(m_szFilename,_T("wt"));
				if (fp)
					fclose(fp);
			}
		}


		//////////////////////////////////////////////////////////////////////////
		tcstr  jBase_Log::GetFileName()
		{
			return m_szFilename;
		}



#define jLogV_PROCESS(LogLevel,LogType,type) \
	TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE];\
	va_list args;\
	va_start(args,szFormat);\
	cstr msg = LogV( LogLevel,LogType,_szTemp234,type,szFormat,args );\
	va_end(args);

		void jBase_Log::Warning(uint32 threadID,tcstr szFormat,...)
		{
			++m_iWarningCount;
			jLogV_PROCESS(0,0,eWarning);
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
			::MessageBox( NULL,msg,_T("Error"),MB_OK|MB_ICONERROR|MB_SYSTEMMODAL );
		}
		void		jBase_Log::LogToConsole(uint32 threadID,tcstr szFormat, ...)
		{
			jLogV_PROCESS(0,0,eLogToConsole);
		}
		void jBase_Log::Warning(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType, tcstr szFormat,...)
		{
			++m_iWarningCount;
			jLogV_PROCESS(0,0,eWarning);
		}
		void jBase_Log::Error(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			++m_iErrorCount;
			tcstr szLevel =0, szType=0;
			jLogV_PROCESS(0,0,eERROR);
		}
		void jBase_Log::Log(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLog);
		}
		void jBase_Log::LogPlus(const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLogPlus);
		}

		void jBase_Log::Log(uint32 threadID,tcstr szFormat,...)
		{
			jLogV_PROCESS(0,0,eLog);
		}
		void jBase_Log::LogPlus(tcstr szFormat,...) 
		{
			jLogV_PROCESS(0,0,eLogPlus);
		}
		void jBase_Log::LogTime(uint32 threadID,tcstr szFormat,...) 
		{
			jLogV_PROCESS(0,0,eLogTime);
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

			_logToFile( _szTemp234 ,logPlus,jx(NULL));
			m_pLogPrinter(_szTemp234,logPlus);
			return _szTemp234;
		}

		//////////////////////////////////////////////////////////////////////
		void jBase_Log::_logToFile(tcstr szString,bool bAdd,StringID FileType)
		{
			static jIVar* pv_file_locale= jCV(jILog,file_locale,_T("korean"),0,"file locale ");

			tcstr szFile = m_szFilename;

			if(!jt_strlen(szFile)) return;
			if (!szString || !szString[0])
				return;


			tofstream of(jA(m_szFilename), ios_base::app);
			if(of.bad()) return;
			of.imbue(locale(jA(pv_file_locale->Get_cstr())));
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
		void jBase_Log::SetReportEvent(tcstr szSourceName,struct jIReportEvent*pRE)
		{
		}
		jIReportEvent*	jBase_Log::GetReportEvent(tcstr szSourceName)
		{
			return 0;
		}
		//--------------------------------------------------------------------------
		void jBase_Log::RunConsoleTool()
			//--------------------------------------------------------------------------
		{
		}
	}
}
