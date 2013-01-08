#pragma once


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			typedef jPacketSocket_IOCP jPacketSocketTCP_IOCP;

			// ConnectedSession�� �����ϴ� Ŭ����
			// ���� ������ ȯ�濡�� �����ϰ� ����ϱ� ���ؼ� CMultiThreadSync�� ��ӹ޽��ϴ�.
			class jConnected_PacketSocket_Manager : public nMech::nNET::nUTIL::CMultiThreadSync<jConnected_PacketSocket_Manager>
			{
			public:
				jConnected_PacketSocket_Manager(VOID);
				virtual ~jConnected_PacketSocket_Manager(VOID);

				// �����ϴ� �Լ�
				BOOL Begin(jIObserver_IOCP* pObs,int iSizeQueue,SOCKET hListenSocket,int iMaxUser);
				// �����ϴ� �Լ�
				VOID End(jIProactor_IOCP* pProactor);

				// ���ӵ� ��� ConnectedSession�� ��Ŷ�� �����ϴ� �Լ�
				VOID WriteAll(jPacket_Base* ,jIServer_IOCP* pServer);

				size_t size(){ return m_vConnectedSessions.size();}

			private:
				// ������ ConnectedSession��ü�� �����͸� �����ϴ� Vector
				std::vector<jPacketSocketTCP_IOCP*> m_vConnectedSessions;
			};

		}// nNet::Impl

	} //nNET
}//nMech

