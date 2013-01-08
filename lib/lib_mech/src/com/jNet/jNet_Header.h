/* file : Global.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:52:49
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Global_heaasdf234234sdfewasasdfder__
#define __Global_heaasdf234234sdfewasasdfder__
#pragma once

#include "common/jCommon.h"

//#import "C:\\Program Files\\Common Files\\System\\ADO\\msado15.dll" rename("EOF"), "EndOfFile") no_namespace

// *_* by icandoit : 2007-06-05 10:31:44 unicode

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			struct jIObserver_IOCP
			{
				virtual tcstr		GetThreadName()=0;
				virtual VOID		OnIoRead(VOID *object, jPacketLen_t dataLength)	= 0;
				virtual VOID		OnIoWrote(VOID *object, jPacketLen_t dataLength)	= 0;
				virtual VOID		OnIoConnected(VOID *object)					= 0;
				virtual VOID		OnIoDisconnected(VOID *object)				= 0;
			};

			struct jIProactor_IOCP
			{
				virtual bool			Begin(jIObserver_IOCP* pObs)=0;
				virtual bool			RegisterSocket(SOCKET socket, ULONG_PTR completionKey)=0;
				virtual void			PostDisconnect(void *pObject, OVERLAPPED *m_OVLP)=0;
				virtual bool			End(jIObserver_IOCP* pObs)=0;
			};


			enum EIO_Type
			{
				eIO_ACCEPT,
				eIO_READ,
				eIO_WRITE,
			};

			struct jOverlappedEx
			{
				OVERLAPPED		m_OVLP;
				EIO_Type		m_eIoType;
				VOID			*m_pVoid;
				jIObserver_IOCP	*m_pObserver;
			} ;

		}//namespace Impl
	}//namespace nNET
}//namespace nMech

#include "header/MultiThreadSync.h"
#include "header/MemoryPool.h"
#include "jSocket_IOCP.h"
#include "jPacketSocket_IOCP.h"
#include "header/nNET_stream.h"
#include "MiniDump.h"



#endif // __Global_heaasdf234234sdfewasasdfder__
