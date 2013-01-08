/* file : jNetIOModel_EventSelect.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:52:58
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __EventSelect_header__
#define __EventSelect_header__
#pragma once


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			class jNetIOModel_EventSelect 
			{
			public:
				virtual void	OnIoConnected(jPacketSocket_IOCP*)=0;
				virtual void 	OnIoRead(jPacketSocket_IOCP*)=0;
				virtual void	OnIoDisconnected(jPacketSocket_IOCP*)=0;

				jNetIOModel_EventSelect(VOID);

			private:
				HANDLE			mSelectEventHandle;
				jPacketSocket_IOCP* m_pSocket;

			public:
				jIPlugIn_Connection* m_pPlugIn;

				BOOL			Begin(jPacketSocket_IOCP* pS);
				void			End();

				VOID			SelectThreadCallback(nThread::jIThread*);
				tname256_t		m_threadName;
			};

		}// nNet::Impl

	} //nNET
}//nMech



#endif // __EventSelect_header__
