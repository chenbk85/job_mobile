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

			// ���ϰ� : net raw ����Ÿ�� �ѱ���.
			int make_send_packet(BYTE TempBuffer[MAX_BUFFER_LENGTH]			// �ӽ� ����
			, int _pkOrgDataLen							// ���� App Logic ��Ŷ ����Ÿ ����
				, uint _pkSqc								// ���� ��Ŷ�� �ο��� ���������� �����ϴ� ��Ŷ ��������ȣ
				, int _pkCmd								// ��Ŷ �������� ��� ��ȣ
				, BYTE* sendData)							// ���� App Logic ����Ÿ
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
			// return �� : APP LOGIC���� ����� ��Ŷ ������ ������
			BYTE* get_packet_info_from_raw_net_buffer(
				/* �Է� */  IN BYTE* pInRawNetBuffer ,IN int inRawNetPkLength
				/* ��� */ ,OUT int* outPkCmd ,OUT uint* outPkSqc ,OUT int* outAppPkLength)
			{
				CPacketHeader ph;
				memcpy(&ph, pInRawNetBuffer, sizeof(ph));

				*outPkCmd = ph.m_iPkCmd;
				*outAppPkLength = ph.m_sPkLen-sizeof(ph);
				*outPkSqc = ph.m_iPkSqc;
				return pInRawNetBuffer + sizeof(ph);
			}
			int get_packet_command(/* �Է� */  IN BYTE* pInRawNetBuffer)
			{
				CPacketHeader ph;
				memcpy(&ph, pInRawNetBuffer, sizeof(ph));
				return ph.m_iPkCmd;
			}


		}//namespace Impl
	}//namespace nNET
}//namespace nMech

