/* file : jClient_IOCP.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-05-09 12:49:04
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jClient_IOCP.h"
#include "interface/squirrel/jISquirrel.h"
#include "Interface/net/jSQ_bind_jINet.h"
#include "base/jxVar.h"
#include "Interface/jILog.h"
#include "interface/jIThread.h"
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
			void _job_MsgLoop_jClient_IOCP( jPacketSocket_IOCP* pS, jIPlugIn_Connection* pPlugIn )
			{
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE pReadBuff[MAX_BUFFER_LENGTH] = {0,};

				if(!pS) return;
				// CPacketSession에서 패킷을 뽑아 냅니다.
				if(!pS->m_pjIPacketDispatchTable)
				{
					jLOG(jFUNC1 _T("pS->m_pjIPacketDispatchTable==NULL : pk=%d, len = %d\n"),dwProtocol, dwPacketLength);
					return;
				}
				while (pS->_getPacket(dwProtocol, pReadBuff, dwPacketLength))
				{
					if(pS->GetFlag_IsDisConnected()) return;
					if(dwProtocol==eNET_OGS_SYSTEM_MSG)
					{
						// jTODO jPacketNum_t수정됨. 작동하는지 확인 활것.
						if(dwPacketLength==sizeof(jPacketNum_t))
						{
							jPacketNum_t msg = *(jPacketNum_t*)pReadBuff;
							if(msg ==eNET_OGS_TCP_KeepAlive)
							{
								GetjILog()->Log(jLogT(KTCB), jFUNC1 _T(" KeepAliveMsg reached"));
							}
						}
						continue;
					}//if(dwProtocol==eNET_OGS_SYSTEM_MSG)
					if(dwProtocol==eNET_GRID_WHO_ARE_YOU)
					{
						assert(dwPacketLength==IMAX_GRID_NAME_RTTI);
						aname32_t szGridNameServer;
						memcpy(szGridNameServer,pReadBuff,IMAX_GRID_NAME_RTTI);
						szGridNameServer[IMAX_GRID_NAME_RTTI-1]=0;
						fname_t szGridNameRTTI_buf;
						tcstr szGridNameRTTI = ((jNetGrid*)pPlugIn->m_pjINetGrid)->get_GridName(pS->m_pE,pPlugIn, szGridNameRTTI_buf);
						if(!szGridNameRTTI)
						{
							pPlugIn->m_pE->DebugPrint(true);
							jERROR_T("szGridNameRTTI == NULL");
							continue;
						}

						BYTE buf[1024];
						aname64_t szSendGridName;
						jIVar* pV = pS->Get_jIE()->GetAttrVar(jS(CHANGE_SERVER_HEADER));
						if( pV && pV->Get_bool() )
							ja_sprintf(szSendGridName , "%s:%s" ,jA(szGridNameRTTI), jA(pS->Get_jIE()->GetAttr(jS(HEADER)) ) );
						else
							ja_sprintf(szSendGridName , "%s" ,jA(szGridNameRTTI));

						memcpy(buf,jA(szSendGridName), IMAX_GRID_NAME_RTTI );
						buf[IMAX_GRID_NAME_RTTI-1]=0;

						jPacket_Base pk;
						pk.num = eNET_GRID_I_AM_WHO;
						pk.buf = buf;
						pk.len = IMAX_GRID_NAME_RTTI;
						pS->WritePacket(&pk);

						if(((jNetGrid*)pPlugIn->m_pjINetGrid)->insertGrid(jT(szGridNameServer),pS,pPlugIn)) 
						{
							jNET_Plugin_callback_OnIoConnected(pPlugIn, pS);
						}
						else
						{
							pPlugIn->DoDisconnect(pS);
						}
						continue;
					}//if(dwProtocol==eNET_GRID_WHO_ARE_YOU)


					if(!pS->m_pjIPacketDispatchTable) 
					{
						if(pS->m_pE)
							pS->m_pE->DebugPrint(true);
						jERROR(_T("pS->m_pjIPacketDispatchTable==NULL (SOCKET=%s), protocal = %d"),pS->GetName() ,dwProtocol);
						return;
					}

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
					else
					{
						jPacket_Base pk;
						pk.buf = pReadBuff;
						pk.len = dwPacketLength;
						pk.num = dwProtocol;

						SquirrelObject* pSO = pPlugIn->GetSQTable();
						if(pSO)
						{
							Get_jPlugInHelpNode(pS->m_pjIPacketDispatchTable->m_pHT , pk.num);// jNamedEventNode* pPHN , tcstr sz
							jt_sprintf(buf,_T("jNET_EVENT_%s"),sz);
							call_SQ_jNetEvent(0);
						}
						pPlugIn->OnIoRead(pS->BaseI(), &pk,0,pS->m_pjIPacketDispatchTable->m_pHT);
					}
				}
			}//_job_MsgLoop_jClient_IOCP

			static void jSchedule_MsgLoop_IOCP_TcpCliet(nEVENT::jIMessage* pMsg)
			{
				jIPlugIn_Connection* pPlugIn= (jIPlugIn_Connection*)pMsg->GetArg(0)->GetUserData();
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pMsg->GetArg(1)->GetUserData();
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				_job_MsgLoop_jClient_IOCP(pS, pPlugIn);
				return;

			}
			jINetSession_Service* jNet::Create_jClient_IOCP(cstr szPlugIn,jIE* pE)
			{
				jIPlugIn_Connection* pPlugIn = static_cast<jIPlugIn_Connection*>( jRTTI::New(szPlugIn , _T("jNet") ) );

				if(!pPlugIn)
				{
					jERROR(_T("PlugIn을 못찾음 : %s"), szPlugIn);
					throw szPlugIn;
				}
				pPlugIn->m_pE = pE;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(pE->GetParent());

				return new jClient_IOCP(g_pjNet->GetProactor(pE),pPlugIn, pE);
			}

			jClient_IOCP::jClient_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Connection* pPlugIn,jIE* pE)
			{
				m_pProactor = pIOCP;
				m_pvSizeQueue = pE->GetAttrVar(_T("QueueSize"));
				m_pPlugIn = pPlugIn;
				m_pPlugIn->m_pClientSession= this;
			}

			jClient_IOCP::~jClient_IOCP(VOID)
			{
				End();
				jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
				m_pPlugIn=0;
				g_pjNet->DeleteProactor(m_pProactor) ;
				m_pProactor = 0;
			}
			void jClient_IOCP::Release(){delete this;}

			//--------------------------------------------------------------------------
			VOID jClient_IOCP::ResetThreadCallbackUdp(nThread::jIThread* pT)
				//--------------------------------------------------------------------------
			{
				jAUTO_LOCK_CS1(m_listUdpClientSocket_CS);
				if(!m_listUdpClientSocket.size()) return;

				m_listUdpClientSocket_it it = m_listUdpClientSocket.begin() , ie = m_listUdpClientSocket.end();
				for(; it!=ie ; ++it)
				{
					(*it)->ResetUdp();
				}
			}

			struct jxStart_IOCPClientNode
			{
				jClient_IOCP* pObj;
				jxStart_IOCPClientNode(jClient_IOCP* p):pObj(p){}
				void operator()(jIE* it)
				{
					if(it->size()==0)
						pObj->Start_ClientSocket(it);
				}
			};

			//--------------------------------------------------------------------------
			bool jClient_IOCP::Start(jIE* pE)
				//--------------------------------------------------------------------------
			{
				//jt_sprintf(m_threadName , _T("%s(%s)"),m_pPlugIn->m_pE->GetTagName(),pE->GetTagName());
				m_listUdpClientSocket.clear();
				
				try
				{
					//--------------------------------------------------------------------------
					// UDP server run
					//--------------------------------------------------------------------------
					if (!m_pProactor->Begin(this)) throw jFUNC;
					nThread::thread_func_t f = boost::bind(&jClient_IOCP::ResetThreadCallbackUdp,this,jBOOST__PLACEHODER_1 );
					g_pjIThreadManager->Run_Timer(f,GetThreadName(),jS(ResetThreadCallbackUdp),pv_RUDP_ResetTime);
					m_pPlugIn_Start();

					pE->for_each(jxStart_IOCPClientNode(this));
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
			struct jxdelete_IOCPClientNode
			{
				jClient_IOCP* pObj;
				jxdelete_IOCPClientNode(jClient_IOCP* p):pObj(p){}
				void operator()(jIE* it)
				{
					if(it->size()==0)
						pObj->delete_ClientSocket(it);
				}
			};
			//--------------------------------------------------------------------------
			void jClient_IOCP::End(VOID)
				//--------------------------------------------------------------------------
			{
				//--------------------------------------------------------------------------
				// UDP
				//--------------------------------------------------------------------------

				//--------------------------------------------------------------------------
				// 공통
				//--------------------------------------------------------------------------
				m_pProactor->End(this);

				m_pPlugIn->m_pE->for_each(jxdelete_IOCPClientNode(this));

				m_pPlugIn_Stop();

				//g_pjIThreadManager->End(GetThreadName(),0);

				GetjILog()->Log(jLogT(USI) ,_T("jClient_IOCP::End()") );
			}

			//--------------------------------------------------------------------------
			VOID jClient_IOCP::OnIoConnected(VOID *object)
				//--------------------------------------------------------------------------
			{
				jASSERT(0,_T("사용 되면 안되는 함수."));
			}

			static void job_reconnect(nEVENT::jIMessage* pM)
			{
				jIE* pejClient_IOCP = (jIE*)pM->GetArg(0)->GetUserData();
				cstr szName = pM->GetArg(1)->Get_cstr();
				jINetSession_Service* pObj1 = xGET_USER_DATA(jINetSession_Service,pejClient_IOCP);
				jClient_IOCP* pObj = (jClient_IOCP*)pObj1;
				jRETURN(pObj);

				jIE* pE = pejClient_IOCP->Find(szName);
				jRETURN(pE);
				jRETURN(pE->GetAttrVar(jS(TYPE)));
				jRETURN(pE->GetAttrVar(jS(TYPE))->IsContents(jS(TCP) ));
				pObj->Start_ClientSocket(pE);
			}

			VOID jClient_IOCP::OnIoDisconnected(VOID *object)
			{
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(object);
				if(!pS)
				{
					jERROR(_T("pS==NULL"));
					return;
				}
				if(pS->GetFlag_IsDelete()) return;

				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				bool is = pS->GetFlag_IsConnected_jClient_IOCP();
				if(!is)
				{
					// 왜 is==false가 되는지 확인해야함.
					//jWARN(_T("pS->GetFlag_IsConnected_jClient_IOCP()==false"));
					return;
				}
				pS->SetFlag_IsConnected_jClient_IOCP(false);
				pS->SetFlag_IsNeedPostDisconProcess(true);
				
				jIE* peParent = pS->Get_jIE()->GetParent();
				tstring sName = pS->Get_jIE()->GetTagName();
				int iRetry=0;
				jIVar* pvCONNECT_RETRY_SEC = pS->Get_jIE()->GetAttrVar(jS(CONNECT_RETRY_SEC));
				if(pvCONNECT_RETRY_SEC && pvCONNECT_RETRY_SEC->Get_int() >0)
				{
					iRetry = pvCONNECT_RETRY_SEC->Get_int();
				}

				jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);
				jPacketSocketTCP_IOCP_DELETE(pS);
// 				if(iRetry)
// 				{
// 					nEVENT::jIMessage* pM = g_pjNet->m_pMM_PacketPump->Regist_TimeBase(0,jFUNC_Msg(job_reconnect), 2,(float)iRetry);
// 					pM->GetArg(0)->SetUserData(m_pPlugIn->m_pE);
// 					pM->GetArg(1)->Set_cstr(sName.c_str());
// 					pM->DoWakeUp();
// 				}
			}

			//--------------------------------------------------------------------------
			VOID jClient_IOCP::OnIoRead(VOID *object, jPacketLen_t dataLength)
				//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;

				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if(pS->GetType()==eUDP_SOCKET)
				{
					jPacketNum_t dwProtocol = 0;
					jPacketLen_t dwPacketLength = 0;
					BYTE	pReadBuff[MAX_BUFFER_LENGTH]		= {0,};

					jIP_Address ipRead;
					if ( pS->ReadFromPacketForIocp(&ipRead, dataLength) )
					{
						while (pS->_getPacketFrom(&ipRead, dwProtocol, pReadBuff, dwPacketLength) )
						{
							if(pv_UseMsgThread->Get_bool())
							{
								//pS->DoWakeUp_ReadSocket();
								if(!pS->m_pjIPacketDispatchTable)
								{
									jERROR(_T("!pS->m_pjIPacketDispatchTable "));
									break;
								}
								const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
								if(pNEH ) 
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
								Get_jPlugInHelpNode(pS->m_pjIPacketDispatchTable->m_pHT , pk.num);// jNamedEventNode* pPHN , tcstr sz
								jt_sprintf(buf,_T("jNET_EVENT_%s_%s"),sz,pS->Get_jIE()->GetAttr(jS(HEADER)) );
								call_SQ_jNetEvent(&ipRead);
							}

							m_pPlugIn->OnIoRead(pS->BaseI(), &pk ,&ipRead,pS->m_pjIPacketDispatchTable->m_pHT );
						}
					}

					if (!pS->InitializeReadFromForIocp())
					{
						jERROR(_T(" jClient_IOCP::OnIoRead() - InitializeReadFromForIocp()") );
						// *_* by icandoit : 2007-06-26 21:25:12 udpserver block때매막아봄
						//End();
						m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);
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
							_job_MsgLoop_jClient_IOCP(pS,  GetPlugIn());
						}
					}//if (pS->ReadPacketForIocp(dataLength))
					else
					{
						jWARN_T("pS->ReadPacketForIocp(%d) return false",dataLength);
						m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);
						return;
					}

					if (!pS->InitializeReadForIocp())
					{
						m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);
						return;
					}

					// *_* by icandoit : 2007-06-05 13:06:33
					//http://blog.naver.com/h64d5791
					if (pS->GetSocket() == NULL)
						m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);

				}
			}

			//--------------------------------------------------------------------------
			VOID jClient_IOCP::OnIoWrote(VOID *object, jPacketLen_t dwDataLength)
				//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;

				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if(pS->GetType()==eUDP_SOCKET) //UDP
				{
					// *_* by icandoit : 2007-08-27 14:50:56
					GetjILog()->Log(jLogT(USI) , _T("\n# jClient_IOCP::OnIoWrote udp data wrote : 0x%x(0x%x)(%d)\n")
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

			//--------------------------------------------------------------------------
			jIPacketSocket_IOCP* jClient_IOCP::add_ClientSocket(jIE* peSocketNode)
			//--------------------------------------------------------------------------
			{
				nXML::jE e = peSocketNode;
				if(!peSocketNode->GetAttrVar(jS(ENABLE))->Get_bool()) return 0;

				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);

				if(pS) 
				{
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					jPacketSocketTCP_IOCP_DELETE(pS);
				}
				pS = jPacketSocket_IOCP::_push_back();
				pS->_PostCreate_PS(this,m_pvSizeQueue->Get_int());
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				pS->SetName(peSocketNode->GetTagName());
				pS->m_pE = peSocketNode;
				pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent_ByTag(peSocketNode);
				jRAISE(pS->m_pjIPacketDispatchTable);
				peSocketNode->SetUserData(jS(jIPacketSocket_IOCP),pS->BaseI() );
				return pS;
			}

			//--------------------------------------------------------------------------
			jIPacketSocket_IOCP* jClient_IOCP::Get_ClientSocket(tcstr sz)
			//--------------------------------------------------------------------------
			{
				jIE* peSocketNode = m_pPlugIn->m_pE->FindByPath(sz);
				//jIE* peSocketNode = m_pPlugIn->m_pE->Find(sz,1);
				if(!peSocketNode) return 0;
				return xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
			}
			void DisableNagle(SOCKET s) {
				const char chOpt = 1;
				setsockopt( s, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char) );
			}

			//--------------------------------------------------------------------------
			jIPacketSocket_IOCP* jClient_IOCP::Start_ClientSocket(jIE* peSocketNode)
			//--------------------------------------------------------------------------
			{
				if(!peSocketNode->GetAttrVar(jS(ENABLE))->Get_bool()) return 0;
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				//jvRETURN_ret(0 ,pS==NULL ,_T("check please : exist connecting") );
				//jvRETURN_ret(0, pS && pS->GetFlag_IsConnected_jClient_IOCP() ,_T(" Exist socket is connected"));
				nXML::jE e = peSocketNode;
				try
				{
					if(!pS) pS = (jPacketSocket_IOCP*)add_ClientSocket(peSocketNode);
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

					pS->SetFlag_IsConnected_jClient_IOCP(false);
					if (!pS->Begin_Socket_PS())						throw _T("pS->Begin_Socket_PS()");
					if( e.Attr(jS(TYPE))->IsContents(jS(UDP)) )
					{
						if (!pS->UdpBind(0,e.Attr(jS(UdpLocalPort))->Get_int() ) )		throw _T("pS->UdpBind(%d)");
						if (!m_pProactor->RegisterSocket(pS->GetSocket(), (ULONG_PTR) pS))	throw _T("RegisterSocket");
						if (!pS->InitializeReadFromForIocp()) throw _T("InitializeReadFromForIocp");
						jAUTO_LOCK_CS1(m_listUdpClientSocket_CS);
						m_listUdpClientSocket.push_back(pS);
					}
					else
					{
						if( !pS->TcpBind()) throw _T("pS->TcpBind()");

						tstring sBuf;

						cstr szIP12 = e.Var()->Get_cstr() ;
						int port = _Get_IP_PORT(szIP12, sBuf);
						if(port < 0) throw _T("IP Adress format");

						if (!m_pProactor->RegisterSocket(pS->GetSocket(), (ULONG_PTR) pS))	throw _T("RegisterSocket");
						DisableNagle( pS->GetSocket() );

						if (!pS->Connect(sBuf.c_str(), port ) ) throw _T("pS->Connect()");
						if (!pS->InitializeReadForIocp()) throw _T("pS->InitializeReadForIocp()");


						pS->SetFlag_IsDisConnected(false);
						pS->SetFlag_IsNeedPostDisconProcess(false);

						pS->SetConnected(TRUE);
						fname_t buf;
						pS->GetAddressString(buf);
						GetjILog()->Log(GetCurrentThreadId(),jx(jNet_DLL),jx(NULL),_T("jClient_IOCP::Start_ClientSocket( %s,%s)"), buf ,peSocketNode->GetTagName());

						if(pv_UseMsgThread->Get_bool() )
						{
							if(!pS->m_pMsg_ReadSocket)
							{
								pS->m_pMsg_ReadSocket = g_pjNet->m_pMM_PacketPump->Regist_Loop(0, jFUNC_Msg(jSchedule_MsgLoop_IOCP_TcpCliet),2,true);
								jRAISE(pS->m_pMsg_ReadSocket->GetArgCount() ==2);
								pS->m_pMsg_ReadSocket->GetArg(1)->SetUserData(pS);
								pS->m_pMsg_ReadSocket->GetArg(0)->SetUserData((jIPlugIn_Connection*)this->GetPlugIn());
								pS->m_pMsg_ReadSocket->DoWakeUp();
							}
						}
					}
					pS->SetFlag_IsConnected_jClient_IOCP(true);
					if(pS->GetType() !=nNET::eUDP_SOCKET)
					{
						fname_t szGridNameRTTI_buf;
						tcstr szGridNameRTTI = ((jNetGrid*)GetPlugIn()->m_pjINetGrid)->get_GridName(pS->m_pE,GetPlugIn(), szGridNameRTTI_buf);
						if(!szGridNameRTTI)
						{
							jNET_Plugin_callback_OnIoConnected(GetPlugIn(), pS);
						}
					}
				}
				catch (cstr sz)
				{
					e->DebugPrint(true);
					jWARN(_T("jClient_IOCP::Start_ClientSocket() : %s"), sz);

					if( e.Attr(jS(TYPE))->IsContents(jS(UDP) ) )
					{
						jAUTO_LOCK_CS1(m_listUdpClientSocket_CS);
						m_listUdpClientSocket_it it = jFIND(m_listUdpClientSocket, pS);
						if(it!=m_listUdpClientSocket.end()) m_listUdpClientSocket.erase(it);
					}
					jPacketSocketTCP_IOCP_DELETE(pS);
					return 0;
				}
				return pS;
			}

			//--------------------------------------------------------------------------
			static void jSchedule_Disconnect(nEVENT::jIMessage* pM)
			//--------------------------------------------------------------------------
			{
				jClient_IOCP* p = (jClient_IOCP*)pM->GetArg(0)->GetUserData();
				jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)pM->GetArg(1)->GetUserData();
				jPacketSocket_IOCP* pSS = (jPacketSocket_IOCP*)pS;
				if(!p || !pS)
				{
					return;
				}
				//shutdown(pSS->GetSocket(),SD_BOTH);
				p->PostDisconnectForProactor(pSS, &pSS->mReadOverlapped.m_OVLP);
				pM->Erase();

			}
			
			//--------------------------------------------------------------------------
			void jClient_IOCP::Stop_ClientSocket(jIE* peSocketNode,bool isRelease)
			//--------------------------------------------------------------------------
			{
				jIPacketSocket_IOCP* pSS = xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				if(!pSS) return;
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pSS;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				shutdown(pS->GetSocket(),SD_BOTH);
				if(isRelease)
				{
					PostDisconnectForProactor(pS, &pS->mReadOverlapped.m_OVLP);
					//delete_ClientSocket(peSocketNode);
					return;
				}
				if( !pS->IsConnected() ) return;
				pS->SetConnected(false);
				nEVENT::jIMessage* pM = g_pjNet->m_pMM_PacketPump->Regist_Loop(1, jFUNC_Msg(jSchedule_Disconnect), 3,true);
				pM->DoSleep();
				pM->GetArg(0)->SetUserData(this);
				pM->GetArg(1)->SetUserData(pS);
				pM->DoWakeUp();
				g_pjNet->DoWakeUp_Msg();
			}

			//--------------------------------------------------------------------------
			void jClient_IOCP::delete_ClientSocket(jIE* peSocketNode)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
				if(!pS) return ;
				{
					nUtil::jCriticalSection::Auto a1(&pS->m_CS_jPacketSocket);
					nUtil::jCriticalSection::Auto a2(&m_listUdpClientSocket_CS);
					m_listUdpClientSocket_it it = jFIND(m_listUdpClientSocket, pS);
					if(it!=m_listUdpClientSocket.end()) m_listUdpClientSocket.erase(it);
					peSocketNode->SetUserData(jS(jIPacketSocket_IOCP),0);
					jIPacketSocket_IOCP* p = xGET_USER_DATA(jIPacketSocket_IOCP,peSocketNode);
					assert(!p);
					jPacketSocketTCP_IOCP_DELETE(pS);
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech

