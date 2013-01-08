// jLog.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#ifdef _WIN32
#include <time.h>
#endif

#include "jLog.h"
#include "Validator.h"
#include "header/jClipboard.h"
#include "interface/ITimer.h"
#include "interface/jIINI_File.h"
#include "base/jWindow_Util.h"
#include "header/jReportEvent_header.h"
#include "interface/jIReportEvent.h"
using namespace nMech;

#define jLog_LOCK jAUTO_LOCK_CS(m_CS);

namespace nMech
{
	tcstr s_szPipe_ConsoleMonitor = _T("\\\\.\\pipe\\jGame_Logger");
	StringID g_Current_LogLevel_jStringID = jx(jLog);
	jIVar* pv_LOG_TO_FILE= jCV(jILog,LOG_TO_FILE,false,0,"Log(), LogPlus() -> print only file ");
	jIVar* pv_LOG_OFF= jCV(jILog,LOG_OFF,false,0,"Log(), LogPlus() -> OFF");
	jIVar* pv_LoggerType = jCV(jILog, LoggerType,_T("NULL"),0,"Option : NULL , CONOUT, jConsoleMonitor  ");
	jIVar* pv_LogLevel_FILE = jCV(jILog,LogLevel_FILE,_T("xml\\LogLevel.xml"),0,"");
	jIVar* pv_ERROR_CHECK_TYPE = jCV(jILog,ERROR_CHECK_TYPE,_T("NULL"), 0, "error action : NULL, EXIT, MSGBOX, MAIL,DEBUG");
	jIVar* pv_WriteCacheBufferSize = jCV(jILog,WriteCacheBufferSize,512,0,"Kbyte. if(WriteCacheBufferSize==0) then no Caching. ");
	jIVar* pv_file_locale= jCV(jILog,file_locale,_T("korean"),0,"file locale ");
	jIVar* pv_LogFileSize= jCV(jILog,file_locale,1024*1024*2,0,"log file size");

	int get_pv_WriteCacheBufferSize()
	{
		return pv_WriteCacheBufferSize->Get_int()* 1024;
	}

	jIVar* pv_LogFileTag;

	namespace nLOG
	{

		jIE* g_peDLL;
		jLog* g_pLog;
		
	}
}

using namespace nMech::nLOG;

namespace nMech
{
	namespace nLOG
	{

		jLIST_TYPEDEF_map(tstring , jIReportEvent*,g_mapReportEvent);
		jIReportEvent* g_pReportEvent;

		inline void insert_log_level_root(nXML::jE eRoot,StringID sz)
		{
			//<test_net_client_DLL x_LevelType="LOG_ALWAYS"   b_jMX_SKIP_CHILD="1">
			nXML::jE e =eRoot[sz];
			e.AttrP(jS(LevelType)).T() = nString::Get_jIStringTable()->GetIndex(jS(OFF));
			assert(e.Attr(jS(LevelType))->IsType(jIVar::EDStringID));
			e.AttrP(jS(jMX_SKIP_CHILD)).T() = true;
		}
		inline void insert_log_level_type(nXML::jE eLogLevel,StringID sz)
		{
			// <b_USI HELP="jUdpServer_IOCP">0</b_USI>
			nXML::jE e = eLogLevel[sz];
			e.T() = false;
			e.AttrP(jS(HELP)).T() = jS(NULL);
		}
#if 0
		void _jConsolePrinterFunc( tcstr szString,bool bAdd )
		{
			DWORD writtenCount;

			if(bAdd)
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
			else
			{
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
			}
		}
#else
		void _jConsolePrinterFunc( tcstr szString,bool bAdd )
		{
			static HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
			static CONSOLE_SCREEN_BUFFER_INFO conInfo;
			static int i =0;
			if(i==0)
			{
				i=1;
				GetConsoleScreenBufferInfo(hCon,&conInfo);
			}
			vector<tstring> out;
			nString::jSplit(szString,_T("$"),out);
			DWORD writtenCount;

			if(!bAdd)
			{
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
			}
			for(size_t i=0; i< out.size(); ++i)
			{
				tcstr sz = out[i].c_str();

				if(sz[0]>=1 && sz[0]<9)
				{
					const int iden[]={
						FOREGROUND_BLUE // 0
						,FOREGROUND_GREEN // 1 
						,FOREGROUND_RED //2 
						,FOREGROUND_BLUE|FOREGROUND_INTENSITY //3 
						,FOREGROUND_GREEN|FOREGROUND_INTENSITY //4 
						,FOREGROUND_RED|FOREGROUND_INTENSITY //5 
						,FOREGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_GREEN|BACKGROUND_BLUE //6 
						,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_BLUE // 7
						,FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_RED}; //8
						int col = sz[0];
						sz = sz+1;
						SetConsoleTextAttribute(hCon, iden[col]);
				}
				else if(sz[0]==0)
				{
					sz = sz+1;
					SetConsoleTextAttribute(hCon, conInfo.wAttributes);
				}
				else
				{
					SetConsoleTextAttribute(hCon, conInfo.wAttributes);
				}
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sz, jt_strlen(sz), &writtenCount, NULL);
			}
		}
#endif
		void jPrintTOConsoleMonitorByPipe(tcstr sz, bool is)
		{
			if(g_pLog->m_pPipeWriter)
				g_pLog->m_pPipeWriter->Write(_T("%d,%s,%s"),is,g_ExeEnv.m_szAppNic, sz);
		}
		void jPrintTOConsoleMonitorBy_jOrb(tcstr sz,bool is)
		{
			if(g_pLog->m_pOrb_ConsoleMonitor)
			{
				g_pLog->m_pOrb_ConsoleMonitor->Send_H_SEND_LOG(sz,is);
			}
			else
			{
				g_pLog->m_pLogPrinter = _jConsolePrinterFunc;
			}
		}

