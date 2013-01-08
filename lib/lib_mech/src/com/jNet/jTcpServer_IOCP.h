/* file : jTcpServer_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-19 17:41:05
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jTcpServer_IOCP_header__
#define __jTcpServer_IOCP_header__
#pragma once



// CIocp를 상속 받습니다.
#include "ConnectedSessionManager.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			class jTcpServer_IOCP : public jIObserver_IOCP , public jIServer_IOCP
			{
				jINTERFACE_HEADER(jIServer_IOCP);
			public:
				jTcpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP* pPlugIn,jIE*);
				virtual ~jTcpServer_IOCP(VOID);

				// KeepAlive Thread Callback 함수
				VOID KeepThreadCallback(nThread::jIThread*);
				//tname256_t m_threadName;

			public:
				// jIObserver_IOCP 인터페이스 구현
				tcstr		GetThreadName(){return m_pPlugIn->m_pE->GetTagName();}
				VOID OnIoRead(VOID *pObject, jPacketLen_t dwDataLength);
				VOID OnIoWrote(VOID *pObject, jPacketLen_t dwDataLength);
				VOID OnIoConnected(VOID *pObject);
				VOID OnIoDisconnected(VOID *pObject);
				
				void PostDisconnectForProactor(VOID *pObject, OVERLAPPED *m_OVLP)
				{
					m_pProactor->PostDisconnect(pObject, m_OVLP);
				}

//			private:
				jIProactor_IOCP* m_pProactor;
				int m_iSizeQueue;
				// 서버의 Listen을 담당할 개체
			public:
				nMech::nUtil::jCriticalSection m_pListenSocket_CS;
				jSocket_IOCP *m_pListenSocket ;
				jIPlugIn_Server_IOCP *m_pPlugIn;
//			private:
				jConnected_PacketSocket_Manager m_Connected_PacketSocket_Manager;
			};

			inline jSOCKADDR_IN* jTcpServer_IOCP::GetTcpListenAddress(){return &m_pListenSocket->GetAddress();}
			inline jIPacketSocket_IOCP* jTcpServer_IOCP::GetUdpListenSocket(){jASSERT0(0);return 0;}
			inline jIPacketSocket_IOCP* jTcpServer_IOCP::GetUdpSocket(StringID &id){ jASSERT0(0);return 0;}
			inline jIPacketSocket_IOCP* jTcpServer_IOCP::AddUdpSocket(StringID &id,cstr szIP,int port){jASSERT0(0);return 0;}
		}// nNet::Impl

	} //nNET
}//nMech



#endif // __jTcpServer_IOCP_header__
