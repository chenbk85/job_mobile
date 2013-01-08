#include "stdafx.h"

#include "ClientSocket.h"	//  Windows.h, WinSock2.h 순서를 유지하기 위해 먼저 include한다.
#include "SmtpClient.h"
#include "Base64.h"
#include "Mime.h"

#include <stdio.h>

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{

#define  DEF_CLIENTSOCKET( name )	ClientSocket*	name = ( ClientSocket* )m_instanceSocket

#define  CHECK_CONNECTION	0
#define  CHECK_HELLO		1

#define  CHECK_LOGIN		2
#define  CHECK_USERNAME		3
#define  CHECK_PASSWORD		4

#define  CHECK_MAIL			5
#define  CHECK_RCPT			6
#define  CHECK_DATA_START	7
#define  CHECK_DATA_END		8
#define  CHECK_QUIT			9
#define  CHECK_DATA			10

			Mime	mime;


			jCTOR_INTERFACE(nMech::nUtil::nDebug::jISMTPClient,SMTPClient)
			{
				return new SMTPClient;
			}
			jDTOR_INTERFACE(nMech::nUtil::nDebug::jISMTPClient,SMTPClient)
			{
				delete this;
			}

			SMTPClient::SMTPClient()
				: m_errorCode( 0 )
			{
				//  배포시 ClientSocket.h를 열외시키기 위해서는 cpp에서 ClientSocket을
				//  사용해야 한다. 때문에 member로는 LPVOID로 선언하고 ClientSocket의
				//  개체를 생성한 후 포인터를 가리키게 하는 것이다.
				ClientSocket*	instance = new ClientSocket;

				m_instanceSocket = instance;


				m_errorMessage[0] = 0;
			}

			SMTPClient::~SMTPClient()
			{
				DEF_CLIENTSOCKET( clientSocket );

				clientSocket->Close();

				delete m_instanceSocket;
			}

			BOOL SMTPClient::CheckResponse( BYTE type )
			{
				DEF_CLIENTSOCKET( clientSocket );
				char	buffer[512], temp[256];
				int		typeNo;
				int		codeList[11] = { 220, 250, 334, 334, 235, 250, 250, 354, 250, 221, 354 };

				ZeroMemory( buffer, 512 );

				int len  = clientSocket->Recv( buffer, sizeof( buffer ) );
				//jLOG(_T("mailserver recv len=%d ,buffer=%s"), len , jT(buffer));
				::strncpy( temp, buffer, 3 );
				temp[3]=0;
				typeNo = atoi( temp );

				if( typeNo != codeList[type] )
				{
					//jWARN( _T("ret=%s ,typeno= %d ,TYPE[%d]=%d"), jT(buffer),typeNo ,type,codeList[type]);
					return FALSE;
				}
				return TRUE;
			}

			BOOL SMTPClient::Connect( acstr ipAddress, acstr userName, acstr password, int portNo )
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR			hostName[127];
				CHAR			buffer[512];
				::gethostname( hostName, 127 );
				if( clientSocket->Connect( ipAddress, portNo ) == false )
				{
					jWARN(_T(" fail Connect( %s ) "),ipAddress);
					return false;

				}
				if( CheckResponse( CHECK_CONNECTION ) == FALSE )
				{
					jWARN(_T("fail CheckResponse( CHECK_CONNECTION ) "));
					return false;

				}
				m_receiverCount = 0;

				if( userName != 0 && password != 0 )
				{
					//jLOG(_T("serName != 0 && password != 0 , "));
					::sprintf( buffer, "EHLO %s\r\n", hostName );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );

					if( CheckResponse( CHECK_HELLO ) == FALSE )
					{
						jWARN(_T("CheckResponse( CHECK_HELLO ) ="));
						return false;
					}

					jWARN(_T("ASDF 16, "));
					if( MailLogin( userName, password ) == FALSE )
					{
						jWARN(_T("MailLogin( %s, %s) == FALSE  "),jT(userName),jT(password));
						return false;
					}
				}
				else
				{
					::sprintf( buffer, "HELO %s\r\n", hostName );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );
					jLOG(_T("SEND TO MAILSERVER : HELO %s "),jT(hostName));

					if( CheckResponse( CHECK_HELLO ) == FALSE )
					{
						jWARN(_T("CheckResponse( CHECK_HELLO ) == FALSE )1234"));
						return false;
					}
				}
				jLOG(_T("mailserver connect ok, "));

				return TRUE;
			}

			BOOL SMTPClient::Disconnect()
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];

				::sprintf( buffer, "QUIT\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );

				return ( CheckResponse( CHECK_QUIT ) == TRUE );
			}

			BOOL SMTPClient::MailLogin( acstr userName, acstr password )
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	encodeUserName[256];
				CHAR	encodePassword[256];
				CHAR	buffer[127];

				Base64Encode( userName, ( int )::strlen( userName ), encodeUserName, 256 );
				Base64Encode( password, ( int )::strlen( password ), encodePassword, 256 );

				::sprintf( buffer, "AUTH LOGIN\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_LOGIN ) == FALSE )
					return FALSE;


				::sprintf( buffer, "%s\r\n", encodeUserName );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_USERNAME ) == FALSE )
					return FALSE;


				::sprintf( buffer, "%s\r\n", encodePassword );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_PASSWORD ) == FALSE )
					return FALSE;

				return TRUE;
			}

			BOOL SMTPClient::MailFrom( acstr email )
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];

				::sprintf( buffer, "MAIL FROM:%s\r\n", email );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );

				return ( CheckResponse( CHECK_MAIL ) == TRUE );
			}

			BOOL SMTPClient::MailTo( acstr to )
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];

				::sprintf( buffer, "RCPT TO:<%s>\r\n", to );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );

				if( CheckResponse( CHECK_RCPT ) == FALSE )
					return FALSE;

				::strcpy( m_listReceiver[m_receiverCount], to );
				m_receiverCount++;

				return TRUE;
			}

			BOOL SMTPClient::MailContents( acstr fromNick, acstr fromEMail, acstr subject, acstr body )
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];

				::sprintf( buffer, "DATA\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_DATA ) == FALSE )
					return FALSE;

				//  발신자 정보
				{
					::sprintf( buffer, "From: %s<%s>\r\n", fromNick, fromEMail );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );

					::sprintf( buffer, "X-Mailer:SSUL SendMail v1.0 [Korea]\r\n" );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				}


				//  수신자 정보
				{
					int		i;

					::sprintf( buffer, "To: <" );
					for( i = 0 ; i < m_receiverCount ; i++ )
					{
						if( i > 0 )
							::strcat( buffer, ";" );

						::strcat( buffer, m_listReceiver[i] );
					}
					::strcat( buffer, ">\r\n" );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				}


				//  메일 제목 전송
				{
					::sprintf( buffer, "Subject: %s\r\n", subject );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				}

				::sprintf( buffer, "Mime-Version: 1.0\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "Content-Type: multipart/mixed; boundary=\"%s\"\r\n\r\n", mime.GetDefaultBoundary() );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "--%s\r\n", mime.GetDefaultBoundary() );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );

				//  메일 본문 전송
				{
					LPSTR		bodyText;
					int			bodySize, encodeSize;

					bodySize	= ( int )::strlen( body );
					encodeSize	= ( int )( ( float )bodySize * 1.5f );
					bodyText = new CHAR [ encodeSize +1];

					::sprintf( buffer, "Content-Type: text/plain; charset=euc_kr\r\n" );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );

					::sprintf( buffer, "Content-Transfer-Encoding: Base64\r\n\r\n" );
					clientSocket->Send( buffer, ( int )::strlen( buffer ) );


					Base64Encode( body, bodySize, bodyText, encodeSize );
					encodeSize = ( int )::strlen( bodyText );
					clientSocket->Send( bodyText, encodeSize );

					delete bodyText;
				}

				return TRUE;
			}

			BOOL	SMTPClient::MailAttachFileW( wcstr fileName )
			{
				return TRUE;
			}

			BOOL SMTPClient::MailAttachFileA( acstr fileName )
			{
				if(!nFileSystem::jFolder::Is_Exist(nUNI::scb1024_t(fileName).getT() )) return false;
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];
				LPSTR	contentType;

				//  Split File extend
				{
					CHAR	drive[127], dir[127];
					CHAR	name[127], ext[24];
					int		i;

					::_splitpath( fileName, drive, dir, name, ext );

					//  dot을 제거한다.
					for( i = 1 ; ext[i] != 0 ; i++ )
					{
						ext[i - 1] = ext[i];
						ext[i] = 0;
					}

					contentType = mime.GetContentType( ext );
				}

				//  Start boundary
				::sprintf( buffer, "\r\n--%s\r\n", mime.GetDefaultBoundary() );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "Content-Type: %s; file=\"%s\"\r\n", contentType, fileName );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "Content-Transfer-Encoding: Base64\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "Content-Disposition: attachment; filename=\"%s\"\r\n", fileName );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "Content-Description: Created from SSUL mail engine\r\n\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				//  Encoding File to Base64
				HANDLE		handleFile;
				CHAR		readBuffer[8192], encodeBuffer[8192];
				DWORD		readBytes;
				int			size;
				//fname_t bufDir;
				//GetCurrentDirectory(_countof(bufDir),bufDir);
				handleFile = CreateFileA( fileName, GENERIC_READ, FILE_SHARE_READ,
					0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
				if( handleFile == INVALID_HANDLE_VALUE )
					return FALSE;

				do
				{
					if( ReadFile( handleFile, readBuffer, 3072, &readBytes, 0 ) == FALSE )
						break;

					Base64Encode( readBuffer, readBytes, encodeBuffer, 8192 );
					size = ( int )::strlen( encodeBuffer );

					if( readBytes > 0 )
						clientSocket->Send( encodeBuffer, size );
				} while( readBytes > 0 );

				CloseHandle( handleFile );

				return TRUE;
			}

			BOOL SMTPClient::MailSubmit()
			{
				DEF_CLIENTSOCKET( clientSocket );
				CHAR	buffer[127];


				::sprintf( buffer, "\r\n--%s--\r\n", mime.GetDefaultBoundary() );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );


				::sprintf( buffer, "\r\n.\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_DATA_END ) == FALSE )
					return FALSE;


				::sprintf( buffer, "QUIT\r\n" );
				clientSocket->Send( buffer, ( int )::strlen( buffer ) );
				if( CheckResponse( CHECK_QUIT ) == FALSE )
					return FALSE;

				return TRUE;
			}



		}
	}
}