		extern "C"
		{
			JLOG_API void* jCreateInterface(jIE* pE)
			{

				g_peDLL= pE;
				g_pLog= new jLog(pE->GetDoc());
				if(nInterface::g_pjILog)
				{
					nInterface::g_pjILog->Release();
				}
				nInterface::g_pjILog = g_pLog; 
				return nInterface::g_pjILog;
			}
			JLOG_API void jDeleteInterface()
			{
				if(g_pLog)
					g_pLog->Release();
			}
			WINDOWS_DLL_TAG tcstr jGetModuleOwnerName()
			{
				return _T("icandoit");
			}

		}

		void jIPipeWriter_OnDisconnect(nPipe::jIPipeWriter* pPipe)
		{
			g_pLog->m_isConnectpipe=false;
			g_pLog->m_pLogPrinter = _jConsolePrinterFunc;
		}

		void jLog::SetPrinter(jConsolePrinterFunc_t* pF)
		{ 
			if(!pF)
			{
				m_pLogPrinter = _jConsolePrinterFunc;

			}
			else
			{
				m_pLogPrinter = pF;
			}
		}

		//////////////////////////////////////////////////////////////////////
		jLog::jLog( jID* )
			:m_pDocLogLevel(0)
			,m_isConnectpipe(false)
			,m_pLogPrinter(0)
			,m_pPipeWriter(0)
			,m_iFlushCount(0)

