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
					eEST_LISTEN_SOCKET=0, // Listen socket�϶� m_eType=eLISTEN_SOCKE�̸鼭 m_pPacketSocket�� �ε����̴�.
					eEST_TOTAL_SOCKET =WSA_MAXIMUM_WAIT_EVENTS 
				};
				struct jSocketInfo
				{
					WSAEVENT    m_eventHandle[eEST_TOTAL_SOCKET];//�̺�Ʈ ������ ���� �̺�Ʈ ��ü
					//SOCKET		m_socketClient[eTOTAL_SOCKET];//Cliet�� ����Ǵ� ����
					jPacketSocket_IOCP	*m_pPacketSocket[eEST_TOTAL_SOCKET];
				};
				SOCKET				m_ListenSocket;
				jSOCKADDR_IN		m_Listen_in;

			private:
				int m_iSizeQueue;
			protected:
				jSocketInfo m_SocketInfo;//Ŭ���̾�Ʈ ���� ���� ����ü
			private:
				int			m_nClientCnt;//���� �Ǿ��ִ� Ŭ���̾�Ʈ ��
				bool		m_bWorkerRun;//�۾� ������ ���� �÷���

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
