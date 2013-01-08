/* file : jNetSession_CS.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-03 13:40:28
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jNetSession_CS_header__
#define __jNetSession_CS_header__
#pragma once


#include "jNetIOModel_EventSelect_CS.h"
#include "jPacketSocket_IOCP.h"
#include "base/jMsgManager.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			// 클라이언트용 소켓객체(eventselect io모델을 사용)
			class jNetSession_CS 
				: public jNetIOModel_EventSelect_CS
				, public jINetSession_Service
			{
				jINTERFACE_HEADER(jINetSession_Service);
			public:
				jNetSession_CS(jIPlugIn_Connection* pPlugIn,jIE* );
				virtual ~jNetSession_CS(VOID);
				bool StartTcpServer(cstr szIP,int port ,jIE* peNet);

				nEVENT::jIMessage* GetMsgSockRead(){ return m_pMsgSockRead;}

				jIPacketSocket_IOCP*	ConnectTcp(jPacketSocket_IOCP* pS,tcstr szRemoteAddress, USHORT u18RemotePort,jIE* peSocketNode);
				jIPacketSocket_IOCP*	ConnectUdp(jPacketSocket_IOCP* pS,tcstr szIP,USHORT u18LocalPort ,jIE* peSocketNode);
				void EndService();

			private:
				int m_iSizeQueue;
				nEVENT::jIMessage* m_pMsgSockRead;

				nUTIL::jCircularQueueBuffer		mTcpReadPacketQueue;
				nUTIL::jCircularQueueBuffer		mUdpReadPacketQueue;
			protected:
				virtual bool			OnIoRead(jPacketSocket_IOCP* pS)
				{
					if(pS->GetType()==eUDP_SOCKET )
					{
						return pS->process_Client_OnIoReadFrom(mUdpReadPacketQueue );
					}
					else
					{
						return pS->process_Client_OnIoReadFrom(mTcpReadPacketQueue);
					}
				}
				virtual VOID			OnIoConnected(jPacketSocket_IOCP*);
				virtual void			OnIoDisconnected(jPacketSocket_IOCP*);

				jIVar* m_pvTcpServerEnable;


			};

			inline jIPlugIn_Connection* jNetSession_CS::GetPlugIn(){	return m_pPlugIn;}

		}// nNet::Impl

	} //nNET
}//nMech


#endif // __jNetSession_CS_header__
