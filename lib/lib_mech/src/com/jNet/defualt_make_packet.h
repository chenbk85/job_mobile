/* file : defualt_make_packet.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-10 22:04:49
comp.: t3.co.kr
title : 
desc : 


// 리턴값 : net raw 데이타의 총길이.
int m_pF_make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH]			// 임시 버퍼
, int _pkOrgDataLen							// 보낼 App Logic 패킷 데이타 길이
, uint _pkSqc								// 보낼 패킷에 부여될 고유적으로 증가하는 패킷 시컨스번호
, int _pkCmd								// 패킷 프로토콜 명령 번호
, BYTE* sendData)							// 보낼 App Logic 데이타




// return 값 : APP LOGIC에서 사용할 패킷 내용의 포인터
BYTE* m_pF_get_packet_info_from_raw_net_buffer(
IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength)


*/

#ifndef __defualt_make_packet_header__
#define __defualt_make_packet_header__
#pragma once


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			struct CPacketHeader
			{
				short		m_sPkLen;		//패킷 길이
				int			m_iPkSqc;		//패킷 순서
				int			m_iPkCmd;		//패킷 명령
			};

			typedef int get_raw_net_packet_size_t(IN BYTE* pNetRawBuffer);
			typedef int make_send_packet_t(BYTE TempBuffer[MAX_BUFFER_LENGTH],int _pkOrgDataLen
				,uint _pkSqc, int _pkCmd, BYTE* sendData);
			typedef BYTE* get_packet_info_from_raw_net_buffer_t(IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength);
			typedef int get_packet_command_t(/* 입력 */  IN BYTE* pInRawNetBuffer);


			int get_raw_net_packet_size(IN BYTE* pNetRawBuffer);
			int make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH],int _pkOrgDataLen
				,uint _pkSqc, int _pkCmd, BYTE* sendData);
			BYTE* get_packet_info_from_raw_net_buffer(IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength);
			int get_packet_command(/* 입력 */  IN BYTE* pInRawNetBuffer);

		}
	}
}




#endif // __defualt_make_packet_header__
