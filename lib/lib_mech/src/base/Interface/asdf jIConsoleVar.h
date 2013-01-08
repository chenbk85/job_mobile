/* file : jIConsoleVar.h
Coder : by icandoit (mech12@nate.com, icandoit@n_jGame_c.net)
Date : 2006-06-07 10:35:24
title : 
desc : 

*/

#ifndef __jIConsoleVar_header__
#define __jIConsoleVar_header__
#pragma once

struct ICVar;

#define     CVAR_INT    1
#define     CVAR_FLOAT  2
#define     CVAR_STRING 3

// if this flag is set during registering a console variable, and the variable exists,
// then the variable will store its value in memory given by src
#define CVF_CHANGE_SOURCE (1u<<16)

#define VF_SERVER_ONCE  			0x00000001
#define VF_CHEAT			   			0x00000002											// stays in the default state when cheats are disabled
#define VF_USERINFO     			0x00000004
#define VF_MODIFIED     			0x00000008
#define VF_SERVER       			0x00000010
#define VF_NONOTIFY     			0x00000020
#define VF_NOCHANGELEV				0x00000040
#define VF_REQUIRE_NET_SYNC		0x00000080											// cannot be changed on client and when connecting the var sent to the client
#define VF_DUMPTODISK					0x00000100
#define VF_SAVEGAME						0x00000200											// stored when saving a savegame
#define VF_NOHELP							0x00000400
#define VF_READONLY						0x00000800											// can not be changed by the user
#define VF_REQUIRE_LEVEL_RELOAD 0x00001000
#define VF_REQUIRE_APP_RESTART  0x00002000

#define jINTERFACE_jIConsoleVar(x) public:	\
	virtual ICVar *CreateVariable(const char *sName,const char *sValue,int nFlags, const char *help = "")##x \
	virtual ICVar *CreateVariable(const char *sName,int iValue,int nFlags, const char *help = "")##x \
	virtual ICVar *CreateVariable(const char *sName,float fValue,int nFlags, const char *help = "")##x \
	virtual void UnregisterVariable(const char *sVarName,bool bDelete=false) ##x \
	virtual int Register(const char *name, void  *src, float defaultvalue, int flags, int type, const char *help = "")##x \    
	virtual float Register(const char *name, float *src, float defaultvalue, int flags=0, const char *help = "")##x \    
	virtual int Register(const char *name, int   *src, float defaultvalue, int flags=0, const char *help = "")##x \    
	virtual void DumpCVars(ICVarDumpSink *pCallback,unsigned int nFlagsFilter=0 )##x \
	virtual ICVar* GetCVar( const char *name, const bool bCaseSensitive=true )##x \
	virtual char *GetVariable( const char * szVarName, const char * szFileName, const char * def_val )##x \
	virtual float GetVariable( const char * szVarName, const char * szFileName, float def_val )##x \
	virtual void AddCommand(const char *sName, const char *sScriptFunc, const DWORD indwFlags=0, const char *help = "") ##x \
	virtual void ExecuteString(const char *command,bool bNeedSlash=false,bool bIgnoreDevMode=false) ##x \
	virtual void Exit(const char *command,...) ##x \
	/* Auto completion.*/\
	virtual int		GetNumVars() ##x \
	virtual void	GetSortedVars( const char **pszArray,size_t numItems ) ##x \
	virtual const char*	AutoComplete( const char* substr ) ##x \
	virtual const char*	AutoCompletePrev( const char* substr ) ##x \
	virtual char *ProcessCompletion( const char *szInputBuffer ) ##x \
	virtual void ResetAutoCompletion()##x \
	virtual void DumpCommandsVars(char *prefix) ##x \
	/* Console variable sink. */\
	/*! Adds a new console variables sink callback. */\
	virtual void AddConsoleVarSink( IConsoleVarSink *pSink )##x \
	/*! Removes a console variables sink callback. */\
	virtual void RemoveConsoleVarSink( IConsoleVarSink *pSink )##x \
	virtual void GetMemoryUsage (nMech::jcISizer* pSizer) ##x \
	virtual bool OnBeforeVarChange( ICVar *pVar,const char *sNewValue ) ##x \;



jINTERFACE_DEFINE(jIConsoleVar);

jSINGLETON_VAR_DEC(jIConsoleVar);

#endif // __jIConsoleVar_header__
