#include "stdafx.h"
#include "header/jCriticalSection.h"
#include "header/MultiThreadSync.h"
#include "jSocket_IOCP.h"
#include <mswsock.h>
#include <process.h>
#include "interface/net/jINet_Util.h"
#include "interface/jIThread.h"


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			bool jSocket_IOCP::_pop_QueueData(_jSendData& sd)
			{
				if (!mReliableWriteQueue.Pop(&sd.m_pObject, sd.m_cData, sd.m_iDataLength
					, &sd.m_IPAddr))
				{
					name_t buf;
					jWARN_T("FAIL : mReliableWriteQueue.Pop(len=%d, %s" ,sd.m_iDataLength, nInterface::g_pjINet_OGS->GetUtil()->Addr2String(sd.m_IPAddr, buf));
					//SetEvent(mReliableUdpWriteCompleteEvent);
					mIsReliableUdpSending = FALSE;
					return false;
				}
				return true;
			}

			void jSocket_IOCP::_PostCreate(jIObserver_IOCP* pObserver,int iSizeQueue)
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				mReliableWriteQueue._PostCreate(iSizeQueue);
				memset(&mAcceptOverlapped, 0, sizeof(mAcceptOverlapped));
				memset(&mReadOverlapped, 0, sizeof(mReadOverlapped));
				memset(&mWriteOverlapped, 0, sizeof(mWriteOverlapped));
				mReadOverlapped.m_pObserver = pObserver;
				mAcceptOverlapped.m_pObserver = pObserver;
				mWriteOverlapped.m_pObserver = pObserver;

				memset(mReadBuffer, 0, sizeof(mReadBuffer));
				memset(&m_UdpRecv_addr_in, 0, sizeof(m_UdpRecv_addr_in));

				mSocket							= INVALID_SOCKET;

				mReliableUdpWriteCompleteEvent	= NULL;

				mIsReliableUdpSending			= FALSE;

				mAcceptOverlapped.m_eIoType		= eIO_ACCEPT;
				mReadOverlapped.m_eIoType			= eIO_READ;
				mWriteOverlapped.m_eIoType			= eIO_WRITE;

				mAcceptOverlapped.m_pVoid		= this;
				mReadOverlapped.m_pVoid			= this;
				mWriteOverlapped.m_pVoid			= this;
				m_eType=eNULL_SOCKET;
				
				m_iFlag=0;
				SetFlag_IsDisConnected(true);

			}

			void jSocket_IOCP::_PostDelete(VOID)
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				mReliableWriteQueue._PostDelete();
				mReadOverlapped.m_pObserver = 0;
				mAcceptOverlapped.m_pObserver = 0;
				mWriteOverlapped.m_pObserver = 0;
				m_iFlag=0;
				SetFlag_IsDisConnected(true);


			}

			BOOL jSocket_IOCP::Begin_Socket(VOID)
			{
				jSocket_IOCP_NEW_DELELTE_DEBUG();
				m_threadName[0]=0;

				jRETURN_ret(FALSE,mSocket==INVALID_SOCKET);
				
				memset(&mSocket_in , 0 , sizeof(mSocket_in));

				memset(mReadBuffer, 0, sizeof(mReadBuffer));
				memset(&m_UdpRecv_addr_in, 0, sizeof(m_UdpRecv_addr_in));

				mSocket							= INVALID_SOCKET;
				mReliableUdpWriteCompleteEvent	= NULL;

				mIsReliableUdpSending			= FALSE;

				//GetjILog()->Log(jLogT(SIOCP),_T("jSocket_IOCP::Begin()"));
				return TRUE;
			}

			BOOL jSocket_IOCP::End_Socket(VOID)
			{
				jSocket_IOCP_NEW_DELELTE_DEBUG();

				jRETURN_ret(FALSE,mSocket!=INVALID_SOCKET);

				closesocket(mSocket);
				mSocket					= INVALID_SOCKET;

				if (mReliableUdpWriteCompleteEvent)
					CloseHandle(mReliableUdpWriteCompleteEvent);
				mReliableWriteQueue.End();

				if(jt_strlen(m_threadName))
					g_pjIThreadManager->End(m_threadName,0);

				GetjILog()->Log(jLogT(SIOCP),_T("jSocket_IOCP::End()"));

				return TRUE;
			}
			VOID jSocket_IOCP::ReliableUdpThreadCallback(nThread::jIThread*pT)
			{
				int retryCount=0;
				_jSendData sd;
NEXT_DATA:
				GetjILog()->Log(jLogT(RUCB),_T("WAIT_OBJECT_0+1 mReliableUdpThreadWakeUpEvent NEXT_DATA"));

				// Write 일 경우 Pop을 해주고
				jRETURN(_pop_QueueData(sd));

				// 데이터가 있을 경우
				// 실제 Write를 해 주고 WaitForSingleObject를 해 준다.
				// 받았을때 그 SetEvent를 해 주면 풀린다.
RETRY:
				if (!WriteTo2(&sd.m_IPAddr, sd.m_cData, sd.m_iDataLength))
				{
					sockaddr_in addr;
					nUTIL::Make_sockaddr_in(sd.m_IPAddr.m_IP.s_addr, sd.m_IPAddr.port, addr);
					tfname_t buf;
					nUTIL::WSAAddressToString(&addr,buf);

					jERROR(_T("  ReliableUdpThreadCallback:: WriteTo2실패 %s"),buf);
					retryCount=0;
					goto NEXT_DATA;
				}

				//GetjILog()->Log(jLogT(RUCB),_T("RETRY WaitForSingleObject "));
				DWORD Result = WaitForSingleObject(mReliableUdpWriteCompleteEvent, pv_RUDP_RetryTime->Get_int() );

				// 받았을 경우 다음 데이터 처리
				if (Result == WAIT_OBJECT_0)
				{
					retryCount=0;
					GetjILog()->Log(jLogT(RUCB),_T("goto NEXT_DATA"));
					goto NEXT_DATA;
				}
				else
				{
					++retryCount;
					if(retryCount>=pv_RUDP_RetryCount->Get_int())
					{
						GetjILog()->Log(jLogT(RUCB),_T("retryCount = %d OVER!!\n"),retryCount);
						//SetEvent(mReliableUdpWriteCompleteEvent);
						retryCount=0;
						goto NEXT_DATA;
					}
					goto RETRY;
				}
			}


			BOOL jSocket_IOCP::Listen(cstr szIP, USHORT port, INT backLog)
			{
				m_eType = eLISTEN_SOCKET;

				if (backLog <= 0)	return FALSE;
				if (mSocket==INVALID_SOCKET)	return FALSE;
				mSocket_in.Set(szIP, port);

				if (::bind(mSocket, (struct sockaddr*) &mSocket_in, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
				{
					jERROR(_T(" jSocket_IOCP::Listen() : bind  : %s, %d"),szIP, port);
					End_Socket();
					return FALSE;
				}

				if (listen(mSocket, backLog) == SOCKET_ERROR)
				{
					jERROR(_T(" jSocket_IOCP::Listen() : listen : %s ,%d"),szIP,port);
					End_Socket();
					return FALSE;
				}

				LINGER Linger;
				Linger.l_onoff	= 1;
				Linger.l_linger = 0;

				if (setsockopt(mSocket, SOL_SOCKET, SO_LINGER, (char*) &Linger, sizeof(LINGER)) == SOCKET_ERROR)
				{
					jERROR(_T(" setsockopt(mSocket, SOL_SOCKET, SO_LINGER : %s ,%d"),szIP,port);
					End_Socket();

					return FALSE;
				}
				mSocket_in.Set(mSocket);
				tname32_t buf;
				//mSocket_in.ToString(buf);
				mSocket_in.ToStringByLocalPort(buf);
				jLOG(_T("socket Listen : %s"),buf);
				if(mSocket_in.sin_addr.s_addr==0)
					mSocket_in.Set(nUNI::scb64_t(g_pjNet->m_listNetHostIP.begin()->c_str()).getT(), mSocket_in.GetPort());

				return TRUE;
			}
			bool jSocket_IOCP::assept(SOCKET listenSocket)
			{
				int nAddrLen = sizeof( SOCKADDR_IN );
				//클라이언트 접속 요청이 들어올 때까지 기다린다.
				mSocket =  accept( listenSocket, (SOCKADDR*) &mSocket_in, &nAddrLen );
				jRETURN_ret(0, INVALID_SOCKET != mSocket );
				m_eType = eACCEPTED_SOCKET;
				return true;
			}

			BOOL jSocket_IOCP::Accept(SOCKET listenSocket)
			{

				jRETURN_ret(0, listenSocket);
				jRETURN_ret(0, mSocket==INVALID_SOCKET);

				mSocket	= WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

				if (mSocket == INVALID_SOCKET)
				{
					jERROR(_T("WSASocket INVALID_SOCKET"));
					End_Socket();
					return FALSE;
				}

				//BOOL NoDelay = TRUE;
				//setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char FAR *)&NoDelay, sizeof(NoDelay));

				if (!AcceptEx(listenSocket, 
					mSocket, 
					mReadBuffer, 
					0, 
					sizeof(sockaddr_in) + 16, 
					sizeof(sockaddr_in) + 16, 
					NULL, 
					&mAcceptOverlapped.m_OVLP))
				{
					DWORD iError = WSAGetLastError() ;
					if (iError!= ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
					{
						jERROR(_T("AcceptEx : WSAGetLastError()=%d"),iError);
						End_Socket();
						return FALSE;
					}
				}

				//GetjILog()->Log(jLogT(SIOCP),jFUNC1  _T(" Ok"));
				m_eType = eACCEPTED_SOCKET;
				return TRUE;
			}

			BOOL jSocket_IOCP::InitializeReadForIocp()
			{

				if (mSocket==INVALID_SOCKET)
					return FALSE;

				WSABUF	WsaBuf;
				DWORD	ReadBytes	= 0;
				DWORD	ReadFlag	= 0;

				WsaBuf.buf			= (CHAR*) mReadBuffer;
				WsaBuf.len			= MAX_BUFFER_LENGTH;

				INT		ReturnValue = WSARecv(mSocket,
					&WsaBuf,
					1,
					&ReadBytes,
					&ReadFlag,
					&mReadOverlapped.m_OVLP,
					NULL);

				DWORD ierror = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue == SOCKET_ERROR && ierror != WSA_IO_PENDING && ierror != WSAEWOULDBLOCK )
					,_T("WSAGetLastError() = %d"),ierror);

				//GetjILog()->Log(jLogT(SIOCP),_T("jSocket_IOCP::InitializeReadForIocp() : OK"));

				return TRUE;
			}

			BOOL jSocket_IOCP::ReadForIocp(BYTE *data, jPacketLen_t &dataLength)
			{
				//if(GetFlag_IsDisConnected())	return TRUE;

				jRETURN_ret(FALSE, mSocket!=INVALID_SOCKET);
				jRETURN_ret(FALSE, (data && dataLength > 0));
				jRETURN_ret(FALSE, (data && dataLength <= sizeof(mReadBuffer)));

				//m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;
				memcpy(data, mReadBuffer, dataLength);

				return TRUE;
			}

			BOOL jSocket_IOCP::ReadForEventSelect(BYTE *data, jPacketLen_t &dataLength)
			{

				jRETURN_ret(FALSE, mSocket!=INVALID_SOCKET);
				jRETURN_ret(FALSE, data);
				//m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;

				WSABUF	WsaBuf;
				DWORD	ReadBytes	= 0;
				DWORD	ReadFlag	= 0;

				WsaBuf.buf			= (CHAR*) mReadBuffer;
				WsaBuf.len			= MAX_BUFFER_LENGTH;

				INT		ReturnValue = WSARecv(mSocket,
					&WsaBuf,
					1,
					&ReadBytes,
					&ReadFlag,
					&mReadOverlapped.m_OVLP,
					NULL);

				DWORD iErr = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue==SOCKET_ERROR && iErr!=WSA_IO_PENDING && iErr!=WSAEWOULDBLOCK) ,_T("WSAGetLastError() = %d"),iErr);

				memcpy(data, mReadBuffer, ReadBytes);
				dataLength = ReadBytes;
				//GetjILog()->Log(jLogT(SIOCP),_T("jSocket_IOCP::ReadForEventSelect() OK"));

				return TRUE;
			}

			BOOL jSocket_IOCP::Write(BYTE *data, jPacketLen_t dataLength)
			{
				//if(GetFlag_IsDisConnected())return TRUE;
				jRETURN_ret(FALSE, mSocket!=INVALID_SOCKET);
				jRETURN_ret(FALSE, data && dataLength > 0);
				m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;
				//jLOG(_T("jSocket_IOCP::Write: %I64d"), m_iPacketSize_UsageInfo);


				WSABUF	WsaBuf;
				DWORD	WriteBytes	= 0;
				DWORD	WriteFlag	= 0;

				WsaBuf.buf			= (CHAR*) data;
				WsaBuf.len			= dataLength;

				INT		ReturnValue	= WSASend(mSocket,
					&WsaBuf,
					1,
					&WriteBytes,
					WriteFlag,
					&mWriteOverlapped.m_OVLP,
					NULL);

				DWORD iErr = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue==SOCKET_ERROR && iErr!=WSA_IO_PENDING && iErr!=WSAEWOULDBLOCK) ,_T("WSAGetLastError() = %d"),iErr);
				return TRUE;
			}

			BOOL jSocket_IOCP::Connect(cstr _address, USHORT port)
			{
				jRETURN_ret(0, _address && port > 0);
				jRETURN_ret(0,INVALID_SOCKET!=mSocket);

				fname_t address;
				ip_string_convert(_address,address);

				m_eType = eCONNECTING_SOCKET;

				mSocket_in.Set(address, port);
				if (WSAConnect(mSocket, (LPSOCKADDR) &mSocket_in, sizeof(SOCKADDR_IN)
					, NULL, NULL, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						jWARN(_T(" jSocket_IOCP::Connect() WSAConnect"));
						End_Socket();
						return FALSE;
					}
				}
				return TRUE;
			}

			BOOL jSocket_IOCP::UdpBind(cstr _szIP, USHORT port)
			{
				fname_t szIP;
				ip_string_convert(_szIP,szIP);

				m_eType = eUDP_SOCKET;
				jRETURN_ret(0,INVALID_SOCKET==mSocket);

				//mSocket_in.Set(szIP,port);
				mSocket_in.Set((cstr)0,port);

				mSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);

				if (mSocket == INVALID_SOCKET)	return FALSE;

				if (::bind(mSocket, (struct sockaddr*) &mSocket_in, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
				{
					jERROR(_T(" jSocket_IOCP::UdpBind() : bind"));
					int i = WSAGetLastError();
					End_Socket();
					return FALSE;
				}
				mSocket_in.Set(mSocket);
				if(mSocket_in.sin_addr.s_addr==0)
					mSocket_in.Set(nUNI::scb64_t(g_pjNet->m_listNetHostIP.begin()->c_str()).getT(), mSocket_in.GetPort());


				// *_* by icandoit : 2007-06-27 10:21:33 WSAECONNRESET문제 솔루션
				// http://support.microsoft.com/default.aspx?kbid=263823
				//--------------------------------------------------------------------------
				DWORD dwBytesReturned = 0;
				BOOL bNewBehavior = FALSE;
				DWORD status;

				// disable  new behavior using
				// IOCTL: SIO_UDP_CONNRESET
				status = WSAIoctl(mSocket, SIO_UDP_CONNRESET,
					&bNewBehavior, sizeof(bNewBehavior),
					NULL, 0, &dwBytesReturned,
					NULL, NULL);

				if (SOCKET_ERROR == status)
				{
					DWORD dwErr = WSAGetLastError();
					if (WSAEWOULDBLOCK == dwErr)
					{
						jERROR(_T("WSAIoctl(SIO_UDP_CONNRESET) WSAEWOULDBLOCK == dwErr"));
						// nothing to do
						return(FALSE);
					}
					else
					{
						jERROR(_T("WSAIoctl(SIO_UDP_CONNRESET) Error: %d"), dwErr);
						return(FALSE);
					}
				}

				// mReliableUdpWriteCompleteEvent
				mReliableUdpWriteCompleteEvent = CreateEvent(0, FALSE, FALSE, 0);
				if (mReliableUdpWriteCompleteEvent == NULL)
				{
					jERROR(_T(" jSocket_IOCP::UdpBind() : mReliableUdpWriteCompleteEvent = CreateEvent"));

					End_Socket();

					return FALSE;
				}
				//

				if (!mReliableWriteQueue.Begin())
				{
					jERROR(_T(" jSocket_IOCP::UdpBind() : mReliableWriteQueue.Begin"));

					End_Socket();

					return FALSE;
				}
				jt_sprintf(m_threadName, _T("RUDP:%s:%d"),szIP,port);
				nThread::thread_func_t f = boost::bind(&jSocket_IOCP::ReliableUdpThreadCallback,this,jBOOST__PLACEHODER_1 );
				m_pReliableUdpThread = g_pjIThreadManager->Run_Wake(f
					,m_threadName,jS(ReliableUdpThreadCallback));
				return TRUE;
			}

			BOOL jSocket_IOCP::TcpBind(VOID)
			{
				m_eType = eLISTEN_SOCKET;
				jRETURN_ret(FALSE, mSocket==INVALID_SOCKET);
				mSocket	= WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
				jRETURN_ret(0,mSocket != INVALID_SOCKET);

				//BOOL NoDelay = TRUE;
				//setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char FAR *)&NoDelay, sizeof(NoDelay));
				return TRUE;
			}
			BOOL jSocket_IOCP::InitializeReadFromForIocp(VOID)
			{
				jRETURN_ret(FALSE, mSocket!=INVALID_SOCKET);

				WSABUF		WsaBuf;
				DWORD		ReadBytes				= 0;
				DWORD		ReadFlag				= 0;
				INT			RemoteAddressInfoSize	= sizeof(m_UdpRecv_addr_in);

				WsaBuf.buf			= (CHAR*) mReadBuffer;
				WsaBuf.len			= MAX_BUFFER_LENGTH;

				INT		ReturnValue = WSARecvFrom(mSocket,
					&WsaBuf,
					1,
					&ReadBytes,
					&ReadFlag,
					(SOCKADDR*) &m_UdpRecv_addr_in,
					&RemoteAddressInfoSize,
					&mReadOverlapped.m_OVLP,
					NULL);

				DWORD iErr = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue==SOCKET_ERROR && iErr!=WSA_IO_PENDING && iErr!=WSAEWOULDBLOCK) ,_T("WSAGetLastError() = %d"),iErr);
				//GetjILog()->Log(jLogT(SIOCP),_T("jSocket_IOCP::InitializeReadFromForIocp() : OK"));
				return TRUE;
			}

			BOOL jSocket_IOCP::ReadFromForIocp(jIP_Address* pIP, BYTE *data, jPacketLen_t &dataLength)
			{
				jRETURN_ret(FALSE, INVALID_SOCKET!=mSocket);
				jRETURN_ret(FALSE, (data && dataLength > 0) );
				//m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;


				memcpy(data, mReadBuffer, dataLength);

				pIP->m_IP.s_addr = ntohl(m_UdpRecv_addr_in.sin_addr.s_addr);
				pIP->port = ntohs(m_UdpRecv_addr_in.sin_port);

				jPacketNum_t Ack = 0;
				memcpy(&Ack, mReadBuffer, sizeof(jPacketNum_t));

				if (Ack == eNET_OGS_RUDP_AckNumber)
				{
					SetEvent(mReliableUdpWriteCompleteEvent);

					return FALSE;
				}
				else
				{
					Ack = eNET_OGS_RUDP_AckNumber;
					WriteTo2(pIP, (BYTE*) &Ack, sizeof(jPacketNum_t));
				}

				return TRUE;
			}

			BOOL jSocket_IOCP::ReadFromForEventSelect(jIP_Address* pIP, BYTE *data, jPacketLen_t &dataLength)
			{
				jRETURN_ret(FALSE, INVALID_SOCKET!=mSocket);
				jRETURN_ret(FALSE, data );
				//m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;

				WSABUF		WsaBuf;
				DWORD		ReadBytes				= 0;
				DWORD		ReadFlag				= 0;
				INT			RemoteAddressInfoSize	= sizeof(m_UdpRecv_addr_in);

				WsaBuf.buf			= (CHAR*) mReadBuffer;
				WsaBuf.len			= MAX_BUFFER_LENGTH;

				INT		ReturnValue = WSARecvFrom(mSocket,
					&WsaBuf,
					1,
					&ReadBytes,
					&ReadFlag,
					(SOCKADDR*) &m_UdpRecv_addr_in,
					&RemoteAddressInfoSize,
					&mReadOverlapped.m_OVLP,
					NULL);

				DWORD iErr = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue==SOCKET_ERROR && iErr!=WSA_IO_PENDING && iErr!=WSAEWOULDBLOCK) ,_T("WSAGetLastError() = %d"),iErr);

				memcpy(data, mReadBuffer, ReadBytes);
				dataLength	= ReadBytes;

				//memcpy(szRemoteAddress, inet_ntoa(m_UdpRecv_addr_in.sin_addr), 32);
				pIP->m_IP.s_addr = ntohl(m_UdpRecv_addr_in.sin_addr.s_addr);
				pIP->port = ntohs(m_UdpRecv_addr_in.sin_port);

				jPacketNum_t Ack = 0;
				memcpy(&Ack, mReadBuffer, sizeof(jPacketNum_t));

				if (Ack == eNET_OGS_RUDP_AckNumber)
				{
					SetEvent(mReliableUdpWriteCompleteEvent);

					return FALSE;
				}
				else
				{
					Ack = eNET_OGS_RUDP_AckNumber;
					WriteTo2(pIP, (BYTE*) &Ack, sizeof(jPacketNum_t));
				}

				return TRUE;
			}

			BOOL jSocket_IOCP::WriteTo(jIP_Address* pIP, BYTE *data, jPacketLen_t dataLength)
			{
				jRETURN_ret(FALSE, INVALID_SOCKET!=mSocket);
				jRETURN_ret(FALSE,(pIP->m_IP.s_addr && pIP->port> 0 ) );
				jRETURN_ret(FALSE,(data && dataLength > 0) );

				m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;
				//jLOG(_T("jSocket_IOCP::WriteTo: %I64d"), m_iPacketSize_UsageInfo);

				jRETURN_ret(FALSE,mReliableWriteQueue.Push(this, data, dataLength, pIP));

				if (!mIsReliableUdpSending)
				{
					mIsReliableUdpSending = TRUE;
					if(m_pReliableUdpThread) m_pReliableUdpThread->DoWake();
				}

				return TRUE;
			}

			BOOL jSocket_IOCP::WriteTo2(jIP_Address* pIP, BYTE *data, jPacketLen_t dataLength)
			{
				jRETURN_ret(FALSE, INVALID_SOCKET!=mSocket);
				jRETURN_ret(FALSE,(pIP->m_IP.s_addr && pIP->port> 0 ) );
				jRETURN_ret(FALSE,(data && dataLength > 0) );
				m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + dataLength;
				//jLOG(_T("jSocket_IOCP::WriteTo2: %I64d"), m_iPacketSize_UsageInfo);

				WSABUF		WsaBuf;
				DWORD		WriteBytes					= 0;
				DWORD		WriteFlag					= 0;

				SOCKADDR_IN	RemoteAddressInfo;
				INT			RemoteAddressInfoSize		= sizeof(RemoteAddressInfo);

				WsaBuf.buf								= (CHAR*) data;
				WsaBuf.len								= dataLength;

				RemoteAddressInfo.sin_family			= AF_INET;
#if 1
	#if 0
				nNET::jSOCKADDR_IN ip2(_T("127.0.0.1"),pIP->port);
				RemoteAddressInfo.sin_addr = ip2.sin_addr;
				RemoteAddressInfo.sin_port = ip2.sin_port;
	#else
				//RemoteAddressInfo.sin_addr.S_un.S_addr	= inet_addr("127.0.0.1");
				RemoteAddressInfo.sin_addr.s_addr = htonl(pIP->m_IP.s_addr);
				RemoteAddressInfo.sin_port				= htons(pIP->port);
	#endif
#else
				RemoteAddressInfo.sin_addr.S_un.S_addr	= inet_addr("127.0.0.1");
				RemoteAddressInfo.sin_port				= htons(8001);

#endif
				//tname_t szBuf123;	nUTIL::WSAAddressToString(&RemoteAddressInfo, szBuf123);
				//jLOG(_T("udp send ip : %s"), szBuf123);
				INT		ReturnValue	= WSASendTo(mSocket,
					&WsaBuf,
					1,
					&WriteBytes,
					WriteFlag,
					(SOCKADDR*) &RemoteAddressInfo,
					RemoteAddressInfoSize,
					&mWriteOverlapped.m_OVLP,
					NULL);

				DWORD iErr = WSAGetLastError();
				jvRETURN_ret(0, !(ReturnValue==SOCKET_ERROR && iErr!=WSA_IO_PENDING && iErr!=WSAEWOULDBLOCK) ,_T("WSAGetLastError() = %d"),iErr);

				return TRUE;
			}

			BOOL jSocket_IOCP::GetRemoteAddressAfterAccept(jIP_Address* pIP)
			{
				jRETURN_ret(0,pIP);

				sockaddr_in		*Local			= NULL;
				INT				LocalLength		= 0;
				sockaddr_in		*Remote			= NULL;
				INT				RemoteLength	= 0;

				GetAcceptExSockaddrs(mReadBuffer, 
					0, 
					sizeof(sockaddr_in) + 16, 
					sizeof(sockaddr_in) + 16,
					(sockaddr **) &Local,
					&LocalLength,
					(sockaddr **) &Remote,
					&RemoteLength);

				jRETURN_ret(FALSE,Remote);
				pIP->m_IP.s_addr =ntohl(Remote->sin_addr.s_addr);
				pIP->port = ntohs(Remote->sin_port);
				return TRUE;
			}


			void jSocket_IOCP::ProcessMessage(cstr sz, void* pData)
			{
				if(!jt_strcmp(sz,_T("reset")) )
				{
					SetEvent(mReliableUdpWriteCompleteEvent);
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech

