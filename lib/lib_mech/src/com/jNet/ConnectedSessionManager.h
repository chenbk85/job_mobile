#pragma once


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			typedef jPacketSocket_IOCP jPacketSocketTCP_IOCP;

			// ConnectedSession을 관리하는 클래스
			// 다중 스레드 환경에서 안전하게 사용하기 위해서 CMultiThreadSync를 상속받습니다.
			class jConnected_PacketSocket_Manager : public nMech::nNET::nUTIL::CMultiThreadSync<jConnected_PacketSocket_Manager>
			{
			public:
				jConnected_PacketSocket_Manager(VOID);
				virtual ~jConnected_PacketSocket_Manager(VOID);

				// 시작하는 함수
				BOOL Begin(jIObserver_IOCP* pObs,int iSizeQueue,SOCKET hListenSocket,int iMaxUser);
				// 종료하는 함수
				VOID End(jIProactor_IOCP* pProactor);

				// 접속된 모든 ConnectedSession에 패킷을 전송하는 함수
				VOID WriteAll(jPacket_Base* ,jIServer_IOCP* pServer);

				size_t size(){ return m_vConnectedSessions.size();}

			private:
				// 생성된 ConnectedSession개체의 포인터를 관리하는 Vector
				std::vector<jPacketSocketTCP_IOCP*> m_vConnectedSessions;
			};

		}// nNet::Impl

	} //nNET
}//nMech

