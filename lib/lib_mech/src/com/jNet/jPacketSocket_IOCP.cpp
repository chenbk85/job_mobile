#include "stdafx.h"
#include "Crypt.h"
#include "header/jCriticalSection.h"
#include "header/MultiThreadSync.h"
#include "jSocket_IOCP.h"
#include "jPacketSocket_IOCP.h"
#include "base/jMsgManager.h"

//#define m_CS_jPacketSocket_AUTOLOCK() jAUTO_LOCK_CS1(m_CS_jPacketSocket);

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{

			jDEFINE_SIMPLE_MEMORY( jPacketSocket_IOCP, 20 , 50 );


			bool jPacketSocket_IOCP::process_Client_OnIoReadFrom(nUTIL::jCircularQueueBuffer& q)
			{
				BYTE	 pReadBuff[MAX_BUFFER_LENGTH]	= {0,};
				jPacketLen_t	dwPacketLength				= 0;
				jPacketNum_t	dwProtocol					= 0;
				bool isRet = false;

				if (this->GetType()==eUDP_SOCKET)
				{
					jIP_Address ip(0,0);
					if (this->ReadFromPacketForEventSelect(&ip))
					{
						while (this->_getPacketFrom(&ip, dwProtocol, pReadBuff, dwPacketLength))
						{
							jCHECK(q.Push(this, dwProtocol, pReadBuff, dwPacketLength, &ip) );
							isRet =true;
						}
					}
				}
				else 
				{
					if (this->ReadPacketForEventSelect())
					{
						while (this->_getPacket(dwProtocol, pReadBuff, dwPacketLength))
						{
							if(dwProtocol==eNET_OGS_SYSTEM_MSG)
							{
								// jTODO jPacketNum_t수정됨. 작동하는지 확인 활것.
								if(dwPacketLength==sizeof(jPacketNum_t))
								{
									jPacketNum_t msg = *(jPacketNum_t*)pReadBuff;
									if(msg ==eNET_OGS_TCP_KeepAlive)
									{
										//GetjILog()->Log(jLogT(KTCB),jFUNC1 _T("KeepAliveMsg reached"));
									}
								}
								//return false;
								// *_* by icandoit : 2008-05-14 19:17:33
								continue;//를 사용해야할지 테스트 해야함.
							}
							if(dwProtocol==eNET_SEND_FILE)
							{
								jPARSE_eNET_SEND_FILE(this);

							}//if(dwProtocol==e NET_SEND_FILE)


							//jLOG(_T("%d  len= %d"),dwProtocol,dwPacketLength);
							q.Push(this, dwProtocol, pReadBuff, dwPacketLength);
							isRet = true;
						}
					}
				}
				if( isRet && pv_UseMsgThread->Get_bool() )
				{
					this->DoWakeUp_ReadSocket();
				}

				return isRet;
			}

			//--------------------------------------------------------------------------
			void jPacketSocket_IOCP::_PostCreate_PS(jIObserver_IOCP* pObs,int iSizeQueue)
			//--------------------------------------------------------------------------
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				jSocket_IOCP::_PostCreate(pObs,iSizeQueue);
				mWriteQueue._PostCreate(iSizeQueue);
#ifdef jUSE_mPacketBuffer
				//memset(m_RecvPacketBuffer, 0, sizeof(m_RecvPacketBuffer));
				mRemainLength			= 0;
				mReadOnlyBarier=123;

#else
				m_RecvPacketQueue._PostCreate(iSizeQueue);
				m_pCurrRecvPacket=0;
#endif
				m_pjIPacketDispatchTable=(0);
				m_pMsg_ReadSocket=(0);
				m_totPacketWrite=(0);
				m_totPacketRead=(0);
				m_pGridNode=(0);

				memset(&m_StartTime,0,sizeof(m_StartTime));
				m_pUserData=0;
				m_pE=0;
				mCurrentPacketOIDNumber	= 1;
				mLastReadPacketOIDNumber	= 1;
				// 접속 되었는지 판별하는 변수
				jt_strcpy(m_szSocketName,_T("NULL"));

				memset(&m_EnCodeInfo, 0, sizeof(m_EnCodeInfo));				
				m_jInfo_eNET_SEND_FILE_Recv.clear();
				m_jInfo_eNET_SEND_FILE_Send.clear();
				m_pM_CheckSendFile=0;
				m_iSendFile_SendActionTime=0;
			}

			jPacketSocket_IOCP::~jPacketSocket_IOCP(VOID)
			{
			}

			BOOL jPacketSocket_IOCP::Begin_Socket_PS()
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				m_iPACKET_HEADER_SIZE = sizeof(CPacketHeader);
				m_pf_get_raw_net_packet_size=get_raw_net_packet_size;
				m_pf_make_send_packet=make_send_packet;
				m_pf_get_packet_info_from_raw_net_buffer=get_packet_info_from_raw_net_buffer;
				m_pf_get_packet_command = get_packet_command;


				m_pSocketDebugPrint=0;
				mCurrentPacketOIDNumber	= 1;
				mLastReadPacketOIDNumber	= 1;

