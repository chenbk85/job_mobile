#ifndef _IINPUT_H_
#define _IINPUT_H_

#ifdef WIN32
	#ifdef JC_GAMEINPUT_EXPORTS
		#define JC_GAMEINPUT_API __declspec(dllexport)
	#else
		#define JC_GAMEINPUT_API __declspec(dllimport)
	#endif
#else
	#define JC_GAMEINPUT_API
#endif
#include "Interface/jIInput.h"

//////////////////////////////////////////////////////////////////////
// Input interface for the XBox controller
//////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

struct ILog;
struct IInput;
struct ISystem;

typedef IInput  (*  JC_PTRCREATEINPUTFNC(ISystem* pSys,void* hinst, void* hwnd, bool usedinput));

JC_GAMEINPUT_API IInput *CreateInput(ISystem* pSys,void* hinst, void* hwnd, bool usedinput);

#ifdef __cplusplus
};
#endif


#endif //_IINPUT_H_