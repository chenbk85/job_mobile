#include "stdafx.h"
#include "jNetIOModel_IOCP.h"
#include <process.h>
#include "interface/jIThread.h"
#include <boost/bind.hpp>


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			jNetIOModel_IOCP::jNetIOModel_IOCP(int threadCount)
			{
				mIocpHandle			= NULL;
				mWorkerThreadCount	= threadCount;
			}

			jNetIOModel_IOCP::~jNetIOModel_IOCP(VOID)
			{
			}

			bool jNetIOModel_IOCP::Begin(jIObserver_IOCP* pObs)
			{
				if(mIocpHandle)
				{
					m_Observers.insert(pObs);
					throw true;
				}
				jASSERT0(m_Observers.empty());
				mIocpHandle			= NULL;

				if(mWorkerThreadCount<=0)
				{
					SYSTEM_INFO SystemInfo;
					GetSystemInfo(&SystemInfo);
					mWorkerThreadCount	= SystemInfo.dwNumberOfProcessors * 2;
				}

				mIocpHandle			= CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

				if (!mIocpHandle)
					return FALSE;


				for (DWORD i=0;i<mWorkerThreadCount;i++)
				{
					fname_t szThreadName;
					jt_sprintf(szThreadName, _T("IOCPWorker%d"),i );

					nThread::thread_func_t f = boost::bind(&jNetIOModel_IOCP::WorkerThreadCallback,this, jBOOST__PLACEHODER_1 );
					g_pjIThreadManager->Run(f,pObs->GetThreadName(),szThreadName,true);
				}
				m_Observers.insert(pObs);
				jLOG(_T("jNetIOModel_IOCP::Begin(thread = %d)"), mWorkerThreadCount);
				return TRUE;
			}

			bool jNetIOModel_IOCP::End(jIObserver_IOCP* pObs)
			{
				if(!mIocpHandle) return true;
				if(pObs)
				{
					m_Observers.erase(pObs);
					if(!m_Observers.empty())
						return true;
				}
				m_Observers.clear();

				DWORD i;
				for (i=0;i<mWorkerThreadCount;i++)
					PostQueuedCompletionStatus(mIocpHandle, 0, 0, NULL);

				if (mIocpHandle)
					CloseHandle(mIocpHandle);
				mIocpHandle=0;
				g_pjIThreadManager->End(pObs->GetThreadName(),0);

				jLOG(_T("jNetIOModel_IOCP::End"));
				return TRUE;

			}

			bool jNetIOModel_IOCP::RegisterSocket(SOCKET soc, ULONG_PTR completionKey)
			{
				if (!soc || !completionKey)
					return FALSE;

				mIocpHandle = CreateIoCompletionPort((HANDLE) soc, mIocpHandle, completionKey, 0);

				if (!mIocpHandle)
					return FALSE;

				return TRUE;
			}

#if 0 ////http://www.codeproject.com/KB/IP/iocp_server_client.aspx?msg=3510987

			UINT IOCPS::IOWorkerThreadProc(LPVOID pParam)
			{
				IOCPS* pThis = reinterpret_cast<IOCPS*>(pParam);
				if ( pThis )
				{
					DWORD dwIoSize;
					ClientContext* lpClientContext;
					CIOCPBuffer *pOverlapBuff;
					bool bError=false;
					HANDLE hCompletionPort = pThis->m_hCompletionPort;
					LPOVERLAPPED lpOverlapped;
					//pOverlapPlus = CONTAINING_RECORD(lpOverlapped, MYOVERLAPPEDPLUS, m_ol);
					while ( !bError )
					{
						pOverlapBuff=NULL;
						lpClientContext=NULL;
						// Get a completed IO request.
						BOOL bIORet = GetQueuedCompletionStatus(
							hCompletionPort,
							&dwIoSize,
							(LPDWORD) &lpClientContext,
							&lpOverlapped, INFINITE);
						// Simulate workload (for debugging, to find possible reordering)
						//Sleep(20);



						// If Something whent wrong..
						if (!bIORet)  
						{
							DWORD dwIOError = GetLastError();
							if(dwIOError != WAIT_TIMEOUT) // It was not an Time out event we wait for ever (INFINITE) 
							{	
								TRACE(_T("GetQueuedCompletionStatus errorCode: %i, %s\n"),WSAGetLastError(),pThis->ErrorCode2Text(dwIOError));			
								// if we have a pointer & This is not an shut down.. 
								//if (lpClientContext!=NULL && pThis->m_bShutDown == false)
								if (lpClientContext!=NULL)
								{
									/*
									* ERROR_NETNAME_DELETED Happens when the communication socket
									* is cancelled and you have pendling WSASend/WSARead that are not finished. 
									* Then the Pendling I/O (WSASend/WSARead etc..) is cancelled and we return with 
									* ERROR_NETNAME_DELETED.. 
									*/
									if(dwIOError==ERROR_NETNAME_DELETED) 
									{

										//TRACE("ERROR_NETNAME_DELETED\r\n");
										pThis->DisconnectClient(lpClientContext); 
										TRACE(">IOWORKER1 (%x)\r\n",lpClientContext);
										pThis->ReleaseClientContext(lpClientContext); //Later Implementati

									}else
									{ // Should not get here if we do: disconnect the client and cleanup & report. 

										pThis->AppendLog(pThis->ErrorCode2Text(dwIOError)); 
										pThis->DisconnectClient(lpClientContext); 
										TRACE(">IOWORKER2 (%x)\r\n",lpClientContext);
										pThis->ReleaseClientContext(lpClientContext); //Should we do this ? 
									}
									// Clear the buffer if returned. 
									pOverlapBuff=NULL;
									if(lpOverlapped!=NULL)
										pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
									if(pOverlapBuff!=NULL)
										pThis->ReleaseBuffer(pOverlapBuff);			
									continue;
								}
								// We shall never come here  
								// anyway this was an error and we should exit the worker thread
								bError = true;
								pThis->AppendLog(pThis->ErrorCode2Text(dwIOError)); 
								pThis->AppendLog("IOWORKER KILLED BECAUSE OF ERROR IN GetQueuedCompletionStatus");

								pOverlapBuff=NULL;
								if(lpOverlapped!=NULL)
									pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
								if(pOverlapBuff!=NULL)
									pThis->ReleaseBuffer(pOverlapBuff);
								continue;
							}
						}//if (!bIORet)  



						if(bIORet && lpOverlapped && lpClientContext) 
						{
							pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
							if(pOverlapBuff!=NULL)
								pThis->ProcessIOMessage(pOverlapBuff, lpClientContext, dwIoSize);
						}	

						if(lpClientContext==NULL&&pOverlapBuff==NULL&&pThis->m_bShutDown)
						{
							TRACE("lpClientContext==NULL \r\n"); 
							bError=true;
						}


						//pThis->ReleaseBuffer(pOverlapBuff);// from previous call

					} ///while ( !bError )

				}//if ( pThis )

				TRACE("IOWorker Died!\r\n");
				return 0xdead;
			}

