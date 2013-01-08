
/* file : jSocket_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:50:59
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __NetworkSession_header__
#define __NetworkSession_header__
#pragma once

#include "jQueueManger.h"

//#define jSocket_IOCP_NEW_DELELTE_DEBUG() printf("###### " __FUNCTION__ "\n");
#define jSocket_IOCP_NEW_DELELTE_DEBUG()

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			class jSocket_IOCP 
				//: public nMech::nNET::nUTIL::CMultiThreadSync<jSocket_IOCP>
			{
			public:
				//nMech::nUtil::jCriticalSection m_CS_jSocket;
			private:
				int m_iFlag;
			public:
				jSET_FLAG(_IsDisConnected,jBIT_0);// jPacketSocket_IOCP에서 사용.
				jSET_FLAG(_IsNeedPostDisconProcess,jBIT_1);// jPacketSocket_IOCP에서 사용.
				jSET_FLAG(_IsConnected_jClient_IOCP,jBIT_2);// jClient_IOCP에서 사용.
				jSET_FLAG(_IsDisconnect_jClient_IOCP,jBIT_3);// jClient_IOCP에서 사용.
				jSET_FLAG(_IsDelete,jBIT_4);// jPacketSocket_IOCP에서 사용.
				jSET_FLAG(_IsConnected,jBIT_5);// jPacketSocket_IOCP에서 사용. 기존 m_bConnected변수역활. 접속되었는지 판별하는 변수 (for tcp)
				jSET_FLAG(_IsNot_IOCP_Socket,jBIT_6);// jPacketSocket_IOCP에서 사용. 기존의 m_IsNot_IOCP_Socket 
				


				void _PostCreate(jIObserver_IOCP* pObserver,int iSizeQueue); // 생성자의 역활
				void jSocket_IOCP::_PostDelete(VOID); // 소멸자의 역활.
				virtual BOOL			Begin_Socket(VOID);
				virtual BOOL			End_Socket(VOID);

				jSocket_IOCP::~jSocket_IOCP(){ _PostDelete();}

				// *_* by icandoit : 2007-06-05 12:43:51
				//http://memolog.blog.naver.com/h64d5791/2
				jOverlappedEx	mReadOverlapped;
			private:
				jOverlappedEx	mAcceptOverlapped;
				jOverlappedEx	mWriteOverlapped;

				BYTE			mReadBuffer[MAX_BUFFER_LENGTH];
				SOCKADDR_IN		m_UdpRecv_addr_in;

				SOCKET			mSocket;
				jSOCKADDR_IN mSocket_in;

				nThread::jIThread* m_pReliableUdpThread;
				tname256_t m_threadName;

				HANDLE			mReliableUdpWriteCompleteEvent;
				nUTIL::jCircularQueueBuffer	mReliableWriteQueue;
				BOOL			mIsReliableUdpSending;

			public:
				ESocket_Type m_eType;



				BOOL			Listen(cstr szIP, USHORT port, INT backLog);
				BOOL			Accept(SOCKET listenSocket);
				bool				assept(SOCKET listenSocket);
				BOOL			TcpBind(VOID);
				BOOL			UdpBind(cstr szIP,USHORT port);

				jSOCKADDR_IN &GetAddress(){return mSocket_in;}

				BOOL			InitializeReadForIocp(VOID);
				BOOL			ReadForIocp(BYTE *data, jPacketLen_t &dataLength);
				BOOL			ReadForEventSelect(BYTE *data, jPacketLen_t &dataLength);

				BOOL			Write(BYTE *data, jPacketLen_t dataLength);

				BOOL			InitializeReadFromForIocp(VOID);
				BOOL			ReadFromForIocp(jIP_Address* pIP, BYTE *data, jPacketLen_t &dataLength);
				BOOL			ReadFromForEventSelect(jIP_Address* pIP, BYTE *data, jPacketLen_t &dataLength);

				BOOL			WriteTo(jIP_Address* pIP, BYTE *data, jPacketLen_t dataLength);
				BOOL			WriteTo2(jIP_Address* pIP, BYTE *data, jPacketLen_t dataLength);

				BOOL			Connect(cstr address, USHORT port);

				SOCKET			GetSocket(VOID){	return mSocket;}

				BOOL			GetRemoteAddressAfterAccept(jIP_Address* pIP);

				VOID			ReliableUdpThreadCallback(nThread::jIThread*);
				void			ProcessMessage(cstr sz, void* pData);

			private:
				struct _jSendData
				{
					jIP_Address m_IPAddr;
					BYTE				m_cData[MAX_BUFFER_LENGTH];
					jPacketLen_t				m_iDataLength	;
					VOID				*m_pObject;
					_jSendData()
					{
						m_IPAddr.m_IP.s_addr=0;
						m_IPAddr.port= 0;
						m_cData[0]=0;
						m_iDataLength	= 0;
						m_pObject= NULL;
					}

				};

				bool _pop_QueueData(_jSendData& sd);

			};//class jSocket_IOCP 

		}// nNet::Impl

	} //nNET
}//nMech

#endif // __NetworkSession_header