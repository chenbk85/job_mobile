/* file : jIGuiCheckBox.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2005-12-29 10:39:30
*/

#ifndef __jIGuiCheckBox_h__
#define __jIGuiCheckBox_h__
#pragma once

namespace nMech
{
	namespace nGUI
	{

#define jINTERFACE_jIGuiCheckBox(x) public:	\
	virtual jIGuiControl* BaseI() ##x \
	virtual int GetChecked() ##x \
	virtual void SetChecked(bool) ##x \

		jINTERFACE_END(jIGuiCheckBox);

	}
}

#endif // __jIGuiCheckBox_h__
