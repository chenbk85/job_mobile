#include "stdafx.h"
#include "header/jCriticalSection.h"
#include "header/MultiThreadSync.h"
#include "jSocket_IOCP.h"
#include "jPacketSocket_IOCP.h"
#include "jNetIOModel_EventSelect.h"
#include "jNetSession_Client.h"
#include "base/jxVar.h"
#include "interface/squirrel/jISquirrel.h"
#include "Interface/net/jSQ_bind_jINet.h"
#include "jNetGrid.h"

#ifndef jFUNC1 
#define jLogT(type) g_Current_LogLevel_jStringID,jx(type)
#define jLogL g_Current_LogLevel_jStringID,jx(NULL)
#define jFUNC1 _T(__FUNCTION__) _T(">")
#endif //jFUNC1 


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			void jSchedule_jNetSession_Client_TCP(nMech::nEVENT::jIMessage* pMsg)
			{
				jINetSession_Service* pHost = (jINetSession_Service*)pMsg->GetArg(0)->GetUserData();
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE pReadBuff[MAX_BUFFER_LENGTH] = {0,};
				jPacketSocket_IOCP* pS;
				//tcp
				while(1)
				{
					pS= (jPacketSocket_IOCP*)pHost->ReadPacket(dwProtocol, pReadBuff, dwPacketLength);
					if (!pS)		break;
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					if(pS->GetFlag_IsDisConnected() )
					{
						jWARN(_T("2 pS->GetFlag_IsDisConnected()==true"));
						return ;
					}
					if( !pS->m_pjIPacketDispatchTable)
					{
						jWARN(_T("2 pS->m_pjIPacketDispatchTable==NULL"));
						return;
					}

					if(pS->m_pjIPacketDispatchTable)
					{
						const _jNamed_Event_Handler* pNEH= pS->m_pjIPacketDispatchTable->find(dwProtocol);
						if(pNEH) 
						{
							pNEH->Call(pS, pReadBuff, dwPacketLength, pHost->GetPlugIn(),0,0);
							continue;
						}
						jPacket_Base pk;
						pk.buf = pReadBuff;
						pk.len = dwPacketLength;
						pk.num = dwProtocol;

						SquirrelObject* pSO = pHost->GetPlugIn()->GetSQTable();
						if(pSO && !pSO->IsNull())
						{
							Get_jPlugInHelpNode(pHost->GetPlugIn()->m_pPHTL , pk.num);// jNamedEventNode* pPHN , tcstr sz

							if( pHost->GetPlugIn()->m_pE->GetAttrVar(jS(TYPE))->IsContents(jS(P2PSession)) )
							{
								tcstr szHEADER = pS->Get_jIE()->GetAttr(jS(HEADER));
								jt_sprintf(buf,_T("jNET_EVENT_%s_%s"),sz,szHEADER);
							}
							else
							{
								jt_sprintf(buf,_T("jNET_EVENT_%s"),sz);
							}
							call_SQ_jNetEvent(0);
						}
						pHost->GetPlugIn()->OnIoRead(pS,&pk,0,pHost->GetPlugIn()->m_pPHTL);
					}
				}
			}

			void jSchedule_jNetSession_Client_UDP(nMech::nEVENT::jIMessage* pMsg)
			{
				jINetSession_Service* pHost = (jINetSession_Service*)pMsg->GetArg(0)->GetUserData();
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE pReadBuff[MAX_BUFFER_LENGTH] = {0,};
				jPacketSocket_IOCP* pS;
				// udp
				nMech::nNET::jIP_Address ipRead;
				while(1)
				{
					pS = (jPacketSocket_IOCP*)pHost->ReadFromPacket(dwProtocol,pReadBuff, dwPacketLength, &ipRead );
					if (!pS)  break;
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					if(pS->GetFlag_IsDisConnected() )
					{
						jWARN(_T("2 pS->GetFlag_IsDisConnected()==true"));
						return ;
					}
					if( !pS->m_pjIPacketDispatchTable)
					{
						jWARN(_T("2 pS->m_pjIPacketDispatchTable==NULL"));
						return;
					}

					if(pS->m_pjIPacketDispatchTable)
					{
						const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
						if(pNEH) 
						{
							pNEH->Call(pS, pReadBuff, dwPacketLength, pHost->GetPlugIn(),&ipRead,0);
							continue;
						}

						jPacket_Base pk;
						pk.buf = pReadBuff;
						pk.len = dwPacketLength;
						pk.num = dwProtocol;

						SquirrelObject* pSO = pHost->GetPlugIn()->GetSQTable();
						if(pSO)
						{
							Get_jPlugInHelpNode(pHost->GetPlugIn()->m_pPHTL , pk.num);// jNamedEventNode* pPHN , tcstr sz
							if( pHost->GetPlugIn()->m_pE->GetAttrVar(jS(TYPE))->IsContents(jS(P2PSession)) )
							{
								tcstr szHEADER = pS->Get_jIE()->GetAttr(jS(HEADER));
								jt_sprintf(buf,_T("jNET_EVENT_%s_%s"),sz,szHEADER);
							}
							else
							{
								jt_sprintf(buf,_T("jNET_EVENT_%s"),sz);
							}
							call_SQ_jNetEvent(&ipRead);
						}

						pHost->GetPlugIn()->OnIoRead(pS,&pk,&ipRead,pHost->GetPlugIn()->m_pPHTL);
					}
				}
			}

			jINetSession_Service* jNet::CreateClientSession(cstr szPlugIn,jIE* peNetNode)
			{
				jIPlugIn_Connection* pPlugIn = static_cast<jIPlugIn_Connection*>(		jRTTI::New(szPlugIn , _T("jNet")) );

				if(!pPlugIn)
				{
					jERROR(_T("PlugIn을 못찾음 : %s"), szPlugIn);
					throw szPlugIn;
				}
				pPlugIn->m_pE = peNetNode;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(peNetNode->GetParent());

				return new jNetSession_Client(pPlugIn,peNetNode);
			}

			void jNetSession_Client::Release()
			{
				delete this;
			}

			jNetSession_Client::jNetSession_Client(jIPlugIn_Connection* pPlugIn,jIE* peNetNode)
				:mReadPacketQueue(peNetNode->GetAttrVar(_T("QueueSize"))->Get_int())
				,m_iSizeQueue(peNetNode->GetAttrVar(_T("QueueSize"))->Get_int())
				,m_iFlag(0)
			{
				m_ClientSocketSession= jPacketSocket_IOCP::_push_back();
				m_ClientSocketSession->_PostCreate_PS(0,peNetNode->GetAttrVar(_T("QueueSize"))->Get_int());

				m_pPlugIn = pPlugIn;
				if(m_pPlugIn)
				{
					m_pPlugIn->m_pClientSession = this;
				}
				m_ClientSocketSession->SetFlag_IsNot_IOCP_Socket(true);
			}

			jNetSession_Client::~jNetSession_Client(VOID)
			{
				if(m_pPlugIn)
				{
					m_pPlugIn_Stop();

					jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
					m_pPlugIn=0;
				}
				jNetSession_Client::_endService();
				mReadPacketQueue._PostDelete();
			}

			jIPacketSocket_IOCP* jNetSession_Client::ConnectTcp(cstr szRemoteAddress, USHORT u18RemotePort,cstr szName)
			{
				if(GetFlag_StartService())
				{
					jWARN(_T("EndService()가 호출안된 상황에서 시작됨. 호출종료."));
					return 0;
				}
				if (!szRemoteAddress || u18RemotePort <= 0)
					return 0;
#if 0
				if(m_ClientSocketSession->GetConnected())
				{
					jWARN(_T("jNetSession_Client::ConnectTcp() 이미 소켓이 접속되어 있음"));
					return &m_ClientSocketSession;
				}
#endif

				tstring sIP = szRemoteAddress;
				szRemoteAddress = _L2G_IP(sIP);


				if (!m_ClientSocketSession->Begin_Socket_PS())
				{
					End();
					return 0;
				}

				if (!m_ClientSocketSession->TcpBind())
				{
					End();
					return 0;
				}

				if (!jNetIOModel_EventSelect::Begin(m_ClientSocketSession))
				{
					End();
					return 0;
				}

				if (!m_ClientSocketSession->Connect(szRemoteAddress, u18RemotePort))
				{
					End();
					return 0;
				}
				m_ClientSocketSession->SetFlag_IsDisConnected(false);
				if(pv_UseMsgThread->Get_bool())
				{
					m_ClientSocketSession->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					jASSERT0(m_ClientSocketSession->m_pjIPacketDispatchTable);
					if(!m_ClientSocketSession->m_pMsg_ReadSocket)
					{
						m_ClientSocketSession->m_pMsg_ReadSocket 
							= g_pjNet->m_pMM_PacketPump->Regist_Loop(0,jFUNC_Msg(jSchedule_jNetSession_Client_TCP), 1,true);
						m_ClientSocketSession->m_pMsg_ReadSocket->GetArg(0)->SetUserData((jINetSession_Service*)this);
						m_ClientSocketSession->m_pMsg_ReadSocket->DoWakeUp();
					}
				}

				m_pPlugIn_Start();

				jLOG(jFUNC1 _T("(remote: %s, %d)"),szRemoteAddress, u18RemotePort);

				SetFlag_StartService(true);
				//m_ClientSocketSession->SetConnected(true);
				return m_ClientSocketSession;

			}

			jIPacketSocket_IOCP* jNetSession_Client::ConnectUdp(cstr szIP,USHORT u18myPort,cstr szName)
			{
#if defined(_EXTERNAL_RELEASE_)
				if (u18myPort <= 0)
					return FALSE;
#endif
				tstring sIP = szIP;
				szIP = _L2G_IP(sIP);
				if(m_ClientSocketSession->GetConnected())
				{
					jWARN(_T("jNetSession_Client::ConnectUdp() 이미 소켓이 접속되어 있음"));
					return m_ClientSocketSession;
				}

				if (!m_ClientSocketSession->Begin_Socket_PS())
				{
					End();
					return 0;
				}

				if (!m_ClientSocketSession->UdpBind(szIP, u18myPort))
				{
					End();
					return 0;
				}

				if (!jNetIOModel_EventSelect::Begin(m_ClientSocketSession))
				{
					End();
					return 0;
				}
				m_ClientSocketSession->SetFlag_IsDisConnected(false);

				if(pv_UseMsgThread->Get_bool())
				{
					m_ClientSocketSession->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					jASSERT0(m_ClientSocketSession->m_pjIPacketDispatchTable);
					if(!m_ClientSocketSession->m_pMsg_ReadSocket)
					{
						m_ClientSocketSession->m_pMsg_ReadSocket 
							= g_pjNet->m_pMM_PacketPump->Regist_Loop(0,jFUNC_Msg(jSchedule_jNetSession_Client_UDP), 1,true);
						m_ClientSocketSession->m_pMsg_ReadSocket->GetArg(0)->SetUserData((jINetSession_Service*)this);
						m_ClientSocketSession->m_pMsg_ReadSocket->DoWakeUp();
					}
				}

				m_pPlugIn_Start();

				tname_t buf;
				jLOG(jFUNC1 _T("(%s)"), m_ClientSocketSession->GetAddressString(buf));

				//m_ClientSocketSession->SetConnected(true);

				SetFlag_StartService(true);

				return m_ClientSocketSession;
			}


			jIPacketSocket_IOCP* jNetSession_Client::ReadPacket(jPacketNum_t &dwProtocolNumber1
				, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength)
			{
				jASSERT0(m_ClientSocketSession->GetType()<eTCP_SOCKET_END);
				VOID *m_pVoid = NULL;
				bool is = mReadPacketQueue.Pop(&m_pVoid, dwProtocolNumber1, pPacketBuff, dwPacketLength);
				if(!is) return 0;
				return ((jPacketSocket_IOCP*)m_pVoid);
			}

			jIPacketSocket_IOCP* jNetSession_Client::ReadFromPacket(jPacketNum_t &dwProtocolNumber1
				, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength, jIP_Address* pIP)
			{
				jASSERT0(m_ClientSocketSession->GetType()==eUDP_SOCKET);
				VOID *m_pVoid = NULL;
				bool is = mReadPacketQueue.Pop(&m_pVoid, dwProtocolNumber1, pPacketBuff
					, dwPacketLength, pIP);
				if(!is) return 0;
				return ((jPacketSocket_IOCP*)m_pVoid);
			}

			void jNetSession_Client::OnIoRead(jPacketSocket_IOCP*)
			{
				m_ClientSocketSession->process_Client_OnIoReadFrom(mReadPacketQueue);
			}

			jIPacketSocket_IOCP* jNetSession_Client::Get_ClientSocket(cstr)
			{
				return m_ClientSocketSession;
			}
			void jNetSession_Client::_endService()
			{
				jPacketSocketTCP_IOCP_DELETE(m_ClientSocketSession);
				jNetIOModel_EventSelect::End();
				SetFlag_StartService(false);
			}
			static void jSchedule_jNetSession_Client_endService(nEVENT::jIMessage* pM)
			{
				if(pM->GetRemainCount()==1)
				{
					jNetSession_Client* _this = (jNetSession_Client*)pM->GetArg(0)->GetUserData();
					_this->_endService();
				}
				g_pjNet->DoWakeUp_Msg();
			}
			void jNetSession_Client::EndService(VOID)
			{

				//if(!GetFlag_StartService()) 		return;
				m_pPlugIn_Stop();

				// 플러그인쪽에서 스톱시 패킷을 날릴수 있으므로 그것을 처리하기 위해...
				nEVENT::jIMessage* pM = g_pjNet->m_pMM_PacketPump->Regist_CountBase(0,jFUNC_Msg(jSchedule_jNetSession_Client_endService), 1,3);
				pM->GetArg(0)->SetUserData(this);
				pM->DoWakeUp();
				g_pjNet->DoWakeUp_Msg();
			}

			void jNetSession_Client::OnIoDisconnected(jPacketSocket_IOCP* pS)
			{
				//jNetIOModel_EventSelect::OnIoDisconnected(pS);
				//클라이언트로 접속중 서버쪽에서 disconnect되었을때 클라이언트 종료처리중 쓰래기 jPakcetSocket_IOCP객체가 사용되는 버그를 위해 추가
				//나중에 제거 하고 테스트 해봐야함. 생략가능할것 같음.
				_endService();
			}
			jIPacketSocket_IOCP* jNetSession_Client::Start_ClientSocket(jIE* peSocketNode)
			{

				return 0;
			}
			void jNetSession_Client::Stop_ClientSocket(jIE* peSocketNode,bool isRelease)
			{

			}

		}// nNet::Impl
	} //nNET
}//nMech


