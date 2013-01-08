/* file : Base64.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 16:56:07
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Base64_header__
#define __Base64_header__
#pragma once

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
			void		Base64Encode( LPCSTR data, int size, LPSTR output, int bufLen );
			void		Base64Decode( LPCSTR data, int size, LPSTR output, int bufLen );
		}
	}
}



#endif // __Base64_header__


