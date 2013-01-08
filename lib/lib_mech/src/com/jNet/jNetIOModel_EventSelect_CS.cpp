/* file : jNetIOModel_EventSelect_CS.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-03 11:59:23
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jNetIOModel_EventSelect_CS.h"
#include <process.h>
#include "interface/jIThread.h"
#include <boost/bind.hpp>

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
			void jNetIOModel_EventSelect_CS::selectThreadCallback(nThread::jIThread* pT)
			{
				WSANETWORKEVENTS	wsaNetworkEvents;
				DWORD				dwObjIdx = 0;
				// *_* by icandoit : 2007-06-05 12:41:32
				//http://blog.naver.com/h64d5791
				while (m_bWorkerRun)
				{
					GetjILog()->Log(jLogT(STCB),_T("WaitForMultipleObjects"));
					//////////////////////////////////////////////////////////////////
					//요청한 m_OVLP I/O작업이 완료되었는지 이벤트를 기다린다.
					dwObjIdx = WSAWaitForMultipleEvents( eEST_TOTAL_SOCKET , 
						m_SocketInfo.m_eventHandle ,FALSE ,INFINITE,FALSE );

					//에러 발생
					if( WSA_WAIT_FAILED == dwObjIdx)
					{
						jERROR(_T("[selectThreadCallback] WSAWaitForMultipleEvents 실패 : %d" )
							,	WSAGetLastError() );
						break;
					}
					SOCKET sock;
					jPacketSocket_IOCP* pS =0;
					if(dwObjIdx==eEST_LISTEN_SOCKET)
					{
						sock = m_ListenSocket;
					}
					else 
					{
						pS = m_SocketInfo.m_pPacketSocket[ dwObjIdx ];
						if(!pS) continue;
						sock = pS->GetSocket();
					}

					if(pS)
					{
						jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
						if(!__selectThreadCallback(sock, dwObjIdx, wsaNetworkEvents, pS))
							return;
					}
					else
					{
						if(!__selectThreadCallback(sock, dwObjIdx, wsaNetworkEvents, pS))
							return;
					}
				}
			}
			void jNetIOModel_EventSelect_CS::_DoDisconnectSocket(DWORD sock_idx)
			{
				jPacketSocket_IOCP* pS = m_SocketInfo.m_pPacketSocket[ sock_idx ];
				if(!pS) return;
				{
					jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
					jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,pS);

					OnIoDisconnected(pS);
					jPacketSocketTCP_IOCP_DELETE(pS);
				}
				m_SocketInfo.m_pPacketSocket[ sock_idx ] =0;

			}


			jNetIOModel_EventSelect_CS::jNetIOModel_EventSelect_CS(VOID)
			{
				m_iSizeQueue=0;
				m_bWorkerRun = true;
				m_nClientCnt = 0;
				m_ListenSocket=INVALID_SOCKET;
				//클라이언트 구조체의 초기화
				for( int i = 0; i < eEST_TOTAL_SOCKET; i++ )
				{
					m_SocketInfo.m_pPacketSocket[i] = 0;
					m_SocketInfo.m_eventHandle[i] = 0;//WSACreateEvent();
				}
			}

			jNetIOModel_EventSelect_CS::~jNetIOModel_EventSelect_CS(VOID)
			{
				for(int i=0; i < eEST_TOTAL_SOCKET ; ++i)
				{
#if 0
					CloseHandle(m_SocketInfo.m_eventHandle[i]);
					m_SocketInfo.m_eventHandle[i]=0;
#endif
					if(i==eEST_LISTEN_SOCKET)
					{
					}
					else
					{
						if(m_SocketInfo.m_pPacketSocket[i])
						{
							jPacketSocketTCP_IOCP_DELETE(m_SocketInfo.m_pPacketSocket[i]);
						}
					}
				}
			}

			//사용되지 않은 Index반환
			int jNetIOModel_EventSelect_CS::getEmptyIndex()
			{
				//0번째 배열은 정보갱신용 이벤트이다.
				for( int i = eEST_LISTEN_SOCKET+1; i < eEST_TOTAL_SOCKET ; i++ )
				{
					if( !m_SocketInfo.m_pPacketSocket[ i ] )//|| !m_SocketInfo.m_pPacketSocket[ i ]->GetSocket())
						return  i;
				}
				return -1;
			}

			//서버의 주소정보를 소켓과 연결시키고 접속 요청을 받기 위해 그 소켓을 등록하는 함수
			bool jNetIOModel_EventSelect_CS::_bindAndListen( cstr szIP,int port)
			{
				SOCKET listenSocket = WSASocket( AF_INET , SOCK_STREAM 
					, IPPROTO_TCP , NULL , NULL , WSA_FLAG_OVERLAPPED );
				if( INVALID_SOCKET == listenSocket )	throw _T("listenSocket = WSASocket");
				m_ListenSocket = listenSocket;
				nNET::nUTIL_SOCKET::Set_REUSEADDR(listenSocket);
				m_Listen_in.Set(szIP,port);

				int nRet = ::bind( listenSocket	, (SOCKADDR*) &m_Listen_in , sizeof( SOCKADDR_IN ) );
				if( 0 != nRet )	throw _T("bind( m_SocketInfo.m_ pListenSocket");

				nRet = WSAEventSelect( listenSocket
					,m_SocketInfo.m_eventHandle[eEST_LISTEN_SOCKET] ,	FD_ACCEPT | FD_CLOSE );
				if( SOCKET_ERROR == nRet )	throw _T("WSAEventSelect( listenSocket)");

				//접속 요청을 받아들이기 위해 m_socketListen소켓을 등록하고 접속대기큐를 5개로 설정 한다.
				nRet = listen( listenSocket , 5);
				m_Listen_in.Set(listenSocket);

				if( 0 != nRet ) throw _T("listen( m_SocketInfo.m_ pListenSocket");
				return true;
			}

			BOOL jNetIOModel_EventSelect_CS::RegistConnectingSocket(jPacketSocket_IOCP* pS)
			{
				int idx = getEmptyIndex();
				if(idx==-1) throw _T("jNetIOModel_EventSelect_CS::RegistConnectingSocket : clent full");
				m_SocketInfo.m_pPacketSocket[ idx ] = pS;
				DWORD Result = WSAEventSelect(pS->GetSocket() 
					, m_SocketInfo.m_eventHandle[idx] , FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
				if (Result == SOCKET_ERROR) throw _T("WSAEventSelect");
				return true;
			}

			BOOL jNetIOModel_EventSelect_CS::BeginServer(cstr szIP,int port , int iSizeQueue)
			{
				try
				{
					//클라이언트 구조체의 초기화
					for( int i = 0; i < eEST_TOTAL_SOCKET; i++ )
					{
						m_SocketInfo.m_eventHandle[i] = WSACreateEvent();
					}

					m_iSizeQueue = iSizeQueue;
					if(szIP)
					{
						_bindAndListen(szIP,port);
						tname_t buf;
						m_Listen_in.ToString(buf);
						jLOG(_T("StartTcpServer(%s, iSizeQueue=%d)")
							,buf,m_iSizeQueue);
					}
					else
					{
						jLOG(_T("Server Create Skip by UserSetting"));
					}
					nThread::thread_func_t f = boost::bind(&jNetIOModel_EventSelect_CS::selectThreadCallback,this,jBOOST__PLACEHODER_1 );
					g_pjIThreadManager->Run(f,m_pPlugIn->m_pE->GetTagName(),jS(selectThreadCallback) ,true);

				}
				catch (cstr szErr)
				{
					jERROR(_T(" %s"),szErr);
					End();
					return FALSE;
				}
				return TRUE;
			}

			BOOL jNetIOModel_EventSelect_CS::End(VOID)
			{
				if(m_ListenSocket!=INVALID_SOCKET)
				{
					jNet::CloseSocket( m_ListenSocket );
					m_ListenSocket=INVALID_SOCKET;
				}

				if(m_SocketInfo.m_eventHandle[eEST_LISTEN_SOCKET] )
				{
					// 종료이벤트
					SetEvent(m_SocketInfo.m_eventHandle[eEST_LISTEN_SOCKET] );
					g_pjIThreadManager->End(m_pPlugIn->m_pE->GetTagName(),0);
					for(int i=0; i < eEST_TOTAL_SOCKET ; ++i)
					{
						if(i!=eEST_LISTEN_SOCKET)
						{
							jPacketSocketTCP_IOCP_DELETE(m_SocketInfo.m_pPacketSocket[i]);
						}
						CloseHandle(m_SocketInfo.m_eventHandle[i]);
						m_SocketInfo.m_eventHandle[i]=0;

					}
				}
				return TRUE;
			}

			void jNetIOModel_EventSelect_CS::DoAccept( SOCKET listenSocket)
			{
				int nAddrLen = sizeof( SOCKADDR_IN );
				//접속을 받을 구조체의 인덱스를 얻어온다.
				int nIdx = getEmptyIndex();
				if( -1 == nIdx )	throw _T("Client Full");

				jPacketSocket_IOCP *pS = jPacketSocket_IOCP::_push_back();
				pS->_PostCreate_PS(0,m_iSizeQueue);
				jAUTO_LOCK_CS1(pS->m_CS_jPacketSocket);
				pS->SetFlag_IsNot_IOCP_Socket(true);
				if(m_pPlugIn)
				{
					pS->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
					jASSERT0(pS->m_pjIPacketDispatchTable);
				}
				if(!pS->Begin_Socket_PS()) throw _T("pS->Begin_Socket_PS()");

				if( !pS->assept(listenSocket) )
					throw _T("pS->assept()");

				jSOCKADDR_IN		&stClientAddr = pS->GetAddress();

				m_SocketInfo.m_pPacketSocket[nIdx] = pS;

				int nRet = WSAEventSelect( pS->GetSocket(),
					m_SocketInfo.m_eventHandle[ nIdx ] ,FD_READ | FD_CLOSE );
				if( SOCKET_ERROR == nRet )	throw _T("WSAEventSelect");

				//클라이언트 갯수 증가
				m_nClientCnt++;
				tname_t buf;
				jLOG( jFUNC1 _T("%s > addr(%s) SOCKET(%d)" )
					,stClientAddr.ToString(buf)
					,m_SocketInfo.m_pPacketSocket[ nIdx ]->GetSocket() );

				pS->SetConnected(TRUE);

				OnIoConnected(pS);

				jNET_Plugin_callback_OnIoConnected(m_pPlugIn,pS);
			}

			bool jNetIOModel_EventSelect_CS::__selectThreadCallback( SOCKET sock, DWORD dwObjIdx, WSANETWORKEVENTS &wsaNetworkEvents, jPacketSocket_IOCP* pS )
			{
				DWORD ret = WSAEnumNetworkEvents(sock ,m_SocketInfo.m_eventHandle[ dwObjIdx ] ,&wsaNetworkEvents );

				if (ret== SOCKET_ERROR)
				{
					jLOG(jFUNC1 _T("SOCKET_ERROR WAIT_OBJECT_0 + 1"));
					return false;
				}

				if( false == m_bWorkerRun && eEST_LISTEN_SOCKET == dwObjIdx )	//쓰레드가 종료 이벤트를 받았다면
					return false;

				if( wsaNetworkEvents.lNetworkEvents & FD_ACCEPT )
				{
					if( 0 != wsaNetworkEvents.iErrorCode[ FD_ACCEPT_BIT ] )
					{
						jERROR(_T("WSAEnumNetworkEvents 실패 : %d"), WSAGetLastError() );
					}
					jASSERT0(dwObjIdx ==eEST_LISTEN_SOCKET);
					DoAccept( sock );
				}
				else if (wsaNetworkEvents.lNetworkEvents & FD_CONNECT)
				{
					GetjILog()->Log(jLogT(STCB),_T("WAIT_OBJECT_0 + 1"));
					OnIoConnected(pS);
					if (wsaNetworkEvents.iErrorCode[FD_CONNECT_BIT])
					{
						jWARN(_T("WAIT_OBJECT_0 + 1 wsaNetworkEvents.iErrorCode[FD_CONNECT_BIT]"));
						return true;
					}

					pS->SetConnected(true);
					if(m_pPlugIn)
					{
						jNET_Plugin_callback_OnIoConnected(m_pPlugIn,pS);
					}
				}
				else if (wsaNetworkEvents.lNetworkEvents & FD_WRITE)
				{
					GetjILog()->Log(jLogT(STCB),_T("FD_WRITE"));
					//OnIoWrote();
				}
				else if (wsaNetworkEvents.lNetworkEvents & FD_READ)
				{
					GetjILog()->Log(jLogT(STCB),_T("FD_READ"));
					OnIoRead(pS);
				}
				else if (wsaNetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					if(dwObjIdx !=eEST_LISTEN_SOCKET)
					{
						GetjILog()->Log(jLogT(STCB),_T("FD_CLOSE"));
						_DoDisconnectSocket(dwObjIdx);
					}
					if(m_SocketInfo.m_pPacketSocket[dwObjIdx])
						pS->SetConnected(false);
				}
				else
				{
					jWARN(_T("unkown event =%d,sockid=%d")
						,wsaNetworkEvents.lNetworkEvents ,dwObjIdx);
				}
				return true;
			}//jNetIOModel_EventSelect_CS::__ s electThreadCallback

		}// nNet::Impl

	} //nNET
}//nMech
