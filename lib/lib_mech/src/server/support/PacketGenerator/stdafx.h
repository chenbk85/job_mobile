// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
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

// net packet  xml �����ɼ�
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
func(App_PacketGenerator,jNOTUSE_PACKET_HPP_INCLUDE, _T("jNOTUSE_PACKET_HPP_INCLUDE"), 0,"��Ŷ �ش����� INCLUDE��ų��")\
func(App_PacketGenerator,jNOTUSE_SQ_CODE, _T("jNOTUSE_SQ_CODE"), 0,"SQURREL�ڵ带 ������ ������ ���� #define �̸�")\
func(App_PacketGenerator,jNOT_USE_PACKET_PLUGIN_HELP, _T("jNOT_USE_PACKET_PLUGIN_HELP"), 0,"g_pPlugInHelpTableList�� �������������� #define �̸�")\
func(App_PacketGenerator,jNOTUSE_PACKET_JXDEFINE, _T("jNOTUSE_PACKET_JXDEFINE"), 0,"jxDEFINE�ڵ带 ������ ������ ���� #define �̸�")\
func(Squirrel,ScriptSide_SendBufSize,jS(1024),0,"SQ���ε��ڵ忡�� WritePacket�� �ӽù���ũ��")\
func(App_PacketGenerator,Use_Squirrel,true,0,"���÷���ũ��Ʈ ��������")\
func(App_PacketGenerator,loglevel_file,_T("xml\\user\\loglevel.xml"), 0 ,"��Ŷ������ �α׷����� ��Ŷ�̸��� �߰���Ŵ")\
func(App_PacketGenerator,Server_TAG,_T("NET"),0,"�ڵ������ ���� ���� �ױ׸�,jxDECL_%1%(),n%1%_Debug::jDebugPrint()� ���")\
func(App_PacketGenerator,file_locale,_T("korean"),0,"file locale ")

var_enum(jCV_DECLARE);

extern tcstr g_szName_HEADER_NameSpace;
// �ش��� ������ pVar��Ʈ�����ڸ� ����
inline tstring GetVar_HEADER(jIVar* pVar)
{
	fname_t buf;
	return tstring(g_szName_HEADER_NameSpace) +tstring(_T("_"))+ pVar->ToString(buf);
}
#define GET_VAR(var) GetVar_HEADER(pv_##var)


extern bool is_char_type(jIVar* pvT);
extern bool is_mystring_type(jIVar* pV);
