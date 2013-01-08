/* file : jClient_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-05-09 12:49:01
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jClient_IOCP_header__
#define __jClient_IOCP_header__
#pragma once

#include "ConnectedSessionManager.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			//--------------------------------------------------------------------------
			class jClient_IOCP : public jIObserver_IOCP , public jINetSession_Service
			//--------------------------------------------------------------------------
			{
				jINTERFACE_HEADER(jINetSession_Service);
			public:
				jClient_IOCP(jIProactor_IOCP* pIOCP,jIPlugIn_Connection* pPlugIn,jIE*);
				virtual ~jClient_IOCP(VOID);
				void PostDisconnectForProactor(VOID *pObject, OVERLAPPED *m_OVLP)
				{
					m_pProactor->PostDisconnect(pObject, m_OVLP);
				}


				jIProactor_IOCP* m_pProactor;
			private:
				jIPlugIn_Connection* m_pPlugIn;

			private: 
				//--------------------------------------------------------------------------
				// UDP관련
				//--------------------------------------------------------------------------
				jIVar* m_pvSizeQueue;

				jLIST_TYPEDEF_list(jPacketSocket_IOCP*,m_listUdpClientSocket);
				nMech::nUtil::jCriticalSection m_listUdpClientSocket_CS;
			public:
				VOID	ResetThreadCallbackUdp(nThread::jIThread*);
				//tname256_t m_threadName;
				tcstr		GetThreadName(){return m_pPlugIn->m_pE->GetTagName();}

				//--------------------------------------------------------------------------
				// TCP관련
				//--------------------------------------------------------------------------

			public:
				VOID OnIoRead(VOID *object, jPacketLen_t dataLength);
				VOID OnIoWrote(VOID *object, jPacketLen_t dataLength);
				VOID OnIoConnected(VOID *object);
				VOID OnIoDisconnected(VOID *object);


			bool Start(jIE* peNetNode);
			void End();

			jIPacketSocket_IOCP* add_ClientSocket(jIE* peSocketNode);
			void delete_ClientSocket(jIE* peSocketNode);
			};
#if 1
			//필요없는것.
			inline jIPacketSocket_IOCP* jClient_IOCP::ReadPacket(jNETARG_NUM_BUFF_LEN){return 0;}
			inline jIPacketSocket_IOCP* jClient_IOCP::ReadFromPacket(jNETARG_NUM_BUFF_LEN , jIP_Address*pIP){return 0;}
#endif
			inline jIPlugIn_Connection* jClient_IOCP::GetPlugIn(){ return m_pPlugIn;}

		}// nNet::Impl

	} //nNET
}//nMech



#endif // __jClient_IOCP_header__
