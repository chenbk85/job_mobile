#ifndef PROTOCOL_H
#define PROTOCOL_H

enum	PTCL {
	PTCL_SERVER_UP					=	15,		// 한 서버가 재기동하면 다른 모든 서버로 접속한 후에 각각의 서버에 보낸다      
	PTCL_CHAT_BROADCAST				=	101,	// 유져 전체에게 보내는 메시지
	PTCL_TEST						=	255
};




#endif         