#include "stdafx.h"
#include "ConnectedSessionManager.h"


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{

			jConnected_PacketSocket_Manager::jConnected_PacketSocket_Manager(VOID)
			{
			}

			jConnected_PacketSocket_Manager::~jConnected_PacketSocket_Manager(VOID)
			{
			}

			// jConnected_PacketSocket_Manager�� �����ϴ� �Լ�
			BOOL jConnected_PacketSocket_Manager::Begin(jIObserver_IOCP* pObs,int iSizeQueue,SOCKET hListenSocket,int iMaxUser)
			{
				// ����ȭ ��ü
				CThreadSync Sync;	

				// �Ķ���ͷ� Listen��ü�� ������ �޾ƾ� �մϴ�.
				// ���� NULL�� ��� �����մϴ�.
				if (!hListenSocket)
					return FALSE;

				// �ִ� �����ڸ�ŭ�� ��ü�� �̸� �����մϴ�.
				for (int i=0;i<iMaxUser;i++)
				{
					jPacketSocketTCP_IOCP *pTest_PacketSocket = jPacketSocketTCP_IOCP::_push_back();
					pTest_PacketSocket->_PostCreate_PS(pObs,iSizeQueue);
					// ������ ��ü�� ��ü�� �����ϴ� m_vConnectedSessions ���Ϳ� �Է��մϴ�.
					m_vConnectedSessions.push_back(pTest_PacketSocket);
				}

				// ������ ��ü���� �ʱ�ȭ�ϰ� Accep t���·� ����� �ݴϴ�.
				for (int i=0;i<iMaxUser;i++)
				{
					// ��ü �ʱ�ȭ�� ������ ��� �����ŵ�ϴ�.
					if (!m_vConnectedSessions[i]->Begin_Socket_PS())
					{
						jConnected_PacketSocket_Manager::End(0);
						return FALSE;
					}

					// ��ü�� Accep t���·� �����ϴ� ������ ������ �����ŵ�ϴ�.
					if (!m_vConnectedSessions[i]->Accept(hListenSocket))
					{
						jConnected_PacketSocket_Manager::End(0);
						return FALSE;
					}
				}

				return TRUE;
			}

			// ConnectedSessionManager�� �����ϴ� �Լ�
			VOID jConnected_PacketSocket_Manager::End(jIProactor_IOCP* pProactor)
			{
				// ����ȭ ��ü
				CThreadSync Sync;

				// �ִ� �����ڸ�ŭ�� ��ü�� �����մϴ�.
				for (DWORD i=0;i<m_vConnectedSessions.size();i++)
				{
					// ��ü ����
					jPacketSocketTCP_IOCP_DELETE(m_vConnectedSessions[i]);
				}

				// �����ϴ� ������ ������ ��� �����ݴϴ�.
				m_vConnectedSessions.clear();
			}

			// ���ӵ� ��� Session�� �����͸� �����ϴ� �Լ�
			VOID jConnected_PacketSocket_Manager::WriteAll(jPacket_Base* pP,jIServer_IOCP* pServer)
			{
				// ����ȭ ��ü
				CThreadSync Sync;

				// ���ӵ� ��� ��ü�� WritePacket�� �� �ݴϴ�.
				for (DWORD i=0;i<m_vConnectedSessions.size();i++)
				{
					// ���ӵǾ� �ִ� ��ü�� ��츸 WritePacket�� �� �ݴϴ�.
					if (m_vConnectedSessions[i]->GetConnected())
					{
						bool is = m_vConnectedSessions[i]->WritePacket(pP);
						if(!is)
						{
							pServer->DisconnectTcpClient(m_vConnectedSessions[i]);
						}
					}
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech


