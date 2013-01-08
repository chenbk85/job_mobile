
#if !defined( __CAIRO_CORELIB_MINIDUMP_LIBRARY__ )
#define       __CAIRO_CORELIB_MINIDUMP_LIBRARY__


#pragma pack(push, exception)
#pragma pack(8)

//
//#include < Common/BaseDef.h >
///////////////////////////////////////////////////////////////////////////////////////////////////

// Standard ///////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include < time.h >
#include < dbghelp.h >
///////////////////////////////////////////////////////////////////////////////////////////////////



#pragma comment (lib, "dbghelp.lib")
#pragma pack(pop, exception)

namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{
			class JUTIL_API  CStackDumper
			{
			public :
				CStackDumper		();
				~CStackDumper		();
			};

		}// nDB
	}// nUTIL
}// nMech





#endif