/* file : test_smtp.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-11 12:15:12
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "Interface/jISMTPClient.h"

using namespace nMech;

namespace 
{
	jTEST_SUITE_BEGIN(com_util)
	std::string g_sMailServer = "mail.actoz.com";
	std::string g_sMailFrom = "icandoit@actoz.com";
	std::string g_sMailTo = "icandoit@actoz.com";
	jTEST(smtp)
	{


		using namespace nMech::nUtil::nDebug;

		BOOL			ret;
		jISMTPClient* pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
		jCHECK(pMail);
		if(!pMail) return;

#if 0
		ret = pMail->Connect( g_sMailServer.c_str() );
		jCHECK(ret);
		ret = pMail->MailFrom( g_sMailFrom.c_str() );
		jCHECK(ret);
		ret = pMail->MailTo( g_sMailTo.c_str() );
		jCHECK(ret);
		ret = pMail->MailContents( "Crasher", "DontSendMe@jGame.co.kr", "力格", "皋老郴侩" );
		jCHECK(ret);
		ret = pMail->MailAttachFileA( "C:\\WINDOWS\\标判.bmp" );
		jCHECK(ret);
		ret = pMail->MailSubmit();
		jCHECK(ret);
		ret = pMail->Disconnect();
		jCHECK(ret);
		SAFE_RELEASE(pMail);
#else
		SAFE_RELEASE(pMail);
		return;
#endif

		pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
		jCHECK(pMail);
		if(!pMail) return;
		ret = pMail->Connect( g_sMailServer.c_str() );
		jCHECK(ret);
		ret = pMail->MailFrom( g_sMailFrom.c_str() );
		jCHECK(ret);
		ret = pMail->MailTo( g_sMailTo.c_str() );
		jCHECK(ret);
		ret = pMail->MailContents( "Crasher2", "DontSendMe@jGame.co.kr", "力格2", "皋老郴侩2" );
		jCHECK(ret);
		ret = pMail->MailAttachFileA( "C:\\WINDOWS\\标判.bmp" );
		jCHECK(ret);
		ret = pMail->MailSubmit();
		jCHECK(ret);
		ret = pMail->Disconnect();
		jCHECK(ret);
		SAFE_RELEASE(pMail);

	}

	jTEST_SUITE_END(com_util)
}