		{
			try
			{
				if(pv_WriteCacheBufferSize->Get_int())
				{
					m_WriteCacheBuffer = new TCHAR[get_pv_WriteCacheBufferSize()];
					memset(m_WriteCacheBuffer,0,sizeof(TCHAR)*get_pv_WriteCacheBufferSize());
				}
				else
					m_WriteCacheBuffer=0;



				jIVar* pv_USE_PIPE = g_peDLL->GetAttrVar(jS(USE_PIPE));
				if(pv_USE_PIPE && pv_USE_PIPE->Get_bool())
					m_pPipeWriter = jCREATE_INTERFACE(nMech::nPipe::jIPipeWriter);

				if(m_pPipeWriter)
				{
					m_isConnectpipe = m_pPipeWriter->Connect(s_szPipe_ConsoleMonitor,jIPipeWriter_OnDisconnect);
				}

//				m_pValidator = new SDefaultValidator(0);
				memset(m_szFilename,0,MAX_FILENAME_SIZE);
/*
				else if( !jt_strcmp(szCon,_T("CONSOLE")))	
				{
					AllocConsole();
					jt_freopen(_T("CONOUT$"), _T("a"), stdout);
					ja_freopen("CONIN$", "r", stdin);
					SetPrinter(_jConsolePrinterFunc);
				}
				else
*/
				if(m_isConnectpipe)
				{
					SetPrinter(jPrintTOConsoleMonitorByPipe);
				}
				else
				{
					SetPrinter(_jConsolePrinterFunc);
				}

				//--------------------------------------------------------------------------
				// 로깅 파일 세팅
				//--------------------------------------------------------------------------
				pv_LogFileTag= jCV(jILog,LogFileTag,g_ExeEnv.m_szAppNic,0,"log file path");
				SetFileName(nInterface::g_pjILog->GetFileName());

				//--------------------------------------------------------------------------
				// 로깅 레벨 세팅
				//--------------------------------------------------------------------------
				m_pDocLogLevel = GetjIXml()->Load(pv_LogLevel_FILE->Get_cstr());
				if(m_pDocLogLevel)
				{
					nXML::jE e = m_pDocLogLevel;
					jIE* it = e[_T("LOG_LEVEL_LIST")]->begin();
					m_mapLogLevel.clear();
					jrFOR(it)
					{
						jLogLevelNode* pLLN = &m_mapLogLevel[it->GetTagID()];
						pLLN->m_pE = it;
						pLLN->m_pV = it->PersistAttr(_T("LevelType"),_T("LOG_OFF"));
						ELogLevelType eLType = (ELogLevelType )pLLN->m_pV->Get_StringID();
						UpdateLogLevel(it->GetTagID(), eLType);
					}
				}

			}
			catch(...)
			{
				jMB("jLog()","error");
				throw _T("jLog() error");
			}
			printf("jLog() ok\n");

		}
		int			jLog::GetWarningCount() 
		{
			return m_iWarningCount;
		}
		int			jLog::GetErrorCount()
		{
			return m_iErrorCount;
		}
		void		jLog::ResetWaringErrorCount()
		{
			m_iWarningCount = m_iErrorCount=0;
			return ;
		}

		//set the file used to log to disk
		//////////////////////////////////////////////////////////////////////
		void jLog::SetFileName(tcstr _command)
		{
			if (!_command)// 값이 NULL이면 파일이름 뒤에 1부터 해서 숫자를 붙인다.
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
			fname_t command;
			jt_strcpy(command , _command);

			std::tstring prevFile = m_szFilename;

			if(jt_strstr(command,_T(":\\")))
			{
				TCHAR* ch = jt_strstr(command, _T("_["));
				if(ch)
				{
					*ch = 0;
				}
				jt_sprintf(m_szFilename, _T("%s_%s.log"),command, g_ExeEnv.m_szRunStartTime);
			}
			else
			{
				TCHAR* ch = jt_strstr(command, _T("_["));
				if(ch)
				{
					*ch = 0;
				}

				tcstr szC = command;
				if(command[0]=='\\')
				{
					szC = command+1;
				}
				jt_sprintf(m_szFilename, _T("%s%s%s.log"),g_ExeEnv.m_szStartDir, szC,g_ExeEnv.m_szRunStartTime);
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
				{
					jt_fprintf(fp , _T("build __TIMESTAMP__=%s"),jT(__TIMESTAMP__));
					fclose(fp);
				}
			}
			//pv_LogFileTag->Set_cstr(command);
		}


