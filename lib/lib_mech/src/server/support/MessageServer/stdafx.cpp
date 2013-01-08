// stdafx.cpp : source file that includes just the standard includes
// MessageServer.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
_xmlid_LIST(jxDEFINE);

var_enum(jCV_DEFINE);

#define BOOST_TEST_MODULE MessageServer
nMech::tcstr g_szTestName =jTEXT(BOOST_TEST_MODULE);
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"

void VCTESTPP_RunTest_Init()
{

}
jIPlugIn_Server_IOCP *g_pCurrServerPlugIn=0;
int MAX_PUBLIC_CHATROOM = 0;	// ypqp35  [2008/11/12] 서버당 공개용채팅방 갯수

namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(MessageServer);
}
