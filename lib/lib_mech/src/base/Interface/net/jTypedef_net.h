/* file : jTypedef_net.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-31 18:05:15
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jTypedef_net_header__
#define __jTypedef_net_header__
#pragma once

#include <WinSock2.h>

namespace nMech
{
	namespace nNET
	{
#ifdef UNICODE
#define jSERVER_CHAR WCHAR
#define jSERVER_LPCSTR LPCWSTR
#define jSERVER_LPSTR LPWSTR
#else
#define jSERVER_CHAR TCHAR
#define jSERVER_LPCSTR LPCTSTR
#define jSERVER_LPSTR LPTSTR
#endif


		const int MAX_BUFFER_LENGTH	=4096*2*2; //�ѹ��� �ְ� ������ �ִ� ������ �ִ� ũ��.
		const int MAX_BUFFER_HEADER_LENGTH=100; //��Ŷ �ش��� �ִ� ũ��.
		const int MAX_SEND_DATA_SIZE=MAX_BUFFER_LENGTH-MAX_BUFFER_HEADER_LENGTH;// �ѹ��� ���� ������ �ִ� ����Ÿ

		typedef CHAR* str_n;//��Ʈ�� api�� . �����ڵ� ���ýÿ��� �ٲٸ� �ȵ�
		typedef const CHAR* cstr_n;// ��Ʈ�� api�� 
		typedef CHAR jIPString[32];
		typedef CHAR name_n[32];
#ifdef J_NET_ORGINAL
		typedef uint32 jPacketNum_t;// ��Ŷ��ȣ�� �ڷ���
		typedef uint32 jPacketLen_t;// ��Ŷũ���� �ڷ���.
		typedef uint32 jPacketOID_t; // ��Ŷ ���� id �ڷ���
#else
		typedef uint16 jPacketNum_t;// ��Ŷ��ȣ�� �ڷ���
		typedef uint16 jPacketLen_t;// ��Ŷũ���� �ڷ���.
		typedef uint32 jPacketOID_t; // ��Ŷ ���� id �ڷ���
#endif
		struct jPacket_Info	
		{		
			jPacketLen_t len;		
			jPacketNum_t num;	
		};
		struct jPacket_Base : public jPacket_Info	
		{	
			BYTE* buf;	
			jPacketLen_t GetLen(){ return len;}
			jPacketNum_t GetNum(){ return num;}
		};

		struct jIP_Address // this is host's ulong ip and host's ushort port
		{
			in_addr m_IP;	
			unsigned short port;
			bool operator ==(const jIP_Address& ip)const {return (m_IP.s_addr==ip.m_IP.s_addr) && (port==ip.port);}
			bool operator <(const jIP_Address& ip)const {return (m_IP.s_addr<ip.m_IP.s_addr) || (port<ip.port);}
			jIP_Address(){m_IP.s_addr=0;port=0;}
			jIP_Address(unsigned long ip,unsigned short _port){m_IP.s_addr= ip; port=_port;}

			struct less
			{
				bool operator()( const jIP_Address& ip1, const jIP_Address& ip2 ) const
				{
					return (ip1.m_IP.s_addr<ip2.m_IP.s_addr ) || (ip1.port < ip2.port);
				}
			};


		};
		struct jIP_String
		{
			jIPString m_IP;//"127.0.0.1"
			unsigned short port;
			jIP_String()
			{
				m_IP[0] = 0;
				port= 0;
			}
		};
		struct jIP_String2 // "127.0.0.1:1234"
		{
			name_n m_szIPStr;
		};


		enum EProtocal_jINet_OGS
		{
			EProtocal_jINet_OGS_BEGIN,
			eNET_OGS_SYSTEM_MSG, 
			eNET_OGS_TCP_KeepAlive,
			eNET_OGS_RUDP_AckNumber,
			eNET_OGS_CONNECT_UDP,
			eNET_OGS_DISCONNECT_UDP,
			eNET_GRID_WHO_ARE_YOU,
			eNET_GRID_I_AM_WHO,
			eNET_SEND_FILE,
			EProtocal_jINet_OGS_END
		};

	}
}

#define jRAISE_PACKET jRAISE
#endif // __jTypedef_net_header__
