#include "stdafx.h"
#include "jNetIOModel_EventSelect.h"
#include <process.h>
#include "interface/jIThread.h"
namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			VOID jNetIOModel_EventSelect::SelectThreadCallback(nThread::jIThread*pT)
			{
				WSANETWORKEVENTS	NetworkEvents;
				DWORD				EventID = 0;
				DWORD				Result	= 0;
				pT->GetDestroyEvent() = CreateEvent(NULL, FALSE, FALSE, NULL);
				HANDLE				hEvent_Select_and_Destroy[2] = {pT->GetDestroyEvent(), mSelectEventHandle};

				// *_* by icandoit : 2007-06-05 12:41:32
				//http://blog.naver.com/h64d5791
				while (TRUE)
				{
					GetjILog()->Log(jLogT(STCB) ,jFUNC1 _T(" :WaitForMultipleObjects"));

					EventID = ::WaitForMultipleObjects(2, hEvent_Select_and_Destroy, FALSE, INFINITE);
					switch (EventID)
					{
					case WAIT_OBJECT_0:
						GetjILog()->Log(jLogT(STCB) ,jFUNC1 _T(" :WAIT_OBJECT_0 종료이벤트"));
						return;

					case WAIT_OBJECT_0 + 1:
						GetjILog()->Log(jLogT(STCB) ,jFUNC1 _T(" :mSelectEventHandle"));
						if(!m_pSocket) 
						{
							jWARN(_T(" :mSelectEventHandle : m_pSocket==NULL"));
							continue;
						}

						EventID = WSAEnumNetworkEvents(m_pSocket->GetSocket(), mSelectEventHandle, &NetworkEvents);

						if (EventID == SOCKET_ERROR)
						{
							jWARN(_T("SOCKET_ERROR WAIT_OBJECT_0 + 1"));
							return;
						}
						else
						{
							if (NetworkEvents.lNetworkEvents & FD_CONNECT)
							{
								GetjILog()->Log(jLogT(STCB) , jFUNC1 _T(" WAIT_OBJECT_0 + 1"));
								jSOCKADDR_IN in(m_pSocket->GetSocket());
								tname_t buf1;
								m_pSocket->GetAddress().ToString(buf1);
								m_pSocket->SetConnected(true);
								OnIoConnected(m_pSocket);

								if (NetworkEvents.iErrorCode[FD_CONNECT_BIT])
								{
									jWARN(_T("WAIT_OBJECT_0 + 1 NetworkEvents.iErrorCode[FD_CONNECT_BIT]"));
									return;
								}

								jNET_Plugin_callback_OnIoConnected(m_pPlugIn,m_pSocket);

							}
							else if (NetworkEvents.lNetworkEvents & FD_WRITE)
							{
								GetjILog()->Log(jLogT(STCB) ,jFUNC1 _T("FD_WRITE"));
								//OnIoWrote(m_pSocket);
							}
							else if (NetworkEvents.lNetworkEvents & FD_READ)
							{
								GetjILog()->Log(jLogT(STCB) , jFUNC1 _T("FD_READ"));
								OnIoRead(m_pSocket);
							}
							else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
							{
								m_pSocket->SetConnected(false);
								GetjILog()->Log(jLogT(STCB) , jFUNC1 _T("FD_CLOSE"));
								jNET_Plugin_callback_OnIoDisconnected(m_pPlugIn,m_pSocket);
								return;
							}
						}
						break;
					default:
						return;
					}
				}
			}

			jNetIOModel_EventSelect::jNetIOModel_EventSelect(VOID)
				:mSelectEventHandle(NULL)
				,m_pSocket(NULL)
			{
			}

			BOOL jNetIOModel_EventSelect::Begin(jPacketSocket_IOCP* pS)
			{
				if (!pS)	return FALSE;
				if (m_pSocket)	return FALSE;
				m_pSocket = pS;
				m_pSocket->m_pjIPacketDispatchTable = g_pjIPacketDispatch->Regist_NamedEvent(m_pPlugIn->m_pE);
				jASSERT0(m_pSocket->m_pjIPacketDispatchTable);

				try
				{
					mSelectEventHandle = WSACreateEvent();
					if (mSelectEventHandle == WSA_INVALID_EVENT) throw false;


					DWORD Result = WSAEventSelect(pS->GetSocket() , mSelectEventHandle
						, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
					if (Result == SOCKET_ERROR)
					{
						jLOG(jFUNC1 _T ("SOCKET_ERROR , WSAEventSelect"));
						throw false;
					}

					jt_sprintf(m_threadName, jFUNC1 _T(" %s"),m_pPlugIn->m_pE->GetTagName());
					nThread::thread_func_t f = boost::bind(&jNetIOModel_EventSelect::SelectThreadCallback,this,jBOOST__PLACEHODER_1 );
					g_pjIThreadManager->Run(f,m_pPlugIn->m_pE->GetTagName(),jS(SelectThreadCallback),true);
				}
				catch (bool isFail)
				{
					jWARN(_T("생성실패"));
					End();
					return isFail;
				}
				return TRUE;
			}

			void jNetIOModel_EventSelect::End()
			{
				if (!m_pSocket)
					return;
				m_pSocket=0;

				g_pjIThreadManager->End(m_pPlugIn->m_pE->GetTagName(),0);

				if (mSelectEventHandle)
					CloseHandle(mSelectEventHandle);
			}

		}// nNet::Impl

	} //nNET
}//nMech

