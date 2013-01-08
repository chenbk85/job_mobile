/* file : PacketGenerator.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-26 10:20:16
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __PacketGenerator_header__
#define __PacketGenerator_header__
#pragma once


#define STRUCT_LIST _T("STRUCT_LIST")
#define PROTOCAL_LIST _T("PROTOCAL_LIST")
extern int g_bDebugPrint;

inline jIE* _check_type(cstr szType)
{
	static jIE* peType  = nGLOBAL::g_pDocApp->Find(_T("App_PacketGenerator"))->Find(_T("USING_TYPE"));
	return peType->Find(szType);
}

extern int _tmain_Gen_Xml(int argc, _TCHAR* argv[]);
extern void _tmain_Gen_ucd(int argc, _TCHAR* argv[]);
extern void _tmain_Gen_usd(int argc, _TCHAR* argv[]);
extern void _tmain_Gen_uss(int argc, _TCHAR* argv[]);
extern void _tmain_Gen_uad(int argc, _TCHAR* argv[]);
extern int g_bDebugPrint;


namespace nUSD_FILE
{
	extern tstring g_sTargetDir_usd ;
	extern tstring g_sTargetDir;
	extern jID* g_pDocProtocalDefine;
	extern jID* g_pDocProtocalPrototype;
};


#endif // __PacketGenerator_header__
