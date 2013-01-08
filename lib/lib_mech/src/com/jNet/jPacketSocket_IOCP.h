/* file : jPacketSocket_IOCP.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:51:59
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __PacketSession_header__
#define __PacketSession_header__
#pragma once

#include "jSocket_IOCP.h"
#include "base/jMsgManager.h"
#include "defualt_make_packet.h"

#define jUSE_mPacketBuffer

namespace nMech
{
	namespace nNET
	{
		const int iRECV_BUFFER_RESERVER=4;

		struct jIGridNode;
		namespace Impl
		{

			struct _READ_PACKET_INFO
			{
				jIP_Address RemoteIP;
				jPacketOID_t dwNetPacketOID;
			} ;

			class jPacketSocket_IOCP :	public jSocket_IOCP , public  jIPacketSocket_IOCP 
				, public nMech::nDataStruct::ySimpleNode<jPacketSocket_IOCP>
			{
			public:
				nMech::nUtil::jCriticalSection m_CS_jPacketSocket;
				jDECLEAR_SIMPLE_MEMORY(jPacketSocket_IOCP);

				virtual void Create(); //ySimpleNode용 생성자
				virtual void Destroy();//ySimpleNode용 소멸자
				virtual void CopyFrom(const jPacketSocket_IOCP*){jASSERT0(0);}//ySimpleNode용

				void			_PostCreate_PS(jIObserver_IOCP* pObs,int iSizeQueue);// 생성자의 역활
				virtual BOOL	Begin_Socket_PS(VOID); // 실제적인 소켓 초기화. 옛날코드 Begin() 를 이름 바꿈. 소켓 Restart될때도 호출.
				virtual ~jPacketSocket_IOCP(VOID);

				jINTERFACE_HEADER(jIPacketSocket_IOCP);

				int m_iPACKET_HEADER_SIZE;
				get_raw_net_packet_size_t *m_pf_get_raw_net_packet_size;
				make_send_packet_t* m_pf_make_send_packet;
				get_packet_info_from_raw_net_buffer_t* m_pf_get_packet_info_from_raw_net_buffer;
				get_packet_command_t *m_pf_get_packet_command;

				// 패킷포워딩용.
				bool getPacketCommand(jPacketNum_t &outAppProtocalCmd);

			private:
				uint64 m_totPacketWrite;// 패킷write량
				uint64 m_totPacketRead;// 패킷read량
				SYSTEMTIME m_StartTime;

				tname_t m_szSocketName;
#ifdef jUSE_mPacketBuffer
				BYTE								m_RecvPacketBuffer[MAX_BUFFER_LENGTH*iRECV_BUFFER_RESERVER]; 
				// 만약 보내는쪽에서 핸드세이크없이 send를 매우 많이 할때는 버퍼사이즈를 늘려주자.iRECV_BUFFER_RESERVER
				int									mReadOnlyBarier;
				int									mRemainLength;
#else
				jCircularQueueBuffer				m_RecvPacketQueue;
				_jNetQueueData*						m_pCurrRecvPacket;
#endif
				jPacketOID_t								mCurrentPacketOIDNumber;
				jPacketOID_t								mLastReadPacketOIDNumber;

				int mWriteQueue_count;

				//std::map<std::string, DWORD>		mLastReadPacketInfoMapForUdp;
				std::vector<_READ_PACKET_INFO>		mLastReadPacketInfoVectorForUdp;

				SocketDebugPrint_t *m_pSocketDebugPrint;
			public:
				const jIPacketDispatchTable* m_pjIPacketDispatchTable;
				jIE* m_pE;
				jIGridNode* m_pGridNode;
			private:
				nUTIL::jCircularQueueBuffer						mWriteQueue;
			public:
				nEVENT::jIMessage* m_pMsg_ReadSocket;
				void DoWakeUp_ReadSocket(){g_pjNet->DoWakeUp_Msg();}
			public:
				//2009/03/09 HMC jmToDo GPK
				jEnCodeInfo	m_EnCodeInfo;
			public:
				bool process_Client_OnIoReadFrom(nUTIL::jCircularQueueBuffer& q);
				void SetName(tcstr szName)
				{
					jt_strncpy(m_szSocketName, szName, sizeof(m_szSocketName) );
				}

				BOOL	ReadPacketForIocp(jPacketLen_t dwReadLength);
				BOOL	ReadPacketForEventSelect(VOID);

				BOOL	ReadFromPacketForIocp(jIP_Address* pIP, jPacketLen_t dwReadLength);
				BOOL	ReadFromPacketForEventSelect(jIP_Address* pIP);

				BOOL	WriteComplete(VOID);

				BOOL	ResetUdp(VOID);

				BOOL	_getPacket(jPacketNum_t &dwProtocol, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength);
				BOOL	_getPacketFrom(jIP_Address* pIP, jPacketNum_t &dwProtocol
													, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength);

				//--------------------------------------------------------------------------
				// for tcp
				//--------------------------------------------------------------------------
				BOOL Restart(SOCKET hListenSocket);
				VOID SetConnected(BOOL bConnected);
				BOOL GetConnected() { return GetFlag_IsConnected(); }
				void* m_pUserData;
				jIPacketSocket_IOCP* BaseI(){ return dynamic_cast<jIPacketSocket_IOCP*>(this);}


				//--------------------------------------------------------------------------
				// eNET_SEND_FILE관련.
				//--------------------------------------------------------------------------
			public:
				struct jInfo_eNET_SEND_FILE_Recv
				{
					send_file_cookie_t cookie;
					tstring sPath;
					tstring sJobThread;
					tstring sTempFile;
					uint32 m_iWriteCount;// 현제까지 받은 파일사이즈.
					DWORD m_BebinTime;
					int m_iFileSize;//받을 파일의 전체 사이즈.
					int m_iRecvCount; // 현제까지 받은 패킷수.
					jInfo_eNET_SEND_FILE_Recv()
						:m_iRecvCount(0), m_BebinTime(0),m_iWriteCount(0),cookie(0),m_iFileSize(0)
					{
					}
					bool deleteFile();
					bool createFile(send_file_cookie_t cookie , tcstr szPath,tcstr szJobThread,tcstr szIP,tcstr szRemotePath);
					bool saveFile(BYTE* buf,int iSize);
				};
				jLIST_TYPEDEF_map(send_file_cookie_t,jInfo_eNET_SEND_FILE_Recv,m_jInfo_eNET_SEND_FILE_Recv);
				nUtil::jCriticalSection m_jInfo_eNET_SEND_FILE_Recv_CS;

				jLIST_TYPEDEF_map(send_file_cookie_t,nEVENT::jIMessage*,m_jInfo_eNET_SEND_FILE_Send);
				nUtil::jCriticalSection m_jInfo_eNET_SEND_FILE_Send_CS;
				nEVENT::jIMessage* m_pM_CheckSendFile;// 파일 송신루틴이 작동중인 3초마다 체크.
				DWORD m_iSendFile_SendActionTime;// 마지막으로 송신이 작동한 시간.
private:
				void regist_CheckSendFile();
public:
				ESendFile Recv_eNET_SEND_FILE(BYTE *pReadBuff,jPacketLen_t dwPacketLength,OUT jPacket_Base& pk);
			};

			inline jIGridNode *jPacketSocket_IOCP::GetGridNode(){ return m_pGridNode;}
			inline jIE* jPacketSocket_IOCP::Get_jIE(){return m_pE;}
			inline ESocket_Type jPacketSocket_IOCP::GetType(){ return jSocket_IOCP::m_eType;}
			inline cstr jPacketSocket_IOCP::GetIP(tname_t buf){	return jSocket_IOCP::GetAddress().GetIP(buf);}
			inline int jPacketSocket_IOCP::GetPort(){	return jSocket_IOCP::GetAddress().GetPort();}
			inline SOCKADDR_IN jPacketSocket_IOCP::GetAddressADDR(){ return jSocket_IOCP::GetAddress();}
			inline cstr jPacketSocket_IOCP::GetAddressString(fname_t buf){return jSocket_IOCP::GetAddress().ToString(buf);}
			inline void jPacketSocket_IOCP::SetUserData(void* v){ m_pUserData = v;}
			inline void* jPacketSocket_IOCP::GetUserData(){ return m_pUserData;}
			inline BOOL  jPacketSocket_IOCP::IsConnected(VOID){ return GetConnected();}
			inline void jPacketSocket_IOCP::SetDebugger(SocketDebugPrint_t* f){m_pSocketDebugPrint= f;}

			inline BOOL	jPacketSocket_IOCP::WritePacket(jPacket_Base& pP){return WritePacket(&pP);}
			inline BOOL	jPacketSocket_IOCP::WriteToPacket(jIP_Address* pIP, jPacket_Base& pP){return WriteToPacket(pIP,&pP);}
			inline BOOL	jPacketSocket_IOCP::WriteToPacket_Direct(jIP_Address* pIP, jPacket_Base& pP){return WriteToPacket_Direct(pIP,&pP);}


		}// nNet::Impl

	} //nNET
}//nMech


#define jPacketSocketTCP_IOCP_DELETE(X) 	jPacketSocket_IOCP::_erase(X);	X =0;

#endif // __PacketSession_header__
