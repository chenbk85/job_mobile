#ifndef __jLog_header__
#define __jLog_header__

//////////////////////////////////////////////////////////////////////
#define MAX_TEMP_LENGTH_SIZE	2048
#define MAX_FILENAME_SIZE			256

#include "interface\\jILog.h"

#ifdef JCOM_UTIL_EXPORTS
#define JCOM_UTIL_API WINDOWS_DLL_TAG
#else
#define JCOM_UTIL_API __declspec(dllimport)
#endif
//////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nUtil
	{
	}
}


#endif //__jLog_header__