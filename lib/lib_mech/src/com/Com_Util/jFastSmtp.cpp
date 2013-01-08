#include "stdafx.h"
#include "jFastSmtp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4267)

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{

			jFastSmtp::jFastSmtp()
			{
				// Initialize variables
				bCon            = false;

				m_pcFromEmail    = NULL;
				m_pcFromName    = NULL;
				m_pcSubject        = NULL;
				m_pcMsgBody        = NULL;
				m_pcXMailer        = NULL;
				m_pcReplyTo        = NULL;
				m_pcIPAddr        = NULL;

				// Initialize WinSock
				WORD wVer    = MAKEWORD(2,2);    
				if (WSAStartup(wVer,&wsaData) != NO_ERROR) {
					printf("WSAStartup %d\r\n", WSAGetLastError());        
					throw; 
				}
				if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) {
					printf("Can't find a useable WinSock DLL\r\n");
					WSACleanup();
					throw; 
				}    
			}

			jFastSmtp::~jFastSmtp()
			{
				// Free recipient lists
				for (unsigned int n = 0; n < Recipients.size(); n++)
					delete Recipients[n];
				for (unsigned int n = 0; n < CCRecipients.size(); n++)
					delete CCRecipients[n];
				for (unsigned int n = 0; n < BCCRecipients.size(); n++)
					delete BCCRecipients[n];

				// Free variables
				if (m_pcFromEmail)
					delete m_pcFromEmail;
				if (m_pcFromName)
					delete m_pcFromName;
				if (m_pcSubject)
					delete m_pcSubject;
				if (m_pcMsgBody)
					delete m_pcMsgBody;
				if (m_pcXMailer)
					delete m_pcXMailer;
				if (m_pcReplyTo)
					delete m_pcReplyTo;

				// Close connection
				if (bCon)
					Disconnect();

				// Cleanup
				WSACleanup();
			}

			bool jFastSmtp::AddRecipient(const char email[], const char name[])
			{
				assert(email);

				size_t s=strlen(email);
				if (s==0)
					return false;

				CRecipient *pRec = new CRecipient();

				char *pcBuf = new char[s+strlen(name)+4];
				sprintf(pcBuf,"%s<%s>",name,email);    
				pRec->SetEmail(pcBuf);
				Recipients.insert(Recipients.end(), pRec);
				delete [] pcBuf;

				return (true);    
			}

			bool jFastSmtp::AddCCRecipient(const char email[], const char name[])
			{
				assert(email);

				size_t s=strlen(email);
				if (s==0)
					return false;

				CRecipient *pRec = new CRecipient();    

				char *pcBuf = new char[s+strlen(name)+4];
				sprintf(pcBuf,"%s<%s>",name,email);    
				pRec->SetEmail(pcBuf);
				CCRecipients.insert(CCRecipients.end(), pRec);
				delete pcBuf;

				return (true);
			}

			bool jFastSmtp::AddBCCRecipient(const char email[], const char name[])
			{
				assert(email);

				size_t s=strlen(email);
				if (s==0)
					return false;

				CRecipient *pRec = new CRecipient();

				char *pcBuf = new char[s+strlen(name)+4];
				sprintf(pcBuf,"%s<%s>",name,email);    
				pRec->SetEmail(pcBuf);
				BCCRecipients.insert(BCCRecipients.end(), pRec);
				delete pcBuf;    

				return (true);
			}

			bool jFastSmtp::Disconnect()
			{
				if (!bCon) {
					printf("Not connected to server!\r\n");
					return (false);
				}

				BYTE        sReceiveBuffer[4096];
				int            iLength = 0;
				int            iEnd = 0;

				if (send(hSocket, (LPSTR)"QUIT\r\n", strlen("QUIT\r\n"),
					NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						return (false);
					}
					iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd, 
						NO_FLAGS);
					iEnd += iLength;
					sReceiveBuffer[iEnd] = '\0';

					bCon=false;    
					shutdown(hSocket,0x02);
					closesocket(hSocket);
					hSocket=NULL;

					return (true);
			}

			bool jFastSmtp::Send()
			{
				// verify sender email
				if (m_pcFromEmail == NULL) {
					printf("Please specifiy a sender email address\r\n");
					return (false);
				}

				BYTE        sReceiveBuffer[4096];
				int            iLength = 0;
				int            iEnd = 0;
				char        buf[4096];
				// get proper header
				char* msgHeader = _formatHeader();

				if (msgHeader == NULL) {
					delete [] msgHeader;
					printf("Failed to format message header\r\n");
					return (false);
				}
				// start
				strcpy(buf, "MAIL FROM: <");
				strcat(buf, m_pcFromEmail);
				strcat(buf, ">\r\n");
				if (send(hSocket, (LPSTR)buf, strlen(buf), NO_FLAGS) == SOCKET_ERROR) {
					printf("Socket send error: %d\r\n", WSAGetLastError());    
					return (false);
				}
				iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd, 
					NO_FLAGS);
				iEnd += iLength;
				sReceiveBuffer[iEnd] = '\0';
				// create message receipts
				char *token;
				for(unsigned int i=0;i<Recipients.size();i++) {
					token = strtok(Recipients.at(i)->GetEmail(),"<");
					token = strtok(NULL,"<");    
					if (token == NULL) 
						token = strtok(Recipients.at(i)->GetEmail(),"<");
					strcpy(buf, "RCPT TO: <");
					strcat(buf, token);
					strcat(buf, "\r\n");
					if (send(hSocket, (LPSTR)buf, strlen(buf), NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						return (false);
					}
					iLength = recv(hSocket, 
						(LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd, 
						NO_FLAGS);
					iEnd += iLength;
					sReceiveBuffer[iEnd] = '\0';
				}
				for(unsigned int i=0;i<CCRecipients.size();i++) {
					token = strtok(CCRecipients.at(i)->GetEmail(),"<");
					token = strtok(NULL,"<");
					if (token == NULL) 
						token = strtok(Recipients.at(i)->GetEmail(),"<");
					strcpy(buf, "RCPT TO: <");
					strcat(buf, token);
					strcat(buf, "\r\n");
					if (send(hSocket, (LPSTR)buf, strlen(buf), NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						return (false);
					}
					iLength = recv(hSocket, 
						(LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd,
						NO_FLAGS);
					iEnd += iLength;
					sReceiveBuffer[iEnd] = '\0';
				}
				for(unsigned int i=0;i<BCCRecipients.size();i++) {
					token = strtok(BCCRecipients.at(i)->GetEmail(),"<");
					token = strtok(NULL,"<");
					if (token == NULL) 
						token = strtok(Recipients.at(i)->GetEmail(),"<");
					strcpy(buf, "RCPT TO: <");
					strcat(buf, token);
					strcat(buf, "\r\n");
					if (send(hSocket, (LPSTR)buf, strlen(buf), NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						return (false);
					}
					iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd,
						sizeof(sReceiveBuffer)-iEnd, 
						NO_FLAGS);
					iEnd += iLength;
					sReceiveBuffer[iEnd] = '\0';
				}
				// init data
				if (send(hSocket, (LPSTR)"DATA\r\n", strlen("DATA\r\n"), NO_FLAGS) == SOCKET_ERROR) {
					printf("Socket send error: %d\r\n", WSAGetLastError());    
					return (false);
				}
				iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd,
					NO_FLAGS);
				iEnd += iLength;
				sReceiveBuffer[iEnd] = '\0';
				// send header    
				if (send(hSocket, 
					(LPSTR)msgHeader, strlen(msgHeader), NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						delete [] msgHeader;
						return (false);
					}
					// send body    
					if (send(hSocket, 
						(LPSTR)m_pcMsgBody, strlen(m_pcMsgBody), NO_FLAGS) == SOCKET_ERROR) {
							printf("Socket send error: %d\r\n", WSAGetLastError());    
							return (false);
						}
						// signal end    
						if (send(hSocket,
							(LPSTR)"\r\n.\r\n", strlen("\r\n.\r\n"), NO_FLAGS) == SOCKET_ERROR) {
								printf("Socket send error: %d\r\n", WSAGetLastError());    
								return (false);
							}
							iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd,
								NO_FLAGS);
							iEnd += iLength;
							sReceiveBuffer[iEnd] = '\0';
							delete [] msgHeader;
							return (true);

			}

			bool jFastSmtp::ConnectServer(const char server[], const unsigned short port)
			{
				assert(server);

				if (bCon)
					Disconnect();
				bCon=false;
				hSocket = INVALID_SOCKET;

				hSocket = _connectServerSocket(server, port);    
				if (hSocket != INVALID_SOCKET) {        
					BYTE        sReceiveBuffer[4096];
					int            iLength = 0;
					int            iEnd = 0;
					char        buf[4096];

					strcpy(buf, "HELO ");
					strcat(buf, server);
					strcat(buf, "\r\n");
					if (send(hSocket, (LPSTR)buf, strlen(buf), NO_FLAGS) == SOCKET_ERROR) {
						printf("Socket send error: %d\r\n", WSAGetLastError());    
						return (false);
					}
					iLength = recv(hSocket, 
						(LPSTR)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd, 
						NO_FLAGS);
					iEnd += iLength;
					sReceiveBuffer[iEnd] = '\0';
				} else {
					printf("Invalid socket\r\n");
					return (false);
				}

				bCon=true;
				return (true);
			}

			SOCKET jFastSmtp::_connectServerSocket(const char server[],
				const unsigned short port)
			{
				int                nConnect;
				short            nProtocolPort;
				LPHOSTENT        lpHostEnt;
				LPSERVENT        lpServEnt;
				SOCKADDR_IN        sockAddr;        

				SOCKET            hServerSocket = INVALID_SOCKET;

				lpHostEnt = gethostbyname(server);
				if (lpHostEnt) {        
					hServerSocket = socket(PF_INET, SOCK_STREAM,DEFAULT_PROTOCOL);
					if (hServerSocket != INVALID_SOCKET) {
						if (port != NULL) {
							nProtocolPort = port;
						}else{
							lpServEnt = getservbyname("mail", DEFAULT_PROTOCOL);
							if (lpServEnt == NULL) 
								nProtocolPort = htons(IPPORT_SMTP); 
							else 
								nProtocolPort = lpServEnt->s_port;
						}
						sockAddr.sin_family = AF_INET;
						sockAddr.sin_port = nProtocolPort;
						sockAddr.sin_addr = *((LPIN_ADDR)*lpHostEnt->h_addr_list);
						nConnect = connect(hServerSocket, (PSOCKADDR)&sockAddr, 
							sizeof(sockAddr));
						if(nConnect) 
							hServerSocket = INVALID_SOCKET;
					} else {
						printf("Invalid socket\r\n");
						throw;
					}
				}
				return(hServerSocket);
			}

			char* jFastSmtp::_formatHeader()
			{
				// check for at least one recipient
				if(Recipients.size() <= 0 )    {
					printf("Please add a message recipient!\r\n");
					return NULL;
				}
				int s=0;
				char *msgHeader = new char[16385];
				//char to[1024];
				size_t i=0;
				for ( i=s=0;i<Recipients.size();i++) {        
					s+=strlen(Recipients.at(i)->GetEmail())+1;
				} if (s==0) s=1; char *to = new char[s];
				//char cc[1024];
				for (i=s=0;i<CCRecipients.size();i++) {        
					s+=strlen(CCRecipients.at(i)->GetEmail())+1;
				} if (s==0) s=1; char *cc = new char[s];
				//char bcc[1024];
				for (i=s=0;i<BCCRecipients.size();i++) {        
					s+=strlen(BCCRecipients.at(i)->GetEmail())+1;
				} if (s==0) s=1; char *bcc = new char[s];

				CHAR szDate[500];
				CHAR sztTime[500];

				// create the recipient string, cc string, and bcc string
				to[0] = '\0';        
				for (i=0;i<Recipients.size();i++) {        
					i > 0 ? strcat(to,","):strcat(to,"");
					strcat(to,Recipients.at(i)->GetEmail());
				}

				cc[0] = '\0';    
				for (i=0;i<CCRecipients.size();i++) {
					i > 0 ? strcat(cc,","):strcat(cc,"");
					strcat(cc,CCRecipients.at(i)->GetEmail());
				}

				bcc[0] = '\0';    
				for (i=0;i<BCCRecipients.size();i++) {
					i > 0 ? strcat(bcc,","):strcat(bcc,"");
					strcat(bcc,BCCRecipients.at(i)->GetEmail());
				}
				// get the current date and time
				SYSTEMTIME st={0};
				::GetSystemTime(&st);
				::GetDateFormatA(LOCALE_SYSTEM_DEFAULT,0,&st,"ddd',' dd MMM yyyy",szDate,sizeof(szDate));
				::GetTimeFormatA(LOCALE_SYSTEM_DEFAULT,TIME_FORCE24HOURFORMAT,&st,
					"HH':'mm':'ss tt",sztTime,sizeof(sztTime));
				// here it is...the main data of the message
				ja_sprintf(msgHeader,"DATE: %s %s\r\n", szDate, sztTime);    
				if (m_pcFromName != NULL) {
					strcat(msgHeader,"FROM: ");
					strcat(msgHeader, m_pcFromName);
					strcat(msgHeader, "\r\n");
				}
				strcat(msgHeader,"To: ");
				strcat(msgHeader, to);
				strcat(msgHeader, "\r\n");
				strcat(msgHeader,"Cc: ");
				strcat(msgHeader, cc);
				strcat(msgHeader, "\r\n");
				if (m_pcSubject != NULL) {
					strcat(msgHeader, "Subject: ");
					strcat(msgHeader, m_pcSubject);
					strcat(msgHeader, "\r\n");
				}
				if (m_pcXMailer != NULL) {
					strcat(msgHeader,"X-Mailer: ");
					strcat(msgHeader, m_pcXMailer);
					strcat(msgHeader, "\r\n");
				}
				// start optional fields
				if (m_pcReplyTo != NULL) {
					strcat(msgHeader, "Reply-To: ");
					strcat(msgHeader, m_pcReplyTo);
					strcat(msgHeader, "\r\n");
				}
				// start MIME versions
				strcat(msgHeader, 
					"MIME-Version: 1.0\r\nContent-type: text/plain; charset=US-ASCII\r\n");
				// send header finish command
				strcat(msgHeader, "\r\n");    
				// clean up
				delete to;
				delete cc;
				delete bcc;
				// done    
				return msgHeader;    
			}

			const char* const jFastSmtp::GetLocalHostIp() 
			{
				in_addr    *iaHost;

				if (gethostname(m_cHostName,255) != SOCKET_ERROR) {
					HOSTENT *pHe = NULL;        
					pHe = gethostbyname(m_cHostName);
					if (pHe != NULL) {
						for (int i=0;pHe->h_addr_list[i] != 0;i++) {
							iaHost = (LPIN_ADDR)pHe->h_addr_list[i];
							m_pcIPAddr = inet_ntoa(*iaHost);
						}
					}            
				} else {            
					DWORD dErr = WSAGetLastError();    
					printf("Failed to get the local ip address\r\n");
				}    

				return m_pcIPAddr;
			}

			const char* const jFastSmtp::GetLocalHostname() 
			{    
				if (gethostname((char FAR*)m_cHostName,255) == SOCKET_ERROR)    
					printf("Failed to get the local hostname\r\n");
				return m_cHostName;
			}


			//**********************************************************************************
			//*** Properties
			//**********************************************************************************

			bool jFastSmtp::GetConnectStatus()
			{
				return (bCon);
			}

			unsigned const int jFastSmtp::GetBCCRecipientCount()
			{
				return (BCCRecipients.size());
			}

			unsigned const int jFastSmtp::GetCCRecipientCount() 
			{
				return (CCRecipients.size());
			}

			unsigned const int jFastSmtp::GetSocket()
			{
				return (hSocket);
			}

			const char* const jFastSmtp::GetMessageBody() 
			{
				return (m_pcMsgBody);
			}

			unsigned const int jFastSmtp::GetRecipientCount()
			{
				return (Recipients.size());
			}

			const char* const jFastSmtp::GetReplyTo()  
			{
				return (m_pcReplyTo);
			}

			const char* const jFastSmtp::GetSenderEmail() 
			{
				return (m_pcFromEmail);
			}

			const char* const jFastSmtp::GetSenderName() 
			{
				return (m_pcFromName);
			}

			const char* const jFastSmtp::GetSubject() 
			{
				return (m_pcSubject);
			}

			const char* const jFastSmtp::GetXMailer() 
			{
				return (m_pcXMailer);
			}

			void jFastSmtp::SetMessageBody(const char body[])
			{
				assert(body);
				int s=strlen(body);
				if (m_pcMsgBody)
					delete [] m_pcMsgBody;
				m_pcMsgBody = new char[s+1];
				strcpy(m_pcMsgBody, body);    
			}

			void jFastSmtp::SetReplyTo(const char replyto[])
			{
				assert(replyto);
				int s=strlen(replyto);
				if (m_pcReplyTo)
					delete [] m_pcReplyTo;
				m_pcReplyTo = new char[s+1];
				strcpy(m_pcReplyTo, replyto);
			}

			void jFastSmtp::SetSenderEmail(const char email[])
			{
				assert(email);
				int s=strlen(email);
				if (m_pcFromEmail)
					delete [] m_pcFromEmail;
				m_pcFromEmail = new char[s+1];
				strcpy(m_pcFromEmail, email);        
			}

			void jFastSmtp::SetSenderName(const char name[])
			{
				assert(name);
				int s=strlen(name);
				if (m_pcFromName)
					delete [] m_pcFromName;
				m_pcFromName = new char[s+1];
				strcpy(m_pcFromName, name);
			}

			void jFastSmtp::SetSubject(const char subject[])
			{
				assert(subject);
				int s=strlen(subject);
				if (m_pcSubject)
					delete [] m_pcSubject;
				m_pcSubject = new char[s+1];
				strcpy(m_pcSubject, subject);
			}

			void jFastSmtp::SetXMailer(const char xmailer[])
			{
				assert(xmailer);
				size_t  s=strlen(xmailer);
				if (m_pcXMailer)
					delete [] m_pcXMailer;
				m_pcXMailer = new char[s+1];
				strcpy(m_pcXMailer, xmailer);
			}

		}
	}
}


#pragma warning(default : 4267)