#endif
			VOID jNetIOModel_IOCP::WorkerThreadCallback(nThread::jIThread*pT)
			{
				BOOL			bOk				= FALSE;
				DWORD			iTransferedByte	= 0;
				VOID			*pCmpt_Key			= NULL;
				OVERLAPPED		*pOvlp				= NULL;
				VOID			*pObj					= NULL;

				// *_* by icandoit : 2007-06-05 12:41:32
				//http://blog.naver.com/h64d5791
				while (pT->IsRun())
				{
					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus Called"));

					bOk = GetQueuedCompletionStatus(
						mIocpHandle,
						&iTransferedByte,
						(PULONG_PTR) &pCmpt_Key,
						&pOvlp,
						INFINITE);

					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus OK"));

					// *_* by icandoit : 2008-12-04 13:59:22
					if (!pCmpt_Key || m_Observers.empty())
					{
						jWARN_T("!pCmpt_Key (%d) , m_Observers.empty() : %d ",!pCmpt_Key , m_Observers.empty());
						//jRAISE( 0 && "if (!pCmpt_Key || m_Observers.empty())");
						/* 상황 설명 
							: 자신의 icop 소켓을 강제 종료 했을때 호출될수 있슴. 
							: jIPlugIn_Connection 객체가 강제 소멸되는상황 
							: net_Client.dll 같은 network plugin 객체가 포함된 동적dll을 unload하는 상황.
						*/
						return;
					}

					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus pCmpt_Key OK"));

					jOverlappedEx *pOvlp_ex =(jOverlappedEx*)pOvlp;
					
					if(!iTransferedByte && !pOvlp_ex )
					{
						jERROR_T("!iTransferedByte && !pOvlp_ex");
						continue;
					}

					pObj			= pOvlp_ex->m_pVoid;
					if(!m_Observers.count(pOvlp_ex->m_pObserver))
						continue;

					if(!bOk) 
					{
						//jLOG(_T("GetQueuedCompletionStatus WSAGetLastError: %i \n"),WSAGetLastError());			

						//http://www.codeproject.com/KB/IP/iocp_server_client.aspx?msg=3510987
						DWORD dwIOError = GetLastError();
						if(dwIOError == WAIT_TIMEOUT) // It was not an Time out event we wait for ever (INFINITE) 
						{
							jWARN_T(" GetQueuedCompletionStatus() return=0, dwIOError == WAIT_TIMEOUT");
						}
						else
						{
							//jTODO 태깅로그로 남길것.
							//jLOG_T(" GetQueuedCompletionStatus() return=0, GetLastError()=%d",dwIOError);
						}


						// case 1 클라이언트 비정상종료시 호출됨.
						GetjILog()->Log(jLogT(WTCB),_T("OnIoDisconnected"));
						if(pOvlp_ex->m_pObserver)
							pOvlp_ex->m_pObserver->OnIoDisconnected(pObj);
						continue;
					}

					if (bOk && !iTransferedByte)
					{
						if (pOvlp_ex->m_eIoType == eIO_ACCEPT)
						{
							GetjILog()->Log(jLogT(WTCB),_T("OnIoConnected"));
							if(pOvlp_ex->m_pObserver)
								pOvlp_ex->m_pObserver->OnIoConnected(pObj);
						}
						else
						{
							GetjILog()->Log(jLogT(WTCB),_T("OnIoDisconnected"));
							if(pOvlp_ex->m_pObserver)
								pOvlp_ex->m_pObserver->OnIoDisconnected(pObj);
						}
						continue;

					}

					jPacketLen_t dwReadLen = iTransferedByte;

					switch (pOvlp_ex->m_eIoType)
					{
					case eIO_READ:
						GetjILog()->Log(jLogT(WTCB),_T("eIO_READ"));
						if(pOvlp_ex->m_pObserver)
							pOvlp_ex->m_pObserver->OnIoRead(pObj, dwReadLen);
						break;

					case eIO_WRITE:
						GetjILog()->Log(jLogT(WTCB),_T("eIO_WRITE"));
						if(pOvlp_ex->m_pObserver)
							pOvlp_ex->m_pObserver->OnIoWrote(pObj, dwReadLen);
						break;
					}
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech
