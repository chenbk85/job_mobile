/* file : SMTPClient.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 16:56:17
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __SMTPClient_header__
#define __SMTPClient_header__
#pragma once
#include "header/jDefine.h"
#include "interface/jISMTPClient.h"


namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
			class SMTPClient : public jISMTPClient
			{
			public:
				jINTERFACE_HEADER(jIInterface);
				jINTERFACE_HEADER(jISMTPClient);

				SMTPClient();
				~SMTPClient();

			private:
				BOOL		MailLogin( acstr userName, acstr password );
				BOOL		CheckResponse( BYTE type );


				LPVOID		m_instanceSocket;
				CHAR		m_errorMessage[127];
				CHAR		m_listReceiver[SMTP_MAXRECEIVERCOUNT][64];
				int			m_errorCode;
				int			m_receiverCount;
			};

		}
	}
}


#endif // __SMTPClient_header__
