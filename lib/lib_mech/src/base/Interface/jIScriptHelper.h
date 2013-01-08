/* file : jIScriptHelper.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-16 12:19:29
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jIScriptHelper_headerasdfasdfkl__
#define __jIScriptHelper_headerasdfasdfkl__
#pragma once

namespace nMech
{
	#define jINTERFACE_jIScriptHelper(X) public:	\
		virtual jID*	GetDoc() ##X \
		\
		virtual void	BeginClass(tcstr szClass) ##X \
		virtual void  RegistFuncHelp(tcstr szFunc,tcstr szArg, tcstr szHelp , tcstr szOpt) ##X \
		virtual void  RegistVarHelp(tcstr szVar,tcstr szHelp , tcstr szOpt) ##X \
		virtual void	EndClass() ##X \
		\
		virtual void	BeginEnum(tcstr szEnumName) ##X \
		virtual void  RegistEnumHelp(tcstr szScope, tcstr szEnum, tcstr szHelp ) ##X \
		\
		virtual void	RegistEnumTable_ToEnumRoot(tcstr szScope, tcstr szHelp ) ##X \
		virtual void  RegistEnumField_ToEnumRoot(tcstr szScope, tcstr szEnum, int iVal,tcstr szHelp ) ##X \
		\
		virtual void	RegistGlobalVar(tcstr szCppVar, tcstr scriptVar) ##X \
		virtual void	End() ##X\

	jINTERFACE_END(jIScriptHelper);

	extern JBASE_API nMech::jIScriptHelper* Get_jIScriptHelper();


}

#endif // __jIScriptHelper_headerasdfasdfkl__
