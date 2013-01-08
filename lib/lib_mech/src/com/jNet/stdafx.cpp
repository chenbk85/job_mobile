// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// LowLib.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.


_xmlid_LIST(jxDEFINE);

var_enum(jCV_DEFINE);


namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jNet_DLL); // 해당 DLL ,EXE 모듈마다 정의해두어야함.

}


nMech::tcstr g_szTestName =_T("DefaultSuite_jINet_OGS");

#define BOOST_TEST_MODULE DefaultSuite_jINet_OGS
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"
#include "interface/xml/jIXml.h"

void VCTESTPP_RunTest_Init()
{
	//nMech::GetjIXml();

}
