/* file : jIGuiSlider.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2005-12-29 10:27:42
*/

#ifndef __jIGuiSlider_h__
#define __jIGuiSlider_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nGUI
	{

#define jINTERFACE_jIGuiSlider(x) public: \
	virtual jIGuiControl* BaseI() ##x \
	virtual void SetRange( int nMin, int nMax ) ##x \
	virtual int GetValue() ##x \
	virtual int GetMin() ##x \
	virtual int GetMax() ##x \
	virtual void SetValue( int nValue ) ##x \

		jINTERFACE_END(jIGuiSlider);

	}
}

#endif //__jIGuiSlider_h__
