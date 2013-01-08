/* file : defualt_make_packet.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-10 21:39:07
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "defualt_make_packet.h"


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{

			// 리턴값 : net raw 데이타의 총길이.
			int make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH]			// 임시 버퍼
			, int _pkOrgDataLen							// 보낼 App Logic 패킷 데이타 길이
				, uint _pkSqc								// 보낼 패킷에 부여될 고유적으로 증가하는 패킷 시컨스번호
				, int _pkCmd								// 패킷 프로토콜 명령 번호
				, BYTE* sendData)							// 보낼 App Logic 데이타
			{
				int pkNetDataLen = sizeof(CPacketHeader) + _pkOrgDataLen;

				if (pkNetDataLen >= MAX_BUFFER_LENGTH)
					return 0;

				CPacketHeader ph;
				ph.m_sPkLen = pkNetDataLen;
				ph.m_iPkSqc = _pkSqc;
				ph.m_iPkCmd = _pkCmd;

				memcpy(TempBuffer, &ph, sizeof(ph));
				memcpy(TempBuffer+sizeof(ph), sendData, _pkOrgDataLen);
				return (int)pkNetDataLen;
			}


			int get_raw_net_packet_size(BYTE* pNetRawBuffer)
			{
				short iNetRawPacketLength = 0;
				memcpy(&iNetRawPacketLength, pNetRawBuffer, sizeof(iNetRawPacketLength));
				//iNetRawPacketLength += sizeof(CPacketHeader);
				return (int)iNetRawPacketLength;
			}

			//--------------------------------------------------------------------------
			// return 값 : APP LOGIC에서 사용할 패킷 내용의 포인터
			BYTE* get_packet_info_from_raw_net_buffer(
				/* 입력 */  IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				/* 출력 */ ,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength)
			{
				CPacketHeader ph;
				memcpy(&ph, pInRawNetBuffer, sizeof(ph));

				*outPkCmd = ph.m_iPkCmd;
				*outAppPkLength = ph.m_sPkLen-sizeof(ph);
				*outPkSqc = ph.m_iPkSqc;
				return pInRawNetBuffer + sizeof(ph);
			}
			int get_packet_command(/* 입력 */  IN BYTE* pInRawNetBuffer)
			{
				CPacketHeader ph;
				memcpy(&ph, pInRawNetBuffer, sizeof(ph));
				return ph.m_iPkCmd;
			}


		}//namespace Impl
	}//namespace nNET
}//namespace nMech

