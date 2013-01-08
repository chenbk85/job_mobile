#ifndef _jI234903287598ksdkauewiCONSOLE_H_
#define _jI234903287598ksdkauewiCONSOLE_H_

#ifdef JCONSOLE_EXPORTS
#define JCONSOLE_API __declspec(dllexport)
#else
#define JCONSOLE_API __declspec(dllimport)
#endif

namespace nMech
{
	namespace nCONSOLE
	{
		struct ICVar;

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

		struct ICVarDumpSink
		{
			virtual void OnElementFound(ICVar *pCVar) = 0;
		};

		struct IKeyBindDumpSink
		{
			virtual void OnKeyBindFound( tcstr sBind,tcstr sCommand ) = 0;
		};

		struct IOutputPrintSink
		{
			virtual void Print( tcstr inszText )=0;
		};

		//! Callback class to derive from when you want to recieve callbacks when console var changes.
		struct IConsoleVarSink
		{
			//! Called by Console before changing console var value, to validate if var can be changed.
			//! @return true if ok to change value, false if should not change value.
			virtual bool OnBeforeVarChange( ICVar *pVar,tcstr sNewValue ) = 0;
		};

		/*! Interface to the engine console.

		The engine console allow to manipulate the internal engine parameters
		and to invoke commands.
		This interface allow external modules to integrate their functionalities
		into the console as commands or variables.

		IMPLEMENTATIONS NOTES:
		The console takes advantage of the script engine to store the console variables,
		this mean that all variables visible through script and console.

		*/ 
		typedef void jNetGameRefreshFunc_t(ICVar*);


#define jINTERFACE_jIConsole(x) public:	\
	/*! delete the variable	NOTE: the variable will automatically unregister itself from the console*/ \
	virtual void Release() ##x \
	virtual ICVar *CreateVariable(cstr sName,cstr sValue,int nFlags, cstr help = _T("") )##x \
	virtual ICVar *CreateVariable(cstr sName,int iValue,int nFlags, cstr help = _T("") )##x \
	virtual ICVar *CreateVariable(cstr sName,float fValue,int nFlags, cstr help = _T("") )##x \
	virtual void UnregisterVariable(tcstr sVarName,bool bDelete=false) ##x\
	/*! Set the y coordinate where the console will stop to scroll when is dropped\
		@param value y in screen coordinates*/\
		virtual void AddOutputPrintSink( nCONSOLE::IOutputPrintSink *inpSink )##x \
		/*! remove output sink (clases which are interested in the output) - order is not guaranteed\
		@param inpSink must not be 0 and has to be added before	*/\
		virtual void RemoveOutputPrintSink( nCONSOLE::IOutputPrintSink *inpSink )##x \
		/*! show/hide the console\
		@param specifies if the window must be (true=show,false=hide) 	*/\
		virtual void DumpCVars(nCONSOLE::ICVarDumpSink *pCallback,unsigned int nFlagsFilter=0 )##x \
		/*! Bind a console command to a key\
		@param sCmd console command that must be executed\
		@param sRes name of the key to invoke the command\
		@param bExecute legacy parameter(will be removed soon)	*/\
		virtual void CreateKeyBind(tcstr sCmd,tcstr sRes,bool bExecute)##x \
		/*! Retrieve a console variable by name\
		@param sName variable name\
		@param bCaseSensitive true=faster, false=much slower but allowes names with wrong case (use only where performce doesn't matter)\
		@return a pointer to the ICVar interface, NULL if is not found		@see ICVar	*/\
		virtual ICVar* GetCVar( tcstr name, const bool bCaseSensitive=true )##x \
		virtual jIVar* jGetVar( tcstr name)##x \
		/*! Execute a string in the console	\
		@param command console command	*/\
		virtual void ExecuteString(tcstr command,bool bNeedSlash=false,bool bIgnoreDevMode=false) ##x \
		/*! Print a message into the log and abort the execution of the application\
		@param message error string to print in the log	*/\
		virtual void Exit(tcstr command,...) ##x \
		/* Auto completion. */\
		virtual int		GetNumVars() ##x \
		virtual void	GetSortedVars( void*pszArray) ##x \
		virtual cstr 	AutoComplete( tcstr substr ) ##x \
		virtual cstr 	AutoCompletePrev( tcstr substr ) ##x \
		virtual tcstr ProcessCompletion( tcstr szInputBuffer ) ##x \
		virtual void ResetAutoCompletion()##x \
		virtual void DumpCommandsVars(tcstr prefix) ##x \
		/*! Calculation of the memory used by the whole console system*/\
		virtual void GetMemoryUsage (jcISizer* pSizer) ##x \
		/*! Dump all key bindings to a callback-interface\
		@param Callback callback-interface which needs to be called for each element	*/\
		virtual void DumpKeyBinds(nCONSOLE::IKeyBindDumpSink *pCallback )##x \
		virtual tcstr FindKeyBind( tcstr sCmd ) ##x \
		/* Console variable sink.*/\
		/*! Adds a new console variables sink callback.*/\
		virtual void AddConsoleVarSink( nCONSOLE::IConsoleVarSink *pSink )##x \
		/*! Removes a console variables sink callback.*/\
		virtual void RemoveConsoleVarSink( nCONSOLE::IConsoleVarSink *pSink )##x \
		virtual void RefreshVariable(cstr sVarName)##x \
		virtual float Register(tcstr name, float *src, float defaultvalue, int flags=0, tcstr help = _T(""))##x \
		virtual int Register(tcstr name, int   *src, float defaultvalue, int flags=0, tcstr help = _T(""))##x  \
		virtual void AddCommand(tcstr sName, tcstr sScriptFunc, const DWORD indwFlags=0, tcstr help = _T(""))##x \
		virtual bool OnInputEvent( const nINPUT::SInputEvent &event )##x \
		virtual nCONSOLE::jNetGameRefreshFunc_t* Set_NetGameRefreshFunc(nCONSOLE::jNetGameRefreshFunc_t*)##x \

