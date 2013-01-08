#ifndef __jILog__header__
#define __jILog__header__

#include "header/jHeader.h"

#define JBASE_API


namespace nMech
{
	namespace nLOG
	{

		typedef void jConsolePrinterFunc_t( tcstr szString,bool bAdd );
		//////////////////////////////////////////////////////////////////////
		/*X:\xml\user\LogLevel.xml
		<LEVEL1>
		<logName1/>
		<logName2/>
		<logName3/>
		<LEVEL1>
		*/
		enum ELogLevelType // jConsoleVar.xml의 <LogLevel>의 항목 속성중 
		{
			eLOG_OFF,
			eLOG_LEVEL, // 해당 LEVEL에 해당하는 로깅이 가능하게 한다. 
			// 하부 로깅logName이 OFF이면 로깅안됨
			eLOG_ALWAYS,// 해당 LEVEL에 해당하는 모든 로깅을 강제 출력.
		};


#define jINTERFACE_jILog(x) public:	\
	virtual void		SetPrinter(nLOG::jConsolePrinterFunc_t*)  x \
	virtual void		SetFileName(tcstr command )   x \
	virtual tcstr		GetFileName()   x \
	virtual void		Release()   x \
	\
	/* 옵션에 따라 에러출력만할수도 있고 예외처리를 할수도 있다.*/\
	\
	virtual void		Warning(uint32 threadID,tcstr szCommand,...)  x \
	virtual void		Error(uint32 threadID,tcstr szCommand,...)  x \
	\
	/* Log("\001 test log"); 001 : 앞에 타임을 찍는다. 로그내용맨앞에 [EVENT]가 있으면 REPORTEVENT로 기록*/\
	virtual void		Log(uint32 threadID,tcstr szCommand,...)  x \
	\
	virtual void		LogPlus(tcstr command,...)   x \
	\
	virtual void		Warning(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType, tcstr szCommand,...)  x \
	virtual void		Error(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szCommand,...)  x \
	virtual void		Log(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szCommand,...)  x \
	virtual void		LogPlus(const StringID arg_LogLevel,const StringID arg_logType,tcstr command,...)   x \
	\
	/*Log()와 동일하나 현제시간을 로그앞에 붙인다. */\
	virtual void		LogTime(uint32 threadID,tcstr command,...)   x \
	/*현재 시간만 로그로 출력한다.*/\
	virtual void		LogTimeTag(uint32 threadID,bool withFile)   x \
	\
	virtual int			GetWarningCount()   x \
	virtual int			GetErrorCount()   x \
	virtual void		ResetWaringErrorCount()   x \
	\
	/* 콘솔 입력창이 있으면 그리로 출력*/\
	virtual void		LogToConsole(uint32 threadID,tcstr command, ...)   x \
	\
	/* arg_logType을 생략하면 해당 arg_logLevel의 [LogFlag]값이 eLOG_LEVEL이거나 eLOG_ALWAYS이면 출력*/\
	/*	참고 : [LogFlag]는 LogLevel.xml에서 해당 logLevel이 가지고 있는 속성값*/\
	/* arg_logType을 지정하면 logLevel의 [LogFlag]값이 */\
	/*					eLOG_ALWAYS이면 항상출력*/\
	/*					eLOG_LEVEL이면 <logType>의 속성값 [ON]이 true일때만 출력.*/\
	virtual bool		TestLogLevel(const StringID arg_LogLevel,const StringID arg_logType,tcstr*szLevel=0, tcstr*szType=0)   x \
	\
	/* UpdateLogLevelVal() -> console에서 해당 LogLevel의 값을 변경시 Update시키는 함수 */ \
	virtual void		UpdateLogLevel(const StringID arg_logLeve, nLOG::ELogLevelType isLogOn)   x\
	\
	/* UpdateLogType()의 리턴값은 이전수정전의 값 */\
	virtual bool		UpdateLogType(const StringID arg_logLeve,const StringID arg_logType, bool isLogOn)   x\
	\
	/* 입력(iWantedIndentCount) 갯수만큼 인덴트 한다. 리턴값은 현재 인덴트 적용후 전체 인덴트된 수*/\
	virtual int			PushIndent(int iWantedIndentCount)   x \
	\
	/* 입력iWantedIndentCount 만큼 인덴트를 제거. 만약 0이면 모든 인덴트를 제거. 전체 인덴트된 수를 리턴*/\
	virtual int			PopIndent(int iWantedIndentCount)   x \
	\
	/* warning과 error를 제외한 모든 로그를 끈다 */\
	virtual void		LogOff(bool is)  x \
	virtual void		ProcessMessage(cstr szMsg,void* v)   x\

	jINTERFACE_END(jILog);

	}//namespace nLOG

	namespace nInterface
	{ 
		extern JBASE_API nLOG::jILog* g_pjILog;
	}

	extern StringID g_Current_LogLevel_jStringID; // 해당 DLL ,EXE 모듈마다 정의해두어야함.

#define jLogT(type) GetCurrentThreadId(),g_Current_LogLevel_jStringID,jx(type)
#define jLogL GetCurrentThreadId(),g_Current_LogLevel_jStringID,jx(NULL)

#define IF_jILogT(type) if(nMech::nInterface::g_pjILog->TestLogLevel(jLogT(type) ) )
#define IF_jILogLT(level,type) if( nMech::nInterface::g_pjILog->TestLogLevel(jx(level),jx(type)  ) )
#define IF_jILogLT_(level,type) if( nMech::nInterface::g_pjILog->TestLogLevel(level,type  ) )

#define GetjILog() if(nMech::nInterface::g_pjILog)nMech::nInterface::g_pjILog

#ifndef jIF_LOG
#ifdef _DEBUG
	#define jIF_LOG(type) if(nMech::nInterface::g_pjILog && nMech::nInterface::g_pjILog->TestLogLevel(g_Current_LogLevel_jStringID,type)  )
#else
	#define jIF_LOG(type) if(0)
#endif //_DEBUG
#endif //jIF_LOG


}//namespace nMech



#endif //__jILog__header__
