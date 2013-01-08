/* file : jNetIOModel_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:52:32
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Iocp_header__
#define __Iocp_header__
#pragma once

#include "jNet_Header.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{

			class jNetIOModel_IOCP : public jIProactor_IOCP
			{
			public:
				jNetIOModel_IOCP(int threadCount);
				virtual ~jNetIOModel_IOCP(VOID);

			private:
				HANDLE				mIocpHandle;
				DWORD				mWorkerThreadCount;

				jLIST_TYPEDEF_set(jIObserver_IOCP* ,m_Observers);

			public:
				// *_* by icandoit : 2007-06-05 12:43:51
				//http://blog.naver.com/h64d5791
				bool				Begin(jIObserver_IOCP* pObs);
				bool				RegisterSocket(SOCKET socket, ULONG_PTR completionKey);
				void				PostDisconnect(VOID *pObject, OVERLAPPED *m_OVLP)	{PostQueuedCompletionStatus(mIocpHandle, 0, (ULONG_PTR) pObject, m_OVLP);}
				bool				End(jIObserver_IOCP* pObs);
			
				VOID				WorkerThreadCallback(nThread::jIThread*);
			};

		}// nNet::Impl

	} //nNET
}//nMech



#endif // __Iocp_header__
