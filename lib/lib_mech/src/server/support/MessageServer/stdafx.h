// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "common/jCommon.h"
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet_OGS.h"
#include "interface/net/jINet_OGS_Util.h"
#include "Interface/jIConsoleDLL.h"
#include "interface/jIConsoleCmd.h"
#include "base/jMsgManager.h"


using namespace std;
using namespace nMech;
using namespace nMech::nNET;


#define _xmlid_LIST(X)\
	X(MessageServer)\
	X(WARNING)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\

//func(FCM,game_type, 69, 0,"from SNDA DATA. FOR AQAQ.")\


var_enum(jCV_DECLARE);

// TODO: reference additional headers your program requires here
