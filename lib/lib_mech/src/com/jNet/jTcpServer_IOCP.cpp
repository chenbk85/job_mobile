/* file : jTcpServer_IOCP.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-19 17:41:07
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jTcpServer_IOCP.h"
#include <process.h>
#include "interface/squirrel/jISquirrel.h"
#include <time.h>
#include "interface/jIThread.h"
#include "jNetGrid.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			jIServer_IOCP* jNet::CreateTcpServer_IOCP(cstr szPlugIn,  jIE* pE)
			{
				jIPlugIn_Server_IOCP* pPlugIn = static_cast<jIPlugIn_Server_IOCP*>( jRTTI::New(szPlugIn , _T("jNet") ) );

				if(!pPlugIn)
				{
					jMB(_T("Plugin��ã��"), szPlugIn);
					jERROR(_T("PlugIn�� ��ã�� : %s"), szPlugIn);
					throw szPlugIn;
				}

				pPlugIn->m_pE = pE;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(pE->GetParent());
				g_pjIPacketDispatch->Regist_NamedEvent(pPlugIn->m_pE);
				return new jTcpServer_IOCP(GetProactor(pE),pPlugIn,pE);
			}

			void jTcpServer_IOCP::Release()
			{
				delete this;
			}

			jIPlugIn_Server_IOCP* jTcpServer_IOCP::GetPlugIn()
			{
				return m_pPlugIn;
			}

			jTcpServer_IOCP::jTcpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP * pPlugIn,jIE* pE)
				:m_iSizeQueue(pE->GetAttrVar(_T("QueueSize"))->Get_int() )
				,m_pListenSocket(0)
			{
				m_pProactor = pIOCP;
				pPlugIn->m_pServer= this;
				m_pPlugIn = pPlugIn;
			}

			jTcpServer_IOCP::~jTcpServer_IOCP(VOID)
			{
				EndServer();
				jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
				m_pPlugIn=0;
				g_pjNet->DeleteProactor(m_pProactor) ;
				m_pProactor = 0;

			}

			VOID jTcpServer_IOCP::KeepThreadCallback(nThread::jIThread* pT)
			{
				// ������ �ִ� ��� Session�� ��Ŷ�� �����մϴ�.
				GetjILog()->Log(jLogT(KTCB),_T("����������ȣ ����, m_Connected_PacketSocket_Manager=%d")
					, m_Connected_PacketSocket_Manager.size());

				jPacketNum_t keep1 = eNET_OGS_TCP_KeepAlive;
				BYTE buf[1024];
				time_t curTime = time(NULL);
				memcpy(buf,&keep1 , sizeof(keep1) );
				memcpy(buf+sizeof(keep1), &curTime, sizeof(time_t));
				
				jPacket_Base pk;
				pk.num = eNET_OGS_SYSTEM_MSG;
				pk.buf = buf;
				pk.len = sizeof(keep1)+ sizeof(time_t);
				m_Connected_PacketSocket_Manager.WriteAll(&pk,this);
			}

			void _job_MsgLoopTcpServer(jIPlugIn_Server_IOCP* pPlugIn,jPacketSocket_IOCP* pS);
			void jSchedule_MsgLoopTcpServer(nEVENT::jIMessage* pMsg)
			{
				jIPlugIn_Server_IOCP* pPlugIn= (jIPlugIn_Server_IOCP*)pMsg->GetArg(0)->GetUserData();
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pMsg->GetArg(1)->GetUserData();
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				_job_MsgLoopTcpServer(pPlugIn,pS);
			}
			void _job_MsgLoopTcpServer(jIPlugIn_Server_IOCP* pPlugIn,jPacketSocket_IOCP* pS)
			{
				jPacketNum_t dwProtocol = 0;
				jPacketLen_t dwPacketLength = 0;
				BYTE pReadBuff[MAX_BUFFER_LENGTH] = {0,};

				if(!pS) return;

				if(pS->GetFlag_IsDisConnected() )
				{
					return ;
				}
				if( !pS->m_pjIPacketDispatchTable)
				{
					jWARN(_T("pS->m_pjIPacketDispatchTable==NULL"));
					return;
				}
				while (pS->_getPacket(dwProtocol, pReadBuff, dwPacketLength))
				{
					if(pS->GetFlag_IsDisConnected() )
					{
						return ;
					}
					if(dwProtocol==eNET_GRID_I_AM_WHO)
					{
						assert(dwPacketLength==IMAX_GRID_NAME_RTTI);
						aname64_t szGridName;
						memcpy(szGridName,pReadBuff,IMAX_GRID_NAME_RTTI);
						szGridName[IMAX_GRID_NAME_RTTI-1]=0;
						vector<astring> out;
						nString::jSplitA(szGridName,":",out);
						if(out.size()>=2)
						{
							tstring str = pPlugIn->m_pE->GetTagName();
							str +=_T("_");
							str +=jT(out[1].c_str());
							pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent_Direct(str.c_str(),jT(out[1].c_str()) );
						}
						bool is =((jNetGrid*)pPlugIn->m_pjINetGrid)->insertGrid(jT(out[0]),pS,pPlugIn);
						jvIF_NOT(is,_T("eNET_GRID_I_AM_WHO : %s"),jT(out[0]))
						{
							pPlugIn->DoDisconnect(pS);
							return;
						}
						jNET_Plugin_callback_OnIoConnected(pPlugIn,pS);
						continue;
					}
					//2009/03/09 HMC jmToDo GPK					
					//if( NULL != pS->m_EnCodeInfo.DeFunc )pS->m_EnCodeInfo.DeFunc( dwProtocol, pReadBuff,dwPacketLength, pS->m_EnCodeInfo.RandIdx);

					if(dwProtocol==eNET_SEND_FILE)
					{
						jPARSE_eNET_SEND_FILE(pS);

					}//if(dwProtocol==e NET_SEND_FILE)


					const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
					if(pNEH)
					{
						jNamedEventNode* pEN = pS->m_pjIPacketDispatchTable->m_pHT->GetByNum(dwProtocol);
						jvCONTINUE(pEN,_T("jTODO : �̼����� ���� �����Ű�� , %d packet number not found : socket(%s)"), pS->GetName());
						if(!pEN->thread_name)
						{
							pNEH->Call(pS, pReadBuff, dwPacketLength, pPlugIn ,0,0);
							continue;
						}
						g_pjNet->Push_To_PacketJobThread(pEN->thread_name, pPlugIn->m_pE->GetTagName(), dwProtocol,pS , pReadBuff , dwPacketLength , pPlugIn ,0,0);
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

			// jIPoractor���� ȣ��
			VOID jTcpServer_IOCP::OnIoConnected(VOID *pObject)
			{
				GetjILog()->Log(jLogT(TSI),_T("OnIoConnected"));
				// ���� �����Լ����� �Ѿ�� pObject�� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
				// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ jPacketSocket_IOCP���� ����ȯ�� �� �־� �ް� �˴ϴ�.
				// ����ȯ�� reinterpret_cast�� ����մϴ�.
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(pObject);
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if( !pS->GetFlag_IsDisConnected() ) return;
				pS->SetFlag_IsDisConnected(false);
				pS->SetFlag_IsNeedPostDisconProcess(false);

				// ������ ��ü�� IO�� IOCP�� ���ؼ� �ޱ����ؼ� IOCP�� ����ϴ� ������ ��ġ�� �˴ϴ�.
				// ���⼭ GetSocket�� �̿��ؼ� ������ ����ϰ� �ش� Ű�� ��ü�� �����͸� �̿��ϰ� �˴ϴ�.
				if (!m_pProactor->RegisterSocket(pS->GetSocket()
					, reinterpret_cast<ULONG_PTR>(pS))) 
					return;

				// IOCP �ʱ� �ޱ⸦ ������ �ݴϴ�.
				if (!pS->InitializeReadForIocp())
				{
					// ���� �������� ��� ��ü�� ������� �ݴϴ�.
					pS->Restart(m_pListenSocket->GetSocket()); 
					return; 
				}

				pS->SetConnected(TRUE);
				jIP_Address ip;
				pS->GetRemoteAddressAfterAccept(&ip);
				pS->GetAddress().Set(ip.m_IP.s_addr,ip.port);

				pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
				jASSERT0(pS->m_pjIPacketDispatchTable);
				
				if(pv_UseMsgThread->Get_bool())
				{
					if(!pS->m_pMsg_ReadSocket)
					{
						pS->m_pMsg_ReadSocket = g_pjNet->m_pMM_PacketPump->Regist_Loop(0, jFUNC_Msg(jSchedule_MsgLoopTcpServer),2,true);
						pS->m_pMsg_ReadSocket->GetArg(0)->SetUserData((jIPlugIn_Server_IOCP*)this->GetPlugIn() );
						pS->m_pMsg_ReadSocket->GetArg(1)->SetUserData(pS);
						pS->m_pMsg_ReadSocket->DoWakeUp();
					}
				}

				fname_t szGridNameRTTI_buf;
				cstr szGridName = ((jNetGrid*)m_pPlugIn->m_pjINetGrid)->get_GridName(m_pPlugIn->m_pE,m_pPlugIn,szGridNameRTTI_buf);
				if(szGridName)
				{
					BYTE buf[1024];
					memcpy(buf,jA(szGridName), IMAX_GRID_NAME_RTTI );
					buf[IMAX_GRID_NAME_RTTI-1]=0;
					jPacket_Base pk;
					pk.num = eNET_GRID_WHO_ARE_YOU;
					pk.buf = buf;
					pk.len = IMAX_GRID_NAME_RTTI;
					pS->WritePacket(&pk);
				}
				else
				{
					jNET_Plugin_callback_OnIoConnected(m_pPlugIn,pS);
				}
		
			}
			VOID jTcpServer_IOCP::OnIoDisconnected(VOID *pObject)
			{
				if(!pObject) return;

				// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
				// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ jPacketSocket_IOCP���� ����ȯ�� �� �־� �ް� �˴ϴ�.
				// ����ȯ�� reinterpret_cast�� ����մϴ�.
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(pObject);

				if(!pS) return;
				if(pS->GetFlag_IsDelete()) return;

				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				if( pS->GetFlag_IsDisConnected() ) return;
				pS->SetFlag_IsDisConnected(true);
				pS->SetFlag_IsNeedPostDisconProcess(true);

				jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);

				// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
				pS->Restart(m_pListenSocket->GetSocket());
				pS->SetConnected(FALSE);
				GetjILog()->Log(jLogT(TSI),_T("OnIoDisconnected"));

			}

			// jIPoractor���� ȣ��
			VOID jTcpServer_IOCP::OnIoRead(VOID *pObject, jPacketLen_t dwDataLength)
			{
				GetjILog()->Log(jLogT(TSI),_T("OnIoRead"));

				// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ 
				// ����� ��ü�� �Ѿ���� �˴ϴ�.
				// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ jPacketSocket_IOCP���� ����ȯ�� �� �־� �ް� �˴ϴ�.
				// ����ȯ�� reinterpret_cast�� ����մϴ�.
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(pObject);
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				// CNetworkSession���� CPacketSession���� �����͸� �����ɴϴ�.
				if (pS->ReadPacketForIocp(dwDataLength))
				{
					if(pv_UseMsgThread->Get_bool())
					{
						pS->DoWakeUp_ReadSocket();
					}
					else
					{
						_job_MsgLoopTcpServer( GetPlugIn() , pS);
					}
				}
				else
				{
					jWARN_T("pS->ReadPacketForIocp(%d) return false",dwDataLength);
					pS->Restart(m_pListenSocket->GetSocket());
				}

				if (!pS->InitializeReadForIocp())
					pS->Restart(m_pListenSocket->GetSocket());

				// *_* by icandoit : 2007-06-05 13:06:33
				//http://blog.naver.com/h64d5791
				if (pS->GetSocket() == NULL)
					m_pProactor->PostDisconnect(pS, &pS->mReadOverlapped.m_OVLP);

			}

			// jIPoractor���� ȣ��
			VOID jTcpServer_IOCP::OnIoWrote(VOID *pObject, jPacketLen_t dwDataLength)
			{
				GetjILog()->Log(jLogT(TSI),_T("OnIoWrote"));
				jPacketSocket_IOCP *pS = reinterpret_cast<jPacketSocket_IOCP*>(pObject);
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				if(m_pPlugIn)
				{
					m_pPlugIn->OnIoWrote(pS->BaseI());
				}
				pS->WriteComplete();


			}

			bool jTcpServer_IOCP::StartServer(jIE* pE)
			{
				tname32_t ip_buf;
				cstr szIP = ip_string_convert(pE->GetAttr(_T("ServerIP") ),ip_buf);
				tstring sIP = szIP; szIP = _L2G_IP(sIP);
				int port = pE->GetAttrVar(_T("ServerTcpPort"))->Get_int();
				int maxUser = pE->GetAttrVar(_T("MaxTcpUser"))->Get_int();

				//jt_sprintf(m_threadName, _T("jTcpServer_IOCP %s:%d"),szIP,port);

				if(m_pListenSocket) 
				{
					jWARN(_T("������ �̹� ���۵Ǿ���."));
					return true;
				}
				try
				{
					// ���� m_pProactor�� ���۵Ǿ����� �׳� ����
					if (!m_pProactor->Begin(this)) return FALSE;
				}
				catch (bool /*isStarted*/)
				{
				}

				try
				{
					// Listen�� ����� ��ü�� �����մϴ�.
					m_pListenSocket  = new jSocket_IOCP;
					m_pListenSocket->_PostCreate(this,m_iSizeQueue);
					{
						jAUTO_LOCK_CS1(m_pListenSocket_CS);
						if (!m_pListenSocket->Begin_Socket()) throw false;
						if (!m_pListenSocket->TcpBind()) throw false;
						if (!m_pListenSocket->Listen(szIP,port, maxUser)) throw false;
						// IOCP�� Listen ������ ��Ͻ��� �ݴϴ�. �׸��� Ű�δ� �ش� ��ü�� �����͸� �����մϴ�.
						if (!m_pProactor->RegisterSocket(m_pListenSocket->GetSocket()
							, reinterpret_cast<ULONG_PTR>(m_pListenSocket ))) throw false;
						if (!m_Connected_PacketSocket_Manager.Begin(this,m_iSizeQueue,m_pListenSocket->GetSocket(), maxUser) ) throw false;
					}



					nThread::thread_func_t f = boost::bind(&jTcpServer_IOCP::KeepThreadCallback,this,jBOOST__PLACEHODER_1 );

					g_pjIThreadManager->Run_Timer(f , GetThreadName(),jS(KeepThreadCallback), pv_TcpKeepTime);
				}
				catch (bool isFail)
				{
					// ���� �������� ��� �����մϴ�.
					m_pProactor->End(this); 
					return isFail; 
				}

				m_pPlugIn_Start();

				fname_t bufIP;
				m_pListenSocket->GetAddress().ToString(bufIP);
				pE->GetAttrVar(_T("ServerIP"))->Set_cstr(szIP);
				jLOG(_T("jTcpServer_IOCP::StartServer(%s user=%d)"),bufIP, maxUser);
				return TRUE;
			}

			void jTcpServer_IOCP::EndServer(VOID)
			{
				if(!m_pListenSocket) 
				{
					jWARN(_T("jTcpServer_IOCP::EndServer() �̹� ���� �����Ϸ�"));
					return;
				}

				m_pPlugIn_Stop();

				// jTcpServer_IOCP�� �����Ҷ�


				// IOCP�� �����մϴ�.
				m_pProactor->End(this);

				//m_pProactor->End���� g_pjIThreadManager->End(GetThreadName(),0);�� ȣ���ߴ��� �׻�Ȯ������.
				//g_pjIThreadManager->End(GetThreadName(),0);

				// jConnected_PacketSocket_Manager�� �����մϴ�.
				m_Connected_PacketSocket_Manager.End(m_pProactor);

				// �����ߴ� Listen�� ��ü�� �����ϰ� ������ �ݴϴ�.
				if (m_pListenSocket )
				{
					jAUTO_LOCK_CS1(m_pListenSocket_CS);
					m_pListenSocket->End_Socket();
				}
				SAFE_DELETE(m_pListenSocket);

				GetjILog()->Log(jLogT(TSI),_T("jTcpServer_IOCP::EndServer()" ) );

			}

			void jSchedule_Disconnect(nEVENT::jIMessage* pM)
			{
				jTcpServer_IOCP* p = (jTcpServer_IOCP*)pM->GetArg(0)->GetUserData();
				jIPacketSocket_IOCP* pSS = (jIPacketSocket_IOCP*)pM->GetArg(1)->GetUserData();
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pSS;
				if(!p || !pS)
				{
					return;
				}
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				shutdown(pS->GetSocket(),SD_BOTH);
				p->PostDisconnectForProactor(pS, &pS->mReadOverlapped.m_OVLP);
				//p->OnIoDisconnected(pSS);
				pM->Erase();
			}
			void jTcpServer_IOCP::DisconnectTcpClient(jIPacketSocket_IOCP* pS)
			{
				nEVENT::jIMessage* pM = g_pjNet->m_pMM_PacketPump->Regist_Loop(1, jFUNC_Msg(jSchedule_Disconnect), 2,true);
				pM->GetArg(0)->SetUserData(this);
				pM->GetArg(1)->SetUserData(pS);
				pM->DoWakeUp();
				g_pjNet->DoWakeUp_Msg();
			}

		}// nNet::Impl

	} //nNET
}//nMech

