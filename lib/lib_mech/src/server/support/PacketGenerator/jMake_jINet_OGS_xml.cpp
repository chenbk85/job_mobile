/* file : jMake_jINet_OGS_xml.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-12 16:08:02
comp.: jgame.co.kr
title : 
desc : 


Z:\source_ES\server\test\PROTOCAL_test\test_Protocol.xml PT uedit32.exe


*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

var_enum(jCV_DEFINE);

namespace nMake_Xml
{
	jID* g_pDocTargetFile =0;
	jIVar* g_pv_jxDEFINE =0;
	bool g_isPrint_jxDEFINE ;

	tstring sNicName ;
	tstring sProtocalEnum;
	tstring sStructureFileName ;
	tstring sReadPacketFileName;
	tstring sWritePacketFileName ;
	tstring sEnumCppFileName ;

}

using namespace nMake_Xml;

void update_loglevel_xml()
{
	jID* pD = GetjIXml()->Load(pv_loglevel_file->Get_cstr());
	if(pD)
	{
		nXML::jE eLL = pD->Find(_T("LOG_LEVEL_LIST") );
		nXML::jE pE;
		pE = eLL[g_szName_HEADER_NameSpace];
		StringID x_LevelType = jx(LOG_LEVEL);
		pE->PersistAttr(jS(LevelType), x_LevelType);
		pE.AttrP(_T("jMX_SKIP_CHILD"))->InitValue(true);

		jIE* it = g_pDocTargetFile->Find(PROTOCAL_LIST);
		it = it->begin();
		jrFOR(it)
		{
			nXML::jE pePr =pE( it->GetTagID() );
			if(pePr.empty())
			{
				pePr = pE[it->GetTagName()];
				pePr.Var()->InitValue(false);
				pePr.AttrP(_T("HELP"))->InitValue(_T(""));
			}
		}
		pD->Save();
	}
}

void show_editor(int argc, _TCHAR* argv[])
{
	if(argc>ARG_TEXT_EDITOR)
	{
		TCHAR buf[1024];
		jt_sprintf(buf, _T("%1% %1%"),argv[ARG_TEXT_EDITOR], sProtocalEnum.c_str() );
		WinExec(nUNI::scb1024_t(buf).getA(), SW_SHOWNORMAL);
		jt_sprintf(buf, _T("%1% %1%"),argv[ARG_TEXT_EDITOR], sStructureFileName.c_str() );
		WinExec(nUNI::scb1024_t(buf).getA(), SW_SHOWNORMAL);
		jt_sprintf(buf, _T("%1% %1%"),argv[ARG_TEXT_EDITOR], sReadPacketFileName.c_str() );
		WinExec(nUNI::scb1024_t(buf).getA(), SW_SHOWNORMAL);
		jt_sprintf(buf, _T("%1% %1%"),argv[ARG_TEXT_EDITOR], sWritePacketFileName.c_str() );
		WinExec(nUNI::scb1024_t(buf).getA(), SW_SHOWNORMAL);
		jt_sprintf(buf, _T("%1% %1%"),argv[ARG_TEXT_EDITOR], sEnumCppFileName.c_str() );
		WinExec(nUNI::scb1024_t(buf).getA(), SW_SHOWNORMAL);
	}
}





//--------------------------------------------------------------------------
int _tmain_Gen_Xml(int argc, _TCHAR* argv[])
//--------------------------------------------------------------------------
{
	if (argc < ARG_TEXT_EDITOR)
	{
		jMB("using : packetgenerator.exe  net \"해더파일.xml\" \"생성Tag\" [TEXTEDITOR]\n", ("ERROR"));
		return 0;
	}

	try
	{
		g_pDocTargetFile = GetjIXml()->Load(argv[ARG_HEADER_XML_FILE]);
		if(!g_pDocTargetFile) throw _T("xml File open failed");
		//g_pDocTargetFile->DebugPrint(nInterface::g_pjILog);
		g_pv_jxDEFINE = g_pDocTargetFile->BaseI()->GetAttrVar(_T("jxDEFINE") );
		g_isPrint_jxDEFINE = !g_pv_jxDEFINE || g_pv_jxDEFINE->Get_bool();

		nFileSystem::jFolder dm;
		dm.GotoByFileName(argv[ARG_HEADER_XML_FILE]);

		g_szName_HEADER_NameSpace = g_pDocTargetFile->BaseI()->GetAttr(_T("HEADER"));
		if(!g_szName_HEADER_NameSpace) jMB("HEADER속성없음",("error") );
		jIVar* pvDPrint = g_pDocTargetFile->BaseI()->GetAttrVar(_T("DebugPrint")) ;
		if(pvDPrint)		g_bDebugPrint = pvDPrint->Get_int();

		sNicName = argv[ARG_CREATE_TAG];
		sProtocalEnum= sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_Enum.h");
		sStructureFileName = sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_Structure.h");
		sReadPacketFileName = sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_ReadPacket.h");
		sWritePacketFileName = sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_WritePacket.h");
		sEnumCppFileName = sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_Enum.cpp");

		//jIVar* pvUsePacketHeader = jCV(App_PacketGenerator,UsePacketHeader,true,0,"enum해더파일사용안하고 패킷별 해더파일사용");


		//if(!pvUsePacketHeader->Get_bool())
		{
			//--------------------------------------------------------------------------
			// enum header file gen
			//--------------------------------------------------------------------------
			make_enum_h_file(sProtocalEnum, argc,argv);
		}
		//else
		{
			// make packet_header file
			make_packet_header_file(argc,argv);
		}

		//--------------------------------------------------------------------------
		// enum cpp file
		//--------------------------------------------------------------------------
		make_enum_cpp_file(sEnumCppFileName,argc,argv);

		make_sq_script_file(argc,argv);

		//--------------------------------------------------------------------------
		// google proto buff
		//--------------------------------------------------------------------------
		{
			make_google_protocal_buffer_doc(sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace,argc,argv);
		}


		//--------------------------------------------------------------------------
		// loglevel.xml파일 수정.
		//--------------------------------------------------------------------------
		update_loglevel_xml();

		show_editor(argc,argv);
	}
	catch (tcstr szErr) 
	{
		jMB(szErr, _T("Error"));
	}
	return 0;
}
