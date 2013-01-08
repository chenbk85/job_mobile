// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// AqWorld.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.
_xmlid_LIST(jxDEFINE);

var_enum_ServerCommon(jCV_DEFINE);
var_enum(jCV_DEFINE);


#define BOOST_TEST_MODULE AqWorld
nMech::tcstr g_szTestName =jTEXT(BOOST_TEST_MODULE);
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"

void VCTESTPP_RunTest_Init()
{

}
jIPlugIn_Server_IOCP *g_pCurrPlugIn=0;

namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(AqWorld);
}
