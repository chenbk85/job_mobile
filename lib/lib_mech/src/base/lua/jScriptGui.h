/* file : jScriptGui.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-23 17:48:41
title : 
desc : 

*/

#ifndef __jScriptGui_header__
#define __jScriptGui_header__
#pragma once
namespace nMech
{
	namespace nLUA
	{

		class jScriptGui :
			public _ScriptableEx<jScriptGui> 
		{
		public:
			void Init(jILua *); 
			static void InitializeTemplate(jILua *pSS);

			//--------------------------------------------------------------------------
			// jIGui
			//--------------------------------------------------------------------------
#define __jIGui_lau_function_list__(x) \
	x(Help)\
	x(ChangeStage)\
	x(SetScriptEvent)\
	x(SetCursorShow)\
	x(IsEnable)\
	x(DrawText)\
	/* jGuiControl*/\
	x(GetClassType)\
	x(GetTypeName)\
	x(GetName)\
	x(Refresh)\
	x(CanHaveFocus)\
	x(OnFocusIn)\
	x(OnFocusOut)\
	x(OnMouseEnter)\
	x(OnMouseLeave)\
	x(GetCtrlAtPt)\
	x(ContainsPoint)\
	x(GetRect)\
	x(SetTextColor)\
	x(GetCtrl)\
	x(GetParent)\
	x(Find)\
	x(GetDlg)\
	x(GetCustomProperty)\
	x(SetCustomProperty)\
	x(SetMouseInput)\
	x(IsMouseInput)\
	x(SetEnabled)\
	x(GetEnable)\
	x(SetVisible)\
	x(GetVisible)\


#define jIGui_lua_func_def(x) int x(IFunctionHandler *pH);
			__jIGui_lau_function_list__(jIGui_lua_func_def);

		};


	}//nLUA_Sink
}//nMech



#endif // __jScriptGui_header__
