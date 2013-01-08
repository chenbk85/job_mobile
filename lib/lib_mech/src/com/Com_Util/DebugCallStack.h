////////////////////////////////////////////////////////////////////////////
//
//  jGame Engine Source File.
//  Copyright (C), jGame Studios, 2001.
// -------------------------------------------------------------------------
//  File name:   jDebugCallStack.h
//  Version:     v1.00
//  Created:     3/12/2001 by Timur.
//  Compilers:   Visual C++ 6.0
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef __DebugCallStack_h__
#define __DebugCallStack_h__

#if _MSC_VER > 1000
#pragma once
#endif


#include "interface/jIDebugCallStack.h"
namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
#ifdef WIN32

			//! Limits the maximal number of functions in call stack.
#define MAX_PATH_LENGTH 1024
#define MAX_SYMBOL_LENGTH 512
			const int MAX_DEBUG_STACK_ENTRIES = 32;
			//!============================================================================
			//!
			//! jDebugCallStack class, capture call stack information from symbol files.
			//!
			//!============================================================================

			class jDebugCallStack : public jIDebugCallStack
			{
				jINTERFACE_HEADER(jIInterface);
				jINTERFACE_HEADER(jIDebugCallStack);

				static void PutVersion( char *str );

			public:

				void	updateCallStack();

				//! Get current call stack information.
				void getCallStack( std::vector<std::string> &functions );

				void dumpCallStack( std::vector<std::string> &functions );

				//! Return name of module where exception happened.
				const char* getExceptionModule() { return m_excModule; }
				const char* getExceptionLine() { return m_excLine; }

				typedef void (*ErrorCallback)( const char* description,const char* value );

				void registerErrorCallback( ErrorCallback call );
				void unregisterErrorCallback( ErrorCallback call );

				std::list<ErrorCallback> m_errorCallbacks;
			public:
				jDebugCallStack();
				virtual ~jDebugCallStack();

				bool initSymbols();
				void doneSymbols();

				std::string	LookupFunctionName( void *adderss,bool fileInfo );
				int			updateCallStack( void *exception_pointer );
				void		FillStackTrace( DWORD64 eip,DWORD64 esp,DWORD64 ebp,PCONTEXT pContext=NULL );

				static	int unhandledExceptionHandler( void *exception_pointer );

				std::vector<std::string> m_functions;

				char m_excLine[256];
				char m_excModule[128];

				void *prevExceptionHandler;

				bool	m_symbols;
			};

#endif //WIN32



		}
	}
}


#endif // __DebugCallStack_h__