#ifdef jUSE_mPacketBuffer
				//memset(m_RecvPacketBuffer, 0, sizeof(m_RecvPacketBuffer));
				mRemainLength			= 0;
#else
				if (!m_RecvPacketQueue.Begin())
					return FALSE;
				m_pCurrRecvPacket=0;
#endif

				mWriteQueue_count=0;
				if (!mWriteQueue.Begin())
					return FALSE;
				

				GetjILog()->Log(jLogT(PSIOCP),_T("ERROR jPacketSocket_IOCP::Begin() "));
				return jSocket_IOCP::Begin_Socket();
			}
			void jPacketSocket_IOCP::Create()
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				SetFlag_IsDelete(false);

			}
			void jPacketSocket_IOCP::Destroy()
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				if(GetFlag_IsDelete()) return;
				SetFlag_IsDelete(true);

				{
					jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Recv_CS);
					m_jInfo_eNET_SEND_FILE_Recv.clear();
				}

				{
					jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Send_CS);
					m_jInfo_eNET_SEND_FILE_Send_it it = m_jInfo_eNET_SEND_FILE_Send.begin(),ie=m_jInfo_eNET_SEND_FILE_Send.end();
					for(;it!=ie;++it){ if(it->second)it->second->Erase();}
					m_jInfo_eNET_SEND_FILE_Send.clear();
				}

				if(m_pM_CheckSendFile)
				{
					m_pM_CheckSendFile->Erase();
					m_pM_CheckSendFile=0;
				}
#if 1
				if(m_pMsg_ReadSocket)
				{
					m_pMsg_ReadSocket->Erase();
					m_pMsg_ReadSocket=0;
				}
#endif
				if(m_pE)
				{
					m_pE->SetUserData(jS(jIPacketSocket_IOCP), 0);
				}
#ifdef jUSE_mPacketBuffer

#else
				m_RecvPacketQueue._PostDelete();
				m_pCurrRecvPacket=0;
