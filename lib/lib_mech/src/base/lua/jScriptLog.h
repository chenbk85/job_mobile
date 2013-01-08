/* file : jScriptLog.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-06 22:00:06
title : 
desc : 

*/

#ifndef __jScriptLog_headerasdf232deg3445__
#define __jScriptLog_headerasdf232deg3445__
#pragma once


#include <header\\_ScriptableEx.h>

/*! This class implements script-functions for exposing the scripting system functionalities

REMARKS:
After initialization of the script-object it will be globally accessable through scripts using the namespace "Script".

Example:
Script.LoadScript("scripts/common.lua")

IMPLEMENTATIONS NOTES:
These function will never be called from C-Code. They're script-exclusive.
*/

namespace nMech
{
	namespace nLUA
	{
		class jScriptLog :
			public _ScriptableEx<jScriptLog> 
		{
		public:
			jScriptLog();
			virtual ~jScriptLog();
			void Init(jILua *); 
			static void InitializeTemplate(jILua *pSS);

			int Log(IFunctionHandler *pH); // void (string))
			int LogAlways(IFunctionHandler *pH); // void (string))
			int Warning(IFunctionHandler *pH); //string (return void)
			int Error(IFunctionHandler *pH); //string (return void)
			int RunTool(IFunctionHandler *pH);
		private:
			void LogString(IFunctionHandler *pH,bool bToConsoleOnly);

		};


	}//nLUA_Sink
}//nMech



#endif // __jScriptLog_headerasdf232deg3445__
