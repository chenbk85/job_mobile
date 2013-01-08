#ifndef __jLog_header__
#define __jLog_header__

//////////////////////////////////////////////////////////////////////
#define MAX_TEMP_LENGTH_SIZE	2048
#define MAX_FILENAME_SIZE			256

#include "interface\\jILog.h"
#include "interface/jIPipe.h"
#include "interface/jIOrb.h"

#ifdef JLOG_EXPORTS
#define JLOG_API WINDOWS_DLL_TAG
#else
#define JLOG_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nLOG
	{

		class jLog:	public jILog
		{
			jINTERFACE_HEADER(jILog);
		private:
			nUtil::jCriticalSection m_CS;

		private: 
			TCHAR* m_WriteCacheBuffer;
			int m_iFlushCount;
			void _flush_WriteCache();


		public:
			jLog( jID* pD);
			~jLog();
			enum ELogType
			{
				eLog,
				eWarning,
				eERROR,
				eLogPlus,
				eLogToConsole,
				eLogTime,
			};
			// interface ILog -------------------------------------------------
			jConsolePrinterFunc_t *m_pLogPrinter;
		private:

			tcstr LogV(uint32 threadID,tcstr szCurrLogLevel,tcstr szCurrLogType,TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE], ELogType ineType
				, tcstr  szFormat, va_list args );
			void _logToFile(tcstr szString,bool bAdd,StringID FileType);
			void _errorCheck(cstr msg);
			void	FormatMessage(const char *szCommand,...);


			fname_t m_szFilename;

		public:
			// checks the verbosity of the message and returns NULL if the message must NOT be
			// logged, or the pointer to the part of the message that should be logged
			//IValidator *					m_pValidator;					//!< Pointer to validator interface.

			jID* m_pDocLogLevel;
			struct jLogLevelNode
			{
				jIE* m_pE;
				jIVar * m_pV; // log type contents
				ELogLevelType m_eLogLevelType; // enum ELogLevelTypeÀÇ °ª
				jLIST_TYPEDEF_vector(StringID, m_LogTypeList);
			};
			jLIST_TYPEDEF_map(StringID,jLogLevelNode , m_mapLogLevel);
			jLogLevelNode* getLogLevelNode(StringID logLevel)
			{
				m_mapLogLevel_it it = m_mapLogLevel.find(logLevel);
				if(it == m_mapLogLevel.end()) return 0;
				return & it->second;
			}
			bool m_isConnectpipe;
			nPipe::jIPipeWriter *m_pPipeWriter;
			uint32 m_iWarningCount , m_iErrorCount;
			nORB::jIOrbNode* m_pOrb_ConsoleMonitor;


		};

		inline nMech::nXML_ORB::jIORB* jLog::GetConsoleToolORB(){ return 0;}

	}
}


#endif //__jLog_header__