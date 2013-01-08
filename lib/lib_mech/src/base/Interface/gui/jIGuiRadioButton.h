/* file : jIGuiRadioButton.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2006-01-16 11:20:47
*/

#ifndef __jIGuiRadioButton_h__
#define __jIGuiRadioButton_h__
#pragma once
namespace nMech
{
	namespace nGUI
	{

		struct jIGuiCheckBox;

#define jINTERFACE_jIGuiRadioButton(x) public:	\
	virtual jIGuiCheckBox* BaseICheck() ##x \
	virtual void ISetChecked( bool bChecked, bool bClearGroup) ##x \
	virtual void ISetChecked( bool bChecked) ##x \
	virtual int IGetChecked() ##x \

		jINTERFACE_END(jIGuiRadioButton);

	}
}

#endif // __jIGuiRadioButton_h__
