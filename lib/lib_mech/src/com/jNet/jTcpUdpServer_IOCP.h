/* file : jTcpUdpServer_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-28 11:23:10
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jTcpUdpServer_IOCP_header__
#define __jTcpUdpServer_IOCP_header__
#pragma once

#include "ConnectedSessionManager.h"



namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			//--------------------------------------------------------------------------
			class jTcpUdpServer_IOCP : public jIObserver_IOCP , public jIServer_IOCP
				//--------------------------------------------------------------------------
			{
				jINTERFACE_HEADER(jIServer_IOCP);
			public:
				jTcpUdpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP* pPlugIn,jIE*);
				virtual ~jTcpUdpServer_IOCP(VOID);
				void PostDisconnectForProactor(VOID *pObject, OVERLAPPED *m_OVLP)
				{
					m_pProactor->PostDisconnect(pObject, m_OVLP);
				}


			private:
				jIProactor_IOCP* m_pProactor;
				jIPlugIn_Server_IOCP* m_pPlugIn;
				
			private: 
				//--------------------------------------------------------------------------
				// UDP관련
				//--------------------------------------------------------------------------
				int m_iSizeQueue;
				jPacketSocket_IOCP			*m_ListenSocketUDP;
				jLIST_TYPEDEF_map(StringID,jPacketSocket_IOCP*,m_ExtraListenSocketUDP);
				nMech::nUtil::jCriticalSection m_ExtraUdpListenSession_CS;
			public:
				VOID	ResetThreadCallbackUdp(nThread::jIThread*);
				//--------------------------------------------------------------------------
				// TCP관련
				//--------------------------------------------------------------------------
			public:
				VOID KeepThreadCallback(nThread::jIThread*);// KeepAlive Thread Callback 함수
				//tname256_t m_threadName;
			//private:
				nMech::nUtil::jCriticalSection m_pListenSocket_CS;
				jSocket_IOCP *m_pListenSocket ;// 서버의 Listen을 담당할 개체
				jConnected_PacketSocket_Manager m_Connected_PacketSocket_Manager;

			public:
				tcstr		GetThreadName(){return m_pPlugIn->m_pE->GetTagName();}
				VOID OnIoRead(VOID *object, jPacketLen_t dataLength);
				VOID OnIoWrote(VOID *object, jPacketLen_t dataLength);
				VOID OnIoConnected(VOID *object);
				VOID OnIoDisconnected(VOID *object);

			};

			inline jSOCKADDR_IN* jTcpUdpServer_IOCP::GetTcpListenAddress(){return &m_pListenSocket->GetAddress();}
			inline jIPlugIn_Server_IOCP* jTcpUdpServer_IOCP::GetPlugIn(){ return m_pPlugIn;}

		}// nNet::Impl

	} //nNET
}//nMech



#endif // __jTcpUdpServer_IOCP_header__
