/* file : jNetIOModel_EventSelect_CS.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-03 11:59:21
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jNetIOModel_EventSelect_CS_header__
#define __jNetIOModel_EventSelect_CS_header__
#pragma once


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			class jNetIOModel_EventSelect_CS
			{
			public:
				enum EEventSelectType
				{
					eEST_LISTEN_SOCKET=0, // Listen socket일때 m_eType=eLISTEN_SOCKE이면서 m_pPacketSocket의 인덱스이다.
					eEST_TOTAL_SOCKET =WSA_MAXIMUM_WAIT_EVENTS 
				};
				struct jSocketInfo
				{
					WSAEVENT    m_eventHandle[eEST_TOTAL_SOCKET];//이벤트 감지를 위한 이벤트 객체
					//SOCKET		m_socketClient[eTOTAL_SOCKET];//Cliet와 연결되는 소켓
					jPacketSocket_IOCP	*m_pPacketSocket[eEST_TOTAL_SOCKET];
				};
				SOCKET				m_ListenSocket;
				jSOCKADDR_IN		m_Listen_in;

			private:
				int m_iSizeQueue;
			protected:
				jSocketInfo m_SocketInfo;//클라이언트 정보 저장 구조체
			private:
				int			m_nClientCnt;//접속 되어있는 클라이언트 수
				bool		m_bWorkerRun;//작업 쓰레드 동작 플래그

				int getEmptyIndex();
				bool _bindAndListen( cstr szIP,int port);
			public:
				jNetIOModel_EventSelect_CS(VOID);
				virtual ~jNetIOModel_EventSelect_CS(VOID);
				BOOL RegistConnectingSocket(jPacketSocket_IOCP* pS);
				BOOL BeginServer(cstr szIP,int port , int iSizeQueue);
				BOOL			End(VOID);

			protected:

				virtual bool 	OnIoRead(jPacketSocket_IOCP*)			= 0;
				virtual VOID	OnIoConnected(jPacketSocket_IOCP*)=0;
				virtual VOID	OnIoDisconnected(jPacketSocket_IOCP*)=0;

				bool _bindAndListen( cstr szIP,int port , int iMaxUser,int iSizeQueue );
				void DoAccept( SOCKET listenSocket);
			public:
				jIPlugIn_Connection* m_pPlugIn;

				VOID			selectThreadCallback(nThread::jIThread*);

				bool __selectThreadCallback( SOCKET sock, DWORD dwObjIdx, WSANETWORKEVENTS &wsaNetworkEvents, jPacketSocket_IOCP* pS );
				//tstring			m_threadnameSelect;
				void _DoDisconnectSocket(DWORD sock_idx);
			};

		}// nNet::Impl

	} //nNET
}//nMech

#endif // __jNetIOModel_EventSelect_CS_header__
