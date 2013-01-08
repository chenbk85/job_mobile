// jScriptLua.h: interface for the jScriptLua class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTOBJECTSCRIPT_H__2432459C_19FC_4AC4_8EAA_D73967BC4B37__INCLUDED_)
#define AFX_SCRIPTOBJECTSCRIPT_H__2432459C_19FC_4AC4_8EAA_D73967BC4B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nLUA
	{
		class jScriptLua :
			public _ScriptableEx<jScriptLua> 
		{
		public:
			jScriptLua();
			virtual ~jScriptLua();
			void Init(jILua *); 
			int LoadScript(IFunctionHandler *pH);
			int ReloadScripts(IFunctionHandler *pH);
			int ReloadScript(IFunctionHandler *pH);
			int UnloadScript(IFunctionHandler *pH);
			int DumpLoadedScripts(IFunctionHandler *pH);
			int Debug(IFunctionHandler *pH);
			int DebugFull(IFunctionHandler *pH);
			static void InitializeTemplate(jILua *pSS);

		private: // -------------------------------------------------------------------------

			//! recursive
			//! /return amount of table elements (recursive)
			DWORD Debug_Buckets_recursive( IScriptObject *pCurrent, string &sPath, std::set<const void *> &setVisited, const DWORD dwMinBucket );

			//! not recursive
			void Debug_Elements( IScriptObject *pCurrent, string &sPath, std::set<const void *> &setVisited );

			//! recursive
			void Debug_Full_recursive( IScriptObject *pCurrent, string &sPath, std::set<const void *> &setVisited );
		};

	}//nLUA_Sink
}//nMech



#endif // !defined(AFX_SCRIPTOBJECTSCRIPT_H__2432459C_19FC_4AC4_8EAA_D73967BC4B37__INCLUDED_)
