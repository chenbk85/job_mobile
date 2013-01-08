#ifndef __base_Log_header__
#define __base_Log_header__

//////////////////////////////////////////////////////////////////////
#define MAX_TEMP_LENGTH_SIZE	2048
#define MAX_FILENAME_SIZE			256

#include "jILog.h"

#ifdef JLOG_EXPORTS
#define JLOG_API __declspec(dllexport)
#else
#define JLOG_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nLOG
	{

		class jBase_Log:	public jILog
		{
			jINTERFACE_HEADER(jILog);
		public:
			jBase_Log();
			enum ELogType
			{
				eLog,
				eWarning,
				eERROR,
				eLogPlus,
				eLogToConsole,
				eLogTime,
			};
		private:

			tcstr LogV(tcstr szCurrLogLevel,tcstr szCurrLogType,TCHAR _szTemp234[MAX_TEMP_LENGTH_SIZE], ELogType ineType
				, tcstr  szFormat, va_list args );
			void _logToFile(tcstr szString,bool bAdd);
			void _errorCheck(cstr msg);
			void	FormatMessage(const char *szCommand,...);
			fname_t m_szFilename;
			jConsolePrinterFunc_t *m_pLogPrinter;

		public:
			uint32 m_iWarningCount , m_iErrorCount;
		};

		inline void jBase_Log::SetPrinter(jConsolePrinterFunc_t* pF){ m_pLogPrinter = pF;}

	}
}


#endif //__base_Log_header__
