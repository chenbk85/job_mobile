#pragma once
#include "protocol.h"

#pragma pack(push,1)
//
// 메시지 구조체는 여기다 정의한다.
//
struct _jNetPacket
{
	WORD		wID;
};
struct jDefaultPacket : public _jNetPacket
{
	char		szMsg[1];
};

struct CHAT_PACKET : public _jNetPacket
{
	BYTE	bStrLength;
	char	szMsg[MAX_CHAT_MSG_LENGHT];
	DWORD	GetPacketSize() 
	{
		return (DWORD)bStrLength+sizeof(_jNetPacket) + sizeof(BYTE);
	}
	CHAT_PACKET(char* msg)
	{
		wID = PTCL_CHAT_BROADCAST;
		bStrLength = lstrlen(msg);
		memcpy(szMsg,msg,bStrLength+1 );
	}
};

struct TEST_PACKET : public _jNetPacket
{
	unsigned int		socket;
	char				szBuf[MAX_PACKET_SIZE-4];
	TEST_PACKET(unsigned int s,WORD len)
	{
		socket = s;
		wID = PTCL_TEST;
	}
};

#pragma pack(pop)