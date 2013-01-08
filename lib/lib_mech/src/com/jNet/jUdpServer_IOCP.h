/* file : jUdpServer_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-19 15:12:39
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jUdpServer_IOCP_header__
#define __jUdpServer_IOCP_header__
#pragma once

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			class jUdpServer_IOCP : public jIObserver_IOCP , public jIServer_IOCP
			{
				jINTERFACE_HEADER(jIServer_IOCP);
			public:
				jUdpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP* pPlugIn,jIE*);
				virtual ~jUdpServer_IOCP(VOID);
				VOID	ResetThreadCallback(nThread::jIThread*);

			private:
				jIProactor_IOCP*		m_pProactor;
				jPacketSocket_IOCP	*m_UdpListenSession;
				jIPlugIn_Server_IOCP *m_pPlugIn;

			public:
				// jIObserver_IOCP 인터페이스 구현
				tname256_t m_threadname;
				tcstr		GetThreadName(){return m_threadname;}
				VOID OnIoRead(VOID *object, jPacketLen_t dataLength);
				VOID OnIoWrote(VOID *object, jPacketLen_t dataLength);
				VOID OnIoConnected(VOID *object);
				VOID OnIoDisconnected(VOID *object);

			};

			inline jSOCKADDR_IN* jUdpServer_IOCP::GetTcpListenAddress(){jASSERT0(0 && "jUdpServer_IOCP::GetTcpListenAddress");return 0;}
			inline jIPlugIn_Server_IOCP *jUdpServer_IOCP::GetPlugIn(){ return m_pPlugIn;}
			inline jIPacketSocket_IOCP* jUdpServer_IOCP::GetUdpListenSocket(){ return m_UdpListenSession->BaseI();}
			inline jIPacketSocket_IOCP* jUdpServer_IOCP::GetUdpSocket(StringID &id){ jASSERT0(0);return 0;}
			inline jIPacketSocket_IOCP* jUdpServer_IOCP::AddUdpSocket(StringID &id,cstr szIP,int port){jASSERT0(0);return 0;}


		}// nNet::Impl

	} //nNET
}//nMech


#endif // __jUdpServer_IOCP_header__
