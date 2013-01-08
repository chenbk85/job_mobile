#pragma once

typedef enum _GAMEMESSAGE
{
	MSG_NONE = 0,
	MSG_CONNECT,
	MSG_GAMEDATA,
	MSG_DISCONNECT,
} GAMEMESSAGE;

struct NetworkPacket
{
	GAMEMESSAGE msg;
	int data;
};
