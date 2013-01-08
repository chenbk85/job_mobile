/* file : jNetSession_Client.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:53:37
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __ClientSession_header__
#define __ClientSession_header__
#pragma once

#include "jNetIOModel_EventSelect.h"
#include "jPacketSocket_IOCP.h"


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			// 클라이언트용 소켓객체(eventselect io모델을 사용)
			class jNetSession_Client : public jNetIOModel_EventSelect , public jINetSession_Service
			{
				//jNetIOModel_EventSelect의 인터페이스구현
				virtual void	OnIoConnected(jPacketSocket_IOCP*);
				virtual void 	OnIoRead(jPacketSocket_IOCP*);
				virtual void	OnIoDisconnected(jPacketSocket_IOCP*);

				jINTERFACE_HEADER(jINetSession_Service);


			public:
				void _endService();// msg loop를 통해 EndService처리를 위함.
				jNetSession_Client(jIPlugIn_Connection* pPlugIn,jIE* );
				virtual ~jNetSession_Client(VOID);

				jIPacketSocket_IOCP*	ConnectTcp(tcstr szRemoteAddress, USHORT u18RemotePort,cstr szName);
				jIPacketSocket_IOCP*	ConnectUdp(tcstr szIP,USHORT u18LocalPort ,cstr szName);
				void EndService();



			private:
				int m_iSizeQueue;
				jPacketSocket_IOCP	*m_ClientSocketSession;

				nUTIL::jCircularQueueBuffer	mReadPacketQueue;
				int m_iFlag;
				jSET_FLAG(_StartService,jBIT_0);

			};

			inline jIPlugIn_Connection* jNetSession_Client::GetPlugIn(){	return m_pPlugIn;}
			inline void jNetSession_Client::OnIoConnected(jPacketSocket_IOCP*){}
		}// nNet::Impl

	} //nNET
}//nMech



#endif // __ClientSession_header__
