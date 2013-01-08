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
		enum ELogLevelType // jConsoleVar.xml�� <LogLevel>�� �׸� �Ӽ��� 
		{
			eLOG_OFF,
			eLOG_LEVEL, // �ش� LEVEL�� �ش��ϴ� �α��� �����ϰ� �Ѵ�. 
			// �Ϻ� �α�logName�� OFF�̸� �α�ȵ�
			eLOG_ALWAYS,// �ش� LEVEL�� �ش��ϴ� ��� �α��� ���� ���.
		};


#define jINTERFACE_jILog(x) public:	\
	virtual void		SetPrinter(nLOG::jConsolePrinterFunc_t*)  x \
	virtual void		SetFileName(tcstr command )   x \
	virtual tcstr		GetFileName()   x \
	virtual void		Release()   x \
	\
	/* �ɼǿ� ���� ������¸��Ҽ��� �ְ� ����ó���� �Ҽ��� �ִ�.*/\
	\
	virtual void		Warning(uint32 threadID,tcstr szCommand,...)  x \
	virtual void		Error(uint32 threadID,tcstr szCommand,...)  x \
	\
	/* Log("\001 test log"); 001 : �տ� Ÿ���� ��´�. �α׳���Ǿտ� [EVENT]�� ������ REPORTEVENT�� ���*/\
	virtual void		Log(uint32 threadID,tcstr szCommand,...)  x \
	\
	virtual void		LogPlus(tcstr command,...)   x \
	\
	virtual void		Warning(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType, tcstr szCommand,...)  x \
	virtual void		Error(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szCommand,...)  x \
	virtual void		Log(uint32 threadID,const StringID arg_LogLevel,const StringID arg_logType,tcstr szCommand,...)  x \
	virtual void		LogPlus(const StringID arg_LogLevel,const StringID arg_logType,tcstr command,...)   x \
	\
	/*Log()�� �����ϳ� �����ð��� �α׾տ� ���δ�. */\
	virtual void		LogTime(uint32 threadID,tcstr command,...)   x \
	/*���� �ð��� �α׷� ����Ѵ�.*/\
	virtual void		LogTimeTag(uint32 threadID,bool withFile)   x \
	\
	virtual int			GetWarningCount()   x \
	virtual int			GetErrorCount()   x \
	virtual void		ResetWaringErrorCount()   x \
	\
	/* �ܼ� �Է�â�� ������ �׸��� ���*/\
	virtual void		LogToConsole(uint32 threadID,tcstr command, ...)   x \
	\
	/* arg_logType�� �����ϸ� �ش� arg_logLevel�� [LogFlag]���� eLOG_LEVEL�̰ų� eLOG_ALWAYS�̸� ���*/\
	/*	���� : [LogFlag]�� LogLevel.xml���� �ش� logLevel�� ������ �ִ� �Ӽ���*/\
	/* arg_logType�� �����ϸ� logLevel�� [LogFlag]���� */\
	/*					eLOG_ALWAYS�̸� �׻����*/\
	/*					eLOG_LEVEL�̸� <logType>�� �Ӽ��� [ON]�� true�϶��� ���.*/\
	virtual bool		TestLogLevel(const StringID arg_LogLevel,const StringID arg_logType,tcstr*szLevel=0, tcstr*szType=0)   x \
	\
	/* UpdateLogLevelVal() -> console���� �ش� LogLevel�� ���� ����� Update��Ű�� �Լ� */ \
	virtual void		UpdateLogLevel(const StringID arg_logLeve, nLOG::ELogLevelType isLogOn)   x\
	\
	/* UpdateLogType()�� ���ϰ��� ������������ �� */\
	virtual bool		UpdateLogType(const StringID arg_logLeve,const StringID arg_logType, bool isLogOn)   x\
	\
	/* �Է�(iWantedIndentCount) ������ŭ �ε�Ʈ �Ѵ�. ���ϰ��� ���� �ε�Ʈ ������ ��ü �ε�Ʈ�� ��*/\
	virtual int			PushIndent(int iWantedIndentCount)   x \
	\
	/* �Է�iWantedIndentCount ��ŭ �ε�Ʈ�� ����. ���� 0�̸� ��� �ε�Ʈ�� ����. ��ü �ε�Ʈ�� ���� ����*/\
	virtual int			PopIndent(int iWantedIndentCount)   x \
	\
	/* warning�� error�� ������ ��� �α׸� ���� */\
	virtual void		LogOff(bool is)  x \
	virtual void		ProcessMessage(cstr szMsg,void* v)   x\

	jINTERFACE_END(jILog);

	}//namespace nLOG

	namespace nInterface
	{ 
		extern JBASE_API nLOG::jILog* g_pjILog;
	}

	extern StringID g_Current_LogLevel_jStringID; // �ش� DLL ,EXE ��⸶�� �����صξ����.

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
