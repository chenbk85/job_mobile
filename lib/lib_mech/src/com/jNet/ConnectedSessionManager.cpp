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

			// jConnected_PacketSocket_Manager를 시작하는 함수
			BOOL jConnected_PacketSocket_Manager::Begin(jIObserver_IOCP* pObs,int iSizeQueue,SOCKET hListenSocket,int iMaxUser)
			{
				// 동기화 개체
				CThreadSync Sync;	

				// 파라미터로 Listen개체의 소켓을 받아야 합니다.
				// 값이 NULL일 경우 실패합니다.
				if (!hListenSocket)
					return FALSE;

				// 최대 접속자만큼의 개체를 미리 생성합니다.
				for (int i=0;i<iMaxUser;i++)
				{
					jPacketSocketTCP_IOCP *pTest_PacketSocket = jPacketSocketTCP_IOCP::_push_back();
					pTest_PacketSocket->_PostCreate_PS(pObs,iSizeQueue);
					// 생성된 개체를 개체를 관리하는 m_vConnectedSessions 벡터에 입력합니다.
					m_vConnectedSessions.push_back(pTest_PacketSocket);
				}

				// 생성한 개체들을 초기화하고 Accep t상태로 만들어 줍니다.
				for (int i=0;i<iMaxUser;i++)
				{
					// 개체 초기화중 실패할 경우 종료시킵니다.
					if (!m_vConnectedSessions[i]->Begin_Socket_PS())
					{
						jConnected_PacketSocket_Manager::End(0);
						return FALSE;
					}

					// 개체를 Accep t상태로 변경하다 문제가 있으면 종료시킵니다.
					if (!m_vConnectedSessions[i]->Accept(hListenSocket))
					{
						jConnected_PacketSocket_Manager::End(0);
						return FALSE;
					}
				}

				return TRUE;
			}

			// ConnectedSessionManager를 종료하는 함수
			VOID jConnected_PacketSocket_Manager::End(jIProactor_IOCP* pProactor)
			{
				// 동기화 개체
				CThreadSync Sync;

				// 최대 접속자만큼의 개체를 삭제합니다.
				for (DWORD i=0;i<m_vConnectedSessions.size();i++)
				{
					// 개체 종료
					jPacketSocketTCP_IOCP_DELETE(m_vConnectedSessions[i]);
				}

				// 관리하는 벡터의 내용을 모두 지워줍니다.
				m_vConnectedSessions.clear();
			}

			// 접속된 모든 Session에 데이터를 전송하는 함수
			VOID jConnected_PacketSocket_Manager::WriteAll(jPacket_Base* pP,jIServer_IOCP* pServer)
			{
				// 동기화 개체
				CThreadSync Sync;

				// 접속된 모든 개체에 WritePacket을 해 줍니다.
				for (DWORD i=0;i<m_vConnectedSessions.size();i++)
				{
					// 접속되어 있는 개체일 경우만 WritePacket을 해 줍니다.
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


