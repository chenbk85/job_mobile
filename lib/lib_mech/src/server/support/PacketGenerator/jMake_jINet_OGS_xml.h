/* file : jMake_jINet_OGS_xml.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-12 16:07:59
comp.: jgame.co.kr
title : 
desc : 


Z:\source_ES\server\test\PROTOCAL_test\test_Protocol.xml PT uedit32.exe

*/

#ifndef __jMake_jINet_OGS_xml_header__
#define __jMake_jINet_OGS_xml_header__
#pragma once
#include "header/uString_stl.h"

namespace nMake_Xml
{
	//--------------------------------------------------------------------------
	inline bool _write_CODE(tofstream& of, jIE* it, cstr szType)
	//--------------------------------------------------------------------------
	{
		if(it->IsName(_T("CODE")) && it->GetAttrVar(_T("TYPE"))->IsContents(szType))
		{
			of<<_jF("%1%") %it->Get_cstr() ;
			return true;
		}
		return false;
	}


	extern jID* g_pDocTargetFile;
	extern jIVar* g_pv_jxDEFINE ;
	extern bool g_isPrint_jxDEFINE ;

	extern tstring sNicName ;
	extern tstring sProtocalEnum;
	extern tstring sStructureFileName ;
	extern tstring sReadPacketFileName;
	extern tstring sWritePacketFileName ;
	extern tstring sEnumCppFileName ;


}
using namespace nMake_Xml;
extern void make_enum_cpp_file(tstring &sEnumCppFileName ,int argc, _TCHAR* argv[]);
extern void make_enum_h_file(tstring& sProtocalEnum,int argc, _TCHAR* argv[]);
extern void make_struct_h_file(tstring& sStructureFileName,int argc, _TCHAR* argv[]);
extern void make_google_protocal_buffer_doc(tstring &sProtoFileName,int argc, _TCHAR* argv[]);


extern void make_read_packet_file(int argc, _TCHAR* argv[]);
extern void make_write_packet_file(int argc, _TCHAR* argv[]);
extern void make_packet_header_file(int argc, _TCHAR* argv[]);
extern void make_sq_script_file(int argc, _TCHAR* argv[]);
#endif // __jMake_jINet_OGS_xml_header__
