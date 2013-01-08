/* file : jUdpServer_IOCP.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-19 15:12:42
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jUdpServer_IOCP.h"
#include <process.h>
#include "interface/squirrel/jISquirrel.h"
#include "Interface/net/jSQ_bind_jINet.h"
#include "interface/jIThread.h"
#include "jNetGrid.h"
#include <boost/bind.hpp>

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			jIServer_IOCP* jNet::CreateUdpServer_IOCP(cstr szPlugIn, jIE* pE)
			{
				jIPlugIn_Server_IOCP* pPlugIn = static_cast<jIPlugIn_Server_IOCP*>( jRTTI::New(szPlugIn , _T("jNet")) );

				if(!pPlugIn)
				{
					jERROR(_T("PlugIn을 못찾음 : %s"), szPlugIn);
					throw szPlugIn;
				}
				pPlugIn->m_pE = pE;
				pPlugIn->m_pjINetGrid = Get_jINetGrid(pE->GetParent());

				g_pjIPacketDispatch->Regist_NamedEvent(pPlugIn->m_pE);

				return new jUdpServer_IOCP(GetProactor(pE),pPlugIn,pE);
			}

			void jUdpServer_IOCP::Release()
			{
				delete this;
			}

			//DWORD WINAPI ResetThreadCallback(LPVOID pThreadParam)
#pragma warning(disable : 4355)
			jUdpServer_IOCP::jUdpServer_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Server_IOCP* pPlugIn ,jIE* pE)
			{
				m_UdpListenSession = jPacketSocket_IOCP::_push_back();
				m_UdpListenSession->_PostCreate_PS(this,pE->GetAttrVar(jS(QueueSize))->Get_int() );
				pPlugIn->m_pServer= this;
				m_pPlugIn = pPlugIn;
				m_pProactor = pIOCP;
			}
#pragma warning(default : 4355)

			jUdpServer_IOCP::~jUdpServer_IOCP(VOID)
			{
				EndServer();
				jRTTI::Del( (nMech::jRttiObj*)m_pPlugIn);
				m_pPlugIn=0;
				g_pjNet->DeleteProactor(m_pProactor) ;
				m_pProactor = 0;
			}

			//--------------------------------------------------------------------------
			VOID jUdpServer_IOCP::ResetThreadCallback(nThread::jIThread* pT)
			//--------------------------------------------------------------------------
			{
				m_UdpListenSession->ResetUdp();
			}

			//--------------------------------------------------------------------------
			bool jUdpServer_IOCP::StartServer(jIE* pE)
			//--------------------------------------------------------------------------
			{
				tname32_t ip_buf;
				cstr szIP = ip_string_convert( pE->GetAttr(_T("ServerIP")) , ip_buf) ;
				tstring sIP = szIP; szIP = _L2G_IP(sIP);
				int port = pE->GetAttrVar(_T("ServerUdpPort"))->Get_int();
				jt_sprintf(m_threadname, jFUNC1 _T(" %s:%d"),sIP.c_str(),port);
				try
				{
					if (!m_pProactor->Begin(this))
					{
						jWARN(_T("jNetIOModel_IOCP::Begin 실패 "));
						return FALSE;
					}
				}
				catch (bool /*isStarted*/)
				{
				}

				try
				{
					if (!m_UdpListenSession->Begin_Socket()) throw _T("m_UdpListenSession->Begin()");
					if (!m_UdpListenSession->UdpBind(szIP,port)) throw _T("m_UdpListenSession->UdpBind()");
					if (!m_pProactor->RegisterSocket(m_UdpListenSession->GetSocket(), (ULONG_PTR) &m_UdpListenSession)) 
						throw _T("RegisterSocket(m_UdpListenSession)");

					if (!m_UdpListenSession->InitializeReadFromForIocp()) throw _T("RegisterSocketToIocp");

					m_UdpListenSession->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					nThread::thread_func_t f = boost::bind(&jUdpServer_IOCP::ResetThreadCallback,this,jBOOST__PLACEHODER_1 ) ;
					g_pjIThreadManager->Run_Timer(f, GetThreadName() ,jS(ResetThreadCallback), pv_RUDP_ResetTime);

				}

				catch (cstr  err)
				{
					jERROR(_T("%s"),err);
					m_pProactor->End(this);
					return FALSE;
				}

				m_pPlugIn_Start();

				pE->GetAttrVar(_T("ServerIP"))->Set_cstr(szIP);

				jLOG(_T("Start OK(port=%d)"),port );

				return TRUE;
			}

			//--------------------------------------------------------------------------
			void jUdpServer_IOCP::EndServer()
				//--------------------------------------------------------------------------
			{

				m_pPlugIn_Stop();

				m_pProactor->End(this);
				//항상 m_pProactor->End 다음에 호출하자.
				g_pjIThreadManager->End(GetThreadName(),0);
				jPacketSocketTCP_IOCP_DELETE(m_UdpListenSession);
				return ;
			}

			//--------------------------------------------------------------------------
			// jIProactor가 호출
			VOID jUdpServer_IOCP::OnIoConnected(VOID *object)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				pS->SetConnected(TRUE);
				jNET_Plugin_callback_OnIoConnected(m_pPlugIn,pS);
			}

			//--------------------------------------------------------------------------
			// jIProactor가 호출
			VOID jUdpServer_IOCP::OnIoDisconnected(VOID *object)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;
				if(pS->GetFlag_IsDelete()) return;

				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);
			}

			//--------------------------------------------------------------------------
			// jIProactor가 호출
			VOID jUdpServer_IOCP::OnIoRead(VOID *object, jPacketLen_t dataLength)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;

				jPacketNum_t 	dwProtocol						= 0;
				BYTE	pReadBuff[MAX_BUFFER_LENGTH]		= {0,};
				jPacketLen_t	dwPacketLength					= 0;

				jIP_Address ipRead;
				if ( pS->ReadFromPacketForIocp(&ipRead, dataLength) )
				{
					while (pS->_getPacketFrom(&ipRead, dwProtocol, pReadBuff, dwPacketLength) )
					{
						bool isRuned=false;
						if(pv_UseMsgThread->Get_bool())
						{
							//pS->DoWakeUp_ReadSocket();
							if(!pS->m_pjIPacketDispatchTable) break;
							const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
							if(pNEH) 
							{
								pNEH->Call(pS, pReadBuff, dwPacketLength, this->GetPlugIn(),&ipRead,0);
								isRuned=true;
							}
						}
						if(!isRuned && m_pPlugIn) 
						{
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

							m_pPlugIn->OnIoRead(pS->BaseI(), &pk ,&ipRead,m_pPlugIn->m_pPHTL );
						}
					}
				}

				if (!pS->InitializeReadFromForIocp())
				{
					jERROR(_T(" jUdpServer_IOCP::OnIoRead() - pS->InitializeReadFromForIocp()") );
					// *_* by icandoit : 2007-06-26 21:25:12 udpserver block때매막아봄
					//End();
					return;
				}
			}

			//--------------------------------------------------------------------------
			// jIProactor가 호출
			VOID jUdpServer_IOCP::OnIoWrote(VOID *object, jPacketLen_t dataLength)
			//--------------------------------------------------------------------------
			{
				jPacketSocket_IOCP *pS = (jPacketSocket_IOCP*) object;
				if(!pS) return;
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);

				pS->WriteComplete();

				GetjILog()->Log(jLogT(USI),_T("\n# jUdpServer_IOCP::OnIoWrote udp data wrote : 0x%x(0x%x)(%d)\n")
					, pS, pS->GetSocket(), dataLength);
			}

			void jUdpServer_IOCP::DisconnectTcpClient(jIPacketSocket_IOCP* pS)
			{
				jASSERT0(0);
			}


		}// nNet::Impl

	} //nNET
}//nMech

