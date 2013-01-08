/* file : make_sq_script_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-23 10:22:02
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;

void make_sq_script_file(int argc, _TCHAR* argv[])
{
	tstring sNicName = argv[ARG_CREATE_TAG];
	tstring sq_file= sNicName + tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_recv_sample_code.txt");
	tofstream of(jA(sq_file));
	of.imbue(locale(jA(pv_file_locale->Get_cstr())));


	of<< _jT("\n\n// 다음코드는 스커럴에서 사용하기위한 샘플 코드\n");
	jIE* pePROTOCAL_LIST = g_pDocTargetFile->Find(jS(PROTOCAL_LIST));
	jIE* it  = pePROTOCAL_LIST->begin();
	jrFOR( it)
	{
		of<< _jF("//jIPacketSocket_IOCP* pS,jPacket_Base* pk,jIP_Address* pFromIP");
		of<< _jF("function jNET_EVENT_%1%(pSock, pk ,pFromIP)") % it->GetTagName();
		of<< _jT("{");
		{AutoTab a;
			of<<_jF("local packet=S_%1%(); packet.ReadPacket(pSock,pk);") % it->GetTagName();
			of<<endl;
		}
		of<<_jT("}");
		of<< endl;

	}

	of<< _jT("\n\n// 다음코드는 C++에서 사용하기위한 샘플 코드\n");

	it  = pePROTOCAL_LIST->begin();
	jrFOR( it)
	{
		of<< _jF("//jIPacketSocket_IOCP* pS,BYTE *pReadBuff, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP");
		of<< _jF("jNET_EVENT_RECEIVER(%1%)") % it->GetTagName();
		of<< _jT("{");
		{AutoTab a;
		of<<_jT("// PlugIn_UNKOWN*p , BYTE buf[1024] , TestUser* pUser");
		of<<_jF("READ_PACKET(%1%);") % it->GetTagName();
		of<<endl;

		}
		of<<_jT("}");

	}


}