#endif

				mWriteQueue._PostDelete();
				mLastReadPacketInfoVectorForUdp.clear();
				GetjILog()->Log(jLogT(PSIOCP),_T(" jPacketSocket_IOCP::Release() "));
				jSocket_IOCP::End_Socket(); // Retart()될때도 호출됨.
				jSocket_IOCP::_PostDelete();

			}
			BOOL jPacketSocket_IOCP::Restart(SOCKET hListenSocket)
			{jSocket_IOCP_NEW_DELELTE_DEBUG();
				if(m_pE)
				{
					m_pE->SetUserData(jS(jIPacketSocket_IOCP), 0);
				}
				SetFlag_IsConnected(false);
				mLastReadPacketInfoVectorForUdp.clear();
				GetjILog()->Log(jLogT(PSIOCP),_T(" jPacketSocket_IOCP::Restart() "));
				jSocket_IOCP::End_Socket();

				return Begin_Socket_PS() && Accept(hListenSocket);
			}
			bool jPacketSocket_IOCP::getPacketCommand(jPacketNum_t &outAppProtocalCmd)
			{
				jRETURN_ret(false,this->m_eType!=eNULL_SOCKET);
#ifdef jUSE_mPacketBuffer
				jRETURN_ret(false,mRemainLength >= this->m_iPACKET_HEADER_SIZE );
				int iNetRawPacketLength = this->m_pf_get_raw_net_packet_size(m_RecvPacketBuffer);
				if (iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0) // Invalid pOutPacketBuff
				{
					jERROR_T("iNetRawPacketLength %d > MAX_BUFFER_LENGTH %d || iNetRawPacketLength <= 0",iNetRawPacketLength , MAX_BUFFER_LENGTH );
					mRemainLength = 0;
					return false;
				}
				outAppProtocalCmd = this->m_pf_get_packet_command(m_RecvPacketBuffer);
#else
				jRETURN_ret(false,m_pCurrRecvPacket);
				int iNetRawPacketLength = this->m_pf_get_raw_net_packet_size(m_pCurrRecvPacket->GetBuffer());
				if (iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0) // Invalid pOutPacketBuff
				{
					jWARN_T("iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0");
					m_pCurrRecvPacket = 0;
					return false;
				}
				outAppProtocalCmd = this->m_pf_get_packet_command(m_pCurrRecvPacket->GetBuffer());
#endif
				return true;

			}

			BOOL jPacketSocket_IOCP::_getPacket(jPacketNum_t &outAppProtocalCmd, BYTE *pOutPacketBuff, jPacketLen_t &outAppPacketLength)
			{
				jRETURN_ret(false,this->m_eType!=eNULL_SOCKET);

				m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + outAppPacketLength;

				jRETURN_ret(false,pOutPacketBuff);

				int pkCmd=0;
				uint iPkSqc=0;
				int iAppPkLength=0;

#ifdef jUSE_mPacketBuffer
				//jvRETURN_ret(false, mRemainLength >= this->m_iPACKET_HEADER_SIZE,_T("%d < %d"),mRemainLength , this->m_iPACKET_HEADER_SIZE);
				if(mRemainLength < this->m_iPACKET_HEADER_SIZE) return FALSE;
				int iNetRawPacketLength = this->m_pf_get_raw_net_packet_size(m_RecvPacketBuffer);
				if (iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0) // Invalid pOutPacketBuff
				{
					jERROR_T("iNetRawPacketLength(%d) > MAX_BUFFER_LENGTH(%u) || iNetRawPacketLength <= 0",iNetRawPacketLength,MAX_BUFFER_LENGTH);
					mRemainLength = 0;
					return FALSE;
				}
// 				else
// 				{
// 					jLOG_T("iNetRawPacketLength = %d ,mRemainLength=%d",iNetRawPacketLength ,mRemainLength);
// 				}
				
				//jvRETURN_ret(false,iNetRawPacketLength <= mRemainLength,_T("%d <= %d"),iNetRawPacketLength,mRemainLength);
				if(iNetRawPacketLength > mRemainLength)
				{
					//jWARN(_T("iNetRawPacketLength %d <= mRemainLength %d"),iNetRawPacketLength,mRemainLength);
					return false;
				}

				BYTE* pAppDataBuff = this->m_pf_get_packet_info_from_raw_net_buffer(m_RecvPacketBuffer,iNetRawPacketLength
					,&pkCmd,&iPkSqc,&iAppPkLength);

#else
				jRETURN_ret(false,m_pCurrRecvPacket);
				int iNetRawPacketLength = this->m_pf_get_raw_net_packet_size(m_pCurrRecvPacket->GetBuffer());
				if (iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0) // Invalid pOutPacketBuff
				{
					jWARN_T("iNetRawPacketLength(%d) > MAX_BUFFER_LENGTH(%u) || iNetRawPacketLength <= 0",iNetRawPacketLength,MAX_BUFFER_LENGTH);
					m_pCurrRecvPacket = 0;
					return FALSE;
				}
				BYTE* pAppDataBuff = this->m_pf_get_packet_info_from_raw_net_buffer(m_pCurrRecvPacket->GetBuffer(),iNetRawPacketLength
					,&pkCmd,&iPkSqc,&iAppPkLength);

				jRETURN_ret(false,iNetRawPacketLength <= m_pCurrRecvPacket->GetBufferSize())
				if(iNetRawPacketLength > m_pCurrRecvPacket->GetBufferSize())return false;
#endif

				jPacketOID_t pkSeqCurr	= iPkSqc;
				outAppProtocalCmd		= pkCmd;
				outAppPacketLength	= iAppPkLength;

				memcpy(pOutPacketBuff, pAppDataBuff,outAppPacketLength );
#ifdef jUSE_mPacketBuffer
				if (mRemainLength - iNetRawPacketLength > 0)
					memmove(m_RecvPacketBuffer, m_RecvPacketBuffer + iNetRawPacketLength, mRemainLength - iNetRawPacketLength);
// 				else
// 				{
// 					jWARN_T("mRemainLength(%d) - iNetRawPacketLength(%d) > 0",mRemainLength,iNetRawPacketLength );
// 				}
				mRemainLength -= iNetRawPacketLength;
				if (mRemainLength < 0)
				{
					mRemainLength = 0;
				}
#else

#endif



				bool is = !pkSeqCurr || (pkSeqCurr> mLastReadPacketOIDNumber) ;
				if(!is)
				{
					jERROR_T("!pkSeqCurr || (pkSeqCurr(%u)> mLastReadPacketOIDNumber(%u)",pkSeqCurr, mLastReadPacketOIDNumber); 
					// 패킷번호가 이전것이거나 같을 경우(복사) 해당 패킷은 무시한다.
					return FALSE;
				}
				mLastReadPacketOIDNumber = pkSeqCurr;
				return TRUE;
			}


			BOOL jPacketSocket_IOCP::_getPacketFrom(jIP_Address* pIP
				, jPacketNum_t &outAppProtocalCmd
				, BYTE *pOutPacketBuff
				, jPacketLen_t &outAppPacketLength)
			{
				jRETURN_ret(FALSE,pOutPacketBuff);
				jRETURN_ret(FALSE,mRemainLength >= this->m_iPACKET_HEADER_SIZE);
				m_iPacketSize_UsageInfo =m_iPacketSize_UsageInfo + outAppPacketLength;

				int  iNetRawPacketLength = this->m_pf_get_raw_net_packet_size(m_RecvPacketBuffer);
				if (iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0) // Invalid pOutPacketBuff
				{
					jWARN_T("iNetRawPacketLength > MAX_BUFFER_LENGTH || iNetRawPacketLength <= 0");
					mRemainLength = 0;
					return FALSE;
				}
				jRETURN_ret(false,iNetRawPacketLength <= mRemainLength);

				int pkCmd=0;
				uint iPkSqc=0;
				int iAppPkLength=0;
				BYTE* pAppDataBuff = this->m_pf_get_packet_info_from_raw_net_buffer(
					// 입력 인자.
					m_RecvPacketBuffer // net raw 패킷 버퍼
					,iNetRawPacketLength // net raw packet 전체 사이즈
					// 출력 인자.
					,&pkCmd // 패킷 커맨드 번호
					,&iPkSqc // 패킷 시퀀스 번호
					,&iAppPkLength); // 로직 데이타의 패킷 사이즈

				if(!pAppDataBuff)  return false;
				outAppPacketLength = (jPacketLen_t)iAppPkLength;

				memcpy(pOutPacketBuff, pAppDataBuff, outAppPacketLength);
				outAppProtocalCmd		= pkCmd;

				if (mRemainLength - iNetRawPacketLength > 0)
					memmove(m_RecvPacketBuffer, m_RecvPacketBuffer + iNetRawPacketLength, mRemainLength - iNetRawPacketLength);

				mRemainLength -= iNetRawPacketLength;
				if (mRemainLength <= 0)
				{
					mRemainLength = 0;
					//memset(m_RecvPacketBuffer, 0, sizeof(m_RecvPacketBuffer));
				}
				for (DWORD i=0;i<mLastReadPacketInfoVectorForUdp.size();i++)
				{
					_READ_PACKET_INFO &ReadPacketInfo = mLastReadPacketInfoVectorForUdp[i];

					if (ReadPacketInfo.RemoteIP.m_IP.s_addr == pIP->m_IP.s_addr
						&& ReadPacketInfo.RemoteIP.port== pIP->port)
					{
						jRETURN_ret(FALSE, iPkSqc && (ReadPacketInfo.dwNetPacketOID >= iPkSqc));
						mLastReadPacketInfoVectorForUdp[i].dwNetPacketOID = iPkSqc;
						return TRUE;
					}
				}

				_READ_PACKET_INFO ReadPacketInfo;
				ReadPacketInfo.dwNetPacketOID = iPkSqc;
				ReadPacketInfo.RemoteIP = *pIP;
				mLastReadPacketInfoVectorForUdp.push_back(ReadPacketInfo);
				return TRUE;
			}
			// ReadPacketForIocp는 FALSE가 떨어질때 까지 while문을 돌린다.
			BOOL jPacketSocket_IOCP::ReadPacketForIocp(jPacketLen_t dwReadLength)
			{
				if(mRemainLength+dwReadLength >= sizeof(m_RecvPacketBuffer))
				{
					jERROR_T("소켓끊자.mRemainLength(%d)+dwReadLength(%d) >= sizeof(m_RecvPacketBuffer)(%d)",mRemainLength,dwReadLength,sizeof(m_RecvPacketBuffer));
					return FALSE;
				}
#ifdef _DEBUG
// 				if(dwReadLength>10000)
// 				{
// 					jLOG(jFUNC1 _T("prev dwReadLength=%d , mRemainLength=%d"),dwReadLength,mRemainLength);
// 				}
// 				else
// 				{
// 					jLOG(jFUNC1 _T("prev dwReadLength=%d , mRemainLength=%d"),dwReadLength,mRemainLength);
// 				}

#endif
				jRETURN_ret(FALSE,jSocket_IOCP::ReadForIocp(m_RecvPacketBuffer + mRemainLength, dwReadLength));

				mRemainLength	+= dwReadLength;
				m_totPacketRead +=dwReadLength;
#ifdef _DEBUG
// 				jLOG(jFUNC1 _T("post dwReadLength=%d , mRemainLength=%d"),dwReadLength,mRemainLength);
#endif

				//return getPacket(dwAppProtocolNumber, pPacketBuff, dwAppPacketLength);
				return TRUE;
			}

			// ReadPacketForEventSelect는 FALSE가 떨어질때 까지 while문을 돌린다.
			BOOL jPacketSocket_IOCP::ReadPacketForEventSelect(VOID)
			{
				jPacketLen_t dwReadLength = 0;
// 				if(mRemainLength+dwReadLength >= sizeof(m_RecvPacketBuffer))
// 				{
// 					jERROR_T("소켓끊자.mRemainLength(%d)+dwReadLength(%d) >= sizeof(m_RecvPacketBuffer)(%d)",mRemainLength,dwReadLength,sizeof(m_RecvPacketBuffer));
// 					return FALSE;
// 				}
				jRETURN_ret(FALSE, jSocket_IOCP::ReadForEventSelect(m_RecvPacketBuffer + mRemainLength, dwReadLength));
				mRemainLength	+= dwReadLength;
				m_totPacketRead +=dwReadLength;

				//return getPacket(dwAppProtocolNumber, pPacketBuff, dwAppPacketLength);
				return TRUE;
			}

			// ReadPacketForIocp는 FALSE가 떨어질때 까지 while문을 돌린다.
			BOOL jPacketSocket_IOCP::ReadFromPacketForIocp(jIP_Address* pIP, jPacketLen_t dwReadLength)
			{
				jRETURN_ret(FALSE,jSocket_IOCP::ReadFromForIocp(pIP, m_RecvPacketBuffer + mRemainLength, dwReadLength));
				mRemainLength	+= dwReadLength;
				m_totPacketRead +=dwReadLength;
				//return getPacket(pIP, dwAppProtocolNumber, pPacketBuff, dwAppPacketLength);
				return TRUE;
			}

			// ReadPacketForEventSelect는 FALSE가 떨어질때 까지 while문을 돌린다.
			BOOL jPacketSocket_IOCP::ReadFromPacketForEventSelect(jIP_Address* pIP)
			{
				jPacketLen_t ReadLength = 0;

				jRETURN_ret(FALSE,jSocket_IOCP::ReadFromForEventSelect(pIP, m_RecvPacketBuffer + mRemainLength, ReadLength));

				mRemainLength	+= ReadLength;
				m_totPacketRead +=ReadLength;

				//return getPacket(pIP, dwAppProtocolNumber, pPacketBuff, dwAppPacketLength);
				return TRUE;
			}

			
			BOOL jPacketSocket_IOCP::WritePacket(jPacket_Base* pP)
			{
				jRETURN_ret(FALSE,GetFlag_IsConnected());
				jRETURN_ret(FALSE,pP->buf);

				//2009/03/09 HMC jmToDo GPK
				//if( NULL != m_EnCodeInfo.EnFunc )	m_EnCodeInfo.EnFunc( pP->num, pP->buf, pP->len, m_EnCodeInfo.RandIdx );

				mCurrentPacketOIDNumber++;
				BYTE TempBuffer[MAX_BUFFER_LENGTH] = {0,};

				jPacketLen_t sendLen = (jPacketLen_t)m_pf_make_send_packet(TempBuffer,pP->len , mCurrentPacketOIDNumber,pP->num, pP->buf);
				jRETURN_ret(FALSE,sendLen > 0);
				if(sendLen> MAX_BUFFER_LENGTH)
				{
					jERROR_T("sendLen %d> MAX_BUFFER_LENGTH %d",sendLen, MAX_BUFFER_LENGTH);
					return FALSE;
				}

				// mWriteQueue를 이용해서 패킷이 전송 완료가 되었을까지 메모리를 살려둔다.
				BYTE *WriteData = mWriteQueue.Push(this, TempBuffer, sendLen);
				jRETURN_ret(FALSE,WriteData);

				++mWriteQueue_count;
				bool is = jSocket_IOCP::Write(WriteData, sendLen);
				m_totPacketWrite +=sendLen;

				if(GetFlag_IsNot_IOCP_Socket())	
					WriteComplete();

				return is;
			}

			BOOL jPacketSocket_IOCP::WriteToPacket_Direct(jIP_Address* pIP, jPacket_Base* pP)
			{
				//mCurrentPacketOIDNumber++;
				BYTE TempBuffer[MAX_BUFFER_LENGTH] = {0,};
				jPacketLen_t sendLen = (jPacketLen_t)m_pf_make_send_packet(TempBuffer,pP->len , 0,pP->num, pP->buf);
				jRETURN_ret(FALSE,sendLen >0) ;
				m_totPacketWrite +=sendLen;
				return jSocket_IOCP::WriteTo2(pIP, TempBuffer, sendLen);
			}

			BOOL jPacketSocket_IOCP::WriteToPacket(jIP_Address* pIP, jPacket_Base* pP)
			{
				jRETURN_ret(FALSE,pP->buf);
				mCurrentPacketOIDNumber++;
				BYTE TempBuffer[MAX_BUFFER_LENGTH] = {0,};
				jPacketLen_t sendLen = (jPacketLen_t)m_pf_make_send_packet(TempBuffer,pP->len , mCurrentPacketOIDNumber,pP->num, pP->buf);
				jRETURN_ret(FALSE,sendLen > 0);
				// mWriteQueue를 이용해서 패킷이 전송 완료가 되었을까지 메모리를 살려둔다.
				BYTE *WriteData = mWriteQueue.Push(this, TempBuffer, sendLen);
				jRETURN_ret(FALSE,WriteData);

				++mWriteQueue_count;
				// *_* by icandoit : 2007-06-05 14:56:04
				//http://memolog.blog.naver.com/h64d5791/40
				bool is = jSocket_IOCP::WriteTo(pIP, WriteData, sendLen);
				m_totPacketWrite +=sendLen;

				if(GetFlag_IsNot_IOCP_Socket())	
					WriteComplete();

				return is;
			}

			BOOL jPacketSocket_IOCP::WriteComplete(VOID)
			{
				//--mWriteQueue_count;
				return mWriteQueue.Pop();
			}

			BOOL jPacketSocket_IOCP::ResetUdp(VOID)
			{
				mLastReadPacketInfoVectorForUdp.clear();
				return TRUE;
			}


			tcstr jPacketSocket_IOCP::GetName(){ return m_szSocketName;}


			void jPacketSocket_IOCP::DebugPrint()
			{ 
				if(!m_pSocketDebugPrint) 
					return;
				m_pSocketDebugPrint(this);
			}

			//2009/03/09 HMC jmToDo GPK
			void jPacketSocket_IOCP::SetEncode_Decode_Func( const jEnCodeInfo& info  )
			{
				//m_EnCodeInfo = info;
			}

			VOID jPacketSocket_IOCP::SetConnected(BOOL bConnected) 
			{ 
				jSocket_IOCP_NEW_DELELTE_DEBUG();// GetjILog()->LogPlus(_T(" bConnected= %d"),bConnected);

				if(bConnected) GetLocalTime(&m_StartTime);
				SetFlag_IsConnected(bConnected);
				if(bConnected && m_eType!=eCONNECTING_SOCKET)// 서버쪽에서 관리되는 소켓이라면
				{
					//jIP_Address ip;
					//GetRemoteAddressAfterAccept(&ip);
					//GetAddress().Set(ip.m_IP.s_addr,ip.port);
					m_eType = eACCEPTED_SOCKET;
				}
			}

		}// nNet::Impl

	} //nNET
}//nMech


