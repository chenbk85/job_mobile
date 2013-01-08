/* file : jTcpUdpServer_IOCP.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-28 11:23:12
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include <time.h>
#include "jTcpUdpServer_IOCP.h"
#include "interface/squirrel/jISquirrel.h"
#include "Interface/net/jSQ_bind_jINet.h"
#include "jNetGrid.h"
#include <boost/bind.hpp>

#ifndef jFUNC1 
#define jLogT(type) g_Current_LogLevel_jStringID,jx(type)
#define jLogL g_Current_LogLevel_jStringID,jx(NULL)
#define jFUNC1 _T(__FUNCTION__) _T(">")
#endif //jFUNC1 

#include "interface/jIThread.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			jIServer_IOCP* jNet::CreateTcpUdpServer_IOCP(cstr szPlugIn,jIE* pE)
			{
				jIPlugIn_Server_IOCP* pPlugIn = static_cast<jIPlugIn_Server_IOCP*>( jRTTI::New(szPlugIn , _T("jNet") ) );

				if(!pPlugIn)
				{
					jERROR(_T("PlugIn을 못찾음 : %s"), szPlugIn);
					throw szPlugIn;
				}
				pPlugIn->m_pE = pE;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(pE->GetParent());
				g_pjIPacketDispatch->Regist_NamedEvent(pPlugIn->m_pE);
				return new jTcpUdpServer_IOCP(GetProactor(pE),pPlugIn, pE);
			}

#pragma warning(disable : 4355)
			jTcpUdpServer_IOCP::jTcpUdpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP* pPlugIn,jIE* pE)
				:m_pListenSocket(0)
			{
				m_ListenSocketUDP = jPacketSocket_IOCP::_push_back();
				m_ListenSocketUDP->_PostCreate_PS(this,pE->GetAttrVar(_T("QueueSize"))->Get_int() );
				m_pProactor = pIOCP;
				m_iSizeQueue = pE->GetAttrVar(_T("QueueSize"))->Get_int();
				m_pPlugIn = pPlugIn;
				m_pPlugIn->m_pServer= this;
			}
#pragma warning(default : 4355)

			jTcpUdpServer_IOCP::~jTcpUdpServer_IOCP(VOID)
			{
				EndServer();
				jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
				m_pPlugIn=0;
				g_pjNet->DeleteProactor(m_pProactor) ;
				m_pProactor = 0;
			}
			void jTcpUdpServer_IOCP::Release(){delete this;}

			//--------------------------------------------------------------------------
			VOID jTcpUdpServer_IOCP::ResetThreadCallbackUdp(nThread::jIThread*pT)
			//--------------------------------------------------------------------------
			{
				GetjILog()->Log(jLogT(USI),_T("jTcpUdpServer_IOCP ResetThreadCallbackUdp, m_ListenSocketUDP->ResetUdp();"));
				m_ListenSocketUDP->ResetUdp();
				if(m_ExtraListenSocketUDP.size())
				{
					m_ExtraUdpListenSession_CS.Lock();
					m_ExtraListenSocketUDP_it it = m_ExtraListenSocketUDP.begin() , ie = m_ExtraListenSocketUDP.end();
					for(; it!=ie ; ++it)
					{
						it->second->ResetUdp();
					}
					m_ExtraUdpListenSession_CS.UnLock();
				}
			}

			//--------------------------------------------------------------------------
			bool jTcpUdpServer_IOCP::StartServer(jIE* pE)
			//--------------------------------------------------------------------------
			{
				tname32_t ip_buf;
				cstr szIP = ip_string_convert(pE->GetAttr(_T("ServerIP")) , ip_buf);
				tstring sIP = szIP; szIP = _L2G_IP(sIP);

				int tcpPort=pE->GetAttrVar(_T("ServerTcpPort"))->Get_int();
				int maxTcpUser=pE->GetAttrVar(_T("MaxTcpUser"))->Get_int();
				int udpPort=pE->GetAttrVar(_T("ServerUdpPort"))->Get_int();
				//jt_sprintf(m_threadName, _T("jTcpUdpServer_IOCP %s:%d"),szIP,tcpPort);


				try
				{
					if(m_pListenSocket)
					{
						jWARN(_T("서버가 이미 시작되었음."));
						return true;
					}
					//--------------------------------------------------------------------------
					// UDP server run
					//--------------------------------------------------------------------------
					try
					{
						if (!m_pProactor->Begin(this))
							throw _T(__FUNCTION__);
					}
					catch (bool /*isStarted*/)
					{
					}

					if (!m_ListenSocketUDP->Begin_Socket_PS())								throw jS(m_ListenSocketUDP->Begin());
					if (!m_ListenSocketUDP->UdpBind(szIP,udpPort))	throw jS(m_ListenSocketUDP->UdpBind());
					if (!m_pProactor->RegisterSocket(m_ListenSocketUDP->GetSocket(), (ULONG_PTR) &m_ListenSocketUDP))	throw jS(RegisterSocket);
					if (!m_ListenSocketUDP->InitializeReadFromForIocp())	throw jS(m_ListenSocketUDP->InitializeReadFromForIocp);

					nThread::thread_func_t f = boost::bind(&jTcpUdpServer_IOCP::ResetThreadCallbackUdp,this,jBOOST__PLACEHODER_1 ) ;

					g_pjIThreadManager->Run_Timer(f
												, GetThreadName(),jS(ResetThreadCallbackUdp),pv_RUDP_ResetTime);
					//--------------------------------------------------------------------------
					// TCP server run
					//--------------------------------------------------------------------------
					m_pListenSocket  = new jSocket_IOCP();//(this,m_iSizeQueue);// Listen에 사용할 개체를 생성합니다.
					m_pListenSocket->_PostCreate(this,m_iSizeQueue);

					jAUTO_LOCK_CS1(m_pListenSocket_CS);

					if (!m_pListenSocket->Begin_Socket()) throw _T("m_pListenSocket->Begin()");
					if (!m_pListenSocket->TcpBind()) throw _T("m_pListenSocket->TcpBind()");
					if (!m_pListenSocket ->Listen(szIP,tcpPort, maxTcpUser))throw _T("m_pListenSocket->Listen(port, maxTcpUser)");

					// IOCP에 Listen 소켓을 등록시켜 줍니다. 그리고 키로는 해당 개체의 포인터를 설정합니다.
					if (!m_pProactor->RegisterSocket(m_pListenSocket->GetSocket(), reinterpret_cast<ULONG_PTR>(m_pListenSocket )) )
						throw _T("RegisterSocket(m_pListenSocket)");

					if (!m_Connected_PacketSocket_Manager.Begin(this,m_iSizeQueue,m_pListenSocket->GetSocket() , maxTcpUser) )
						throw _T("m_Connected_PacketSocket_Manager.Begin()");

					// KeepAlive 종료 이벤트를 생성합니다.
					nThread::thread_func_t f1 = boost::bind(&jTcpUdpServer_IOCP::KeepThreadCallback,this,jBOOST__PLACEHODER_1 ) ;
					g_pjIThreadManager->Run_Timer(f1
						, GetThreadName() ,jS(KeepThreadCallback), pv_TcpKeepTime);

					fname_t szIP4;
					//jSOCKADDR_IN in(m_pListenSocket->GetSocket());
					//in.ToString(szIP4);
					m_pListenSocket->GetAddress().ToString(szIP4);
					uint16 iPort = m_pListenSocket->GetAddress().GetPort();
					nXML::jE e = pE;
					e.AttrP(jS(SERVICED_PORT)).SetType(jIVar::EDint)->Set_int(iPort);
					pE->GetAttrVar(_T("ServerIP"))->Set_cstr(szIP);

					jLOG(jFUNC1 _T ("tcp server start : %s (user=%d)"),szIP4,maxTcpUser);
					jLOG(jFUNC1 _T ("udp server start : %s"),GetUdpListenSocket()->GetAddressString(szIP4));

					m_ListenSocketUDP->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					m_pPlugIn_Start();
				}
				catch(cstr sz)
				{
					jERROR(_T("%s"),sz);
					m_pProactor->End(this);
					return false;
				}
				catch (...)
				{
					jERROR(_T("Unkown error"));
					m_pProactor->End(this);
					return false;
				}
				return TRUE;
			}

			//--------------------------------------------------------------------------
			void jTcpUdpServer_IOCP::EndServer(VOID)
			//--------------------------------------------------------------------------
			{
				//--------------------------------------------------------------------------
				// 공통
				//--------------------------------------------------------------------------
				jPacketSocketTCP_IOCP_DELETE(m_ListenSocketUDP);
				m_pProactor->End(this);

				//항상 m_pProactor->End 다음에 호출하자.
				//g_pjIThreadManager->End(GetThreadName(),0);

				m_ExtraListenSocketUDP_it it = m_ExtraListenSocketUDP.begin(), ie = m_ExtraListenSocketUDP.end();
				for( ; it!=ie ;++it)
				{
					jPacketSocketTCP_IOCP_DELETE(it->second);
				}
				m_ExtraListenSocketUDP.clear();

				m_Connected_PacketSocket_Manager.End(m_pProactor);

				if (m_pListenSocket )
				{
					jAUTO_LOCK_CS1(m_pListenSocket_CS);
					m_pListenSocket->End_Socket();
				}
				SAFE_DELETE(m_pListenSocket) ;

				m_pPlugIn_Stop();

				GetjILog()->Log(jLogT(USI),_T("jTcpUdpServer_IOCP::End()") );
			}

			void _job_MsgLoopTcpUdpServer( jPacketSocket_IOCP* pS, jIPlugIn_Server_IOCP* pPlugIn )
			{
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE pReadBuff[MAX_BUFFER_LENGTH] = {0,};



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

				while (pS->_getPacket(dwProtocol, pReadBuff, dwPacketLength))
				{
					if(pS->GetFlag_IsDisConnected() || !pS->m_pjIPacketDispatchTable) 
						return ;

#if 0
					if(dwProtocol==eNET_GRID_I_AM_WHO)
					{
						//jTODO 구현예정.
						continue;
					}
#endif
					if(dwProtocol==eNET_SEND_FILE)
					{
						jPARSE_eNET_SEND_FILE(pS);

					}//if(dwProtocol==e NET_SEND_FILE)


					const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
					if(pNEH) 
					{
						pNEH->Call(pS, pReadBuff, dwPacketLength, pPlugIn ,0,0);
						continue;
					}

					jPacket_Base pk;
					pk.buf = pReadBuff;
					pk.len = dwPacketLength;
					pk.num = dwProtocol;

					SquirrelObject* pSO = pPlugIn->GetSQTable();
					if(pSO)
					{
						Get_jPlugInHelpNode(pPlugIn->m_pPHTL, pk.num);// jNamedEventNode* pPHN , tcstr sz
						jt_sprintf(buf,_T("jNET_EVENT_%s"),sz);
						call_SQ_jNetEvent(0);
						continue;
					}

					pPlugIn->OnIoRead(pS->BaseI(), &pk,0,pPlugIn->m_pPHTL);
				}
			}

			void jSchedule_MsgLoopTcpUdpServer(nEVENT::jIMessage* pMsg)
			{
				jIPlugIn_Server_IOCP* pPlugIn= (jIPlugIn_Server_IOCP*)pMsg->GetArg(0)->GetUserData();
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pMsg->GetArg(1)->GetUserData();
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				_job_MsgLoopTcpUdpServer(pS, pPlugIn);
			}

			//--------------------------------------------------------------------------
			VOID jTcpUdpServer_IOCP::OnIoConnected(VOID *object)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;

				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if( !pS->GetFlag_IsDisConnected() ) return;
				pS->SetFlag_IsDisConnected(false);
				pS->SetFlag_IsNeedPostDisconProcess(false);

				fname_t buf;
				if(pS->GetType()<eTCP_SOCKET_END)//tcp
				{
					if( !pS || !pS->GetFlag_IsDisConnected() ) 
						return;
					pS->SetFlag_IsDisConnected(false);

					// 접속한 개체의 IO를 IOCP를 통해서 받기위해서 IOCP에 등록하는 과정을 거치게 됩니다.
					// 여기서 GetSocket을 이용해서 소켓을 등록하고 해당 키는 개체의 포인터를 이용하게 됩니다.
					if (!m_pProactor->RegisterSocket(pS->GetSocket(),reinterpret_cast<ULONG_PTR>(pS))) 
						return;

					// IOCP 초기 받기를 실행해 줍니다.
					if (!pS->InitializeReadForIocp())
					{
						// 만일 실패했을 경우 개체를 재시작해 줍니다.
						GetjILog()->Warning(jLogL,_T("jTcpUdpServer_IOCP::OnIoConnected( %s) - pS->Restart()")
							, pS->GetAddressString(buf) );
						pS->Restart(m_pListenSocket ->GetSocket()); 
						return; 
					}
					pS->SetConnected(TRUE);
					jIP_Address ip;
					pS->GetRemoteAddressAfterAccept(&ip);
					pS->GetAddress().Set(ip.m_IP.s_addr,ip.port);

					pS->GetAddressString(buf);
					GetjILog()->Log(jLogL,_T("jTcpUdpServer_IOCP::OnIoConnected( %s)"), buf );

					if(pv_UseMsgThread->Get_bool())
					{
						if(!pS->m_pMsg_ReadSocket)
						{
							pS->m_pMsg_ReadSocket = g_pjNet->m_pMM_PacketPump->Regist_Loop(0, jFUNC_Msg(jSchedule_MsgLoopTcpUdpServer),2,true);
							pS->m_pMsg_ReadSocket->GetArg(1)->SetUserData(pS);
							pS->m_pMsg_ReadSocket->DoWakeUp();

						}
						pS->m_pMsg_ReadSocket->GetArg(0)->SetUserData((jIPlugIn_Server_IOCP*)this->GetPlugIn());
					}

				}
				else // udp
				{
					jASSERT0(0);//절대 실행안됨.
				}

				if(m_pPlugIn)
				{
					pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					jNET_Plugin_callback_OnIoConnected(m_pPlugIn,pS);
				}

				if(!pS->m_pjIPacketDispatchTable)
				{
					m_pPlugIn->m_pE->DebugPrint(true);
					jMB("pS->m_pjIPacketDispatchTable","NULL입니다.");
				}
			}

			VOID jTcpUdpServer_IOCP::OnIoDisconnected(VOID *object)
			{
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(object);
				if(!pS) return;
				if(pS->GetFlag_IsDelete()) return;

				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if(pS->GetType() < eTCP_SOCKET_END)
				{
					if( !pS || pS->GetFlag_IsDisConnected() ) 
						return;
					pS->SetFlag_IsDisConnected(true);

					// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
					fname_t buf;
					GetjILog()->Log(jLogL,_T("jTcpUdpServer_IOCP::OnIoDisconnected( %s)"), pS->GetAddressString(buf) );
					pS->SetConnected(FALSE);
					pS->Restart(m_pListenSocket ->GetSocket());

					jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);
				}
				else
				{
					jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);

				}
				if( !pS || pS->GetFlag_IsDisConnected() ) 
					return;
				pS->SetFlag_IsDisConnected(true);
				pS->SetFlag_IsNeedPostDisconProcess(true);
				pS->DoWakeUp_ReadSocket();

			}

			//--------------------------------------------------------------------------
			VOID jTcpUdpServer_IOCP::OnIoRead(VOID *object, jPacketLen_t dataLength)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				// 받은 프로토콜과 패킷 길이를 저장하는 변수
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE	pReadBuff[MAX_BUFFER_LENGTH]		= {0,};

				if(pS->GetType()==eUDP_SOCKET)
				{
					jIP_Address ipRead;
					if ( pS->ReadFromPacketForIocp(&ipRead, dataLength) )
					{
						while (pS->_getPacketFrom(&ipRead, dwProtocol, pReadBuff, dwPacketLength) )
						{
							if(pv_UseMsgThread->Get_bool())
							{
								//pS->DoWakeUp_ReadSocket();
								if(!pS->m_pjIPacketDispatchTable) return;
								const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
								if(pNEH) 
								{
									pNEH->Call(pS, pReadBuff, dwPacketLength, this->GetPlugIn(),&ipRead,0);
									continue;
								}
							}

							jPacket_Base pk;
							pk.buf = pReadBuff;
							pk.len = dwPacketLength;
							pk.num = dwProtocol;

							SquirrelObject* pSO = m_pPlugIn->GetSQTable();
							if(pSO)
							{
								Get_jPlugInHelpNode(m_pPlugIn->m_pPHTL, pk.num);// jNamedEventNode* pPHN , tcstr sz
								jt_sprintf(buf,_T("jNET_EVENT_%s"),sz);
								call_SQ_jNetEvent(&ipRead);
							}

							m_pPlugIn->OnIoRead(pS->BaseI(), &pk ,&ipRead ,m_pPlugIn->m_pPHTL );
						}
					}

					if (!pS->InitializeReadFromForIocp())
					{
						jERROR(_T(" jTcpUdpServer_IOCP::OnIoRead() - InitializeReadFromForIocp()") );
						// *_* by icandoit : 2007-06-26 21:25:12 udpserver block때매막아봄
						//End();
						return;
					}
				}
				else // eTCP_SOCKET이면
				{
					if (pS->ReadPacketForIocp(dataLength))
					{
						if(pv_UseMsgThread->Get_bool())
						{
							pS->DoWakeUp_ReadSocket();
						}
						else
						{
							_job_MsgLoopTcpUdpServer(pS, GetPlugIn());
						}
					}
					else
					{
						jWARN_T("pS->ReadPacketForIocp(%d) return false",dataLength);
						pS->Restart(m_pListenSocket ->GetSocket());
					}

					if (!pS->InitializeReadForIocp())
						pS->Restart(m_pListenSocket ->GetSocket());

					// *_* by icandoit : 2007-06-05 13:06:33
					//http://blog.naver.com/h64d5791
					if (pS->GetSocket() == NULL)
						m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);
				}
			}

			//--------------------------------------------------------------------------
			VOID jTcpUdpServer_IOCP::OnIoWrote(VOID *object, jPacketLen_t dwDataLength)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if(pS->GetType()==eUDP_SOCKET) //UDP
				{
					// *_* by icandoit : 2007-08-27 14:50:56
					//pS->WriteComplete();
					GetjILog()->Log(jLogT(USI),_T("\n# jTcpUdpServer_IOCP::OnIoWrote udp data wrote : 0x%x(0x%x)(%d)\n")
						, pS, pS->GetSocket(), dwDataLength);
				}
				else // TCP
				{
					if(m_pPlugIn)
					{
						m_pPlugIn->OnIoWrote(pS->BaseI());
					}
				}
				pS->WriteComplete();

			}

			VOID jTcpUdpServer_IOCP::KeepThreadCallback(nThread::jIThread* pT)
			{
				// 접속해 있는 모든 Session에 패킷을 전송합니다.
				GetjILog()->Log(jLogT(KTCB),_T("연결유지신호 전송, m_Connected_PacketSocket_Manager=%d")
					, m_Connected_PacketSocket_Manager.size());

				jPacketNum_t keep1 = eNET_OGS_TCP_KeepAlive;
				BYTE buf[1024];
				memcpy(buf,&keep1 , sizeof(keep1) );
				time_t curTime = time(NULL);
				memcpy(buf+sizeof(keep1), &curTime, sizeof(time_t));

				jPacket_Base pk;
				pk.num = eNET_OGS_SYSTEM_MSG;
				pk.buf = buf;
				pk.len = sizeof(keep1)+ sizeof(time_t);
				//m_Connected_PacketSocket_Manager.WriteAll(&pk,this);

			}

			jIPacketSocket_IOCP* jTcpUdpServer_IOCP::AddUdpSocket(StringID& id, cstr szIP,int port)
			{
				if(id ==jx(NULL)) return 0;
				m_ExtraListenSocketUDP_it it = m_ExtraListenSocketUDP.find(id);
				if(it!=m_ExtraListenSocketUDP.end()) return 0;
				m_ExtraUdpListenSession_CS.Lock();
				jPacketSocket_IOCP* pS = jPacketSocket_IOCP::_push_back();
				pS->_PostCreate_PS(this,m_iSizeQueue);
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				pS->SetName(nString::Get_jIStringTable()->GetName(id));
				pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);

				m_ExtraListenSocketUDP.insert(m_ExtraListenSocketUDP_vt(id ,pS ) );
				m_ExtraUdpListenSession_CS.UnLock();

				try
				{
					if (!pS->Begin_Socket_PS())						throw _T("pS->Begin_Socket_PS()");
					if (!pS->UdpBind(0,port))		throw _T("pS->UdpBind(%d)");
					if (!m_pProactor->RegisterSocket(pS->GetSocket(), (ULONG_PTR) pS))	throw _T("RegisterSocket");
					if (!pS->InitializeReadFromForIocp()) throw _T("InitializeReadFromForIocp");
				}
				catch (cstr sz)
				{
					jLOG(_T("jTcpUdpServer_IOCP::AddUdpSocket() : %s"), sz);
					m_ExtraUdpListenSession_CS.Lock();
					SAFE_DELETE(pS);
					m_ExtraListenSocketUDP.erase(id);
					m_ExtraUdpListenSession_CS.UnLock();
					return 0;
				}
				return pS;
			}
			jIPacketSocket_IOCP* jTcpUdpServer_IOCP::GetUdpListenSocket(){ return m_ListenSocketUDP;	}
			jIPacketSocket_IOCP* jTcpUdpServer_IOCP::GetUdpSocket(StringID& id)
			{	
				if(id==jx(NULL))
					return m_ListenSocketUDP;

				m_ExtraListenSocketUDP_it it =m_ExtraListenSocketUDP.find(id);
				if(it==m_ExtraListenSocketUDP.end() )return 0;
				return it->second;
			}

			static void jSchedule_Disconnect(nEVENT::jIMessage* pM)
			{
				jTcpUdpServer_IOCP* p = (jTcpUdpServer_IOCP*)pM->GetArg(0)->GetUserData();
				jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)pM->GetArg(1)->GetUserData();
				jPacketSocket_IOCP* pSS = (jPacketSocket_IOCP*)pS;
				if(!p || !pS)
				{
					return;
				}
				shutdown(pSS->GetSocket(),SD_BOTH);
				p->PostDisconnectForProactor(pSS, &pSS->mReadOverlapped.m_OVLP);
				pM->Erase();
			}
			void jTcpUdpServer_IOCP::DisconnectTcpClient(jIPacketSocket_IOCP* pS)
			{
				nEVENT::jIMessage* pM = g_pjNet->m_pMM_PacketPump->Regist_Loop(1, jFUNC_Msg(jSchedule_Disconnect), 2,true);
				pM->DoSleep();
				pM->GetArg(0)->SetUserData(this);
				pM->GetArg(1)->SetUserData(pS);
				pM->DoWakeUp();
			}
		}// nNet::Impl

	} //nNET
}//nMech

