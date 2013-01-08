/* file : jSMTP_Client.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 16:58:53
comp.: pantavision.co.kr
title : 
desc : 


#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "SMTPClient.h"

void main()
{
SMTPClient		smtp;
BOOL			ret;

ret = smtp.Connect( "extremendl.net" );
ret = smtp.MailFrom( "Sender@extremendl.net" );
ret = smtp.MailTo( "Receiver@extremendl.net" );
ret = smtp.MailContents( "Nickname", "reinlainer@extremendl.net", "Subject", "Body" );
ret = smtp.MailAttachFile( "TestFile.dat" );
ret = smtp.MailSubmit();

smtp.Disconnect();
}

*/

#ifndef __jSMTP_Client_header__
#define __jSMTP_Client_header__
#pragma once

#define  SMTP_DEFAULT_PORT		25
#define  SMTP_MAXRECEIVERCOUNT	64

#ifdef UNICODE
#define MailAttachFile MailAttachFileW
#else
#define MailAttachFile MailAttachFileA
#endif

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
#define jINTERFACE_jISMTPClient(x) public:	\
	virtual BOOL		Connect( acstr ipAddress, acstr userName = 0,acstr password = 0, int portNo = SMTP_DEFAULT_PORT ) ##x \
	virtual BOOL		Disconnect() ##x \
	virtual BOOL		MailFrom( acstr email ) ##x \
	virtual BOOL		MailTo( acstr to ) ##x \
	virtual BOOL		MailContents( acstr fromNick, acstr fromEMail, acstr subject, acstr body ) ##x \
	virtual BOOL		MailAttachFileA( acstr fileName ) ##x \
	virtual BOOL		MailAttachFileW( wcstr fileName ) ##x \
	virtual BOOL		MailSubmit() ##x \

		jINTERFACE_END_BASE1(jISMTPClient, nInterface::jIInterface);

		// »ç¿ë¹ý.
		// jISMTPClient* pjISMTPClient = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
		}
	}
}



#endif // __jSMTP_Client_header__
