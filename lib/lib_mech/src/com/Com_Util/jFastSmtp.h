/* file : jFastSmtp.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-10-07 14:12:26
title : 
desc : 

#include "stdafx.h"
#include "jFastSmtp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	

	CFastSmtp mail;

	if (mail.ConnectServer("218.55.107.26")) {
		mail.SetSenderName("Sender's Name");
		mail.SetSenderEmail("icandoit@jGameClient.n_jGame_c.dev");
		mail.SetSubject("CFastSmtp v1.1 Release");

		mail.AddRecipient("bug@jGameClient.n_jGame_c.dev");
		//mail.AddCCRecipient("test@test.com");
		//mail.AddBCCRecipient("test@test.com");

		mail.SetMessageBody("Here is another test of CFastSmtp SMTP class!");

		if (mail.GetConnectStatus()) {        
			printf(mail.Send() ? "Send was a success!" : "Send failed!");
			mail.Disconnect();                    
		}
	}   
	return 0;
}

*/
// jFastSmtp.h: interface for the Smtp class.
//http://www.codeproject.com/internet/zsmtp.asp#xx791810xx
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_)
#define AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h>
#include <assert.h>
#include <vector>

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{

			const int DEFAULT_PROTOCOL = 0;
			const int NO_FLAGS = 0;

			class jFastSmtp  
			{
			public:        
				jFastSmtp();    
				virtual ~jFastSmtp();
				bool    AddRecipient(const char email[], const char name[]="");
				bool    AddBCCRecipient(const char email[], const char name[]="");
				bool    AddCCRecipient(const char email[], const char name[]="");    
				bool    ConnectServer(const char server[], const unsigned short port=NULL);
				bool    Disconnect();
				bool    GetConnectStatus();    
				const unsigned int    GetBCCRecipientCount();    
				const unsigned int    GetCCRecipientCount();
				const unsigned int    GetRecipientCount();    
				const unsigned int    GetSocket();
				const char*    const    GetLocalHostIp();
				const char*    const    GetLocalHostname();    
				const char*    const    GetMessageBody();    
				const char*    const    GetReplyTo();
				const char*    const    GetSenderEmail();
				const char*    const    GetSenderName();
				const char*    const    GetSubject();    
				const char*    const    GetXMailer();    
				bool    Send();
				void    SetMessageBody(const char body[]);    
				void    SetSubject(const char subject[]);    
				void    SetSenderName(const char name[]);    
				void    SetSenderEmail(const char email[]);    
				void    SetReplyTo(const char replyto[]);    
				void    SetXMailer(const char xmailer[]);

			private:
				class CRecipient
				{
				public:
					CRecipient() 
					{ 
						m_pcEmail = NULL;
					};
					CRecipient& operator=(const CRecipient& src)
					{
						if (&src != this)
						{
							if (m_pcEmail)
								delete [] m_pcEmail;
							size_t s = strlen(src.m_pcEmail);
							m_pcEmail = new char[s+1];
							strcpy(m_pcEmail, src.m_pcEmail);
						}
						return (*this);
					};
					virtual ~CRecipient()
					{
						if (m_pcEmail)
							delete [] m_pcEmail;
					};
					char* GetEmail()
					{
						return m_pcEmail;
					};
					void SetEmail(const char email[])
					{
						assert(email);
						size_t s=strlen(email);
						if (s > 0)
						{
							m_pcEmail = new char[s+1];
							strcpy(m_pcEmail, email);
						}        
					};
				private:
					char *m_pcEmail;
				};
				bool bCon;
				char m_cHostName[MAX_PATH];
				char* m_pcFromEmail;
				char* m_pcFromName;
				char* m_pcSubject;
				char* m_pcMsgBody;
				char* m_pcXMailer;
				char* m_pcReplyTo;
				char* m_pcIPAddr;    

				WSADATA wsaData;
				SOCKET hSocket;

				char*   _formatHeader();    
				bool    _formatMessage();
				SOCKET  _connectServerSocket(const char* server, const unsigned short port=NULL);    
			public:
				std::vector<CRecipient*> Recipients;
				std::vector<CRecipient*> CCRecipients;
				std::vector<CRecipient*> BCCRecipients;    

			};

		}
	}
}


#endif // !defined(AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_)