		//////////////////////////////////////////////////////////////////////////
		tcstr  jLog::GetFileName()
		{
			return m_szFilename;
		}



#define jLogV_PROCESS(threadID,LogLevel,LogType,type) \
	TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE];\
	va_list args;\
	va_start(args,szFormat);\
	cstr msg = LogV( threadID,LogLevel,LogType,_szTemp234,type,szFormat,args );\
	va_end(args);

		void jLog::Warning(uint32 threadID,tcstr szFormat,...)
		{
			jLog_LOCK;

			++m_iWarningCount;
			jLogV_PROCESS(threadID,0,0,eWarning);
// 
// 			SValidatorRecord record;
// 			record.file = 0;
// 			record.text = _szTemp234;
// 			record.module = VALIDATOR_MODULE_UNKNOWN;
// 			record.severity = VALIDATOR_WARNING;
// 			record.flags = 0;
// 			m_pValidator->Report( record );

		}
		void jLog::Error(uint32 threadID,tcstr szFormat,...)
		{
			jLog_LOCK;
			++m_iErrorCount;
			jLogV_PROCESS(threadID,0,0,eERROR);
			_errorCheck(msg);
		}
		void jLog::_errorCheck(cstr msg)
		{
			if(msg==0) return;
			// get system error message before any attempt to write into log
			tcstr  szSysErrorMessage = nUtil::nWIN::GetLastSystemErrorMessage();
			//if (szSysErrorMessage )	Log( _T("Last System Error: %s"),szSysErrorMessage );

			_flush_WriteCache();

// #ifdef _DEBUG
// 			DEBUG_BREAK;
// #endif
			if( pv_ERROR_CHECK_TYPE->IsContents(_T("MSGBOX")) )
			{
				::MessageBox( NULL,msg,_T("Error"),MB_OK|MB_ICONERROR|MB_SYSTEMMODAL );
			}
			else if( pv_ERROR_CHECK_TYPE->IsContents(_T("EXIT")) )
			{
				exit(1);
			}
			else if( pv_ERROR_CHECK_TYPE->IsContents(_T("MAIL")) )
			{

			}
			else if( pv_ERROR_CHECK_TYPE->IsContents(_T("NULL")) )
			{
				return;
			}
			else if( pv_ERROR_CHECK_TYPE->IsContents(_T("DEBUG")) )
			{
				 DEBUG_BREAK;
				return;
			}
		}

		void		jLog::LogToConsole(uint32 threadID,tcstr szFormat, ...)
		{
			jLogV_PROCESS(threadID,0,0,eLogToConsole);

		}

		void jLog::Warning(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType, tcstr szFormat,...)
		{
			jLog_LOCK;
			++m_iWarningCount;

			tcstr szLevel =0, szType=0;
			if(TestLogLevel(arg_LogLevel, arg_logType,&szLevel ,&szType))
			{
				jLogV_PROCESS(threadID,szLevel,szType,eWarning);

// 				SValidatorRecord record;
// 				record.file = 0;
// 				record.text = _szTemp234;
// 				record.module = VALIDATOR_MODULE_UNKNOWN;
// 				record.severity = VALIDATOR_WARNING;
// 				record.flags = 0;
// 				m_pValidator->Report( record );

			}
		}
		void jLog::Error(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLog_LOCK;
			++m_iErrorCount;

			tcstr szLevel =0, szType=0;
			if(TestLogLevel(arg_LogLevel, arg_logType,&szLevel ,&szType))
			{
				jLogV_PROCESS(threadID,szLevel,szType,eERROR);
			}

		}
		void jLog::Log(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLog_LOCK;

			tcstr szLevel =0, szType=0;
			if(TestLogLevel(arg_LogLevel, arg_logType,&szLevel ,&szType))
			{
				jLogV_PROCESS(threadID,szLevel,szType,eLog);
			}
		}
		void jLog::LogPlus(const StringID arg_LogLevel,const StringID arg_logType,tcstr szFormat,...)
		{
			jLog_LOCK;

			tcstr szLevel =0, szType=0;
			if(TestLogLevel(arg_LogLevel, arg_logType,&szLevel ,&szType))
			{
				jLogV_PROCESS(0,szLevel,szType,eLogPlus);
			}
		}

		void jLog::Log(uint32 threadID,tcstr szFormat,...)
		{
			jLog_LOCK;

			jLogV_PROCESS(threadID,0,0,eLog);
		}
		void jLog::LogPlus(tcstr szFormat,...) 
		{
			jLog_LOCK;

			jLogV_PROCESS(0,0,0,eLogPlus);
		}
		void jLog::LogTime(uint32 threadID,tcstr szFormat,...) 
		{
			jLog_LOCK;

			jLogV_PROCESS(threadID,0,0,eLogTime);
		}

		void jLog::LogTimeTag(uint32 threadID,bool withFile)
		{
			fname_t buf;
			nTIME::Get_ITimer()->GetCurrentTimeString(buf);
			if(withFile)
			{
				_logToFile( buf,true,jx(NULL));
			}
			if (m_pLogPrinter) m_pLogPrinter(buf,true);	
		}


