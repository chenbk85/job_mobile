/* file : _jxCopyAttribute.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-15 19:20:56
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef ___jxCopyAttribute_header__
#define ___jxCopyAttribute_header__
#pragma once

struct _jxCopyAttributeTo
{
	nXML::jE e;
	_jxCopyAttributeTo(jIE* p):e(p){}
	void operator()(jIA* a)
	{
		a->GetVar()->CopyTo(e.AttrP(a->GetTagID()));
	}
};



#endif // ___jxCopyAttribute_header__