		jINTERFACE_END(jIConsole);

		//! this interface is the 1:1 "C++ representation"
		//! of a console variable.
		//! NOTE: a console variable is accessible in C++ trough
		//! this interface and in all scripts as global variable
		//! (with the same name of the variable in the console)

#define jINTERFACE_ICVar(x) public:	\
	/*! delete the variable\
		NOTE: the variable will automatically unregister itself from the console\
		*/\
		virtual void Release() ##x \
		\
		/*! Return the integer value of the variable\
		@return the value\
		*/\
		virtual int GetIVal() ##x \
		\
		/*! Return the float value of the variable\
		@return the value\
		*/\
		virtual float GetFVal() ##x \
		\
		/*! Return the string value of the variable\
		@return the value\
		*/\
		virtual TCHAR *GetString() ##x \
		\
		/*! set the string value of the variable\
		@param s string representation the value\
		*/\
		virtual void Set(tcstr s)##x \
		\
		/*! Force to set the string value of the variable - can be called \
		from inside code only\
		@param s string representation the value\
		*/\
		virtual void ForceSet(tcstr s)##x \
		\
		/*! set the float value of the variable\
		@param s float representation the value\
		*/\
		virtual void Set(float f)##x \
		\
		/*! set the float value of the variable\
		@param s integer representation the value\
		*/\
		virtual void Set(int i)##x \
		\
		/*! refresh the values of the variable\
		*/\
		virtual void Refresh()##x \
		\
		/*! clear the specified bits in the flag field\
		*/\
		virtual void ClearFlags (int flags)##x \
		\
		/*! return the variable's flags \
		@return the variable's flags\
		*/\
		virtual int GetFlags()##x \
		\
		/*! Set the variable's flags \
		*/\
		virtual int SetFlags( int flags )##x \
		\
		/*! return the primary variable's type\
		@return the primary variable's type\
		*/\
		virtual int GetType()##x \
		\
		/*! return the variable's name\
		@return the variable's name\
		*/\
		virtual tcstr GetName()##x \
		\
		/*! return the variable's name\
		@return the variable's name\
		*/\
		virtual tcstr GetHelp()##x \

		jINTERFACE_END(ICVar);
	}//namespace nCONSOLE
	namespace nInterface
	{
		extern JBASE_API nCONSOLE::jIConsole* g_pjIConsole;
	}
}


#endif //_jI234903287598ksdkauewiCONSOLE_H_
