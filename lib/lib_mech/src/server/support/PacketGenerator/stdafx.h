// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <iostream>


#include "common/jCommon.h"
#include "interface/ITimer.h"
//#include "jCommon.h"
//#include "jInit.h"
using namespace nMech;
using namespace nMech::nFileSystem;

#include "interface/xml/jIXml.h"



#include "header/jBoost.h"
#include "PacketGenerator.h"

// net packet  xml 생성옵션
const int ARG_SOCKET = 1;
const int ARG_HEADER_XML_FILE = 2;
const int ARG_CREATE_TAG = 3;
const int ARG_TEXT_EDITOR = 4;
const int ARG_NET_MAX = 4;




using namespace std;



#define _xmlid_LIST(X)\
	X(PacketGenerator)\

_xmlid_LIST(jxDECL);

extern tstring m_sTabBuf;
inline void ClearTab(){m_sTabBuf.clear();}
inline void AddTab(){m_sTabBuf+=_T("\t");}
inline void DecTab(){m_sTabBuf.erase(m_sTabBuf.begin());}
inline tstring& Tab(){ return m_sTabBuf; }

struct AutoTab
{
	AutoTab(){ AddTab();}
	~AutoTab(){DecTab();}
};

#define _jF(X) endl<<Tab()<< boost::tformat(_T(X))
#define _jT(X) endl<<Tab()<< _T(X)


#define __jF(X) boost::tformat(_T(X))


#define var_enum(func)\
func(App_PacketGenerator,jNOTUSE_PACKET_HPP_INCLUDE, _T("jNOTUSE_PACKET_HPP_INCLUDE"), 0,"패킷 해더들을 INCLUDE시킬지")\
func(App_PacketGenerator,jNOTUSE_SQ_CODE, _T("jNOTUSE_SQ_CODE"), 0,"SQURREL코드를 제외할 구문에 대한 #define 이름")\
func(App_PacketGenerator,jNOT_USE_PACKET_PLUGIN_HELP, _T("jNOT_USE_PACKET_PLUGIN_HELP"), 0,"g_pPlugInHelpTableList를 생성할지에대한 #define 이름")\
func(App_PacketGenerator,jNOTUSE_PACKET_JXDEFINE, _T("jNOTUSE_PACKET_JXDEFINE"), 0,"jxDEFINE코드를 제외할 구문에 대한 #define 이름")\
func(Squirrel,ScriptSide_SendBufSize,jS(1024),0,"SQ바인드코드에서 WritePacket시 임시버퍼크기")\
func(App_PacketGenerator,Use_Squirrel,true,0,"스컬럴스크립트 지원여부")\
func(App_PacketGenerator,loglevel_file,_T("xml\\user\\loglevel.xml"), 0 ,"패킷생성시 로그레벨에 패킷이름을 추가시킴")\
func(App_PacketGenerator,Server_TAG,_T("NET"),0,"코드생성시 사용될 고유 테그명,jxDECL_%1%(),n%1%_Debug::jDebugPrint()등에 사용")\
func(App_PacketGenerator,file_locale,_T("korean"),0,"file locale ")

var_enum(jCV_DECLARE);

extern tcstr g_szName_HEADER_NameSpace;
// 해더를 포함한 pVar스트링문자를 리턴
inline tstring GetVar_HEADER(jIVar* pVar)
{
	fname_t buf;
	return tstring(g_szName_HEADER_NameSpace) +tstring(_T("_"))+ pVar->ToString(buf);
}
#define GET_VAR(var) GetVar_HEADER(pv_##var)


extern bool is_char_type(jIVar* pvT);
extern bool is_mystring_type(jIVar* pV);