#define RETURN

		//////////////////////////////////////////////////////////////////////
		jLog::~jLog()
		{
			SAFE_DELETE_ARRAY(m_WriteCacheBuffer);
			SAFE_RELEASE(m_pPipeWriter);
		}
		void jLog::Release()
		{
			_flush_WriteCache();
			if(m_pDocLogLevel)
			{
				GetjIXml()->UnLoad(m_pDocLogLevel);
			}
			m_pDocLogLevel=0;

			g_pLog =0;
			delete this;
		}

		bool check_report_event_tag(tcstr szFormat, tname32_t szReportEvent)
		{
			if((szFormat)[0]!='{') return false;

			++(szFormat);
			szReportEvent[0]=0;
			if( (szFormat)[0]=='}')
				return true;

			tcstr ch = jt_strchr(szFormat, '}');
			int len = ch - szFormat;
			if(len>=31)
				return true;

			jt_strncpy(szReportEvent, szFormat,len);
			szReportEvent[len]=0;
			return true;
		}

		//will log the text both to file and console
		//////////////////////////////////////////////////////////////////////
		cstr jLog::LogV(uint32 threadID,tcstr szCurrLogLevel,tcstr szCurrLogType, TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE],ELogType type, tcstr  szFormat, va_list args )
		{
			if(pv_LOG_OFF->Get_bool() && type!=eWarning && type!=eERROR)
			{
				return 0;
			}
			const size_t TEMP_LEN = MAX_TEMP_LENGTH_SIZE;

			if (!szFormat) return _T("");
	
			TCHAR *szString=_szTemp234;
			tname32_t szReportEvent=_T("");
			nLOG::EEventType eReportType = eEL_NULL;

			size_t skipLen=0;
			size_t len=0;
			bool logPlus =false;
			bool isPrintTime=false;
			switch(type)
			{
			case eWarning:
				{
					isPrintTime= true;
					eReportType = nLOG::eEL_WARNING;
					if(check_report_event_tag(szFormat,szReportEvent))
					{
						eReportType = nLOG::eEL_WARNING;
					}

				}
				break;
			case eERROR:
				{
					isPrintTime= true;
					eReportType = nLOG::eEL_ERROR;

					if(check_report_event_tag(szFormat,szReportEvent))
					{
						eReportType = nLOG::eEL_ERROR;
					}

				}
				break;
			case eLogPlus: // LogPlus
				logPlus=true;
				break;

			case eLog:
				{
					if(szFormat[0]!=1)
					{
						isPrintTime= true;
					}
					else
					{
						++szFormat;
					}
					if(check_report_event_tag(szFormat,szReportEvent))
					{
						eReportType = nLOG::eEL_INFORMATION;
					}

					break;
				}
			case eLogTime:
				{
					isPrintTime= true;
					break;
				}
			case eLogToConsole: // LogToConsole
				{
					jt_vsnprintf( szString, TEMP_LEN-skipLen-32, szFormat, args );
					_szTemp234[TEMP_LEN-1]=0;
					_logToFile( szString ,logPlus,jx(NULL));
					if (m_pLogPrinter)
						m_pLogPrinter(_szTemp234,logPlus);
					return _szTemp234;
				}
				break;
			default:
				return 0;
				;

			}

			//--------------------------------------------------------------------------
			// 시간 태그 출력.
			//--------------------------------------------------------------------------
			if(threadID && isPrintTime)
			{
				fname_t szTimeTag;
				nTIME::Get_ITimer()->GetCurrentTimeString(szTimeTag);
				switch(type)
				{
				case eERROR:
					{
						jt_sprintf( szString,_T("\005[%s]~%05u ERROR "),szTimeTag ,threadID);
						break;
					}
				case eWarning:
					{
						jt_sprintf( szString,_T("\004[%s]~%05u WARNING "),szTimeTag,threadID );
						break;
					}
				default:
					{
						jt_sprintf( szString,_T("[%s]~%05u "),szTimeTag ,threadID);
						break;
					}
				}
				len = jt_strlen(szString);
				szString += len;
				skipLen +=len;
			}
			else
			{
				if(threadID)
				{
					jt_sprintf( szString,_T("~%05u "),threadID );
					len = jt_strlen(szString);
					szString += len;
					skipLen +=len;
				}
			}

			//--------------------------------------------------------------------------
			// 로깅 레벨 스트링 출력
			//--------------------------------------------------------------------------
			if(szCurrLogLevel)
			{
				size_t backup_skipLen= skipLen;
				skipLen += jt_strlen(szCurrLogLevel);
				if(skipLen)
				{
					jt_strncpy(_szTemp234+backup_skipLen, szCurrLogLevel, skipLen);
					if(szCurrLogType)
					{
						_szTemp234[skipLen]='}';
						++skipLen;
						size_t len = jt_strlen(szCurrLogType);
						jt_strncpy(&_szTemp234[skipLen], szCurrLogType, len);
						skipLen+=len;
					}
					_szTemp234[skipLen]='}';
					_szTemp234[skipLen+1]='}';
					skipLen+=2;
					szString +=skipLen;
				}
			}

			jt_vsnprintf( szString, TEMP_LEN-skipLen-32, szFormat, args );
			_szTemp234[TEMP_LEN-1]=0;

			if(eReportType!=eEL_NULL)
			{
				jIReportEvent* pRE = g_pReportEvent;
				if(jt_strlen(szReportEvent))
				{
					g_mapReportEvent_it it = g_mapReportEvent.find(szReportEvent);
					if(it!=g_mapReportEvent.end())
					{
						pRE = it->second;
					}
				}

				if(pRE)
				{
					pRE->Write(eReportType ,0,EVT_NORMAL, _szTemp234);
				}
			}

			_logToFile( _szTemp234 ,logPlus,jx(NULL));

			if(!pv_LOG_TO_FILE->Get_bool())
			{
				if (m_pLogPrinter)m_pLogPrinter(_szTemp234,logPlus);
			}

			return _szTemp234;
		}

		void jLog::_flush_WriteCache()
		{
			if(!m_WriteCacheBuffer) return;
			if(!m_WriteCacheBuffer[0]) return;

			tofstream of(jA(m_szFilename), ios_base::app);
			if(of.bad()) return;
			of.imbue(locale(jA(pv_file_locale->Get_cstr())));
			of << m_WriteCacheBuffer;

			memset(m_WriteCacheBuffer,0,sizeof(TCHAR)*get_pv_WriteCacheBufferSize());
#if 0			
			if(m_iFlushCount > 1000)
			{
				m_iFlushCount=0;
				SetFileName(0);
			}
#else

			of.seekp( 0, ios_base::beg );
			of.seekp( 0, ios_base::end );
			streamoff iSize = of.tellp();
			if(iSize > pv_LogFileSize->Get_int())
			{
				SetFileName(0);
			}
#endif

		}

		//////////////////////////////////////////////////////////////////////
		void jLog::_logToFile(tcstr szString,bool bAdd,StringID FileType)
		{
			if(!jt_strlen(m_szFilename)) return;
			if (!szString || !szString[0])
				return;
			if(szString[0]<=9)
				++szString ;

			if(m_WriteCacheBuffer)
			{
				int iMAX_LEN = (get_pv_WriteCacheBufferSize()-1);
				if(!bAdd) --iMAX_LEN;
				int iWriteLen = jt_strlen(szString);
				int iBuffUse = jt_strlen(m_WriteCacheBuffer);
				if( (iWriteLen + iBuffUse )  >  iMAX_LEN)
				{
					++m_iFlushCount;
					_flush_WriteCache();
					iBuffUse=0;
				}

				if(!bAdd)
				{
					jt_strcat(m_WriteCacheBuffer,_T("\n"));
				}

				if(iWriteLen >= iMAX_LEN)
				{
					tstring str = szString;
					str[iMAX_LEN]=0;
					jt_strcat(m_WriteCacheBuffer,str.c_str());
				}
				else
				{
					jt_strcat(m_WriteCacheBuffer,szString);
				}
			}
			else
			{
				tofstream of(jA(m_szFilename), ios_base::app);
				if(of.bad()) return;
				of.imbue(locale(jA(pv_file_locale->Get_cstr())));
				if(!bAdd) of << endl;
				of << szString;

				of.seekp( 0, ios_base::beg );
				of.seekp( 0, ios_base::end );
				streamoff iSize = of.tellp();
				if(iSize > pv_LogFileSize->Get_int())
				{
					SetFileName(0);
				}

			}
		}

		/* *_* by icandoit : 2006-06-13 11:02:16
		#System:UpdateLogLevel("jIInput", 1)  
		Level로깅만 허용.

		#System:UpdateLogLevel("jIInput");
		디버깅 출력.

		#System:UpdateLogLevel("jIInput",2 , "ER|CV");
		타입로깅 허용하며 타입은 ER, CV를 허용.
		*/ //*_* by icandoit : 2006-06-13 11:02:17


		bool jLog::TestLogLevel(const StringID logLevel , const StringID logType , tcstr*szLevel, tcstr*szType)
		{
			tcstr szLevel1,szType1;
			if(!m_pDocLogLevel) return false;
			if(logLevel==jx(NULL))return false;
			jLogLevelNode* pLLN = getLogLevelNode(logLevel);
			szLevel1 = pLLN? pLLN->m_pE->GetTagName():_T("NULL");
			if(szLevel) 
			{
				*szLevel = szLevel1;
			}
			if(!pLLN) 
			{
				//jWARN(_T("jLog::TestLogLevel( %s not found )"), nString::Get_jIStringTable()->GetName(logLevel));
				nXML::jE eRoot = m_pDocLogLevel->Find(jS(LOG_LEVEL_LIST));
#ifdef _DEBUG
				if(eRoot(logLevel).empty())
				{
					insert_log_level_root(eRoot,logLevel);
					m_pDocLogLevel->Save();
				}
#endif
				return false;
			}
			if(pLLN->m_eLogLevelType==eLOG_OFF) return false;

			// logType체크하지말고 logLevel조건만 맞으면 무조건 출력.
			//그러나 eLLT_OFF일때는 출력off된다.
			if(logType ==jx(NULL) || pLLN->m_eLogLevelType==eLOG_ALWAYS) 
			{
				//LogPlus(_T("%s}NULL}"),szLevel1);
				return true;
			}

			jLogLevelNode::m_LogTypeList_it it 
				= find( pLLN->m_LogTypeList.begin(), pLLN->m_LogTypeList.end() , logType);
			if(it ==pLLN->m_LogTypeList.end()) 
			{
#ifdef _DEBUG
				if(!pLLN->m_pE->Find(logType))
				{
					insert_log_level_type(pLLN->m_pE, logType);
					m_pDocLogLevel->Save();
				}
#endif
				return false;
			}
			szType1 = nString::Get_jIStringTable()->GetName(logType);
			if( szType )
				*szType = szType1;

			//LogPlus(_T("%s}%s}"),szLevel1,szType1);
			return true;
		}

		void jLog::UpdateLogLevel(const StringID logLevel,ELogLevelType isLogOn)
		{
			if(!m_pDocLogLevel) return ;
			jLogLevelNode* pLLN = getLogLevelNode(logLevel);
			if(!pLLN) return;

			pLLN->m_pV->Set_StringID( make_String(isLogOn) );
			pLLN->m_eLogLevelType = isLogOn;
			if(isLogOn == eLOG_OFF)
				return;

			pLLN->m_LogTypeList.clear();
			jIE* it = pLLN->m_pE->begin();
			jrFOR(it)
			{
				if(!it->GetVar()->Get_bool() ) continue;
				pLLN->m_LogTypeList.push_back( it->GetTagID() );
			}
			//if(!pLLN->m_LogTypeList.size()) pLLN->m_eLogLevelType = eLOG_OFF;
		}

		bool jLog::UpdateLogType(const StringID logLevel,const StringID logType, bool isLogOn)
		{
			if(!m_pDocLogLevel) return false;
			nXML::jE eRoot = m_pDocLogLevel->Find(jS(LOG_LEVEL_LIST))->Find(logLevel);
			bool isSave = false;
			if(eRoot.empty())
			{
				insert_log_level_root(m_pDocLogLevel->Find(jS(LOG_LEVEL_LIST)) , logLevel);
				eRoot =m_pDocLogLevel->Find(jS(LOG_LEVEL_LIST))->Find(logLevel);
				isSave = true;
			}
			assert(eRoot.full());
			nXML::jE e = eRoot(logType);
			bool ret = false;
			if(e.empty())
			{
				insert_log_level_type(eRoot , logType);
				e= eRoot(logType);
				isSave = true;
			}
			else
				ret = e;
			if(isSave)m_pDocLogLevel->Save();

			assert(e.full());
			if(ret == isLogOn) return ret;

			//e.M() = isLogOn;
			jLogLevelNode* pLLN = getLogLevelNode(logLevel);
			if(!pLLN) return ret;

			jLogLevelNode::m_LogTypeList_it it = jFIND(pLLN->m_LogTypeList , logType);
			if(it!=pLLN->m_LogTypeList.end())
				pLLN->m_LogTypeList.erase(it);
			return ret;
		}

		/* 입력(iWantedIndentCount) 갯수만큼 인덴트 한다. 리턴값은 현제 인덴트 적용후 전체 인덴트된 수*/
		int			jLog::PushIndent(int iWantedIndentCount)
		{

			return 0;

		}
		/* 입력iWantedIndentCount 만큼 인덴트를 제거. 만약 0이면 모든 인덴트를 제거*/
		int			jLog::PopIndent(int iWantedIndentCount)
		{
			return 0;
		}
		void		jLog::LogOff(bool is)
		{
			pv_LOG_OFF->Set_bool(is);
		}
		void		jLog::ProcessMessage(cstr szMsg,void* v)
		{
			if(tstring(_T("flush_WriteCache")) == szMsg)
			{
				_flush_WriteCache();
			}
		}
		//--------------------------------------------------------------------------
		void jLog::RunConsoleTool()
			//--------------------------------------------------------------------------
		{
			if(!nInterface::g_pjIOrb) return;

			jORB(ORB_ConsoleMonitor);
			if(pORB_ConsoleMonitor && pORB_ConsoleMonitor->IsRemoteOk()) 
			{
				HWND hWnd = pORB_ConsoleMonitor->GetRemoteWnd();
				if(hWnd)
					BringWindowToTop(hWnd);
				::ShowWindow(hWnd, SW_SHOWNORMAL);
				return;
			}
#if 0
			if(!sz || !strcmp(sz,"CONSOLE"))
			{
				/* *_* by icandoit : 2006-11-03 15:41:26

				AllocConsole();
				freopen("CONOUT$", "a", stdout);
				freopen("CONIN$", "r", stdin);
				*/ //*_* by icandoit : 2006-11-03 15:41:28

				return;
			}
#endif

			jIVar* pV = jCV(jILog,RunConsoleMonitor,true,0,"is run console monitor");
			if( !pV->Get_bool()) return;

			cstr szExe = nInterface::g_pjIOrb->GetDoc()->Find(jS(ORB_ConsoleMonitor))->GetAttr(jS(EXE));
			nFileSystem::jFolder dm;
			dm.Goto(g_ExeEnv.m_szModuleDir);
			::WinExec(jA(szExe), SW_NORMAL);
		}

		void jLog::SetReportEvent(tcstr szSourceName,struct jIReportEvent*pRE)
		{
			if(szSourceName && jt_strlen(szSourceName))
			{
				g_mapReportEvent[szSourceName] = pRE;
			}
			else
				g_pReportEvent=pRE;
		}
		jIReportEvent*	jLog::GetReportEvent(tcstr szSourceName)
		{
			if(szSourceName && jt_strlen(szSourceName))
				return g_mapReportEvent[szSourceName];
			return g_pReportEvent;
		}

		jORB_HANDLER(ORB_ConsoleMonitor , H_HELLO_OK)
		{
			if(!m_pOrb->IsRemoteServerMode()) return;
			g_pLog->m_pOrb_ConsoleMonitor = m_pOrb;
			g_pLog->m_pLogPrinter = jPrintTOConsoleMonitorBy_jOrb;
		}
		jORB_HANDLER(ORB_ConsoleMonitor,H_HELLO)
		{
			if(!m_pOrb->IsRemoteServerMode()) return;
			g_pLog->m_pOrb_ConsoleMonitor = m_pOrb;
			g_pLog->m_pLogPrinter = jPrintTOConsoleMonitorBy_jOrb;
		}
		jORB_HANDLER(ORB_ConsoleMonitor,H_DISCONNECT)
		{
			if(!m_pOrb->IsRemoteServerMode()) return;
			assert(g_pLog->m_pOrb_ConsoleMonitor==m_pOrb);
			g_pLog->m_pOrb_ConsoleMonitor=0;
		}

	}//namespace nLOG
}
