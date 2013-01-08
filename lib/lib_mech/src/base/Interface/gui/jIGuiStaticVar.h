/* file : jIGuiStaticVar.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2005-12-29 15:06:51
*/

#ifndef __jIGuiStaticVar_h__
#define __jIGuiStaticVar_h__
#pragma once

namespace nMech
{
	namespace nGUI
	{

		//#include "jIGuiStaticVar.h"

#define jINTERFACE_jIGuiStaticVar(x) public: \
	virtual jIGuiControl* BaseI() ##x \
	virtual void SetValue(jIE* pE, jIA* pA) ##x \
	virtual void SetVar(jIE* , jIA*) ##x \
	virtual jIVar* GetVar() ##x \

		jINTERFACE_END(jIGuiStaticVar);


	}
}

#endif // __jIGuiStaticVar_h__
