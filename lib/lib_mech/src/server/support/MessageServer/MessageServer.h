// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MESSAGESERVER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MESSAGESERVER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif

#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

//--------------------------------------------------------------------------
class MessageServer : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern MessageServer* g_pTrServerDLL;
extern jIPlugIn_Connection* g_pCurrPlugIn;
