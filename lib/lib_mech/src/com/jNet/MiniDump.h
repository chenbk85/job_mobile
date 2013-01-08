/* file : MiniDump.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:50:25
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __MiniDump_header__
#define __MiniDump_header__
#pragma once

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			class CMiniDump
			{
			public:
				static BOOL Begin(VOID);
				static BOOL End(VOID);
			};

		}// nNet::nUTIL

	} //nNET
}//nMech



#endif // __MiniDump_header__

