/* file : defualt_make_packet.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-10 22:04:49
comp.: t3.co.kr
title : 
desc : 


// ���ϰ� : net raw ����Ÿ�� �ѱ���.
int m_pF_make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH]			// �ӽ� ����
, int _pkOrgDataLen							// ���� App Logic ��Ŷ ����Ÿ ����
, uint _pkSqc								// ���� ��Ŷ�� �ο��� ���������� �����ϴ� ��Ŷ ��������ȣ
, int _pkCmd								// ��Ŷ �������� ��� ��ȣ
, BYTE* sendData)							// ���� App Logic ����Ÿ




// return �� : APP LOGIC���� ����� ��Ŷ ������ ������
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
				short		m_sPkLen;		//��Ŷ ����
				int			m_iPkSqc;		//��Ŷ ����
				int			m_iPkCmd;		//��Ŷ ���
			};

			typedef int get_raw_net_packet_size_t(IN BYTE* pNetRawBuffer);
			typedef int make_send_packet_t(BYTE TempBuffer[MAX_BUFFER_LENGTH],int _pkOrgDataLen
				,uint _pkSqc, int _pkCmd, BYTE* sendData);
			typedef BYTE* get_packet_info_from_raw_net_buffer_t(IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength);
			typedef int get_packet_command_t(/* �Է� */  IN BYTE* pInRawNetBuffer);


			int get_raw_net_packet_size(IN BYTE* pNetRawBuffer);
			int make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH],int _pkOrgDataLen
				,uint _pkSqc, int _pkCmd, BYTE* sendData);
			BYTE* get_packet_info_from_raw_net_buffer(IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength);
			int get_packet_command(/* �Է� */  IN BYTE* pInRawNetBuffer);

		}
	}
}




#endif // __defualt_make_packet_header__
