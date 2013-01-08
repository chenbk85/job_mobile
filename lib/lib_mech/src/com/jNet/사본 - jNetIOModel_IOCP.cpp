#include "stdafx.h"
#include "jNetIOModel_IOCP.h"
#include <process.h>


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{

			//DWORD WINAPI WorkerThreadCallback(LPVOID pThreadParam)
			static unsigned __stdcall _WorkerThreadCallback( void* pThreadParam)
			{
				jNetIOModel_IOCP *Owner = (jNetIOModel_IOCP*) pThreadParam;
				Owner->WorkerThreadCallback();

				return 0;
			}

			jNetIOModel_IOCP::jNetIOModel_IOCP(int threadCount)
			{
				mIocpHandle			= NULL;
				mWorkerThreadCount	= threadCount;
				mStartupEventHandle	= NULL;
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
				jAssert0(m_Observers.empty());
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

				mStartupEventHandle = CreateEvent(0, FALSE, FALSE, 0);
				if (mStartupEventHandle == NULL)
				{
					End(0);
					return FALSE;
				}

				for (DWORD i=0;i<mWorkerThreadCount;i++)
				{
					HANDLE WorkerThread = (HANDLE)_beginthreadex(NULL, 0, _WorkerThreadCallback, this, 0, NULL);
					GetjILog()->Log(jLogT(CT),_T("thread create : WorkerThreadCallback"));

					mWorkerThreadVector.push_back(WorkerThread);

					GetjILog()->Log(jLogT(Wait),_T("WaitForSingleObject(mStartupEventHandle, INFINITE);"));
					WaitForSingleObject(mStartupEventHandle, INFINITE);
				}
				m_Observers.insert(pObs);
				GetjILog()->Log(_T("jNetIOModel_IOCP::Begin(thread = %d)"), mWorkerThreadCount);
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

				for (DWORD i=0;i<mWorkerThreadVector.size();i++)
					PostQueuedCompletionStatus(mIocpHandle, 0, 0, NULL);

				DWORD dwExitCode=0;
				for (DWORD i=0;i<mWorkerThreadVector.size();i++)
				{
					GetjILog()->Log(jLogT(Wait),_T("WaitForSingleObject(mWorkerThreadVector[i], INFINITE);"));
					//WaitForSingleObject(mWorkerThreadVector[i], INFINITE);
					//CloseHandle(mWorkerThreadVector[i]);
					TerminateThread(mWorkerThreadVector[i],dwExitCode);
				}

				if (mIocpHandle)
					CloseHandle(mIocpHandle);
				mIocpHandle=0;

				mWorkerThreadVector.clear();

				if (mStartupEventHandle)
					CloseHandle(mStartupEventHandle);
				mStartupEventHandle=0;
				return TRUE;

				GetjILog()->Log(_T("jNetIOModel_IOCP::End"));

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

			VOID jNetIOModel_IOCP::WorkerThreadCallback(VOID)
			{
				BOOL			bSuccessed				= FALSE;
				DWORD			dwNumberOfByteTransfered	= 0;
				VOID			*pCompletionKey			= NULL;
				OVERLAPPED		*pOverlapped				= NULL;
				OVERLAPPED_EX	*pOverlappedEx			= NULL;
				VOID			*pObject					= NULL;

				// *_* by icandoit : 2007-06-05 12:41:32
				//http://blog.naver.com/h64d5791
				SetEvent(mStartupEventHandle);
				while (TRUE)
				{
					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus Called"));

					bSuccessed = GetQueuedCompletionStatus(
						mIocpHandle,
						&dwNumberOfByteTransfered,
						(LPDWORD) &pCompletionKey,
						&pOverlapped,
						INFINITE);

					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus OK"));

					// *_* by icandoit : 2008-12-04 13:59:22
					// 리턴할지 continue;할지 테스트해봐야함
					if (!pCompletionKey || m_Observers.empty())
						return;

					GetjILog()->Log(jLogT(WTCB),_T("GetQueuedCompletionStatus pCompletionKey OK"));

					pOverlappedEx	= (OVERLAPPED_EX*) pOverlapped;
					
					if(!dwNumberOfByteTransfered && !pOverlappedEx )
					{
						//GetjILog()->Log(_T("!dwNumberOfByteTransfered && !pOverlappedEx"));
						continue;
					}
#if 0
					if(!bSuccessed && !dwNumberOfByteTransfered)
					{
						GetjILog()->Log(_T("!bSuccessed && !dwNumberOfByteTransfered"));
						continue;
					}
#endif

					pObject			= pOverlappedEx->Object;
					if(!m_Observers.count(pOverlappedEx->ObjectHost))
						continue;

					if(!bSuccessed) 
					{
						// case 1 클라이언트 비정상종료시 호출됨.
						GetjILog()->Log(jLogT(WTCB),_T("OnIoDisconnected"));
						pOverlappedEx->ObjectHost->OnIoDisconnected(pObject);
						continue;
					}

					if (!bSuccessed || (bSuccessed && !dwNumberOfByteTransfered))
					{
						if (pOverlappedEx->IoType == IO_ACCEPT)
						{
							GetjILog()->Log(jLogT(WTCB),_T("OnIoConnected"));
							pOverlappedEx->ObjectHost->OnIoConnected(pObject);
						}
						else
						{
							GetjILog()->Log(jLogT(WTCB),_T("OnIoDisconnected"));
							pOverlappedEx->ObjectHost->OnIoDisconnected(pObject);
						}
						continue;

					}

					jPacketLen_t dwReadLen = dwNumberOfByteTransfered;

					switch (pOverlappedEx->IoType)
					{
					case IO_READ:
						GetjILog()->Log(jLogT(WTCB),_T("IO_READ"));
						pOverlappedEx->ObjectHost->OnIoRead(pObject, dwReadLen);
						break;

					case IO_WRITE:
						GetjILog()->Log(jLogT(WTCB),_T("IO_WRITE"));
						pOverlappedEx->ObjectHost->OnIoWrote(pObject, dwReadLen);
						break;
					}
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech
