/* file : jIGuiScrollBar.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-28 11:05:12
title : 
desc : 

*/

#ifndef __jIGuiScrollBar_header__
#define __jIGuiScrollBar_header__
#pragma once

namespace nMech
{
	namespace nGUI
	{

#define jINTERFACE_jIGuiScrollBar(x) public:	\
	virtual jIGuiControl* BaseI() ##x \
	virtual void SetTrackRange( int nStart, int nEnd ) ##x \
	virtual int GetTrackPos() ##x \
	virtual void SetTrackPos( int nPosition ) ##x \
	virtual int GetPageSize() ##x \
	virtual void SetPageSize( int nPageSize ) ##x \
	virtual void Scroll( int nDelta ) ##x \
	/* Scroll by nDelta items (plus or minus) */ \
	virtual void ShowItem( int nIndex ) ##x \
	/* Ensure that item nIndex is displayed, scroll if necessary*/\

		jINTERFACE_END(jIGuiScrollBar);


	}
}


#endif // __jIGuiScrollBar_header__
