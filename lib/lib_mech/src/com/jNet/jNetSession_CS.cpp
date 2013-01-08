/* file : jNetSession_CS.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-03 13:40:30
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jNetSession_CS.h"
#include "header/jCriticalSection.h"
#include "header/MultiThreadSync.h"
#include "jSocket_IOCP.h"
#include "jPacketSocket_IOCP.h"
#include "jNetIOModel_EventSelect.h"
#include "base/jxVar.h"
#include "jNetGrid.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			static void jSchedule_P2PMsgLoop(nMech::nEVENT::jIMessage* pMsg)
			{
				extern void jSchedule_jNetSession_Client_TCP(nMech::nEVENT::jIMessage* pMsg);
				extern void jSchedule_jNetSession_Client_UDP(nMech::nEVENT::jIMessage* pMsg);
				jSchedule_jNetSession_Client_TCP(pMsg);
				jSchedule_jNetSession_Client_UDP(pMsg);
			}

			jINetSession_Service* jNet::CreateNetSession_CS(cstr szPlugIn,jIE* peNetNode)
			{
				jIPlugIn_Connection* pPlugIn = static_cast<jIPlugIn_Connection*>( jRTTI::New(szPlugIn , _T("jNet") ) );

				if(!pPlugIn)
				{
					jERROR(_T("PlugIn을 못찾음 : %s"), szPlugIn);
					throw szPlugIn;
				}
				pPlugIn->m_pE = peNetNode;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(peNetNode->GetParent());
				g_pjIPacketDispatch->Regist_NamedEvent(pPlugIn->m_pE);

				return new jNetSession_CS(pPlugIn,peNetNode);
			}

			void jNetSession_CS::Release()
			{
				delete this;
			}

			jNetSession_CS::jNetSession_CS(jIPlugIn_Connection* pPlugIn,jIE* peNetNode)
				:mTcpReadPacketQueue(peNetNode->GetAttrVar(_T("QueueSize"))->Get_int())
				,mUdpReadPacketQueue(peNetNode->GetAttrVar(_T("QueueSize"))->Get_int())
				,m_iSizeQueue(peNetNode->GetAttrVar(_T("QueueSize"))->Get_int())
			{
				m_pvTcpServerEnable = peNetNode->GetAttrVar(_T("TcpServerEnable"));
				jASSERT0(m_pvTcpServerEnable);
				if(pv_UseMsgThread->Get_bool())
				{
					m_pMsgSockRead = g_pjNet->m_pMM_PacketPump->Regist_Loop(0 , jFUNC_Msg(jSchedule_P2PMsgLoop ), 1, true);
					m_pMsgSockRead->GetArg(0)->SetUserData((jINetSession_Service*)this);
					m_pMsgSockRead->DoWakeUp();

				}

				m_pPlugIn = pPlugIn;
				if(m_pPlugIn)
				{
					m_pPlugIn->m_pClientSession= this;
				}
			}

			jNetSession_CS::~jNetSession_CS(VOID)
			{
				if(m_pMsgSockRead)
				{
					m_pMsgSockRead->Erase();
					m_pMsgSockRead=0;
				}

				jNetSession_CS::EndService();
				jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
				m_pPlugIn=0;
				mTcpReadPacketQueue._PostDelete();
				mUdpReadPacketQueue._PostDelete();
			}

			bool jNetSession_CS::StartTcpServer(cstr szIP,int port ,jIE* peNet)
			{
				tstring sIP = szIP; szIP = _L2G_IP(sIP);

				if(!m_pvTcpServerEnable->Get_bool())
					szIP = 0;

				if(!jNetIOModel_EventSelect_CS::BeginServer(szIP,port,m_iSizeQueue)) return false;

				jIE* it = peNet->begin();
				jrFOR(it)
				{
					Start_ClientSocket(it);
				}

				if(szIP)
					peNet->GetAttrVar(_T("LocalTcpServerIP"))->Set_cstr(szIP);
				m_pPlugIn_Start();

				return true;
			}

			jIPacketSocket_IOCP* jNetSession_CS::ConnectTcp(jPacketSocket_IOCP* pS,cstr szRemoteAddress, USHORT u18RemotePort,jIE* peSocketNode)
			{
				tstring sIP = szRemoteAddress; szRemoteAddress = _L2G_IP(sIP);

				jLOG(_T("jNetSession_CS::ConnectTcp : %s"),peSocketNode->GetTagName());
				pS->SetName(peSocketNode->GetTagName());
				try
				{
					if ( !pS->Begin_Socket_PS() ) throw _T("pS->Begin_Socket_PS");
					if ( !pS->TcpBind() ) throw _T("pS->TcpBind()");
					if ( !jNetIOModel_EventSelect_CS::RegistConnectingSocket(pS) ) throw _T("RegistConnectingSocket");
					if ( !pS->Connect(szRemoteAddress, u18RemotePort) ) throw _T("pS->Connect");
					pS->SetFlag_IsDisConnected(false);

					tname_t buf;
					jLOG(jFUNC1 _T ("(sock=%s)(arg=%s, %d)"),
						pS->GetAddressString(buf),szRemoteAddress, u18RemotePort);
				}
				catch (cstr sz)
				{
					jERROR(_T("(%s)"),sz);
					return 0;
				}
				return pS;
			}

			jIPacketSocket_IOCP* jNetSession_CS::ConnectUdp(jPacketSocket_IOCP* pS,cstr szIP,USHORT u18LocalPort,jIE* peSocketNode)
			{
#if defined(_EXTERNAL_RELEASE_)
				if (u18LocalPort <= 0)
					return 0;
#endif
				tstring sIP = szIP; szIP = _L2G_IP(sIP);

				pS->SetName(peSocketNode->GetTagName());
				try
				{
					if (!pS->Begin_Socket_PS()) throw _T("pS->Begin_Socket_PS()");
					if (!pS->UdpBind(szIP, u18LocalPort)) throw _T("m_ClientSocketSession->UdpBind()");
					if (!jNetIOModel_EventSelect_CS::RegistConnectingSocket(pS))
						throw _T("jNetIOModel_EventSelect_CS::RegistConnectingSocket");
					tname_t buf;
					jLOG(jFUNC1 _T ("(sock=%s,arg=%s,%d)")
						,pS->GetAddressString(buf)
						,szIP, u18LocalPort );
				}
				catch (cstr sz)
				{
					jERROR(_T("(%s) ip=%s,port=%d"),sz,szIP,u18LocalPort);
				}
				return pS;
			}

			void jNetSession_CS::EndService()
			{
				m_pPlugIn_Stop();
				mTcpReadPacketQueue.End();
				mUdpReadPacketQueue.End();
				jNetIOModel_EventSelect_CS::End();

			}

			jIPacketSocket_IOCP* jNetSession_CS::ReadPacket(jPacketNum_t &dwProtocolNumber1
				, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength)
			{
				VOID *pObject = NULL;
				bool is ;
				do {
					is = mTcpReadPacketQueue.Pop(&pObject, dwProtocolNumber1, pPacketBuff, dwPacketLength);
					if(!is)  	return 0;
				} while(!pObject);
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pObject;
				assert(pS->GetType()<eTCP_SOCKET_END);
				return pS;
			}

			jIPacketSocket_IOCP* jNetSession_CS::ReadFromPacket(jPacketNum_t &dwProtocolNumber1
				, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength, jIP_Address* pIP)
			{
				VOID *pObject = NULL;
				bool is ;
				do{
					is= mUdpReadPacketQueue.Pop(&pObject, dwProtocolNumber1, pPacketBuff
						, dwPacketLength, pIP);
					if(!is)  return 0;
				}while(!pObject);
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pObject;
				assert(pS->GetType()==eUDP_SOCKET);
				return pS;
			}

			jIPacketSocket_IOCP* jNetSession_CS::Get_ClientSocket(cstr szName)
			{
				jIE* pE = m_pPlugIn->m_pE->Find(szName,1);
				if(!pE) 
				{
					jWARN(_T("jNetSession_CS::Get_ClientSocket(%s)"),szName);
					return 0;
				}

				jIPacketSocket_IOCP* pS = xGET_USER_DATA(jIPacketSocket_IOCP,pE);
				return pS;

			}

			void jNetSession_CS::OnIoDisconnected(jPacketSocket_IOCP*pS)
			{
				if(pS->GetFlag_IsDelete()) return;

				pS->SetFlag_IsDisConnected(true);

				if(pS->GetType() == nNET::eCONNECTING_SOCKET)
				{
					pS->SetConnected(false);
					jIE* it = m_pPlugIn->m_pE->Find(pS->GetName());
					if(it)
					{
						
						it->SetUserData(jS(jIPacketSocket_IOCP), 0);
						jIPacketSocket_IOCP* p = xGET_USER_DATA(jIPacketSocket_IOCP,it);
						assert(!p);

					}
				}
				else if(pS->GetType()== nNET::eACCEPTED_SOCKET)
				{
				
				}
				else
				{
					jWARN(_T("%s: 처리할수 없는 소켓타입=%d"),_T(__FUNCTION__),pS->GetType() );
				}
			}	

			VOID jNetSession_CS::OnIoConnected(jPacketSocket_IOCP* pS)
			{
				if(pS->GetType()<eTCP_SOCKET_END)//tcp
				{
				}
				else // udp
				{
					jASSERT0(0);//절대 실행안됨.
				}
			}

			jIPacketSocket_IOCP* jNetSession_CS::Start_ClientSocket(jIE* peSocketNode)
			{
				if(!peSocketNode->GetAttrVar(_T("ENABLE") )->Get_bool())
				{
					return 0;
				}
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				if(pS) 
				{
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					jPacketSocketTCP_IOCP_DELETE(pS);
				}

				{
					pS = jPacketSocket_IOCP::_push_back();
					pS->_PostCreate_PS(0,m_iSizeQueue);
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					pS->SetName(peSocketNode->GetTagName());
					pS->m_pE = peSocketNode;
					pS->SetFlag_IsNot_IOCP_Socket(true);
					
					peSocketNode->SetUserData(jS(jIPacketSocket_IOCP), pS);
					pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent_ByTag(peSocketNode);
					jRAISE(pS->m_pjIPacketDispatchTable );

				}

				jIVar* pPType = peSocketNode->GetParent()->GetAttrVar(jS(TYPE));
				if(pPType&& pPType->IsContents(jS(P2PSession)))
				{
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					cstr szName = peSocketNode->GetTagName();
					if(peSocketNode->GetAttrVar(jS(TYPE))->IsContents(_T("TCP")) )
					{
						tstring sBuf;
						int port = _Get_IP_PORT(peSocketNode->Get_cstr(), sBuf);
						ConnectTcp(pS,sBuf.c_str(), port , peSocketNode );
					}
					else 
					{
						tcstr szUdpLocalIP = peSocketNode->GetAttr(_T("UdpLocalIP"));
						jIVar* LocalPort= peSocketNode->GetAttrVar(_T("UdpLocalPort"));
						ConnectUdp(pS,szUdpLocalIP,LocalPort->Get_int(), peSocketNode);
					}
					return pS;
				}
				else
				{
					peSocketNode->DebugPrint(true);
					jWARN(_T("jNetSession_CS::Start_ClientSocket() socket node error"));
				}
				return 0;
			}
			void jNetSession_CS::Stop_ClientSocket(jIE* peSocketNode,bool isRelease)
			{
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				if(!pS) return;

				int isFind=false;
				for(int i=0; i < eEST_TOTAL_SOCKET ; ++i)
				{
					if( m_SocketInfo.m_pPacketSocket[i] == pS)
					{
						_DoDisconnectSocket(i);
						isFind=true;
					}
				}
				if(!isFind)
				{
					peSocketNode->DebugPrint(true);
					jWARN(_T("jNetSession_CS::Stop_ClientSocket : %s not found"),peSocketNode->GetTagName());
				}

				peSocketNode->SetUserData(jS(jIPacketSocket_IOCP),0);
				
				jIPacketSocket_IOCP* p = xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				assert(!p);

			}

		}// nNet::Impl

	} //nNET
}//nMech
