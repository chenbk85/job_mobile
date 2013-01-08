/* file : jIDebugCallStack.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-23 14:31:14
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jIDebugCallStack_header__
#define __jIDebugCallStack_header__
#pragma once

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
			struct ISystemUserCallback
			{
				/** Signals to User that engine error occured.
				@return true to Halt execution or false to ignore this error.
				*/
				virtual bool OnError( const char *szErrorString ) = 0;
				/** If working in Editor environment notify user that engine want to Save current document.
				This happens if critical error have occured and engine gives a user way to save data and not lose it
				due to crash.
				*/
				virtual void OnSaveDocument() = 0;
				/** Notify user that system wants to switch out of current process.
				(For ex. Called when pressing ESC in game mode to go to Menu).
				*/
				virtual void OnProcessSwitch() = 0;
			};
#define jINTERFACE_jIDebugCallStack(x) public:	\
	virtual void  Init()##x\
	virtual void  LogCallstack()##x\
	virtual void  SetExitUserCallback(ISystemUserCallback*)##x \
	virtual void  AddUserModule(acstr szOwner , acstr szModule)##x \
	virtual bool  SaveDumpFile(OUT aname1024_t szFilePath, EXCEPTION_POINTERS*exceptionInfo) ##x\
	virtual int	  handleException( void *exception_pointer ) ##x \

			jINTERFACE_END_BASE1(jIDebugCallStack, nInterface::jIInterface);

			// *_* by icandoit : 2007-07-23 14:32:01
			// »ç¿ë¹ý
			// jIDebugCallStack* pjIDebugCallStack = jCREATE_INTERFACE(nMech::nUtil::nDebug::jIDebugCallStack);

		}// nDebug

	}//nUtil

}


#endif // __jIDebugCallStack_header__
